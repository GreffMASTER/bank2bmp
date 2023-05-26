#ifndef TILE_H
#define TILE_H

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <SDL.h>
#include "BaltieTypes.h"

/*
     BALTIE TILE
     A Tile stores its pixel information as well as its transparency mask color
*/

class Tile {
    public:
        Tile();                                 // Make empty tile
        Tile(SDL_RWops * bankfile);             // Load tile from a Bank file
        Tile(SDL_Surface * surf, uint8_t tcol); // Make tile from surface
        virtual ~Tile();
        void draw(SDL_Renderer * renderer, int x, int y, bool transparent);
        void to_bmp(const char * path);         // Save tile to BMP image
        void write(SDL_RWops * bankfile);

        SDL_Surface * m_tilesurface = nullptr;  // Tiles surface
        SDL_Surface * m_tilesurface_t = nullptr;// Transperent Tiles surface
        SDL_Rect m_tilerect;                    // Tiles Rect
        uint8_t m_transpcolor;                  // Transparent color
};

#endif // TILE_H
