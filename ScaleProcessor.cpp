#include "ScaleProcessor.h"

//ScaleProcessor::ScaleProcessor()
//{

//}

double ScaleProcessor::m_currentScaleRatio;


void ScaleProcessor::init()
{
    calculateScaleRatio();
}

double ScaleProcessor::calculateScaleRatio()
{
    if ( DEVICE_TYPE == DeviceType::Mobile ){

        QRect rect = QGuiApplication::primaryScreen()->geometry();
        double deviceViewportWidth = rect.width();
        double deviceViewportHeight = rect.height();

        //double deviceResolutionHeight = qMax(rect.width(), rect.height());
        //double deviceResolutionWidth = qMin(rect.width(), rect.height());
        //qDebug()<< "rect.width()" << rect.width()<< "rect.height()" << rect.height();
        //762×685

        double widthRatio = deviceViewportWidth / GAME_ORIGINAL_WIDTH;
        double heightRatio = deviceViewportHeight / GAME_ORIGINAL_HEIGHT;
        double scaleRatio = std::min(widthRatio, heightRatio);

        ScaleProcessor::m_currentScaleRatio = scaleRatio;
    }
    else if ( DEVICE_TYPE == DeviceType::Desktop ){

        ScaleProcessor::m_currentScaleRatio = 1;
    }

}

double ScaleProcessor::getScaleRatio()
{
    return ScaleProcessor::m_currentScaleRatio;
}
