
#include "SCredits.hpp"
#include "SMenu.hpp"

SCredits::SCredits(Game* game) :
    GameState(game),
    mCreditsBG(NULL),
    mCredits1(NULL)
{
}

SCredits::~SCredits()
{

}

void SCredits::Init()
{
    std::cout << "-- SCredits::Init()" << std::endl;

    SetRunningState(true);

    mCreditsBG = new sf::Sprite;
    mCreditsBG->SetImage( mGame->mResourceManager.GetImage("creditsBG.png") );

    mCredits1 = new sf::Sprite;
    //mCredits1->SetImage( mGame->mResourceManager->GetImage("credits1.png") );
    mCredits1->SetImage( mGame->mResourceManager.GetImage("aliens.png") );
    mCredits1->SetPosition(250, 200);

    mCreditsMusic.OpenFromFile("music/creditsMusic.ogg");
    mCreditsMusic.Play();

    mAlpha = 0.0f;
}

void SCredits::End()
{
    mCreditsMusic.Stop();

    delete mCredits1;
    mCredits1 = NULL;

    delete mCreditsBG;
    mCreditsBG = NULL;

    std::cout << "-- SCredits::End()" << std::endl;
}


void SCredits::Pause()
{
    SetRunningState(false);
    mCreditsMusic.Pause();
}

void SCredits::Resume()
{
    SetRunningState(true);
    mCreditsMusic.Play();
}

void SCredits::HandleEvents(const sf::Event& theEvent)
{
    // Escape key pressed
    if ((theEvent.Type == sf::Event::KeyPressed) && (theEvent.Key.Code == sf::Key::Escape))
    {
      if(NULL != mGame)
      {
        SetRunningState(false);
        End();
        //mGame->End();
      }
    }

    if ((theEvent.Type == sf::Event::KeyPressed) && (theEvent.Key.Code == sf::Key::Space))
    {
        //std::cout << "SCredits::HandleEvents" << std::endl;
        //mCreditsBG->SetPosition( mCreditsBG->GetPosition().x + 10, mCreditsBG->GetPosition().y + 10);
    }

    if ((theEvent.Type == sf::Event::KeyPressed) && (theEvent.Key.Code == sf::Key::N))
    {
        std::cout << "SCredits - next SCENE!!" << std::endl;
        if ( timer.GetElapsedTime() > 0.05 )
        {
            //mGame->mStateManager.RemoveActiveState();
            mGame->mStateManager.PushState( new(std::nothrow) SMenu(mGame) );
        } timer.Reset();
        SetRunningState(false);
    }
}


void SCredits::Update()
{
    //std::cout << "SCredits::Update" << std::endl;
    if ( IsRunning() )
    {
        mAlpha += mGame->mApp.GetFrameTime();
        //std::cout << "Alpha = " << mAlpha << std::endl;
        float FadeDuration = 5.0f;
        float alpha = (255 * mAlpha / FadeDuration );
        if (alpha > 255) alpha = 255;
        //mCredits1->SetColor( sf::Color(255, 255, 255, (sf::Uint8) (255 * mAlpha / 5.0f )) );
        mCredits1->SetColor( sf::Color(255, 255, 255, (sf::Uint8) (alpha)) );
    }
}


void SCredits::Draw()
{
    mGame->mApp.Draw(*mCreditsBG);
    mGame->mApp.Draw(*mCredits1);
}


