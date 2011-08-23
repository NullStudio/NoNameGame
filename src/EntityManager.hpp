#ifndef ENTITYMANAGER_HPP
#define ENTITYMANAGER_HPP

#define NUM_LAYERS		32

#include "Game.hpp"
#include "Entity.hpp"

class EntityManager : public sf::Drawable
{
    public:
        static EntityManager& GetInstance();

        void Init(sf::RenderWindow* window);
        void End();

        void AddEntity(Entity* entity);
        void AddEntityToLayer(int layer, Entity* entity);

        void Clear();

        void Update(float frametime);

        int GetNumEntities() const;
        int GetNumEntities(int layer) const;

        void RenderEntitiesLayer(int layer);
        void RenderAll();

    private:
        EntityManager();
        EntityManager(const EntityManager&);
        ~EntityManager();

        sf::RenderWindow* mWindow;
        void Render(sf::RenderTarget& target) const;


        typedef std::vector<Entity*>    EntityVector;
        EntityVector                    mEntities[NUM_LAYERS];
};

#endif
