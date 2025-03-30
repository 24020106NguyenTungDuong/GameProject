#include "camera.hpp"

void camera::updateCamera(Entity& p_center)
{
    viewPortion.x=p_center.position.x+entityScalar*p_center.currentFrame.w/2-screenWidth/2;
}
