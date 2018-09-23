#ifndef EVENTEMITTER_H
#define EVENTEMITTER_H

#include <list>
#include <map>
#include <string>
#include <functional>
//#include <algorithm>
#include <QDebug>

template <typename T, typename ...Arg>
class EventEmitter
{
    //using T = std::function<void(int, int)>;
public:
    EventEmitter()
    {
    }

private:
    std::map< std::string, std::list<T*> > m_events;

public:
    void addListener(std::string type, T* listener )
    {
        m_events[type].push_front(listener);
        //return *this;
    }

    void removeListener( std::string type, T* listener )
    {
        auto event_it = m_events.find(type);
        if ( event_it == m_events.end() )
        {
            /*return *this;*/
        }
        else
        {
            auto& handlers = m_events[type];
            auto it = handlers.begin();
            while ( it != handlers.end() )
                if (*it == listener){
                    it = handlers.erase(it);
                    if ( handlers.size() == 0 ) m_events.erase(event_it);
                    //return *this;
                }
                else {
                    ++it;
                }
                //qDebug()<< "111111";
        }

        //return *this;
    }
    bool emitEvent( std::string type, Arg ...args)
    {
        if ( m_events.find(type) == m_events.end() ) return false;

        auto& handlers = m_events[type];
        for ( auto it = handlers.begin(); it != handlers.end(); ++it )
        {
            (**it)(args...);
        }
        return true;
    }
};

#endif // EVENTEMITTER_H
