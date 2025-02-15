#include <ultra64.h>

Vtx D_800E8700[] = {
    {{{    8,    8,    0}, 0, {960,    0}, {0xFF, 0xFF, 0xFF, 0xFF}}},
    {{{    8,   -8,    0}, 0, {960,  960}, {0xFF, 0xFF, 0xFF, 0xFF}}},
    {{{   -8,   -8,    0}, 0, {0,  960}, {0xFF, 0xFF, 0xFF, 0xFF}}},
    {{{   -8,    8,    0}, 0, {0,    0}, {0xFF, 0xFF, 0xFF, 0xFF}}},
};

Vtx D_800E8740[] = {
    {{{    1,    2,    0}, 0, {0,    0}, {0xFF, 0xFF, 0xFF, 0xFF}}},
    {{{    2,   -2,    0}, 0, {0,  960}, {0xFF, 0xFF, 0xFF, 0xFF}}},
    {{{   -2,   -2,    0}, 0, {960,  960}, {0xFF, 0xFF, 0xFF, 0xFF}}},
    {{{   -1,    2,    0}, 0, {960,    0}, {0xFF, 0xFF, 0xFF, 0xFF}}},
};

Vtx D_800E8780[] = {
    {{{    2,    4,    0}, 0, {4032,    0}, {0xFF, 0xFF, 0xFF, 0xFF}}},
    {{{    2,    0,    0}, 0, {4032, 4032}, {0xFF, 0xFF, 0xFF, 0xFF}}},
    {{{   -2,    0,    0}, 0, {0, 4032}, {0xFF, 0xFF, 0xFF, 0xFF}}},
    {{{   -2,    4,    0}, 0, {0,    0}, {0xFF, 0xFF, 0xFF, 0xFF}}},
};

Vtx D_800E87C0[] = {
    {{{    2,    2,    0}, 0, {1984,    0}, {0x00, 0x00, 0x7F, 0xFF}}},
    {{{    2,   -2,    0}, 0, {1984, 1984}, {0x00, 0x00, 0x7F, 0xFF}}},
    {{{   -2,   -2,    0}, 0, {0, 1984}, {0x00, 0x00, 0x7F, 0xFF}}},
    {{{   -2,    2,    0}, 0, {0,    0}, {0x00, 0x00, 0x7F, 0xFF}}},
};

Vtx D_800E8800[] = {
    {{{    0,    4,    0}, 0, {0,    0}, {0xFF, 0xFF, 0xFF, 0xFF}}},
    {{{    0,    0,    0}, 0, {0, 1984}, {0xFF, 0xFF, 0xFF, 0xFF}}},
    {{{   -4,    0,    0}, 0, {4032, 1984}, {0xFF, 0xFF, 0xFF, 0xFF}}},
    {{{   -4,    4,    0}, 0, {4032,    0}, {0xFF, 0xFF, 0xFF, 0xFF}}},
};

Vtx D_800E8840[] = {
    {{{    4,    4,    0}, 0, {0,    0}, {0xFF, 0xFF, 0xFF, 0xFF}}},
    {{{    4,    0,    0}, 0, {0, 1984}, {0xFF, 0xFF, 0xFF, 0xFF}}},
    {{{    0,    0,    0}, 0, {4032, 1984}, {0xFF, 0xFF, 0xFF, 0xFF}}},
    {{{    0,    4,    0}, 0, {4032,    0}, {0xFF, 0xFF, 0xFF, 0xFF}}},
};

Vtx D_800E8880[] = {
    {{{    2,    2,    0}, 0, {0,    0}, {0xFF, 0xFF, 0xFF, 0xFF}}},
    {{{    2,    0,    0}, 0, {0, 1984}, {0xFF, 0xFF, 0xFF, 0xFF}}},
    {{{   -2,    0,    0}, 0, {4032, 1984}, {0xFF, 0xFF, 0xFF, 0xFF}}},
    {{{   -2,    2,    0}, 0, {4032,    0}, {0xFF, 0xFF, 0xFF, 0xFF}}},
};

