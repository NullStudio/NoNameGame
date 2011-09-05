
#include "SMenuInGame.hpp"

SMenuInGame::SMenuInGame(Game* game) :
    GameState(game),
    mMenuInGameBG(NULL)
{
}

SMenuInGame::~SMenuInGame()
{

}

void SMenuInGame::Init()
{
    mMenuInGameBG = new sf::Sprite;
    mMenuInGameBG->SetImage( mGame->mResourceManager.GetImage("BGMenuInGame.png") );
}

void SMenuInGame::End()
{
    std::cout << "SMenuInGame::End()" << std::endl;
    delete mMenuInGameBG;
    mMenuInGameBG = NULL;
}


void SMenuInGame::HandleEvents(const sf::Event& theEvent)
{
    // Escape key pressed
    if ((theEvent.Type == sf::Event::KeyPressed) && (theEvent.Key.Code == sf::Key::Escape))
    {
      if(NULL != mGame)
      {
        End();
        //mGame->End();
      }
    }

    if ((theEvent.Type == sf::Event::KeyPressed) && (theEvent.Key.Code == sf::Key::Space))
    {
        //std::cout << "SMenuInGame::HandleEvents" << std::endl;
        mMenuInGameBG->SetPosition(0, 0);
    }

    if ((theEvent.Type == sf::Event::KeyPressed) && (theEvent.Key.Code == sf::Key::P))
    {
        std::cout << "MenuInGame - PopState() SCENE!!" << std::endl;
        mGame->mStateManager.PopState();
    }

}


void SMenuInGame::Update()
{
    //std::cout << "SMenuInGame::Update" << std::endl;
}


void SMenuInGame::Draw()
{
    mGame->mApp.Draw(*mMenuInGameBG);

}


