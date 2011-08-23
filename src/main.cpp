
#include "Game.hpp"

int main(int argc, char *argv[])
{
    /*
	Game* GameEngine = new Game();
    int exitCode = GameEngine->Run();
    delete GameEngine;
    GameEngine = NULL;

    return exitCode;
    */

    //OR

    Game& game = Game::GetInstance();
    game.Run();

    //OR
    //Game::GetInstance().Run();

    return EXIT_SUCCESS;
}
