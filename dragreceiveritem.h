#ifndef DRAGRECEIVERITEM_H
#define DRAGRECEIVERITEM_H

#include "sprite.h"

class QMimeData;
class DragReceiverItem : public Sprite
{
    Q_OBJECT
public:
    explicit DragReceiverItem(uint colv,uint rowv,qreal cellW,qreal cellH,Sprite *parent = 0);
    ~DragReceiverItem();
    uint col;
    uint row;
    qreal cellWidth;
    qreal cellHeight;

signals:
    void onDrop(QPointF scenePos,const QMimeData* data);

protected:
    void dragEnterEvent(QGraphicsSceneDragDropEvent *event);
    void dragLeaveEvent(QGraphicsSceneDragDropEvent *event);
    void dragMoveEvent(QGraphicsSceneDragDropEvent *event);
    void dropEvent(QGraphicsSceneDragDropEvent *event);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
private:
    QVector<QPoint> vector;

public slots:

};

#endif // DRAGRECEIVERITEM_H
