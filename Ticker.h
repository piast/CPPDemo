#ifndef TICKER_H
#define TICKER_H

#include <QObject>
#include <QElapsedTimer>
#include <list>
#include <QDebug>
#include <functional>
#include <algorithm>
#include <QTimerEvent>

class Ticker : public QObject
{
    //typedef std::function<void (void)> CallbackType;
private:
    std::list< std::function<void (int)>* > m_functions;
    QElapsedTimer m_timer;

protected:
    void timerEvent(QTimerEvent*)override;

public:
    Ticker(int nInterval = 1000/60);
    void add( std::function<void (int)>* );
    void remove( std::function<void (int)>* );


};

#endif // TICKER_H
