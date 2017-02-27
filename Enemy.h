#ifndef ENEMY_H
#define ENEMY_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QGraphicsItem>

class Enemy: public QObject,public QGraphicsPixmapItem{
    Q_OBJECT
public:
    Enemy(QGraphicsItem * parent=0);
    double get_speed();
    virtual void init();
public slots:
    void move();
    virtual void shot_target();
protected:
    double speed;
};

#endif // ENEMY_H
