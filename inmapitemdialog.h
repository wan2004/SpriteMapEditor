#ifndef INMAPITEMDIALOG_H
#define INMAPITEMDIALOG_H

#include <QDialog>

namespace Ui {
    class InMapItemDialog;
}
class MapInfo;
class MapManager;
class MapItem;
class Sprite;
class InMapItemDialog : public QDialog
{
    Q_OBJECT

public:
    InMapItemDialog(MapInfo* mapinfo,MapManager* manager,QWidget *parent = 0);
    ~InMapItemDialog();
    MapItem* getMapItem(Sprite* base);
private:
    MapInfo* mapInfo;
    MapManager* mapManager;
    Ui::InMapItemDialog *ui;
};

#endif // INMAPITEMDIALOG_H
