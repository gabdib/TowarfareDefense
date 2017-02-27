#ifndef BUILDICON_H
#define BUILDICON_H

#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>

class BuildIcon: public QGraphicsPixmapItem{
public:
    BuildIcon();
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) = 0;
    virtual void init() = 0;
};

#endif // BUILDICON_H
