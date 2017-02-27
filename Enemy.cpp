#include "Enemy.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QList>
#include <stdlib.h>
#include <qmath.h>
#include <QDebug>
#include "Game.h"

extern Game * game;

Enemy::Enemy(QGraphicsItem *parent): QObject(), QGraphicsPixmapItem(parent){
    //set random x position
    int random_x = rand() % game->getWindowWidth();
    setPos(random_x,0);

    // make/connect a timer to move() the enemy every so often
    QTimer * timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(move()));

    // start the timer
    timer->start(game->moveTime());
}

void Enemy::init()
{
    //set random speed
    speed = rand() % 7 + 1;

    // drew the rect
    setPixmap(QPixmap(":/assets/img/militar_enemy.png"));
    setTransformOriginPoint(50,50);
    setRotation(180);
    setScale(0.3);
}

void Enemy::move(){
    // move enemy down
    setPos(x(),y()+speed);

    // destroy enemy when it goes out of the screen
    if (pos().y() > game->getWindowHeight()){
        //decrease the health
        game->health->decrease();

        scene()->removeItem(this);
        delete this;
    }
}

double Enemy::get_speed()
{
    return speed;
}

void Enemy::shot_target()
{
    qDebug()<<"shot";
}
