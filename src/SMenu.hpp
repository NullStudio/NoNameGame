#ifndef SMENU_HPP
#define SMENU_HPP

#include <SFML/Graphics.hpp>

#include "GameState.hpp"

class SMenu : public GameState
{
    public:
        SMenu(Game* game);
        virtual ~SMenu();

        void Init();
        void End();

        void HandleEvents(const sf::Event& theEvent);
        void Update();
        void Draw();

    private:
        sf::Sprite*    mMenuBG;
        sf::Sprite*    mRock;
};

#endif
