#include "inmapitemdialog.h"
#include "ui_inmapitemdialog.h"
#include "mapinfo.h"
#include "mapmanager.h"
#include "mapitem.h"
#include "sprite.h"
#include <QPushButton>

InMapItemDialog::InMapItemDialog(MapInfo* mapinfo,MapManager* manager,QWidget *parent) :
    QDialog(parent),
    mapInfo(mapinfo),
    mapManager(manager),
    ui(new Ui::InMapItemDialog)
{
    ui->setupUi(this);
    ui->buttonBox->button(QDialogButtonBox::Ok)->setText(tr("确定"));
    ui->buttonBox->button(QDialogButtonBox::Cancel)->setText(tr("取消"));

}

InMapItemDialog::~InMapItemDialog()
{
    delete ui;
}

//实现插入MapItem
MapItem* InMapItemDialog::getMapItem(Sprite* base)
{
    MapItem* returnItem = 0;
    this->exec();
    return returnItem;
}
