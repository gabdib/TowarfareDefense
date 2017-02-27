#ifndef ENEMYINFO_H
#define ENEMYINFO_H

#include <QPointF>
#include <QDateTime>

class EnemyInfo
{
public:
    EnemyInfo();
    double get_step_speed();
    double get_unit_time();
    QPointF get_position();
    QDateTime get_detection_time();
    void set_step_speed(double step_speed);
    void set_unit_time(double unit_time);
    void set_position(QPointF position);
    void set_detection_time(QDateTime detection_time);
private:
    double step_speed;
    QDateTime detection_time;
    double unit_time;
    QPointF position;
};

#endif // ENEMYINFO_H
