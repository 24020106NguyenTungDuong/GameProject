#include "Projectile.hpp"


void Projectile::updateProj(float timeAcumulator)
{

        currentFrame.x=int(timeAcumulator/(timeStep/2))%6*slashWidth;

}
