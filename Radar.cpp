#include "Radar.h"
#include <QPixmap>
#include <QVector>
#include <QPointF>
#include <QPolygonF>
#include "Bullet.h"
#include <QPointF>
#include <QLineF>
#include "Game.h"
#include <QTimer>
#include <QGraphicsRectItem>
#include <QDebug>
#include <qmath.h>

extern Game * game;

Radar::Radar(QGraphicsItem *parent):QObject(), QGraphicsPixmapItem(parent){
    // set the graphics
    setPixmap(QPixmap(":/assets/img/militar_radar_green.png"));
    setScale(0.6);

    // create points vector
    QVector<QPointF> points;
    points << QPoint(1,0) << QPoint(2,0) << QPoint(3,1) << QPoint(3,2) << QPoint(2,3)
               << QPoint(1,3) << QPoint(0,2) << QPoint(0,1);

    // scale points
    int SCALE_FACTOR = 250;
    for (int i = 0, n = points.size(); i < n; i++)
    {
        points[i] *= SCALE_FACTOR;
    }

    // create the QGraphicsPolygonItem
    attack_area = new QGraphicsPolygonItem(QPolygonF(points),this);

    // move the polygon
    QPointF poly_center(2.4,2.4);
    poly_center *= SCALE_FACTOR;
    poly_center = mapToScene(poly_center);;
    QPointF Radar_center(x()+27,y()+27);
    QLineF ln(poly_center,Radar_center);
    attack_area->setPos(x()+ln.dx(),y()+ln.dy());

    // connect a timer to attack_target
    QTimer * timer = new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(aquire_target()));
    timer->start(game->aquireTargetTime());
}

double Radar::distanceTo(QGraphicsItem *item)
{
    QLineF ln(pos(),item->pos());
    return ln.length();
}

void Radar::aquire_target()
{
    has_target = false;
    // get a list of all items colliding with attack_area
    QList<QGraphicsItem *> colliding_items = attack_area->collidingItems();

    if (colliding_items.size() == 1)
    {
        return;
    }

    EnemyInfo enemy_info;
    enemy_info.set_position(QPointF(0,0));


    double closest_dist = qSqrt(qPow(game->getWindowHeight(), 2)
                               +qPow(game->getWindowWidth(),2));


    QPointF closest_pt = QPointF(0,0);
    for (int i = 0, n = colliding_items.size(); i < n; i++)
    {
        Enemy * enemy = dynamic_cast<Enemy *>(colliding_items[i]);
        if (enemy)
        {
            double this_dist = distanceTo(enemy);
            enemy_info.set_step_speed(enemy->get_speed());
            enemy_info.set_unit_time(game->moveTime());
            enemy_info.set_detection_time(QDateTime::currentDateTime());
            if (this_dist < closest_dist)
            {
                closest_dist = this_dist;
                closest_pt = colliding_items[i]->pos();
                has_target = true;
            }
        }
    }
    enemy_info.set_position(closest_pt);
    if(has_target)
    {
        emit fire(enemy_info);
    }
}
