#include "chunkMap.hpp"

void inputMap(int p_map[][mapTileWidth],string filePath)
{
    std::ifstream file(filePath);
    for(int i=0;i<mapTileHeight;i++)
        for(int j=0;j< mapTileWidth;j++)
    {
        file>>p_map[i][j];
    }


    file.close();



    return;
}
void loadChunk(int p_map[][mapTileWidth],SDL_Texture* greenBrick,SDL_Texture* platform,vector <tileMap> &chunk,int chunkPosition,int chunkNumber)
{
    chunk.clear();
                    for(int y=0;y<mapTileHeight;y++)
        {
            for(int x=0;x<mapTileWidth;x++)
                {
                    if(p_map[y][x]==solidTile)
                                    {
                                        chunk.push_back(tileMap(greenBrick,vector2f(32*x+(chunkNumber+chunkPosition)*screenWidth,32*y),solidTile));
                                    }
                    else if(p_map[y][x]==platformer)
                                    {
                                        chunk.push_back(tileMap(platform,vector2f(32*x+(chunkNumber+chunkPosition)*screenWidth,32*y),platformer));
                                        if(p_map[y][x-1]==1)
                                        {
                                            int lastTileAdded=chunk.size()-1;
                                            chunk[lastTileAdded].src.x=4*16;
                                        }
                                        else if(p_map[y][x+1]==1)
                                        {
                                            int lastTileAdded=chunk.size()-1;
                                            chunk[lastTileAdded].src.x=5*16;
                                        }
                                    }

                }
        }



}


