#include "Player.h"


Player::Player(QString animationName, Mode mode, void (*callback)()):
    Sprite(animationName, mode, callback)
{
    m_tweener = tweeny::from<float, float>(.0f, .0f).to(.0f, .0f).during(0);

    double width = boundingRect().width();
    double height = boundingRect().height();
    setOffset(-width/2, -height/2);
}

tweeny::tween<float, float>& Player::getTweener()
{
    return m_tweener;
}

void Player::move(int x, int y)
{
    float x1 = (float)(pos().x());
    float y1 = (float)(pos().y());
    float x2 = (float)x;
    float y2 = (float)y;
    if(x1 == x2 && y1 == y2) return;

    float speed = 0.2;
    float during = static_cast<float>(sqrt(pow(x2-x1, 2) + pow(y2-y1, 2)) / speed);


    setDirection(x1, y1, x2, y2);

    m_tweener = tweeny::from<float, float>(x1, y1).to(x2, y2).during(during).via(tweeny::easing::linear);
    m_tweener.onStep([&](tweeny::tween<float, float>& t, float x, float y) {
        //qDebug()<<"qweUpdate1"<< x << y << t.progress() << t.peek()[0] << t.peek()[1];
        this->setPos(x, y);
        if (t.progress() >= 1.0f) { return true; }
        return false;
    });
}


void Player::flipHorizontal()
{
    // Get the current transform
    QTransform transform(this->transform());

    qreal m11 = transform.m11();    // Horizontal scaling
    qreal m12 = transform.m12();    // Vertical shearing
    qreal m13 = transform.m13();    // Horizontal Projection
    qreal m21 = transform.m21();    // Horizontal shearing
    qreal m22 = transform.m22();    // vertical scaling
    qreal m23 = transform.m23();    // Vertical Projection
    qreal m31 = transform.m31();    // Horizontal Position (DX)
    qreal m32 = transform.m32();    // Vertical Position (DY)
    qreal m33 = transform.m33();    // Addtional Projection Factor


//    qreal scale = m11;

    // Horizontal flip
    m11 = -m11;

    // Re-position back to origin
//    if(m31 > 0)
//        m31 = 0;
//    else
//        m31 = (boundingRect().width() * scale);

    // Write back to the matrix
    transform.setMatrix(m11, m12, m13, m21, m22, m23, m31, m32, m33);

    // Set the items transformation
    setTransform(transform);
}

void Player::setDirection(float x1, float y1, float x2, float y2)
{
    resetTransform();
    setRotation(0);

    if(x2 > x1) flipHorizontal();
    if(y2 > y1 && ((y2-y1)/std::abs(x2-x1)) > 1 ) setRotation(-90);
}

Player::State Player::state()
{
    return m_state;
}

void Player::setState(State state)
{
    m_state = state;
}



