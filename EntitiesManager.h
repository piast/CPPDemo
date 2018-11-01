#ifndef ENTITIESMANAGER_H
#define ENTITIESMANAGER_H

#include "Player.h"
#include "Shark.h"
#include "GraphicsView.h"
#include "ScaleProcessor.h"
#include <QGraphicsScene>
#include <EventEmitter.h>


//#include <time.h>

class EntitiesManager
{
private:
    GraphicsView* m_view;
    QGraphicsScene* m_scene;
    Player* m_player;
    std::list<Shark*> m_sharks;
    QGraphicsTextItem * m_textGameOver;
    QGraphicsTextItem * m_textClickToContinue;
    EventEmitter< std::function<void(void)> > m_eventEmitter;

public:
    EntitiesManager();


    void init(GraphicsView*, QGraphicsScene*);
    void restart();
    EventEmitter< std::function<void (void)> >& eventEmitter();
    void update(int);
    void onMousePress(int, int);
    void showDeadProcess();
    void showTextGameOver();
    void hideTextGameOver();
    void showTextClickToContinue();
    void hideTextClickToContinue();

};

#endif // ENTITIESMANAGER_H
