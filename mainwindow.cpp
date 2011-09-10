#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mapinfo.h"
#include "mapbase.h"
#include "mapmanager.h"
#include "sprite.h"
#include "inmapitemdialog.h"
#include "dragreceiveritem.h"
#include <QObject>
#include <QCloseEvent>
#include <QMessageBox>
#include <QDebug>
#include <QFileDialog>
#include <QColorDialog>
#include <QList>
#include <QTimer>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QPixmap>
#include <QBitmap>
#include <typeinfo>

const char* DEF_BASE = "base1.png";

static QString base(DEF_BASE);

MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent),
    ui(new Ui::MainWindow),
    opened(false),
    changed(false)
{

    scene = new QGraphicsScene(this);
    itemSelectScene = new QGraphicsScene(this);
    timer = new QTimer(this);
    curMapInfo = 0;
    bakMapInfo = 0;
    curSprite = 0;
    select = 0;
    drag = 0;
    copyItem = 0;
    baseItems = new Sprite();
    manager = new MapManager(scene);
    ui->setupUi(this); //选择背景图片

    this->timer->setInterval(600);
    connect(this->timer,SIGNAL(timeout()),this,SLOT(time_out()));

    //初始化布局大小
    //this->setWindowFlags(Qt::WindowMinimizeButtonHint);
    this->setFixedSize(this->width(),this->height());

    this->ui->graphicsView->setScene(this->scene);

    this->ui->items_GraphicsView->setScene(this->itemSelectScene);

    this->ui->pasteMapItemAction->setEnabled(false);  //粘贴一开始失效

    connect(this->baseItems,SIGNAL(onMousePress(qreal,qreal,Qt::MouseButtons)),this,SLOT(base_items_on_mouse_press(qreal,qreal,Qt::MouseButtons)));

    if(!this->timer->isActive()){
        this->timer->start();
    }
    delete select;
}

MainWindow::~MainWindow()
{
    delete this->timer;
    delete this->curMapInfo;
    delete this->select;
    delete this->ui;
    delete this->scene;
    delete this->baseItems;
    delete this->itemSelectScene;
}

void MainWindow::reset()
{
    this->ui->mapitemViewAction->setCheckable(true);
    this->ui->mapbaseViewAction->setCheckable(true);
    this->scene->clear();
}
//初始化地图
void MainWindow::initByMapInfo(MapInfo *map)
{

    this->curSprite = 0;     //必须设置为0后在删除，因为timer时刻正访问curSprite
    delete this->curMapInfo; //不能删除this->curSprite 因为已包含在curMapInfo中
    reset();
    this->curMapInfo = map;

    this->ui->lineEdit_name->setText(this->curMapInfo->name);

    this->ui->lineEdit_bgcolor->setText(this->curMapInfo->background.name().mid(1));

    this->ui->label_color->setStyleSheet(QObject::tr("QLabel{background:%1}").arg(this->curMapInfo->background.name()));

    this->ui->lineEdit_type->setText(QVariant(this->curMapInfo->type).toString());

    this->ui->width_spinBox->setValue(this->curMapInfo->width);

    this->ui->height_spinBox->setValue(this->curMapInfo->height);

    int i;

    if(this->ui->mapbaseAction->isChecked()){//根据菜单选择状态 初始化操作
        QList<MapBase*> list = this->curMapInfo->getMapBaseInfo();
        for(i=0;i<list.length();i++){
            this->regSignalForMapBase(list.at(i));
        }
    }else if(this->ui->mapitemAction->isChecked()){
        QList<MapItem*> list1 = this->curMapInfo->getMapItemInfo();
        for(i=0;i<list1.length();i++){
            this->regSignalForMapItem(list1.at(i));
        }
    }

    this->manager->initMap(this->curMapInfo);

    this->baseItems->setPixmap(this->curMapInfo->base);   //更新选择贴图区基本图片
    if(!this->itemSelectScene->items().contains(this->baseItems))
        this->itemSelectScene->addItem(this->baseItems);
    this->itemSelectScene->update();
    this->ui->items_GraphicsView->scroll(0,0);

}
//在选择区选择时加入的选区范围图示
void MainWindow::changeSelectBase(int mhindex,int mvindex)
{
    delete select;
    select = itemSelectScene->addRect( mhindex * curSprite->sizeH ,
                                          mvindex * curSprite->sizeV ,
                                          curSprite->sizeH ,
                                          curSprite->sizeV ,
                                          QPen(Qt::DashLine) ,
                                          QBrush(Qt::blue,Qt::Dense7Pattern)
                                          );

}
//连接 基本贴图点击信号
void MainWindow::regSignalForMapBase(MapBase* base)
{
    base->setFlags(QGraphicsItem::ItemIsFocusable);
    connect(base,SIGNAL(onKeyRelease(int)),this,SLOT(map_base_on_press(int)));
    connect(base,SIGNAL(onMousePress(qreal,qreal,Qt::MouseButtons)),this,SLOT(map_base_on_mouse_press(qreal,qreal,Qt::MouseButtons)));
}
//连接 物件点击信号
void MainWindow::regSignalForMapItem(MapItem *item)
{
    item->setFlags(QGraphicsItem::ItemIsFocusable);
    connect(item,SIGNAL(onKeyRelease(int)),this,SLOT(map_base_on_press(int)));
    connect(item,SIGNAL(onMousePress(qreal,qreal,Qt::MouseButtons)),this,SLOT(map_item_start_drag(qreal,qreal,Qt::MouseButtons)));

}
//贴图区-物件单击
void MainWindow::base_items_on_mouse_press(qreal x,qreal y,Qt::MouseButtons button)
{
    qDebug() << "select item";
    this->changed=true;
    if(this->curSprite){

        int _hindex = int( x / this->curSprite->sizeH);
        int _vindex = int( y / this->curSprite->sizeV);
        this->changeSelectBase(_hindex,_vindex);
        this->curSprite->hindex =_hindex;
        this->curSprite->vindex =_vindex;
    }
}

