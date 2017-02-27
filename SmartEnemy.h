#ifndef SMARTENEMY_H
#define SMARTENEMY_H

#include "Enemy.h"
#include "Radar.h"

class SmartEnemy : public Enemy
{
public:
    SmartEnemy();
    virtual void init();
    void fire();
    void decrease_health();
    int get_health();
    double distanceTo(QGraphicsItem *item);
public slots:
    void shot_target();
private:
    int health;
    QPointF attack_dest;
    QGraphicsPolygonItem * attack_area;
    bool has_target;
};

#endif // SMARTENEMY_H
