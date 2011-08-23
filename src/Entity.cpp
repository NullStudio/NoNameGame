
#include "Entity.hpp"

Entity::Entity(const sf::Image& image) :
    Sprite(image)
{
    mLife = 100;
}

Entity::~Entity()
{

}
