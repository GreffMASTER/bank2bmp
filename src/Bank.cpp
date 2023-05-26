#include "Bank.h"

Bank::Bank() {
    // Make empty tileset
    for(int i=0;i<150;i++) m_tileset[i] = new Tile();
}

Bank::Bank(const char * path) {
    SDL_RWops * bankfile = SDL_RWFromFile(path, "rb");
    if(bankfile == NULL) {
        printf("Bank error: %s\nMaking an empty Bank...\n", SDL_GetError());
        // Make empty tileset instead
        for(int i=0;i<150;i++) m_tileset[i] = new Tile();
        return;
    }
    char bankmagic[5] = {0};
    bankfile->read(bankfile, bankmagic, 4, 1);
    if(strcmp(bankmagic, "BANK") != 0) {            // If not a BANK file, create empty bank
        bankfile->close(bankfile);
        for(int i=0;i<150;i++) m_tileset[i] = new Tile();
        return;
    }

    bankfile->seek(bankfile, 0x034, RW_SEEK_SET);   // Skip undiscovered stuff

    for(int itile=0;itile<150;itile++) {            // Load tiles in bank
        m_tileset[itile] = new Tile(bankfile);
    }

    bankfile->close(bankfile);
}

Bank::~Bank() {
    for(int i=0;i<150;i++) delete m_tileset[i]; // Free all 150 tiles
}

int Bank::to_bmp(const char * path) {
    SDL_RWops * bmpfile = SDL_RWFromFile(path, "wb");
    if(bmpfile == NULL) {
        printf("to_bmp error: %s\n", SDL_GetError());
        return 1;
    }
    // Create a surface with all tiles on it
    SDL_Surface * surf = SDL_CreateRGBSurface(0, 585, 290, 32, 0, 0, 0, 0);

    int x = 0, y = 0;
    for(int i=0;i<150;i++) {
        SDL_Rect targetrect;
        targetrect.x = x; targetrect.y = y; targetrect.w = 39; targetrect.h = 29;
        SDL_BlitSurface(m_tileset[i]->m_tilesurface, &m_tileset[i]->m_tilerect, surf, &targetrect);
        x += 39;
        if( x > 546 ) {
            x = 0;
            y += 29;
        }
    }
    // Save as BMP
    SDL_SaveBMP_RW(surf, bmpfile, 0);
    bmpfile->close(bmpfile);
    SDL_FreeSurface(surf);
    return 0;
}

void Bank::to_file(const char * path) {
    SDL_RWops * bankfile = SDL_RWFromFile(path, "wb");


    bankfile->write(bankfile, "BANK", 4, 1);

    uint8_t zero[] = {0x00, 0x00, 0x00, 0x00};
    bankfile->write(bankfile, zero, sizeof(zero), 1);

    uint8_t blob[] = {  0x2A, 0x00, 0x00, 0x00, 0x3F, 0x00, 0x00, 0x2A,
                        0x2A, 0x00, 0x15, 0x2A, 0x00, 0x00, 0x2A, 0x2A,
                        0x15, 0x2A, 0x2A, 0x2A, 0x15, 0x15, 0x15, 0x00,
                        0x3F, 0x00, 0x00, 0x3F, 0x3F, 0x2A, 0x15, 0x3F,
                        0x3F, 0x15, 0x15, 0x3F, 0x2A, 0x00, 0x3F, 0x3F,
                        0x00, 0x3F, 0x3F, 0x3F };

    bankfile->write(bankfile, blob, sizeof(blob), 1);

    for(int i=0;i<150;i++) {    // For each tile
        m_tileset[i]->write(bankfile);
    }

    bankfile->close(bankfile);
}
