#include <iostream>
#include <string>
#include "SDL.h"
#include "Bank.h"

const char* C_VER = "1.0.0";

void prnt_help() {
    printf("BANK2BMP v%s by GreffMASTER, 2023\n", C_VER);
    printf("A tool for extracting image data from Balite/Baltik 2.0/3.0 BANK files.\n");
    printf("Usage: bank2bmp <infile> [params]\n");
    printf("Parameters:\n");
    printf("-o <path>  -  output path\n");
    printf("If output path is not provided, the input file name will be used as output with added .bmp extension\n");
}

int main( int argc, char ** argv ){
    std::string inpath;
    std::string outpath;
    int requiredargs = 2;
    if(argc<2) {
        prnt_help();
        return 0;
    }
    inpath = argv[1];
    outpath = inpath + ".bmp";

    for(int i=2;i<argc;i++) {
        if(strcmp(argv[i], "-o") == 0) {
            requiredargs += 2;
            if(argc<requiredargs) {
                printf("-o parameter requires a path\n");
                prnt_help();
                return 0;
            }
            outpath = argv[i+1];
        }
    }

    // PROGRAM ARGUMENTS CORRECT, PROCEED

    if( SDL_Init( 0 ) != 0 ) {
        printf("Failed to initialize SDL.");
        return 1;
    }

    Bank * in_bank = new Bank(inpath.c_str());
    if(in_bank->to_bmp(outpath.c_str()) != 0) {
        printf("Failed to save the bmp file \"%s\"!\n", outpath.c_str());
        return 1;
    }

    printf("Successfully exported from %s to %s!\n", inpath.c_str(), outpath.c_str());
    delete in_bank;
    SDL_Quit();

    return 0;
}
