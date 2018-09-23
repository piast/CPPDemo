#include "GraphicsView.h"


GraphicsView::GraphicsView(QWidget *parent) : QGraphicsView(parent)
{
}

EventEmitter<std::function<void (int, int)>, int, int>& GraphicsView::eventEmitter()
{
    return m_eventEmitter;
}

void GraphicsView::mousePressEvent(QMouseEvent *event)
{

    m_eventEmitter.emitEvent( "mousePress", (int)(event->localPos().x()), (int)(event->localPos().y()) );
    //qDebug()<<"mousePressEvent "<< event->pos().x() << event->pos().x();
}
