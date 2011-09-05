#ifndef SINGAME_HPP
#define SINGAME_HPP

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

#include "EntityManager.hpp"  //It also includes "Entity.hpp" inside
#include "LevelManager.hpp"
#include "InputManager.hpp"

#include "GameState.hpp"

//definitions for physics world <-> window projection coordinate transformation
#define PIXELS_PER_METER	64.0f
#define METERS_PER_PIXEL	(1.0f/PIXELS_PER_METER)
//shorthand version
#define PPM PIXELS_PER_METER
#define MPP METERS_PER_PIXEL


class SInGame : public GameState
{
    public:
        SInGame(Game* game);
        virtual ~SInGame();

        void Init();
        void End();

        void HandleEvents(const sf::Event& theEvent);
        void Update();
        void Draw();

        void RenderAll();

    private:

        //Camera Manager
        EntityManager&  mEntityMgr;
        LevelManager&   mLevelMgr;
        InputManager&   mInputMgr;

        Entity*    mInGameBG;
        Entity*    mCharacter;

        //Animation* PlayerAnimation;
        Player*     mPlayer;
        b2World*    mWorld;

        sf::Clock   *timer;

        sf::Vector2f ConvertToScreen(const b2Vec2& physicsVector) const;
};

#endif
