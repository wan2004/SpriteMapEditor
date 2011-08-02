#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include "sprite.h"
#include "mapinfo.h"
#include "mapitem.h"
#include "mapmanager.h"
namespace Ui {
    class MainWindow;
}


class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    bool isOpen();
    bool isChange();
protected:
    void closeEvent( QCloseEvent * event );
private:
    Ui::MainWindow *ui;
    QGraphicsScene* itemSelectScene; //选择背景图片
    QGraphicsScene* scene;// 主要地图显示
    Sprite* baseItems; //贴图元件
    QGraphicsItem* select;
    MapManager* manager;
    MapInfo* curMapInfo;
    MapInfo* bakMapInfo;
    MapBase* curSprite;
    QTimer* timer;
    void regHandleSignal(Sprite* sprite);
    void changeSelectBase(int mhindex,int mvindex);
    void initByMapInfo(MapInfo* map);
    bool opened;
    bool changed;
private slots:
    void on_height_spinBox_valueChanged(int );
    void on_width_spinBox_valueChanged(int );
    void on_pushButton_clicked();
    void on_lineEdit_bgcolor_textEdited(QString );
    void on_saveAction_triggered();
    void on_exitAction_triggered();
    void on_openAction_triggered();
    void on_newAction_triggered();
    void map_base_on_press(int);
    void map_base_on_mouse_press(qreal,qreal,Qt::MouseButtons);
    void base_items_on_mouse_press(qreal,qreal,Qt::MouseButtons);
    void time_out();
    void on_mapitemAction_triggered(bool checked);
    void on_mapbaseAction_triggered(bool checked);
    void on_lineEdit_type_textChanged(const QString& type);
    void on_lineEdit_name_textChanged(const QString& name);
    void on_mapbaseViewAction_triggered(bool checked);
    void on_mapitemViewAction_triggered(bool checked);
    void on_insertMapItemAction_triggered();
};

#endif // MAINWINDOW_H
