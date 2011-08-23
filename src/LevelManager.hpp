#ifndef LEVELMANAGER_HPP
#define LEVELMANAGER_HPP

#include <iostream>

#include <SFML/Graphics.hpp>

#define GUI_LAYER 0

class LevelManager
{
    public:
        static LevelManager& GetInstance();

        //Init
        void Init(sf::RenderWindow* window);

        //Layers
        int GetCurrentLayer();
        void SetCurrentLayer(int layer);

        //Cameras
		void SetCamera(sf::View* camera);
		sf::View*	GetCurrentCamera();

		sf::View*	GetCameraA() 	{ return Camera_A; }
		sf::View*	GetCameraB() 	{ return Camera_B; }
        sf::View*	GetCameraC() 	{ return Camera_C; }
		sf::View*	GetCameraGUI()	{ return Camera_GUI; }

		void        CameraMoveUp();
		void        CameraMoveDown();
		void        CameraMoveRight();
		void        CameraMoveLeft();

		void        CameraLookAt(const sf::Vector2f& lookat);

    private:

        sf::RenderWindow* mWindow;

        LevelManager();
        LevelManager(const LevelManager&);
        ~LevelManager();

        //Cameras
        // 4 main layers - GUI + 3 scroll parallax layers
        float Offset_A;
		float Offset_B;
        float Offset_C;
		float Offset_GUI;

        sf::View*		Camera_A;
		sf::View*		Camera_B;
        sf::View*		Camera_C;
		sf::View*		Camera_GUI;

		int 			mCurrentLayer;
		sf::View* 		mCurrentCamera;


};

#endif
