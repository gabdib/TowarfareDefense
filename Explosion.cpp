#include <QGraphicsScene>
#include <QTimer>
#include "Explosion.h"
#include "Game.h"

extern Game * game;

Explosion::Explosion(QPointF point): QObject(), QGraphicsPixmapItem()
{
    // drew the rect
    setPixmap(QPixmap(":/assets/img/explosion.png"));
    setScale(0.5);
    setPos(point.x(),point.y()-50);

    // make/connect a timer to move() the enemy every so often
    QTimer * timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(remove_explosion()));
    timer->start(300);
}

void Explosion::remove_explosion()
{
    delete this;
}
