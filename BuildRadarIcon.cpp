#include "BuildRadarIcon.h"
#include "Game.h"

extern Game * game;

BuildRadarIcon::BuildRadarIcon() :
    BuildIcon()
{
    init();
}

void BuildRadarIcon::init()
{
    setPixmap(QPixmap(":/assets/img/militar_radar_green.png"));
    setPos(x(),y()+200);
}

void BuildRadarIcon::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (!game->build)
    {
        game->build = new Radar();
        game->setCursor(QString(":/assets/img/militar_radar_green.png"));
    }
}
