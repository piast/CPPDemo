#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <QGraphicsPixmapItem>


class Background : public QGraphicsPixmapItem
{
public:
    explicit Background(const QPixmap &pixmap, QGraphicsItem *parent = 0);
};

#endif // BACKGROUND_H
