
#include "InputManager.hpp"

InputManager& InputManager::GetInstance()
{
    static InputManager self;
    return self;
}

InputManager::InputManager()
{

}


InputManager::~InputManager()
{

}


void InputManager::Init(sf::RenderWindow* window, Player* player)
{
    mWindow = window;
    mPlayer = player;
}

void InputManager::ProcessInput(float elapsedTime)
{
    const sf::Input& input = mWindow->GetInput();

    if (input.IsKeyDown(sf::Key::Up)) {
        std::cout << "Up!!" << std::endl;
	}

	if (input.IsKeyDown(sf::Key::Down)) {
		std::cout << "Down!!" << std::endl;
	}

	if (input.IsKeyDown(sf::Key::Right)) {
		std::cout << "Right!!" << std::endl;
	}

	if (input.IsKeyDown(sf::Key::Left)) {
		std::cout << "Left!!" << std::endl;
	}
}

