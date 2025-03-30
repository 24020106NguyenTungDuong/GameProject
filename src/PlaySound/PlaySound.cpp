#include "PlaySound.hpp"
#include<SDL_mixer.h>

void playSound(Mix_Chunk* sfx,int volume)
{
          Mix_PlayChannel(-1,sfx,0);
            Mix_VolumeChunk(sfx,volume);


}
 void PlaySound::CleanUp()
 {
    Mix_FreeMusic(backgroundMusic);
    Mix_FreeChunk(slashSound);
    Mix_FreeChunk(dashSound);
    Mix_FreeChunk(bulletSound);
    Mix_FreeChunk(runningSound);
    Mix_FreeChunk(jumpSound);
        Mix_Quit();
 }
