#ifndef SCREDITS_HPP
#define SCREDITS_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "GameState.hpp"

class SCredits : public GameState
{
    public:
        SCredits(Game* game);
        virtual ~SCredits();

        void Init();
        void End();

        void Pause();
        void Resume();

        void HandleEvents(const sf::Event& theEvent);
        void Update();
        void Draw();

    private:
        float          mAlpha;
        sf::Sprite*    mCreditsBG;
        sf::Sprite*    mCredits1;
        sf::Clock      timer;
        sf::Music      mCreditsMusic;
};

#endif
