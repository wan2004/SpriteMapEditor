#ifndef MAPITEM_H
#define MAPITEM_H
#include "mapbase.h"
#define DEF_TYPENAME "item"

class MapItem : public MapBase
{
public:
    MapItem(QPixmap* base,QString tName = QString(DEF_TYPENAME),unsigned int hindex = 0,unsigned int vindex = 0,
            unsigned int hnum = 1,unsigned int vnum = 1,QGraphicsItem* parent = 0);
    int crossType;
    int checkType;
    int breakType;
    int special;
    int mapX;
    int mapY;
    int mapZ;
    QString typeName;
};

#endif // MAPITEM_H
