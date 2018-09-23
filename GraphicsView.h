#ifndef GRAPHICSVIEW_H
#define GRAPHICSVIEW_H

#include <QGraphicsView>
#include <QMouseEvent>
#include "EventEmitter.h"


class GraphicsView : public QGraphicsView
{

public:
    GraphicsView(QWidget *parent = nullptr);

    EventEmitter<std::function<void (int, int)>, int, int>& eventEmitter();

protected:
    void mousePressEvent(QMouseEvent *event)override;
    EventEmitter< std::function<void(int, int)>, int, int > m_eventEmitter;

};

#endif // GRAPHICSVIEW_H
