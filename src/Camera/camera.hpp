#ifndef CAMERA_HPP
#define CAMERA_HPP
#include <SDL.h>
#include "constants.hpp"
#include "Entity.hpp"
struct camera
{
    public:
        SDL_Rect viewPortion;
            camera()
            {
                viewPortion.x=0;
                viewPortion.y=0;
                viewPortion.w=screenWidth;
                viewPortion.h=screenHeight;

            };
        void updateCamera(Entity& p_center);

};

#endif // CAMERA_HPP
