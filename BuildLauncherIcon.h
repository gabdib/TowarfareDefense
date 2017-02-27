#ifndef BUILDLAUNCHERICON_H
#define BUILDLAUNCHERICON_H

#include "BuildIcon.h"
#include "Launcher.h"

class BuildLauncherIcon : public BuildIcon
{
public:
    BuildLauncherIcon();
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void init();

};

#endif // BUILDLAUNCHERICON_H
