#include "Player.h"
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QDebug>
#include "Bullet.h"
#include <qmath.h>
#include "Game.h"
#include "Enemy.h"

extern Game * game;
const int STEP_SIZE = 15;


Player::Player(QGraphicsItem *parent): QGraphicsPixmapItem(parent){

    // set graphic
    setPixmap(QPixmap(":/assets/img/player.png"));
    setScale(0.05);
    setPos(x(),y()-300);
}

void Player::keyPressEvent(QKeyEvent *event){
    // move the player left
    if (event->key() == Qt::Key_Left){
        if (pos().x() > 0)
        {
            double theta = rotation();
            double dx = STEP_SIZE * qCos(theta);
            setPos(x()-dx,y());
        }
    }
    // move the player right
    else if (event->key() == Qt::Key_Right){
        if (pos().x() + 100 < game->getWindowWidth())
        {
            double theta = rotation();
            double dx = STEP_SIZE * qCos((theta*M_PI)/180);
            setPos(x()+dx,y());
        }
    }
    // move the player up
    else if (event->key() == Qt::Key_Up){
        if (pos().y() > 0)
        {
            double theta = rotation();
            double dy = STEP_SIZE * qCos((theta*M_PI)/180);
            setPos(x(),y()-dy);
        }
    }
    // move the player down
    else if (event->key() == Qt::Key_Down){
        if (pos().y() + 100 < game->getWindowHeight())
        {
            double theta = rotation();
            double dy = STEP_SIZE * qCos((theta*M_PI)/180);
            setPos(x(),y()+dy);
        }
    }
    // shoot with the spacebar
    else if (event->key() == Qt::Key_Space){
        // create a bullet
        Bullet * bullet = new Bullet();
        bullet->setRotation(-90);
        bullet->setPos(x()+45,y());
        scene()->addItem(bullet);

    }
}
