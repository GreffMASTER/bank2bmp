#ifndef BALTIETYPES_H_INCLUDED
#define BALTIETYPES_H_INCLUDED

namespace BaltieType {
    const uint32_t colors[16] = {   // Baltie color palette
        0x000000, // 0 black
        0x00AA00, // 1 dark green
        0x0000FF, // 2 blue
        0x0000AA, // 3 dark blue
        0xAA0055, // 4 magenta
        0xAA0000, // 5 red
        0xAAAA55, // 6 dark yellow
        0xAAAAAA, // 7 light gray
        0x505050, // 8 gray
        0x00FF00, // 9 green
        0x00FFFF, // 10 cyan
        0xAA55FF, // 11 purple
        0xFF5555, // 12 light red
        0xFFAA00, // 13 orange
        0xFFFF00, // 14 yellow
        0xFFFFFF  // 15 white
    };

    enum direction {
        EAST = 1,
        SOUTH = 2,
        WEST = 3,
        NORTH = 4
    };

    typedef uint8_t colormask[5];
}

#endif // BALTIETYPES_H_INCLUDED
