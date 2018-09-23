#include "Game.h"
#include <functional>
#include <EventEmitter.h>



Game::Game(QObject *parent): QObject(parent)
{

}

Game::~Game()
{

}

void Game::init()
{
    setState(Game::RUN);

    m_ticker = new Ticker(1000/60);

    m_view = new GraphicsView;
    m_view->show();
    //m_framesDataPool = new FramesDataPool;
    FramesDataPool::init();

    QPixmap& bgrPixmap = FramesDataPool::getFrame("background.png");
    m_background = new Background( bgrPixmap );
    //m_mainWindow->setGeometry(0,0,800,600);


    // create the scene
    m_scene = new QGraphicsScene();
    m_scene->setSceneRect(m_background->boundingRect());
    //m_scene->addRect(m_scene->sceneRect());

    //m_view = m_mainWindow->getGraphicsView();
    m_view->setFixedSize(bgrPixmap.size());
    //m_view->scale(1.4, 1.4);
    m_view->setScene(m_scene);
    m_scene->setItemIndexMethod(QGraphicsScene::NoIndex);

    m_view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_view->setTransformationAnchor(QGraphicsView::NoAnchor);
    m_view->setViewportUpdateMode(QGraphicsView::SmartViewportUpdate);
    m_view->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    m_view->setCacheMode(QGraphicsView::CacheBackground);

    m_scene->addItem(m_background);

    m_entitiesManager = new EntitiesManager;
    m_entitiesManager->init(m_view, m_scene);




    mp_gameUpdate = std::bind( &Game::update, this, std::placeholders::_1 );
    m_ticker->add( &mp_gameUpdate );

    mp_move = std::bind(&Game::onMousePress, this, std::placeholders::_1, std::placeholders::_2);
    m_view->eventEmitter().addListener( "mousePress", &mp_move );

    mp_gameOver = std::bind(&Game::gameOver, this);
    m_entitiesManager->eventEmitter().addListener( "gameOver", &mp_gameOver );


//    m_ticker->add( f );
//    m_ticker->add( std::bind([](){qDebug()<<"qwe2";}) );
//    m_ticker->add( [](){qDebug()<<"qwe2";} );
//    EventEmitter a;
//    a.addListener("qwe", std::bind([](){qDebug()<<"qwe2";}));
//    a.addListener("qwe", std::bind([](){qDebug()<<"qwe2";}));
//    std::function<void(void)> f = std::bind([](){qDebug()<<"qwe2";});
//    std::function<void(void)> f = std::bind(&Game::update, this);
//    std::function<void(void)>* ff = &f;
//    a.addListener( "qwe", ff );
//    a.emitEvent("qwe");
//    a.removeListener("qwe", ff);
//    a.emitEvent("qwe");


}

void Game::gameOver()
{
    setState(Game::OVER);


}

void Game::restart()
{
    setState(Game::RUN);
    m_entitiesManager->restart();
    qDebug()<< "restart";
}

void Game::update(int time)
{
     //qDebug()<< time;
    m_entitiesManager->update(time);
}

void Game::onMousePress(int x, int y)
{
    if(state() == Game::RUN){

        m_entitiesManager->onMousePress(x, y);
    }

    if(state() == Game::OVER){

        //m_entitiesManager->onMousePress(x, y);
        restart();
    }

}

Game::State Game::state()
{
    return m_state;
}

void Game::setState(State state)
{
    m_state = state;
}
