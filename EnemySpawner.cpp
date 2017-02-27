#include "EnemySpawner.h"
#include "Game.h"
#include <stdlib.h>
#include <QDebug>

extern Game * game;

EnemySpawner::EnemySpawner()
{
}

void EnemySpawner::spawn()
{

    double random = rand() % 10;

    if(random == 0)
    {
        //create a smart enemy
        SmartEnemy * smartEnemy = new SmartEnemy();
        smartEnemy->init();
        game->scene->addItem(smartEnemy);
    }
    else{
        //create an enemy
        Enemy * enemy = new Enemy();
        enemy->init();
        game->scene->addItem(enemy);
    }
}
