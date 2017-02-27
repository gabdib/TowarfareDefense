#include "Launcher.h"
#include <QPixmap>
#include <QVector>
#include <QPointF>
#include <QPolygonF>
#include "Bullet.h"
#include <QPointF>
#include <qmath.h>
#include <QLineF>
#include "Game.h"
#include <QTimer>
#include <QGraphicsRectItem>
#include <QDebug>


extern Game * game;

Launcher::Launcher(QGraphicsItem *parent):QObject(), QGraphicsPixmapItem(parent)
{
    // set the graphics
    setPixmap(QPixmap(":/assets/img/big_militar_launcher_green.png"));
    setScale(0.4);

    for(int i=0; i < game->radars.size();i++)
    {
        connect(game->radars.at(i),SIGNAL(fire(EnemyInfo)),this,SLOT(fire(EnemyInfo)));
    }

    locked = false;

}

void Launcher::fire(EnemyInfo enemy_info){

    locked = true;

    Bullet * bullet = new Bullet();

    connect(bullet, SIGNAL(unlock_launcher()), this, SLOT(unlock()));

    bullet->setPos(x()+25,y()+25);

    QLineF distance_ln(pos(), enemy_info.get_position());


    double dy = distance_ln.length() * (enemy_info.get_step_speed() / bullet->get_step_size());

    QPointF attack_dest;
    attack_dest.setY(enemy_info.get_position().y()+dy);
    attack_dest.setX(enemy_info.get_position().x());

    QLineF ln(QPointF(x()+25,y()+25),attack_dest);

    double angle;

    if(pos().y()>enemy_info.get_position().y())
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

void Launcher::connectRadar(Radar* radar)
{
    connect(radar,SIGNAL(fire(EnemyInfo)),this,SLOT(fire(EnemyInfo)));
}

void Launcher::unlock()
{
    locked = false;
}

double Launcher::attack_angle(EnemyInfo enemy_info, Bullet * bullet)
{
    double xm = (double)enemy_info.get_position().x() + 25;
    double ym = (double) enemy_info.get_position().y() + 25;

    double xl = (double) this->pos().x();
    double yl = (double) this->pos().y();

    double xa = (double)this->pos().x();
    double ya = (double)this->pos().y();

    double vm = ((double) bullet->get_step_size())/((double)game->moveTime());
    double va = ((double)enemy_info.get_step_speed())/((double)game->moveTime());


    double yla = yl-ya;

    double vam = va/vm;

    double xal = xa-xl;

    double alfa = qAtan(yla/vm * vm/xal)/M_PI*180;


    qDebug()<<"xm = " + QString::number(this->pos().x())+ "\nya = " + QString::number((double)enemy_info.get_position().y()) + "\nvm = " + QString::number(vm) + "\nva = " + QString::number(va);
    qDebug()<<"alfa = " + QString::number(alfa);

    return alfa;
}
