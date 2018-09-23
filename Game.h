#ifndef GAME_H
#define GAME_H

#include <QDebug>
#include <QWidget>
#include <QGraphicsScene>
#include <functional>
#include "Ticker.h"
#include "FramesDataPool.h"
#include "GraphicsView.h"
#include "Background.h"
#include "EntitiesManager.h"


class Game : public QObject
{
Q_OBJECT
private:
    enum State {
        RUN,
        OVER
    };
    State m_state;
    GraphicsView* m_view;
    QGraphicsScene* m_scene;
    FramesDataPool* m_framesDataPool;
    QGraphicsItem* m_background;
    EntitiesManager* m_entitiesManager;
    Ticker* m_ticker;
    std::function<void(int)> mp_gameUpdate;
    std::function<void(int, int)> mp_move;
    std::function<void(void)> mp_gameOver;


public:
    Game(QObject *parent = nullptr);
    virtual ~Game();
    void init();
    void gameOver();
    void restart();
    State state();
    void setState(State);

//protected:
    //virtual void mousePressEvent(QMouseEvent *event);
    //virtual void QGraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent* event);

public slots:
    void update(int);
    void onMousePress(int, int);

};

#endif // GAME_H
