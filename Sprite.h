#ifndef SPRITE_H
#define SPRITE_H

#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <FramesDataPool.h>
#include <QTimer>
#include <QObject>

class Sprite : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:

    enum Mode { Once, Loop };
    Sprite(QString animationName, Mode mode, void (*callback)());
    virtual ~Sprite();

private:
    //QString m_animationName;
    QVector<QString> m_frameNames;
    int m_frameRate;

    FramesDataPool::AnimationData m_animationData;
    Mode m_mode;
    void (*m_onComplete)();
    int m_startFrameIndex;
    int m_lastFrameIndex;
    int m_currentFrameIndex;
    float_t m_elapsedFrame;
    bool m_isPlaying;

    QTimer m_timer;

protected:
    void play();
    void stop();

private slots:
    void update(/*float_t time = 16.6*/);






};

#endif // SPRITE_H
