#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include "Game.hpp"

class GameState
{
    public:
        virtual void Init() = 0;
        //virtual void Init() { mInitialized = true; }
        virtual void End() = 0;

        virtual void Pause()
        {
            mPaused = true;
        }

        virtual void Resume()
        {
            mPaused = false;
        }

        void SetRunningState(bool value) { mIsRunning = value; }
        bool IsRunning() { return mIsRunning; }
        bool IsPaused() { return mPaused; }

        virtual void HandleEvents(const sf::Event& theEvent) = 0;
        virtual void Update() = 0;
        virtual void Draw() = 0;

        virtual ~GameState()
        {
            mGame = NULL;
        }

        protected:
            Game*   mGame;

            GameState(Game* theGame) {
                mGame = theGame;
            };

        private:
            bool           mIsRunning;
            bool           mPaused;

            GameState(const GameState&);
            GameState& operator=(const GameState&);
};

#endif
