#ifndef BULLET_H
#define BULLET_H

#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QObject>

class Bullet: public QObject,public QGraphicsPixmapItem {
    Q_OBJECT
public:
    Bullet(QGraphicsItem * parent=0);
    int get_step_size();
    void explode();
public slots:
    void move();
signals:
    void unlock_launcher();
};

#endif // BULLET_H
