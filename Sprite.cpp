#include "Sprite.h"
#include <QDebug>

Sprite::Sprite(QString animationName, Mode mode, void (*callback)()): QGraphicsPixmapItem()
{
    m_frameNames = FramesDataPool::getAnimationData(animationName).frameNames;
    m_frameRate = FramesDataPool::getAnimationData(animationName).frameRate;
    m_mode = mode;
    m_onComplete = callback;
    m_startFrameIndex = 0;
    m_currentFrameIndex = m_startFrameIndex;
    m_lastFrameIndex = m_frameNames.size()-1;
    m_isPlaying = false;

    setPixmap(FramesDataPool::getFrame(m_frameNames[m_currentFrameIndex]));

    connect(&m_timer, SIGNAL(timeout()), this, SLOT(update(/*float_t*/)));
    m_timer.setInterval(1000/m_frameRate);
    //m_timer.start();
    play();

}

Sprite::~Sprite()
{

}

void Sprite::play()
{
    if(m_isPlaying == true){
        return;
    }

    m_isPlaying = true;
    m_timer.start();
}

void Sprite::stop()
{
    if(!m_isPlaying){
        return;
    }

    m_isPlaying = false;
    m_timer.stop();
}


void Sprite::update(/*float_t time*/)
{

    //16.6ms
//    float_t dt = time / 1000.0;// delta time sec
//    m_elapsedFrame += dt * m_frameRate;
//    m_currentFrameIndex = m_startFrameIndex + floor(m_elapsedFrame);

    ++m_currentFrameIndex;
    if (m_currentFrameIndex <= m_lastFrameIndex){

        setPixmap(FramesDataPool::getFrame(m_frameNames[m_currentFrameIndex]));
        //qWarning()<<m_currentFrameIndex<< " " << m_frameNames[m_currentFrameIndex] <<" " << m_frameNames.size();
    }
    else {
        if (m_mode == Loop) {

            m_currentFrameIndex	%= m_frameNames.size();
            setPixmap(FramesDataPool::getFrame(m_frameNames[m_currentFrameIndex]));
            //qWarning()<<m_currentFrameIndex<< " " << m_frameNames[m_currentFrameIndex] <<" " << m_frameNames.size();
        }
        else {

            //this.gotoAndStop(m_lastFrameIndex);
            if (m_onComplete != nullptr){
                m_onComplete();
                return;
            }
        }

    }


}


