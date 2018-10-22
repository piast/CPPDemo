#include "EntitiesManager.h"
#include <QGraphicsColorizeEffect>

#include <qguiapplication.h>
#include <qscreen.h>
#include <string>
#include <sstream>


EntitiesManager::EntitiesManager()
{

}

void EntitiesManager::init(GraphicsView *view, QGraphicsScene *scene){

    m_view = view;
    m_scene = scene;

    m_player = new Player("player", Sprite::Loop, nullptr);
    m_player->setState(Player::SWIM);
    m_player->setPos(300,300);
    m_scene->addItem(m_player);


    m_textGameOver = new QGraphicsTextItem;
    //m_textGameOver->setPlainText("Game Over");
    m_textGameOver->setHtml("<h1 style=\"font-size: 60px; font-family: sans-serif; color: #fff;\">GAME OVER</h1>");
    double width = m_textGameOver->boundingRect().width();//m_scene->width()
    m_textGameOver->setPos(m_scene->width()/2 - width/2,320);


    m_textClickToContinue = new QGraphicsTextItem;
    m_textClickToContinue->setHtml("<h1 style=\"font-size: 30px; font-family: sans-serif; color: #000;\">click to continue</h1>");
    width = m_textClickToContinue->boundingRect().width();
    m_textClickToContinue->setPos(m_scene->width()/2 - width/2,320);


//    QRect rect = QGuiApplication::primaryScreen()->geometry();
////    qreal height = qMax(rect.width(), rect.height());
////    qreal width = qMin(rect.width(), rect.height());
////    qDebug()<< "rect.width()" << rect.width();
////    qDebug()<< "rect.height()" << rect.height();
//    std::string text1("<h1 style=\"font-size: 30px; font-family: sans-serif; color: #000;\">");
//    std::string text2("</h1>");
//    std::stringstream text3;
//    text3 << rect.width();
//    std::string textResult = text1 + text3.str() + text2;
//    QGraphicsTextItem * text;
//    text->setHtml(textResult.data());
//    m_scene->addItem(text);


}

void EntitiesManager::restart()
{
    hideTextClickToContinue();


    auto it = m_sharks.begin();
    while ( it != m_sharks.end() ){

        m_scene->removeItem( (*it) );
        delete (*it);
        it = m_sharks.erase(it);
        //qDebug()<< "delete entitie" << m_sharks.size();
    }

    m_player->setState(Player::SWIM);
    m_player->resetTransform();
    m_player->setRotation(0);
    m_player->setPos(300,300);
    m_player->setGraphicsEffect(0);
}

EventEmitter< std::function<void(void)> >& EntitiesManager::eventEmitter()
{
    return m_eventEmitter;
}

void EntitiesManager::update(int deltaTime)
{

    //обновляем движение плеера
    m_player->getTweener().step(deltaTime);

    //обновляем движене всех акул
    //проверяем на столкновение каждой акулы с игроком
    //удаляем акул, которые вышли за границы сцены
    auto it = m_sharks.begin();
    while ( it != m_sharks.end() ){

        (*it)->getTweener().step(deltaTime);

        if( m_player->collidesWithItem( (*it), Qt::IntersectsItemShape ) ){

            //qDebug()<< " collidesWithItem ";
            if(m_player->state() == Player::SWIM){
                m_player->setState(Player::DEAD);
                showDeadProcess();
                //m_eventEmitter.emitEvent( "gameOver" );
            }

        }


        if ( (*it)->pos().x() > m_scene->width() + (*it)->boundingRect().width()/2 ){

            m_scene->removeItem( (*it) );
            delete (*it);
            it = m_sharks.erase(it);
            //qDebug()<< "delete entitie" << m_sharks.size();
        }
        else{

           ++it;
        }
    }

    //генерируем акул пока живой игрок
    if( m_player->state() == Player::SWIM ){

        int minValue = 0;
        int rangeValue = 100;
        int roulette = minValue + std::rand() % rangeValue;

        if(roulette < 4) {

            int minValueY = 150;
            int rangeValueY = m_scene->height() - minValueY - 40;
            int randomPosY = minValueY + std::rand() % rangeValueY;

            if(roulette < 2) {
                Shark* shark = new Shark("shark", Sprite::Loop, nullptr);
                m_sharks.push_front(shark);
                shark->setPos(-shark->boundingRect().width()/2, randomPosY);
                m_scene->addItem(shark);
                shark->move(1000, randomPosY);
                //qDebug()<<"shark generate with pos: " << randomPosY;

            }
            else {

    //            Shark* shark = new Player("shark", Sprite::Loop, nullptr);
    //            m_sharks.push_front(shark);
            }
        }
    }

}

void EntitiesManager::onMousePress(int x, int y)
{
    if(m_player->state() == Player::SWIM){

        auto playerWidth = m_player->boundingRect().width();
        auto playerHeight = m_player->boundingRect().height();

        //если игрок пересекает допустимые гранцы игровой зоны, то ограничиваем его координаты
        if( x <= playerWidth/2 ) x = playerWidth/2;
        if( x >= m_scene->width() - playerWidth/2 ) x = m_scene->width() - playerWidth/2 ;
        if( y <= playerHeight/2 + 120 ) y = playerHeight/2 + 120;
        if( y >= m_scene->height() - playerHeight/2 ) y = m_scene->height() - playerHeight/2;

        m_player->move(x, y);
    }
}

void EntitiesManager::showDeadProcess()
{

    QGraphicsColorizeEffect* colorEffect = new QGraphicsColorizeEffect;
    colorEffect->setColor(QColor(255, 0, 0));
    m_player->setGraphicsEffect(colorEffect);
    //m_player->setGraphicsEffect(0);
    //m_view->eventEmitter().removeListener( "mousePress", &(m_player->m_p_move) );


    m_player->move(m_player->pos().x(), m_scene->height() - 40);
    m_player->getTweener().onStep([&](tweeny::tween<float, float>& t) {

        if (t.progress() >= 1.0f) {
            //qDebug()<<"player pos" /*<< t.progress()*/ << t.peek()[0] << t.peek()[1];
            hideTextGameOver();
            showTextClickToContinue();
            eventEmitter().emitEvent("gameOver");
            return true; }
        return false;
    });

    showTextGameOver();
}

void EntitiesManager::showTextGameOver()
{

    m_scene->addItem(m_textGameOver);
}

void EntitiesManager::hideTextGameOver()
{

    m_scene->removeItem(m_textGameOver);
}

void EntitiesManager::showTextClickToContinue()
{
    m_scene->addItem(m_textClickToContinue);
}

void EntitiesManager::hideTextClickToContinue()
{
    m_scene->removeItem(m_textClickToContinue);
}




