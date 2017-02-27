#ifndef EXPLOSION_H
#define EXPLOSION_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QGraphicsItem>
#include <QPointF>

class Explosion: public QObject,public QGraphicsPixmapItem{
    Q_OBJECT
public:
    Explosion(QPointF point);
private slots:
    void remove_explosion();
};

#endif // EXPLOSION_H