//编辑-物品贴图
void MainWindow::on_mapitemAction_triggered(bool checked)
{
    if(opened){

        ui->mapbaseAction->setChecked(!checked);
        int size = this->curMapInfo->getMapBaseInfo().size();
        for(int i = 0; i < size ;i++){
            Sprite* sprite = this->curMapInfo->getMapBaseInfo().at(i);
            sprite->disconnect(sprite,0,this,0);  //取消型号连接
        }
        size = this->curMapInfo->getMapItemInfo().size();
        for(int i = 0; i < size ;i++){
            MapItem* sprite = this->curMapInfo->getMapItemInfo().at(i);
            this->regSignalForMapItem(sprite);
        }
    }else{
        static_cast<QAction*>(this->sender())->setChecked(!checked);
        QMessageBox::information(this,tr("错误"),tr("需要打开一个文件"));
    }
}
//编辑-基本贴图
void MainWindow::on_mapbaseAction_triggered(bool checked)
{
    if(opened){

        ui->mapitemAction->setChecked(!checked);
        int size = this->curMapInfo->getMapItemInfo().size();
        for(int i = 0; i < size ;i++){
            Sprite* sprite = this->curMapInfo->getMapItemInfo().at(i);
            sprite->disconnect(sprite,0,this,0);
        }
        size = this->curMapInfo->getMapBaseInfo().size();
        for(int i = 0; i < size ;i++){
            MapBase* sprite = this->curMapInfo->getMapBaseInfo().at(i);
            this->regSignalForMapBase(sprite);
        }
    }else{
        static_cast<QAction*>(this->sender())->setChecked(!checked);
        QMessageBox::information(this,tr("错误"),tr("需要打开一个文件"));
    }
}
//文件-新建地图
void MainWindow::on_newAction_triggered()
{

    unsigned int i,j;

    MapInfo* map = new MapInfo(base);

    if(!this->bakMapInfo)this->bakMapInfo =  new MapInfo(base);

    QString tname = tr("新地图");
    map->name = tname;
    this->bakMapInfo->name = tname;
    map->background = QColor(Qt::black);
    this->bakMapInfo->background = QColor(Qt::black);
    map->height = 6;
    this->bakMapInfo->height = 6;
    map->width = 8;
    this->bakMapInfo->width = 8;
    map->type=1;
    this->bakMapInfo->type = 1;

    QList<MapBase*> list = map->getMapBaseInfo();
    for(j=0;j < map->height;j++){
        for(i=0;i < map->width;i++){

            MapBase* base1 = new MapBase(map->base);
            list.append(base1);
        }
    }
    map->setMapBaseInfo(list);

    this->initByMapInfo(map);
    this->opened=true;
    this->changed=true;
}
//文件-打开地图
void MainWindow::on_openAction_triggered()
{
    QString fileName;
    fileName = QFileDialog::getOpenFileName(this,tr("打开地图文件"), ".", tr("地图文件 (*.mdt)"));

    if(fileName.length()>0){

        MapInfo* map = new MapInfo(base);

        map->readMap(fileName);
        if(!this->bakMapInfo)this->bakMapInfo =  new MapInfo(base);

        this->bakMapInfo->name = map->name;
        this->bakMapInfo->width = map->width;
        this->bakMapInfo->height = map->height;
        this->bakMapInfo->type = map->type;
        this->bakMapInfo->background = map->background;

        this->opened = true;
        this->initByMapInfo(map);

    }
}
//保存地图按钮
void MainWindow::on_saveAction_triggered()
{
    if(opened){
        QString filename = QFileDialog::getSaveFileName(this,tr("保存地图文件"), ".", tr("地图文件 (*.mdt)"));
        if(filename.length()<=0) return;
        if(filename.indexOf(".mdt") == -1)
        {
            filename = filename + ".mdt";
        }
        this->curMapInfo->name = this->ui->lineEdit_name->text();
        this->curMapInfo->type = QVariant(this->ui->lineEdit_type->text()).toUInt();
        this->curMapInfo->writeMap(filename);
        this->changed = false;
    }else{
        QMessageBox::information(this,tr("错误"),tr("需要打开一个文件"));
    }
}

