#include "Bullet.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QList>
#include <QDebug>
#include <QLabel>
#include <qmath.h>
#include <QMovie>
#include "Enemy.h"
#include "Explosion.h"
#include "Game.h"

extern Game * game;

const int STEP_SIZE = 25;

Bullet::Bullet(QGraphicsItem *parent): QObject(), QGraphicsPixmapItem(parent){
    // draw graphics
    setPixmap(QPixmap(":/assets/img/militar_bullet.png"));
    setScale(0.06);

    // make/connect a timer to move() the bullet every so often
    QTimer * timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(move()));

    // start the timer
    timer->start(game->moveTime());
}

void Bullet::move(){
    // get a list of all the items currently colliding with this bullet
    QList<QGraphicsItem *> colliding_items = collidingItems();

    // if one of the colliding items is an Enemy, destroy both the bullet and the enemy
    for (int i = 0, n = colliding_items.size(); i < n; ++i)
    {
        if (typeid(*(colliding_items[i])) == typeid(Enemy))
        {
            // increase the score
            game->score->increase();

            // remove them from the scene (still on the heap)
            scene()->removeItem(colliding_items[i]);
            scene()->removeItem(this);

            // delete them from the heap to save memory
            delete colliding_items[i];
            explode();
            delete this;
            return;
        }
        if (typeid(*(colliding_items[i])) == typeid(SmartEnemy))
        {
            SmartEnemy * smartEnemy = dynamic_cast<SmartEnemy*>(colliding_items[i]);

            //decrease enemy health
            smartEnemy->decrease_health();

            if(smartEnemy->get_health()<=0)
            {
                delete colliding_items[i];
                explode();
            }
            delete this;
            return;
        }
        if(typeid(*(colliding_items[i])) == typeid(Bullet))
        {
            delete colliding_items[i];
            explode();

            delete this;
            return;
        }
    }

    double theta = rotation()*M_PI/180;
    double dx = STEP_SIZE * qCos(theta);
    double dy = STEP_SIZE * qSin(theta);

    setPos(x()+dx, y()+dy);

    // if the bullet is off the screen, destroy it
    if ((pos().y() < 0)||(pos().x() < 0)){
        scene()->removeItem(this);
        delete this;
    }
}

int Bullet::get_step_size()
{
    return STEP_SIZE;
}

void Bullet::explode()
{
    Explosion *explosion = new Explosion(pos());
    game->scene->addItem(explosion);
    emit unlock_launcher();
}
