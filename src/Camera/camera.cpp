#include "camera.hpp"

void camera::updateCamera(Entity& p_center)
{
    viewPortion.x=p_center.position.x+entityScalar*p_center.currentFrame.w/2-screenWidth/2;
    //viewPortion.y=p_center.position.y+entityScalar*p_center.currentFrame.h/2-screenHeight/2;
}