//操作区-贴图按键
void MainWindow::map_base_on_press(int key)
{
    MapBase* base = (MapBase*)(sender());
    if(key == Qt::Key_Space){
        if(base->isVisible()){
            base->hide();
        }else{
            base->show();
        }
    }else if(key == Qt::Key_1){
        base->hindex = 0;
        base->vindex = 0;
        base->update();
    }else if(key == Qt::Key_Delete){

        if(typeid(*(this->curSprite)) == typeid(MapItem)){ //RTTI 判断类型为MapItem时可以删除
            MapItem* item = dynamic_cast<MapItem*>(this->curSprite);
            this->manager->removeSprite(item,item->typeName);
            this->curMapInfo->getMapItemsPtr()->removeAll(item);
            delete item;
            this->curSprite = 0;
        }
    }

    qDebug()<< "key_press = " << key ;
}
//退出
void MainWindow::on_exitAction_triggered()
{
    int yn;

    isChange();

    if(this->changed)
        yn = QMessageBox::question(this,tr("是否保存"),tr("文件的修改是否保存"),QMessageBox::Yes|QMessageBox::No|QMessageBox::Cancel);
    else
        yn = QMessageBox::No;

    if(yn == QMessageBox::No){//不保存
        exit(0);
    }else if(yn == QMessageBox::Yes){ //保存
        on_saveAction_triggered();
        QApplication::exit();
    }
}
//操作区-基本贴图点击
void MainWindow::map_base_on_mouse_press(qreal x,qreal y,Qt::MouseButtons btns)
{
    MapBase* base = (MapBase*)(sender());
    if(btns == Qt::LeftButton){

        if(this->curSprite)this->curSprite->setOpacity(1);
        this->curSprite = base;
        this->ui->statusBar->clearMessage ();
        this->ui->statusBar->showMessage (" hindex:(" +
                                           QVariant(((MapBase*)(this->curSprite))->hindex).toString()
                                           + ") vindex:(" +
                                           QVariant(((MapBase*)(this->curSprite))->vindex).toString()
                                           + ") width:(" +
                                           QVariant(this->curSprite->getWidth()).toString()
                                           + ") height: (" +
                                           QVariant(this->curSprite->getHeight()).toString()
                                           + ") cols: (" +
                                           QVariant(((MapBase*)(this->curSprite))->iColnum).toString()
                                           + ") rows: (" +
                                           QVariant(((MapBase*)(this->curSprite))->iRownum).toString()
                                           + ") deepin: (" +
                                           QVariant(((MapBase*)(this->curSprite))->zValue()).toString()
                                           + ") "
                                           );
        this->changeSelectBase(this->curSprite->hindex,this->curSprite->vindex);
        ui->items_GraphicsView->centerOn(this->curSprite->hindex * this->curSprite->getWidth(),this->curSprite->vindex * this->curSprite->getHeight());

        if(!this->timer->isActive()){
            this->timer->start();
        }
    }
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    event->ignore();
    on_exitAction_triggered();
}

//背景选择编辑
void MainWindow::on_lineEdit_bgcolor_textEdited(QString colorname)
{
    this->changed = true;
    this->ui->label_color->setStyleSheet(tr("QLabel{background:#%1}").arg(colorname));
    this->curMapInfo->background = QColor("#"+colorname);
    this->scene->setBackgroundBrush(this->curMapInfo->background);
}

