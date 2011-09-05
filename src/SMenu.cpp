
#include "SMenu.hpp"
#include "SInGame.hpp"

SMenu::SMenu(Game* game) :
    GameState(game),
    mMenuBG(NULL),
    mRock(NULL)
{
}

SMenu::~SMenu()
{

}

void SMenu::Init()
{
    std::cout << "-- SMenu::Init()" << std::endl;
    mMenuBG = new sf::Sprite;
    mMenuBG->SetImage( mGame->mResourceManager.GetImage("back.png") );

    mRock = new sf::Sprite;
    mRock->SetImage( mGame->mResourceManager.GetImage("rock2.png") );
}

void SMenu::End()
{
    delete mMenuBG;
    delete mRock;
    mMenuBG = NULL;
    mRock = NULL;
    std::cout << "-- SMenu::End()" << std::endl;
}


void SMenu::HandleEvents(const sf::Event& theEvent)
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
        //std::cout << "SMenu::HandleEvents" << std::endl;
        mMenuBG->SetPosition(0, 0);
        mRock->SetPosition( mRock->GetPosition().x + 10, mRock->GetPosition().y + 10);
    }

    if ((theEvent.Type == sf::Event::KeyPressed) && (theEvent.Key.Code == sf::Key::N))
    {
        std::cout << "Menu - next SCENE!!" << std::endl;
        mGame->mStateManager.PushState( new(std::nothrow) SInGame(mGame) );
    }

    if ((theEvent.Type == sf::Event::KeyPressed) && (theEvent.Key.Code == sf::Key::P))
    {
        std::cout << "Menu - prev. SCENE!!" << std::endl;
        mGame->mStateManager.PopState();
    }

}


void SMenu::Update()
{
    //std::cout << "SMenu::Update" << std::endl;
}


void SMenu::Draw()
{
    mGame->mApp.Draw(*mMenuBG);
    mGame->mApp.Draw(*mRock);
}


