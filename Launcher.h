#ifndef LAUNCHER_H
#define LAUNCHER_H

#include <QGraphicsPixmapItem>
#include <QGraphicsPolygonItem>
#include <QGraphicsItem>
#include <QPointF>
#include <QObject>
#include "Radar.h"
#include "Enemy.h"
#include "EnemyInfo.h"
#include "Bullet.h"

class Launcher: public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
public:
    Launcher(QGraphicsItem * parent=0);
    double distanceTo(QPointF target);
    void connectRadar(Radar* radar);
    double attack_angle(EnemyInfo enemy_info, Bullet *bullet);
public slots:
    void fire(EnemyInfo enemyInfo);
    void unlock();
private:
    bool has_target;
    bool locked;
};

#endif // LAUNCHER_H
