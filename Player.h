#ifndef PLAYER_H
#define PLAYER_H

#include <functional>

#include "Sprite.h"
#include "libs/tweeny/tweeny.h"


class Player : public Sprite
{
public:
    enum State {
        DEAD,
        SWIM
    };

    Player(QString animationName, Mode mode, void (*callback)());

    void move(int x, int y);

    tweeny::tween<float, float>& getTweener();

    void flipHorizontal();
    void setDirection(float,float,float,float);

    State state();
    void setState(State);

//    QPainterPath shape() const
//    {
//        QPainterPath path;
//        path.addEllipse(0, 0, 40, 40);
//        return path;
//    }

private:
    tweeny::tween<float, float> m_tweener;
    State m_state;

};


#endif // PLAYER_H
