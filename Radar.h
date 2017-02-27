#ifndef RADAR_H
#define RADAR_H

#include <QGraphicsPixmapItem>
#include <QGraphicsPolygonItem>
#include <QGraphicsItem>
#include <QPointF>
#include <QObject>
#include "Enemy.h"
#include "EnemyInfo.h"

class Radar : public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
public:
    Radar(QGraphicsItem * parent=0);
    double distanceTo(QGraphicsItem * item);
signals:
    void fire(EnemyInfo enemy_info);
public slots:
    void aquire_target();
private:
    QGraphicsPolygonItem * attack_area;
    bool has_target;
};

#endif // RADAR_H
