#ifndef SMENUINGAME_HPP
#define SMENUINGAME_HPP

#include <SFML/Graphics.hpp>

#include "GameState.hpp"

class SMenuInGame : public GameState
{
    public:
        SMenuInGame(Game* game);
        virtual ~SMenuInGame();

        void Init();
        void End();

        void HandleEvents(const sf::Event& theEvent);
        void Update();
        void Draw();

    private:
        sf::Sprite*    mMenuInGameBG;
};

#endif
