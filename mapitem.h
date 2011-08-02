#ifndef MAPITEM_H
#define MAPITEM_H
#include "mapbase.h"
#define DEF_TYPENAME "item"

class MapItem : public MapBase
{
public:
    MapItem(QPixmap* base,QString tName = QString(DEF_TYPENAME),unsigned int hindex = 0,unsigned int vindex = 0,
            unsigned int hnum = 1,unsigned int vnum = 1,QGraphicsItem* parent = 0);
    int crossType;//穿透
    int checkType;//调查
    int breakType;//可破坏
    int special;//特殊操作
    int mapX;//地图X坐标
    int mapY;//地图Y坐标
    int mapZ;//地图Z坐标
    QString typeName;//类别表示名称（manager里面的存储类别）
    void updateLocation();
};

#endif // MAPITEM_H
