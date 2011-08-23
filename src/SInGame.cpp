
#include "SInGame.hpp"
#include "SMenuInGame.hpp"

SInGame::SInGame(Game* game) :
    GameState(game),
    mEntityMgr( EntityManager::GetInstance() ),
    mLevelMgr( LevelManager::GetInstance() ),
    mInputMgr( InputManager::GetInstance() ),
    mInGameBG(NULL),
    timer(NULL)
{

}

SInGame::~SInGame()
{
    delete mCharacter;
    mCharacter = NULL;

    delete mInGameBG;
    mInGameBG = NULL;

    delete mPlayer;
    mPlayer = NULL;

    delete mWorld;
    mWorld = NULL;

    delete timer;
}

void SInGame::Init()
{

    //INIT Physics -----------------------------------------------------------------

    mWorld = new b2World( b2Vec2(0, 10.0), true);

    //------------------------------------------------------------------------------

    timer = new sf::Clock();

    mInGameBG = new Entity( mGame->mResourceManager->GetImage("blue-gradient.png") );
    mCharacter = new Entity( mGame->mResourceManager->GetImage("tree.png") );

    std::vector<AnimationDef> animDefs = mGame->mResourceManager->LoadAnimationXML("./data/player.xml");
    Animation* PlayerAnimation = new Animation( mGame->mResourceManager->GetImage("player.png"), animDefs );
    PlayerAnimation->SetAnimation("idle");
    PlayerAnimation->SetCenter(40.0f, 40.0f);

    //Player Physics
    b2BodyDef myBodyDef;
    myBodyDef.type = b2_dynamicBody; //this will be a dynamic body
    myBodyDef.position.Set(0, 20); //set the starting position
    myBodyDef.angle = 0; //set the starting angle

    b2Body* dynamicBody = mWorld->CreateBody(&myBodyDef);

    b2PolygonShape boxShape;
    boxShape.SetAsBox(1, 1);

    b2FixtureDef boxFixtureDef;
    boxFixtureDef.shape = &boxShape;
    boxFixtureDef.density = 1;
    dynamicBody->CreateFixture(&boxFixtureDef);

	mPlayer = new Player(PlayerAnimation, dynamicBody);
    mPlayer->GetAnimation()->SetPosition(100, 200);
	//-----------------------------------------

    mLevelMgr.Init( &(mGame->GetApp()) );
    mEntityMgr.Init( &(mGame->GetApp()) );
    mInputMgr.Init( &(mGame->GetApp()), mPlayer );

    mEntityMgr.AddEntityToLayer(1, mInGameBG);
    mEntityMgr.AddEntityToLayer(2, mCharacter);

    //Add player to EntityManager
    //mEntityMgr.AddEntityToLayer(3, mPlayer->GetAnimation() );
}

void SInGame::End()
{
    std::cout << "SInGame::End()" << std::endl;
    //mEntityMgr.Clear();
}


void SInGame::HandleEvents(const sf::Event& theEvent)
{

    //mInputMgr.ProcessInput( mGame->GetApp().GetFrameTime() );

    //---------------------------------------------------------------------------------------------
    //*

    // Escape key pressed
    //if ((theEvent.Type == sf::Event::KeyPressed) && (theEvent.Key.Code == sf::Key::Escape))
    if ( mGame->GetApp().GetInput().IsKeyDown(sf::Key::Escape) )
    {
        if (timer->GetElapsedTime() > 0.05 )
        {
          if(NULL != mGame)
          {
            End();
            //mGame->End();
          }
        }
        timer->Reset();
    }

    //Player Control ---------------------------------------------------------------------
    //if ((theEvent.Type == sf::Event::KeyPressed) && (theEvent.Key.Code == sf::Key::Up))
    if ( mGame->GetApp().GetInput().IsKeyDown(sf::Key::Up) )
    {
        //mLevelMgr.CameraMoveUp();
    }


    //if ((theEvent.Type == sf::Event::KeyPressed) && (theEvent.Key.Code == sf::Key::Down))
    if ( mGame->GetApp().GetInput().IsKeyDown(sf::Key::Down) )
    {
        //mLevelMgr.CameraMoveDown();
    }


    //if ((theEvent.Type == sf::Event::KeyPressed) && (theEvent.Key.Code == sf::Key::Right))
    if ( mGame->GetApp().GetInput().IsKeyDown(sf::Key::Right) )
    {
        //mLevelMgr.CameraMoveRight();
        mPlayer->GetAnimation()->FlipX(false);
        mPlayer->GetAnimation()->SetAnimation("walk");
        mPlayer->GetAnimation()->SetPosition( mPlayer->GetAnimation()->GetPosition().x + 10,
                                              mPlayer->GetAnimation()->GetPosition().y     );
    }


    //if ((theEvent.Type == sf::Event::KeyPressed) && (theEvent.Key.Code == sf::Key::Left))
    if ( mGame->GetApp().GetInput().IsKeyDown(sf::Key::Left) )
    {
        //mLevelMgr.CameraMoveLeft();

        mPlayer->GetAnimation()->FlipX(true);
        mPlayer->GetAnimation()->SetAnimation("walk");
        mPlayer->GetAnimation()->SetPosition( mPlayer->GetAnimation()->GetPosition().x - 10,
                                              mPlayer->GetAnimation()->GetPosition().y     );
    }

    //if ((theEvent.Type == sf::Event::KeyPressed) && (theEvent.Key.Code == sf::Key::Space))
    if ( mGame->GetApp().GetInput().IsKeyDown(sf::Key::Space) )
    {
        //std::cout << "SInGame::HandleEvents" << std::endl;
        mPlayer->GetAnimation()->SetAnimation("jump");
    }

    if ( mGame->GetApp().GetInput().IsKeyDown(sf::Key::R) )
    {

    }

    //---------------------------------------------------------------------------------------

    if ( mGame->GetApp().GetInput().IsKeyDown(sf::Key::N) )
    {
        if ( timer->GetElapsedTime() > 0.02 ) {
            mGame->mStateManager.PushState( new(std::nothrow) SMenuInGame(mGame) );
        }
        timer->Reset();
    }

    if ( mGame->GetApp().GetInput().IsKeyDown(sf::Key::P) )
    {
        std::cout << "MenuInGame - PopState() SCENE!!" << std::endl;
        mGame->mStateManager.PopState();
    }
    //*/
    //---------------------------------------------------------------------------------------------

}


void SInGame::Update()
{
    //std::cout << "SInGame::Update" << std::endl;
    //mEntityMgr.Update(frametime);

    //mPlayer->GetAnimation()->Update( mGame->mApp.GetFrameTime() );
}


void SInGame::RenderAll()
{
    mLevelMgr.SetCamera( mLevelMgr.GetCameraA() );
    mEntityMgr.RenderEntitiesLayer(1);

    mLevelMgr.CameraLookAt( mPlayer->GetAnimation()->GetPosition() );

    mLevelMgr.SetCamera( mLevelMgr.GetCameraB() );
    mEntityMgr.RenderEntitiesLayer(2);

    mLevelMgr.SetCamera( mLevelMgr.GetCameraC() );
    mEntityMgr.RenderEntitiesLayer(3);

    mLevelMgr.SetCamera( mLevelMgr.GetCameraGUI() );
    mEntityMgr.RenderEntitiesLayer(GUI_LAYER);
}


void SInGame::Draw()
{
    RenderAll();
}


