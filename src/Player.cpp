
#include "Player.hpp"

Player::Player(Animation* animation, b2Body* body) :
    mAnimation(animation), mBody(body)
{

}


Player::~Player()
{
    delete mAnimation;
}

b2Body* Player::GetBody()
{
    return mBody;
}

b2Vec2 Player::GetPosition()
{
    return mBody->GetPosition();
}

Animation* Player::GetAnimation()
{
    return mAnimation;
}


float Player::GetMaxWalkVelocity() const
{
    return  10.0f;
}

float Player::GetJumpVelocity() const
{
	return 2.0f;
}
