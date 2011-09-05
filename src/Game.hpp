#ifndef GAME_HPP
#define GAME_HPP

#include <iostream>
#include <string>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "StateManager.hpp"
#include "ResourceManager.hpp"

class Game
{
    public:

        static Game& GetInstance();

        //Variables
        sf::RenderWindow    mApp;
        const sf::Input&    mInput;

        //Managers HERE
        StateManager&       mStateManager;
        ResourceManager&    mResourceManager;

        sf::RenderWindow& GetApp();

        void Init(std::string title);
        void End();

        int Run();
        void Loop();

        void SetView(const sf::View& view);
        bool IsRunning(void) const;

    private:
        //Singleton
        Game();  //Ctor is private
        virtual ~Game(); //Dtor is private too
        //Dont allow copies
        Game(const Game&);
        Game& operator=(const Game&);

        std::string         mTitle;
        bool                mIsRunning;
};

#endif

