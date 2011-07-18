#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mapinfo.h"
#include "mapbase.h"
#include "mapmanager.h"
#include "sprite.h"
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

#define DEF_BASE "base1.png"

static QString base(DEF_BASE);

void MainWindow::initByMapInfo(MapInfo *map)
{

    if(this->curInfo)delete this->curInfo;

    this->curInfo = map;

    this->ui->lineEdit_name->setText(this->curInfo->name);

    this->ui->lineEdit_bgcolor->setText(this->curInfo->background.name().mid(1));

    this->ui->label_color->setStyleSheet(QObject::tr("QLabel{background:%1}").arg(this->curInfo->background.name()));

    this->ui->lineEdit_type->setText(QVariant(this->curInfo->type).toString());

    this->ui->width_spinBox->setValue(this->curInfo->width);

    this->ui->height_spinBox->setValue(this->curInfo->height);

    int i;
    QList<MapBase*> list = this->curInfo->getMapBaseInfo();
    for(i=0;i<list.length();i++){
        this->regHandleSignal(list.at(i));
    }
    QList<MapItem*> list1 = this->curInfo->getMapItemInfo();
    for(i=0;i<list1.length();i++){
        //this->regHandleSignal(list1.at(i));//物品无初始化事件

    }
    this->manager->initMap(this->curInfo);

    this->baseItems->setPixmap(this->curInfo->base);
    this->itemSelectScene->addItem(this->baseItems);
    this->itemSelectScene->update();
    this->ui->items_GraphicsView->scroll(0,0);
    //QGraphicsItemGroup* group = this->scene->createItemGroup(this->scene->items());
    //group->setPos(100,100);
    //this->scene->destroyItemGroup(group);
    //
    //this->scene->setSceneRect(0,0,780,600);
}
void MainWindow::changeSelectBase(int mhindex,int mvindex)
{
    if(select)delete select;
    select = itemSelectScene->addRect( mhindex * curSprite->sizeH ,
                                          mvindex * curSprite->sizeV ,
                                          curSprite->sizeH ,
                                          curSprite->sizeV ,
                                          QPen(Qt::DashLine) ,
                                          QBrush(Qt::blue,Qt::Dense7Pattern)
                                          );

}
void MainWindow::regHandleSignal(Sprite* sprite)
{

    sprite->setFlags(QGraphicsItem::ItemIsFocusable);
    this->connect(sprite,SIGNAL(onKeyRelease(int)),this,SLOT(map_base_on_press(int)));
    this->connect(sprite,SIGNAL(onMousePress(qreal,qreal,Qt::MouseButtons)),this,SLOT(map_base_on_mouse_press(qreal,qreal,Qt::MouseButtons)));
}
MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent),
    ui(new Ui::MainWindow),
    opened(false),
    changed(false)
{

    scene = new QGraphicsScene(this);
    itemSelectScene = new QGraphicsScene(this);
    timer = new QTimer(this);
    curInfo = 0;
    curSprite = 0;
    select = 0;
    baseItems = new Sprite();
    manager = new MapManager(scene);
    ui->setupUi(this); //选择背景图片

    this->timer->setInterval(500);
    connect(this->timer,SIGNAL(timeout()),this,SLOT(time_out()));

    this->ui->graphicsView->setScene(this->scene);
    //connect(ui->mapitemAction,SIGNAL(triggered()),this,SLOT(on_mapitemAction_triggered()));
    this->ui->items_GraphicsView->setScene(this->itemSelectScene);
    //this->ui->items_GraphicsView->setSceneRect(0,0,800,600);
    connect(this->baseItems,SIGNAL(onMousePress(qreal,qreal,Qt::MouseButtons)),this,SLOT(base_items_on_mouse_press(qreal,qreal,Qt::MouseButtons)));
}

