#ifndef MAPMANAGER_H
#define MAPMANAGER_H

#include <QObject>
#include <QGraphicsScene>
#include <QMap>
#include <QList>
const int DEF_SPRITE_LEVEL=1;
class Sprite;
class MapInfo;
class MapBase;
class MapManager : public QObject
{
    Q_OBJECT
public:
    MapManager(QGraphicsScene* scene,QObject *parent = 0);
    ~MapManager();
    bool initMap(MapInfo* mapinfo);
    Sprite* addSprite(Sprite* sprite,QString type,int level=DEF_SPRITE_LEVEL);
    Sprite* removeSprite(Sprite* sprite,QString type);
    bool isInitialized();
    QMap< QString , QList<Sprite*>* > spriteMap;
private:
    QGraphicsScene* drawScene;
    MapInfo* curMapInfo;
    bool initialized;
signals:

public slots:

};

#endif // MAPMANAGER_H
