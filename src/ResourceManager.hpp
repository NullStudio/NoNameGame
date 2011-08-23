
#ifndef SE_RESOURCEMANAGER_HPP
#define SE_RESOURCEMANAGER_HPP

#include <iostream>
#include <map>
#include <SFML/Graphics.hpp>

//Animation
#include "Animation.hpp"

class ResourceManager {

	public:

		ResourceManager();
		~ResourceManager();

		bool Init();
		void End();

		const sf::Image&	GetImage(const std::string& filename);
		void				DeleteImage(const sf::Image& image);
		void				DeleteImage(const std::string& filename);
		void				AddResourceDir(const std::string& dir);
		void				RemoveResourceDir(const std::string& dir);

		//AnimationDef Load from XML
		std::vector<AnimationDef>    LoadAnimationXML(const std::string& filename);

	private:

		std::map< std::string, sf::Image > mImages;
		std::vector< std::string > mResourceDir;
};

#endif
