
#include "EntityManager.hpp"

EntityManager& EntityManager::GetInstance()
{
    static EntityManager self;
    return self;
}

EntityManager::EntityManager()
{

}


EntityManager::~EntityManager()
{

}



void EntityManager::Init(sf::RenderWindow* window)
{
    mWindow = window;
}


void EntityManager::End()
{

}


void EntityManager::AddEntity(Entity* entity)
{
	mEntities[0].push_back(entity);
}


void EntityManager::AddEntityToLayer(int layer, Entity* entity)
{
	mEntities[layer].push_back(entity);
}

void EntityManager::Clear()
{
	EntityVector::iterator it;
	for(int i=0; i < NUM_LAYERS; ++i)
	{
		for(it = mEntities[i].begin(); it != mEntities[i].end(); ++it)
		{
			delete *it;
		}
		mEntities[i].clear();
	}
}

void EntityManager::Update(float frametime)
{

}


int EntityManager::GetNumEntities() const
{
	return (int) mEntities[0].size();
}


int EntityManager::GetNumEntities(int layer) const
{
	return (int) mEntities[layer].size();
}


void EntityManager::RenderEntitiesLayer(int layer)
{
	std::vector<Entity*>::iterator it;
	for(it = mEntities[layer].begin(); it != mEntities[layer].end(); ++it)
	{
		mWindow->Draw(**it);
	}
}

void EntityManager::RenderAll()
{
}



//PRIVATE METHODS -----------------------------------------------------

void EntityManager::Render(sf::RenderTarget& target) const
{
	std::vector<Entity*>::const_iterator it;
	for (int i = 0; i < NUM_LAYERS; ++i)
	{
		for(it = mEntities[i].begin(); it != mEntities[i].end(); ++it)
		{
			target.Draw(**it);
		}
	}
}



