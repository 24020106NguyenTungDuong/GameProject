#ifndef UTILS_HPP
#define UTILS_HPP
#include<SDL.h>
namespace utils
{
    inline float getTimeSeconds()
    {
     float timeTicks=SDL_GetTicks();
     timeTicks*=0.001f;
        return timeTicks;
    }

}

#endif // UTILS_HPP
