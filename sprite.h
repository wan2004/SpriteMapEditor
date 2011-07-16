#ifndef SPRITE_H
#define SPRITE_H

#include <QGraphicsItem>
#include <QObject>
#include <QPixmap>
class Sprite : public  QObject,public QGraphicsItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)
public:
    Sprite(QGraphicsItem *parent = 0);
    ~Sprite();

    void setPixmap(QPixmap *pixmap);
    QPixmap* getPixmap(void);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;
    void setWidth(qreal width);
    void setHeight(qreal height);

    qreal getWidth();
    qreal getHeight();
    void resize(qreal width,qreal height);

public slots:

signals:
    void onKeyPress(int ascii);
    void onKeyRelease(int ascii);
    void onMousePress(qreal x,qreal y, Qt::MouseButtons buttons);
    void onMouseRelease(qreal x,qreal y, Qt::MouseButtons buttons);
    void onHover(QGraphicsSceneHoverEvent *event);
    void onFoucs(bool inOrOut);

protected:
    qreal width;
    qreal height;

    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
    void hoverMoveEvent(QGraphicsSceneHoverEvent *event);
    void foucsInEvent(QFocusEvent *event);
    void foucsOutEvent(QFocusEvent *event);

private:
    QPixmap* _pixmap;
};

#endif // SPRITE_H
