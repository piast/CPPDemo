#include "Ticker.h"
#include <functional>
#include <algorithm>
#include <list>
#include <iostream>



void Ticker::timerEvent(QTimerEvent*)
{
    int deltaTime = m_timer.elapsed();
    m_timer.restart();

    for ( auto i = m_functions.cbegin(); i != m_functions.cend(); ++i )
    {
        (**i)(deltaTime);
    }
}


Ticker::Ticker(int nInterval): QObject()
{
    m_timer.start();
    startTimer(nInterval);
}

void Ticker::add(std::function<void (int)>* func)
{
    //qWarning()<<"add Ticker";
    auto it = m_functions.begin();
    while ( it != m_functions.end() )
        if (*it == func){
            return;
        }
        else {
            ++it;
        }

    m_functions.push_front(func);
}

void Ticker::remove(std::function<void (int)>* func)
{
    auto it = m_functions.begin();
    while ( it != m_functions.end() )
        if (*it == func){
            it = m_functions.erase(it);
            return;
        }
        else {
            ++it;
        }
}