Vtx D_800E88C0[] = {
    {{{    2,    0,    0}, 0, {0,    0}, {0xFF, 0xFF, 0xFF, 0xFF}}},
    {{{    2,   -2,    0}, 0, {0, 1984}, {0xFF, 0xFF, 0xFF, 0xFF}}},
    {{{   -2,   -2,    0}, 0, {4032, 1984}, {0xFF, 0xFF, 0xFF, 0xFF}}},
    {{{   -2,    0,    0}, 0, {4032,    0}, {0xFF, 0xFF, 0xFF, 0xFF}}},
};

Vtx D_800E8900[][4] = {
    {
        {{{    2,    4,    0}, 0, {0,    0}, {0x00, 0xFF, 0xFF, 0x70}}},
        {{{    2,    0,    0}, 0, {0, 4032}, {0x00, 0xFF, 0xFF, 0x70}}},
        {{{    0,    0,    0}, 0, {1984, 4032}, {0xFF, 0xFF, 0x00, 0x70}}},
        {{{    0,    4,    0}, 0, {1984,    0}, {0x00, 0xFF, 0xFF, 0x70}}},
    },

    {
        {{{    0,    4,    0}, 0, {0,    0}, {0x00, 0xFF, 0xFF, 0x70}}},
        {{{    0,    0,    0}, 0, {0, 4032}, {0xFF, 0xFF, 0x00, 0x70}}},
        {{{   -2,    0,    0}, 0, {1984, 4032}, {0x00, 0xFF, 0xFF, 0x70}}},
        {{{   -2,    4,    0}, 0, {1984,    0}, {0x00, 0xFF, 0xFF, 0x70}}},
    },

    {
        {{{    2,    4,    0}, 0, {1984,    0}, {0x00, 0xFF, 0xFF, 0x70}}},
        {{{    2,    0,    0}, 0, {1984, 4032}, {0x00, 0xFF, 0xFF, 0x70}}},
        {{{    0,    0,    0}, 0, {0, 4032}, {0xFF, 0xFF, 0x00, 0x70}}},
        {{{    0,    4,    0}, 0, {0,    0}, {0x00, 0xFF, 0xFF, 0x70}}},
    },

    {
        {{{    0,    4,    0}, 0, {1984,    0}, {0x00, 0xFF, 0xFF, 0x70}}},
        {{{    0,    0,    0}, 0, {1984, 4032}, {0xFF, 0xFF, 0x00, 0x70}}},
        {{{   -2,    0,    0}, 0, {0, 4032}, {0x00, 0xFF, 0xFF, 0x70}}},
        {{{   -2,    4,    0}, 0, {0,    0}, {0x00, 0xFF, 0xFF, 0x70}}},
    },
};

Vtx D_800E8A00[] = {
    {{{    2,    4,    0}, 0, {0,    0}, {0xF0, 0x00, 0x00, 0x60}}},
    {{{    2,    0,    0}, 0, {0, 4032}, {0xF0, 0x00, 0x00, 0x60}}},
    {{{    0,    0,    0}, 0, {1984, 4032}, {0xFF, 0xFF, 0x14, 0x60}}},
    {{{    0,    4,    0}, 0, {1984,    0}, {0xF0, 0x00, 0x00, 0x60}}},
};

Vtx D_800E8A40[] = {
    {{{    0,    4,    0}, 0, {0,    0}, {0xF0, 0x00, 0x00, 0x60}}},
    {{{    0,    0,    0}, 0, {0, 4032}, {0xFF, 0xFF, 0x14, 0x60}}},
    {{{   -2,    0,    0}, 0, {1984, 4032}, {0xF0, 0x00, 0x00, 0x60}}},
    {{{   -2,    4,    0}, 0, {1984,    0}, {0xF0, 0x00, 0x00, 0x60}}},
};

