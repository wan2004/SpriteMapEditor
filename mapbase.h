#ifndef MAPBASE_H
#define MAPBASE_H
#include <QGraphicsItem>
#include "sprite.h"

#define DEF_MAPBASE_WIDTH 32
#define DEF_MAPBASE_HEIGHT 32

class QPixmap;
class MapBase : public Sprite
{
public:
    MapBase(QPixmap* base,unsigned int hindex = 0,unsigned int vindex = 0,
            unsigned int hnum = 1,unsigned int vnum = 1,QGraphicsItem* parent = 0);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    qreal sizeV;
    qreal sizeH;
    unsigned int depth;
    unsigned int iColnum;
    unsigned int iRownum;
    unsigned int hindex;
    unsigned int vindex;
    void setIColnum(uint col);
    void setIRownum(uint row);
};

#endif // MAPBASE_H
