#include "EnemyInfo.h"

EnemyInfo::EnemyInfo()
{
}


QPointF EnemyInfo::get_position()
{
    return position;
}

double EnemyInfo::get_step_speed()
{
    return step_speed;
}

double EnemyInfo::get_unit_time()
{
    return unit_time;
}

QDateTime EnemyInfo::get_detection_time()
{
    return detection_time;
}

void EnemyInfo::set_position(QPointF position)
{
    this->position.setX(position.x());
    this->position.setY(position.y());
}

void EnemyInfo::set_step_speed(double step_speed)
{
    this->step_speed = step_speed;
}

void EnemyInfo::set_unit_time(double unit_time)
{
    this->unit_time = unit_time;
}

void EnemyInfo::set_detection_time(QDateTime detection_time)
{
    this->detection_time = detection_time;
}
