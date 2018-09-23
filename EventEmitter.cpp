//#include "EventEmitter.h"

////using T = std::function<void(int, int)>;
//template<class T>
//EventEmitter<T>::EventEmitter()
//{

//}
//template<class T>
//void EventEmitter<T>::addListener(std::string type, T* listener)
//{
//    m_events[type].push_front(listener);
//    //return *this;
//}

//template<class T>
//void EventEmitter<T>::removeListener(std::string type, T* listener)
//{
//    auto event_it = m_events.find(type);
//    if ( event_it == m_events.end() )
//    {
//        /*return *this;*/
//    }
//    else
//    {
//        auto& handlers = m_events[type];
//        auto it = handlers.begin();
//        while ( it != handlers.end() )
//            if (*it == listener){
//                it = handlers.erase(it);
//                if ( handlers.size() == 0 ) m_events.erase(event_it);
//                //return *this;
//            }
//            else {
//                ++it;
//            }
//            //qDebug()<< "111111";
//    }

//    //return *this;
//}
//template<class T>
//bool EventEmitter<T>::emitEvent(std::string type, int arg1, int arg2)
//{
//    if ( m_events.find(type) == m_events.end() ) return false;

//    auto& handlers = m_events[type];
//    for ( auto it = handlers.begin(); it != handlers.end(); ++it )
//    {
//        (**it)(arg1, arg2);
//    }
//}
