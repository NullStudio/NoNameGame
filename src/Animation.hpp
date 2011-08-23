#ifndef ANIMATION_HPP
#define ANIMATION_HPP

#include <string>
#include <vector>
#include <map>

#include <SFML/Graphics.hpp>

#include "Entity.hpp"


struct AnimationDef
{
    std::string                 Name;
    int                         FPS;
    std::vector<sf::IntRect>    Frames;
};

class Animation : public Entity
{
    public:

        Animation(const sf::Image& spriteSheet, const std::vector<AnimationDef>& definition);
        void Update(float elapsedTime);
        void SetAnimation(const std::string AnimName);

    private:
        void                                    NextFrame();

        std::map<std::string, AnimationDef>     mAnimations;
        //const AnimationDef* mCurrentAnimation;  ??
        AnimationDef*                           mCurrentAnimation;
        unsigned int                            mCurrentFrame;
        float                                   mAnimationTime;
};

#endif
