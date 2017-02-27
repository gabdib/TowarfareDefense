#include "Game.h"
#include <QTimer>
#include <QDebug>
#include <QGraphicsTextItem>
#include <QFont>
#include <QBrush>
#include <QImage>

const int WINDOW_WIDTH = 1024;
const int WINDOW_HEIGHT = 1024;
const int AQUIRE_TARGET_TIME = 1500;
const int ENEMY_RESPAWN_TIME = 2000;
const int MOVE_TIME = 50;

Game::Game(){
    // create the scene
    scene = new QGraphicsScene();
    scene->setSceneRect(0,0,WINDOW_WIDTH,WINDOW_HEIGHT); // make the scene WINDOW_WIDTHxWINDOW_HEIGHT instead of infinity by infinity (default)
    setBackgroundBrush(QBrush(QImage(":/assets/img/militar_bg.png")));
    setAutoFillBackground(true);
    // make the newly created scene the scene to visualize (since Game is a QGraphicsView Widget,
    // it can be used to visualize scenes)
    setScene(scene);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(WINDOW_WIDTH, WINDOW_HEIGHT);

//    // create the player
//    player = new Player();
//    player->setPos(WINDOW_WIDTH/2,WINDOW_HEIGHT-100); // TODO generalize to always be in the middle bottom of screen
//    // make the player focusable and set it to be the current focus
//    player->setFlag(QGraphicsItem::ItemIsFocusable);
//    player->setFocus();
//    // add the player to the scene
//    scene->addItem(player);

    // create the score/health
    score = new Score();
    scene->addItem(score);
    health = new Health();
    health->setPos(health->x(),health->y()+25);
    scene->addItem(health);

    // set cursor
    cursor = nullptr;
    build = nullptr;
    setMouseTracking(true);

    // create the launcher icon
    BuildLauncherIcon * launcherIcon = new BuildLauncherIcon();
    scene->addItem(launcherIcon);

    // create the radar icon
    BuildRadarIcon * radarIcon = new BuildRadarIcon();
    scene->addItem(radarIcon);

    // spawn enemies
    QTimer * timer = new QTimer();
    enemySpawner = new EnemySpawner();
    QObject::connect(timer,SIGNAL(timeout()),enemySpawner,SLOT(spawn()));
    timer->start(ENEMY_RESPAWN_TIME);

    show();
}

int Game::getWindowWidth()
{
    return WINDOW_WIDTH;
}

int Game::getWindowHeight()
{
  return WINDOW_HEIGHT;
}

int Game::aquireTargetTime()
{
    return AQUIRE_TARGET_TIME;
}

int Game::moveTime()
{
    return MOVE_TIME;
}

void Game::setCursor(QString filename){
    if (cursor){
        scene->removeItem(cursor);
        delete cursor;
    }

    cursor = new QGraphicsPixmapItem();
    cursor->setPixmap(QPixmap(filename));
    cursor->setScale(0.5);
    cursor->setOpacity(0.7);
    scene->addItem(cursor);
}

void Game::mouseMoveEvent(QMouseEvent *event){
    if (cursor){
        cursor->setPos(event->pos());
    }
}

void Game::mousePressEvent(QMouseEvent *event){
    if (build)
    {
        // return if the cursor is colliding with a radar
        QList<QGraphicsItem *> items = cursor->collidingItems();
        for (int i = 0, n = items.size(); i < n; i++)
        {
            if (!dynamic_cast<Enemy*>(items[i]))
            {
                return;
            }
        }
        build->setScale(0.5);
        scene->addItem(build);
        build->setPos(event->pos());
        scene->removeItem(cursor);
        delete cursor;
        cursor = nullptr;

        if(typeid(*build)==typeid(Radar))
        {
            Radar* radar = dynamic_cast<Radar*>(build);
            radars.append(radar);
            for(int i = 0; i<launchers.size();i++)
            {
                launchers.at(i)->connectRadar(radar);
            }
        }
        else if(typeid(*build)==typeid(Launcher))
        {
            launchers.append(dynamic_cast<Launcher*>(build));
        }
        build = nullptr;
    }
    else
    {
        QGraphicsView::mousePressEvent(event);
    }
}
