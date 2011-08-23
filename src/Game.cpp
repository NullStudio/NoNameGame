
#include "Game.hpp"

#include "SCredits.hpp"
#include "SMenu.hpp"

Game& Game::GetInstance()
{
   static Game self;
   return self;
}

Game::Game() :
    mInput( mApp.GetInput() ),
    mStateManager(),
    mIsRunning(false)
{

}

Game::~Game()
{
    mIsRunning = false;
}


sf::RenderWindow& Game::GetApp()
{
    return mApp;
}

void Game::Init(std::string theTitle)
{
    std::cout << "Game::Init" << std::endl;

    mIsRunning = true;

    std::cout << "mApp.Create" << std::endl;
	mApp.Create(sf::VideoMode(1024, 768, 32), theTitle);
    //mApp.Create(sf::VideoMode(1024, 768, 32), theTitle, sf::Style::Fullscreen);
	//mApp.Create(sf::VideoMode(1024, 768, 32), "OLAF Game Test", sf::Style::Fullscreen);
    std::cout << "mApp.Create post" << std::endl;

    //mApp.ShowMouseCursor(true);
    mApp.EnableKeyRepeat(true);
    mApp.UseVerticalSync(true);
    mApp.SetFramerateLimit(60);

    //ResourceManager INIT
    mResourceManager = new ResourceManager;
    mResourceManager->AddResourceDir("images/");

    //StateManager INIT
    mStateManager.Register(this);
    mStateManager.AddActiveState(new(std::nothrow) SCredits(this) );
}

void Game::End()
{
    std::cout << "Game::End()" << std::endl;
    delete mResourceManager;
    mApp.Close();
}

int Game::Run()
{
    Init("OLAF Game Test");
    Loop();
    return EXIT_SUCCESS;
}

void Game::Loop()
{
    std::cout << "Game::Loop()" << std::endl;
    mApp.Display();

    //EVENT LOOP HERE
    sf::Event Event;
    while( mIsRunning && mApp.IsOpened() )
    {
        //Get current State
        GameState* ActualState = mStateManager.GetActiveState();

        while( mApp.GetEvent(Event) )
        {
            // Close window : exit
            if (Event.Type == sf::Event::Closed)
                End();
            // Escape key : exit
            if ((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::Escape))
                End();
            //Gained Focus
            if (Event.Type == sf::Event::GainedFocus)
                ActualState->Resume();
            //Lost Focus
            if (Event.Type == sf::Event::LostFocus)
                ActualState->Pause();

            /*
            switch(Event.Type)
            {
                case sf::Event::Closed:
                    //ActualState->End();
                    End();
                    break;
                case sf::Event::GainedFocus:
                    ActualState->Resume();
                    break;
                case sf::Event::LostFocus:
                    ActualState->Pause();
                    break;
                case sf::Event::Resized:
                    break;
                default:
                    ActualState->HandleEvents(Event);
                    break;
            }
            */
            ActualState->HandleEvents(Event);
        }
        mApp.Clear();
        //Current Scene Update & Draw HERE
        ActualState->Update();
        ActualState->Draw();
        mApp.Display();
    }
}

void Game::SetView(const sf::View& view)
{
    mApp.SetView(view);
}
