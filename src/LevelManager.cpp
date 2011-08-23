
#include "LevelManager.hpp"

LevelManager& LevelManager::GetInstance()
{
    static LevelManager self;
    return self;
}

//ctor
LevelManager::LevelManager()
{
    Camera_A = new sf::View(sf::FloatRect(0, 0, 1024, 768));
	Camera_B = new sf::View(sf::FloatRect(0, 0, 1024, 768));
	Camera_C = new sf::View(sf::FloatRect(0, 0, 1024, 768));
	Camera_GUI = new sf::View(sf::FloatRect(0, 0, 1024, 768));

    mCurrentLayer = 1;

    Offset_A = 150.f;
    Offset_B = 250.f;
    Offset_C = 300.f;
    Offset_GUI = 450.f;
}

//dtor
LevelManager::~LevelManager()
{
    delete Camera_A;
	delete Camera_B;
	delete Camera_C;
	delete Camera_GUI;
}


void LevelManager::Init(sf::RenderWindow* window)
{
    mWindow = window;
}

int LevelManager::GetCurrentLayer()
{
	return mCurrentLayer;
}

void LevelManager::SetCurrentLayer(int layer)
{
	mCurrentLayer = layer;
	switch(layer)
	{
		case(GUI_LAYER): 	mCurrentCamera = Camera_GUI; 	break;
		case(1): 			mCurrentCamera = Camera_A; 		break;
		case(2): 			mCurrentCamera = Camera_B; 		break;
		case(3): 			mCurrentCamera = Camera_C; 		break;
		default: 											break;
	}
}

void LevelManager::SetCamera(sf::View* camera)
{
	mWindow->SetView(*camera);
	mCurrentCamera = camera;
}


sf::View* LevelManager::GetCurrentCamera()
{
    return mCurrentCamera;
}


void LevelManager::CameraMoveUp()
{
        Camera_A->Move(0, -Offset_A * mWindow->GetFrameTime() );
        Camera_B->Move(0, -Offset_B * mWindow->GetFrameTime() );
        Camera_C->Move(0, -Offset_C * mWindow->GetFrameTime() );
}


void LevelManager::CameraMoveDown()
{
        Camera_A->Move(0, Offset_A * mWindow->GetFrameTime() );
        Camera_B->Move(0, Offset_B * mWindow->GetFrameTime() );
        Camera_C->Move(0, Offset_C * mWindow->GetFrameTime() );
}


void LevelManager::CameraMoveRight()
{
        Camera_A->Move(Offset_A * mWindow->GetFrameTime(), 0 );
        Camera_B->Move(Offset_B * mWindow->GetFrameTime(), 0 );
        Camera_C->Move(Offset_C * mWindow->GetFrameTime(), 0 );
}


void LevelManager::CameraMoveLeft()
{
        Camera_A->Move(-Offset_A * mWindow->GetFrameTime(), 0 );
        Camera_B->Move(-Offset_B * mWindow->GetFrameTime(), 0 );
        Camera_C->Move(-Offset_C * mWindow->GetFrameTime(), 0 );
}


void LevelManager::CameraLookAt(const sf::Vector2f& lookat)
{
    mCurrentCamera->SetCenter(lookat);
}



