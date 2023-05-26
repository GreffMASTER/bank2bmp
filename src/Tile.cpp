#include "Tile.h"

void reversearray(uint8_t* arr, uint32_t s) {
    uint8_t * iarr = arr, * iend = iarr + s;
    std::reverse(iarr, iend);
}

Tile::Tile() {
    m_transpcolor = 0xFF;   // No transparency
    m_tilerect.x = 0; m_tilerect.y = 0; m_tilerect.w = 39; m_tilerect.h = 29;
    m_tilesurface = SDL_CreateRGBSurface(0, m_tilerect.w, m_tilerect.h, 32, 0, 0, 0, 0);
    m_tilesurface_t = SDL_CreateRGBSurface(0, m_tilerect.w, m_tilerect.h, 32, 0, 0, 0, 0);
    SDL_BlitSurface(m_tilesurface, &m_tilerect, m_tilesurface_t, nullptr);
    if(m_transpcolor != 0xFF) SDL_SetColorKey(m_tilesurface_t, SDL_TRUE, BaltieType::colors[m_transpcolor]);
}

Tile::Tile(SDL_RWops * bankfile) {
    m_tilerect.x = 0; m_tilerect.y = 0; m_tilerect.w = 39; m_tilerect.h = 29;
    SDL_Surface * tilesurf = SDL_CreateRGBSurface(0, m_tilerect.w, m_tilerect.h, 32, 0, 0, 0, 0);
    uint32_t * pixels = (uint32_t *) tilesurf->pixels;
    char idk[3];
    bankfile->read(bankfile, idk, sizeof(idk), 1);
    bankfile->read(bankfile, &m_transpcolor, sizeof(m_transpcolor), 1);

    for(int line=0;line<29;line++) { // Begin tile read
        BaltieType::colormask masks[4] = {0};
        bankfile->read(bankfile, masks, sizeof(BaltieType::colormask), 4);

        for(int i=0;i<4;i++) reversearray(masks[i], sizeof(BaltieType::colormask));

        uint64_t mask1, mask2, mask3, mask4;
        std::memcpy(&mask1, masks[0], sizeof(uint64_t));
        std::memcpy(&mask2, masks[1], sizeof(uint64_t));
        std::memcpy(&mask3, masks[2], sizeof(uint64_t));
        std::memcpy(&mask4, masks[3], sizeof(uint64_t));
        for(int pixpos=0;pixpos<40;pixpos++) {
            uint8_t color = 0;
            if((mask4 >> pixpos) & 1) color = color | 0b0001;
            if((mask3 >> pixpos) & 1) color = color | 0b0010;
            if((mask2 >> pixpos) & 1) color = color | 0b0100;
            if((mask1 >> pixpos) & 1) color = color | 0b1000;

            uint32_t gpixelpos = (line*39)+39-pixpos;

            pixels[gpixelpos] = BaltieType::colors[color];
        }
    } // End of tile read
    char idk2[2];
    bankfile->read(bankfile, idk2, sizeof(idk2), 1);


    m_tilesurface = tilesurf;
    m_tilesurface_t = SDL_CreateRGBSurface(0, m_tilerect.w, m_tilerect.h, 32, 0, 0, 0, 0);
    SDL_BlitSurface(m_tilesurface, &m_tilerect, m_tilesurface_t, nullptr);
    if(m_transpcolor != 0xFF) SDL_SetColorKey(m_tilesurface_t, SDL_TRUE, BaltieType::colors[m_transpcolor]);
}

Tile::Tile(SDL_Surface * surf, uint8_t tcol) {
    m_transpcolor = tcol;
    m_tilerect.x = 0; m_tilerect.y = 0; m_tilerect.w = 39; m_tilerect.h = 29;
    m_tilesurface = surf;
    m_tilesurface_t = SDL_CreateRGBSurface(0, m_tilerect.w, m_tilerect.h, 32, 0, 0, 0, 0);
    SDL_BlitSurface(m_tilesurface, &m_tilerect, m_tilesurface_t, nullptr);
    if(m_transpcolor != 0xFF) SDL_SetColorKey(m_tilesurface_t, SDL_TRUE, BaltieType::colors[m_transpcolor]);
}

Tile::~Tile() {
    SDL_FreeSurface(m_tilesurface);
    SDL_FreeSurface(m_tilesurface_t);
}

void Tile::draw(SDL_Renderer * renderer, int x, int y, bool transparent) {
    SDL_Rect rect = {x,y,39,29};
    SDL_Texture * tex = nullptr;
    if(transparent) tex = SDL_CreateTextureFromSurface(renderer, m_tilesurface_t);
    else tex = SDL_CreateTextureFromSurface(renderer, m_tilesurface);
    SDL_RenderCopy(renderer, tex, NULL, &rect);
    SDL_DestroyTexture(tex);
}

void Tile::to_bmp(const char * path) {
    SDL_RWops * bmpfile = SDL_RWFromFile(path, "wb");
    SDL_SaveBMP_RW(m_tilesurface, bmpfile, 0);
    bmpfile->close(bmpfile);
}

void Tile::write(SDL_RWops * bankfile) {
    uint8_t blob2[] = {0x26, 0x01, 0x1C};
    bankfile->write(bankfile, blob2, sizeof(blob2), 1);
    bankfile->write(bankfile, &m_transpcolor, sizeof(m_transpcolor), 1);
    uint32_t * pixels = (uint32_t *) m_tilesurface->pixels;

    // TODO fix

    for(int lini = 0; lini<29; lini++) {        // For each tile

        BaltieType::colormask mask[4] = {0};

        uint8_t maski = 4;
        for(int pixi = 0; pixi<39; pixi++) {    // For each pixel in a tile

            uint8_t colorindex = 0;             // Get color index
            for(int i=0;i<16;i++) {
                if(pixels[(lini*39)+pixi] == (BaltieType::colors[i] | 0x000000FF)) break;
                colorindex++;
            }

            for(int j=0;j<4;j++) {
                if((colorindex >> j) & 1) mask[j][maski] |= 1UL << (39-pixi);
            }

            if(pixi == 7) maski = 1;
            if(pixi == 15) maski = 2;
            if(pixi == 23) maski = 3;
            if(pixi == 31) maski = 4;
        }

        for(int j=0;j<4;j++) {
            bankfile->write(bankfile, mask[j], sizeof(BaltieType::colormask), 1);
        }
    }

    // EOTODO

    uint8_t blob3[] = {0xD8, 0xD3};
    bankfile->write(bankfile, blob3, sizeof(blob3), 1);
}
