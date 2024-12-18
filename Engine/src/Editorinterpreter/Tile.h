// Used to avoid circular includes, and just better practice than shoving this in a random class
#pragma once

struct Tile
{
    std::string name;
    int tileID;
    SDL_Texture* tileTexture;
    int xPos;
    int yPos;
    int xSize;
    int ySize;
};