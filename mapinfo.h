#ifndef MAPINFO_H
#define MAPINFO_H

#include <QObject>
#include <QList>
#include "mapbase.h"
#include "mapitem.h"
class QPixmap;
class Sprite;
class MapInfo : public QObject
{
    Q_OBJECT
public:
    MapInfo(QString &basefile,QObject *parent = 0);
    ~MapInfo();
    QString name;
    unsigned int width;
    unsigned int height;
    QColor background;
    unsigned int type;
    QPixmap* base;
    QList<MapBase*> getMapBaseInfo();// 获得 地图上每个背景块
    QList<MapItem*> getMapItemInfo();// 获得 地图上每个背景块，
    void setMapBaseInfo(QList<MapBase*> list);
    bool setMapBase(unsigned int row,unsigned int col,MapBase* base); //设置指定点的Base
    bool readMap(QString &path); //读取地图文件
    bool writeMap(QString &path);
private:
    QList<MapBase*> _data;
    QList<MapItem*> _item;
    void analysisString(const QByteArray);
    void analysisHandleLine(const QByteArray);

};

#endif // MAPINFO_H
