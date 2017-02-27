#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QWidget>
#include <QGraphicsScene>
#include <QMouseEvent>
#include "Enemy.h"
#include "Bullet.h"
#include "Player.h"
#include "Score.h"
#include "Health.h"
#include "Launcher.h"
#include "Radar.h"
#include "BuildIcon.h"
#include "BuildLauncherIcon.h"
#include "BuildRadarIcon.h"
#include "EnemySpawner.h"

class Game: public QGraphicsView{
public:
    Game();

    EnemySpawner * enemySpawner;
    Player * player;
    Score * score;
    Health * health;
    QGraphicsItem * build;
    QList<Launcher*> launchers;
    QList<Radar*> radars;
    QGraphicsScene * scene;
    QGraphicsPixmapItem * cursor;


    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void setCursor(QString filename);

    int getWindowWidth();
    int getWindowHeight();
    int aquireTargetTime();
    int moveTime();
};

#endif // GAME_H
