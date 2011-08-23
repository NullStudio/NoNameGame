#ifndef STATEMANAGER_HPP
#define STATEMANAGER_HPP

#include <vector>

class Game;
class GameState;

class StateManager
{
    public:
        StateManager();
        virtual ~StateManager();

        void Register(Game* game);
        bool IsEmpty();

        void AddActiveState(GameState* state);
        void RemoveActiveState();
        GameState* GetActiveState();

        void ChangeState(GameState* state);
        void PushState(GameState* state);
        void PopState();

        /*
        void ChangeState(GameState* state);
        void PushState(GameState* state);
        void PopState();
        */

        void CleanUp();

    private:
        Game*                   mGame;
        std::vector<GameState*> mGameStates;
};

#endif // STATEMANAGER_HPP
