#include "Projectile.hpp"


void Projectile::updateProj(float timeAcumulator)
{

        currentFrame.x=int(timeAcumulator/timeStep)%6*slashWidth;

}