Vtx D_800E8A80[] = {
    {{{    2,    4,    0}, 0, {1984,    0}, {0xF0, 0x00, 0x00, 0x60}}},
    {{{    2,    0,    0}, 0, {1984, 4032}, {0xF0, 0x00, 0x00, 0x60}}},
    {{{    0,    0,    0}, 0, {0, 4032}, {0xFF, 0xFF, 0x14, 0x60}}},
    {{{    0,    4,    0}, 0, {0,    0}, {0xF0, 0x00, 0x00, 0x60}}},
};

Vtx D_800E8AC0[] = {
    {{{    0,    4,    0}, 0, {1984,    0}, {0xF0, 0x00, 0x00, 0x60}}},
    {{{    0,    0,    0}, 0, {1984, 4032}, {0xFF, 0xFF, 0x14, 0x60}}},
    {{{   -2,    0,    0}, 0, {0, 4032}, {0xF0, 0x00, 0x00, 0x60}}},
    {{{   -2,    4,    0}, 0, {0,    0}, {0xF0, 0x00, 0x00, 0x60}}},
};

Vtx D_800E8B00[] = {
    {{{    1,   12,    0}, 0, {0,    0}, {0xFF, 0xFF, 0xFF, 0xF0}}},
    {{{    2,    0,    0}, 0, {0, 4032}, {0xFF, 0xFF, 0xFF, 0xF0}}},
    {{{   -2,    0,    0}, 0, {1984, 4032}, {0xFF, 0xFF, 0xFF, 0xF0}}},
    {{{   -1,   12,    0}, 0, {1984,    0}, {0xFF, 0xFF, 0xFF, 0xF0}}},
};

Vtx D_800E8B40[] = {
    {{{    2,    1,    0}, 0, {0,    0}, {0xFF, 0xFF, 0xFF, 0xFF}}},
    {{{    2,   -1,    0}, 0, {0, 1984}, {0xFF, 0xFF, 0xFF, 0xFF}}},
    {{{   -2,   -1,    0}, 0, {4032, 1984}, {0xFF, 0xFF, 0xFF, 0xFF}}},
    {{{   -2,    1,    0}, 0, {4032,    0}, {0xFF, 0xFF, 0xFF, 0xFF}}},
};

Vtx D_800E8B80[] = {
    {{{    4,    1,    0}, 0, {0,    0}, {0xFF, 0xFF, 0xFF, 0xFF}}},
    {{{    4,   -1,    0}, 0, {0, 1984}, {0xFF, 0xFF, 0xFF, 0xFF}}},
    {{{    0,   -1,    0}, 0, {4032, 1984}, {0xFF, 0xFF, 0xFF, 0xFF}}},
    {{{    0,    1,    0}, 0, {4032,    0}, {0xFF, 0xFF, 0xFF, 0xFF}}},
};

Vtx D_800E8BC0[] = {
    {{{    0,    1,    0}, 0, {0,    0}, {0xFF, 0xFF, 0xFF, 0xFF}}},
    {{{    0,   -1,    0}, 0, {0, 1984}, {0xFF, 0xFF, 0xFF, 0xFF}}},
    {{{   -4,   -1,    0}, 0, {4032, 1984}, {0xFF, 0xFF, 0xFF, 0xFF}}},
    {{{   -4,    1,    0}, 0, {4032,    0}, {0xFF, 0xFF, 0xFF, 0xFF}}},
};

Vtx D_800E8C00[] = {
    {{{    2,    4,    0}, 0, {0,    0}, {0xFF, 0xFF, 0xFF, 0xFF}}},
    {{{    2,    0,    0}, 0, {0, 4032}, {0xFF, 0xFF, 0xFF, 0xFF}}},
    {{{   -2,    0,    0}, 0, {1984, 4032}, {0xFF, 0xFF, 0xFF, 0xFF}}},
    {{{   -2,    4,    0}, 0, {1984,    0}, {0xFF, 0xFF, 0xFF, 0xFF}}},
};

