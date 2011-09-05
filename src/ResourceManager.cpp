
#include <string>

#include "ResourceManager.hpp"

//tinyxml++
#define TIXML_USE_TICPP
#include "ticpp/ticpp.h"

void StringToValues(std::string str, std::string separator, std::vector<int>* results)
{
    char *token = strtok( const_cast<char*>(str.c_str() ), separator.c_str() );
    while ( token != NULL )
    {
        results->push_back( atoi(token) );
        token = strtok( NULL, separator.c_str() );
    }
}


ResourceManager& ResourceManager::GetInstance()
{
    static ResourceManager self;
    return self;
}


ResourceManager::ResourceManager()
{

}

ResourceManager::~ResourceManager()
{

}

bool ResourceManager::Init()
{
	return 1;
}

void ResourceManager::End()
{

}

const sf::Image& ResourceManager::GetImage(const std::string& filename) {

	for(std::map<std::string, sf::Image>::const_iterator it = mImages.begin(); it != mImages.end(); ++it)
	{
		if (it->first == filename)
		{
			//std::cout << "DEBUG:: " << filename << " using existing image." << std::endl;
			return it->second;
		}
	}

	sf::Image img;

	if ( img.LoadFromFile(filename) )
	{
		mImages[filename] = img;
		//std::cout << "DEBUG:: " << filename << " loading image." << std::endl;
		return mImages[filename];
	}

	//Search registered directories
	for( std::vector<std::string>::iterator it = mResourceDir.begin(); it != mResourceDir.end(); ++it)
	{
		if ( img.LoadFromFile( (*it) + filename ) )
		{
			mImages[filename] = img;
			//std::cout << "DEBUG:: " << filename << " loading image." << std::endl;
			return mImages[filename];
		}
	}

	//std::cout << "DEBUG: SliderEngine ERROR: Image was not found - filled with an empty image" << std::endl;
	mImages[filename] = img;
	return mImages[filename];
}


void ResourceManager::DeleteImage(const sf::Image& image) {

	for( std::map<std::string, sf::Image>::iterator it = mImages.begin(); it != mImages.end(); ++it)
	{
		if ( &image == &it->second )
		{
			mImages.erase( it );
			return;
		}
	}
}

void ResourceManager::DeleteImage(const std::string& filename) {

	std::map<std::string, sf::Image>::iterator it = mImages.find(filename);
	if ( it != mImages.end() )
		mImages.erase( it );
}

void ResourceManager::AddResourceDir(const std::string& dir) {

	std::cout << "DEBUG: AddResourceDir called!" << std::endl;

	for( std::vector<std::string>::const_iterator it = mResourceDir.begin(); it != mResourceDir.end(); ++it)
	{
		if (dir == (*it) )
			return;
	}
	mResourceDir.push_back(dir);
}

void ResourceManager::RemoveResourceDir(const std::string& dir) {

	for(std::vector<std::string>::iterator it = mResourceDir.begin(); it != mResourceDir.end(); ++it)
	{
		if ( dir == (*it) )
			it = mResourceDir.erase(it);
		else
			++it;
	}
}


//Animation XML

std::vector<AnimationDef> ResourceManager::LoadAnimationXML(const std::string& filename)
{
	std::vector<AnimationDef> animDefs;

	ticpp::Document doc(filename);
	doc.LoadFile();
	ticpp::Iterator<ticpp::Element> itAnim;
	for( itAnim = itAnim.begin( doc.FirstChildElement() ); itAnim != itAnim.end(); ++itAnim)
	{
	    AnimationDef def;
	    itAnim->FirstChild("action")->FirstChild()->ToText()->GetValue(&def.Name);
	    itAnim->FirstChild("fps")->FirstChild()->ToText()->GetValue(&def.FPS);

	    ticpp::Iterator<ticpp::Element> frame;
	    for( frame = frame.begin(itAnim->FirstChild("frames")); frame != frame.end(); ++frame)
	    {
	        std::string frameValue = frame->FirstChild()->ToText()->Value();
	        //std::cout << "frameValue = " << frameValue << std::endl;
	        std::vector<int> tokens;
	        StringToValues(frameValue, ",", &tokens);
	        def.Frames.push_back( sf::IntRect( tokens[0], tokens[1], tokens[2], tokens[3] ));
	    }
	    animDefs.push_back(def);
	}
    return animDefs;
}





