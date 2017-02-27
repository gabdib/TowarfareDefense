#ifndef ENEMYSPAWNER_H
#define ENEMYSPAWNER_H

#include "Enemy.h"
#include "SmartEnemy.h"
#include <QObject>

class EnemySpawner: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

public:
    EnemySpawner();
public slots:
    void spawn();

};

#endif // ENEMYSPAWNER_H
