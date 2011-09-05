
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

    mWorld = new b2World( b2Vec2(0.0, 2.0), true);

    //------------------------------------------------------------------------------

    timer = new sf::Clock();

    mInGameBG = new Entity( mGame->mResourceManager.GetImage("blue-gradient.png") );
    mCharacter = new Entity( mGame->mResourceManager.GetImage("tree.png") );

    mCharacter->SetScale(0.5, 0.5);

    std::vector<AnimationDef> animDefs = mGame->mResourceManager.LoadAnimationXML("./data/player.xml");
    Animation* PlayerAnimation = new Animation( mGame->mResourceManager.GetImage("player.png"), animDefs );
    PlayerAnimation->SetAnimation("idle");
    PlayerAnimation->SetCenter(40.0f, 40.0f);

    //Player Physics
    b2BodyDef myBodyDef;
    myBodyDef.type = b2_dynamicBody; //this will be a dynamic body
    myBodyDef.position.Set(200*MPP, 50*MPP); //set the starting position
    myBodyDef.angle = 0; //set the starting angle

    b2Body* dynamicBody = mWorld->CreateBody(&myBodyDef);

    b2PolygonShape boxShape;
    boxShape.SetAsBox(32*MPP, 32*MPP);

    b2FixtureDef boxFixtureDef;
    boxFixtureDef.shape = &boxShape;
    boxFixtureDef.density = 1;
    dynamicBody->CreateFixture(&boxFixtureDef);

	mPlayer = new Player(PlayerAnimation, dynamicBody);
    //mPlayer->GetAnimation()->SetPosition(100, 200);
	//-----------------------------------------

	//Add a BOX2D Floor
	//define the static ground body, keeping the shapes from falling into oblivion
	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set( (mGame->mApp.GetWidth())/2*METERS_PER_PIXEL, (mGame->mApp.GetHeight())*METERS_PER_PIXEL);
	//create ground body (static body)
	b2Body *groundBody = mWorld->CreateBody(&groundBodyDef);
	//create a polygon shape for the ground
	b2PolygonShape groundBox;
	groundBox.SetAsBox( (mGame->mApp.GetWidth())/2*METERS_PER_PIXEL, 5*METERS_PER_PIXEL);
	//fix the ground box shape to the ground body
	groundBody->CreateFixture(&groundBox, 0.0f);
	//------------------------------------------


    mLevelMgr.Init( &(mGame->GetApp()) );
    mEntityMgr.Init( &(mGame->GetApp()) );
    mInputMgr.Init( &(mGame->GetApp()), mPlayer );

    mEntityMgr.AddEntityToLayer(1, mInGameBG);
    mEntityMgr.AddEntityToLayer(3, mCharacter);

    //Add player to EntityManager
    mEntityMgr.AddEntityToLayer(2, mPlayer->GetAnimation() );
}

void SInGame::End()
{
    std::cout << "SInGame::End()" << std::endl;
    //mEntityMgr.Clear();
}


