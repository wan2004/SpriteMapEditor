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
class QGraphicsItem;
class QGraphicsScene;
class InMapItemDialog : public QDialog
{
    Q_OBJECT

public:
    InMapItemDialog(MapInfo* mapinfo,MapManager* manager,MapItem* mapitem = 0,QWidget *parent = 0);
    ~InMapItemDialog();
    MapItem* createMapItem();
    bool isChange();
protected:
    void closeEvent(QCloseEvent *);
private:
    MapInfo* mapInfo;
    MapManager* mapManager;
    MapItem* returnItem;
    QGraphicsScene* selectScene;
    QGraphicsItem* selectRect;
    Sprite* baseItems;
    Ui::InMapItemDialog *ui;
    bool change;
    void changeSelectBase(int mhindex,int mvindex);
private slots:
    void ok_click();
    void cancel_click();
    void rule_slider();
    void select_item_on_mouse_press(qreal x,qreal y,Qt::MouseButtons button);
};

#endif // INMAPITEMDIALOG_H
