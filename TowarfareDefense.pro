#-------------------------------------------------
#
# Project created by QtCreator 2016-04-04T16:51:16
#
#-------------------------------------------------

QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TowarfareDefense
TEMPLATE = app


SOURCES += main.cpp \
    MyRect.cpp \
    Bullet.cpp \
    Enemy.cpp \
    Game.cpp \
    Score.cpp \
    Player.cpp \
    Health.cpp \
    Launcher.cpp \
    BuildIcon.cpp \
    Radar.cpp \
    BuildLauncherIcon.cpp \
    BuildRadarIcon.cpp \
    EnemySpawner.cpp \
    EnemyInfo.cpp \
    SmartEnemy.cpp \
    Explosion.cpp

HEADERS  += \
    MyRect.h \
    Bullet.h \
    Enemy.h \
    Game.h \
    Score.h \
    Player.h \
    Health.h \
    Launcher.h \
    BuildIcon.h \
    Radar.h \
    BuildLauncherIcon.h \
    BuildRadarIcon.h \
    EnemySpawner.h \
    EnemyInfo.h \
    SmartEnemy.h \
    Explosion.h

FORMS    +=

RESOURCES += \
    res.qrc
