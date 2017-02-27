#include "SmartEnemy.h"
#include "Game.h"
#include <qmath.h>
#include <QTimer>

extern Game * game;

SmartEnemy::SmartEnemy() : Enemy()
{
}

void SmartEnemy::init()
{
    //set random speed
    speed = rand() % 3 + 8;

    health = 2;

    // drew the rect
    setPixmap(QPixmap(":/assets/img/player.png"));
    setTransformOriginPoint(50,50);
    setRotation(180);
    setScale(0.05);

    // create points vector
    QVector<QPointF> points;
    points << QPoint(0,0) << QPoint(1,-1) << QPoint(2,-2) << QPoint(3,-3) << QPoint(2,-3)
           << QPoint(1,-3) << QPoint(0,-3) << QPoint(-1,-3) << QPoint(-2,-3) << QPoint(-3,-3)
           << QPoint(-2,-2) << QPoint(-1,-1) << QPoint(0,0);

    // scale points
    int SCALE_FACTOR = 1000;
    for (int i = 0, n = points.size(); i < n; i++)
    {
        points[i] *= SCALE_FACTOR;
    }

    // create the QGraphicsPolygonItem
    attack_area = new QGraphicsPolygonItem(QPolygonF(points),this);

    // move the polygon
    QPointF poly_center(6.0,2.0);
    poly_center *= SCALE_FACTOR;
    poly_center = mapToScene(poly_center);;
    QPointF smartEnemy_center(x()+27,y()+27);
    QLineF ln(poly_center,smartEnemy_center);
    attack_area->setPos(x()+ln.dx(),y()+ln.dy());

    // connect a timer to shot_target
    QTimer * timer = new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(shot_target()));
    timer->start(game->aquireTargetTime());
}

double SmartEnemy::distanceTo(QGraphicsItem *item)
{
    QLineF ln(pos(),item->pos());
    return ln.length();
}

void SmartEnemy::decrease_health()
{

    if(health > 0)
    {
        health--;
        setOpacity(opacity()-0.3);
    }
}

int SmartEnemy::get_health()
{
    return health;
}

void SmartEnemy::shot_target()
{
    has_target = false;
    // get a list of all items colliding with attack_area
    QList<QGraphicsItem *> colliding_items = attack_area->collidingItems();

    if (colliding_items.size() == 1)
    {
        return;
    }

//    attack_dest = QPoint(0,0);


    double closest_dist = qSqrt(qPow(game->getWindowHeight(), 2)
                               +qPow(game->getWindowWidth(),2));


    QPointF closest_pt = QPointF(0,0);
    for (int i = 0, n = colliding_items.size(); i < n; i++)
    {
        Launcher * launcher = dynamic_cast<Launcher *>(colliding_items[i]);
        if (launcher)
        {
            double this_dist = distanceTo(launcher);
            if (this_dist < closest_dist)
            {
                closest_dist = this_dist;
                closest_pt = colliding_items[i]->pos();
                has_target = true;
            }
        }
    }

    attack_dest = closest_pt;
    if(has_target)
    {
        fire();
    }
}

void SmartEnemy::fire(){

    Bullet * bullet = new Bullet();

    bullet->setPos(x()+25,y()+25);

    QLineF ln(QPointF(x()+25,y()+25),attack_dest);

    double angle;

    if(pos().y()>attack_dest.y())
    {
        angle = - 1 * (ln.angle());
    }
    else
    {
        angle = 360 - (ln.angle());
    }

    bullet->setRotation(angle);
    game->scene->addItem(bullet);
}