//背景颜色选择
void MainWindow::on_pushButton_clicked()
{

    QColorDialog dialog(this);
    QColor color;
    if(this->curMapInfo){
        color = dialog.getColor(this->curMapInfo->background);
    }else{
        color = dialog.getColor(QColor("#"+this->ui->lineEdit_bgcolor->text()));
    }
    this->ui->lineEdit_bgcolor->setText(color.name().mid(1));
    this->ui->label_color->setStyleSheet(tr("QLabel{background:%1}").arg(color.name()));
    this->curMapInfo->background = color;
    this->scene->setBackgroundBrush(this->curMapInfo->background);
}

//被选闪耀
void MainWindow::time_out()
{
    if(this->curSprite){
        if(this->curSprite->opacity() == 1)
            this->curSprite->setOpacity(0.5);
        else
            this->curSprite->setOpacity(1);
    }
}

/*
 * 修改地图大小
 */
//调整地图宽度
void MainWindow::on_width_spinBox_valueChanged(int value)
{

    if(this->curMapInfo){
        if((unsigned int)value > this->curMapInfo->width ){
            unsigned int i;
            QList<MapBase*> list = this->curMapInfo->getMapBaseInfo();
            for(i= 0 ; i < (((unsigned int)value - this->curMapInfo->width) * this->curMapInfo->height) ;i++){
                MapBase* tmpbase = new MapBase(this->curMapInfo->base);
                list.insert( (i+1)*this->curMapInfo->width + i ,tmpbase);
                this->regSignalForMapBase(tmpbase);
            }
            this->curMapInfo->width = (unsigned int)value;

            this->curMapInfo->setMapBaseInfo(list); //只能设置 get出来的list

            this->manager->initMap(this->curMapInfo);

        }
    }
    qDebug() << "value is " <<  value;
}
//调整地图高度
void MainWindow::on_height_spinBox_valueChanged(int value)
{

    if(this->curMapInfo){
        if( (unsigned int)value > this->curMapInfo->height ){
            unsigned int i;
            QList<MapBase*> list = this->curMapInfo->getMapBaseInfo();
            for(i= 0 ; i <this->curMapInfo->width ;i++){
                MapBase* tmpbase = new MapBase(this->curMapInfo->base);
                list.append(tmpbase);
                this->regSignalForMapBase(tmpbase);
            }
            this->curMapInfo->height = (unsigned int)value;

            this->curMapInfo->setMapBaseInfo(list); //只能设置 get出来的list

            this->manager->initMap(this->curMapInfo);

        }
    }
    qDebug() << "value is " <<  value;
}

//修改地图类型
void MainWindow::on_lineEdit_type_textChanged(const QString& type)
{
    if(this->curMapInfo){
        this->curMapInfo->type = type.toInt();
    }
    qDebug() << "type is " <<  type;
}


void MainWindow::on_lineEdit_name_textChanged(const QString& name)
{
    if(this->curMapInfo){
        this->curMapInfo->name = name;
    }
    qDebug() << "name is " <<  name;
}
/*
  检测当前文档属性是否变更
  */
bool MainWindow::isChange(){
    if(this->curMapInfo){  //检查属性变更
        if(this->curMapInfo->name != this->bakMapInfo->name)
            this->changed = true;

        if(this->curMapInfo->type != this->bakMapInfo->type)
            this->changed = true;

        if(this->curMapInfo->width != this->bakMapInfo->width)
            this->changed = true;

        if(this->curMapInfo->height != this->bakMapInfo->height)
            this->changed = true;

        if(this->curMapInfo->background != this->bakMapInfo->background)
            this->changed = true;
    }

    return this->changed;
}

bool MainWindow::isOpen()
{
    return this->opened;
}
//查看-显示背景
void MainWindow::on_mapbaseViewAction_triggered(bool checked)
{
    if(this->opened){
        QList<MapBase*> baseList = this->curMapInfo->getMapBaseInfo();
        foreach(MapBase* base,baseList){
            base->setVisible(checked);
        }
    }
}
//查看-显示物件
void MainWindow::on_mapitemViewAction_triggered(bool checked)
{
    if(this->opened){
        QList<MapItem*> itemList = this->curMapInfo->getMapItemInfo();
        foreach(MapItem* item,itemList){
            item->setVisible(checked);
        }
    }
}
//编辑-插入物件
void MainWindow::on_insertMapItemAction_triggered()
{
    if(isOpen()){
        InMapItemDialog dialog(this->curMapInfo,this->manager,0,this);
        dialog.setWindowTitle(tr("插入物件"));
        MapItem* insertItem = dialog.createMapItem();

        if(insertItem){ //创建物件成功
            this->curMapInfo->getMapItemsPtr()->append(insertItem); //加入到MapInfo里面
            insertItem->updateLocation();
            this->manager->addSprite(insertItem,insertItem->typeName,insertItem->mapZ);
            if(this->ui->mapitemAction->isChecked())this->regSignalForMapItem(insertItem);
        }
    }
}

