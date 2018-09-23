#ifndef SHARK_H
#define SHARK_H

#include <functional>
#include <EventEmitter.h>
#include "Sprite.h"
#include "libs/tweeny/tweeny.h"


class Shark : public Sprite
{
private:
    tweeny::tween<float, float> m_tweener;

public:
    Shark(QString animationName, Mode mode, void (*callback)());
    void move(int x, int y);
    std::function<void(int, int)> m_p_move;
    tweeny::tween<float, float>& getTweener();

    void flipHorizontal();
    void setDirection(float x1, float y1, float x2, float y2);


};

#endif // SHARK_H
