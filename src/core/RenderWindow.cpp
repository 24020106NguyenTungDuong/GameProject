#include<SDL.h>
#include <SDL_image.h>
#include<iostream>
#include "RenderWindow.hpp"
#include "Entity.hpp"
#include "utils.hpp"
#include "constants.hpp"
#include "camera.hpp"
RenderWindow::RenderWindow(const char* title,int p_width,int p_height)
    :window(NULL),renderer(NULL)
{
    window=SDL_CreateWindow(title,SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,p_width,p_height,SDL_WINDOW_SHOWN);
    if(window==NULL)
        std::cout<<"Window failed to innit. Error:"<<SDL_GetError<<std::endl;
    renderer=SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(renderer==NULL)
        std::cout<<"Renderer failed to innit. Error:"<<SDL_GetError<<std::endl;
}
//void gameLoop()
//{
//    bool GameRunning=1;
//    SDL_Event event;
//    float accumulator=0.0f;
//    float currentTime=utils::getTimeSeconds();
//    while(GameRunning)
//    {
//        float newTime=utils::getTimeSeconds();
//        float frameTime=newTime-currentTime;
//        accumulator+=frameTime;
//        currentTime=newTime;
//        while(accumulator>=timeStep)
//        {
//                while(SDL_PollEvent(&event))
//            {
//            if(event.type==SDL_QUIT||event.type==SDL_KEYDOWN)
//                GameRunning=0;
//                if(event.type==SDL_KEYDOWN)
//                {
//                    platform0.moveDown();
//                }
//
//            }
//            accumulator-=timeStep;
//        }
//
//    }
//
//}
SDL_Texture* RenderWindow::LoadTexture(const char* p_FilePath)
{
    SDL_Texture* Texture=NULL;
    Texture=IMG_LoadTexture(renderer,p_FilePath);
    if(Texture==NULL)
    {
        std::cout<<"IMG_LoadTexture failed. Error:"<<IMG_GetError()<<std::endl;

    }
    return Texture;
}
void RenderWindow::CleanUp()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}
void RenderWindow::ClearScreen()
{
    SDL_RenderClear(renderer);
}
void RenderWindow::RenderTexture(Entity& p_entity,camera& p_cam)
{
    SDL_Rect src;
    src.x=p_entity.currentFrame.x;
	src.y=p_entity.currentFrame.y;
	src.w=p_entity.currentFrame.w;
	src.h=p_entity.currentFrame.h;

	SDL_Rect dst;
	dst.x=p_entity.position.x-p_cam.viewPortion.x;
	dst.y=p_entity.position.y-p_cam.viewPortion.y;
	dst.w=p_entity.currentFrame.w * entityScalar;
	dst.h=p_entity.currentFrame.h * entityScalar;

   // if(dst.x+dst.w<p_cam.viewPortion.x || dst.x>p_cam.viewPortion.x+screenWidth) return;
    //if(dst.y+dst.h<p_cam.viewPortion.y || dst.y>p_cam.viewPortion.y+screenHeight) return;

    SDL_RenderCopyEx(renderer, p_entity.getTexture(),&src,&dst,p_entity.rotateAngle,NULL,p_entity.spriteFlip);
}
void RenderWindow::RenderMap(tileMap& p_tileMap,camera p_cam)
{
    SDL_Rect dst=p_tileMap.dst;
    int xPos=p_tileMap.position.x;
    int yPos=p_tileMap.position.y;

    dst.x-=p_cam.viewPortion.x;
    dst.y-=p_cam.viewPortion.y;
    if(xPos+dst.w<p_cam.viewPortion.x || xPos >p_cam.viewPortion.x+screenWidth) return;
    if(yPos+dst.h<p_cam.viewPortion.y || yPos >p_cam.viewPortion.y+screenHeight) return;
    SDL_RenderCopy(renderer,p_tileMap.getTexture(),&p_tileMap.src,&dst);
}
void RenderWindow::Display()
{
    SDL_RenderPresent(renderer);


}


