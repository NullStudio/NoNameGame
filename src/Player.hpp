#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>

#include "Animation.hpp"

class Player
{
  public:
    Player(Animation* animation, b2Body* body);
    ~Player();

    b2Body*     GetBody();
    b2Vec2      GetPosition();
    Animation*  GetAnimation();

    float       GetMaxWalkVelocity() const;
    float       GetJumpVelocity() const;

  private:
    Animation*  mAnimation;
    b2Body*     mBody;

};

#endif