void SInGame::HandleEvents(const sf::Event& theEvent)
{

    //mInputMgr.ProcessInput( mGame->GetApp().GetFrameTime() );
    float frameTime = mGame->GetApp().GetFrameTime();

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
        //mPlayer->GetBody()->ApplyForce(b2Vec2(500.0f*frameTime, 0.0f), mPlayer->GetBody()->GetPosition());

        //float impulse = mPlayer->GetBody()->GetMass() * 0.25;
        float impulse = (mPlayer->GetMaxWalkVelocity() - mPlayer->GetBody()->GetLinearVelocity().x) / 12.0f;
        mPlayer->GetBody()->ApplyLinearImpulse( b2Vec2(impulse, 0.0f), mPlayer->GetBody()->GetWorldCenter() );

        //mPlayer->GetAnimation()->SetPosition( mPlayer->GetAnimation()->GetPosition().x + 10,
        //                                     mPlayer->GetAnimation()->GetPosition().y     );
    }


    //if ((theEvent.Type == sf::Event::KeyPressed) && (theEvent.Key.Code == sf::Key::Left))
    if ( mGame->GetApp().GetInput().IsKeyDown(sf::Key::Left) )
    {
        //mLevelMgr.CameraMoveLeft();

        mPlayer->GetAnimation()->FlipX(true);
        mPlayer->GetAnimation()->SetAnimation("walk");
        //mPlayer->GetBody()->ApplyForce(b2Vec2(-500.0f*frameTime, 0.0f), mPlayer->GetBody()->GetPosition());

        //float impulse = mPlayer->GetBody()->GetMass() * 0.25;
        float impulse = (mPlayer->GetMaxWalkVelocity() + mPlayer->GetBody()->GetLinearVelocity().x) / 12.0f;
        mPlayer->GetBody()->ApplyLinearImpulse( b2Vec2(-impulse, 0.0f), mPlayer->GetBody()->GetWorldCenter() );

        //mPlayer->GetAnimation()->SetPosition( mPlayer->GetAnimation()->GetPosition().x - 10,
        //                                      mPlayer->GetAnimation()->GetPosition().y     );
    }

    //if ((theEvent.Type == sf::Event::KeyPressed) && (theEvent.Key.Code == sf::Key::Space))
    if ( mGame->GetApp().GetInput().IsKeyDown(sf::Key::Space) )
    {
        //std::cout << "SInGame::HandleEvents" << std::endl;
        mPlayer->GetAnimation()->SetAnimation("jump");
        //mPlayer->GetBody()->ApplyForce(b2Vec2(0.2, 0.5), b2Vec2(0.0, 0.0) );
        //mPlayer->GetBody()->ApplyForce(b2Vec2(0.0f, -1000.0f*frameTime), mPlayer->GetBody()->GetWorldCenter());

        float impulse = mPlayer->GetBody()->GetMass() * 0.75;
        mPlayer->GetBody()->ApplyLinearImpulse( b2Vec2(0, -impulse), mPlayer->GetBody()->GetWorldCenter() );

        //player->getBody()->ApplyImpulse(b2Vec2(0, 5.0f), player->getBody()->GetWorldCenter());
    }

    if ( mGame->GetApp().GetInput().IsKeyDown(sf::Key::I) )
    {
        std::cout << "Physics position = " << mPlayer->GetBody()->GetPosition().x << " - " << mPlayer->GetBody()->GetPosition().y << std::endl;
        std::cout << "SFML position = " << mPlayer->GetAnimation()->GetPosition().x << " - " << mPlayer->GetAnimation()->GetPosition().y<< std::endl;

        std::cout << "Linear Velocity X = " << mPlayer->GetBody()->GetLinearVelocity().x << std::endl;

        //sf::Vector2f ConvertedPositionBody = ConvertToScreen( mPlayer->GetBody()->GetPosition() );
        //std::cout << "ConvertedPositionBody = " << ConvertedPositionBody.x << " - " << ConvertedPositionBody.y << std::endl;
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

    mPlayer->GetAnimation()->SetPosition( mPlayer->GetBody()->GetPosition().x*PPM, mPlayer->GetBody()->GetPosition().y*PPM);
    //std::cout << "ConvertedPositionBody = " << ConvertedPositionBody.x << " - " << ConvertedPositionBody.y << std::endl;

    mPlayer->GetAnimation()->Update( mGame->mApp.GetFrameTime() );
}


void SInGame::Draw()
{
    mWorld->Step(1.0f/60.0f, 8, 3);
    RenderAll();
}


void SInGame::RenderAll()
{
    mLevelMgr.SetCamera( mLevelMgr.GetCameraA() );
    mEntityMgr.RenderEntitiesLayer(1);

    mLevelMgr.SetCamera( mLevelMgr.GetCameraB() );
    mEntityMgr.RenderEntitiesLayer(2);

    mLevelMgr.SetCamera( mLevelMgr.GetCameraC() );
    mEntityMgr.RenderEntitiesLayer(3);

    //mLevelMgr.CameraLookAt( mPlayer->GetAnimation()->GetPosition() );

    mLevelMgr.SetCamera( mLevelMgr.GetCameraGUI() );
    mEntityMgr.RenderEntitiesLayer(GUI_LAYER);

}




//Private methods -------------------------------

sf::Vector2f SInGame::ConvertToScreen(const b2Vec2& physicsVector) const
{
	return sf::Vector2f(physicsVector.x * 10.0f, physicsVector.y * -10.0f);
}


