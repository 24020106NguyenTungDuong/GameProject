#ifndef ANIMATION_HPP
#define ANIMATION_HPP
#include<SDL.h>
#include <SDL_image.h>
class animation
{
    public:
        SDL_Rect src;
        int frameCounter;
    public:
            animation()
            :spriteSheet(NULL),frameWidth(32),frameHeight(32),totalFrames(0)
            {


            }
            animation(SDL_Texture* p_spriteSheet,int p_frameWidth,int p_frameHeight,int p_totalFrames)
                :spriteSheet(p_spriteSheet),frameWidth(p_frameWidth),frameHeight(p_frameHeight),totalFrames(p_totalFrames)
            {
                src.x=0;
                src.y=0;
                src.w=frameWidth;
                src.h=frameHeight;
                frameCounter=0;
            }

    private:
        SDL_Texture* spriteSheet;
        int frameWidth;
        int frameHeight;
        int totalFrames;
};

#endif // ANIMATION_HPP
