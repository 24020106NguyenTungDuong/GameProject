#include "camera.hpp"

void camera::updateCamera(Entity& p_center)
{
    viewPortion.x=p_center.position.x-screenWidth/2;
    viewPortion.y=p_center.position.y-screenHeight/2;



}
