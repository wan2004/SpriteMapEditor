#include "dragreceiveritem.h"
#include <QPainter>
#include <QDebug>
#include <QGraphicsSceneDragDropEvent>
#include <QMimeData>
DragReceiverItem::DragReceiverItem(uint colv,uint rowv,qreal cellW,qreal cellH,Sprite *parent) :
    Sprite(parent),
    col(colv),
    row(rowv),
    cellWidth(cellW),
    cellHeight(cellH)
{
    setAcceptDrops(true);
    this->setWidth(cellWidth * col);
    this->setHeight(cellHeight * row);

    for(uint i = 0; i <= col ; i++ ){
        //画线 对应 col 画 y 轴 直线
        vector.append(QPoint(i*cellWidth,0));
        vector.append(QPoint(i*cellWidth,row*cellHeight));
    }

    for(uint i = 0; i <= row ; i++ ){
        //画线 对应 row 画 x 轴 直线
        vector.append(QPoint(0,i*cellHeight));
        vector.append(QPoint(col*cellWidth,i*cellHeight));
    }

}

DragReceiverItem::~DragReceiverItem()
{

}
void DragReceiverItem::dragEnterEvent(QGraphicsSceneDragDropEvent *event)
{
    //qDebug() << "drag enter evnet";
}

void DragReceiverItem::dragLeaveEvent(QGraphicsSceneDragDropEvent *event)
{
    //qDebug() << "drag leave evnet";
}

void DragReceiverItem::dragMoveEvent(QGraphicsSceneDragDropEvent *event)
{

}

void DragReceiverItem::dropEvent(QGraphicsSceneDragDropEvent *event)
{
    /*
    qDebug() << "drop event " ;
    qDebug() << "pos =  " << event->pos();
    qDebug() << "scene pos = " << event->scenePos();
    qDebug() << "screen pos = " << event->screenPos();
    qDebug() << "mime data = " << event->mimeData();
    */
    emit onDrop(event->scenePos(),event->mimeData());
}

void DragReceiverItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(QPen(Qt::yellow));
    painter->drawLines(vector);
}
