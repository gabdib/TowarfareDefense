#include "BuildLauncherIcon.h"
#include "Game.h"

extern Game * game;

BuildLauncherIcon::BuildLauncherIcon() :
    BuildIcon()
{
    init();
}

void BuildLauncherIcon::init()
{
    setPixmap(QPixmap(":/assets/img/big_militar_launcher_green.png"));
    setScale(0.6);
    setPos(x(),y()+100);
}

void BuildLauncherIcon::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (!game->build)
    {
        game->build = new Launcher();
        game->setCursor(QString(":/assets/img/big_militar_launcher_green.png"));
    }
}
