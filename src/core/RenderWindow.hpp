#ifndef RENDERWINDOW_HPP
#define RENDERWINDOW_HPP
#include<SDL.h>
#include <SDL_image.h>
#include<SDL_ttf.h>
#include "Entity.hpp"
#include "constants.hpp"
#include "tileMap.hpp"
#include "camera.hpp"
#include "chunkMap/chunkMap.hpp"
class RenderWindow
{
    public:
        RenderWindow  (const char* title,int p_width,int p_height);
        SDL_Texture* LoadTexture(const char* p_FilePath);
        void renderChunk(camera p_camera,vector <tileMap>& leftChunk,vector <tileMap>& centerChunk,vector <tileMap>&rightChunk);
        //GameLoop
        void CleanUp();
        //Clear window, renderer and quit SDL

        void ClearScreen();
        void RenderTexture(Entity& p_entity,camera& p_cam);
        void RenderMap(tileMap& p_tileMap,camera p_cam);
        void Display();
        void renderBackGround();
        void renderPNG(SDL_Texture* img);
        void renderCursor(int mouseX,int mouseY);
        void renderText(const char* text,vector2f textPosition,SDL_Color textColor=textcolor);
    private:
        SDL_Window* window;
        SDL_Renderer* renderer;
        TTF_Font* font;
        SDL_Texture* background;
        SDL_Texture* cursor;
        int backgroundType;
};
#endif // RENDERWINDOW_HPP
