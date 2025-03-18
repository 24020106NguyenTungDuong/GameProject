#include "PlaySound.hpp"
#include<SDL_mixer.h>

void playSound(Mix_Chunk* sfx,int volume)
{
          Mix_PlayChannel(-1,sfx,0);
            Mix_VolumeChunk(sfx,volume);


}

