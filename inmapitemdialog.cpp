#include "inmapitemdialog.h"
#include "ui_inmapitemdialog.h"
#include "mapinfo.h"
#include "mapmanager.h"
#include "mapitem.h"
#include "mapbase.h"
#include "sprite.h"
#include <QPushButton>
#include <QDebug>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QSlider>
InMapItemDialog::InMapItemDialog(MapInfo* mapinfo,MapManager* manager,QWidget *parent) :
    QDialog(parent),
    mapInfo(mapinfo),
    mapManager(manager),
    returnItem(0),
    selectScene(new QGraphicsScene(this)),
    selectRect(0),
    baseItems(new Sprite()),
    ui(new Ui::InMapItemDialog)
{
    ui->setupUi(this);
    ui->buttonBox->button(QDialogButtonBox::Ok)->setText(tr("确定"));
    ui->buttonBox->button(QDialogButtonBox::Cancel)->setText(tr("取消"));

    ui->tileHeight->setSingleStep(DEF_MAPBASE_HEIGHT);
    ui->tileHeight->setPageStep(DEF_MAPBASE_HEIGHT);
    ui->tileWidth->setSingleStep(DEF_MAPBASE_WIDTH);
    ui->tileWidth->setPageStep(DEF_MAPBASE_WIDTH);
    connect(ui->tileWidth,SIGNAL(sliderReleased()),this,SLOT(rule_slider()));
    connect(ui->tileHeight,SIGNAL(sliderReleased()),this,SLOT(rule_slider()));

    connect(ui->buttonBox,SIGNAL(accepted()),this,SLOT(ok_click()));
    connect(ui->buttonBox,SIGNAL(rejected()),this,SLOT(cancel_click()));
    connect(ui->tileWidth,SIGNAL(sliderMoved(int)),ui->tileWidthLabel,SLOT(setNum(int)));
    connect(ui->tileHeight,SIGNAL(sliderMoved(int)),ui->tileHeightLabel,SLOT(setNum(int)));
    connect(ui->tileWidth,SIGNAL(valueChanged(int)),ui->tileWidthLabel,SLOT(setNum(int)));
    connect(ui->tileHeight,SIGNAL(valueChanged(int)),ui->tileHeightLabel,SLOT(setNum(int)));

    ui->itemView->setScene(selectScene);
    baseItems->setPixmap(this->mapInfo->base);
    connect(baseItems,SIGNAL(onMouseRelease(qreal,qreal,Qt::MouseButtons)),this,SLOT(select_item_on_mouse_press(qreal,qreal,Qt::MouseButtons)));
    this->selectScene->addItem(baseItems);
}

InMapItemDialog::~InMapItemDialog()
{
    delete ui;
    delete baseItems;
    if(selectRect)delete selectRect;
    delete selectScene;
}

void InMapItemDialog::closeEvent(QCloseEvent *)
{
    this->cancel_click();
}

//实现插入MapItem 返回 0表示取消插入
MapItem* InMapItemDialog::createMapItem()
{

    returnItem = new MapItem(this->mapInfo->base);

    this->exec();

    return returnItem;
}

void InMapItemDialog::ok_click()
{

    returnItem->typeName = this->ui->itemNameEdit->text();
    returnItem->iColnum = this->ui->tileWidth->value();
    returnItem->iRownum = this->ui->tileHeight->value();

    qDebug() << "onOkClick";
}

void InMapItemDialog::cancel_click()
{
    qDebug() << "onCancelClick";
    delete this->returnItem;
    this->returnItem = 0;
}

//贴图区-物件单击
void InMapItemDialog::select_item_on_mouse_press(qreal x,qreal y,Qt::MouseButtons button)
{
    qDebug()<<" select_itme";
    int _hindex = int( x / DEF_MAPBASE_WIDTH);
    int _vindex = int( y / DEF_MAPBASE_HEIGHT);
    this->changeSelectBase(_hindex,_vindex);
    this->returnItem->hindex =_hindex;
    this->returnItem->vindex =_vindex;
}

//在选择区选择时加入的选区范围图示
void InMapItemDialog::changeSelectBase(int mhindex,int mvindex)
{
    if(this->selectRect)delete this->selectRect;
    this->selectRect = this->selectScene->addRect( mhindex *  DEF_MAPBASE_WIDTH,
                                          mvindex * DEF_MAPBASE_HEIGHT ,
                                          ui->tileWidth->value() ,
                                          ui->tileHeight->value() ,
                                          QPen(Qt::DashLine) ,
                                          QBrush(Qt::blue,Qt::Dense7Pattern)
                                          );
}
void InMapItemDialog::rule_slider()
{
    QSlider* sender = static_cast<QSlider* >(this->sender());
    sender->setValue(sender->value() - sender->value() % sender->singleStep());
}
