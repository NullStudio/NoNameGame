#ifndef INPUTMANAGER_HPP
#define INPUTMANAGER_HPP

#include <iostream>

#include <SFML/Graphics.hpp>

#include "Player.hpp"

class InputManager
{
    public:
        static InputManager& GetInstance();

        void Init(sf::RenderWindow* window, Player* player);
        //void End();
        void ProcessInput(float elapsedTime);

    private:
        InputManager();
        InputManager(const InputManager&);
        ~InputManager();

        sf::RenderWindow*   mWindow;
        Player*             mPlayer;
        //CollisionManager* mCollisionMgr;

};

#endif