//贴图文件开始拖动
void MainWindow::map_item_start_drag(qreal mx,qreal my,Qt::MouseButtons btn)
{
    MapBase* base = static_cast<MapBase*>(sender());

    if(btn == Qt::LeftButton){
        DragReceiverItem* obj = new DragReceiverItem( curMapInfo->width, curMapInfo->height, DEF_MAPBASE_WIDTH, DEF_MAPBASE_HEIGHT);

        connect(obj,SIGNAL(onDrop(QPointF,const QMimeData*)),this,SLOT(map_item_end_drag(QPointF,const QMimeData*)));

        this->manager->addSprite(obj,"frame");

        if(this->curSprite)this->curSprite->setOpacity(1); //恢复上个贴图显示
        this->curSprite = base;

        this->drag = new QDrag(this);

        QMimeData* data = new QMimeData();
        this->drag->setMimeData(data);

        QPixmap pixmap(this->curSprite->getWidth(),this->curSprite->getHeight());
        QPainter painter(&pixmap);

        //pixmap.fill(Qt::white);
        this->curSprite->paint(&painter,0,0);

        this->drag->setPixmap(pixmap);
        this->drag->setHotSpot(QPoint(this->curSprite->getWidth() / 2,this->curSprite->getHeight() / 2));

        this->drag->exec();   //开始拖拽, 释放拖拽执行下面代码

        this->manager->removeSprite(obj,"frame");

        disconnect(obj);

        #ifdef Q_WS_WIN
        delete drag;
        #endif
        delete obj;
    }
}
//贴图文件结束拖动
void MainWindow::map_item_end_drag(QPointF pos,const QMimeData* data)
{
    if(this->curSprite){
        qreal mx = pos.x();
        qreal my = pos.y();
        MapItem* tmp_item = static_cast<MapItem*>(this->curSprite);
        tmp_item->setPos(mx - static_cast<int>(mx) % DEF_MAPBASE_WIDTH,
                                my - static_cast<int>(my) % DEF_MAPBASE_HEIGHT);
        int x_bak = tmp_item->mapX;
        int y_bak = tmp_item->mapY;

        tmp_item->mapX = mx / static_cast<qreal>(DEF_MAPBASE_WIDTH);
        tmp_item->mapY = my / static_cast<qreal>(DEF_MAPBASE_HEIGHT);
        if(x_bak != tmp_item->mapX || y_bak != tmp_item->mapY)
            this->changed =true;

    }
}


//编辑-复制物件
void MainWindow::on_copyMapItemAction_triggered()
{
    if(this->curSprite && typeid(*this->curSprite) == typeid(MapItem)){
        MapItem* curItem = dynamic_cast<MapItem*>(this->curSprite);
        MapItem* item = new MapItem(this->curMapInfo->base);
        item->hindex = curItem->hindex;
        item->vindex = curItem->vindex;
        item->setIColnum(curItem->iColnum);
        item->setIRownum(curItem->iRownum);
        item->sizeV = curItem->sizeV;
        item->sizeH = curItem->sizeH;
        item->mapZ = curItem->mapZ;
        item->mapX = 1;
        item->mapY = 1;
        item->special = curItem->special;
        item->crossType = curItem->crossType;
        item->checkType = curItem->checkType;
        item->typeName = curItem->typeName;
        item->updateLocation();
        this->copyItem = item;
        this->ui->pasteMapItemAction->setEnabled(true);
    }else{
        QMessageBox::information(this,tr("操作错误"),tr("请选择一个物品"));
    }
}

//编辑-粘贴物件
void MainWindow::on_pasteMapItemAction_triggered()
{
    if(this->copyItem){
        MapItem* item = this->copyItem;
        this->manager->addSprite(item,item->typeName,item->mapZ);
        this->curMapInfo->getMapItemsPtr()->append(item);
        this->regSignalForMapItem(item);
    }
}
//编辑-修改物件
void MainWindow::on_changeMapItemAction_triggered()
{
    if(this->curSprite){
        if(typeid(*this->curSprite) == typeid(MapItem)){
            if(isOpen()){
                MapItem* item = static_cast<MapItem*>(this->curSprite);
                InMapItemDialog dialog(this->curMapInfo,this->manager,item,this);
                dialog.setWindowTitle(tr("修改物件"));
                MapItem* updateItem = dialog.createMapItem();

                if(updateItem){ //更新物件成功
                    updateItem->updateLocation();
                }
            }
        }
    }
}