Vtx D_800E8C40[] = {
    {{{    9,   18,   -9}, 0, {0,  990}, {0xFF, 0xFF, 0xFF, 0x37}}},
    {{{    9,    0,   -9}, 0, {0,    0}, {0xFF, 0xFF, 0xFF, 0x9B}}},
    {{{   -9,    0,   -9},  0, {990,    0}, {0xFF, 0xFF, 0xFF, 0x9B}}},
    {{{   -9,   18,   -9},  0, {990,  990}, {0xFF, 0xFF, 0xFF, 0x37}}},
    {{{    9,   18,    9}, 0, {0,  990}, {0xFF, 0xFF, 0xFF, 0x37}}},
    {{{    9,    0,    9}, 0, {0,    0}, {0xFF, 0xFF, 0xFF, 0x9B}}},
    {{{   -9,    0,    9},  0, {990,    0}, {0xFF, 0xFF, 0xFF, 0x9B}}},
    {{{   -9,   18,    9},  0, {990,  990}, {0xFF, 0xFF, 0xFF, 0x37}}},
};

Vtx D_800E8CC0[] = {
    {{{    9,   70,   -9}, 0, {0,  990}, {0xFF, 0xFF, 0xFF, 0x37}}},
    {{{    9,    0,   -9}, 0, {0,    0}, {0xFF, 0xFF, 0xFF, 0x9B}}},
    {{{   -9,    0,   -9},  0, {990,    0}, {0xFF, 0xFF, 0xFF, 0x9B}}},
    {{{   -9,   70,   -9},  0, {990,  990}, {0xFF, 0xFF, 0xFF, 0x37}}},
    {{{    9,   70,    9}, 0, {0,  990}, {0xFF, 0xFF, 0xFF, 0x37}}},
    {{{    9,    0,    9}, 0, {0,    0}, {0xFF, 0xFF, 0xFF, 0x9B}}},
    {{{   -9,    0,    9},  0, {990,    0}, {0xFF, 0xFF, 0xFF, 0x9B}}},
    {{{   -9,   70,    9},  0, {990,  990}, {0xFF, 0xFF, 0xFF, 0x37}}},
};

Gfx D_800E8D40[] = {
    gsSPClearGeometryMode(G_LIGHTING),
    gsDPSetAlphaCompare(G_AC_NONE),
    gsDPSetRenderMode(G_RM_AA_ZB_XLU_SURF, G_RM_AA_ZB_XLU_SURF2),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPVertex(D_800E8C40, 8, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsSP1Triangle(0, 2, 3, 0),
    gsSP1Triangle(4, 7, 6, 0),
    gsSP1Triangle(4, 6, 5, 0),
    gsSP1Triangle(0, 4, 5, 0),
    gsSP1Triangle(0, 5, 1, 0),
    gsSP1Triangle(3, 7, 4, 0),
    gsSP1Triangle(0, 3, 4, 0),
    gsSP1Triangle(7, 3, 6, 0),
    gsSP1Triangle(3, 2, 6, 0),
    gsSP1Triangle(1, 5, 6, 0),
    gsSP1Triangle(2, 1, 6, 0),
    gsSPEndDisplayList(),
};

Gfx D_800E8DD0[] = {
    gsSPClearGeometryMode(G_LIGHTING),
    gsDPSetAlphaCompare(G_AC_NONE),
    gsDPSetRenderMode(G_RM_AA_ZB_XLU_SURF, G_RM_AA_ZB_XLU_SURF2),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPVertex(D_800E8CC0, 8, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsSP1Triangle(0, 2, 3, 0),
    gsSP1Triangle(4, 7, 6, 0),
    gsSP1Triangle(4, 6, 5, 0),
    gsSP1Triangle(0, 4, 5, 0),
    gsSP1Triangle(0, 5, 1, 0),
    gsSP1Triangle(3, 7, 4, 0),
    gsSP1Triangle(0, 3, 4, 0),
    gsSP1Triangle(7, 3, 6, 0),
    gsSP1Triangle(3, 2, 6, 0),
    gsSP1Triangle(1, 5, 6, 0),
    gsSP1Triangle(2, 1, 6, 0),
    gsSPEndDisplayList(),
};
