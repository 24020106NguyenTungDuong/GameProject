#ifndef RENDERWINDOW_HPP
#define RENDERWINDOW_HPP
#include<SDL.h>
#include <SDL_image.h>
#include "Entity.hpp"
#include "constants.hpp"
#include "tileMap.hpp"
#include "camera.hpp"
#include "chunkMap/chunkMap.hpp"
class RenderWindow
{
    public:
        RenderWindow(const char* title,int p_width,int p_height);
        SDL_Texture* LoadTexture(const char* p_FilePath);
        void renderChunk(camera p_camera,vector <tileMap>& leftChunk,vector <tileMap>& centerChunk,vector <tileMap>&rightChunk);
        //GameLoop
        void CleanUp();
        //Clear window, renderer and quit SDL

        void ClearScreen();
        void RenderTexture(Entity& p_entity,camera& p_cam);
        void RenderMap(tileMap& p_tileMap,camera p_cam);
        void Display();
        SDL_Renderer* &getRenderer();


    private:
        SDL_Renderer* renderer;
        SDL_Window* window;
};
void gameLoop();
#endif // RENDERWINDOW_HPP
