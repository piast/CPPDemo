#ifndef SCALEPROCESSOR_H
#define SCALEPROCESSOR_H

#include "globalconst.h"
#include <qguiapplication.h>
#include <qscreen.h>
#include <QDebug>


class ScaleProcessor
{
private:
    static double m_currentScaleRatio;

public:
    //ScaleProcessor();
    static void init();
    static double calculateScaleRatio();
    static double getScaleRatio();




};

#endif // SCALEPROCESSOR_H