MainWindow::~MainWindow()
{

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
//文件-新建地图
void MainWindow::on_newAction_triggered()
{

    unsigned int i,j;

    MapInfo* map = new MapInfo(base);

    map->name = tr("新地图");
    map->background = QColor(Qt::black);
    map->height = 6;
    map->width = 8;
    map->type=1;
    QList<MapBase*> list = map->getMapBaseInfo();
    for(j=0;j < map->height;j++){
        for(i=0;i < map->width;i++){

            MapBase* base1 = new MapBase(map->base);
            list.append(base1);
        }
    }
    map->setMapBaseInfo(list);

    this->initByMapInfo(map);
    this->changed=true;
}

//编辑-物品贴图
void MainWindow::on_mapitemAction_triggered(bool checked)
{
    if(opened){
        qDebug()<< checked ;
        ui->mapbaseAction->setChecked(!checked);
        int size = this->curInfo->getMapBaseInfo().size();
        for(int i = 0; i < size ;i++){
            Sprite* sprite = this->curInfo->getMapBaseInfo().at(i);
            sprite->disconnect(sprite,0,this,0);
        }
        size = this->curInfo->getMapItemInfo().size();
        for(int i = 0; i < size ;i++){
            Sprite* sprite = this->curInfo->getMapItemInfo().at(i);
            this->regHandleSignal(sprite);
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
        qDebug()<< checked;
        ui->mapitemAction->setChecked(!checked);
        int size = this->curInfo->getMapItemInfo().size();
        for(int i = 0; i < size ;i++){
            Sprite* sprite = this->curInfo->getMapItemInfo().at(i);
            sprite->disconnect(sprite,0,this,0);
        }
        size = this->curInfo->getMapBaseInfo().size();
        for(int i = 0; i < size ;i++){
            Sprite* sprite = this->curInfo->getMapBaseInfo().at(i);
            this->regHandleSignal(sprite);
        }
    }else{
        static_cast<QAction*>(this->sender())->setChecked(!checked);
        QMessageBox::information(this,tr("错误"),tr("需要打开一个文件"));
    }
}

//文件-打开地图
void MainWindow::on_openAction_triggered()
{
    QString fileName;
    fileName = QFileDialog::getOpenFileName(this,tr("打开地图文件"), ".", tr("地图文件 (*.mdt)"));

    if(fileName.length()>0){

        MapInfo* map = new MapInfo(base);
        map->readMap(fileName);
        this->opened = true;
        this->initByMapInfo(map);

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
    }

    qDebug()<< "key_press" ;
}
//操作区-基本贴图点击
void MainWindow::map_base_on_mouse_press(qreal x,qreal y,Qt::MouseButtons btns)
{
    MapBase* base = (MapBase*)(sender());
    if(btns == Qt::LeftButton){

        if(this->curSprite)this->curSprite->show();
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
//退出
void MainWindow::on_exitAction_triggered()
{
    int yn;
    if(changed)
        yn = QMessageBox::question(this,tr("是否保存"),tr("修改是否保存"),QMessageBox::Yes|QMessageBox::No|QMessageBox::Cancel);
    else
        yn = QMessageBox::No;

    if(yn == QMessageBox::No){//不保存
        exit(0);
    }else if(yn == QMessageBox::Yes){ //保存
        on_saveAction_triggered();
        exit(0);
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
        this->curInfo->name = this->ui->lineEdit_name->text();
        this->curInfo->type = QVariant(this->ui->lineEdit_type->text()).toUInt();
        this->curInfo->writeMap(filename);
    }else{
        QMessageBox::information(this,tr("错误"),tr("需要打开一个文件"));
    }
}

//背景选择编辑
void MainWindow::on_lineEdit_bgcolor_textEdited(QString colorname)
{
    this->changed = true;
    this->ui->label_color->setStyleSheet(tr("QLabel{background:#%1}").arg(colorname));
    this->curInfo->background = QColor("#"+colorname);
    this->scene->setBackgroundBrush(this->curInfo->background);
}

//背景颜色选择
void MainWindow::on_pushButton_clicked()
{

    QColorDialog dialog(this);
    QColor color;
    if(this->curInfo){
        color = dialog.getColor(this->curInfo->background);
    }else{
        color = dialog.getColor(QColor("#"+this->ui->lineEdit_bgcolor->text()));
    }
    this->ui->lineEdit_bgcolor->setText(color.name().mid(1));
    this->ui->label_color->setStyleSheet(tr("QLabel{background:%1}").arg(color.name()));
    this->curInfo->background = color;
    this->scene->setBackgroundBrush(this->curInfo->background);
}

//被选闪耀
void MainWindow::time_out()
{

    if(this->curSprite){
        if(this->curSprite->isVisible())
            this->curSprite->hide();
        else
            this->curSprite->show();
    }
}

/*
 * 修改地图大小
 */
//调整地图宽度
void MainWindow::on_width_spinBox_valueChanged(int value)
{

    if(this->curInfo){
        if((unsigned int)value > this->curInfo->width ){
            unsigned int i;
            QList<MapBase*> list = this->curInfo->getMapBaseInfo();
            for(i= 0 ; i < (((unsigned int)value - this->curInfo->width) * this->curInfo->height) ;i++){
                MapBase* tmpbase = new MapBase(this->curInfo->base);
                list.insert( (i+1)*this->curInfo->width + i ,tmpbase);
                this->regHandleSignal(tmpbase);
            }
            this->curInfo->width = (unsigned int)value;

            this->curInfo->setMapBaseInfo(list); //只能设置 get出来的list

            this->manager->initMap(this->curInfo);

        }
    }
    qDebug() << "value is " <<  value;
}
//调整地图高度
void MainWindow::on_height_spinBox_valueChanged(int value)
{

    if(this->curInfo){
        if( (unsigned int)value > this->curInfo->height ){
            unsigned int i;
            QList<MapBase*> list = this->curInfo->getMapBaseInfo();
            for(i= 0 ; i <this->curInfo->width ;i++){
                MapBase* tmpbase = new MapBase(this->curInfo->base);
                list.append(tmpbase);
                this->regHandleSignal(tmpbase);
            }
            this->curInfo->height = (unsigned int)value;

            this->curInfo->setMapBaseInfo(list); //只能设置 get出来的list

            this->manager->initMap(this->curInfo);

        }
    }
    qDebug() << "value is " <<  value;
}

bool MainWindow::isChange(){
    return this->changed;
}

bool MainWindow::isOpen(){
    return this->opened;
}
