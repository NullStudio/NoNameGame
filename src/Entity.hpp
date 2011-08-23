#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

class Entity : public sf::Sprite
{
    public:
        Entity(const sf::Image& image);
        ~Entity();
    private:
        int mLife;
};

#endif
