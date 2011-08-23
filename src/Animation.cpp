
#include "Animation.hpp"

Animation::Animation(const sf::Image& spriteSheet, const std::vector<AnimationDef>& definition) :
    //Sprite(spriteSheet), mCurrentAnimation(0), mCurrentFrame(0), mAnimationTime(0.0f)
    Entity(spriteSheet), mCurrentAnimation(0), mCurrentFrame(0), mAnimationTime(0.0f)
{
    for(std::vector<AnimationDef>::const_iterator it = definition.begin(); it != definition.end(); ++it)
    {
        mAnimations[it->Name] = *it;
    }
}


void Animation::Update(float elapsedTime)
{
    if ( mCurrentAnimation && mCurrentAnimation->FPS > 0 )
    {
        mAnimationTime += elapsedTime;
        if ( mAnimationTime >= ( 1.0f / mCurrentAnimation->FPS) )
        {
            NextFrame();
            mAnimationTime = 0;
        }
        SetSubRect( mCurrentAnimation->Frames[mCurrentFrame] );
    }
}


void Animation::SetAnimation(const std::string AnimName)
{
    if ( mCurrentAnimation && mCurrentAnimation->Name == AnimName ) return;

    //const_iterator here??  or ::iterator ?
    std::map<std::string, AnimationDef>::iterator it = mAnimations.find(AnimName);
    if ( it != mAnimations.end() )
    {
        mCurrentAnimation = &(it->second);
        mCurrentFrame = 0;
        mAnimationTime = 0;
        SetSubRect( mCurrentAnimation->Frames[mCurrentFrame]);
    }
}

//Private method
void Animation::NextFrame()
{
    mCurrentFrame = (mCurrentFrame >= mCurrentAnimation->Frames.size()-1) ? 0 : mCurrentFrame + 1;
}
