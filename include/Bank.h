#ifndef BANK_H
#define BANK_H

#include "Tile.h"

/*
     BALTIE BANK
     A Bank stores 150 Tiles
*/

class Bank {
    public:
        Bank();                         // Make empty Bank
        Bank(const char * path);        // Load Bank from file
        virtual ~Bank();
        int to_bmp(const char * path);  // Save Bank as BMP image
        void to_file(const char * path);// Save Bank to a BANK file

        Tile * m_tileset[150];          // All tiles stored here
};

#endif // BANK_H
