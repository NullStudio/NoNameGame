
#include "StateManager.hpp"
#include "Game.hpp"
#include "GameState.hpp"

StateManager& StateManager::GetInstance()
{
    static StateManager self;
    return self;
}

StateManager::StateManager()
{
    //ctor
    mGame = NULL;
}


StateManager::~StateManager()
{
    //dtor
    while ( !mGameStates.empty() )
    {
        GameState* anState = mGameStates.back();
        mGameStates.pop_back();
        anState->Pause();
        anState->End();
        delete anState;
        anState = NULL;
    }
    mGame = NULL;
}


void StateManager::Register(Game* game)
{
    mGame = game;
}


bool StateManager::IsEmpty()
{
    return mGameStates.empty();
}


void StateManager::AddActiveState(GameState* state)
{
    if ( !mGameStates.empty() )
    {
        mGameStates.back()->Pause();
    }
    mGameStates.push_back(state);
    mGameStates.back()->Init();
}

void StateManager::RemoveActiveState()
{
    std::cout << "StateManager::RemoveActiveState() - before" << std::endl;
    // Is there no currently active state to drop?
    if(!mGameStates.empty())
    {
      // Retrieve the currently active state
      GameState* anState = mGameStates.back();
      // Pause the currently active state
      anState->Pause();
      // Cleanup the currently active state before we pop it off the stack
      //anState->End();
      // Pop the currently active state off the stack
      mGameStates.pop_back();
      // Don't keep pointers around we don't need anymore
      anState = NULL;
      std::cout << "StateManager::RemoveActiveState() - after" << std::endl;
    }
    else
    {
      // Quit the application with an error status response
      if(NULL != mGame)
      {
        mGame->End();
      }
      return;
    }

    // Is there another state to activate? then call Resume to activate it
    if(!mGameStates.empty())
    {
      // Has this state ever been initialized?
//      if(mGameStates.back()->IsInitialized())
      if( mGameStates.back()->IsRunning() )
      {
        // Resume the new active state
        mGameStates.back()->Resume();
      }
      else
      {
        // Initialize the new active state
        mGameStates.back()->Init();
      }
    }
    /*
    else
    {
      // There are no mGameStates on the stack, exit the program
      if(NULL != mGame)
      {
        mGame->End();
      }
    }
    */
}


GameState* StateManager::GetActiveState()
{
    return mGameStates.back();
}

//NEW STATE CHANGE   ///////////////////////////////
void StateManager::ChangeState(GameState* state)
{
    std::cout << "### StateManager::ChangeState" << std::endl;
	// cleanup the current state
	if ( !mGameStates.empty() ) {
		mGameStates.back()->End();
		mGameStates.pop_back();
	}


	// store and init the new state
	mGameStates.push_back(state);
	mGameStates.back()->Init();

}

void StateManager::PushState(GameState* state)
{
    std::cout << "### StateManager::PushState" << std::endl;
	// pause current state
	if ( !mGameStates.empty() ) {
		mGameStates.back()->Pause();
	}

	// store and init the new state
	mGameStates.push_back(state);
	mGameStates.back()->Init();

}

void StateManager::PopState()
{
	// cleanup the current state
	if ( !mGameStates.empty() ) {
		//mGameStates.back()->End();
		mGameStates.pop_back();
	}

	// resume previous state
	if ( !mGameStates.empty() ) {
		mGameStates.back()->Resume();
	}
}

//////////////////////////////////////////////////

void StateManager::CleanUp()
{
    mGameStates.back()->End();
}
