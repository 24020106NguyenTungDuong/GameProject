#ifndef PLAYSOUND_HPP
#define PLAYSOUND_HPP
#include<SDL_mixer.h>


class PlaySound
{
    public:
    PlaySound()
    {
        backgroundMusic=Mix_LoadMUS("res/Sound/Music/Pocket Universe - Context Sensitive.mp3");
        slashSound=Mix_LoadWAV("res/Sound/SFX/slash.wav");
        dashSound=Mix_LoadWAV("res/Sound/SFX/dash.wav");
        runningSound=Mix_LoadWAV("res/Sound/SFX/running.wav");
        jumpSound=Mix_LoadWAV("res/Sound/SFX/jump.wav");
    };

    public:
    Mix_Music* backgroundMusic;
    Mix_Chunk* slashSound;
    Mix_Chunk* dashSound;
    Mix_Chunk* runningSound;
    Mix_Chunk* jumpSound;
};
 void playSound(Mix_Chunk* sfx,int volume);
#endif // PLAYSOUND_HPP
