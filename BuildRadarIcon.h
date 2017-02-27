#ifndef BUILDRADARICON_H
#define BUILDRADARICON_H

#include "BuildIcon.h"
#include "Radar.h"

class BuildRadarIcon : public BuildIcon
{
public:
    BuildRadarIcon();
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void init();

};

#endif // BUILDLAUNCHERICON_H
