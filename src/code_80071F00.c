#include <ultra64.h>
#include <macros.h>
#include <defines.h>
#include <functions.h>

#include "code_80071F00.h"
#include "main.h"
#include "memory.h"
#include "camera.h"
#include "math_util.h"
#include "math_util_2.h"
#include "hud_renderer.h"
#include "objects.h"
#include "waypoints.h"
#include "variables.h"
#include "code_80005FD0.h"
#include "code_80057C60.h"
#include "code_80086E70.h"
#include "common_textures.h"
#include "audio/external.h"
#include "sounds.h"
#include <actors.h>
#include "race_logic.h"
#include "collision.h"
#include "code_8008C1D0.h"
#include "code_80091440.h"
#include "code_80091750.h"
#include "podium_ceremony_actors.h"
#include "courses/all_course_data.h"
#include "menus.h"

// TODO: unused?
f32 D_800E43B0[] = { 
    65536.0, 0.0,     1.0, 0.0,
    0.0,     65536.0, 0.0, 1.0,
    0.0,     0.0,     0.0, 0.0,
    0.0,     0.0,     0.0, 0.0
};

Vtx D_800E43F0[] = {
    {{{  -24,  -19,    0}, 0, {    0,    0}, { 0xFF, 0xFF, 0xFF, 0xFF}}},
    {{{   23,  -19,    0}, 0, { 3008,    0}, { 0xFF, 0xFF, 0xFF, 0xFF}}},
    {{{   23,   20,    0}, 0, { 3008, 2496}, { 0xFF, 0xFF, 0xFF, 0xFF}}},
    {{{  -24,   20,    0}, 0, {    0, 2496}, { 0xFF, 0xFF, 0xFF, 0xFF}}},
    {{{  -24,  -19,    0}, 0, { 3008,    0}, { 0xFF, 0xFF, 0xFF, 0xFF}}},
    {{{   23,  -19,    0}, 0, {    0,    0}, { 0xFF, 0xFF, 0xFF, 0xFF}}},
    {{{   23,   20,    0}, 0, {    0, 2496}, { 0xFF, 0xFF, 0xFF, 0xFF}}},
    {{{  -24,   20,    0}, 0, { 3008, 2496}, { 0xFF, 0xFF, 0xFF, 0xFF}}},
};

Vtx D_800E4470[] = {
    {{{  -24,  -19,    0}, 0, {    0,    0}, { 0xFF, 0xFF, 0xFF, 0xFF}}},
    {{{   23,  -19,    0}, 0, { 3008,    0}, { 0xFF, 0xFF, 0xFF, 0xFF}}},
    {{{   23,   20,    0}, 0, { 3008, 2496}, { 0xFF, 0xFF, 0xFF, 0xFF}}},
    {{{  -24,   20,    0}, 0, {    0, 2496}, { 0xFF, 0xFF, 0xFF, 0xFF}}},
};

Vtx D_800E44B0[] = {
    {{{  -24,  -19,    0}, 0, { 3008,    0}, { 0xFF, 0xFF, 0xFF, 0xFF}}},
    {{{   23,  -19,    0}, 0, {    0,    0}, { 0xFF, 0xFF, 0xFF, 0xFF}}},
    {{{   23,   20,    0}, 0, {    0, 2496}, { 0xFF, 0xFF, 0xFF, 0xFF}}},
    {{{  -24,   20,    0}, 0, { 3008, 2496}, { 0xFF, 0xFF, 0xFF, 0xFF}}},
};

u8 *gItemWindowTLUTs[] = {
    gTLUTItemWindowNone, gTLUTItemWindowBanana, gTLUTItemWindowBananaBunch, gTLUTItemWindowGreenShell,
    gTLUTItemWindowTripleGreenShell, gTLUTItemWindowRedShell, gTLUTItemWindowTripleRedShell, gTLUTItemWindowBlueShell,
    gTLUTItemWindowThunderBolt, gTLUTItemWindowFakeItemBox, gTLUTItemWindowStar, gTLUTItemWindowBoo,
    gTLUTItemWindowMushroom, gTLUTItemWindowDoubleMushroom, gTLUTItemWindowTripleMushroom, gTLUTItemWindowSuperMushroom
};

u8 *gItemWindowTextures[] = {
    gTextureItemWindowNone, gTextureItemWindowBanana, gTextureItemWindowBananaBunch, gTextureItemWindowGreenShell,
    gTextureItemWindowTripleGreenShell, gTextureItemWindowRedShell, gTextureItemWindowTripleRedShell, gTextureItemWindowBlueShell,
    gTextureItemWindowThunderBolt, gTextureItemWindowFakeItemBox, gTextureItemWindowStar, gTextureItemWindowBoo,
    gTextureItemWindowMushroom, gTextureItemWindowDoubleMushroom, gTextureItemWindowTripleMushroom, gTextureItemWindowSuperMushroom
};

u8 *D_800E4570[] = {
    D_0D00B158, D_0D00B558, D_0D00B958
};

u8 *gPortraitTLUTs[] = {
    gTLUTPortraitMario, gTLUTPortraitLuigi, gTLUTPortraitYoshi, gTLUTPortraitToad,
    gTLUTPortraitDonkeyKong, gTLUTPortraitWario, gTLUTPortraitPeach, gTLUTPortraitBowser
};

u8 *gPortraitTextures[] = {
    gTexturePortraitMario, gTexturePortraitLuigi, gTexturePortraitYoshi, gTexturePortraitToad,
    gTexturePortraitDonkeyKong, gTexturePortraitWario, gTexturePortraitPeach, gTexturePortraitBowser
};

s32 find_unused_obj_index(s32* arg0) {
    s32 temp_v0;
    s32 temp_v1;

    temp_v1 = D_80183D5C;
    temp_v0 = 0; do
    {
        ++temp_v1;
        ++temp_v0;

        if (temp_v1 == 0x226) {
            temp_v1 = 0;
        }

    } while ((D_80165C18[temp_v1].unk_0CA != 0) && (temp_v0 != 0x226));

    D_80165C18[temp_v1].unk_0CA = 1;

    *arg0 = temp_v1;
    D_80183D5C = temp_v1;
    return temp_v1;
}

// Not actually sure about the pointer type, but its definitely SOME type of pointer
void func_80071F6C(s32 *arg0) {
    func_80072428(*arg0);
    D_80165C18[*arg0].unk_0CA = 0;
    *arg0 = -1;
}

s32 func_80071FBC(void) {
    s32 objectIndex;
    s32 someCount = 0;
    for (objectIndex = 0; objectIndex < OBJECT_LIST_SIZE; objectIndex++) {
        if (D_80165C18[objectIndex].unk_0CA != 0) {
            someCount++;
        }
    }
    return someCount;
}

s32 func_80072044(s32 *arg0, s32 *arg1, s32 arg2) {
    s32 var_v1;
    s32 temp_v0;
    s32 *var_a0_2;

    if (*arg1 >= arg2) {
        *arg1 = 0;
    }
    var_v1 = 0;
    var_a0_2 = &arg0[*arg1];
    /*
     * This HAS to be a for-loop of some variety, but I can't make a for-loop to match.
     * If you replace this with ```for(var_v1 = 0; var_v1 < arg2; var_v1++)```
     * The diff gets massive.
    */
    if (arg2 > 0) {
loop_3:
        if (*var_a0_2 == -1) {
            temp_v0 = find_unused_obj_index(var_a0_2);
            *arg1 += 1;
        } else {
            *arg1 += 1;
            if (*arg1 >= arg2) {
                *arg1 = 0;
            }
            var_v1 += 1;
            var_a0_2 = &arg0[*arg1];
            if (var_v1 != arg2) {
                goto loop_3;
            }
        }
    }
    if (var_v1 == arg2) {
        temp_v0 = -1;
    }
    return temp_v0;
}

void func_80072100(s32 *arg0) {
    func_80071F6C(arg0);
}

void func_80072120(s32 *arg0, s32 arg1) {
    s32 i;

    for (i = 0; i < arg1; i++) {
            func_800721E8(*arg0, 0x00600000);
            arg0++;
    }
}

void func_80072180(void) {
    if (gModeSelection == TIME_TRIALS) {
        if (((gPlayerOne->unk_000 & PLAYER_EXISTS) != 0) &&
        ((gPlayerOne->unk_000 & (PLAYER_INVISIBLE_OR_BOMB | PLAYER_CPU)) == 0)) {
            D_80162DF8 = 1;
        }
    }
}

void func_800721C0(s32 arg0, s32 arg1) {
    D_80165C18[arg0].unk_054 |= arg1;
}

void func_800721E8(s32 arg0, s32 arg1) {
    D_80165C18[arg0].unk_054 &= ~arg1;
}

UNUSED void func_80072214(s32 arg0, s32 arg1) {
    D_80165C18[arg0].unk_054 ^= arg1;
}

s32 func_8007223C(s32 arg0, s32 arg1) {
    s32 phi_v1 = 0;
    if ((D_80165C18[arg0].unk_054 & arg1) != 0) {
        phi_v1 = 1;
    }
    return phi_v1;
}

s32 func_80072270(s32 arg0, s32 arg1) {
    s32 phi_v1 = 0;
    if ((D_80165C18[arg0].unk_054 & arg1) == 0) {
        phi_v1 = 1;
    }
    return phi_v1;
}

void func_800722A4(s32 arg0, s32 arg1) {
    D_80165C18[arg0].unk_058 |= arg1;
}

void func_800722CC(s32 arg0, s32 arg1) {
    D_80165C18[arg0].unk_058 &= ~arg1;
}

UNUSED void func_800722F8(s32 arg0, s32 arg1) {
    D_80165C18[arg0].unk_058 ^= arg1;
}

s32 func_80072320(s32 arg0, s32 arg1) {
    s32 phi_v1 = 0;
    if ((D_80165C18[arg0].unk_058 & arg1) != 0) {
        phi_v1 = 1;
    }
    return phi_v1;
}

s32 func_80072354(s32 arg0, s32 arg1) {
    s32 phi_v1 = 0;
    if ((D_80165C18[arg0].unk_058 & arg1) == 0) {
        phi_v1 = 1;
    }
    return phi_v1;
}

void func_80072388(s32 arg0, s32 arg1) {
    D_80165C18[arg0].unk_0CB = arg1;
}

void func_800723A4(s32 arg0, s32 arg1) {
    D_80165C18[arg0].unk_054 = 0;
    D_80165C18[arg0].unk_058 = 0;
    D_80165C18[arg0].unk_05C = 0;
    D_80165C18[arg0].unk_0CD = 0;
    D_80165C18[arg0].unk_0CF = 0;
    func_80072388(arg0, 0);
    D_80165C18[arg0].unk_0D8 = arg1;
    D_80165C18[arg0].unk_0A6 = 1;
}

UNUSED void func_80072408(s32 arg0) {
    func_80072388(arg0, 0);
}

void func_80072428(s32 arg0) {
    D_80165C18[arg0].unk_0A6 = 0;
    D_80165C18[arg0].unk_0D8 = 0;
    func_80072388(arg0, 0);
    D_80165C18[arg0].unk_054 = 0;
    D_80165C18[arg0].unk_058 = 0;
    D_80165C18[arg0].unk_05C = 0;
    func_80086F60(arg0);
}

void func_80072488(s32 arg0) {
    func_80072388(arg0,  0);
    func_800721E8(arg0, 0x2000);
    D_80165C18[arg0].unk_0A6++;
}

void func_800724DC(s32 arg0) {
    D_80165C18[arg0].unk_0D7 = 0;
}

void func_800724F8(s32 arg0, s32 arg1) {
    D_80165C18[arg0].unk_084[D_80165C18[arg0].unk_0D7] = arg1;
    D_80165C18[arg0].unk_0D7++;
}

s16 func_80072530(s32 arg0) {
    D_80165C18[arg0].unk_0D7--;
    return D_80165C18[arg0].unk_084[D_80165C18[arg0].unk_0D7];
}

void func_80072568(s32 arg0, s32 arg1) {
    func_80072388(arg0, 0);
    func_800721E8(arg0, 0x2000);
    func_800721E8(arg0, 8);
    func_80072488(arg0);
    func_800724F8(arg0, D_80165C18[arg0].unk_0A6);
    D_80165C18[arg0].unk_0A6 = arg1;
}

void func_800725E8(s32 arg0, s32 arg1, s32 arg2) {
    func_80072388(arg0, 0);
    func_800721E8(arg0, 0x2000);
    func_800721E8(arg0, 8);
    D_80165C18[arg0].unk_0A6 = arg2;
    func_800724F8(arg0, D_80165C18[arg0].unk_0A6);
    D_80165C18[arg0].unk_0A6 =  arg1;
}

s16 func_80072530(s32); // extern

void func_8007266C(s32 arg0) {
    func_80072388(arg0, 0);
    func_800721E8(arg0, 0x2000);
    func_800721E8(arg0, 8);
    D_80165C18[arg0].unk_0A6 = func_80072530(arg0);
}

void func_800726CC(s32 arg0, s32 arg1) {
    func_80072388(arg0, 0);
    func_800721E8(arg0, 0x2000);
    D_80165C18[arg0].unk_0A6 = arg1;
}

UNUSED void func_8007271C(s32 arg0, s32 arg1) {
    if (D_80165C18[arg0].unk_0CB == 0) {
        D_80165C18[arg0].unk_0A6 = arg1;
    }
}

UNUSED void func_8007274C(s32 arg0) {
    if (D_80165C18[arg0].unk_0CB == 0) {
        func_80072488(arg0);
    }
}

s32 func_8007278C(s32 arg0, s32 arg1) {
    s32 phi_v1;

    phi_v1 = 0;
    if (D_80165C18[arg0].unk_0CB == 0) {
        func_80072388(arg0, 1);
        D_80165C18[arg0].unk_050 = arg1;
    }

    D_80165C18[arg0].unk_050--;
    if (D_80165C18[arg0].unk_050 < 0) {
        func_80072388(arg0, 0);
        func_80072488(arg0);
        phi_v1 = 1;
    }
    
    return phi_v1;
}

UNUSED s32 func_8007281C(s32 arg0, s32 arg1) {
    s32 phi_a2;

    phi_a2 = 0;
    if (D_80165C18[arg0].unk_0CB == 0) {
        func_80072388(arg0, 1);
        D_80165C18[arg0].unk_050 = random_int((u16) arg1);
    }

    D_80165C18[arg0].unk_050--;
    if (D_80165C18[arg0].unk_050 < 0) {
        func_80072388(arg0, 0);
        func_80072488(arg0);
        phi_a2 = 1;
    }
    
    return phi_a2;
}

UNUSED s32 func_800728B0(s32 arg0, s32 arg1, s32 arg2) {
    s32 phi_a3;

    phi_a3 = 0;
    if (D_80165C18[arg0].unk_0CB == 0) {
        func_80072388(arg0, 1);
        D_80165C18[arg0].unk_050 = random_int((u16) arg2) + arg1;
    }

    D_80165C18[arg0].unk_050--;
    if (D_80165C18[arg0].unk_050 < 0) {
        func_80072388(arg0, 0);
        func_80072488(arg0);
        phi_a3 = 1;
    }
    
    return phi_a3;
}

void func_80072950(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    if (arg1 == arg2) {
        D_80165C18[arg0].unk_0A6 = arg3;
    }
}

UNUSED void func_80072974(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    if (arg1 != arg2) {
        D_80165C18[arg0].unk_0A6 = arg3;
    }
}

UNUSED void func_80072998(s32 arg0) {
        D_80165C18[arg0].unk_0CC = 0;
}

void func_800729B4(s32 arg0, s32 arg1) {
    D_80165C18[arg0].unk_0A2 = arg1;
}

void func_800729D0(s32 arg0, s32 arg1) {
    D_80165C18[arg0].unk_0A4 = arg1;
}

void func_800729EC(s32 arg0) {
    u32 temp_v1 = 1; 
    s32 i;

    start_race();
    func_80072488(arg0);
    D_8018D2BC = 1;
    D_8018D2A4 = 1;

    if (gCurrentCourseId != 4) {
        for (i = 0; i < D_8018EDF3; i++) {
                D_8018CA70[i].unk_81 = temp_v1;
        }
    }
    func_8005AB20();
}

UNUSED void func_80072A78(s32 arg0, s32 arg1) {
    D_80165C18[arg0].unk_0D2 = arg1;
    func_80072488(arg0);
}

s32 func_80072AAC(s32 arg0, s32 arg1, s32 arg2) {
    s32 phi_v1;

    phi_v1 = 0;
    if (D_80165C18[arg0].unk_0CB == 0) {

        func_80072388(arg0, 1);
        D_80165C18[arg0].unk_0D2 = arg1;
        D_80165C18[arg0].unk_050 = arg2;
    }

    D_80165C18[arg0].unk_050--;
    if (D_80165C18[arg0].unk_050 < 0) {
        func_80072388(arg0, 0);
        func_80072488(arg0);
        phi_v1 = 1;
    }

    return phi_v1;
}

s32 func_80072B48(s32 arg0, s32 arg1) {
    s32 phi_v1;

    phi_v1 = 0;
    if (D_80165C18[arg0].unk_0CB == 0) {
        func_80072388(arg0, 1);
        func_800721C0(arg0, 0x80000);
        D_80165C18[arg0].unk_0D2 = D_8018D140;
        D_80165C18[arg0].unk_050 = arg1;
    }

    D_80165C18[arg0].unk_050--;
    if (D_80165C18[arg0].unk_050 < 0) {
        func_800721E8(arg0, 0x80000);
        func_80072388(arg0, 0);
        func_80072488(arg0);
        phi_v1 = 1;
    }

    return phi_v1;
}

void func_80072C00(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    if (func_80072270(arg0, 0x2000) != 0) {
        D_80165C18[arg0].unk_050 = arg2;
        D_80165C18[arg0].unk_0D2 = arg1;
        D_80165C18[arg0].unk_0D4 = 1;
        D_80165C18[arg0].unk_0CC = arg3;
        func_800721C0(arg0, 0x2000);
    } else {
        D_80165C18[arg0].unk_050--;
        if (D_80165C18[arg0].unk_050 < 0) {
            D_80165C18[arg0].unk_050 = arg2;
            D_80165C18[arg0].unk_0D4--;
            if ((D_80165C18[arg0].unk_0D4 & 1) != 0) {
                func_800721E8(arg0, 0x80000);
            } else {
                func_800721C0(arg0, 0x80000);
            }

            if (D_80165C18[arg0].unk_0D4 < 0) {
                D_80165C18[arg0].unk_0D4 = 1;

                if (D_80165C18[arg0].unk_0CC > 0) {
                    D_80165C18[arg0].unk_0CC--;
                }

                if (D_80165C18[arg0].unk_0CC == 0) {
                    func_800721E8(arg0, 0x2000);
                    func_80072488(arg0);
                }
            }
        }
    }
}

void func_80072D3C(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    if (func_80072270(arg0, 0x2000) != 0) {
        D_80165C18[arg0].unk_050 = arg3;
        D_80165C18[arg0].unk_0D2 = arg1;
        D_80165C18[arg0].unk_0D4 = 1;
        D_80165C18[arg0].unk_0CC = arg4;
        func_800721C0(arg0, 0x2000);
        return;
    }

    D_80165C18[arg0].unk_050--;
    if (D_80165C18[arg0].unk_050 < 0) {
        D_80165C18[arg0].unk_050 = arg3;
        D_80165C18[arg0].unk_0D4--;
        if ((D_80165C18[arg0].unk_0D4 & 1) != 0) {
            D_80165C18[arg0].unk_0D2 = arg1;
        } else {
            D_80165C18[arg0].unk_0D2 = arg2;
        }
        
        if (D_80165C18[arg0].unk_0D4 < 0) {
            D_80165C18[arg0].unk_0D4 = 1;
            if (D_80165C18[arg0].unk_0CC > 0) {
                D_80165C18[arg0].unk_0CC--;
            }

            if (D_80165C18[arg0].unk_0CC == 0) {
                func_800721E8(arg0, 0x2000);
                func_80072488(arg0);
            }
        }
    }
}

s32 func_80072E54(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    s32 sp24;

    sp24 = 0;
    if (func_80072270(arg0, 0x2000) != 0) {
        D_80165C18[arg0].unk_0D2 = arg1;
        D_80165C18[arg0].unk_050 = arg4;
        D_80165C18[arg0].unk_0CC = arg5;
        func_80072388(arg0, 1);
        func_800721C0(arg0, 0x2000);
    } else {
        D_80165C18[arg0].unk_050--;
        if (D_80165C18[arg0].unk_050 <= 0) {
            D_80165C18[arg0].unk_050 = arg4;
            D_80165C18[arg0].unk_0D2 += arg3;
            if (arg2 < D_80165C18[arg0].unk_0D2) {

                if (D_80165C18[arg0].unk_0CC > 0) {
                    D_80165C18[arg0].unk_0CC--;
                }
                if (D_80165C18[arg0].unk_0CC == 0) {
                    D_80165C18[arg0].unk_0D2 = arg2;
                    func_800721E8(arg0, 0x2000);
                    func_80072388(arg0, 0);
                    func_80072488(arg0);
                    sp24 = 1;
                } else {
                    D_80165C18[arg0].unk_0D2 = arg1;
                }
            }
        }
    }
    return sp24;
}

s32 func_80072F88(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    s32 sp24;

    sp24 = 0;
    if (func_80072270(arg0, 0x2000) != 0) {
        D_80165C18[arg0].unk_0D2 = arg1;
        D_80165C18[arg0].unk_050 = arg4;
        D_80165C18[arg0].unk_0CC = arg5;
        func_80072388(arg0, 1);
        func_800721C0(arg0, 0x2000);
    } else {
        D_80165C18[arg0].unk_050--;
        if (D_80165C18[arg0].unk_050 <= 0) {
            D_80165C18[arg0].unk_050 = arg4;
            D_80165C18[arg0].unk_0D2 -= arg3;
            if (D_80165C18[arg0].unk_0D2 < arg2) {
                if (D_80165C18[arg0].unk_0CC > 0) {
                    D_80165C18[arg0].unk_0CC--;
                }
                if (D_80165C18[arg0].unk_0CC == 0) {
                    D_80165C18[arg0].unk_0D2 = arg2;
                    func_800721E8(arg0, 0x2000);
                    func_80072388(arg0, 0);
                    func_80072488(arg0);
                    sp24 = 1;
                } else {
                    D_80165C18[arg0].unk_0D2 = arg1;
                }
            }
        }
    }
    return sp24;
}

s32 func_800730BC(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    s32 sp24;

    sp24 = 0;
    if (func_80072270(arg0 ,0x2000) != 0) {
        D_80165C18[arg0].unk_0D2 = arg1;
        D_80165C18[arg0].unk_050 = arg4;
        D_80165C18[arg0].unk_0CC = arg5;
        func_80072388(arg0, 1);
        func_800721C0(arg0, 0x2000);
        func_800721E8(arg0, 0x4000);
    } else {
        D_80165C18[arg0].unk_050--;
        if (D_80165C18[arg0].unk_050 <= 0) {
            D_80165C18[arg0].unk_050 = arg4;
            if (func_80072270(arg0, 0x4000) != 0) {
                D_80165C18[arg0].unk_0D2 += arg3;
                if (D_80165C18[arg0].unk_0D2 >= arg2) {
                    D_80165C18[arg0].unk_0D2 = arg2;
                    func_800721C0(arg0, 0x4000);
                }
            } else {
                D_80165C18[arg0].unk_0D2 -= arg3;
                if (arg1 >= D_80165C18[arg0].unk_0D2) {
                    D_80165C18[arg0].unk_0D2 = arg1;
                    if (D_80165C18[arg0].unk_0CC > 0) {
                        D_80165C18[arg0].unk_0CC--;
                    }

                    if (D_80165C18[arg0].unk_0CC == 0) {
                        func_800721E8(arg0, 0x80);
                        func_800721E8(arg0, 0x2000);
                        func_80072388(arg0, 0);
                        func_80072488(arg0);
                        sp24 = 1;
                    } else {
                        func_800721E8(arg0, 0x4000);
                        func_800721C0(arg0, 0x80);
                    }
                }
            }
        }
    }
    return sp24;
}

s32 func_8007326C(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    s32 sp24;

    sp24 = 0;
    if (func_80072270(arg0, 0x2000) != 0) {
        D_80165C18[arg0].unk_0D2 = arg1;
        D_80165C18[arg0].unk_050 = arg4;
        D_80165C18[arg0].unk_0CC = arg5;
        func_80072388(arg0, 1);
        func_800721C0(arg0, 0x2000);
        func_800721E8(arg0, 0x4000);
    } else {
        D_80165C18[arg0].unk_050--;
        if (D_80165C18[arg0].unk_050 <= 0) {
            D_80165C18[arg0].unk_050 = arg4;
            if (func_80072270(arg0, 0x4000) != 0) {
                D_80165C18[arg0].unk_0D2 -= arg3;
                if (arg2 >= D_80165C18[arg0].unk_0D2) {
                    D_80165C18[arg0].unk_0D2 = arg2;
                    func_800721C0(arg0, 0x4000);
                }
            } else {
                D_80165C18[arg0].unk_0D2 += arg3;
                if (D_80165C18[arg0].unk_0D2 >= arg1) {
                    D_80165C18[arg0].unk_0D2 = arg1;
                    if (D_80165C18[arg0].unk_0CC > 0) {
                        D_80165C18[arg0].unk_0CC--;
                    }
                    if (D_80165C18[arg0].unk_0CC == 0) {
                        func_800721E8(arg0, 0x2000);
                        func_80072388(arg0, 0);
                        func_80072488(arg0);
                        sp24 = 1;
                    } else {
                        func_800721E8(arg0, 0x4000);
                    }
                }
            }
        }
    }
    return sp24;
}

void func_80073404(s32 arg0, u8 arg1, u8 arg2, Vtx *arg3) {
  D_80165C18[arg0].unk_074 = arg3;
  D_80165C18[arg0].textureWidth = arg1;
  D_80165C18[arg0].textureHeight = arg2;
  D_80165C18[arg0].unk_0D2 = 0;
  D_80165C18[arg0].unk_0D3 = -1;
  D_80165C18[arg0].unk_054 = 0;
}

void func_80073444(s32 arg0, u8 *texture, u8* arg2, u8 arg3, u16 arg4) {
    D_80165C18[arg0].tlutList = texture;
    D_80165C18[arg0].textureList = arg2;
    D_80165C18[arg0].textureWidth = arg3;
    D_80165C18[arg0].textureHeight = arg4;
    D_80165C18[arg0].unk_0D2 = 0;
    D_80165C18[arg0].unk_0D3 = -1;
    D_80165C18[arg0].unk_054 = 0;
}

UNUSED void func_8007348C(s32 arg0, u8 *arg1, u8 arg2, u8 arg3, Vtx *arg4) {
    D_80165C18[arg0].activeTLUT = arg1;
    D_80165C18[arg0].tlutList = arg1;
    D_80165C18[arg0].textureWidth = arg2;
    D_80165C18[arg0].textureHeight = arg3;
    D_80165C18[arg0].unk_074 = arg4;
    D_80165C18[arg0].unk_0D2 = 0;
    D_80165C18[arg0].unk_0D3 = -1;
    D_80165C18[arg0].unk_054 = 0;
}

UNUSED void func_800734D4() {
}

void func_800734DC(s32 arg0) {
    // I have no idea why this typecast works
    D_80165C18[arg0].activeTLUT = (u32*)D_80165C18[arg0].tlutList + (D_80165C18[arg0].unk_0D2 << 7);
    D_80165C18[arg0].activeTexture = D_80165C18[arg0].textureList;
}

void func_80073514(s32 arg0) {
    D_80165C18[arg0].activeTLUT = D_80165C18[arg0].tlutList;
    D_80165C18[arg0].activeTexture = D_80165C18[arg0].textureList + (D_80165C18[arg0].textureWidth * D_80165C18[arg0].textureHeight * D_80165C18[arg0].unk_0D2);
}

UNUSED void func_80073568() {
}

UNUSED void func_80073570(s32 objectIndex) {
    s16 *test = &D_80165C18[objectIndex].unk_0A6;

    D_8018D1EC++;
    if (D_8018D1EC == 5) {
        D_8018D1EC = 0;
    }
    (*test)++;
} 

void func_800735BC(s32 arg0, Gfx *arg1, f32 arg2) {
    D_80165C18[arg0].unk_054 = 0;
    D_80165C18[arg0].unk_070 = arg1;
    D_80165C18[arg0].sizeScaling = arg2;
    func_80072488(arg0);
}

void func_80073600(s32 arg0) {
    func_80072388(arg0, 0);
    D_80165C18[arg0].unk_0D6 = 0;
    D_80165C18[arg0].unk_04C = -1;
    func_800721E8(arg0, 0x8000);
}

void func_80073654(s32 arg0) {
    func_800721E8(arg0, 0x8000);
    ++D_80165C18[arg0].unk_0D6;
}

UNUSED void func_8007369C(s32 arg0, s32 arg1) {
    func_800721E8(arg0, 0x8000);
    D_80165C18[arg0].unk_0D6 = arg1;
}

void func_800736E0(s32 arg0) {
    func_800721E8(arg0, 0x8000);
    D_80165C18[arg0].unk_0D6 = 1;
}

void func_80073720(s32 arg0) {
    func_800721E8(arg0, 0x8000);
    D_80165C18[arg0].unk_0D6 = 0;
}

s32 func_8007375C(s32 objectIndex, s32 arg1) {
    s32 sp24;

    sp24 = 0;
    if (func_80072270(objectIndex, 0x00008000) != 0) {
        D_80165C18[objectIndex].unk_04C = arg1;
        func_800721C0(objectIndex, 0x00008000);
    }
    D_80165C18[objectIndex].unk_04C--;
    if (D_80165C18[objectIndex].unk_04C < 0) {
        func_800721E8(objectIndex, 0x00008000);
        func_80073654(objectIndex);
        sp24 = 1;
    }
    return sp24;
}

void func_80073800(s32 arg0, s32 arg1) {
    D_80165C18[arg0].unk_0CF = arg1;
}

void func_8007381C(s32 arg0) {
    D_80165C18[arg0].unk_0DC++;
}

void func_80073844(s32 arg0) {
    func_80073800(arg0, 0);
    D_80165C18[arg0].unk_0DC = 1;
}

void func_80073884(s32 arg0) {
    D_80165C18[arg0].unk_0DC = 0;
    D_80165C18[arg0].unk_0CF = 0;
}

s32 func_800738A8(s32 arg0, s16* arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6) {
    s32 phi_t0;

    phi_t0 = 0;
    if (D_80165C18[arg0].unk_0CF == 0) {
        *arg1 = arg2;
        D_80165C18[arg0].unk_0AC = arg5;
        D_80165C18[arg0].unk_0D0 = arg6;
        func_80073800(arg0, 1);
    } else {
        D_80165C18[arg0].unk_0AC--;
        if (D_80165C18[arg0].unk_0AC < 0) {
            D_80165C18[arg0].unk_0AC = arg5;
            *arg1 += arg4;
            if (arg3 < *arg1) {
                if (D_80165C18[arg0].unk_0D0 > 0) {
                    D_80165C18[arg0].unk_0D0--;
                }

                if (D_80165C18[arg0].unk_0D0 == 0) {
                    *arg1 = arg3;
                    func_80073800(arg0, 0);
                    func_8007381C(arg0);
                    phi_t0 = 1;
                } else {
                    *arg1 = arg2;
                }
            }
        }
    }

    return phi_t0;
}

void func_80073998(s32 arg0, s16* arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6) {
    func_800738A8(arg0, arg1, arg2, arg3, arg4, arg5, arg6);
}

UNUSED void func_800739CC(s32 arg0, s16* arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6) {
    if (*arg1 < arg3) {
        func_800738A8(arg0, arg1, arg2, arg3, arg4, arg5, arg6);
    }
}

s32 func_80073A10(s32 arg0, s16* arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6) {
    s32 phi_t0;

    phi_t0 = 0;
    if (D_80165C18[arg0].unk_0CF == 0) {
        *arg1 = arg2;
        D_80165C18[arg0].unk_0AC = arg5;
        D_80165C18[arg0].unk_0D0 = arg6;
        func_80073800(arg0, 1);
    } else {
        D_80165C18[arg0].unk_0AC--;
        if (D_80165C18[arg0].unk_0AC < 0) {
            D_80165C18[arg0].unk_0AC = arg5;
            *arg1 -= arg4;
            if (*arg1 < arg3) {
                if (D_80165C18[arg0].unk_0D0 > 0) {
                    D_80165C18[arg0].unk_0D0--;
                }

                if (D_80165C18[arg0].unk_0D0 == 0) {
                    *arg1 = arg3;
                    func_80073800(arg0, 0);
                    func_8007381C(arg0);
                    phi_t0 = 1;
                } else {
                    *arg1 = arg2;
                }
            }
        }
    }

    return phi_t0;
}

s32 func_80073B00(s32 arg0, s16* arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6) {
    return func_80073A10(arg0, arg1, arg2, arg3, arg4, arg5, arg6);
}

s32 func_80073B34(s32 arg0, s16* arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6) {
    if (arg3 < *arg1) {
        return func_80073A10(arg0, arg1, arg2, arg3, arg4, arg5, arg6);
    }
}

s32 func_80073B78(s32 arg0, s32 arg1, s16* arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7) {
    s32 phi_t0;

    phi_t0 = 0;
    if (D_80165C18[arg1].unk_0CF == 0) {
        D_80165C18[arg1].unk_0AC = arg6;
        if (arg0 != 0) {
            *arg2 = arg3;
        }
        D_80165C18[arg1].unk_0D0 = arg7;
        func_80073800(arg1, 1);
    } else {
        D_80165C18[arg1].unk_0AC--;
        if (D_80165C18[arg1].unk_0AC < 0) {
            D_80165C18[arg1].unk_0AC = arg6;
            if (D_80165C18[arg1].unk_0CF == 1) {
                *arg2 += arg5;
                if (*arg2 >= arg4) {
                    *arg2 = arg4;
                    D_80165C18[arg1].unk_0CF++;
                }
            } else {
                *arg2 -= arg5;
                if (arg3 >= *arg2) {
                    *arg2 = arg3;
                    if (D_80165C18[arg1].unk_0D0 > 0) {
                        D_80165C18[arg1].unk_0D0--;
                    }
                    if (D_80165C18[arg1].unk_0D0 == 0) {
                        func_80073800(arg1, 0);
                        func_8007381C(arg1);
                        phi_t0 = 1;
                    } else {
                        D_80165C18[arg1].unk_0CF = 1;
                    }
                }
            }
        }
    }

    return phi_t0;
}

void func_80073CB0(s32 arg0, s16* arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6) {
    func_80073B78(1, arg0, arg1, arg2, arg3, arg4, arg5, arg6);
}

void func_80073D0C(s32 arg0, s16* arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6) {
    func_80073B78(0, arg0, arg1, arg2, arg3, arg4, arg5, arg6);
}

UNUSED void func_80073D68(s32 arg0, s16* arg1, s16 arg2, s32 arg3) {
    *arg1 = *arg1 + arg3;
    if (*arg1 >= arg2) {
        *arg1 = arg2;
        func_80073800(arg0, 0);
        func_8007381C(arg0);
    }
}

void func_80073DC0(s32 arg0, s16* arg1, s16 arg2, s32 arg3) {
    *arg1 = *arg1 - arg3;
    if (arg2 >= *arg1) {
        *arg1 = arg2;
        func_80073800(arg0, 0);
        func_8007381C(arg0);
    }
}

s32 func_80073E18(s32 arg0, u16* arg1, u16 arg2, s32 arg3) {
    s32 phi_t0;
    s32 temp_v1;

    phi_t0 = 0;
    if (D_80165C18[arg0].unk_0CF == 0) {
        func_80073800(arg0, 1);
        D_80165C18[arg0].unk_048 = arg3;
    }

    temp_v1 = D_80165C18[arg0].unk_048 - arg2;
    if (temp_v1 <= 0) {
        *arg1 += D_80165C18[arg0].unk_048;
        func_80073800(arg0, 0);
        phi_t0 = 1;
    } else {
        *arg1 += arg2;
        D_80165C18[arg0].unk_048 = temp_v1;
    }
    
    return phi_t0;
}

UNUSED s32 func_80073ED4(s32 arg0, u16* arg1, u16 arg2, s32 arg3) {
    s32 phi_t0;
    s32 temp_v1;

    phi_t0 = 0;
    if (D_80165C18[arg0].unk_0CF == 0) {
        func_80073800(arg0, 1);
        D_80165C18[arg0].unk_048 = arg3;
    }

    temp_v1 = D_80165C18[arg0].unk_048 - arg2;
    if (temp_v1 <= 0) {
        *arg1 += D_80165C18[arg0].unk_048;
        func_80073800(arg0, 0);
        phi_t0 = 1;
    } else {
        *arg1 -= arg2;
        D_80165C18[arg0].unk_048 = temp_v1;
    }
    return phi_t0;
}

void func_80073F90(s32 arg0, s32 arg1) {
    D_80165C18[arg0].unk_0CD = arg1;
}

void func_80073FAC(s32 arg0) {
    D_80165C18[arg0].unk_0DB++;
}

void func_80073FD4(s32 arg0) {
    func_80073F90(arg0, 0);
    D_80165C18[arg0].unk_0DB = 1;
}

UNUSED void func_80074014(void) {

}

s32 func_8007401C(s32 arg0, f32* arg1, f32 arg2, f32 arg3, f32 arg4, s32 arg5, s32 arg6) {
    s32 phi_a3;

    phi_a3 = 0;
    if (D_80165C18[arg0].unk_0CD == 0) {
        *arg1 = arg2;
        D_80165C18[arg0].unk_0AA = arg5;
        D_80165C18[arg0].unk_0CE = arg6;
        func_80073F90(arg0, 1);
    } else {
        D_80165C18[arg0].unk_0AA--;
        if ((s32) D_80165C18[arg0].unk_0AA < 0) {
            D_80165C18[arg0].unk_0AA = arg5;
            *arg1 += arg4;
            if (arg3 < *arg1) {
                if ((s32) D_80165C18[arg0].unk_0CE > 0) {
                    D_80165C18[arg0].unk_0CE--;
                }
                if (D_80165C18[arg0].unk_0CE == 0) {
                    *arg1 = arg3;
                    func_80073F90(arg0, 0);
                    func_80073FAC(arg0);
                    phi_a3 = 1;
                } else {
                    *arg1 = arg2;
                }
            }
        }
    }
    
    return phi_a3;
}

s32 func_80074118(s32 arg0, f32* arg1, f32 arg2, f32 arg3, f32 arg4, s32 arg5, s32 arg6) {
    return func_8007401C(arg0, arg1, arg2, arg3, arg4, arg5, arg6);
}

s32 func_8007415C(s32 arg0, f32* arg1, f32 arg2, f32 arg3, f32 arg4, s32 arg5, s32 arg6) {
    if (*arg1 < arg3) {
        return func_8007401C(arg0, arg1, arg2, arg3, arg4, arg5, arg6);
    }
}

s32 func_800741B4(s32 arg0, f32* arg1, f32 arg2, f32 arg3, f32 arg4, s32 arg5, s32 arg6) {
    if (D_80165C18[arg0].unk_0CD == 0) {
        *arg1 = arg2;
        D_80165C18[arg0].unk_0AA = arg5;
        D_80165C18[arg0].unk_0CE = arg6;
        func_80073F90(arg0, 1);
    } else {
        D_80165C18[arg0].unk_0AA += -1;
        if (D_80165C18[arg0].unk_0AA < 0) {
            D_80165C18[arg0].unk_0AA = arg5;
            *arg1 -= arg4;
            if (*arg1 < arg3) {
                if (D_80165C18[arg0].unk_0CE > 0) {
                    D_80165C18[arg0].unk_0CE--;
                }
                if (D_80165C18[arg0].unk_0CE == 0) {
                    *arg1 = arg3;
                    func_80073F90(arg0, 0);
                    func_80073FAC(arg0);
                } else {
                    *arg1 = arg2;
                }
            }
        }
    }
    
    return 0;
}


UNUSED void func_800742A8(s32 arg0, f32* arg1, f32 arg2, f32 arg3, f32 arg4, s32 arg5, s32 arg6) {
    func_800741B4(arg0, arg1, arg2, arg3, arg4, arg5, arg6);
}

UNUSED void func_800742EC(s32 arg0, f32* arg1, f32 arg2, f32 arg3, f32 arg4, s32 arg5, s32 arg6) {
    if (arg3 < *arg1) {
        func_800741B4(arg0, arg1, arg2, arg3, arg4, arg5, arg6);
    }
}

void func_80074344(s32 arg0, f32* arg1, f32 arg2, f32 arg3, f32 arg4, s32 arg5, s32 arg6) {
    if (D_80165C18[arg0].unk_0CD == 0) {
        *arg1 = arg2;
        D_80165C18[arg0].unk_0AA = arg5;
        D_80165C18[arg0].unk_0CE = arg6;
        func_80073F90(arg0, 1);
        return;
    }

    D_80165C18[arg0].unk_0AA--;
    if (D_80165C18[arg0].unk_0AA < 0) {
        D_80165C18[arg0].unk_0AA = arg5;
        if (D_80165C18[arg0].unk_0CD == 1) {
            *arg1 += arg4;
            if (arg3 <= *arg1) {
                *arg1 = arg3;
                D_80165C18[arg0].unk_0CD++;
            }
        } else {
            *arg1 -= arg4;
            if (*arg1 <= arg2) {
                *arg1 = arg2;

                if (D_80165C18[arg0].unk_0CE > 0) {
                    D_80165C18[arg0].unk_0CE--;
                }
                if (D_80165C18[arg0].unk_0CE == 0) {
                    func_80073F90(arg0, 0);
                    func_80073FAC(arg0);
                } else {
                    D_80165C18[arg0].unk_0CD = 1;
                }
            }
        }
    }
}

void func_80074478(s32 arg0) {
    D_80165C18[arg0].unk_054 |= 1;
}

void func_800744A0(s32 arg0) {
    D_80165C18[arg0].unk_054 &= ~1;
}

void func_800744CC(void) {
    if (D_8018D224 != 0) {
        osRecvMesg(&gDmaMesgQueue, &gMainReceivedMesg, OS_MESG_BLOCK);
        D_8018D224 = 0;
    }
}

void func_80074510(uintptr_t devAddr, void * vaddr, size_t nbytes) {
    func_800744CC();
    osPiStartDma(&gDmaIoMesg, OS_MESG_PRI_NORMAL, OS_READ, devAddr, vaddr, nbytes, &gDmaMesgQueue);
    D_8018D224 = 1;
}

void func_80074574(u8 *arg0, void *arg1, u16 arg2, u16 arg3) {
    func_80074510((uintptr_t) &_other_texturesSegmentRomStart[SEGMENT_OFFSET(arg0)], arg1, arg2 * arg3);
}

// todo: arg1 should likely be a u8 *
void func_800745C8(s32 objectIndex, s32 arg1) {
    s32 phi_a1;

    if ((D_80165C18[objectIndex].unk_054 & 1) != 0) {
        phi_a1 = 0;
        if (D_80165C18[objectIndex].tlutList != D_80165C18[objectIndex].activeTLUT) {
            D_80165C18[objectIndex].activeTLUT = D_80165C18[objectIndex].tlutList;
        }

        D_80165C18[objectIndex].unk_054 ^= 2;
        if ((D_80165C18[objectIndex].unk_054 & 2) != 0) {
            phi_a1 = 1;
        }
        
        D_80165C18[objectIndex].activeTexture = (u8 *) (D_80165C18[objectIndex].textureWidth * D_80165C18[objectIndex].textureHeight * phi_a1) + arg1;
        func_800744A0(objectIndex);
    }
}

void func_8007466C(s32 arg0, s32 arg1) {
    s32 phi_a1;

    if ((D_80165C18[arg0].unk_054 & 1) != 0) {
        // I have no idea why this typecase works
        D_80165C18[arg0].activeTLUT = (u32*)D_80165C18[arg0].tlutList + (D_80165C18[arg0].unk_0D3 << 7) ;
        D_80165C18[arg0].unk_054 ^= 2;
        phi_a1 = 0;
        if ((D_80165C18[arg0].unk_054 & 2) != 0) {
            phi_a1 = 1;
        }
        D_80165C18[arg0].activeTexture = (u8 *) (D_80165C18[arg0].textureWidth * D_80165C18[arg0].textureHeight * phi_a1) + arg1;
        func_800744A0(arg0);
    }
}

void func_80074704(s32 arg0, s32 arg1) {
    s32 phi_a1;
    
    if ((D_80165C18[arg0].unk_054 & 1) != 0) {
        D_80165C18[arg0].activeTLUT = D_80165C18[arg0].tlutList;
        D_80165C18[arg0].unk_054 ^= 2;
        phi_a1 = 0;
        if ((D_80165C18[arg0].unk_054 & 2) != 0) {
            phi_a1 = 1;
        }
        D_80165C18[arg0].activeTexture = (u8 *) (D_80165C18[arg0].textureWidth * D_80165C18[arg0].textureHeight * phi_a1) + arg1;
        func_800744A0(arg0);
    }
}

u8 *func_80074790(s32 arg0, u8 *arg1) {
    s32 phi_a2;

    D_80165C18[arg0].unk_054 ^= 4;
    phi_a2 = 0;
    if ((D_80165C18[arg0].unk_054 & 4) != 0) {
        phi_a2 = 1;
    }
    return (D_80165C18[arg0].textureWidth * D_80165C18[arg0].textureHeight * phi_a2) + arg1;
}

void func_800747F0(s32 objectIndex, u8 *arg1) {
    u8 *sp24;
    if (D_80165C18[objectIndex].unk_0D2 != D_80165C18[objectIndex].unk_0D3) {
        sp24 = D_80165C18[objectIndex].textureList + (D_80165C18[objectIndex].textureWidth * D_80165C18[objectIndex].textureHeight * D_80165C18[objectIndex].unk_0D2);
        func_80074574(sp24, (void *) func_80074790(objectIndex, arg1), D_80165C18[objectIndex].textureWidth, D_80165C18[objectIndex].textureHeight);
        D_80165C18[objectIndex].unk_0D3 = D_80165C18[objectIndex].unk_0D2;
        func_80074478(objectIndex);
    }
}

void func_80074894(s32 objectIndex, u8 *arg1) {
    func_800747F0(objectIndex, arg1);
    func_800745C8(objectIndex, (s32)arg1);
}

void func_800748C4(s32 objectIndex, u8 *arg1) {
    func_800747F0(objectIndex, arg1);
    func_8007466C(objectIndex, (s32)arg1);
}

void func_800748F4(s32 objectIndex, u8 *arg1) {
    func_800747F0(objectIndex, arg1);
    func_80074704(objectIndex, (s32)arg1);
}

struct _struct_D_800E6F30_0x3 {
    /* 0x0 */ u8 unk0;                              /* inferred */
    /* 0x1 */ u8 unk1;                              /* inferred */
    /* 0x2 */ u8 unk2;                              /* inferred */
};                                                  /* size = 0x3 */

struct _struct_D_800E6F48_0x3 {
    /* 0x0 */ u8 unk0;                              /* inferred */
    /* 0x1 */ u8 unk1;                              /* inferred */
    /* 0x2 */ u8 unk2;                              /* inferred */
};                                                  /* size = 0x3 */

//void func_8008B80C(s32, ?, ?, ?);                      /* extern */
extern u16 D_80165748;
extern s16 D_80165718;
extern s16 D_80165720;
extern s16 D_80165728;

extern struct _struct_D_800E6F30_0x3 D_800E6F30[8];
extern struct _struct_D_800E6F30_0x3 D_800E6F48[8];

//extern f32 D_8018D01C;
// static struct _struct_D_800E6F30_0x3 D_800E6F30[8] = {
//     { 0xC8, 1, 0 },
//     { 0, 0x70, 1 },
//     { 0x10, 0x79, 0x51 },
//     { 0, 0x59, 0x70 },
//     { 0x70, 0x55, 0 },
//     { 0x7A, 0x7E, 0 },
//     { 0x77, 0x2C, 0x24 },
//     { 0x30, 0x14, 0x58 },
// };
// static struct _struct_D_800E6F48_0x3 D_800E6F48[8] = {
//     { 0xDC, 0, 0 },
//     { 0, 0x8C, 6 },
//     { 0, 0, 0x51 },
//     { 0, 0, 0 },
//     { 0, 0, 0 },
//     { 0, 0, 0 },
//     { 0, 0, 0 },
//     { 0, 0, 0 },
// };

void func_80074924(s32 objectIndex) {
    s32 sp2C;
    s32 sp28;
    s32 sp24;
    s32 sp20;
    s16 temp_v0;
    s32 temp_a0;
    struct _struct_D_800E6F30_0x3 *temp_v0_2;
    struct _struct_D_800E6F48_0x3 *temp_v1;
    struct_80165C18_entry *temp_s0;

    temp_s0 = &D_80165C18[objectIndex];
    temp_s0->sizeScaling = 0.15f;
    temp_v0 = gCurrentCourseId;
    switch (temp_v0) {                              /* irregular */
    case 0:
        sp2C = random_int(0x00C8U);
        sp28 = random_int(D_80165748);
        sp24 = random_int(0x0096U);
        sp20 = random_int(0x2000U);
        temp_s0->unk_010[0] = (f32) ((((f64) D_80165718 + 100.0) - (f64) sp2C) * (f64) D_8018D01C);
        temp_s0->unk_010[1] = (f32) (D_80165720 + sp28);
        temp_s0->unk_010[2] = (f32) (((f64) D_80165728 + 200.0) - (f64) sp24);
        break;
    case 7:
        sp2C = random_int(0x0168U);
        sp28 = random_int(D_80165748);
        sp24 = random_int(0x00B4U);
        sp20 = random_int(0x2000U);
        temp_s0->unk_010[0] = (f32) ((((f64) D_80165718 + 180.0) - (f64) sp2C) * (f64) D_8018D01C);
        temp_s0->unk_010[1] = (f32) (D_80165720 + sp28);
        temp_s0->unk_010[2] = (f32) (((f64) D_80165728 + 200.0) - (f64) sp24);
        break;
    case 8:
        sp2C = random_int(0x012CU);
        sp28 = random_int(D_80165748);
        sp24 = random_int(0x0096U);
        sp20 = random_int(0x2000U);
        temp_s0->unk_010[0] = (f32) ((((f64) D_80165718 + 150.0) - (f64) sp2C) * (f64) D_8018D01C);
        temp_s0->unk_010[1] = (f32) (D_80165720 + sp28);
        temp_s0->unk_010[2] = (f32) (((f64) D_80165728 + 200.0) - (f64) sp24);
        break;
    }
    func_8008B80C(objectIndex, 0, 0, 0);
    if (D_8018EDF3 == 1) {
        temp_s0->unk_038[1] = (f32) (((f64) (f32) (sp2C % 4) * 0.25) + 0.8);
    } else {
        temp_s0->unk_038[1] = (f32) (((f64) (f32) (sp2C % 3) * 0.2) + 0.4);
    }
    temp_a0 = sp2C % 8;
    temp_v0_2 = &D_800E6F30[temp_a0];
    temp_v1 = (struct _struct_D_800E6F48_0x3 *)&D_800E6F48[temp_a0];
    temp_s0->unk_084[0] = (s16) temp_v0_2->unk0;
    temp_s0->unk_084[1] = (s16) temp_v0_2->unk1;
    temp_s0->unk_084[2] = (s16) temp_v0_2->unk2;
    temp_s0->unk_084[3] = (s16) temp_v1->unk0;
    temp_s0->unk_084[4] = (s16) temp_v1->unk1;
    temp_s0->unk_084[5] = (s16) temp_v1->unk2;
    temp_s0->unk_084[6] = sp20 - 0x1000;
    if (sp2C & 1) {
        temp_s0->unk_084[7] = (sp20 / 32) + 0x100;
    } else {
        temp_s0->unk_084[7] = -0x100 - (sp20 / 32);
    }
    temp_s0->unk_0A0 = 0x00E6;
    func_80072488(objectIndex);
}

void func_80074D94(s32 arg0) {
    if (D_80165C18[arg0].unk_0AE == 1) {
        if ((D_80165740 <= D_80165C18[arg0].unk_028[1]) && (s16_step_down_towards(&D_80165C18[arg0].unk_0A0, 0, 8) != 0)) {
            func_80086F60(arg0);
        }
        func_800877C4(arg0);
    }
    func_8008BF18(arg0);
}

void func_80074E28(s32 arg0) {
    switch (D_80165C18[arg0].unk_0A6) {
    case 1:
        func_80074924(arg0);
        break;
    case 2:
        if (func_8007278C(arg0, 1) != 0) {
            func_80086E70(arg0);
            break;
        }
    case 0:
        break;
    case 3:
        func_80041480(&D_80165C18[arg0].unk_084[6], -0x1000, 0x1000, &D_80165C18[arg0].unk_084[7]);
        if (D_80165C18[arg0].unk_0AE == 0) {
            func_80072428(arg0);
        }
        break;
    }
}

void func_80074EE8(void) {
    s32 someIndex;
    s32 objectIndex;
    s32 someCount;
    struct_80165C18_entry *object;

    someCount = 0;
    for (someIndex = 0; someIndex < D_80165738; someIndex++) {
        objectIndex = D_8018C630[someIndex];
        if (objectIndex != -1) {
            object = &D_80165C18[objectIndex];
            if (object->unk_0A6 != 0) {
                func_80074E28(objectIndex);
                func_80074D94(objectIndex);
                if (object->unk_0A6 == 0) {
                    func_80072100(&D_8018C630[someIndex]);
                }
                someCount += 1;
            }
        }
    }
    if (someCount == 0) {
        D_80165730 = 0;
    }
}

void func_80074FD8(s32 objectIndex) {
    switch (D_80165C18[objectIndex].unk_0A6) {                              /* irregular */
    case 0:
        break;
    case 1:
        if (func_80087E08(objectIndex, D_80165C18[objectIndex].unk_038[1], 0.12f, D_80165C18[objectIndex].unk_034, D_80165C18[objectIndex].unk_0BE[1], 0x00000064) != 0) {
            func_80072488(objectIndex);
        }
        func_8008BF18(objectIndex);
        D_80165C18[objectIndex].unk_0B2[0] += D_8016582C[0];
        D_80165C18[objectIndex].unk_0B2[1] += D_8016582C[1];
        D_80165C18[objectIndex].unk_0B2[2] += D_8016582C[2];
        break;
    case 2:
        func_80086F60(objectIndex);
        func_80072428(objectIndex);
        break;
    }
}

void func_800750D8(s32 objectIndex, s32 arg1, Vec3f arg2, s32 arg3, s32 arg4) {
    s32 sp24;
    s32 temp_v0;
    struct_80165C18_entry *temp_v1;

    func_800723A4(objectIndex, 0);
    sp24 = random_int(0x01F4U);
    temp_v0 = random_int(0x0032U);
    temp_v1 = &D_80165C18[objectIndex];
    temp_v1->unk_0D5 = arg3;
    temp_v1->sizeScaling = ((f64) (f32) sp24 * 0.0005) + 0.05;
    // ALL HAIL THE FAKE MATCH GODS!!!!!
    temp_v1->unk_038[1] = ((f64) (f32) temp_v0 * (0.05 * 1.0)) + 2.0;
    temp_v1->unk_034 = ((f64) (f32)(temp_v0 % 5) * 0.1) + 1.0;
    temp_v1->unk_0BE[1] = (arg1 << 0x10) / arg4;
    temp_v1->unk_010[0] = (arg2[0] + (temp_v0 / 2)) - 12.0f;
    temp_v1->unk_010[1] = (arg2[1] - 10.0) + random_int(0x000AU);
    temp_v1->unk_010[2] = (arg2[2] + (temp_v0 / 2)) - 12.0f;
    temp_v1->unk_0B2[0] = sp24 << 7;
    temp_v1->unk_0B2[1] = temp_v0 * 0x50;
    temp_v1->unk_0B2[2] = temp_v0 * 0x50;
}

void func_80075304(Vec3f arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 var_s1;
    s32 var_s0;

    for (var_s1 = 0; var_s1 < arg3; var_s1++) {
        switch (arg1) {                             /* irregular */
        case 1:
            var_s0 = func_80072044(D_8018C1B0, &D_80183E38, 0x00000080);
            break;
        case 2:
            var_s0 = func_80072044(D_8018C3F0, &D_80183E4C, 0x00000080);
            break;
        case 3:
            var_s0 = func_80072044(D_8018C630, &D_80183E5C, 0x00000080);
            break;
        }
        if (var_s0 == -1) break;
        func_800750D8(var_s0, var_s1, arg0, arg2, arg3);
    }
}

void func_8007542C(s32 arg0) {
    s32 var_v0;
    s32 var_s2;
    s32 *var_s3;
    struct_80165C18_entry *temp_s0;

    D_8016582C[0] += 0x2000;
    D_8016582C[1] += 0x1000;
    D_8016582C[2] += 0x1800;
    for (var_s2 = 0; var_s2 < 0x80; var_s2++) {
        switch (arg0) {                             /* irregular */
        case 1:
            var_s3 = D_8018C1B0;
            break;
        case 2:
            var_s3 = D_8018C3F0;
            break;
        case 3:
            var_s3 = D_8018C630;
            break;
        }
        var_v0 = var_s3[var_s2];
        if (var_v0 != -1) {
            temp_s0 = &D_80165C18[var_v0];
            if (temp_s0->unk_0A6 != 0) {
                func_80074FD8(var_v0);
                if (temp_s0->unk_0A6 == 0) {
                    func_80072100(&var_s3[var_s2]);
                }
            }
        }

    }
}

void func_80075574(s32 objectIndex, Vec3f arg1, f32 arg2) {
    struct_80165C18_entry *temp_v1;
    UNUSED s32 pad[2];

    func_800723A4(objectIndex, 0);
    temp_v1 = &D_80165C18[objectIndex];
    temp_v1->unk_010[0] = arg1[0];
    temp_v1->unk_010[1] = arg1[1];
    temp_v1->unk_010[2] = arg1[2];
    temp_v1->unk_038[1] = arg2;
    temp_v1->unk_0A4 = random_int(0x0064U) + 0x1E;
}

s32 func_800755FC(s32 arg0, Vec3f arg1, f32 arg2) {
    s32 temp_v0;

    if (arg0 == 0) {
        temp_v0 = func_80072044(D_8018C3F0, &D_80183E4C, D_8018C3F0_SIZE);
        if (temp_v0 != -1) {
            func_80075574(temp_v0, arg1, arg2);
        }
    } else {
        temp_v0 = func_80072044(D_8018C630, &D_80183E5C, D_8018C630_SIZE);
        if (temp_v0 != -1) {
            func_80075574(temp_v0, arg1, arg2);
        }
    }
    return temp_v0;
}

void func_80075698(s32 arg0) {
    D_80165C18[arg0].unk_0D5 = 1;
    D_80165C18[arg0].activeTexture = D_8018D490;
    D_80165C18[arg0].textureList = D_8018D490;
    D_80165C18[arg0].unk_0A0 = 0xFF;
    D_80165C18[arg0].unk_0BE[1] = 0;
    D_80165C18[arg0].unk_0B2[0] = 0;
    D_80165C18[arg0].unk_0B2[2] = 0;
    D_80165C18[arg0].unk_028[0] = 0.0f;
    D_80165C18[arg0].unk_028[1] = 0.0f;
    D_80165C18[arg0].unk_028[2] = 0.0f;
    D_80165C18[arg0].sizeScaling = 0.5f;
    func_80072488(arg0);
}

void func_80075714(s32 objectIndex) {
    switch (D_80165C18[objectIndex].unk_0A6) {
    case 1:
        func_80075698(objectIndex);
        break;
    case 2:
        D_80165C18[objectIndex].unk_038[1] -= 0.03;
        f32_step_up_towards(&D_80165C18[objectIndex].unk_028[1], 100.0f, D_80165C18[objectIndex].unk_038[1]);
        func_8007415C(objectIndex, &D_80165C18[objectIndex].sizeScaling, 0.55f, 1.0f, 0.1f, 1, 0);
        if (func_80073B00(objectIndex, &D_80165C18[objectIndex].unk_0A0, 0xFF, 0x1E, 7, 0, 0) != 0) {
            func_80072488(objectIndex);
        }
        break;
    case 3:
        func_80072428(objectIndex);
        break;
    case 0:
        break;
    }
    
    func_8008BF18(objectIndex);
}

#ifdef MIPS_TO_C
//generated by m2c commit d9d3d6575355663122de59f6b2882d8f174e2355 on Dec-28-2022
extern s32 D_801636A0;
extern s32 D_801637AC;
extern s16 D_8016578C;
extern s16 D_80165790;
extern ? D_8018C5F0;

void func_80075838(void) {
    s32 *var_s1;
    s32 *var_s1_2;
    s32 temp_a0;
    s32 temp_a0_2;
    s32 var_s2;
    s32 var_s2_2;
    struct_80165C18_entry *temp_s0;
    struct_80165C18_entry *temp_s0_2;

    if (D_8016578C != 0) {
        D_8016578C -= 1;
    }
    if (D_80165790 != 0) {
        D_80165790 -= 1;
    }
    var_s2 = 0;
    if ((D_801636A0 != 0) || (D_8016578C != 0)) {
        var_s1 = D_8018C3F0;
        do {
            temp_a0 = *var_s1;
            if (temp_a0 != -1) {
                temp_s0 = &D_80165C18[temp_a0];
                if (temp_s0->unk_0A6 != 0) {
                    func_80075714(temp_a0);
                    if (temp_s0->unk_0A6 == 0) {
                        func_80072100(var_s1);
                    }
                    var_s2 += 1;
                }
            }
            var_s1 += 4;
        } while (var_s1 != &D_8018C5F0);
        if (var_s2 != 0) {
            D_8016578C = 0x0064;
        }
    }
    if ((D_801637AC != 0) || (D_80165790 != 0)) {
        var_s2_2 = 0;
        var_s1_2 = D_8018C630;
        do {
            temp_a0_2 = *var_s1_2;
            if (temp_a0_2 != -1) {
                temp_s0_2 = &D_80165C18[temp_a0_2];
                if (temp_s0_2->unk_0A6 != 0) {
                    func_80075714(temp_a0_2);
                    if (temp_s0_2->unk_0A6 == 0) {
                        func_80072100(var_s1_2);
                    }
                    var_s2_2 += 1;
                }
            }
            var_s1_2 += 4;
        } while (var_s1_2 != &D_8018C830);
        if (var_s2_2 != 0) {
            D_80165790 = 0x0064;
        }
    }
}
#else
GLOBAL_ASM("asm/non_matchings/code_80071F00/func_80075838.s")
#endif

void func_800759EC(s32 objectIndex, Vec3f arg1, f32 arg2) {
    struct_80165C18_entry *temp_v0;

    func_800723A4(objectIndex, 0);
    temp_v0 = &D_80165C18[objectIndex];
    temp_v0->unk_010[0] = arg1[0];
    temp_v0->unk_010[1] = arg1[1];
    temp_v0->unk_010[2] = arg1[2];
    temp_v0->unk_038[1] = arg2;
    temp_v0->unk_0A4 = 0x00FF;
    temp_v0->unk_0A2 = 0x0096;
}

s32 func_80075A6C(s32 arg0, Vec3f arg1, f32 arg2) {
    s32 temp_v0;

    if (arg0 == 0) {
        temp_v0 = func_80072044(D_8018C3F0, &D_80183E4C, 0x80);
        if (temp_v0 != -1) {
            func_800759EC(temp_v0, arg1, arg2);
        }
    } else {
        temp_v0 = func_80072044(D_8018C630, &D_80183E5C, 0x80);
        if (temp_v0 != -1) {
            func_800759EC(temp_v0, arg1, arg2);
        }
    }
    
    return temp_v0;
}

void func_80075B08(s32 arg0) {
    D_80165C18[arg0].unk_0D5 = 6;
    D_80165C18[arg0].activeTexture = D_8018D490;
    D_80165C18[arg0].textureList = D_8018D490;
    D_80165C18[arg0].unk_0A0 = 0xFF;
    D_80165C18[arg0].unk_0BE[1] = 0;
    D_80165C18[arg0].unk_0B2[0] = 0;
    D_80165C18[arg0].unk_0B2[2] = 0;
    D_80165C18[arg0].unk_028[0] = 0.0f;
    D_80165C18[arg0].unk_028[1] = 0.0f;
    D_80165C18[arg0].unk_028[2] = 0.0f;
    D_80165C18[arg0].sizeScaling = 0.5f;
    func_80072488(arg0);
}

void func_80075B84(s32 arg0) {
    switch (D_80165C18[arg0].unk_0A6) {
    case 1:
        func_80075B08(arg0);
        break;
    case 2:
        D_80165C18[arg0].unk_038[1] -= 0.03;
        f32_step_up_towards(&D_80165C18[arg0].unk_028[1], 100.0f, D_80165C18[arg0].unk_038[1]);
        func_8007415C(arg0, &D_80165C18[arg0].sizeScaling, 0.55f, 1.0f, 0.1f, 1, 0);
        if (func_80073B00(arg0, &D_80165C18[arg0].unk_0A0, 0xFF, 0x1E, 7, 0, 0) != 0) {
            func_80072488(arg0);
        }
        break;
    case 3:
        func_80072428(arg0);
        break;
    case 0:
        break;
    }

    func_8008BF18(arg0);
}

#ifdef MIPS_TO_C
//generated by m2c commit d9d3d6575355663122de59f6b2882d8f174e2355 on Dec-28-2022
extern s32 D_801637E8;
extern s32 D_80163814;
extern s16 D_8016578C;
extern s16 D_80165790;
extern ? D_8018C5F0;

void func_80075CA8(void) {
    s32 *var_s1;
    s32 *var_s1_2;
    s32 temp_a0;
    s32 temp_a0_2;
    s32 var_s2;
    s32 var_s2_2;
    struct_80165C18_entry *temp_s0;
    struct_80165C18_entry *temp_s0_2;

    if (D_8016578C != 0) {
        D_8016578C -= 1;
    }
    if (D_80165790 != 0) {
        D_80165790 -= 1;
    }
    var_s2 = 0;
    if ((D_801637E8 != 0) || (D_8016578C != 0)) {
        var_s1 = D_8018C3F0;
        do {
            temp_a0 = *var_s1;
            if (temp_a0 != -1) {
                temp_s0 = &D_80165C18[temp_a0];
                if (temp_s0->unk_0A6 != 0) {
                    func_80075B84(temp_a0);
                    if (temp_s0->unk_0A6 == 0) {
                        func_80072100(var_s1);
                    }
                    var_s2 += 1;
                }
            }
            var_s1 += 4;
        } while (var_s1 != &D_8018C5F0);
        if (var_s2 != 0) {
            D_8016578C = 0x0064;
        }
    }
    if ((D_80163814 != 0) || (D_80165790 != 0)) {
        var_s2_2 = 0;
        var_s1_2 = D_8018C630;
        do {
            temp_a0_2 = *var_s1_2;
            if (temp_a0_2 != -1) {
                temp_s0_2 = &D_80165C18[temp_a0_2];
                if (temp_s0_2->unk_0A6 != 0) {
                    func_80075B84(temp_a0_2);
                    if (temp_s0_2->unk_0A6 == 0) {
                        func_80072100(var_s1_2);
                    }
                    var_s2_2 += 1;
                }
            }
            var_s1_2 += 4;
        } while (var_s1_2 != &D_8018C830);
        if (var_s2_2 != 0) {
            D_80165790 = 0x0064;
        }
    }
}
#else
GLOBAL_ASM("asm/non_matchings/code_80071F00/func_80075CA8.s")
#endif

void func_80075E5C(s32 objectIndex, Vec3f arg1, u16 arg2, f32 arg3, s32 arg4) {
    struct_80165C18_entry *temp_v0;

    func_800723A4(objectIndex, 0);
    temp_v0 = &D_80165C18[objectIndex];
    temp_v0->sizeScaling = 0.5f;
    temp_v0->unk_0D5 = 5;
    temp_v0->unk_010[0] = arg1[0];
    temp_v0->unk_010[1] = arg1[1];
    temp_v0->unk_010[2] = arg1[2];
    temp_v0->unk_0BE[0] = 0x0C00;
    temp_v0->unk_0BE[2] = 0;
    temp_v0->unk_034 = arg3 * 4.0;
    temp_v0->unk_0BE[1] = arg2;
    temp_v0->unk_0A4 = 0x00FF;
    temp_v0->unk_0A2 = 0x00FF;
    temp_v0->unk_048 = arg4 * 2;
}

s32 func_80075F28(Vec3f arg0, u16 arg1, f32 arg2, s32 arg3) {
    s32 temp_v0;

    temp_v0 = func_80072044(D_8018C1B0, &D_80183E38, 0x80);
    if (temp_v0 != -1) {
        func_80075E5C(temp_v0, arg0, arg1, arg2, arg3);
    }
    return temp_v0;
}

void func_80075F98(Vec3f arg0, u16 arg1, f32 arg2) {
    s32 someIndex;

    for (someIndex = 0; someIndex < 10; someIndex++) {
        if (func_80075F28(arg0, arg1, arg2, someIndex) == -1) break;
    }
}

void func_8007601C(s32 arg0) {
    if (D_80165C18[arg0].unk_04C > 0) {
        D_80165C18[arg0].unk_04C--;
        if (D_80165C18[arg0].unk_04C == 0) {
            func_800722CC(arg0, 1);
        }
    }

    if (D_80165C18[arg0].unk_048 > 0) {
        D_80165C18[arg0].unk_048--;
        if (D_80165C18[arg0].unk_048 == 0) {
            func_800C9EF4(D_80165C18[arg0].pos, 0x5102800A);
        }
    }

    if (D_80165C18[arg0].unk_04C == 0) {
        func_8008A6DC(arg0, 300.0f);
        if ((func_8007223C(arg0, 0x40000) != 0) && (func_80072354(arg0, 1) != 0)) {
            func_800722A4(arg0, 1);
            func_80075F98(D_80165C18[arg0].pos, (u16) D_80165C18[arg0].unk_0BE[1], 1.0f);
            func_800C9D80(D_80165C18[arg0].pos, D_80165C18[arg0].unk_038, 0x5102800A);
            if (D_80165C18[arg0].unk_0A4 > 0) {
                D_80165C18[arg0].unk_0A4--;
                D_80165C18[arg0].unk_04C = 0x5A;
            } else {
                D_80165C18[arg0].unk_04C = 0x12C;
            }

            D_80165C18[arg0].unk_048 = 0x3C;
        }
    }

    if (func_8008A8B0(9, 0xB) == 0) {
        D_80165C18[arg0].unk_0A4 = 2;
    }
}

void func_8007614C(void) {
    s32 someIndex;

    for (someIndex = 0; someIndex < 4; someIndex++) {
        func_8007601C(D_8018BFA8[someIndex]);
    }
}

void func_80076194(s32 objectIndex, Vec3f arg1, f32 arg2, s32 arg3) {
    struct_80165C18_entry *temp_v0;

    func_800723A4(objectIndex, 0);
    temp_v0 = &D_80165C18[objectIndex];
    temp_v0->unk_0D5 = 4;
    temp_v0->sizeScaling = 1.0f;
    temp_v0->unk_010[0] = arg1[0];
    temp_v0->unk_010[1] = arg1[1];
    temp_v0->unk_010[2] = arg1[2];
    temp_v0->unk_0BE[0] = 0x0C00;
    temp_v0->unk_0BE[2] = 0;
    temp_v0->unk_0BE[1] = 0x2100;
    if (gIsMirrorMode != 0) {
        temp_v0->unk_0BE[1] += -0x4000;
    }
    temp_v0->unk_0A4 = 0x00FF;
    temp_v0->unk_0A2 = 0x00FF;
    temp_v0->unk_048 = arg3 * 2;
    temp_v0->unk_034 = arg2 * 8.0;
}

s32 func_80076278(Vec3f arg0, f32 arg1, s32 arg2) {
    s32 temp_v0;

    temp_v0 = func_80072044(D_8018C1B0, &D_80183E38, D_8018C1B0_SIZE);
    if (temp_v0 != -1) {
        func_80076194(temp_v0, arg0, arg1, arg2);
    }
    return temp_v0;
}

void func_800762DC(Vec3f arg0, f32 arg1) {
    s32 someIndex;

    for (someIndex = 0; someIndex < 0x14; someIndex++) {
        if (func_80076278(arg0, arg1, someIndex) == -1) break;
    }
}

void func_8007634C(s32 objectIndex) {
    struct_80165C18_entry *temp_v0;

    temp_v0 = &D_80165C18[objectIndex];
    temp_v0->activeTexture = D_0D02BC58;
    temp_v0->textureList = D_0D02BC58;
    temp_v0->unk_0A0 = 0x00FF;
    func_8008B8BC(objectIndex, 0U, 0U, 0U);
    func_8008B80C(objectIndex, 0.0f, 0.0f, 0.0f);
    func_80072488(objectIndex);
}

void func_800763CC(s32 objectIndex) {
    struct_80165C18_entry *temp_s0;

    if(objectIndex){}
    temp_s0 = &D_80165C18[objectIndex];
    switch (temp_s0->unk_0A6) {
    case 1:
        func_8007634C(objectIndex);
        break;
    case 2:
        if (func_8007278C(objectIndex, temp_s0->unk_048) != 0) {
            func_80086E70(objectIndex);
        }
        break;
    case 3:
        if (temp_s0->unk_0D5 == 4) {
            f32_step_towards(&temp_s0->sizeScaling, 4.0f, 0.1f);
            s16_step_towards(&temp_s0->unk_0A4, 0, 0x0018);
            s16_step_towards(&temp_s0->unk_0A2, 0x0080, 0x000C);
        } else {
            f32_step_towards(&temp_s0->sizeScaling, 1.0f, 0.1f);
            s16_step_towards(&temp_s0->unk_0A4, 0, 0x0018);
            s16_step_towards(&temp_s0->unk_0A2, 0x0080, 0x000C);
        }
        if ((temp_s0->unk_0AE >= 2) && (func_80073B00(objectIndex, &temp_s0->unk_0A0, 0x000000FF, 0x00000050, 0x00000020, 0, 0) != 0)) {
            func_80072488(objectIndex);
        }
        break;
    case 4:
        func_80072428(objectIndex);
        func_80086F60(objectIndex);
        break;
    case 0:
    default:
        break;
    }
}

void func_80076538(s32 objectIndex) {
    switch (D_80165C18[objectIndex].unk_0AE) {
    case 0:
        break;
    case 1:
        if ((u8) D_80165C18[objectIndex].unk_0D5 == 4) {
            if (func_80087060(objectIndex, 0x0000000E) != 0) {
                func_80086FD4(objectIndex);
            }
        } else if (func_80087060(objectIndex, 2) != 0) {
            func_80086FD4(objectIndex);
        }
        break;
    case 2:
        u16_step_down_towards(&D_80165C18[objectIndex].unk_0BE[0], 0, 0x00000400);
        break;
    }
    if (D_80165C18[objectIndex].unk_0AE > 0) {
        func_80087844(objectIndex);
        func_8008BF18(objectIndex);
    }
}

void func_8007661C(void) {
    s32 objectIndex;

    objectIndex = D_80183F28[0];
    if (D_80165C18[objectIndex].unk_04C > 0) {
        D_80165C18[objectIndex].unk_04C--;
        if (D_80165C18[objectIndex].unk_04C == 0) {
            func_800722CC(objectIndex, 1);
        }
    }
    if (D_80165C18[objectIndex].unk_048 > 0) {
        D_80165C18[objectIndex].unk_048--;
        if (D_80165C18[objectIndex].unk_048 == 0) {
            func_800C9EF4(D_80165C18[objectIndex].pos, 0x51038009U);
        }
    }
    if (D_80165C18[objectIndex].unk_04C == 0) {
        func_8008A6DC(objectIndex, 750.0f);
        if ((func_8007223C(objectIndex, 0x00040000) != 0) && (func_80072354(objectIndex, 1) != 0)) {
            func_800722A4(objectIndex, 1);
            func_800762DC(D_80165C18[objectIndex].pos, 1.0f);
            func_800C9D80(D_80165C18[objectIndex].pos, D_80165C18[objectIndex].unk_038, 0x51038009U);
            if (D_80165C18[objectIndex].unk_0A4 > 0) {
                D_80165C18[objectIndex].unk_0A4--;
                D_80165C18[objectIndex].unk_04C = 0x0000005A;
            } else {
                D_80165C18[objectIndex].unk_04C = 0x0000012C;
            }
            D_80165C18[objectIndex].unk_048 = 0x0000003C;
        }
    }
    if (func_8008A8B0(4, 5) == 0) {
        D_80165C18[objectIndex].unk_0A4 = 2;
    }
}

void func_8007675C(s32 objectIndex, Vec3s arg1, s32 arg2) {
    struct_80165C18_entry *temp_v0;

    func_800723A4(objectIndex, 0);
    temp_v0 = &D_80165C18[objectIndex];
    temp_v0->unk_0D5 = 9;
    temp_v0->sizeScaling = 1.0f;
    temp_v0->unk_010[0] = arg1[0];
    temp_v0->unk_010[1] = arg1[1];
    temp_v0->unk_010[2] = arg1[2];
    temp_v0->unk_0BE[0] = 0x0C00;
    temp_v0->unk_0BE[1] = 0x2100;
    temp_v0->unk_0BE[2] = 0;
    temp_v0->unk_0A4 = 0x00FF;
    temp_v0->unk_0A2 = 0x00FF;
    temp_v0->unk_034 = 8.0f;
    temp_v0->unk_038[1] = 8.0f;
    temp_v0->unk_048 = arg2;
}

s32 func_80076828(Vec3s arg0, s32 arg1) {
    s32 temp_v0;

    temp_v0 = func_80072044(D_8018C1B0, &D_80183E38, D_8018C1B0_SIZE);
    if (temp_v0 != -1) {
        func_8007675C(temp_v0, arg0, arg1);
    }
    return temp_v0;
}

extern s16 D_800E5740[1]; //[15][3];                               /* unable to generate initializer */
extern s16 D_800E579C[1]; //[15][3];                               /* unable to generate initializer */
extern s16 D_800E57F8[1]; //[15][3];                               /* unable to generate initializer */

void func_80076884(s32 arg0) {
    UNUSED s32 pad[2];
    s32 i;
    s16 *var_s2;
    u16 temp_v0;
    temp_v0 = random_int(0x000FU);
    switch (arg0)
    {
        case 0:
        var_s2 = *(&D_800E5740 + temp_v0 * 3);
        break;

        case 1:
        var_s2 = *(&D_800E579C + temp_v0 * 3);
        break;

        case 2:
        var_s2 = *(&D_800E57F8 + temp_v0 * 3);
        break;

    }

    for (i = 0; i < 1; i++)
    {
        if (func_80076828(var_s2, i) == (-1))
        {
        break;
        }
    }
}

void func_80076958(s32 objectIndex) {
    struct_80165C18_entry *temp_v0;

    temp_v0 = &D_80165C18[objectIndex];
    temp_v0->activeTexture = D_0D02BC58;
    temp_v0->textureList = D_0D02BC58;
    temp_v0->unk_0A0 = 0x00FF;
    func_8008B8BC(objectIndex, 0U, 0U, 0U);
    func_8008B80C(objectIndex, 0.0f, 0.0f, 0.0f);
    func_80072488(objectIndex);
}

void func_800769D8(s32 objectIndex) {
    struct_80165C18_entry *temp_s0;

    temp_s0 = &D_80165C18[objectIndex];
    switch (temp_s0->unk_0A6) {
        case 0:
            break;
        case 1:
            func_80076958(objectIndex);
            break;
        case 2:
            if (func_8007278C(objectIndex, temp_s0->unk_048) != 0) {
                func_80086E70(objectIndex);
            }
            break;
        case 3:
            f32_step_towards(&temp_s0->sizeScaling, 2.0f, 0.05f);
            s16_step_towards(&temp_s0->unk_0A4, 0, 0x0018);
            if ((temp_s0->unk_0AE >= 2) && (func_80073B00(objectIndex, &temp_s0->unk_0A0, 0x000000FF, 0x00000050, 0x00000020, 0, 0) != 0)) {
                func_80072488(objectIndex);
            }
            break;
        case 4:
            func_80072428(objectIndex);
            func_80086F60(objectIndex);
            break;
    }
}

void func_80076AEC(s32 objectIndex) {
    s32 thing;
    thing = D_80165C18[objectIndex].unk_0AE;
    if(thing) {}
    if (thing != 0) {
        if (thing == 1) {
            if (func_80087060(objectIndex, 0x0000000A) != 0) {
                func_80086FD4(objectIndex);
            }
        } else {
            thing = D_80165C18[objectIndex].unk_0AE;
        }
    }
    if (D_80165C18[objectIndex].unk_0AE > 0) {
        func_800877C4(objectIndex);
        func_8008BF18(objectIndex);
    }
}

void func_80076B7C(void) {

}

void func_80076B84(void) {
    s32 someIndex;
    s32 objectIndex;
    struct_80165C18_entry *object;

    func_8007661C();
    func_8007614C();
    for (someIndex = 0; someIndex < D_8018C1B0_SIZE; someIndex++) {
        objectIndex = D_8018C1B0[someIndex];
        if (objectIndex != -1) {
            object = &D_80165C18[objectIndex];
            if (object->unk_0A6 != 0) {
                if ((object->unk_0D5 == 4) || (object->unk_0D5 == 5)) {
                    func_800763CC(objectIndex);
                    func_80076538(objectIndex);
                } else if (object->unk_0D5 == 9) {
                    func_800769D8(objectIndex);
                    func_80076AEC(objectIndex);
                }
                if (object->unk_0A6 == 0) {
                    func_80072100(&D_8018C1B0[someIndex]);
                }
            }
        }
    }
}

void func_80076C9C(s32 objectIndex, Vec3f arg1, s16 arg2) {
    struct_80165C18_entry *temp_v0;

    func_800723A4(objectIndex, (s32) arg2);
    temp_v0 = &D_80165C18[objectIndex];
    temp_v0->unk_0D5 = 0x0A;
    temp_v0->activeTexture = D_0D02BC58;
    temp_v0->textureList = D_0D02BC58;
    temp_v0->sizeScaling = 0.3f;
    func_8008B7D4(objectIndex, arg1[0], arg1[1], arg1[2]);
    temp_v0->unk_0A4 = 0x00FF;
    temp_v0->unk_034 = 0.0f;
    func_8008B8BC(objectIndex, 0U, 0U, 0U);
    func_8008B80C(objectIndex, 0.0f, 0.0f, 0.0f);
}

void func_80076D70(Vec3f arg0, UNUSED f32 arg1, s16 arg2) {
    s32 temp_v0;

    temp_v0 = func_80072044(D_8018C870, &D_80183E6C, 0x00000040);
    if (temp_v0 != -1) {
        func_80076C9C(temp_v0, arg0, arg2);
    }
}

void func_80076DC4(s32 objectIndex) {
    func_80072488(objectIndex);
    if (D_80165C18[objectIndex].unk_0D5 != 0x0B) {
        func_80086E70(objectIndex);
    }
}

void func_80076E14(s32 objectIndex) {
    switch (D_80165C18[objectIndex].unk_0A6) {
        case 1:
            func_80076DC4(objectIndex);
            break;
        case 2:
            if ((D_80165C18[objectIndex].unk_0AE >= 2) && (func_80073B00(objectIndex, &D_80165C18[objectIndex].unk_0A0, 0x000000FF, 0x00000050, 0x00000020, 0, 0) != 0)) {
                func_80072488(objectIndex);
            }
            break;
        case 0:
            break;
        case 3:
            func_80072428(objectIndex);
            func_80086F60(objectIndex);
            break;
    }
}

void func_80076ED8(s32 objectIndex) {
    if ((D_80165C18[objectIndex].unk_0AE != 0) && (D_80165C18[objectIndex].unk_0AE == 1)) {
        func_80086FD4(objectIndex);
    }
    func_8008BF18(objectIndex);
}

void func_80076F2C(void) {
    s32 someIndex;
    s32 flameIndex;
    struct_80165C18_entry *object;

    for (someIndex = 0; someIndex < D_8018C870_SIZE; someIndex++) {
        flameIndex = D_8018C870[someIndex];
        if (flameIndex != -1) {
            object = &D_80165C18[flameIndex];
            if (object->unk_0A6 != 0) {
                func_80076E14(flameIndex);
                func_80076ED8(flameIndex);
                if (object->unk_0A6 == 0) {
                    func_80072100(&D_8018C870[someIndex]);
                }
            }
        }
    }
}
 
extern s16 D_800E6788[1]; // todo: fix this extern
void func_80076FEC(s32 objectIndex, s32 flameIndex) {
    func_800723A4(objectIndex, 3);

    D_80165C18[objectIndex].unk_0D5 = 0xB;
    D_80165C18[objectIndex].activeTexture = D_0D02BC58;
    D_80165C18[objectIndex].textureList = D_0D02BC58;
    D_80165C18[objectIndex].sizeScaling = 0.8f;

    // Mixing arr + offset and array access... Why?
    // todo: ifdef this to proper array access.
    D_80165C18[objectIndex].unk_010[0] = (f32)(intptr_t)(*(&D_800E6788 + flameIndex * 3)[0]) * D_8018D01C;
    D_80165C18[objectIndex].unk_010[1] = (f32)(intptr_t)(*(&D_800E6788 + flameIndex * 3)[1]);
    D_80165C18[objectIndex].unk_010[2] = (f32)(intptr_t)(*(&D_800E6788 + flameIndex * 3)[2]);
    D_80165C18[objectIndex].unk_034 = 0;
    D_80165C18[objectIndex].unk_0A4 = 255;
    D_80165C18[objectIndex].unk_0A2 = 255;
    D_80165C18[objectIndex].unk_0A0 = 255;
    func_8008B8BC(objectIndex, 0, 0, 0);
    func_8008B80C(objectIndex, 0, 0, 0);
}

void func_800770F0(s32 arg0) {
    s32 temp_v0;

    temp_v0 = func_80072044(D_8018C870, &D_80183E6C, 0x00000040);
    if (temp_v0 != -1) {
        func_80076FEC(temp_v0, arg0);
    }
}

void func_80077138(s32 objectIndex, Vec3f arg1, s32 arg2) {
    s8 temp_v0_3;
    Vec3s sp30;

    func_800723A4(objectIndex, arg2);
    D_80165C18[objectIndex].unk_0D5 = 0x0C;
    D_80165C18[objectIndex].sizeScaling = 0.05f;
    func_8008B7D4(objectIndex, arg1[0], arg1[1], arg1[2]);
    func_8008B8BC(objectIndex, 0U, 0U, 0U);
    func_8008B80C(objectIndex, 0.0f, 0.0f, 0.0f);
    switch (arg2) {
        case 0:
            D_80165C18[objectIndex].unk_038[1] = -1.0f;
            D_80165C18[objectIndex].unk_034 = (f32) ((random_int(0x004BU) * 0.01) + 0.25);
            D_80165C18[objectIndex].unk_0BE[1] = random_int(0x0040U) << 0xA;
            func_8008751C(objectIndex);
            D_80165C18[objectIndex].unk_084[5] = 0x001E;
            break;
        case 1:
            D_80165C18[objectIndex].unk_038[1] = 1.5f;
            D_80165C18[objectIndex].unk_034 = (f32) ((random_int(0x0064U) * 0.01) + 0.5);
            D_80165C18[objectIndex].unk_0BE[1] = random_int(0x0040U) << 0xA;
            func_8008751C(objectIndex);
            D_80165C18[objectIndex].unk_084[5] = 0x0032;
            break;
    }
    temp_v0_3 = random_int(0x000CU);
    if (temp_v0_3 < 9) {
        func_8005C674(temp_v0_3, &sp30[2], &sp30[1], sp30);
        D_80165C18[objectIndex].unk_048 = 0;
        D_80165C18[objectIndex].unk_084[0] = sp30[2];
        D_80165C18[objectIndex].unk_084[1] = sp30[1];
        D_80165C18[objectIndex].unk_084[2] = sp30[0];
    } else {
        temp_v0_3 = random_int(3U);
        func_8005C6B4(temp_v0_3, &sp30[2], &sp30[1], sp30);
        D_80165C18[objectIndex].unk_084[0] = sp30[2];
        D_80165C18[objectIndex].unk_084[1] = sp30[1];
        D_80165C18[objectIndex].unk_084[2] = sp30[0];
        D_80165C18[objectIndex].unk_084[4] = temp_v0_3;
        D_80165C18[objectIndex].unk_048 = 1;
    }
    D_80165C18[objectIndex].unk_0A0 = 0x00FF;
    D_80165C18[objectIndex].unk_084[3] = random_int(0x0800U) + 0x400;
    if ((D_80165C18[objectIndex].unk_0BE[1] < 0x3000) || (D_80165C18[objectIndex].unk_0BE[1] >= 0xB001)) {
        D_80165C18[objectIndex].unk_084[3] = -D_80165C18[objectIndex].unk_084[3];
    }
}

void func_800773D8(f32 *arg0, s32 arg1) {
    s32 temp_v0 = func_80072044(D_8018C630, &D_80183E5C, 0x80);
    if (temp_v0 != -1) {
        func_80077138(temp_v0, arg0, arg1);
    }
}

void func_80077428(s32 arg0) {
    func_80072488(arg0);
    func_80086E70(arg0);
}

void func_80077450(s32 objectIndex) {
    UNUSED s16 stackPadding0;
    s16 sp3C;
    s16 sp3A;
    s16 sp38;

    switch (D_80165C18[objectIndex].unk_0A6) {
        case 0:
            break;
        case 1:
            func_80077428(objectIndex);
            break;
        case 2:
            f32_step_up_towards(&D_80165C18[objectIndex].sizeScaling, 0.1f, 0.01f);
            if ((D_80165C18[objectIndex].pos[1] <= D_80165C18[objectIndex].unk_084[5]) && (func_80073B00(objectIndex, &D_80165C18[objectIndex].unk_0A0, 0x000000FF, 0, 0x00000010, 0, 0) != 0)) {
                func_80086F60(objectIndex);
                func_80072428(objectIndex);
            }
            break;
    }
    if (D_80165C18[objectIndex].unk_048 != 0) {
        D_80165C18[objectIndex].unk_084[4] = (s16) ((s32) (D_80165C18[objectIndex].unk_084[4] + 1) % 3);
        func_8005C6B4(D_80165C18[objectIndex].unk_084[4], &sp3C, &sp3A, &sp38);
        D_80165C18[objectIndex].unk_084[0] = sp3C;
        D_80165C18[objectIndex].unk_084[1] = sp3A;
        D_80165C18[objectIndex].unk_084[2] = sp38;
    }
}

void func_80077584(s32 objectIndex) {
    struct_80165C18_entry *temp_v0;

    temp_v0 = &D_80165C18[objectIndex];
    if ((temp_v0->unk_0AE != 0) && (temp_v0->unk_0AE == 1) && ((u8) temp_v0->unk_0D8 != 0)) {
        if (temp_v0->unk_038[1] >= -0.5) {
            temp_v0->unk_038[1] -= 0.15;
        } else {
            temp_v0->unk_038[2] = 0.0f;
            temp_v0->unk_038[0] = 0.0f;
        }
    }
    temp_v0->unk_0B2[2] += temp_v0->unk_084[3];
    func_80087710(objectIndex);
    func_8008BF18(objectIndex);
}

void func_80077640(void) {
    s32 someIndex;
    s32 objectIndex;
    struct_80165C18_entry *object;

    for(someIndex = 0; someIndex < D_8018C630_SIZE; someIndex++) {
        objectIndex = D_8018C630[someIndex];
        if (objectIndex != -1) {
            object = &D_80165C18[objectIndex];
            if (object->unk_0A6 != 0) {
                func_80077450(objectIndex);
                func_80077584(objectIndex);
                if (object->unk_0A6 == 0) {
                    func_80072100(&D_8018C630[someIndex]);
                }
            }
        }
    }
}

void func_80077700(s32 objectIndex, Vec3f arg1, s32 arg2) {
    UNUSED s32 stackPadding1;
    UNUSED u16 stackPadding0;
    u16 temp_s0;
    u16 sp3E;
    u16 sp3C;

    func_800723A4(objectIndex, 0);
    D_80165C18[objectIndex].unk_0D5 = 7;
    D_80165C18[objectIndex].activeTLUT = (u32 *) D_0D028DD8;
    D_80165C18[objectIndex].tlutList = (u32 *) D_0D028DD8;
    D_80165C18[objectIndex].sizeScaling = 0.1f;
    D_80165C18[objectIndex].unk_044 = arg1[1];
    switch (gCurrentCourseId) {
        case COURSE_MARIO_RACEWAY:
            func_8008BD14(objectIndex, arg1[0], arg1[1] + 25.0, arg1[2], 0x00000014, 0x0000001E, 0x00000014);
            D_80165C18[objectIndex].unk_034 = 1.5f;
            D_80165C18[objectIndex].unk_038[1] = 1.5f;
            break;
        case COURSE_YOSHI_VALLEY:
            func_8008BD14(objectIndex, arg1[0], arg1[1] + 25.0, arg1[2], 0x00000014, 0x0000001E, 0x00000014);
            D_80165C18[objectIndex].unk_034 = 2.0f;
            D_80165C18[objectIndex].unk_038[1] = 2.0f;
            break;
        case COURSE_ROYAL_RACEWAY:
            func_8008BD14(objectIndex, arg1[0], arg1[1] + 30.0, arg1[2], 0x00000010, 0x00000028, 0x00000010);
            D_80165C18[objectIndex].unk_034 = 2.0f;
            D_80165C18[objectIndex].unk_038[1] = 2.0f;
            break;
        case COURSE_LUIGI_RACEWAY:
            func_8008BD14(objectIndex, arg1[0], arg1[1] + 25.0, arg1[2], 0x00000014, 0x0000001E, 0x00000014);
            D_80165C18[objectIndex].unk_034 = 1.5f;
            D_80165C18[objectIndex].unk_038[1] = 1.0f;
            break;
    }
    temp_s0 = random_int(0x0010U) << 0xC;
    sp3E = random_int(0x0010U) << 0xC;
    sp3C = random_int(0x0010U) << 0xC;
    func_8008B888(objectIndex, 0U, (arg2 * 0xFFFF) / 20, 0U);
    func_8008B8BC(objectIndex, temp_s0, sp3E, sp3C);
}

s32 func_80077A54(Vec3f arg0, s32 arg1) {
    s32 temp_v0;

    temp_v0 = func_80072044(D_8018C970, &D_80183E7C, D_8018C970_SIZE);
    if (temp_v0 != -1) {
        func_80077700(temp_v0, arg0, arg1);
    }
    return temp_v0;
}

void func_80077AB0(Vec3f arg0, UNUSED s32 arg1) {
    s32 var_s0;

    for (var_s0 = 0; var_s0 < D_8018C970_SPAWN_SIZE; var_s0++) {
        if (func_80077A54(arg0, var_s0) == -1) break;
    }
}

void func_80077B14(s32 arg0) {
    func_80072488(arg0);
    func_80086E70(arg0);
}

void func_80077B3C(s32 objectIndex) {
    struct_80165C18_entry *temp_v1;
    temp_v1 = &D_80165C18[objectIndex];

    switch (temp_v1->unk_0A6) {
        case 0:
            break;
        case 1:
            func_80077B14(objectIndex);
            break;
        case 2:
            if (temp_v1->unk_0AE == 0) {
                func_80072488(objectIndex);
            }
            break;
        case 3:
            func_80072428(objectIndex);
            break;
    }
}

void func_80077BCC(s32 objectIndex) {
    switch (D_80165C18[objectIndex].unk_0AE) {
        case 1:
            func_80087E08(objectIndex, D_80165C18[objectIndex].unk_038[1], 0.2f, D_80165C18[objectIndex].unk_034, (s16) (s32) D_80165C18[objectIndex].unk_0BE[1], 0x0000000A);
            break;
        case 2:
            if (func_80087B84(objectIndex, 0.4f, D_80165C18[objectIndex].unk_044) != 0) {
                func_80086F60(objectIndex);
            }
            break;
    }
    func_8008BF18(objectIndex);
    D_80165C18[objectIndex].unk_0B2[0] += 0x1000;
    D_80165C18[objectIndex].unk_0B2[1] += 0x1000;
}

void func_80077C9C(void) {
    s32 someIndex;
    s32 leafIndex;
    struct_80165C18_entry *object;

    for(someIndex = 0; someIndex < D_8018C970_SIZE; someIndex++) {
        leafIndex = D_8018C970[someIndex];
        if (leafIndex != -1) {
            object = &D_80165C18[leafIndex];
            if (object->unk_0A6 != 0) {
                func_80077B3C(leafIndex);
                func_80077BCC(leafIndex);
                if (object->unk_0A6 == 0) {
                    func_80072100(&D_8018C970[someIndex]);
                }
            }
        }
    }
}

#ifdef MIPS_TO_C
//generated by m2c commit 8267401fa4ef7a38942dcca43353cc1bcc6efabc
extern s32 D_8016559C;
extern ? D_8018CC80;
extern s16 D_8018D17C;
extern s32 D_8018D1F0;

void func_80077D5C(s32 arg0) {
    s32 temp_a0;
    s32 temp_a2;
    s32 var_a1;

    if ((D_8016559C == 0) && (temp_a2 = D_8018D1F0, var_a1 = 0, (temp_a2 > 0))) {
loop_3:
        D_8018D17C += 1;
        var_a1 += 1;
        if (D_8018D17C >= temp_a2) {
            D_8018D17C = 0;
        }
        temp_a0 = *((arg0 * 4) + &D_8018CC80 + (D_8018D17C * 4));
        if (D_80165C18[temp_a0].unk_0A6 == 0) {
            func_800723A4(temp_a0, 1);
            return;
        }
        if (var_a1 >= temp_a2) {

        } else {
            goto loop_3;
        }
    }
}
#else
GLOBAL_ASM("asm/non_matchings/code_80071F00/func_80077D5C.s")
#endif

void func_80077E20(s32 objectIndex) {
    struct_80165C18_entry *temp_v0;

    temp_v0 = &D_80165C18[objectIndex];
    temp_v0->activeTexture = D_0D0293D8;
    temp_v0->textureList = D_0D0293D8;
    // There's something up with the handling of D_0D005770 and the loading of 0x10 right here
    temp_v0->unk_074 = D_0D005770;
    temp_v0->textureHeight = 0x10;
    temp_v0->textureWidth = temp_v0->textureHeight;
    temp_v0->sizeScaling = 0.15f;
    func_800721C0(objectIndex, 0x00000010);
    func_80086EF0(objectIndex);
    temp_v0->unk_0A0 = 0x00FF;
    temp_v0->unk_0D5 = 0;
    temp_v0->unk_0A4 = 0;
    func_80072488(objectIndex);
}

extern f32 D_8018D1E8;
extern s16 D_8018D208;
extern s16 D_8018D210;
extern s16 D_8018D218;

void func_80077EB8(s32 objectIndex, u16 arg1, Camera *camera) {
    s16 temp_v0;

    temp_v0 = camera->rot[1] - arg1;
    if ((temp_v0 >= D_8018D210) || (D_8018D208 >= temp_v0)) {
        D_80165C18[objectIndex].unk_028[0] = D_8018D218 + (D_8018D1E8 * (f32) temp_v0);
        func_800721C0(objectIndex, 0x00000010);
        return;
    }
    func_800721E8(objectIndex, 0x00000010);
}

void func_80077F64(s32 objectIndex, Camera *camera) {

    f64 rand;

    switch (D_80165C18[objectIndex].unk_0AE) {                              /* irregular */
        case 1:
            D_80165C18[objectIndex].unk_0BE[1] = (camera->rot[1] + random_int(0x4000U)) - 0x2000;
            func_8008BAB4(objectIndex, 0x00B4, 0x0014U);
            rand = random_int(0x0064U);

            D_80165C18[objectIndex].unk_038[1] = (f32) (-0.75 - (f64) (f32) (rand * 0.01));
            D_80165C18[objectIndex].unk_028[0] = 0.0f;
            D_80165C18[objectIndex].unk_028[1] = 0.0f;
            func_80086FD4(objectIndex);
            return;
        case 2:
            func_80077EB8(objectIndex, D_80165C18[objectIndex].unk_0BE[1], camera);
            func_800877C4(objectIndex);
            func_8008BF18(objectIndex);
            func_8008BFC0(objectIndex);
            if (D_80165C18[objectIndex].pos[1] <= 0.0f) {
                func_80086FD4(objectIndex);
                return;
            }
        case 0:
            return;
        case 3:
            func_80086F60(objectIndex);
            break;
    }
}

void func_800780CC(s32 objectIndex, Camera *camera) {
    switch (D_80165C18[objectIndex].unk_0A6) {                              /* irregular */
    case 1:
        func_80077E20(objectIndex);
        return;
    case 2:
        func_80077F64(objectIndex, camera);
        if (D_80165C18[objectIndex].unk_0AE == 0) {
            func_80072488(objectIndex);
            return;
        }
    case 0:
        return;
    case 3:
        func_80072428(objectIndex);
        break;
    }
}

void func_80078170(s32 arg0, Camera *arg1) {
    s32 objectIndex;
    s32 i;

    func_80077D5C(arg0);
    for (i = 0; i < D_8018D1F0; i++) {
        objectIndex = D_8018CC80[arg0 + i];
        if (D_80165C18[objectIndex].unk_0A6 != 0) {
            func_800780CC(objectIndex, arg1);
        }
    }
}

void func_80078220(s32 objectIndex) {
    struct_80165C18_entry *temp_v0;

    temp_v0 = &D_80165C18[objectIndex];
    temp_v0->activeTexture = D_0D0293D8;
    temp_v0->textureList = D_0D0293D8;
    temp_v0->unk_074 = D_0D005770;
    temp_v0->sizeScaling = 0.15f;
    func_80086EF0(objectIndex);
    func_80072488(objectIndex);
}

void func_80078288(s32 objectIndex) {
    s16 sp3E;
    s16 sp3C;
    s16 sp3A;
    UNUSED u16 pad;
    u16 temp_t6;

    switch (D_80165C18[objectIndex].unk_0AE) {                              /* irregular */
    case 0:
        break;
    case 1:
        if (gGamestate != 9) {
            sp3A = ((gPlayerOneCopy->unk_094 / 18) * 216) / 2;
            sp3E = (random_int(0x000FU) - sp3A) + 0x2D;
            sp3C = random_int(0x012CU) + 0x1E;
            temp_t6 = camera1->rot[1] + ((s32) (random_int(0x3000U) - 0x1800) / (s16) ((sp3A / 15) + 1));
            D_80165C18[objectIndex].unk_010[0] = gPlayerOneCopy->pos[0] + (sins(temp_t6) * sp3C);
            D_80165C18[objectIndex].unk_010[1] = sp3E + gPlayerOneCopy->unk_074;
            D_80165C18[objectIndex].unk_010[2] = gPlayerOneCopy->pos[2] + (coss(temp_t6) * sp3C);
            D_80165C18[objectIndex].unk_0C4 = random_int(0x0400U) + 0x100;
            D_80165C18[objectIndex].unk_01C[0] = (f32) (((f32) random_int(0x0064U) * 0.03) + 2.0);
            D_80165C18[objectIndex].unk_038[1] = (f32) (-0.3 - (f64) (f32) (random_int(0x0032U) * 0.01));
            D_80165C18[objectIndex].unk_028[0] = 0.0f;
            D_80165C18[objectIndex].unk_028[1] = 0.0f;
            func_80086FD4(objectIndex);
        } else {
            sp3C = random_int(0x0064U) + 0x28;
            temp_t6 = camera1->rot[1] + random_int(0x3000U) - 0x1800;
            D_80165C18[objectIndex].unk_010[0] = camera1->pos[0] + (sins(temp_t6) * sp3C);
            D_80165C18[objectIndex].unk_010[1] = camera1->pos[1] + 45.0;
            D_80165C18[objectIndex].unk_010[2] = camera1->pos[2] + (coss(temp_t6) * sp3C);
            D_80165C18[objectIndex].unk_0C4 = random_int(0x0400U) + 0x100;
            D_80165C18[objectIndex].unk_01C[0] = (f32) (((f32) random_int(0x0064U) * 0.03) + 2.0);
            D_80165C18[objectIndex].unk_038[1] = (f32) (-0.6 - (f64) (f32) (random_int(0x0032U) * 0.01));
            D_80165C18[objectIndex].unk_028[0] = 0.0f;
            D_80165C18[objectIndex].unk_028[1] = 0.0f;
            func_80086FD4(objectIndex);
        }
        break;
    case 2:
        func_800877C4(objectIndex);
        D_80165C18[objectIndex].unk_0BE[0] += D_80165C18[objectIndex].unk_0C4;
        D_80165C18[objectIndex].unk_028[0] = sins(D_80165C18[objectIndex].unk_0BE[0]) * D_80165C18[objectIndex].unk_01C[0];
        func_8008BF18(objectIndex);
        if ((f64) D_80165C18[objectIndex].pos[1] <= 0.0) {
            func_80086FD4(objectIndex);
        }
        D_80165C18[objectIndex].unk_0B2[1] = func_800872D8(objectIndex, camera1);
        break;
    case 3:
        func_80086F60(objectIndex);
        break;
    }
}

void func_800786EC(s32 objectIndex) {
    switch (D_80165C18[objectIndex].unk_0A6) {                              /* irregular */
    case 0:
        break;
    case 1:
        func_80078220(objectIndex);
        break;
    case 2:
        func_80078288(objectIndex);
        if (D_80165C18[objectIndex].unk_0AE == 0) {
            func_80072488(objectIndex);
        }
        break;
    case 3:
        func_80072428(objectIndex);
        break;
    }
}

void func_80078790(void) {
    s32 someIndex;

    for (someIndex = 0; someIndex < NUM_SNOWFLAKES; someIndex++) {
        D_8018D174 += 1;
        if (D_8018D174 >= NUM_SNOWFLAKES) {
            D_8018D174 = 0;
        }
        if (D_80165C18[D_8018C1B0[D_8018D174]].unk_0A6 == 0) {
            func_800723A4(D_8018C1B0[D_8018D174], 1);
            break;
        }
    }
}

void func_80078838(void) {
    s32 someIndex;
    s32 snowflakeIndex;

    if (gGamestate != CREDITS_SEQUENCE) {
        func_80078790();
    } else {
        func_80078790();
        func_80078790();
        func_80078790();
        func_80078790();
    }
    for (someIndex = 0; someIndex < NUM_SNOWFLAKES; someIndex++) {
        snowflakeIndex = D_8018C1B0[someIndex];
        if (D_80165C18[snowflakeIndex].unk_0A6 != 0) {
            func_800786EC(snowflakeIndex);
        }
    }
}

extern f32 D_8018D1E8;
extern s16 D_8018D208;
extern s16 D_8018D210;
extern s16 D_8018D218;

void func_800788F8(s32 objectIndex, u16 rot, Camera *camera) {
    s16 temp_v0;

    temp_v0 = camera->rot[1] + rot;
    if ((temp_v0 >= D_8018D210) && (D_8018D208 >= temp_v0)) {
        D_80165C18[objectIndex].unk_09C = (D_8018D218 + (D_8018D1E8 * temp_v0));
        func_800721C0(objectIndex, 0x00000010);
        return;
    }
    func_800721E8(objectIndex, 0x00000010);
}

#ifdef MIPS_TO_C
//generated by mips_to_c commit 3c3b0cede1a99430bfd3edf8d385802b94f91307
//void func_800788F8(s32, u16, ?); // extern
//extern ? D_8018CC80;
//extern s32 D_8018D1F0;

void func_800789AC(s32 arg0, Camera *arg1, Vec3s *arg2) {
    //s32 temp_s0;
    //s32 *phi_s1;
    s32 i;

    //phi_s1 = &D_8018CC80[arg0];
    for (i = 0; i < D_8018D1F0; i++) {
        func_800788F8(D_8018CC80[arg0 + i], arg2[0][i], arg1);
        //*phi_s1 += 4;
    }

    // if (D_8018D1F0 > 0) {
    //     phi_s1 = (arg0 * 4) + &D_8018CC80;
    //     do {
    //         func_800788F8(*phi_s1, *((phi_s0 * 8) + arg2), arg1);
    //         temp_s0 = phi_s0 + 1;
    //         phi_s1 += 4;
    //         phi_s0 = temp_s0;
    //     } while (temp_s0 < D_8018D1F0);
    // }
}
#else
GLOBAL_ASM("asm/non_matchings/code_80071F00/func_800789AC.s")
#endif

typedef struct {
    Vec3su unk0;
    u16 pad;
    Vec3su unkA;
    u16 pad2;
} test;

typedef u16 testA[44][4];

void func_80078A44(s32 arg0, Camera *camera, u16 rot[][4]) {
  s32 temp_s0;
  s32 i;

    for (i = 0; i < D_8018D1F0; i++, arg0++) {
        temp_s0 = D_8018CC80[arg0];

        //                              rot[i][0] 
        func_800788F8(temp_s0, *(u16 *)(rot + i), camera);
        switch (i % 5U) {
            case 0:
                func_80073CB0(temp_s0, &D_80165C18[temp_s0].unk_0A0, 0x00000028, 0x000000B4, 0x000000FF, 0, -1);
                break;
            case 1:
                func_80073CB0(temp_s0, &D_80165C18[temp_s0].unk_0A0, 0x00000080, 0x000000FF, 0x000000FF, 0, -1);
                break;
            case 2:
                func_80073CB0(temp_s0, &D_80165C18[temp_s0].unk_0A0, 0x00000050, 0x000000C8, 0x000000FF, 0, -1);
                break;
            case 3:
                func_80073CB0(temp_s0, &D_80165C18[temp_s0].unk_0A0, 0, 0x0000009B, 0x000000FF, 0, -1);
                break;
            case 4:
                func_80073CB0(temp_s0, &D_80165C18[temp_s0].unk_0A0, 0x0000005A, 0x00000080, 0x000000FF, 0, -1);
                break;
        }
    }
}

UNUSED void func_80078C68() {

}

extern u16 D_800E6A38[];                                /* unable to generate initializer; const */
extern u16 D_800E6AA8[];                                /* unable to generate initializer; const */
extern u16 D_800E6B00[];                                /* unable to generate initializer; const */
extern u16 D_800E6B38[];                                /* unable to generate initializer; const */
extern u16 D_800E6BA8[];                                /* unable to generate initializer; const */
extern u16 D_800E6C10[];                                /* unable to generate initializer; const */
extern u16 D_800E6C80[][4];                                /* unable to generate initializer; const */
extern u16 D_800E6DE0[][4];                                /* unable to generate initializer; const */

extern s16 D_8018D200;
extern s16 D_8018D208;
extern s16 D_8018D210;
extern f32 D_8018D1E8;
extern s16 D_8018D218;

void func_80078C70(s32 arg0) {
    s32 sp1C;
    Camera *camera;

    if (D_801657C8 == 0) {
        switch (arg0) {                             /* switch 1 */
        case 0:                                     /* switch 1 */
            sp1C = 0;
            camera = camera1;
            D_8018D200 = gCameraZoom[0] + 40.0f;
            break;
        case 1:                                     /* switch 1 */
            sp1C = 0;
            camera = camera1;
            D_8018D200 = gCameraZoom[0] + 40.0f;
            break;
        case 2:                                     /* switch 1 */
            camera = camera2;
            sp1C = D_8018D1F0;
            D_8018D200 = gCameraZoom[1] + 40.0f;
            break;
        case 3:                                     /* switch 1 */
            sp1C = 0;
            camera = camera1;
            D_8018D200 = gCameraZoom[0] + 40.0f;
            break;
        case 4:                                     /* switch 1 */
            camera = camera2;
            sp1C = D_8018D1F0;
            D_8018D200 = gCameraZoom[1] + 40.0f;
            break;
        }

        D_8018D208 = ( (D_8018D200 / 2) * 0xB6) + 0x71C;
        D_8018D210 = (-(D_8018D200 / 2) * 0xB6) - 0x71C;
        D_8018D1E8 = 1.7578125 / D_8018D200;
        D_8018D218 = 0xA0;
        switch (gCurrentCourseId) {                          /* switch 2 */
            case 0:                                     /* switch 2 */
                func_800789AC(sp1C, camera, D_800E6A38);
                break;
            case 4:                                     /* switch 2 */
                func_800789AC(sp1C, camera, D_800E6AA8);
                break;
            case 5:                                     /* switch 2 */
                func_80078170(sp1C, camera);
                break;
            case 6:                                     /* switch 2 */
                func_800789AC(sp1C, camera, D_800E6B00);
                break;
            case 7:                                     /* switch 2 */
                func_800789AC(sp1C, camera, D_800E6B38);
                break;
            case 8:                                     /* switch 2 */
                func_800789AC(sp1C, camera, D_800E6A38);
                break;
            case 9:                                     /* switch 2 */
                func_800789AC(sp1C, camera, D_800E6AA8);
                break;
            case 10:                                    /* switch 2 */
                func_80078A44(sp1C, camera, D_800E6C80);
                break;
            case 11:                                    /* switch 2 */
                func_800789AC(sp1C, camera, D_800E6C10);
                break;
            case 12:                                    /* switch 2 */
                func_800789AC(sp1C, camera, D_800E6BA8);
                break;
            case 13:                                    /* switch 2 */
                func_80078A44(sp1C, camera, D_800E6C80);
                break;
            case 14:                                    /* switch 2 */
                func_80078A44(sp1C, camera, D_800E6DE0);
                break;
        }
    }
}

void func_80078F64(void) {
    switch (gScreenModeSelection) {                              /* irregular */
    case SCREEN_MODE_1P:
        func_800723A4(D_80183DB8[0], 1);
        break;
    case SCREEN_MODE_2P_SPLITSCREEN_VERTICAL:
        func_800723A4(D_80183DB8[0], 1);
        func_800723A4(D_80183DB8[1], 1);
        break;
    case SCREEN_MODE_2P_SPLITSCREEN_HORIZONTAL:
        func_800723A4(D_80183DB8[0], 1);
        func_800723A4(D_80183DB8[1], 1);
        break;
    case SCREEN_MODE_3P_4P_SPLITSCREEN:
        func_800723A4(D_80183DB8[0], 1);
        func_800723A4(D_80183DB8[1], 1);
        func_800723A4(D_80183DB8[2], 1);
        func_800723A4(D_80183DB8[3], 1);
        break;
    }
}

void func_80079054(s32 arg0) {
    func_800723A4(D_80183DB8[arg0], 2);
}

void func_80079084(s32 arg0) {
    func_800723A4(D_80183DB8[arg0], 4);
}

void func_800790B4(s32 arg0) {
    func_800723A4(D_80183DB8[arg0], 5);
}

void func_800790E4(s32 arg0) {
    func_800723A4(D_80183DB8[arg0], 6);
}

void func_80079114(s32 objectIndex, s32 arg1, s32 arg2) {
    s32 a;
    if (D_80165C18[objectIndex].unk_0A6 >= 2) {
        if ((u8)D_80165C18[objectIndex].unk_0D8 == 1) {
            if (arg1 == 0) {
                func_80074894(objectIndex, D_8018C028);
                return;
            }
            a = D_80183DB8[0];
            D_80165C18[objectIndex].activeTLUT = D_80165C18[a].activeTLUT;
            D_80165C18[objectIndex].activeTexture = D_80165C18[a].activeTexture;
            if (0) { }
            return;
        }
        switch (arg2) {
            case 0:
                func_800748F4(objectIndex, D_8018C028);
                break;
            case 1:
                func_800748C4(objectIndex, D_8018C028);
                break;
            case 2:
                func_80074894(objectIndex, D_8018C028);
                break;
        }
    }
}

void func_800791F0(s32 objectIndex, s32 playerId) {
    Player *temp_v1 = &gPlayerOne[playerId];

    if ((D_80165C18[objectIndex].unk_0D8 != 3) && (D_80165C18[objectIndex].unk_0D8 != 7)) {
        func_800722CC(objectIndex, 1);
        if (gCurrentCourseId == 0x000C) {
            temp_v1->unk_0CA &= 0xFFEF;
        }
    } else {
        // ?????
    }
    if (gCurrentCourseId == 0x000C) {
        func_800722CC(objectIndex, 0x00000010);
        temp_v1->unk_0CA &= 0xFFDF;
    }
    func_800C9018(playerId, 0x0100FA28);
}

extern u8 *D_0F05EB50;
extern s16 D_801656F0;
extern s32 D_8018D168;
extern s32 D_8018D180;

void func_800792D8(s32 objectIndex, s32 arg1) {
    if (arg1 == 0) {
        D_801656F0 = 0;
        D_8018D168 = 0;
    }
    func_80073444(objectIndex, (u8 *) gTLUTLakituCountdown, (u8 *) &D_0F05EB50, 0x38U, (u16) 0x00000048);
    D_80165C18[objectIndex].unk_074 = (Vtx *) D_0D005EB0;
    D_80165C18[objectIndex].sizeScaling = 0.15f;
    func_800721E8(objectIndex, 0x00000010);
    func_80072488(objectIndex);
    D_80165C18[objectIndex].unk_048 = D_8018D180;
}

extern s16 D_801656F0;
extern s32 D_8018D160;
extern s32 D_8018D168;
extern u16 D_800E67B8[][4]; // static

void func_80079380(s32 objectIndex, s32 arg1) {
    UNUSED s32 pad;
    switch (D_80165C18[objectIndex].unk_0A6) {
        case 0:
            break;
        case 1:
            func_800792D8(objectIndex, arg1);
            break;
        case 2:
            func_8007278C(objectIndex, D_80165C18[objectIndex].unk_048);
            if ((D_80165C18[objectIndex].unk_050 == 0x00000055) && (D_8018EDF3 == 3) && (arg1 == 0)) {
                D_8018D168 = 1;
            }
            break;
        case 3:
            func_800721C0(objectIndex, 0x00000010);
            func_80086F10(objectIndex, 1, D_800E67B8);
            func_80072488(objectIndex);
            break;
        case 4:
            if ((func_8007278C(objectIndex, 0x0000001E) != 0) && (D_8018EDF3 != 3) && (arg1 == 0)) {
                D_8018D168 = 1;
            }
            break;
        case 5:
            func_8007278C(objectIndex, 0x0000001E);
            break;
        case 6:
            func_80072E54(objectIndex, 1, 7, 1, 2, 0);
            break;
        case 7:
            if (func_8007278C(objectIndex, 0x00000014) != 0) {
                D_80165C18[objectIndex].tlutList += 0x200;
                if (arg1 == 0) {
                    play_sound2(SOUND_ACTION_COUNTDOWN_LIGHT);
                }
            }
            break;
        case 8:
            func_80072E54(objectIndex, 8, 0x0000000F, 1, 6, 0);
            break;
        case 9:
            if ((func_8007278C(objectIndex, 8) != 0) && (arg1 == 0)) {
                play_sound2(SOUND_ACTION_COUNTDOWN_LIGHT);
            }
            break;
        case 10:
            if ((func_80072E54(objectIndex, 0x00000010, 0x00000017, 1, 6, 0) != 0) && (arg1 == 0)) {
                D_801656F0 = 1;
            }
            break;
        case 11:
            if (func_8007278C(objectIndex, 8) != 0) {
                D_80165C18[objectIndex].tlutList += 0x200;
                if (arg1 == 0) {
                    play_sound2(SOUND_ACTION_GREEN_LIGHT);
                }
            }
            break;
        case 12:
            func_80072E54(objectIndex, 0x00000018, 0x0000001B, 1, 6, 0);
            break;
        case 13:
            if (arg1 == 0) {
                func_800729EC(objectIndex);
                D_8018D160 = 1;
                break;
            }
            func_80072488(objectIndex);
            break;
        case 14:
            func_8007278C(objectIndex, 0x00000078);
            break;
        case 15:
            func_80072428(objectIndex);
            break;
    }
}

extern u8 *D_0F07E350;
//extern s32 D_8018C028;
extern u16 D_800E6834[][4]; // static

void func_8007963C(s32 objectIndex, s32 playerIndex) {
    struct_80165C18_entry *temp_v0;

    func_800791F0(objectIndex, playerIndex);
    func_80073444(objectIndex, gTLUTLakituCheckeredFlag, (u8 *) &D_0F07E350, 0x48U, (u16) 0x00000038);
    temp_v0 = &D_80165C18[objectIndex];
    temp_v0->activeTexture = D_8018C028;
    temp_v0->unk_074 = D_0D006730;
    temp_v0->pos[2] = 5000.0f;
    temp_v0->pos[1] = 5000.0f;
    temp_v0->pos[0] = 5000.0f;
    temp_v0->sizeScaling = 0.15f;
    func_80086F10(objectIndex, 2, D_800E6834);
    func_800721E8(objectIndex, 0x00000010);
    func_80072488(objectIndex);
}

void func_80079700(s32 objectIndex, s32 playerIndex) {
    switch (D_80165C18[objectIndex].unk_0A6) {
        case 0:
            break;
        case 1:
            func_8007963C(objectIndex, playerIndex);
            break;
        case 2:
            func_800721C0(objectIndex, 0x00000010);
            func_80072488(objectIndex);
            break;
        case 3:
            func_80072E54(objectIndex, 0, 0x0000001F, 1, 2, -1);
            break;
        case 4:
            func_80072428(objectIndex);
            break;
    }
}

void func_800797AC(s32 playerId) {
    s32 objectIndex;
    Player *player;

    objectIndex = D_80183DB8[playerId];
    player = &gPlayerOne[playerId];
    if ((gCurrentCourseId == COURSE_SHERBET_LAND) && (player->unk_0CA & 1)) {
        func_800723A4(objectIndex, 7);
        player->unk_0CA |= 0x10;
    } else {
        func_800723A4(objectIndex, 3);
    }
    func_800722A4(objectIndex, 1);
}

void func_80079860(s32 playerId) {
    s32 objectIndex;
    Player *player;

    objectIndex = D_80183DB8[playerId];
    player = &gPlayerOne[playerId];
    if ((func_80072354(objectIndex, 1) != 0) &&
        (
            ((func_802ABDF4(player->unk_110.unk3A) != 0) && (player->unk_110.unk3C[2] <= 3.0f)) ||
            (player->unk_0CA & 1) ||
            ((player->unk_0F8 == 0x00FD) && !(player->unk_0BC & 8))
        )
        ) {
        func_80090778(player);
        func_800797AC(playerId);
    }
}

void func_8007993C(s32 objectIndex, Player *player) {
    if (player->unk_0CA & 4) {
        func_800722A4(objectIndex, 2);
        D_80165C18[objectIndex].unk_0A0 = player->unk_0C6;
        return;
    }
    func_800722CC(objectIndex, 2);
}

extern u8 D_0F0CCF50;

void func_800799A8(s32 objectIndex, s32 arg1) {
    func_800791F0(objectIndex, arg1);
    func_80073444(objectIndex, gTLUTLakituFishing, &D_0F0CCF50, 0x38U, (u16) 0x00000048);
    D_80165C18[objectIndex].unk_074 = D_0D005F30;
    D_80165C18[objectIndex].sizeScaling = 0.15f;
    func_80086E70(objectIndex);
    func_800721E8(objectIndex, 0x00000010);
    func_80073720(objectIndex);
    func_80072488(objectIndex);
    func_800C8F80((u8)arg1, 0x0100FA28);
}

void func_80079A5C(s32 objectIndex, UNUSED Player *player) {
    switch (D_80165C18[objectIndex].unk_0AE) {
    case 0:
        break;
    case 1:
        D_80165C18[objectIndex].unk_010[2] = 0.0f;
        D_80165C18[objectIndex].unk_010[1] = 0.0f;
        D_80165C18[objectIndex].unk_010[0] = 0.0f;
        D_80165C18[objectIndex].unk_028[2] = 0.0f;
        D_80165C18[objectIndex].unk_028[0] = 0.0f;
        D_80165C18[objectIndex].unk_028[1] = 80.0f;
        func_80086FD4(objectIndex);
        break;
    case 2:
        if (f32_step_down_towards(&D_80165C18[objectIndex].unk_028[1], 5.0f, 1.0f) != 0) {
            func_80086F60(objectIndex);
        }
        break;
    case 3:
        if (f32_step_up_towards(&D_80165C18[objectIndex].unk_028[1], 100.0f, 1.0f) != 0) {
            func_80086F60(objectIndex);
        }
        break;
    }
}

void func_80079B40(s32 objectIndex, s32 playerId) {
    Player *player = &gPlayerOne[playerId];

    switch (D_80165C18[objectIndex].unk_0A6) {                              /* switch 1; irregular */
        case 0:                                         /* switch 1 */
            break;
        case 1:                                         /* switch 1 */
            func_800799A8(objectIndex, playerId);
            break;
        case 2:                                         /* switch 1 */
            func_800721C0(objectIndex, 0x00000010);
            func_800736E0(objectIndex);
            func_80072488(objectIndex);
            break;
        case 3:                                         /* switch 1 */
            func_800730BC(objectIndex, 0, 3, 1, 2, -1);
            break;
    }
    switch (D_80165C18[objectIndex].unk_0D6) {
        case 0:
            break;
        case 1:
            if (func_80086FA4(objectIndex) != 0) {
                func_80073654(objectIndex);
            }
            break;
        case 2:
            func_80090868(player);
            func_80073654(objectIndex);
            break;
        case 3:
            if (!(player->unk_0CA & 2)) {
                func_80086EAC(objectIndex, 0, 3);
                func_80073654(objectIndex);
            }
            break;
        case 4:
            if (func_80086FA4(objectIndex) != 0) {
                func_80073654(objectIndex);
            }
            break;
        case 5:
            func_800722CC(objectIndex, 1);
            func_800C9018((u8) playerId, 0x0100FA28);
            func_80072428(objectIndex);
            func_80073720(objectIndex);
            break;
    }
    if (D_80165C18[objectIndex].unk_0A6 >= 2) {
        func_8007993C(objectIndex, player);
    }
    func_80079A5C(objectIndex, player);
}

void func_80079D44(s32 objectIndex, s32 playerId) {

    Player *temp_s1;

    temp_s1 = &gPlayerOne[playerId];
    switch (D_80165C18[objectIndex].unk_0A6) {                              /* switch 1; irregular */
        case 0:                                         /* switch 1 */
            break;
        case 1:                                         /* switch 1 */
            func_800799A8(objectIndex, playerId);
            break;
        case 2:                                         /* switch 1 */
            func_800721C0(objectIndex, 0x00000010);
            func_800736E0(objectIndex);
            temp_s1->unk_0CA |= 0x80;
            func_80072488(objectIndex);
            break;
        case 3:                                         /* switch 1 */
            func_800730BC(objectIndex, 0, 3, 1, 2, -1);
            break;
    }
    switch (D_80165C18[objectIndex].unk_0D6) {
        case 1:
            if (func_80086FA4(objectIndex) != 0) {
                func_800C9060((u8) playerId, 0x1900A055U);
                func_80073654(objectIndex);
            }
            break;
        case 2:
            func_80090868(temp_s1);
            func_800722A4(objectIndex, 4);
            func_80073654(objectIndex);
            break;
        case 3:
            if ((temp_s1->unk_0F8 == 9) && !(temp_s1->unk_0CA & 1) && ((f64) temp_s1->unk_110.unk3C[2] <= 30.0)) {
                func_800722A4(objectIndex, 8);
            }
            if (!(temp_s1->unk_0CA & 2)) {
                func_80086EAC(objectIndex, 0, 3);
                func_80073654(objectIndex);
            }
            break;
        case 4:
            func_8007375C(objectIndex, 0x0000001E);
            break;
        case 5:
            temp_s1->unk_0CA &= 0xFF7F;
            func_800722A4(objectIndex, 0x00000010);
            func_800722A4(objectIndex, 0x00000020);
            func_800722CC(objectIndex, 4);
            func_800722CC(objectIndex, 8);
            func_80073654(objectIndex);
            func_800C9060((u8) playerId, 0x1900A056U);
            break;
        case 6:
            if (func_8007375C(objectIndex, 0x000000A0) != 0) {
                func_800722CC(objectIndex, 0x00000010);
                temp_s1->unk_0CA &= 0xFFEF;
                temp_s1->unk_0CA |= 0x20;
            }
            break;
        case 7:
            func_8007375C(objectIndex, 0x0000003C);
            break;
        case 8:
            func_80073720(objectIndex);
            func_80072428(objectIndex);
            temp_s1->unk_0CA &= 0xFFDF;
            func_800722CC(objectIndex, 1);
            func_800C9018((u8) playerId, 0x0100FA28);
            break;
    }

    if (D_80165C18[objectIndex].unk_0A6 >= 2) {
        func_8007993C(objectIndex, temp_s1);
    }
    func_80079A5C(objectIndex, temp_s1);
}

extern u8 *D_0F09DB50[];
extern u16 D_800E694C[];

void func_8007A060(s32 objectIndex, s32 playerIndex) {
    struct_80165C18_entry *temp_v0;

    func_800791F0(objectIndex, playerIndex);
    func_80073444(objectIndex, gTLUTLakituSecondLap, (u8 *) D_0F09DB50, 0x48U, (u16) 0x00000038);
    temp_v0 = &D_80165C18[objectIndex];
    temp_v0->activeTexture = D_8018C028;
    temp_v0->unk_074 = D_0D006730;
    temp_v0->pos[2] = 5000.0f;
    temp_v0->pos[1] = 5000.0f;
    temp_v0->pos[0] = 5000.0f;
    temp_v0->sizeScaling = 0.15f;
    func_800721E8(objectIndex, 0x00000010);
    func_80086F10(objectIndex, 5, &D_800E694C);
    func_80072488(objectIndex);
}

void func_8007A124(s32 objectIndex, s32 playerIndex) {
    switch (D_80165C18[objectIndex].unk_0A6) {
        case 0:
            break;
        case 1:
            func_8007A060(objectIndex, playerIndex);
            break;
        case 2:
            func_800721C0(objectIndex, 0x00000010);
            func_80072488(objectIndex);
            break;
        case 3:
            func_8007278C(objectIndex, 0x00000014);
            break;
        case 4:
            func_80072E54(objectIndex, 0, 0x0000000F, 1, 2, 1);
            break;
        case 5:
            func_8007278C(objectIndex, 0x0000003C);
            break;
        case 6:
            func_80072F88(objectIndex, 0x0000000F, 0, 1, 2, 1);
            break;
        case 7:
            if (D_80165C18[objectIndex].unk_0AE == 0) {
                func_80072428(objectIndex);
            }
            break;
    }
}

extern u8 *D_0F0AD750;

void func_8007A228(s32 objectIndex, s32 playerIndex) {
    struct_80165C18_entry *temp_v0;

    func_800791F0(objectIndex, playerIndex);
    func_80073444(objectIndex, gTLUTLakituFinalLap, (u8 *)&D_0F0AD750, 0x48U, (u16) 0x00000038);
    temp_v0 = &D_80165C18[objectIndex];
    temp_v0->activeTexture = D_8018C028;
    temp_v0->unk_074 = D_0D006730;
    temp_v0->pos[2] = 5000.0f;
    temp_v0->pos[1] = 5000.0f;
    temp_v0->pos[0] = 5000.0f;
    temp_v0->sizeScaling = 0.15f;
    func_800721E8(objectIndex, 0x00000010);
    func_80086F10(objectIndex, 5, &D_800E694C);
    func_80072488(objectIndex);
}

void func_8007A2EC(s32 objectIndex, s32 playerIndex) {
    switch (D_80165C18[objectIndex].unk_0A6) {
        case 0:
            break;
        case 1:
            func_8007A228(objectIndex, playerIndex);
            break;
        case 2:
            func_800721C0(objectIndex, 0x00000010);
            func_80072488(objectIndex);
            break;
        case 3:
            func_8007278C(objectIndex, 0x00000014);
            break;
        case 4:
            func_80072E54(objectIndex, 0, 0x0000000F, 1, 2, 1);
            break;
        case 5:
            func_8007278C(objectIndex, 0x0000003C);
            break;
        case 6:
            func_80072F88(objectIndex, 0x0000000F, 0, 1, 2, 1);
            break;
        case 7:
            if (D_80165C18[objectIndex].unk_0AE == 0) {
                func_80072428(objectIndex);
            }
            break;
    }
}

extern u8 D_0F0BD350[];
extern u16 D_800E69B0[][4]; // static?

void func_8007A3F0(s32 objectIndex, s32 arg1) {
    f32 var = 5000.0f;
    func_800791F0(objectIndex, arg1);
    func_80073444(objectIndex, gTLUTLakituReverse, D_0F0BD350, 0x48U, (u16) 0x00000038);
    D_80165C18[objectIndex].activeTexture = D_8018C028;
    D_80165C18[objectIndex].unk_074 = D_0D006730;
    D_80165C18[objectIndex].pos[2] = var;
    D_80165C18[objectIndex].pos[1] = var;
    D_80165C18[objectIndex].pos[0] = var;
    D_80165C18[objectIndex].sizeScaling = 0.15f;
    func_800721E8(objectIndex, 0x00000010);
    func_80086F10(objectIndex, 6, D_800E69B0);
    D_80165C18[objectIndex].unk_0D6 = 0;
    func_80072488(objectIndex);
    func_800C8F80((u8)arg1, 0x0100FA28);
}

extern u16 D_800E69F4[][4]; // static?

void func_8007A4D4(s32 objectIndex, s32 playerId) {
    Player *sp2C = &gPlayerOne[playerId];

    switch (D_80165C18[objectIndex].unk_0A6) {
        case 0:
            break;
        case 1:
            func_8007A3F0(objectIndex, playerId);
            break;
        case 2:
            func_800721C0(objectIndex, 0x00000010);
            D_80165C18[objectIndex].unk_0D6 = 1;
            func_80072488(objectIndex);
            break;
        case 3:
            func_800730BC(objectIndex, 0, 0x0000000F, 1, 2, -1);
            break;
        case 4:
            func_80072428(objectIndex);
            break;
    }
    switch (D_80165C18[objectIndex].unk_0D6) {                              /* switch 1; irregular */
        case 1:                                         /* switch 1 */
            if ((D_80165C18[objectIndex].unk_0A6 >= 3) && (!(sp2C->unk_0BC & 0x400000))) {
                func_80086F10(objectIndex, 6, D_800E69F4);
                D_80165C18[objectIndex].unk_0D6 = 2;
                D_80165C18[objectIndex].unk_04C = 0x00000050;
                func_800C9018((u8) playerId, 0x0100FA28);
                return;
            }
            return;
        case 2:                                         /* switch 1 */
            D_80165C18[objectIndex].unk_04C--;
            if (D_80165C18[objectIndex].unk_04C == 0) {
                func_80072488(objectIndex);
                D_80165C18[objectIndex].unk_0D6 = 0;
            }
            break;
    }
}

void func_8007A66C(s32 objectIndex, Player *player, Camera *camera) {
    u16 temp_t8;

    temp_t8 = 0x8000 - camera->rot[1];
    D_80165C18[objectIndex].pos[0] = (player->pos[0] + (coss(temp_t8) * (D_80165C18[objectIndex].unk_010[0] + D_80165C18[objectIndex].unk_028[0]))) - (sins(temp_t8) * (D_80165C18[objectIndex].unk_010[2] + D_80165C18[objectIndex].unk_028[2]));
    D_80165C18[objectIndex].pos[1] = player->unk_074 + D_80165C18[objectIndex].unk_010[1] + D_80165C18[objectIndex].unk_028[1];
    D_80165C18[objectIndex].pos[2] = (player->pos[2] + (sins(temp_t8) * (D_80165C18[objectIndex].unk_010[0] + D_80165C18[objectIndex].unk_028[0]))) + (coss(temp_t8) * (D_80165C18[objectIndex].unk_010[2] + D_80165C18[objectIndex].unk_028[2]));
}

void func_8007A778(s32 objectIndex, Player *player, Camera *camera) {
    u16 temp_t8;

    temp_t8 = 0x8000 - camera->rot[1];
    D_80165C18[objectIndex].pos[0] = (player->pos[0] + (coss(temp_t8) * (D_80165C18[objectIndex].unk_010[0] + D_80165C18[objectIndex].unk_028[0]))) - (sins(temp_t8) * (D_80165C18[objectIndex].unk_010[2] + D_80165C18[objectIndex].unk_028[2]));
    D_80165C18[objectIndex].pos[1] = player->pos[1] + D_80165C18[objectIndex].unk_010[1] + D_80165C18[objectIndex].unk_028[1];
    D_80165C18[objectIndex].pos[2] = (player->pos[2] + (sins(temp_t8) * (D_80165C18[objectIndex].unk_010[0] + D_80165C18[objectIndex].unk_028[0]))) + (coss(temp_t8) * (D_80165C18[objectIndex].unk_010[2] + D_80165C18[objectIndex].unk_028[2]));
}

UNUSED void func_8007A884(void) {

}

void func_8007A88C(s32 playerId) {
    s32 objectIndex;
    Player *player;

    objectIndex = D_80183DB8[playerId];
    player = &gPlayerOne[playerId];

    if ((D_80165C18[objectIndex].unk_0A6 == 0) && (player->unk_0BC & 0x400000)) {
        func_800790E4(playerId);
    }
}

void func_8007A910(s32 arg0) {
    if (D_801657B4 == 0) {
        func_8007A88C(arg0);
    }
    func_80079860(arg0);
}

void func_8007A948(s32 arg0) {
    s32 temp_s0 = D_80183DB8[arg0];

    switch (D_80165C18[temp_s0].unk_0D8) {
        case 0:
            break;
        case 1:
            func_80079380(temp_s0, arg0);
            func_8008BFFC(temp_s0);
            break;
        case 2:
            func_80079700(temp_s0, arg0);
            func_8008BFFC(temp_s0);
            break;
        case 3:
            func_80079B40(temp_s0, arg0);
            break;
        case 4:
            func_8007A124(temp_s0, arg0);
            func_8008BFFC(temp_s0);
            break;
        case 5:
            func_8007A2EC(temp_s0, arg0);
            func_8008BFFC(temp_s0);
            break;
        case 6:
            func_8007A4D4(temp_s0, arg0);
            func_8008BFFC(temp_s0);
            break;
        case 7:
            func_80079D44(temp_s0, arg0);
            break;
    }
}

void func_8007AA44(s32 arg0) {
    s32 temp_s0;

    func_8007A910(arg0);
    temp_s0 = D_80183DB8[arg0];
    D_8018C028 = D_80183FA8[arg0];
    switch (D_80165C18[temp_s0].unk_0D8) {
    case 1:
        func_80079114(temp_s0, arg0, 2);
        func_8007A66C(temp_s0, D_8018CF1C, D_8018CF14);
        break;
    case 2:
        func_80079114(temp_s0, arg0, 0);
        func_8007A66C(temp_s0, D_8018CF1C, D_8018CF14);
        break;
    case 3:
        func_80079114(temp_s0, arg0, 0);
        func_8007A778(temp_s0, D_8018CF1C, D_8018CF14);
        break;
    case 4:
        func_80079114(temp_s0, arg0, 0);
        func_8007A66C(temp_s0, D_8018CF1C, D_8018CF14);
        break;
    case 5:
        func_80079114(temp_s0, arg0, 0);
        func_8007A66C(temp_s0, D_8018CF1C, D_8018CF14);
        break;
    case 6:
        func_80079114(temp_s0, arg0, 0);
        func_8007A66C(temp_s0, D_8018CF1C, D_8018CF14);
        break;
    case 7:
        func_80079114(temp_s0, arg0, 0);
        func_8007A778(temp_s0, D_8018CF1C, D_8018CF14);
        break;
    case 0:
    default:
        break;
    }
}

void func_8007ABFC(s32 playerId, s32 arg1) {
    s32 itemWindow;

    if (D_8018CA70[playerId].raceCompleteBool == 0) {
        itemWindow = gItemWindowObjectByPlayerId[playerId];
        if (func_80072354(itemWindow, 4) != 0) {
            func_800723A4(itemWindow, 0);
            if (arg1 != 0) {
                D_8018CA70[playerId].itemOverride = arg1;
            }
        }
        func_800C9060(playerId, 0x19008406U);
    }
}

void func_8007AC9C(s32 playerId) {
    UNUSED s32 pad;
    Player *player;
    s32 objectIndex;
    struct_80165C18_entry *itemWindow;

    player = &gPlayerOne[playerId];
    objectIndex = gItemWindowObjectByPlayerId[playerId];
    itemWindow = &D_80165C18[objectIndex];
    if (itemWindow->unk_0A4 == 0x000F) {
        if (func_80072354(objectIndex, 2) != 0) {
            func_800722A4(objectIndex, 2);
            itemWindow->unk_098 = 0x0258;
            func_800726CC(objectIndex, 0x00000032);
        }
        if (itemWindow->unk_098 == 0) {
            func_800722CC(objectIndex, 2);
            player->unk_010 = 0;
            itemWindow->unk_0A4 = 0;
            func_80072388(objectIndex, 0);
            func_800726CC(objectIndex, 9);
        }
    } else {
        player->unk_010 = 0;
        itemWindow->unk_0A4 = 0;
        func_80072388(objectIndex, 0);
    }
}

extern u8 sRandomItemIndex;
extern u8 gControllerRandom;
extern s32 gRaceFrameCounter;

// todo: Cleanup this function to use array access and struct if possible.
u8 gen_random_item(s16 arg0, s16 arg1)
{
    u16 rand = random_int(100);
    u8 *curve;
    u8 randomItem;

    // sRandomItemIndex not initialized for further randomness?
    sRandomItemIndex = ((u32) rand + (sRandomItemIndex + gControllerRandom) + gRaceFrameCounter) % 100U;

    if (gModeSelection == VERSUS) {
        switch (gPlayerCountSelection1) {
            case TWO_PLAYERS_SELECTED:
                curve = segmented_to_virtual((void *) gVersus2PlayerItemCurve);
                break;
            case THREE_PLAYERS_SELECTED:
                curve = segmented_to_virtual((void *) gVersus3PlayerItemCurve);
                break;
            case FOUR_PLAYERS_SELECTED:
                curve = segmented_to_virtual((void *) gVersus4PlayerItemCurve);
                break;
        }
        randomItem = *((arg0 * 100) + curve + sRandomItemIndex);

    } else if (gModeSelection == BATTLE) {
        curve = segmented_to_virtual((void *) gBattleItemCurve);
        randomItem = curve[sRandomItemIndex];
    } else { // GP Mode
        if (arg1 == 0) {
            curve = segmented_to_virtual((void *) gGrandPrixHumanItemCurve);
        }
        else {
            curve = segmented_to_virtual((void *) gGrandPrixCPUItemCurve);
        }
        randomItem =  *((arg0 * 100) + curve + sRandomItemIndex);
    }
    return randomItem;
}

u8 func_8007AF40(UNUSED s16 arg0, s16 arg1) {
    return gen_random_item(arg1, 0);
}

u8 func_8007AF78(UNUSED s32 arg0, s16 arg1) {
    return gen_random_item(arg1, 1);
}

s16 func_8007AFB0(s32 objectIndex, s32 arg1) {
    UNUSED s32 pad[3];
    s16 randomItem;

    randomItem = func_8007AF40(gLapCountByPlayerId[arg1], gGPCurrentRaceRankByPlayerId[arg1]);
    
    if (D_8018CA70[arg1].itemOverride != 0) {
        randomItem = (s16) D_8018CA70[arg1].itemOverride;
        D_8018CA70[arg1].itemOverride = 0;
    }

    func_800729B4(objectIndex, (s32) randomItem);

    return randomItem;
}

#ifdef NON_MATCHING
// https://decomp.me/scratch/yWKlx
// More stupid register allocation nonsense

s32 func_8007B040(s32 objectIndex, s32 playerId) {
    s16 stackPadding;
    s32 temp_v1;
    s32 var_a3;
    s32 var_t3;
    s32 temp_a0;
    s32 var_v1;
    s32 sp50[4];
    s32 sp40[4];
    s32 var_v1_2;
    Player *sp38;
    s16 temp_a1;

    var_a3 = 0;
    var_t3 = 0;
    if (gModeSelection == GRAND_PRIX) {
        if (random_int(0x0064U) < 0x51) {
            var_v1 = func_8007AF40(gLapCountByPlayerId[playerId], gGPCurrentRaceRankByPlayerId[playerId]);
        } else {
            var_v1 = 0;
            func_800C9060(playerId, 0x1900A058U);
        }
        var_t3 = 1;
        D_80165C18[objectIndex].unk_0A2 = var_v1;
        D_80165C18[objectIndex].unk_0D2 = var_v1;
    } else {
        for (var_v1_2 = 0; var_v1_2 < gPlayerCountSelection1; var_v1_2++) {
            temp_a0 = gItemWindowObjectByPlayerId[var_v1_2];
            if (var_v1_2 != playerId) {
                if (D_80165C18[temp_a0].unk_0A4 != 0) {
                    sp50[var_a3] = var_v1_2;
                    sp40[var_a3] = D_80165C18[temp_a0].unk_0A4;
                    var_a3 += 1;
                }
            }
        }
        if (var_a3 != 0) {
            var_v1 = random_int(var_a3);
            temp_v1 = sp50[var_v1];
            D_80165C18[objectIndex].unk_0D1 = temp_v1;
            temp_a1 = sp40[var_v1];
            D_80165C18[objectIndex].unk_0A2 = temp_a1;
            D_80165C18[objectIndex].unk_0D2 = temp_a1;
            temp_a0 = gItemWindowObjectByPlayerId[temp_v1];
            sp38 = &gPlayerOne[temp_v1];
            func_800722A4(temp_a0, 1);
            D_80165C18[temp_a0].unk_0A4 = 0;
            sp38->unk_010 = 0;
            if (func_80072320(temp_a0, 2) != 0) {
                func_800722CC(temp_a0, 2);
                D_80165C18[temp_a0].unk_098 = 0;
            }
            var_t3 = 1;
        }
    }
    return var_t3;
}
#else
GLOBAL_ASM("asm/non_matchings/code_80071F00/func_8007B040.s")
#endif

#ifdef MIPS_TO_C
//generated by m2c commit eefca95b040d7ee0c617bc58f9ac6cd1cf7bce87 on Aug-10-2023
extern s8 D_80165888;
extern s16 D_8018CAB8;

void func_8007B254(s32 objectIndex, u8 arg1) {
    struct_80165C18_entry *sp18;
    s8 temp_v1;
    struct_80165C18_entry *temp_v0;

    func_80072428(objectIndex);
    temp_v0 = &D_80165C18[objectIndex];
    temp_v0->unk_0A6 = 2;
    temp_v0->unk_0A4 = 0;
    temp_v0->tlutList = (u8 *) gTLUTItemWindowNone;
    temp_v0->textureList = gTextureItemWindowNone;
    temp_v0->textureWidth = 0x28;
    temp_v0->textureHeight = 0x20;
    temp_v0->unk_04C = 0x00000032;
    temp_v0->unk_0D6 = 1;
    temp_v0->unk_098 = 0;
    sp18 = temp_v0;
    func_800722A4(objectIndex, 4);
    if (D_80165888 != 0) {
        sp18 = temp_v0;
        func_800726CC(objectIndex, 8);
        temp_v0->unk_0A4 = 0x000E;
        temp_v1 = temp_v0->unkA5;
        temp_v0->unk_0D6 = 2;
        temp_v0->unk_0D2 = temp_v1;
        temp_v0->unk_0A2 = (s16) temp_v1;
        D_8018CAB8 = 0;
        D_80165888 = 0;
        return;
    }
    func_800C8F80(arg1, 0x0100FE1C);
}
#else
GLOBAL_ASM("asm/non_matchings/code_80071F00/func_8007B254.s")
#endif

#ifdef MIPS_TO_C
//generated by m2c commit eefca95b040d7ee0c617bc58f9ac6cd1cf7bce87 on Sep-05-2023
? func_8007B254(s32, s32);                          /* extern */
extern s8 D_80165888;
static u8 *gItemWindowTLUTs[0x10];
static u8 *gItemWindowTextures[0x10];

void func_8007B34C(s32 playerId) {
    s32 sp40;
    Player *sp38;
    struct_80165C18_entry *sp2C;
    struct_8018CA70_entry *sp28;
    s16 temp_a1;
    s16 temp_a1_2;
    s16 temp_a1_3;
    s16 temp_v0_4;
    s32 temp_s0;
    s32 temp_v0_2;
    s8 temp_v0_5;
    struct_80165C18_entry *temp_t0;
    struct_8018CA70_entry *temp_v1;
    struct_8018CA70_entry *temp_v1_2;
    struct_8018CA70_entry *temp_v1_3;
    struct_8018CA70_entry *temp_v1_4;
    struct_8018CA70_entry *temp_v1_5;
    struct_8018CA70_entry *temp_v1_6;
    u16 temp_t6;
    u16 temp_v0;
    u8 temp_v0_3;

    sp38 = &gPlayerOne[playerId];
    sp40 = 0;
    temp_s0 = gItemWindowObjectByPlayerId[playerId];
    if (gControllerOne[playerId].buttonPressed & 0x2000) {
        sp40 = 1;
    }
    if (D_80165888 != 0) {
        func_800723A4(temp_s0, 0);
    }
    temp_t0 = &D_80165C18[temp_s0];
    sp2C = temp_t0;
    temp_t6 = (u16) temp_t0->unk_0A6;
    switch (temp_t6) {
    case 1:
        func_8007B254(temp_s0, playerId);
        break;
    case 2:
        if (gActiveScreenMode == 0) {
            temp_v1 = &D_8018CA70[playerId];
            sp28 = temp_v1;
            s16_step_up_towards(&temp_v1->slideItemBoxY, 0x0040, 4);
            if (temp_v1->slideItemBoxY == 0x0040) {
                func_80072488(temp_s0);
            }
        } else if (gActiveScreenMode == 3) {
            if ((playerId == 0) || (playerId == 2)) {
                temp_v1_2 = &D_8018CA70[playerId];
                sp28 = temp_v1_2;
                s16_step_up_towards(&temp_v1_2->slideItemBoxX, 0x0080, 8);
                if (temp_v1_2->slideItemBoxX == 0x0080) {
                    func_80072488(temp_s0);
                }
            } else {
                temp_v1_3 = &D_8018CA70[playerId];
                sp28 = temp_v1_3;
                s16_step_down_towards(&temp_v1_3->slideItemBoxX, -0x0080, 8);
                if (temp_v1_3->slideItemBoxX == -0x0080) {
                    func_80072488(temp_s0);
                }
            }
        } else {
            temp_v1_4 = &D_8018CA70[playerId];
            sp28 = temp_v1_4;
            s16_step_up_towards(&temp_v1_4->slideItemBoxX, 0x0080, 8);
            if (temp_v1_4->slideItemBoxX == 0x0080) {
                func_80072488(temp_s0);
            }
        }
        break;
    case 3:
        func_80072E54(temp_s0, 1, 0x0000000F, 1, 2, 2);
        break;
    case 4:
        func_80072E54(temp_s0, 1, 6, 1, 8, 1);
        break;
    case 5:
        func_80072E54(temp_s0, 1, 4, 1, 0x00000010, 1);
        break;
    case 6:
        sp2C->unk_0D2 = func_8007AFB0(temp_s0, playerId);
        sp2C->unk_04C = 8;
        sp2C->unk_0D6 = 2;
        func_80072488(temp_s0);
        sp28 = (struct_8018CA70_entry *) (u8) playerId;
        func_800C9018((u8) playerId, 0x0100FE1C);
        func_800C8F80((u8) playerId, 0x0100FE47);
        break;
    case 7:
        func_80072D3C(temp_s0, (s32) sp2C->unk_0A2, 0, 8, 0x0000000A);
        break;
    case 9:
        func_800722CC(temp_s0, 4);
        func_80073600(temp_s0);
        sp2C->unk_0D2 = 0;
        func_80072488(temp_s0);
        break;
    case 10:
        func_8007278C(temp_s0, 0x00000014);
        break;
    case 11:
        if (gActiveScreenMode == 0) {
            if (s16_step_down_towards(&D_8018CA70[playerId].slideItemBoxY, 0, 4) != 0) {
                func_80072488(temp_s0);
            }
        } else if (gActiveScreenMode == 3) {
            if ((playerId == 0) || (playerId == 2)) {
                temp_v1_5 = &D_8018CA70[playerId];
                sp28 = temp_v1_5;
                s16_step_down_towards(&temp_v1_5->slideItemBoxX, 0, 8);
                if (temp_v1_5->slideItemBoxX == 0) {
                    func_80072488(temp_s0);
                }
            } else {
                temp_v1_6 = &D_8018CA70[playerId];
                sp28 = temp_v1_6;
                s16_step_up_towards(&temp_v1_6->slideItemBoxX, 0, 8);
                if (temp_v1_6->slideItemBoxX == 0) {
                    func_80072488(temp_s0);
                }
            }
        } else if (s16_step_down_towards(&D_8018CA70[playerId].slideItemBoxX, 0, 8) != 0) {
            func_80072488(temp_s0);
        }
        break;
    case 12:
        func_80072428(temp_s0);
        break;
    case 20:
        temp_a1 = sp2C->unk_0A2;
        if (temp_a1 == 0x000B) {
            func_80072D3C(temp_s0, (s32) temp_a1, 0, 8, 0x0000000A);
        } else {
            func_80072D3C(temp_s0, (s32) temp_a1, 0x0000000B, 8, 0x0000000A);
        }
        break;
    case 21:
        func_800726CC(temp_s0, 8);
        sp2C->unk_0D6 = 2;
        break;
    case 30:
        temp_a1_2 = sp2C->unk_0A2;
        if (temp_a1_2 == 0x000B) {
            func_80072D3C(temp_s0, (s32) temp_a1_2, 0, 8, 0x0000000A);
        } else {
            func_80072D3C(temp_s0, (s32) temp_a1_2, 0x0000000B, 8, 0x0000000A);
        }
        break;
    case 31:
        func_800726CC(temp_s0, 9);
        break;
    case 40:
        temp_a1_3 = sp2C->unk_0A2;
        if (temp_a1_3 == 0x000D) {
            func_80072D3C(temp_s0, (s32) temp_a1_3, 0x0000000E, 8, 0x0000000A);
        } else {
            func_80072D3C(temp_s0, (s32) temp_a1_3, 0x0000000D, 8, 0x0000000A);
        }
        break;
    case 41:
        func_800726CC(temp_s0, 8);
        break;
    case 50:
        func_80072D3C(temp_s0, (s32) sp2C->unk_0A2, 0, 8, 0x00000064);
        break;
    }
    if (func_80072320(temp_s0, 2) != 0) {
        temp_v0 = sp2C->unk_098;
        if (temp_v0 == 0) {
            func_8007AC9C(playerId);
        } else {
            sp2C->unk_098 = temp_v0 - 1;
        }
    }
    temp_v0_2 = sp2C->unk_04C;
    if (temp_v0_2 >= 0) {
        if (temp_v0_2 > 0) {
            sp2C->unk_04C = temp_v0_2 - 1;
        } else {
            temp_v0_3 = sp2C->unk_0D6;
            switch (temp_v0_3) {                    /* switch 1; irregular */
            case 1:                                 /* switch 1 */
                if (sp40 != 0) {
                    func_80073600(temp_s0);
                    func_800726CC(temp_s0, 6);
                }
                break;
            case 2:                                 /* switch 1 */
                func_800729D0(temp_s0, (s32) sp2C->unk_0A2);
                sp2C->unk_0D6 = 3;
                break;
            case 3:                                 /* switch 1 */
                if (sp2C->unk_0A4 == 0) {
                    if (func_80072354(temp_s0, 1) != 0) {
                        temp_v0_4 = sp2C->unk_0A2;
                        if (temp_v0_4 == 0x000B) {
                            if (func_8007B040(temp_s0, playerId) != 0) {
                                func_800726CC(temp_s0, 0x00000014);
                                sp2C->unk_0D6 = 0;
                            } else {
                                func_800726CC(temp_s0, 9);
                            }
                        } else if ((temp_v0_4 == 0x000D) || (temp_v0_4 == 0x000E)) {
                            sp2C->unk_0A2 = temp_v0_4 - 1;
                            func_800729D0(temp_s0, (s32) sp2C->unk_0A2);
                            sp2C->unk_0D6 = 3;
                            func_800726CC(temp_s0, 0x00000028);
                        } else {
                            func_800726CC(temp_s0, 9);
                        }
                    } else {
                        func_800722CC(temp_s0, 1);
                        func_800726CC(temp_s0, 0x0000001E);
                        sp2C->unk_0D6 = 0;
                    }
                }
                break;
            }
        }
    }
    temp_v0_5 = sp2C->unk_0D2;
    sp2C->activeTLUT = gItemWindowTLUTs[temp_v0_5];
    sp2C->activeTexture = gItemWindowTextures[temp_v0_5];
    sp38->unk_010 = sp2C->unk_0A4;
}
#else
GLOBAL_ASM("asm/non_matchings/code_80071F00/func_8007B34C.s")
#endif

void func_8007BB9C(s32 arg0) {
    func_8007B34C(arg0);
}

void func_8007BBBC(s32 objectIndex) {
    f32 var_f14;
    struct_80165C18_entry *temp_s1;

    temp_s1 = &D_80165C18[objectIndex];
    switch (temp_s1->unk_0A6) {                              /* irregular */
    case 1:
        func_800735BC(objectIndex, d_course_banshee_boardwalk_dl_cheep_cheep, 2.0f);
        func_800721C0(objectIndex, 0x00000010);
        temp_s1->unk_0D5 = 0;
        break;
    case 2:
        if (gIsMirrorMode != 0) {
            func_80087E08(objectIndex, 18.0f, 0.7f, 25.0f, (s16) -0x00005800, 0x0000012C);
        } else {
            func_80087E08(objectIndex, 18.0f, 0.7f, 25.0f, (s16) 0x00005800, 0x0000012C);
        }
        if (temp_s1->unk_038[2] < 0.0f) {
            var_f14 = -temp_s1->unk_038[2];
        } else {
            var_f14 = temp_s1->unk_038[2];
        }
        temp_s1->unk_0BE[0] = func_80041658(temp_s1->unk_038[1], var_f14);
        func_8007278C(objectIndex, 0x00000046);
        break;
    case 3:
        func_80072428(objectIndex);
        break;
    case 0:
        break;
    }
}

void func_8007BD04(s32 playerId) {
    s32 objectIndex;

    objectIndex = D_80183F28[0];
    if (D_80165C18[objectIndex].unk_0A6 == 0) {
        if (((s32) gNearestWaypointByPlayerId[playerId] >= 0xA0) && ((s32) gNearestWaypointByPlayerId[playerId] < 0xAB)) {
            func_8008B7D4(objectIndex, D_8018D01C * -1650.0, -200.0f, -1650.0f);
            func_800723A4(objectIndex, 1);
        }
    }
}

void func_8007BDA8(void) {
    UNUSED s32 pad;
    s32 temp_a0;

    func_8007BD04(0);
    temp_a0 = D_80183F28[0];
    func_8007BBBC(temp_a0);
    func_8008BF18(temp_a0);
}

void func_8007BDE0(s32 objectIndex) {
    struct_80165C18_entry *temp_v0;

    temp_v0 = &D_80165C18[objectIndex];
    temp_v0->unk_0D5 = 1;
    temp_v0->unk_054 = 0;
    temp_v0->unk_070 = d_course_banshee_boardwalk_dl_cheep_cheep;
    temp_v0->sizeScaling = 0.2f;
    func_80072488(objectIndex);
    func_8008B7D4(objectIndex, D_800E634C[0][0], D_800E634C[0][1] + 55.0, D_800E634C[0][2]);
    func_8008B80C(objectIndex, 0.0f, 30.0f, 0.0f);
    func_8008B888(objectIndex, 0U, 0x3800U, 0U);
}

void func_8007BEC8(s32 objectIndex) {
    struct_80165C18_entry *temp_v0;

    temp_v0 = &D_80165C18[objectIndex];
    switch (temp_v0->unk_0A6) {
    case 1:
        func_8007BDE0(objectIndex);
        break;
    case 2:
        if (func_8007278C(objectIndex, 0x0000003C) != 0) {
            func_800721C0(objectIndex, 0x00000010);
            func_80086E70(objectIndex);
        }
        break;
    case 3:
        if (temp_v0->unk_0AE == 0) {
            func_80072488(objectIndex);
        }
        break;
    case 4:
        if (func_8007278C(objectIndex, 0x0000000A) != 0) {
            func_8008701C(objectIndex, 2);
        }
        break;
    case 5:
        if (temp_v0->unk_0AE == 0) {
            func_80072428(objectIndex);
        }
        break;
    case 0:
    default:
        break;
    }
}

void func_8007BFB0(s32 objectIndex) {
    struct_80165C18_entry *temp_s0;

    temp_s0 = &D_80165C18[objectIndex];
    switch (temp_s0->unk_0AE) {
    case 0:
        break;
    case 1:
        temp_s0->unk_038[1] = -0.2f;
        if ((f64) temp_s0->unk_028[1] <= 0.0) {
            temp_s0->unk_028[1] = 0.0f;
            temp_s0->unk_038[1] = 0.0f;
            func_80086F60(objectIndex);
        }
        break;
    case 2:
        if (func_800871AC(objectIndex, 0x00000014) != 0) {
            temp_s0->unk_084[7] = 0x0040;
        }
        break;
    case 3:
        temp_s0->sizeScaling = (f32) ((f64) temp_s0->sizeScaling - 0.0015);
        if ((s32) temp_s0->unk_0BE[0] >= 0xA01) {
            temp_s0->unk_084[7] -= 4;
        }
        if (u16_step_up_towards(temp_s0->unk_0BE, 0x0C00U, (u16) temp_s0->unk_084[7]) != 0) {
            func_80086FD4(objectIndex);
        }
        break;
    case 4:
        temp_s0->sizeScaling = (f32) ((f64) temp_s0->sizeScaling - 0.0015);
        temp_s0->unk_034 = 0.001f;
        func_80086FD4(objectIndex);
        temp_s0->unk_084[7] = 0;
        break;
    case 5:
        if (temp_s0->unk_034 <= 0.004) {
            temp_s0->unk_034 += 0.0002;
        }
        temp_s0->sizeScaling += temp_s0->unk_034;
        s16_step_up_towards(&temp_s0->unk_084[7], 0x0100, 0x0010);
        temp_s0->unk_0BE[0] -= temp_s0->unk_084[7];
        if (func_80087060(objectIndex, 0x00000035) != 0) {
            func_80086FD4(objectIndex);
        }
        break;
    case 6:
        if (func_80087060(objectIndex, 0x0000000F) != 0) {
            func_80086FD4(objectIndex);
            D_801658CE = 1;
        }
        break;
    case 7:
        temp_s0->sizeScaling = (f32) ((f64) temp_s0->sizeScaling - 0.05);
        if ((f64) temp_s0->sizeScaling <= 0.01) {
            func_800721E8(objectIndex, 0x00000010);
            temp_s0->sizeScaling = 0.000001f;
            func_80086FD4(objectIndex);
        }
        break;
    case 8:
        func_80086F60(objectIndex);
        break;
    }
    if (temp_s0->unk_0AE < 0xA) {
        func_80074344(objectIndex, &temp_s0->sizeScaling, 0.2f, 0.21f, 0.001f, 0, -1);
    }
    func_800877C4(objectIndex);
    func_8008BF18(objectIndex);
}

void func_8007C280(void) {
    s32 objectIndex;

    objectIndex = D_80183F28[0];
    if (D_801658BC == 1) {
        D_801658BC = 0;
        func_800723A4(objectIndex, 0);
    }
    if (D_80165C18[objectIndex].unk_0A6 != 0) {
        func_8007BEC8(objectIndex);
        func_8007BFB0(objectIndex);
    }
}

void func_8007C2F8(s32 arg0) {
    switch (arg0) {
        case 0:
            func_8007BDA8();
            break;
        case 1:
            func_8007C280();
            break;
    }
}

void func_8007C340(void) {
    func_8007CC00();
}

#ifdef MIPS_TO_C
//generated by m2c commit d9d3d6575355663122de59f6b2882d8f174e2355 on Dec-27-2022
void func_8007C360(s32 objectIndex, Camera *camera) {
    struct_80165C18_entry *sp20;
    s32 sp1C;
    s32 temp_t0;
    s32 temp_t2;
    s32 var_t1;
    struct_80165C18_entry *temp_a2;

    temp_a2 = &D_80165C18[objectIndex];
    temp_t0 = (((temp_a2->unk_0BE[1] - (u16) camera->rot[1]) + 0x8000) & 0xFFFF) * 0x24;
    var_t1 = temp_t0 >> 0x10;
    if (temp_t0 < 0) {
        var_t1 = (s32) (temp_t0 + 0xFFFF) >> 0x10;
    }
    temp_t2 = var_t1 & 0xFFFF;
    if (temp_t2 < 0x13) {
        sp20 = temp_a2;
        sp1C = temp_t2;
        func_800721E8(objectIndex, 0x00000080);
        temp_a2->unk_0D2 = (s8) sp1C;
        return;
    }
    sp20 = temp_a2;
    sp1C = temp_t2;
    func_800721C0(objectIndex, 0x00000080);
    temp_a2->unk_0D2 = 0x24 - temp_t2;
}
#else
GLOBAL_ASM("asm/non_matchings/code_80071F00/func_8007C360.s")
#endif

void func_8007C420(s32 objectIndex, Player *player, Camera *camera) {
    f32 x;
    f32 z;

    x = player->pos[0] - D_80165C18[objectIndex].pos[0];
    z = player->pos[2] - D_80165C18[objectIndex].pos[2];
    D_80165C18[objectIndex].unk_0BE[1] = func_800417B4(D_80165C18[objectIndex].unk_0BE[1], atan2s(x, z));
    func_8007C360(objectIndex, camera);
}

UNUSED void func_8007C49C(void) {

}

#ifdef MIPS_TO_C
//generated by m2c commit 9841ff34ca242f5f14b2eab2b54a7a65ac47d80f
void func_8007C4A4(s32 objectIndex) {
    struct_80165C18_entry *sp20;
    s32 sp1C;
    s32 temp_t0;
    s32 temp_t8;
    s32 var_t9;
    struct_80165C18_entry *temp_v1;

    temp_v1 = &D_80165C18[objectIndex];
    temp_t8 = temp_v1->unk_0BE[1] * 0x24;
    var_t9 = temp_t8 >> 0x10;
    if (temp_t8 < 0) {
        var_t9 = (s32) (temp_t8 + 0xFFFF) >> 0x10;
    }
    temp_t0 = var_t9 & 0xFFFF;
    if (temp_t0 < 0x13) {
        sp20 = temp_v1;
        sp1C = temp_t0;
        func_800721E8(objectIndex, 0x00000080);
        temp_v1->unk_0D2 = (s8) sp1C;
        return;
    }
    sp20 = temp_v1;
    sp1C = temp_t0;
    func_800721C0(objectIndex, 0x00000080);
    temp_v1->unk_0D2 = 0x24 - temp_t0;
}
#else
GLOBAL_ASM("asm/non_matchings/code_80071F00/func_8007C4A4.s")
#endif

void func_8007C550(s32 objectIndex) {
    D_80165C18[objectIndex].unk_0BE[1] = func_800417B4(D_80165C18[objectIndex].unk_0BE[1], atan2s(D_80165C18[objectIndex].unk_038[0], D_80165C18[objectIndex].unk_038[2]));
    func_8007C4A4(objectIndex);
}

extern u8 d_course_banshee_boardwalk_boo_tlut[];
extern u8 *D_80165880;

void func_8007C5B4(s32 objectIndex) {
    struct_80165C18_entry *temp_s0;

    func_80073444(objectIndex, d_course_banshee_boardwalk_boo_tlut, D_80165880, 48, 40);
    temp_s0 = &D_80165C18[objectIndex];
    temp_s0->pos[0] = 0.0f;
    temp_s0->pos[1] = 0.0f;
    temp_s0->pos[2] = 0.0f;
    func_800721C0(objectIndex, 0x00000020);
    func_80072488(objectIndex);
    temp_s0->unk_0A0 = 0;
    func_80073844(objectIndex);
    temp_s0->sizeScaling = 0.15f;
    temp_s0->unk_034 = 1.0f;
    func_80073FD4(objectIndex);
    func_80086EF0(objectIndex);
    func_800721C0(objectIndex, 0x00000800);
    temp_s0->unk_0B2[0] = 0;
    temp_s0->unk_0B2[2] = 0x8000;
}

void func_8007C684(s32 objectIndex) {
    switch(D_80165C18[objectIndex].unk_0A6) {
    case 0:
        break;
    case 1:
        func_8007C5B4(objectIndex);
        break;
    }
    if (D_80165C18[objectIndex].unk_0A6 >= 2) {
        switch (D_80165C18[objectIndex].unk_0DC) {
        case 0:
            break;
        case 1:
            func_80073998(objectIndex, &D_80165C18[objectIndex].unk_0A0, 0, 0x00000050, 2, 1, 0);
            break;
        case 2:
            func_80073CB0(objectIndex, &D_80165C18[objectIndex].unk_0A0, 0x00000050, 0x00000078, 1, 0, -1);
            break;
        case 3:
            func_80073DC0(objectIndex, &D_80165C18[objectIndex].unk_0A0, 0, 2);
            break;
        case 4:
            func_80072428(objectIndex);
            func_80086F60(objectIndex);
            func_80073884(objectIndex);
            break;
        }
        func_80073514(objectIndex);
    }
}

#ifdef NON_MATCHING
//generated by m2c commit 9841ff34ca242f5f14b2eab2b54a7a65ac47d80f
extern s16 D_8018CFF0;
extern s16 D_8018D048;
// static ? D_800E5988;                                /* unable to generate initializer */
// static ? D_800E5A44;                                /* unable to generate initializer */
// static ? D_800E5B08;                                /* unable to generate initializer */
// static ? D_800E5BD4;                                /* unable to generate initializer */
// static ? D_800E5C90;                                /* unable to generate initializer */
// static s32 D_800E5D9C[5] = {
//     (s32) &D_800E5988,
//     (s32) &D_800E5A44,
//     (s32) &D_800E5B08,
//     (s32) &D_800E5BD4,
//     (s32) &D_800E5C90,
// };
// static ? D_800E5DB0;                                /* unable to generate initializer */
extern s32 D_800E5D9C[];
extern s32 D_800E5DB0;

// Close but not yet
void func_8007C7B4(s32 arg0, s32 arg1) {
    //s32 *sp40;
    s16 temp_s1_2;
    s16 temp_s4;
    s16 temp_s5;
    s32 *var_s2;
    s32 var_s3;
    s32 *temp_s1;
    UNUSED s32 *temp_v1;
    //struct_80165C18_entry *temp_s0;
    //s32 i = 0;
    
    temp_s1 = &D_8018BFA8[arg0];
    //sp40   = D_8018BFA8[arg0];
    var_s2 = (s32 *)&D_800E5D9C;

    do { //for (i = 0; i < 20; i++) {
        var_s3 = *temp_s1;
        //temp_s1 = *var_s3;
        func_800723A4(var_s3, 1);
        //temp_s0 = &D_80165C18[var_s3[i]];
        D_80165C18[var_s3].unk_0D1 = arg1;
        temp_s1_2 = random_int(60) - 30;
        temp_s4 = random_int(20) - 10;
        temp_s5 = random_int(80) - 40;
        random_int(4096); // burn a card?
        temp_v1 = (s32 *) var_s2;
        var_s2 += 4;
        temp_s1 += 4;
        D_80165C18[var_s3].unk_010[0] = (f32)temp_s1_2;
        D_80165C18[var_s3].unk_080 = (u16 *) var_s2;
        D_80165C18[var_s3].unk_010[1] = (f32) temp_s4;
        D_80165C18[var_s3].unk_010[2] = (f32) temp_s5;
    } while (*var_s2 != D_800E5DB0);

    func_800C9060(arg1, 0x1900705A);
    if (&D_8018BFA8[arg0] == D_8018BFA8) {
        D_8018CFF0 = 1;
        return;
    }
    D_8018D048 = 1;
}
#else
GLOBAL_ASM("asm/non_matchings/code_80071F00/func_8007C7B4.s")
#endif

#ifdef MIPS_TO_C
//generated by m2c commit 8267401fa4ef7a38942dcca43353cc1bcc6efabc
extern s16 D_8018CFF0;
extern s16 D_8018D048;

void func_8007C91C(s32 objectIndex) {
    s32 *temp_a0;
    s32 *temp_a1;
    struct_80165C18_entry *temp_a2;
    struct_80165C18_entry *temp_a2_2;
    struct_80165C18_entry *temp_a2_3;
    struct_80165C18_entry *temp_a2_4;
    struct_80165C18_entry *temp_a2_5;

    temp_a1 = &D_8018BFA8[objectIndex];
    temp_a0 = &temp_a1[1];
    temp_a2 = &D_80165C18[*temp_a1];
    temp_a2->unk_0DC += 1;
    temp_a2_2 = &D_80165C18[temp_a0->unk0];
    temp_a2_2->unk_0DC += 1;
    temp_a2_3 = &D_80165C18[temp_a0->unk4];
    temp_a2_3->unk_0DC += 1;
    temp_a2_4 = &D_80165C18[temp_a0->unk8];
    temp_a2_4->unk_0DC += 1;
    temp_a2_5 = &D_80165C18[temp_a0->unkC];
    temp_a2_5->unk_0DC += 1;
    if (temp_a1 == D_8018BFA8) {
        D_8018D048 = 0;
        return;
    }
    D_8018CFF0 = 0;
}
#else
GLOBAL_ASM("asm/non_matchings/code_80071F00/func_8007C91C.s")
#endif

s32 func_8007C9F8(void) {
    s32 ret;
    s32 first, second;
    if (D_8018EDF3 == 1) {
        ret = 0;
    } else {
        if (D_8018EDF3 == 2) {
            if (gModeSelection == 0) {
                first = gGPCurrentRaceRankByPlayerId[0];
                second = gGPCurrentRaceRankByPlayerId[1];
                if (first < second) {
                    ret =  0;
                } else {
                    ret =  1;
                }
            } else {
                ret =  gGPCurrentRacePlayerIdByRank[0];
            }
        } else {
            ret =  gGPCurrentRacePlayerIdByRank[0];
        }
    }
    return ret;
}

#ifdef MIPS_TO_C
//generated by m2c commit 8267401fa4ef7a38942dcca43353cc1bcc6efabc
void func_8007C7B4(?, s16);                            /* extern */
void func_8007C91C(?, s16);                            /* extern */
s16 func_8007C9F8();                                /* extern */
extern s16 D_8018CFF0;
extern s16 D_8018D018;
extern s16 D_8018D048;
extern s16 D_8018D110;

void func_8007CA70(void) {
    u16 *sp1C;
    s16 temp_a1;
    s16 temp_a1_2;
    s16 temp_v0;
    s16 temp_v0_2;
    u16 *temp_v1_2;
    u16 *temp_v1_4;
    u16 temp_v1;
    u16 temp_v1_3;
    u16 var_v0;
    u16 var_v0_2;

    if (D_8018CFF0 == 0) {
        temp_v0 = func_8007C9F8();
        temp_v1 = gNearestWaypointByPlayerId[temp_v0];
        D_8018D018 = temp_v0;
        if (((s32) temp_v1 >= 0xC9) && ((s32) temp_v1 < 0xD2)) {
            func_8007C7B4(0, temp_v0);
        }
    }
    if (D_8018CFF0 != 0) {
        temp_a1 = D_8018D018;
        temp_v1_2 = &gNearestWaypointByPlayerId[temp_a1];
        var_v0 = *temp_v1_2;
        if (((s32) var_v0 >= 0xB5) && ((s32) var_v0 < 0xBE)) {
            sp1C = temp_v1_2;
            func_8007C91C(0, temp_a1);
            var_v0 = *temp_v1_2;
        }
        if (((s32) var_v0 >= 0x119) && ((s32) var_v0 < 0x122)) {
            func_8007C91C(0);
        }
    }
    if (D_8018D048 == 0) {
        temp_v0_2 = func_8007C9F8();
        temp_v1_3 = gNearestWaypointByPlayerId[temp_v0_2];
        D_8018D110 = temp_v0_2;
        if (((s32) temp_v1_3 >= 0x1FF) && ((s32) temp_v1_3 < 0x208)) {
            func_8007C7B4(5, temp_v0_2);
        }
    }
    if (D_8018D048 != 0) {
        temp_a1_2 = D_8018D110;
        temp_v1_4 = &gNearestWaypointByPlayerId[temp_a1_2];
        var_v0_2 = *temp_v1_4;
        if (((s32) var_v0_2 >= 0x1EB) && ((s32) var_v0_2 < 0x1F4)) {
            sp1C = temp_v1_4;
            func_8007C91C(5, temp_a1_2);
            var_v0_2 = *temp_v1_4;
        }
        if (((s32) var_v0_2 >= 0x26D) && ((s32) var_v0_2 < 0x276)) {
            func_8007C91C(5);
        }
    }
}
#else
GLOBAL_ASM("asm/non_matchings/code_80071F00/func_8007CA70.s")
#endif

void func_8007CC00(void) {
    u16 temp_t4;
    s32 someIndex;
    s32 objectIndex;
    Player *player;
    Camera *camera;
    struct_80165C18_entry *object;

    func_8007CA70();
    for (someIndex = 0; someIndex < NUM_BOOS; someIndex++) {
        objectIndex = D_8018BFA8[someIndex];
        object = &D_80165C18[objectIndex];
        if (object->unk_0A6 != 0) {
            func_8007C684(objectIndex);
            func_8008B78C(objectIndex);
            player = &gPlayerOne[object->unk_0D1];
            camera = &camera1[object->unk_0D1];
            temp_t4 = (0x8000 - camera->rot[1]);
            object->pos[0] = player->pos[0] + (coss(temp_t4) * (object->unk_010[0] + object->unk_028[0])) - (sins(temp_t4) * (object->unk_010[2] + object->unk_028[2]));
            object->pos[1] = 6.5 + player->unk_074 + object->unk_010[1] + object->unk_028[1];
            object->pos[2] = player->pos[2] + (sins(temp_t4) * (object->unk_010[0] + object->unk_028[0])) + (coss(temp_t4) * (object->unk_010[2] + object->unk_028[2]));
            func_8007C550(objectIndex);
            if (func_8007223C(objectIndex, 0x00000080) != 0) {
                object->unk_074 = D_800E44B0;
            } else {
                object->unk_074 = D_800E4470;
            }
        }
    }
}

void func_8007CE0C(s32 objectIndex) {
    struct_80165C18_entry *temp_s0;

    func_80073444(objectIndex, d_course_banshee_boardwalk_boo_tlut, D_0F0D0E50, 0x30U, (u16) 0x00000028);
    temp_s0 = &D_80165C18[objectIndex];
    temp_s0->unk_0D2 = 0x1C;
    temp_s0->pos[0] = 0.0f;
    temp_s0->pos[1] = 0.0f;
    temp_s0->pos[2] = 0.0f;
    temp_s0->sizeScaling = 0.15f;
    func_80072488(objectIndex);
    temp_s0->unk_0A0 = 0;
    func_80073844(objectIndex);
    func_80086EF0(objectIndex);
    temp_s0->unk_0BE[2] = 0x8000;
    temp_s0->unk_0BE[1] = atan2s(D_8018CF1C->pos[0] - temp_s0->unk_010[0], D_8018CF1C->pos[2] - temp_s0->unk_010[2]);
}

void func_8007CEDC(s32 objectIndex) {
    struct_80165C18_entry *temp_s0;

    temp_s0 = &D_80165C18[objectIndex];
    switch (temp_s0->unk_0A6) {                              /* switch 1 */
    case 0:                                         /* switch 1 */
        break;
    case 1:                                         /* switch 1 */
        func_8007CE0C(objectIndex);
        break;
    case 2:                                         /* switch 1 */
        func_8007278C(objectIndex, 0x0000001E);
        break;
    case 3:                                         /* switch 1 */
        func_8007278C(objectIndex, 0x000003E8);
        break;
    case 4:                                         /* switch 1 */
        func_80072428(objectIndex);
        break;
    default:                                        /* switch 2 */
        break;
    }
    if (temp_s0->unk_0A6 >= 2) {
        func_80072950(objectIndex, (s32) temp_s0->unk_0DC, 0, 4);
        func_80073514(objectIndex);
        switch (temp_s0->unk_0DC) {                          /* switch 2 */
        case 1:                                     /* switch 2 */
            func_80073998(objectIndex, &temp_s0->unk_0A0, 0x00000028, 0x00000050, 4, 0, 0);
            break;
        case 2:                                     /* switch 2 */
            func_80073CB0(objectIndex, &temp_s0->unk_0A0, 0x00000050, 0x000000B4, 2, 0, -1);
            if ((temp_s0->unk_0AE == 0) || (temp_s0->unk_0A6 == 3)) {
                temp_s0->unk_0DC += 1;
            }
            break;
        case 3:                                     /* switch 2 */
            func_80073DC0(objectIndex, &temp_s0->unk_0A0, 0, 4);
            break;
        case 4:                                     /* switch 2 */
            func_80073884(objectIndex);
            break;
        case 0:
        default:                                        /* switch 2 */
            break;
        }
    }
}

#ifdef MIPS_TO_C
//generated by m2c commit eefca95b040d7ee0c617bc58f9ac6cd1cf7bce87 on Aug-10-2023
extern s32 D_8016559C;
extern s32 D_8018C1D8;
extern ? D_8018C228;
static Vtx D_800E4470;                              /* unable to generate initializer */
static Vtx D_800E44B0;                              /* unable to generate initializer */
static s16 D_800E5D54[4];                           /* unable to generate initializer */
static ? D_800E5DB4;                                /* unable to generate initializer */

void func_8007D070(void) {
    f32 sp44;
    f32 temp_f2;
    f32 temp_f4;
    f32 temp_f6;
    s16 temp_s2;
    s32 *var_s2;
    s32 temp_s1;
    s32 temp_s1_2;
    s32 temp_s3;
    s32 temp_t2;
    s32 temp_t5;
    s32 var_v0;
    struct_80165C18_entry *temp_s0;
    struct_80165C18_entry *temp_s0_2;

    var_v0 = 0;
    if ((D_8016559C == 0) && (D_8018D2A4 != 0) && (*D_8018CF68 < 0x1D) && (*(&D_800E5DB4 + *D_8018CF68) == 1)) {
        if (D_80165C18[D_8018C1D8].unk_0A6 != 0) {
loop_5:
            var_v0 += 1;
            if (var_v0 != 0x1E) {
                if (D_80165C18[D_8018C1B0[var_v0].unk28].unk_0A6 != 0) {
                    goto loop_5;
                }
            }
        }
        temp_s1 = D_8018C1B0[var_v0].unk28;
        if (var_v0 != 0x1E) {
            temp_s0 = &D_80165C18[temp_s1];
            if (temp_s0->unk_0A6 == 0) {
                func_800723A4(temp_s1, 1);
                temp_s2 = random_int(0x012CU);
                temp_s3 = (random_int(0x1000U) - 0x800) & 0xFFFF;
                temp_t5 = (random_int(0x000FU) - 5) << 0x10;
                temp_s0->unk_0BE[1] = D_8018CF1C->unk_02C[1] + 0x8000;
                temp_t2 = (D_8018CF14->rot[1] + temp_s3) & 0xFFFF;
                temp_f2 = (f32) temp_s2;
                temp_f6 = sins(temp_t2 & 0xFFFF) * temp_f2;
                sp44 = temp_f2;
                temp_s0->unk_010[1] = (f32) (temp_t5 >> 0x10);
                temp_s0->unk_010[0] = temp_f6 + D_8018CF1C->pos[0];
                temp_f4 = coss(temp_t2 & 0xFFFF) * temp_f2;
                temp_s0->unk_080 = (s16 (*)[4]) D_800E5D54;
                temp_s0->unk_010[2] = temp_f4 + D_8018CF1C->pos[2];
            }
        }
    }
    var_s2 = D_8018C1B0;
    do {
        temp_s1_2 = var_s2->unk28;
        temp_s0_2 = &D_80165C18[temp_s1_2];
        if (temp_s0_2->unk_0A6 != 0) {
            func_8007CEDC(temp_s1_2);
            func_8008B724(temp_s1_2);
            temp_s0_2->pos[0] = temp_s0_2->unk_028[0] + temp_s0_2->unk_010[0];
            temp_s0_2->pos[1] = temp_s0_2->unk_028[1] + (D_8018CF1C->unk_074 + temp_s0_2->unk_010[1]);
            temp_s0_2->pos[2] = temp_s0_2->unk_028[2] + temp_s0_2->unk_010[2];
            func_8007C420(temp_s1_2, D_8018CF1C, D_8018CF14);
            if (func_8007223C(temp_s1_2, 0x00000080) != 0) {
                temp_s0_2->unk_074 = &D_800E44B0;
            } else {
                temp_s0_2->unk_074 = &D_800E4470;
            }
        }
        var_s2 += 4;
    } while (var_s2 != &D_8018C228);
}
#else
GLOBAL_ASM("asm/non_matchings/code_80071F00/func_8007D070.s")
#endif

void func_8007D360(s32 objectIndex, s32 arg1) {
    if (arg1 == 1) {
        D_80165C18[objectIndex].unk_010[0] = (f32) ((-1775.0 - random_int(0x001EU)) * (f64) D_8018D01C);
        D_80165C18[objectIndex].unk_010[1] = (f32) (random_int(0x0019U) + 25.0);
        D_80165C18[objectIndex].unk_010[2] = (f32) (random_int(0x001EU) + 130.0);
        D_80165C18[objectIndex].unk_01C[0] = (f32) ((f64) D_8018D01C * -2500.0);
        D_80165C18[objectIndex].unk_01C[1] = 0.0f;
        D_80165C18[objectIndex].unk_01C[2] = (f32) (220.0 - random_int(0x0096U));
        D_80165C18[objectIndex].unk_0BE[0] = 0xDC00;
        D_80165C18[objectIndex].unk_0C6 = 0x0800;
    }
    if (arg1 == 2) {
        D_80165C18[objectIndex].unk_010[0] = (f32) (-0x55B - random_int(0x001EU)) * D_8018D01C;
        D_80165C18[objectIndex].unk_010[1] = (f32) (random_int(0x0019U) + 0xF);
        D_80165C18[objectIndex].unk_010[2] = (f32) (random_int(0x001EU) - 0xE8);
        D_80165C18[objectIndex].unk_01C[0] = (f32) ((f64) D_8018D01C * -2100.0);
        D_80165C18[objectIndex].unk_01C[1] = 0.0f;
        D_80165C18[objectIndex].unk_01C[2] = (f32) (random_int(0x00C8U) + -290.0);
        D_80165C18[objectIndex].unk_0BE[0] = 0;
        D_80165C18[objectIndex].unk_0C6 = 0;
    }
    D_80165C18[objectIndex].unk_0BE[1] = func_80041770(D_80165C18[objectIndex].unk_010[0], D_80165C18[objectIndex].unk_01C[0], D_80165C18[objectIndex].unk_010[2], D_80165C18[objectIndex].unk_01C[2]);
    D_80165C18[objectIndex].unk_0BE[2] = 0;
    func_8008B80C(objectIndex, 0.0f, 0.0f, 0.0f);
    D_80165C18[objectIndex].unk_0B0 = 0;
    if (gCCSelection < 2) {
       D_80165C18[objectIndex].unk_034 = (random_int(4U) + 4.0);
    } else {
        D_80165C18[objectIndex].unk_034 = (random_int(4U) + 5.0);
    }
}

void func_8007D6A8(s32 objectIndex, s32 arg1) {
    UNUSED s32 pad[2];
    struct_80165C18_entry *temp_v0;

    temp_v0 = &D_80165C18[objectIndex];
    temp_v0->unk_0D5 = 0x0D;
    func_8007D360(objectIndex, arg1);
    temp_v0->sizeScaling = 0.1f;
    func_800721C0(objectIndex, 0x00000200);
    temp_v0->unk_0C8 = 3;
}

void func_8007D714(s32 arg0) {
    s32 var_v0;

    if (arg0 == 1) {
        var_v0 = func_80072044(D_8018C3F0, &D_80183E4C, 0x00000028);
    } else {
        var_v0 = func_80072044(D_8018C630, &D_80183E5C, 0x0000001E);
    }
    if (var_v0 != -1) {
        func_800723A4(var_v0, 0);
        func_8007D6A8(var_v0, arg0);
    }
}

void func_8007D794(s32 objectIndex) {
    if (gCCSelection == CC_50) {
        func_80089A04(objectIndex, 0.5f, 0.2f);
    } else if (gCCSelection == CC_100) {
        func_80089A04(objectIndex, 0.4f, 0.15f);
    } else {
        func_80089A04(objectIndex, 0.25f, 0.1f);
    }
}

s32 func_8007D804(s32 objectIndex) {
    s32 loopIndex;
    s32 someCount;

    someCount = 0;
    for (loopIndex = 0; loopIndex < gPlayerCountSelection1; loopIndex++) {
        if (func_8008A140(objectIndex, &camera1[loopIndex], 0x4000U) != 0) {
            someCount += 1;
        }
    }
    return someCount;
}

void func_8007D8AC(s32 arg0) {
    func_80072488(arg0);
    func_80086E70(arg0);
}

void func_8007D8D4(s32 objectIndex, s32 arg1) {
    switch (D_80165C18[objectIndex].unk_0A6) {
    case 1:
        func_8007D8AC(objectIndex);
        break;
    case 2:
        if (func_8007D804(objectIndex) == 0) {
            func_80072428(objectIndex);
        }
        if (arg1 == 1) {
            if (gIsMirrorMode != 0) {
                if (D_80165C18[objectIndex].pos[0] >= 2540.0) {
                    func_80072428(objectIndex);
                }
            } else if (D_80165C18[objectIndex].pos[0] <= -2540.0) {
                func_80072428(objectIndex);
            }
        } else if (gIsMirrorMode != 0) {
            if (D_80165C18[objectIndex].pos[0] >= 2150.0) {
                func_80072428(objectIndex);
            }
        } else {
            if (D_80165C18[objectIndex].pos[0] <= -2150.0) {
                func_80072428(objectIndex);
            }
        }
        break;
    case 0:
        break;
    }
}

void func_8007DA4C(s32 arg0) {
    func_8008781C(arg0);
    func_8008BF18(arg0);
}

void func_8007DA74(s32 objectIndex) {
    UNUSED s32 pad;
    if ((D_80165C18[objectIndex].unk_0AE != 0) && (D_80165C18[objectIndex].unk_0AE == 1)) {
        if (func_80087060(objectIndex, 0x0000001E) != 0) {
            D_80165C18[objectIndex].unk_0C6 = 0U;
        }
    }
    D_80165C18[objectIndex].unk_0BE[0] = func_800417B4(D_80165C18[objectIndex].unk_0BE[0], D_80165C18[objectIndex].unk_0C6);
    func_80087844(objectIndex);
    func_8008BF18(objectIndex);
}

void func_8007DAF8(s32 objectIndex, s32 arg1) {
    switch (arg1) {                                 /* irregular */
    case 1:
        func_8007DA74(objectIndex);
        return;
    case 2:
        func_8007DA4C(objectIndex);
        return;
    }
}

#ifdef MIPS_TO_C
//generated by m2c commit d9d3d6575355663122de59f6b2882d8f174e2355 on Dec-28-2022
? func_8007D794(s32);                               /* extern */
extern ? D_8018C490;
extern ? D_8018C6A8;
extern s16 D_8018CFB0;
extern s16 D_8018CFC8;
extern s16 D_8018CFD8;
extern s16 D_8018D000;
extern s16 D_8018D010;

void func_8007DB44(void) {
    s32 *var_s2;
    s32 *var_s2_2;
    s32 temp_s0;
    s32 temp_s0_2;
    s32 temp_s0_3;
    struct_80165C18_entry *temp_s1;
    struct_80165C18_entry *temp_s1_2;
    struct_80165C18_entry *temp_s1_3;

    if (D_8018CFC8 != 0) {
        D_8018CFC8 -= 1;
    }
    if (D_8018D000 != 0) {
        D_8018D000 -= 1;
    }
    temp_s0 = *D_80183EA0;
    func_80072E54(temp_s0, 0, 3, 1, 0, -1);
    func_80073514(temp_s0);
    temp_s1 = &D_80165C18[temp_s0];
    func_80073CB0(temp_s0, &temp_s1->unk_0A0, -0x00001000, 0x00001000, 0x00000400, 0, -1);
    temp_s1->unk_0B2[2] = temp_s1->unk_0A0 + 0x8000;
    if ((D_8018CFB0 != 0) || (D_8018CFC8 != 0)) {
        D_8018CFD8 = 0;
        var_s2 = D_8018C3F0;
        do {
            temp_s0_2 = *var_s2;
            if (temp_s0_2 != -1) {
                temp_s1_2 = &D_80165C18[temp_s0_2];
                if (temp_s1_2->unk_0A6 != 0) {
                    func_8007D8D4(temp_s0_2, 1);
                    func_8007DAF8(temp_s0_2, 1);
                    func_8007D794(temp_s0_2);
                    if (temp_s1_2->unk_0A6 == 0) {
                        func_80072100(var_s2);
                    }
                    D_8018CFD8 += 1;
                }
            }
            var_s2 += 4;
        } while (var_s2 != &D_8018C490);
        if (D_8018CFD8 != 0) {
            D_8018CFC8 = 0x012C;
        }
    }
    if (D_8018CFE8 == 0) {
        if (D_8018D000 != 0) {
            goto block_19;
        }
        return;
    }
block_19:
    D_8018D010 = 0;
    var_s2_2 = D_8018C630;
    do {
        temp_s0_3 = *var_s2_2;
        if (temp_s0_3 != -1) {
            temp_s1_3 = &D_80165C18[temp_s0_3];
            if (temp_s1_3->unk_0A6 != 0) {
                func_8007D8D4(temp_s0_3, 2);
                func_8007DAF8(temp_s0_3, 2);
                func_8007D794(temp_s0_3);
                if (temp_s1_3->unk_0A6 == 0) {
                    func_80072100(var_s2_2);
                }
                D_8018D010 += 1;
            }
        }
        var_s2_2 += 4;
    } while (var_s2_2 != &D_8018C6A8);
    if (D_8018D010 != 0) {
        D_8018D000 = 0x012C;
    }
}
#else
GLOBAL_ASM("asm/non_matchings/code_80071F00/func_8007DB44.s")
#endif

void func_8007DDC0(s32 objectIndex) {
    f32 sp2C;
    struct_80165C18_entry *temp_s0;

    temp_s0 = &D_80165C18[objectIndex];
    if (temp_s0->unk_04C > 0) {
        temp_s0->unk_04C--;
        if (temp_s0->unk_04C == 0) {
            func_800722CC(objectIndex, 1);
        }
    }
    if (temp_s0->unk_048 > 0) {
        temp_s0->unk_048--;
        if (temp_s0->unk_048 == 0) {
            func_800C9EF4(temp_s0->pos, 0x51028006U);
        }
    }
    if (temp_s0->unk_04C == 0) {
        if ((gCCSelection == CC_50) || (gCCSelection == CC_100) || (gCCSelection == CC_150) || (gCCSelection == CC_EXTRA)) {
            sp2C = 1150.0f;
        }
        func_8008A6DC(objectIndex, sp2C);
        if ((func_8007223C(objectIndex, 0x00040000) != 0) && (func_80072354(objectIndex, 1) != 0)) {
            func_800722A4(objectIndex, 1);
            func_800C9D80(temp_s0->pos, temp_s0->unk_038, 0x51028006U);
            func_800726CC(objectIndex, 3);
            if (temp_s0->unk_0A4 > 0) {
                temp_s0->unk_0A4--;
                temp_s0->unk_04C = 0x00000168;
            } else {
                temp_s0->unk_04C = 0x00000168;
            }
            temp_s0->unk_048 = 0x0000012C;
        }
    }
    if (func_8008A8B0(0x000F, 0x0012) == 0) {
        temp_s0->unk_0A4 = 2;
    }
}

void init_bb_trash_bin(s32 objectIndex) {
    D_80165C18[objectIndex].sizeScaling = 1.0f;
    D_80165C18[objectIndex].unk_070 = d_course_banshee_boardwalk_dl_trash_bin;
    D_80165C18[objectIndex].unk_04C = 0;
    D_80165C18[objectIndex].unk_084[7] = 0;
    func_8008B8BC(objectIndex, 0U, 0U, 0U);
    if (gIsMirrorMode != 0) {
        D_80165C18[objectIndex].pos[0] = 1765.0f;
        D_80165C18[objectIndex].pos[2] = 195.0f;
        D_80165C18[objectIndex].unk_0B2[1] = 0x8000;
    } else {
        D_80165C18[objectIndex].pos[0] = -1765.0f;
        D_80165C18[objectIndex].pos[2] = 70.0f;
    }
    D_80165C18[objectIndex].pos[1] = 45.0f;
    func_8008B8F0(objectIndex, 0.0f, 0.0f, 0.0f);
    D_80165C18[objectIndex].unk_0A4 = 0;
    func_80072488(objectIndex);
}

#ifdef MIPS_TO_C
//generated by m2c commit b52d92c2340f6f4ba1aafb464188bb698752fbb0 on Jul-29-2023
extern s32 D_80165594;
extern s16 D_8018CFB0;

void func_8007E00C(s32 objectIndex) {
    s16 temp_v1;
    struct_80165C18_entry *temp_s0;
    u16 temp_t8;
    u16 temp_v0;

    temp_s0 = &D_80165C18[objectIndex];
    temp_t8 = (u16) temp_s0->unk_0A6;
    switch (temp_t8) {
    case 1:
        init_bb_trash_bin(objectIndex);
        return;
    case 3:
        D_8018CFB0 = 1;
        func_80072488(objectIndex);
        return;
    case 4:
        func_8007278C(objectIndex, 0x000000D2);
        if (D_80165594 == 0) {
            if (gCCSelection < 2) {
                func_8007D714(1);
                func_8007D714(1);
            } else {
                func_8007D714(1);
                func_8007D714(1);
                func_8007D714(1);
                func_8007D714(1);
            }
        }
        func_80073CB0(objectIndex, &temp_s0->unk_0A0, -0x00002000, 0, 0x00000400, 0, -1);
        temp_v1 = temp_s0->unk_084[7];
        temp_s0->unk_0B2[2] = (u16) temp_s0->unk_0A0;
        if (temp_v1 == 0) {
            func_800C98B8(temp_s0->pos, temp_s0->unk_038, 0x1901904EU);
            temp_s0->unk_084[7] = 0x0014;
            return;
        }
        temp_s0->unk_084[7] = temp_v1 - 1;
        return;
    case 5:
        temp_v0 = func_800417B4(temp_s0->unk_0B2[2], 0U);
        temp_s0->unk_0B2[2] = temp_v0;
        if (!(temp_v0 & 0xFFFF)) {
            func_80072488(objectIndex);
            return;
        }
    default:
        return;
    case 6:
        temp_s0->unk_0B2[2] = 0;
        temp_s0->unk_084[7] = 0;
        func_80072488(objectIndex);
        D_8018CFB0 = 0;
        break;
    }
}
#else
GLOBAL_ASM("asm/non_matchings/code_80071F00/func_8007E00C.s")
#endif

#ifdef MIPS_TO_C
//generated by mips_to_c commit 3c3b0cede1a99430bfd3edf8d385802b94f91307
void func_8007DDC0(s32); // extern
void func_8007E00C(s32); // extern
extern s32 D_80183EA4;

void func_8007E1AC(void) {
    s32 sp1C;
    s32 temp_a0;

    temp_a0 = D_80183EA4;
    sp1C = temp_a0;
    func_8007E00C(temp_a0);
    if (gModeSelection != TIME_TRIALS) {
        func_8007DDC0(temp_a0);
    }
}
#else
GLOBAL_ASM("asm/non_matchings/code_80071F00/func_8007E1AC.s")
#endif

void func_8007E1F4(s32 objectIndex) {
    f32 sp2C;
    struct_80165C18_entry *temp_s0;

    temp_s0 = &D_80165C18[objectIndex];
    if (temp_s0->unk_04C > 0) {
        temp_s0->unk_04C--;
        if (temp_s0->unk_04C == 0) {
            func_800722CC(objectIndex, 1);
        }
    }
    if (temp_s0->unk_048 > 0) {
        temp_s0->unk_048--;
        if (temp_s0->unk_048 == 0) {
            func_800C9EF4(temp_s0->pos, 0x51028006U);
        }
    }
    if (temp_s0->unk_04C == 0) {
        if ((gCCSelection == CC_50) || (gCCSelection == CC_100) || (gCCSelection == CC_150) || (gCCSelection == CC_EXTRA)) {
            sp2C = 700.0f;
        }
        func_8008A6DC(objectIndex, sp2C);
        if ((func_8007223C(objectIndex, 0x00040000) != 0) && (func_80072354(objectIndex, 1) != 0)) {
            func_800722A4(objectIndex, 1);
            func_800C9D80(temp_s0->pos, temp_s0->unk_038, 0x51028006U);
            func_800726CC(objectIndex, 3);
            if (temp_s0->unk_0A4 > 0) {
                temp_s0->unk_0A4--;
                temp_s0->unk_04C = 0x00000168;
            } else {
                temp_s0->unk_04C = 0x00000168;
            }
            temp_s0->unk_048 = 0x0000012C;
        }
    }
    if (func_8008A8B0(0x000F, 0x0013) == 0) {
        temp_s0->unk_0A4 = 2;
    }
}

void func_8007E358(s32 objectIndex) {
    D_80165C18[objectIndex].pos[0] = -1371.0f * D_8018D01C;
    D_80165C18[objectIndex].pos[1] = 31.0f;
    D_80165C18[objectIndex].pos[2] = -217.0f;
    func_8008B8F0(objectIndex, 0.0f, 0.0f, 0.0f);
    D_80165C18[objectIndex].unk_0A4 = 0;
    D_80165C18[objectIndex].unk_04C = 0;
    D_80165C18[objectIndex].unk_084[7] = 0;
    func_80072488(objectIndex);
}

void func_8007E3EC(s32 objectIndex) {

    switch (D_80165C18[objectIndex].unk_0A6) {
    case 1:
        func_8007E358(objectIndex);
        break;
    case 3:
        D_8018CFE8 = 1;
        func_80072488(objectIndex);
        break;
    case 4:
        func_8007278C(objectIndex, 0x000000D2);
        if (D_80165598 == 0) {
            if (gCCSelection < CC_150) {
                func_8007D714(2);
            } else {
                func_8007D714(2);
                func_8007D714(2);
            }
        }
        break;
    case 5:
        D_8018CFE8 = 0;
        func_80072488(objectIndex);
        break;
    case 0:
    case 2:
    default:
        break;
    }
}

void func_8007E4C4(void) {
    s32 objectIndex = D_80183EA0[2];
    func_8007E3EC(objectIndex);
    if (gModeSelection != TIME_TRIALS) {
        func_8007E1F4(objectIndex);
    }
}

s32 func_8007E50C(s32 objectIndex, Player *player, Camera *camera) {
    s32 sp24;

    sp24 = 0;
    if ((func_80072354(objectIndex, 4) != 0) && (func_80088A58(objectIndex, player, 300.0f) != 0) && (func_8008A0B4(objectIndex, player, camera, 0x4000U) != 0) && (func_8008A060(objectIndex, camera, 0x1555U) != 0)) {
        func_800722A4(objectIndex, 4);
        sp24 = 1;
    }
    return sp24;
}

s32 func_8007E59C(s32 objectIndex) {
    Camera *camera;
    Player *player;
    s32 temp_v0;
    s32 someIndex;

    temp_v0 = 0;
    player = gPlayerOne;
    camera = camera1;
    for (someIndex = 0; someIndex < gPlayerCountSelection1; someIndex++) {
        temp_v0 = func_8007E50C(objectIndex, player++, camera++);
        if (temp_v0 != 0) break;
    }
    return temp_v0;
}

void func_8007E63C(s32 objectIndex) {
    switch (D_80165C18[objectIndex].unk_0A6) {                              /* irregular */
    case 0x32:
        if (f32_step_up_towards(&D_80165C18[objectIndex].unk_028[1], D_80165C18[objectIndex].unk_01C[1] + 15.0, 1.5f) != 0) {
            func_800721C0(objectIndex, 0x00000200);
            func_800722A4(objectIndex, 1);
            func_800722CC(objectIndex, 2);
            func_80072488(objectIndex);
        }
        break;
    case 0x33:
        if (f32_step_down_towards(&D_80165C18[objectIndex].unk_028[1], 0.0f, 2.0f) != 0) {
            if (D_80165C18[objectIndex].unk_028[1] >= 16.0f) {
                D_80165C18[objectIndex].unk_0D2 = 0;
            } else if (D_80165C18[objectIndex].unk_028[1] >= 8.0f) {
                D_80165C18[objectIndex].unk_0D2 = 1;
            } else {
                D_80165C18[objectIndex].unk_0D2 = 2;
            }
            func_800722CC(objectIndex, 1);
            if (func_8007223C(objectIndex, 0x00010000) != 0) {
                func_800722A4(objectIndex, 0x00000010);
                if (func_8007223C(objectIndex, 0x00040000) != 0) {
                    func_800722A4(objectIndex, 0x00000020);
                }
            }
            if (func_80072320(objectIndex, 2) != 0) {
                func_800726CC(objectIndex, 0x00000064);
            } else {
                func_80072488(objectIndex);
            }
        }
        break;
    case 0x34:
        func_80072AAC(objectIndex, 3, 6);
        break;
    case 0x35:
        func_80072AAC(objectIndex, 2, 0x00000032);
        break;
    case 0x36:
        if (D_80165C18[objectIndex].unk_028[1] >= 20.0f) {
            D_80165C18[objectIndex].unk_0D2 = 0;
        } else if (D_80165C18[objectIndex].unk_028[1] >= 18.0f) {
            D_80165C18[objectIndex].unk_0D2 = 1;
        }
        if (f32_step_up_towards(&D_80165C18[objectIndex].unk_028[1], D_80165C18[objectIndex].unk_01C[1], 0.5f) != 0) {
            func_800721E8(objectIndex, 0x00000200);
            func_8007266C(objectIndex);
        }
        break;
    case 0x64:
        func_80072E54(objectIndex, 3, 5, 1, 8, 0);
        break;
    case 0x65:
        func_8007278C(objectIndex, 0x0000001E);
        break;
    case 0x66:
        if (f32_step_up_towards(&D_80165C18[objectIndex].unk_028[1], 20.0f, 1.5f) != 0) {
            func_80072488(objectIndex);
        }
        break;
    case 0x67:
        if (f32_step_down_towards(&D_80165C18[objectIndex].unk_028[1], 0.0f, 1.5f) != 0) {
            if (func_8007223C(objectIndex, 0x00020000) != 0) {
                func_800722A4(objectIndex, 0x00000010);
                if (func_8007223C(objectIndex, 0x00040000) != 0) {
                    func_800722A4(objectIndex, 0x00000020);
                }
            }
            func_80072488(objectIndex);
        }
        break;
    case 0x68:
        if (f32_step_up_towards(&D_80165C18[objectIndex].unk_028[1], 12.0f, 1.5f) != 0) {
            func_80072488(objectIndex);
        }
        break;
    case 0x69:
        if (f32_step_down_towards(&D_80165C18[objectIndex].unk_028[1], 0.0f, 1.5f) != 0) {
            if (func_8007223C(objectIndex, 0x00020000) != 0) {
                func_800722A4(objectIndex, 0x00000010);
                if (func_8007223C(objectIndex, 0x00040000) != 0) {
                    func_800722A4(objectIndex, 0x00000020);
                }
            }
            func_800C98B8(D_80165C18[objectIndex].pos, D_80165C18[objectIndex].unk_038, 0x19018045U);
            func_80072488(objectIndex);
        }
        break;
    case 0x6A:
        if (func_8007326C(objectIndex, 5, 3, 1, 6, 3) != 0) {
            func_80080DE4(objectIndex);
        }
        break;
    case 0x6B:
        if (D_80165C18[objectIndex].unk_028[1] >= 22.0f) {
            D_80165C18[objectIndex].unk_0D2 = 0;
        } else if (D_80165C18[objectIndex].unk_028[1] >= 20.0f) {
            D_80165C18[objectIndex].unk_0D2 = 1;
        } else if (D_80165C18[objectIndex].unk_028[1] >= 18.0f) {
            D_80165C18[objectIndex].unk_0D2 = 2;
        } else if (D_80165C18[objectIndex].unk_028[1] >= 16.0f) {
            D_80165C18[objectIndex].unk_0D2 = 3;
        } else if (D_80165C18[objectIndex].unk_028[1] >= 14.0f) {
            D_80165C18[objectIndex].unk_0D2 = 4;
        } else {
            func_800730BC(objectIndex, 3, 5, 1, 6, -1);
        }
        if (f32_step_up_towards(&D_80165C18[objectIndex].unk_028[1], D_80165C18[objectIndex].unk_01C[1], 0.5f) != 0) {
            func_80072388(objectIndex, 0);
            func_80072488(objectIndex);
        }
        break;
    case 0x6C:
        if (func_8007278C(objectIndex, 0x00000064) != 0) {
            func_800722CC(objectIndex, 2);
            func_800721E8(objectIndex, 0x00000200);
            func_8007266C(objectIndex);
        }
        break;
    case 0xC8:
        if (func_8007278C(objectIndex, 0x0000012C) != 0) {
            func_80072320(objectIndex, 0x00000080);
            func_80072428(objectIndex);
            func_800726CC(objectIndex, 1);
        }
        break;
    case 0x12C:
        if (func_80073E18(objectIndex, &D_80165C18[objectIndex].unk_0B2[1], 0x0400U, 0x00008000) != 0) {
            func_800722CC(objectIndex, 4);
            func_8007266C(objectIndex);
        }
        break;
    }
}

void func_8007EC30(s32 objectIndex) {
    struct_80165C18_entry *temp_s1;

    temp_s1 = &D_80165C18[objectIndex];
    temp_s1->unk_044 = 0.0f;
    temp_s1->unk_010[1] = 0.0f;
    func_8008B80C(objectIndex, 0.0f, 0.0f, 0.0f);
    if (gIsMirrorMode != 0) {
        func_8008B888(objectIndex, 0U, 0x4000U, 0U);
        func_8008B8BC(objectIndex, 0U, 0x4000U, 0U);
    } else {
        func_8008B888(objectIndex, 0U, 0xC000U, 0U);
        func_8008B8BC(objectIndex, 0U, 0xC000U, 0U);
    }
    func_80073444(objectIndex, d_course_bowsers_castle_thwomp_tlut, d_course_bowsers_castle_thwomp_faces, 0x10U, (u16) 0x00000040);
    temp_s1->unk_070 = d_course_bowsers_castle_dl_thwomp;
    temp_s1->unk_0C8 = 0x000C;
    temp_s1->sizeScaling = 1.0f;
    temp_s1->unk_01C[1] = 30.0f;
    func_800721C0(objectIndex, 0x05000220);
    temp_s1->unk_0A4 = 0;
    temp_s1->unk_0DF = 6;
    func_800724DC(objectIndex);
    func_80072488(objectIndex);
}

void func_8007ED6C(s32 objectIndex) {
    s32 stackPadding[4];
    switch (D_80165C18[objectIndex].unk_0A6) {
    case 0:
        break;
    case 1:
        func_8007EC30(objectIndex);
        break;
    case 2:
        func_8007278C(objectIndex, 0x0000003C);
        break;
    case 3:
        func_80072568(objectIndex, 0x00000032);
        break;
    case 4:
        if (func_8007E59C(objectIndex) != 0) {
            func_800725E8(objectIndex, 0x0000012C, 2);
        } else {
            func_800726CC(objectIndex, 2);
        }
        break;
    }
    func_8007E63C(objectIndex);
    func_8008BF18(objectIndex);
    D_80165C18[objectIndex].unk_0BE[1] = D_80165C18[objectIndex].unk_0B2[1];
    func_80073514(objectIndex);
}

void func_8007EE5C(s32 objectIndex) {
    struct_80165C18_entry *temp_s0;

    func_80073444(objectIndex, d_course_bowsers_castle_thwomp_tlut, d_course_bowsers_castle_thwomp_faces, 0x10U, (u16) 0x00000040);
    temp_s0 = &D_80165C18[objectIndex];
    temp_s0->sizeScaling = 1.0f;
    temp_s0->unk_070 = d_course_bowsers_castle_dl_thwomp;
    temp_s0->unk_0C8 = 0x000C;
    func_800721C0(objectIndex, 0x04000220);
    temp_s0->unk_0A4 = 0;
    temp_s0->unk_0DF = 6;
    func_80086E70(objectIndex);
    temp_s0->unk_044 = 0.0f;
    temp_s0->unk_010[1] = 0.0f;
    func_8008B80C(objectIndex, 0.0f, 20.0f, 0.0f);
    temp_s0->unk_01C[1] = 20.0f;
    if (gIsMirrorMode != 0) {
        func_8008B888(objectIndex, 0U, 0x4000U, 0U);
        func_8008B8BC(objectIndex, 0U, 0x4000U, 0U);
    } else {
        func_8008B888(objectIndex, 0U, 0xC000U, 0U);
        func_8008B8BC(objectIndex, 0U, 0xC000U, 0U);
    }
    temp_s0->unk_0AE = 1;
    if (temp_s0->unk_0A0 == 0) {
        temp_s0->unk_0DD = 1;
    } else {
        temp_s0->unk_0DD = 2;
    }
    func_80072488(objectIndex);
}

void func_8007EFBC(s32 objectIndex) {
    switch (D_80165C18[objectIndex].unk_0AE) {
    case 1:
        if (func_80073E18(objectIndex, (u16 *) &D_80165C18[objectIndex].unk_0B2[1], 0x0800U, 0x00008000) != 0) {
            D_80165C18[objectIndex].unk_01C[0] = (f32) ((f64) D_8018D01C * 200.0);
            func_80086FD4(objectIndex);
        }
        break;
    case 2:
        if (f32_step_towards(D_80165C18[objectIndex].unk_028, D_80165C18[objectIndex].unk_01C[0], 4.0f) != 0) {
            func_80086FD4(objectIndex);
        }
        break;
    case 3:
        if (func_80073E18(objectIndex, (u16 *) &D_80165C18[objectIndex].unk_0B2[1], 0x0400U, 0x00008000) != 0) {
            func_800726CC(objectIndex, 3);
            func_80086FD4(objectIndex);
        }
        break;
    case 5:
        if (func_80073E18(objectIndex, (u16 *) &D_80165C18[objectIndex].unk_0B2[1], 0x0400U, 0x0000C000) != 0) {
            func_80086FD4(objectIndex);
        }
        break;
    case 6:
        if (f32_step_down_towards(&D_80165C18[objectIndex].unk_028[2], -100.0f, 2.0f) != 0) {
            func_80086FD4(objectIndex);
        }
        break;
    case 7:
        if (func_80073E18(objectIndex, (u16 *) &D_80165C18[objectIndex].unk_0B2[1], 0x0400U, 0x00004000) != 0) {
            func_80086FD4(objectIndex);
            func_800726CC(objectIndex, 3);
        }
        break;
    case 9:
        if (func_80073E18(objectIndex, (u16 *) &D_80165C18[objectIndex].unk_0B2[1], 0x0400U, 0x00010000) != 0) {
            func_80086FD4(objectIndex);
        }
        break;
    case 10:
        if (f32_step_towards(D_80165C18[objectIndex].unk_028, 0.0f, 4.0f) != 0) {
            func_80086FD4(objectIndex);
        }
        break;
    case 11:
        if (func_80073E18(objectIndex, (u16 *) &D_80165C18[objectIndex].unk_0B2[1], 0x0400U, 0x00010000) != 0) {
            func_80086FD4(objectIndex);
            func_800726CC(objectIndex, 3);
        }
        break;
    case 13:
        if (func_80073E18(objectIndex, (u16 *) &D_80165C18[objectIndex].unk_0B2[1], 0x0400U, 0x00014000) != 0) {
            func_80086FD4(objectIndex);
        }
        break;
    case 14:
        if (f32_step_up_towards(&D_80165C18[objectIndex].unk_028[2], 0.0f, 2.0f) != 0) {
            func_80086FD4(objectIndex);
        }
        break;
    case 15:
        if (func_80073E18(objectIndex, (u16 *) &D_80165C18[objectIndex].unk_0B2[1], 0x0400U, 0x0000C000) != 0) {
            func_80086FD4(objectIndex);
            func_800726CC(objectIndex, 3);
        }
        break;
    case 17:
        func_8008701C(objectIndex, 1);
        break;
    case 0:
    default:
        break;
    }
}

void func_8007F280(s32 objectIndex) {
    switch (D_80165C18[objectIndex].unk_0AE) {
    case 1:
        if (func_80073E18(objectIndex, (u16 *) &D_80165C18[objectIndex].unk_0B2[1], 0x0400U, 0x00010000) != 0) {
            D_80165C18[objectIndex].unk_01C[0] = (f32) ((f64) D_8018D01C * -200.0);
            func_80086FD4(objectIndex);
        }
        break;
    case 2:
        if (f32_step_towards(D_80165C18[objectIndex].unk_028, D_80165C18[objectIndex].unk_01C[0], 4.0f) != 0) {
            func_80086FD4(objectIndex);
        }
        break;
    case 3:
        if (func_80073E18(objectIndex, (u16 *) &D_80165C18[objectIndex].unk_0B2[1], 0x0400U, 0x00010000) != 0) {
            func_800726CC(objectIndex, 3);
            func_80086FD4(objectIndex);
        }
        break;
    case 5:
        if (func_80073E18(objectIndex, (u16 *) &D_80165C18[objectIndex].unk_0B2[1], 0x0400U, 0x00004000) != 0) {
            func_80086FD4(objectIndex);
        }
        break;
    case 6:
        if (f32_step_up_towards(&D_80165C18[objectIndex].unk_028[2], 100.0f, 2.0f) != 0) {
            func_80086FD4(objectIndex);
        }
        break;
    case 7:
        if (func_80073E18(objectIndex, (u16 *) &D_80165C18[objectIndex].unk_0B2[1], 0x0400U, 0x0000C000) != 0) {
            func_80086FD4(objectIndex);
            func_800726CC(objectIndex, 3);
        }
        break;
    case 9:
        if (func_80073E18(objectIndex, (u16 *) &D_80165C18[objectIndex].unk_0B2[1], 0x0400U, 0x00008000) != 0) {
            func_80086FD4(objectIndex);
        }
        break;
    case 10:
        if (f32_step_towards(D_80165C18[objectIndex].unk_028, 0.0f, 4.0f) != 0) {
            func_80086FD4(objectIndex);
        }
        break;
    case 11:
        if (func_80073E18(objectIndex, (u16 *) &D_80165C18[objectIndex].unk_0B2[1], 0x0400U, 0x00008000) != 0) {
            func_80086FD4(objectIndex);
            func_800726CC(objectIndex, 3);
        }
        break;
    case 13:
        if (func_80073E18(objectIndex, (u16 *) &D_80165C18[objectIndex].unk_0B2[1], 0x0400U, 0x0000C000) != 0) {
            func_80086FD4(objectIndex);
        }
        break;
    case 14:
        if (f32_step_down_towards(&D_80165C18[objectIndex].unk_028[2], 0.0f, 2.0f) != 0) {
            func_80086FD4(objectIndex);
        }
        break;
    case 15:
        if (func_80073E18(objectIndex, (u16 *) &D_80165C18[objectIndex].unk_0B2[1], 0x0400U, 0x00014000) != 0) {
            func_80086FD4(objectIndex);
            func_800726CC(objectIndex, 3);
        }
        break;
    case 17:
        func_8008701C(objectIndex, 1);
        break;
    case 0:
    default:
        break;
    }
}

void func_8007F544(s32 objectIndex) {
    switch (D_80165C18[objectIndex].unk_0DD) {                              /* irregular */
    case 1:
        func_8007EFBC(objectIndex);
        break;
    case 2:
        func_8007F280(objectIndex);
        break;
    }
}

void func_8007F5A8(s32 objectIndex) {

    switch (D_80165C18[objectIndex].unk_0A6) {                              /* irregular */
    case 0:
        break;
    case 1:
        func_8007EE5C(objectIndex);
        break;
    case 3:
        func_80072568(objectIndex, 0x00000032);
        break;
    case 4:
        func_80086FD4(objectIndex);
        func_80072488(objectIndex);
        break;
    }
    func_8007E63C(objectIndex);
    func_8007F544(objectIndex);
    func_8008BF18(objectIndex);
    func_80073514(objectIndex);
}

void func_8007F660(s32 objectIndex, s32 arg1, s32 arg2) {
    struct_80165C18_entry *temp_v0;

    func_800722A4(objectIndex, 8);
    func_80086E70(objectIndex);
    temp_v0 = &D_80165C18[objectIndex];
    temp_v0->unk_0DD = 1;
    temp_v0->unk_0D1 = arg1;
    temp_v0->unk_048 = arg2;
}

void func_8007F6C4(s32 objectIndex, s32 playerId) {
    Player *player;

    player = &gPlayerOne[playerId];
    func_800722A4(objectIndex, 8);
    func_80086E70(objectIndex);
    D_80165C18[objectIndex].unk_0DD = 2;
    D_80165C18[objectIndex].unk_01C[0] = player->pos[0] - D_80165C18[objectIndex].unk_010[0];
    D_80165C18[objectIndex].unk_0D1 = playerId;
}

s32 func_8007F75C(s32 playerId) {
    s32 someIndex;
    s32 objectIndex;
    s32 temp_s7;
    s32 var_s6;
    s32 waypoint;

    waypoint = gNearestWaypointByPlayerId[playerId];
    var_s6 = 0;
    if ((waypoint >= 0xAA) && (waypoint < 0xB5)) {
        temp_s7 = random_int(0x0032U) + 0x32;
        for (someIndex = 0; someIndex < D_80165750; someIndex++) {
            objectIndex = D_80183EA0[someIndex];
            if (D_80165C18[objectIndex].unk_0D5 == 3) {
                var_s6 = 1;
                func_8007F660(objectIndex, playerId, temp_s7);
            }
        }
    } else if ((waypoint >= 0xD7) && (waypoint < 0xE2)) {
        for (someIndex = 0; someIndex < D_80165750; someIndex++) {
            objectIndex = D_80183EA0[someIndex];
            if (D_80165C18[objectIndex].unk_0D5 == 3) {
                var_s6 = 1;
                func_8007F6C4(objectIndex, playerId);
            }
        }
    }
    return var_s6;
}

void func_8007F8D8(void) {
    Player *player;
    s32 objectIndex;
    s32 var_s0;
    s32 someIndex;
    s32 var_s4;
    struct_80165C18_entry *object;

    player = gPlayerOne;
    var_s4 = 1;
    for (someIndex = 0; someIndex < D_80165750; someIndex++){
        objectIndex = D_80183EA0[someIndex];
        object = &D_80165C18[objectIndex];
        if (object->unk_0D5 == 3) {
            var_s0 = 0;
            if ((object->unk_0A6 >= 2) && (func_80072354(objectIndex, 8) != 0)) {
                var_s0 = 1;
            }
            var_s4 *= var_s0;
        }
    }
    if (var_s4 != 0) {
        for (var_s0 = 0; var_s0 < 4; var_s0++, player++){
            if ((player->unk_000 & 0x8000) && !(player->unk_000 & 0x1000)) {
                if (func_8007F75C(var_s0) != 0) break;
            }
        }
    }
}

void func_8007FA08(s32 objectIndex) {
    struct_80165C18_entry *temp_s0;

    func_80073444(objectIndex, d_course_bowsers_castle_thwomp_tlut, d_course_bowsers_castle_thwomp_faces, 0x10U, (u16) 0x00000040);
    temp_s0 = &D_80165C18[objectIndex];
    temp_s0->unk_070 = d_course_bowsers_castle_dl_thwomp;
    temp_s0->unk_0C8 = 0x000C;
    temp_s0->sizeScaling = 1.0f;
    func_800721C0(objectIndex, 0x04000220);
    temp_s0->unk_0A4 = 0;
    temp_s0->unk_044 = 0.0f;
    temp_s0->unk_010[1] = 0.0f;
    func_8008B80C(objectIndex, 0.0f, 0.0f, 0.0f);
    func_8008B888(objectIndex, 0U, 0U, 0U);
    if (gIsMirrorMode != 0) {
        func_8008B8BC(objectIndex, 0U, 0xC000U, 0U);
    } else {
        func_8008B8BC(objectIndex, 0U, 0x4000U, 0U);
    }
    temp_s0->unk_038[0] = 0.0f;
    temp_s0->unk_0BE[1] = temp_s0->unk_0B2[1];
    temp_s0->unk_0DD = 1;
    temp_s0->unk_0DF = 8;
    temp_s0->unk_028[1] = 15.0f;
    temp_s0->unk_01C[1] = 15.0f;
    func_80072488(objectIndex);
}

#ifdef MIPS_TO_C
//generated by m2c commit 8267401fa4ef7a38942dcca43353cc1bcc6efabc
extern f32 D_8018D01C;
extern s32 D_8018D400;

void func_8007FB48(s32 objectIndex) {
    struct_80165C18_entry *sp18;
    s16 temp_a0;
    s16 var_a0;
    s32 temp_v0;
    s32 var_v0;
    struct_80165C18_entry *temp_v1;
    u16 temp_t2;
    u16 temp_v0_2;

    temp_v1 = &D_80165C18[objectIndex];
    temp_t2 = (u16) temp_v1->unk_0AE;
    switch (temp_t2) {
    case 1:
        temp_v1->unk_0B0 = 0x00A0;
        temp_v1->unk_028[0] = 0.0f;
        temp_v1->unk_028[2] = 0.0f;
        temp_v1->unk_038[2] = 0.0f;
        func_80086FD4(objectIndex);
        return;
    case 2:
        temp_v0 = temp_v1->unk_048;
        temp_a0 = temp_v1->unk_0B0;
        temp_v1->unk_038[0] = (f32) ((f64) (gPlayerOne[temp_v1->unk_0D1].unk_094 * D_8018D01C) * 1.25);
        if (temp_v0 >= temp_a0) {
            if (temp_a0 == temp_v0) {
                if (D_8018D400 & 1) {
                    temp_v1->unk_038[2] = 1.5f;
                } else {
                    temp_v1->unk_038[2] = -1.5f;
                }
            }
            if ((f64) temp_v1->unk_038[2] >= 0.0) {
                if ((f64) temp_v1->unk_028[2] >= 40.0) {
                    temp_v1->unk_038[2] = -1.5f;
                }
            } else if ((f64) temp_v1->unk_028[2] <= -40.0) {
                temp_v1->unk_038[2] = 1.5f;
            }
        }
        sp18 = temp_v1;
        func_8008775C(objectIndex);
        var_a0 = temp_v1->unk_0B0;
        if (var_a0 < 0x65) {
            sp18 = temp_v1;
            var_a0 = temp_v1->unk_0B0;
            temp_v1->unk_0B2[1] = func_800417B4(temp_v1->unk_0B2[1], (temp_v1->unk_0BE[1] + 0x8000) & 0xFFFF);
            if (var_a0 == 0x0064) {
                temp_v1->unk_0D2 = 1;
                var_a0 = temp_v1->unk_0B0;
            }
        }
        var_v0 = 0;
        if (gIsMirrorMode != 0) {
            if ((f64) temp_v1->unk_028[0] <= -1000.0) {
                goto block_20;
            }
        } else if ((f64) temp_v1->unk_028[0] >= 1000.0) {
block_20:
            var_v0 = 1;
        }
        temp_v1->unk_0B0 = var_a0 - 1;
        if ((temp_v1->unk_0B0 == 0) || (var_v0 != 0)) {
            temp_v1->unk_034 = 0.0f;
            func_800726CC(objectIndex, 3);
            func_80086FD4(objectIndex);
            return;
        }
    default:
        return;
    case 4:
        sp18 = temp_v1;
        f32_step_towards(&temp_v1->unk_028[2], 0.0f, 2.0f);
        f32_step_towards(temp_v1->unk_028, 0.0f, 5.0f);
        if ((f64) (temp_v1->unk_028[2] + temp_v1->unk_028[0]) == 0.0) {
            func_80086FD4(objectIndex);
            return;
        }
        break;
    case 5:
        sp18 = temp_v1;
        temp_v0_2 = func_800417B4(temp_v1->unk_0B2[1], temp_v1->unk_0BE[1]);
        temp_v1->unk_0B2[1] = temp_v0_2;
        if ((temp_v0_2 & 0xFFFF) == temp_v1->unk_0BE[1]) {
            sp18 = temp_v1;
            func_800722CC(objectIndex, 8);
            func_80086FD4(objectIndex);
            temp_v1->unk_0D2 = 0;
        }
        break;
    }
}
#else
GLOBAL_ASM("asm/non_matchings/code_80071F00/func_8007FB48.s")
#endif

void func_8007FEA4(s32 objectIndex) {
    struct_80165C18_entry *temp_v1;

    temp_v1 = &D_80165C18[objectIndex];
    switch (temp_v1->unk_0AE) {
    case 1:
        if (f32_step_towards(&temp_v1->unk_028[0], temp_v1->unk_01C[0], 5.0f) != 0) {
            func_800726CC(objectIndex, 3);
            func_80086FD4(objectIndex);
            break;
        }
    case 0:
    case 2:
        break;
    case 3:
        if (f32_step_towards(&temp_v1->unk_028[0], 0.0f, 5.0f) != 0) {
            func_80086FD4(objectIndex);
            func_800722CC(objectIndex, 8);
        }
        break;
    }
}

void func_8007FF5C(s32 objectIndex)
{
    switch(D_80165C18[objectIndex].unk_0DD) {
        case 1:
            func_8007FB48(objectIndex);
            break;
        case 2:
            func_8007FEA4(objectIndex);
            break;
    }
}

void func_8007FFC0(s32 objectIndex) {
    switch (D_80165C18[objectIndex].unk_0A6) {                              /* irregular */
        case 0:
            break;
        case 1:
            func_8007FA08(objectIndex);
            break;
        case 3:
            func_80072568(objectIndex, 0x00000032);
            break;
        case 4:
            func_80072488(objectIndex);
            func_80086FD4(objectIndex);
            break;
    }
    func_8007E63C(objectIndex);
    func_8007FF5C(objectIndex);
    func_8008BF18(objectIndex);
    func_80073514(objectIndex);
}

void func_80080078(s32 objectIndex) {
    struct_80165C18_entry *temp_s0;

    func_80073444(objectIndex, d_course_bowsers_castle_thwomp_tlut, d_course_bowsers_castle_thwomp_faces, 0x10U, (u16) 0x00000040);
    temp_s0 = &D_80165C18[objectIndex];
    temp_s0->unk_070 = d_course_bowsers_castle_dl_thwomp;
    temp_s0->unk_0C8 = 0x000C;
    temp_s0->sizeScaling = 1.0f;
    func_800721C0(objectIndex, 0x04000220);
    temp_s0->unk_0A4 = 2;
    temp_s0->unk_0DF = 8;
    func_8008B888(objectIndex, 0U, 0U, 0U);
    temp_s0->unk_044 = 0.0f;
    temp_s0->unk_010[1] = 0.0f;
    func_8008B80C(objectIndex, 0.0f, 0.0f, 0.0f);
    temp_s0->unk_01C[1] = 30.0f;
    if (gIsMirrorMode != 0) {
        func_8008B8BC(objectIndex, 0U, 0x4000U, 0U);
    } else {
        func_8008B8BC(objectIndex, 0U, 0xC000U, 0U);
    }
    switch (temp_s0->unk_0A0) {                              /* irregular */
    case 0:
        temp_s0->unk_050 = 2;
        break;
    case 1:
        temp_s0->unk_050 = 0x0000003C;
        break;
    case 2:
        temp_s0->unk_050 = 0x00000078;
        break;
    case 3:
        temp_s0->unk_050 = 0x000000B4;
        break;
    }
    func_800724DC(objectIndex);
    func_80072488(objectIndex);
}

void func_800801FC(s32 objectIndex) {
    struct_80165C18_entry *temp_v0;

    temp_v0 = &D_80165C18[objectIndex];
    switch (temp_v0->unk_0A6) {
    case 0:
        break;
    case 1:
        func_80080078(objectIndex);
        break;
    case 2:
        func_8007278C(objectIndex, temp_v0->unk_050);
        break;
    case 3:
        func_80072568(objectIndex, 0x00000032);
        break;
    case 4:
        temp_v0->unk_050 = 0x0000003C;
        func_800726CC(objectIndex, 2);
        break;
    }
    func_8007E63C(objectIndex);
    func_8008BF18(objectIndex);
    func_80073514(objectIndex);
}

void func_800802C0(s32 objectIndex) {
    struct_80165C18_entry *temp_s0;

    temp_s0 = &D_80165C18[objectIndex];
    temp_s0->unk_0D8 = 0;
    func_80073444(objectIndex, d_course_bowsers_castle_thwomp_tlut, d_course_bowsers_castle_thwomp_faces, 0x10U, (u16) 0x00000040);
    temp_s0->unk_070 = d_course_bowsers_castle_dl_thwomp;
    temp_s0->unk_0D2 = 0;
    temp_s0->unk_0C8 = 0x000C;
    temp_s0->sizeScaling = 1.5f;
    func_800721C0(objectIndex, 0x05000220);
    temp_s0->unk_0A4 = 1;
    temp_s0->unk_0DF = 6;
    func_8008B80C(objectIndex, 0.0f, 0.0f, 0.0f);
    func_8008B888(objectIndex, 0U, 0U, 0U);
    temp_s0->unk_044 = 0.0f;
    temp_s0->unk_010[1] = 0.0f;
    temp_s0->unk_028[1] = 10.0f;
    temp_s0->unk_01C[1] = 10.0f;
    if (gIsMirrorMode != 0) {
        func_8008B8BC(objectIndex, 0U, 0x4000U, 0U);
    } else {
        func_8008B8BC(objectIndex, 0U, 0xC000U, 0U);
    }
    temp_s0->unk_028[0] = 0.0f;
    temp_s0->unk_028[2] = 0.0f;
    func_800724DC(objectIndex);
    func_80072488(objectIndex);
}

void func_80080408(s32 objectIndex) {
    switch (D_80165C18[objectIndex].unk_0A6) {
    case 0:
        break;
    case 1:
        func_800802C0(objectIndex);
        break;
    case 2:
        func_8008A6DC(objectIndex, 100.0f);
        if (func_8007223C(objectIndex, 0x00040000) != 0) {
            func_800C98B8(D_80165C18[objectIndex].pos, D_80165C18[objectIndex].unk_038, 0x19018045U);
            func_80072488(objectIndex);
        }
        break;
    case 3:
        if (func_800730BC(objectIndex, 3, 5, 1, 6, 6) != 0) {
            D_80165C18[objectIndex].unk_0D2 = 0;
        }
        break;
    case 4:
        if (func_8007278C(objectIndex, 0x0000012C) != 0) {
            func_800726CC(objectIndex, 2);
        }
        break;
    }
    func_8008BF18(objectIndex);
    func_80073514(objectIndex);
}

void func_80080524(s32 objectIndex) {
    struct_80165C18_entry *temp_s0;

    func_80073444(objectIndex, d_course_bowsers_castle_thwomp_tlut, d_course_bowsers_castle_thwomp_faces, 0x10U, (u16) 0x00000040);
    temp_s0 = &D_80165C18[objectIndex];
    temp_s0->unk_070 = d_course_bowsers_castle_dl_thwomp;
    temp_s0->unk_0C8 = 0x000C;
    temp_s0->unk_0D2 = 0;
    temp_s0->sizeScaling = 1.0f;
    func_800721C0(objectIndex, 0x04000220);
    temp_s0->unk_0A4 = 0;
    temp_s0->unk_0DF = 0x0A;
    func_80086E70(objectIndex);
    func_8008B80C(objectIndex, 0.0f, 0.0f, 0.0f);
    temp_s0->unk_044 = 70.0f;
    temp_s0->unk_010[1] = 70.0f;
    temp_s0->unk_01C[1] = 0.0f;
    func_8008B888(objectIndex, 0U, 0U, 0U);
    if ((gIsMirrorMode != 0) || (gGamestate == 9)) {
        func_8008B8BC(objectIndex, 0U, 0xC000U, 0U);
    } else {
        func_8008B8BC(objectIndex, 0U, 0x4000U, 0U);
    }
    switch (temp_s0->unk_0A0) {                              /* irregular */
    case 0:
        temp_s0->unk_0DD = 2;
        temp_s0->unk_038[2] = -1.0f;
        break;
    case 1:
        temp_s0->unk_0DD = 2;
        temp_s0->unk_038[2] = -1.5f;
        break;
    }
    func_800722A4(objectIndex, 0x00000080);
    func_80072488(objectIndex);
}

void func_800806BC(s32 objectIndex) {
    switch (D_80165C18[objectIndex].unk_0AE) {
    case 0:
        break;
    case 1:
        if (f32_step_towards(&D_80165C18[objectIndex].unk_028[2], 250.0f, D_80165C18[objectIndex].unk_038[2]) != 0) {
            D_80165C18[objectIndex].unk_038[2] = -D_80165C18[objectIndex].unk_038[2];
            func_80086FD4(objectIndex);
        }
        break;
    case 2:
        if (f32_step_towards(&D_80165C18[objectIndex].unk_028[2], 0.0f, D_80165C18[objectIndex].unk_038[2]) != 0) {
            D_80165C18[objectIndex].unk_038[2] = -D_80165C18[objectIndex].unk_038[2];
            func_8008701C(objectIndex, 1);
        }
        break;
    }
}

void func_8008078C(s32 objectIndex) {
    switch (D_80165C18[objectIndex].unk_0AE) {
    case 0:
        break;
    case 1:
        if (f32_step_towards(&D_80165C18[objectIndex].unk_028[2], -250.0f, D_80165C18[objectIndex].unk_038[2]) != 0) {
            D_80165C18[objectIndex].unk_038[2] = -D_80165C18[objectIndex].unk_038[2];
            func_80086FD4(objectIndex);
        }
        break;
    case 2:
        if (f32_step_towards(&D_80165C18[objectIndex].unk_028[2], 0.0f, D_80165C18[objectIndex].unk_038[2]) != 0) {
            D_80165C18[objectIndex].unk_038[2] = -D_80165C18[objectIndex].unk_038[2];
            func_8008701C(objectIndex, 1);
        }
        break;
    }
}

void func_8008085C(s32 objectIndex) {
    switch (D_80165C18[objectIndex].unk_0DD) {
    case 1:
        func_800806BC(objectIndex);
        break;
    case 2:
        func_8008078C(objectIndex);
        break;
    }
    func_8008BF18(objectIndex);
}

#ifdef MIPS_TO_C
//generated by m2c commit eefca95b040d7ee0c617bc58f9ac6cd1cf7bce87 on Aug-10-2023
extern s32 D_8018D40C;
extern s16 gCutsceneShotTimer;

void func_800808CC(s32 arg0) {
    struct_80165C18_entry *sp20;
    s16 var_v1;
    struct_80165C18_entry *temp_t0;

    temp_t0 = &D_80165C18[arg0];
    var_v1 = temp_t0->unk_0A6;
    switch (var_v1) {                               /* irregular */
    case 0:
        break;
    case 1:
        sp20 = temp_t0;
        func_80080524(arg0);
block_6:
        var_v1 = temp_t0->unk_0A6;
        break;
    case 2:
        sp20 = temp_t0;
        func_800730BC(arg0, 3, 5, 1, 6, -1);
        goto block_6;
    }
    if (var_v1 >= 2) {
        sp20 = temp_t0;
        func_8007E63C(arg0);
        func_8008085C(arg0);
        func_80073514(arg0);
        if (gGamestate != 9) {
            if ((D_8018D40C == 0) && (temp_t0->unk_0A6 == 2)) {
                func_800C98B8(temp_t0->pos, temp_t0->unk_038, 0x19036045U);
            }
        } else if ((gCutsceneShotTimer < 0xBF) && (((s16) gCutsceneShotTimer % 88) == 0x0000001E)) {
            func_800C98B8(temp_t0->pos, temp_t0->unk_038, 0x19036045U);
        }
    }
}
#else
GLOBAL_ASM("asm/non_matchings/code_80071F00/func_800808CC.s")
#endif

void func_80080A14(s32 objectIndex, Player *player) {
    if (func_80088A58(objectIndex, player, 12.0f) != 0) {
        player->boundingBoxCorners[0].unk_14 |= 3;
    }
}

void func_80080A4C(s32 objectIndex, s32 cameraPlayerId) {
    Camera *camera = &camera1[cameraPlayerId];
    Player *player = &gPlayerOne[cameraPlayerId];

    if (gScreenModeSelection != 3) {
        if ((func_80072320(objectIndex, 0x00000010) != 0) && (func_80088A58(objectIndex, player, 500.0f) != 0)) {
            func_8001CA10(camera);
            func_800C98B8(D_80165C18[objectIndex].pos, D_80165C18[objectIndex].unk_038, 0x1900800FU);
        }
    }
}

void func_80080B28(s32 objectIndex, s32 playerId) {
    f32 temp_f0;
    Player *temp_s0;

    temp_s0 = &gPlayerOne[playerId];
    if (func_8007223C(objectIndex, 0x00000200) != 0) {
        if (!(temp_s0->statusEffects & 0x100)) {
            temp_f0 = func_80088F54(objectIndex, temp_s0);
            if ((temp_f0 <= 9.0) && !(temp_s0->unk_0BC & 0x04000000) && (func_80088D18(objectIndex, temp_s0) != 0)) {
                if ((temp_s0->unk_000 & 0x8000) && !(temp_s0->unk_000 & 0x100)) {
                    if (!(temp_s0->unk_0BC & 0x200)) {
                        func_80089474(objectIndex, playerId, 1.4f, 1.1f, 0x1900A04CU);
                    } else if (func_80072354(objectIndex, 0x00000040) != 0) {
                        if (temp_s0->unk_000 & 0x1000) {
                            func_800C98B8(temp_s0->pos, temp_s0->unk_034, 0x1901A24AU);
                        } else {
                            func_800C9060((u8) playerId, 0x1901A24AU);
                        }
                        func_80080DE4(objectIndex);
                        func_80075304(D_80165C18[objectIndex].pos, 3, 3, D_8018D3C4);
                        func_800721E8(objectIndex, 0x00000200);
                        func_800722A4(objectIndex, 0x00000040);
                        func_80086F60(objectIndex);
                        func_800726CC(objectIndex, 0x000000C8);
                    }
                }
            } else if ((temp_f0 <= 17.5) && (func_80072320(objectIndex, 1) != 0) && (func_80088A58(objectIndex, temp_s0, (temp_s0->unk_094 * 0.5) + 7.0) != 0)) {
                if ((temp_s0->unk_000 & 0x8000) && !(temp_s0->unk_000 & 0x100)) {
                    if (func_8007223C(objectIndex, 0x04000000) != 0) {
                        func_80072180();
                    }
                    func_800722A4(objectIndex, 2);
                    temp_s0->unk_040 = (s16) objectIndex;
                    temp_s0->unk_046 |= 2;
                    temp_s0->statusEffects |= 0x100;
                    func_80088FF0(temp_s0);
                }
            }
        } else {
            func_80088FF0(temp_s0);
        }
    }
}

void func_80080DE4(s32 arg0) {
    Player *player;
    s32 var_v1;

    player = gPlayerOne;
    for (var_v1 = 0; var_v1 < 8; var_v1++, player++) {
        if (arg0 == player->unk_040) {
            player->statusEffects &= ~0x100;
            player->unk_040 = -1;
        }
    }
}

#ifdef MIPS_TO_C
//generated by m2c commit eefca95b040d7ee0c617bc58f9ac6cd1cf7bce87 on Aug-10-2023
f32 D_800E594C[5][2] = {
    { -8.0f, 8.0f },
    { 8.0f, 8.0f },
    { 0.0f, 0.0f },
    { 8.0f, -8.0f },
    { -8.0f, -8.0f },
};
s16 D_800E597C[6] = { 0, 0, 0x4000, 0x8000, 0x8000, 0xC000 };

void func_80080E8C(s32 objectIndex1, s32 objectIndex2, s32 arg2) {
    f32 sp38;
    struct_80165C18_entry *sp2C;
    s32 sp28;
    f32 *sp24;
    f32 *temp_v1;
    s32 temp_t1;
    s32 temp_t7;
    struct_80165C18_entry *temp_s0;
    struct_80165C18_entry *temp_v0;
    u16 temp_s1;

    func_800723A4(objectIndex1, arg2);
    temp_t1 = arg2 * 2;
    temp_v1 = &(*D_800E594C)[temp_t1];
    temp_s0 = &D_80165C18[objectIndex1];
    temp_s0->unk_0D5 = 2;
    sp24 = temp_v1;
    sp28 = temp_t1;
    temp_v0 = &D_80165C18[objectIndex2];
    temp_s1 = temp_v0->unk_0BE[1];
    sp2C = temp_v0;
    sp38 = func_800416D8(temp_v1->unk4, temp_v1->unk0, temp_s1);
    temp_s0->unk_010[0] = temp_v0->pos[0] + func_80041724(temp_v1->unk4, temp_v1->unk0, temp_s1 & 0xFFFF);
    temp_s0->unk_010[1] = (f32) ((f64) temp_v0->unk_044 - 9.0);
    temp_s0->unk_010[2] = temp_v0->pos[2] + sp38;
    temp_t7 = (*(D_800E597C + sp28) + temp_v0->unk_0BE[1]) & 0xFFFF;
    temp_s0->unk_038[0] = (f32) ((f64) sins(temp_t7 & 0xFFFF) * 0.6);
    temp_s0->unk_038[2] = (f32) ((f64) coss(temp_t7 & 0xFFFF) * 0.6);
}
#else
GLOBAL_ASM("asm/non_matchings/code_80071F00/func_80080E8C.s")
#endif

void func_80080FEC(s32 arg0) {
    s32 temp_v0;
    s32 var_s0;

    for (var_s0 = 0; var_s0 < 6; var_s0++) {
        temp_v0 = func_80072044(D_8018C3F0, &D_80183E4C, D_8018C3F0_SIZE);
        if (temp_v0 == -1) break;
        func_80080E8C(temp_v0, arg0, var_s0);
    }
}

void func_80081080(s32 objectIndex) {
    struct_80165C18_entry *temp_v0;

    temp_v0 = &D_80165C18[objectIndex];
    temp_v0->activeTexture = D_8018D490;
    temp_v0->textureList = D_8018D490;
    temp_v0->unk_0A0 = 0x00FF;
    temp_v0->unk_0BE[1] = 0;
    temp_v0->unk_0B2[0] = 0;
    temp_v0->unk_0B2[2] = 0;
    temp_v0->unk_028[0] = 0.0f;
    temp_v0->unk_028[1] = 0.0f;
    temp_v0->unk_028[2] = 0.0f;
    temp_v0->sizeScaling = 0.25f;
    func_80072488(objectIndex);
}

void func_800810F4(s32 objectIndex) {
    switch (D_80165C18[objectIndex].unk_0A6) {                              /* irregular */
    case 0:
        break;
    case 1:
        func_80081080(objectIndex);
        break;
    case 2:
        func_8008775C(objectIndex);
        f32_step_up_towards(&D_80165C18[objectIndex].unk_028[1], 14.0f, 0.5f);
        func_8007415C(objectIndex, &D_80165C18[objectIndex].sizeScaling, 0.25f, 0.75f, 0.025f, 1, 0);
        if (func_80073B00(objectIndex, &D_80165C18[objectIndex].unk_0A0, 0x000000FF, 0, 4, 0, 0) != 0) {
            func_80072488(objectIndex);
        }
        break;
    case 3:
        func_80072428(objectIndex);
        break;
    }
    func_8008BF18(objectIndex);
}

void func_80081208(void) {

}

void func_80081210(void) {
    Player *player;
    s32 var_s2;
    s32 var_s2_3;
    s32 var_s4;

    D_80165834[0] += 0x100;
    D_80165834[1] += 0x200;
    for (var_s4 = 0; var_s4 < D_80165750; var_s4++) {
        var_s2 = D_80183EA0[var_s4];
        func_800722CC(var_s2, 0x00000010);
        func_8008A4CC(var_s2);
    }
    func_8007F8D8();
    for (var_s4 = 0; var_s4 < D_80165750; var_s4++) {
        var_s2 = D_80183EA0[var_s4];
        if (D_80165C18[var_s2].unk_0A6 != 0) {
            switch (D_80165C18[var_s2].unk_0D5) {
            case 1:
                func_8007ED6C(var_s2);
                break;
            case 2:
                func_8007F5A8(var_s2);
                break;
            case 3:
                func_8007FFC0(var_s2);
                break;
            case 4:
                func_800801FC(var_s2);
                break;
            case 6:
                func_80080408(var_s2);
                break;
            case 5:
                func_800808CC(var_s2);
                break;
            }
        }
    }
    player = gPlayerOne;
    for (var_s4 = 0; var_s4 < 8; var_s4++, player++) {
        player->boundingBoxCorners[0].unk_14 &= ~3;
        player->unk_046 &= ~0x0006;
        for (var_s2_3 = 0; var_s2_3 < D_80165750; var_s2_3++) {
            var_s2 = D_80183EA0[var_s2_3];
            if (!(player->unk_0BC & 0x80000000)) {
                func_80080B28(var_s2, var_s4);
            }
            if (func_8007223C(var_s2, 0x00020000) != 0) {
                func_80080A14(var_s2, player);
            }
            if (func_8007223C(var_s2, 0x00010000) != 0) {
                func_80080A4C(var_s2, var_s4);
            }
        }
    }
    func_8007542C(3);
    for (var_s4 = 0; var_s4 < D_80165750; var_s4++) {
        var_s2 = D_80183EA0[var_s4];
        if (func_80072320(var_s2, 0x00000020) == 0) continue;

        func_800722CC(var_s2, 0x00000020);
        func_80080FEC(var_s2);
    }
    for (var_s4 = 0; var_s4 < D_8018C3F0_SIZE; var_s4++) {
        var_s2 = D_8018C3F0[var_s4];
        if (var_s2 == -1) continue;
        if (D_80165C18[var_s2].unk_0A6 == 0) continue;
        func_800810F4(var_s2);
        if (D_80165C18[var_s2].unk_0A6 != 0) continue;
        func_80072100(&D_8018C3F0[var_s4]);
    }
}

void func_8008153C(s32 objectIndex) {
    s32 stackPadding[3];
    s32 sp70;
    s32 var_s1;
    s32 var_s7;
    s32 loopObjectIndex;

    if (gPlayerCountSelection1 == 1) {
        sp70 = 8;
    } else {
        sp70 = 4;
    }

    for (var_s7 = 0; var_s7 < sp70; var_s7++) {
        for (var_s1 = 0; var_s1 < D_8018C3F0_SIZE; var_s1++) {
            loopObjectIndex = D_8018C3F0[var_s1];

            if (D_80165C18[loopObjectIndex].unk_0A6 != 0) continue;

            func_800723A4(loopObjectIndex, 0);
            D_80165C18[loopObjectIndex].activeTLUT = d_course_moo_moo_farm_mole_dirt;
            D_80165C18[loopObjectIndex].tlutList = d_course_moo_moo_farm_mole_dirt;
            D_80165C18[loopObjectIndex].sizeScaling = 0.15f;
            D_80165C18[loopObjectIndex].unk_038[1] = random_int(0x000AU);
            D_80165C18[loopObjectIndex].unk_038[1] = (D_80165C18[loopObjectIndex].unk_038[1] * 0.1) + 4.8;
            D_80165C18[loopObjectIndex].unk_034 = random_int(5U);
            D_80165C18[loopObjectIndex].unk_034 = (D_80165C18[loopObjectIndex].unk_034 * 0.01) + 0.8;
            D_80165C18[loopObjectIndex].unk_0B2[1] = (0x10000 / sp70) * var_s1;
            D_80165C18[loopObjectIndex].unk_010[0] = D_80165C18[objectIndex].unk_010[0];
            D_80165C18[loopObjectIndex].unk_010[1] = D_80165C18[objectIndex].unk_010[1] - 13.0;
            D_80165C18[loopObjectIndex].unk_010[2] = D_80165C18[objectIndex].unk_010[2];
            break;
        }
    }
}

void func_80081790(s32 objectIndex) {
    switch (D_80165C18[objectIndex].unk_0A6) {   
    case 0:
        break;                           /* irregular */
    case 1:
        if (func_80087E08(objectIndex, D_80165C18[objectIndex].unk_038[1], 0.3f, D_80165C18[objectIndex].unk_034, D_80165C18[objectIndex].unk_0B2[1], 0x00000032) != 0) {
            func_80072488(objectIndex);
        }
        func_8008BF18(objectIndex);
        break;
    case 2:
        func_80072428(objectIndex);
        func_80086F60(objectIndex);
        break;
    }
}

void func_80081848(s32 objectIndex) {
    func_80073444(objectIndex, d_course_moo_moo_farm_mole_tlut, d_course_moo_moo_farm_mole_frames, 0x20U, (u16) 0x00000040);
    D_80165C18[objectIndex].sizeScaling = 0.15f;
    D_80165C18[objectIndex].unk_0D2 = 0;
    func_8008B80C(objectIndex, 0.0f, 0.0f, 0.0f);
    func_8008B888(objectIndex, 0U, 0U, 0U);
    func_8008B8BC(objectIndex, 0U, 0U, 0x8000U);
    D_80165C18[objectIndex].unk_0C8 = 6;
    D_80165C18[objectIndex].unk_038[1] = 4.0f;
    func_800721C0(objectIndex, 0x04000000);
    func_80072488(objectIndex);
}

void func_80081924(s32 objectIndex) {
    switch (D_80165C18[objectIndex].unk_0AE) {
    case 1:
        if (f32_step_up_towards(&D_80165C18[objectIndex].unk_028[1], 9.0f, 0.7f) != 0) {
            func_80086FD4(objectIndex);
        }
        break;
    case 2:
        func_800871AC(objectIndex, 0x0000000A);
        break;
    case 3:
        if (f32_step_down_towards(&D_80165C18[objectIndex].unk_028[1], 3.0f, 1.0f) != 0) {
            func_80086F60(objectIndex);
        }
        break;
    case 4:
        func_80087D24(objectIndex, 3.6f, 0.25f, 0.0f);
        break;
    case 5:
        func_80086F60(objectIndex);
        break;
    case 10:
        D_80165C18[objectIndex].unk_0B2[2] += 0x1000;
        D_80165C18[objectIndex].unk_038[1] -= 0.184;
        func_8008751C(objectIndex);
        func_80087710(objectIndex);
        if (D_80165C18[objectIndex].pos[1] <= -10.0) {
            func_80086F60(objectIndex);
        }
        break;
    case 0:
    default:
        break;
    }
}

void func_80081A88(s32 objectIndex) {
    switch (D_80165C18[objectIndex].unk_0DD) {                              /* irregular */
    case 0:
        break;
    case 1:
        func_8008B724(objectIndex);
        break;
    case 2:
        func_80081924(objectIndex);
        break;
    }
    func_8008BF18(objectIndex);
}

#ifdef MIPS_TO_C
//generated by m2c commit b52d92c2340f6f4ba1aafb464188bb698752fbb0 on Jul-25-2023
extern ? D_8018D198;
extern ? D_8018D1A8;
extern ? D_8018D1B8;

void func_80081AFC(s32 objectIndex, s32 arg1) {
    ? *sp2C;
    s16 temp_v1;
    s32 temp_v0;
    struct_80165C18_entry *temp_s0;

    temp_s0 = &D_80165C18[objectIndex];
    temp_v1 = temp_s0->unk_0A6;
    switch (temp_v1) {                              /* irregular */
    case 0x1:
        func_80081848(objectIndex);
        break;
    case 0x2:
        temp_v0 = temp_s0->unk_04C;
        if (temp_v0 == 0) {
            func_80086EAC(objectIndex, 2, 1);
            func_80072488(objectIndex);
            func_800721C0(objectIndex, 0x00000200);
        } else {
            temp_s0->unk_04C = temp_v0 - 1;
        }
        break;
    case 0x3:
        if (temp_s0->unk_0AE == 0) {
            func_80086EAC(objectIndex, 2, 4);
            func_8008153C(objectIndex);
            func_80072488(objectIndex);
            func_800C98B8(temp_s0->pos, temp_s0->unk_038, 0x19018007U);
        }
        break;
    case 0x4:
        if (func_80072E54(objectIndex, 1, 6, 1, 2, 0) != 0) {
            func_800726CC(objectIndex, 0x00000064);
        }
        break;
    case 0xA:
        func_80072E54(objectIndex, 1, 6, 1, 0, -1);
        if (temp_s0->unk_0AE == 0) {
            func_800726CC(objectIndex, 0x00000064);
        }
        break;
    case 0x64:
        if (temp_s0->unk_0AE == 0) {
            func_800721E8(objectIndex, 0x00000200);
            func_80072428(objectIndex);
            switch (arg1) {                         /* switch 1; irregular */
            case 1:                                 /* switch 1 */
                sp2C = &D_8018D198;
                break;
            case 2:                                 /* switch 1 */
                sp2C = &D_8018D1A8;
                break;
            case 3:                                 /* switch 1 */
                sp2C = &D_8018D1B8;
                break;
            }
            *(sp2C + temp_s0->unk_0A4) = 0;
        }
        break;
    }
    if (temp_s0->unk_0A6 >= 2) {
        func_80073514(objectIndex);
    }
}
#else
GLOBAL_ASM("asm/non_matchings/code_80071F00/func_80081AFC.s")
#endif

void func_80081D34(s32 objectIndex) {
    Player *var_s1;
    Camera *var_s4;
    s32 var_s2;
    s32 var_s5;
    struct_80165C18_entry *temp_s0;

    var_s5 = 0;
    var_s1 = gPlayerOne;
    var_s4 = camera1;
    for (var_s2 = 0; var_s2 < D_8018D158; var_s2++, var_s1++, var_s4++) {
        if ((func_8007223C(objectIndex, 0x00000200) != 0) && !(var_s1->unk_0BC & 0x80000000) && (func_80088DA4(objectIndex, var_s1) != 0)) {
            if ((var_s1->unk_000 & 0x8000) && !(var_s1->unk_000 & 0x100)) {
                var_s5 = 1;
                temp_s0 = &D_80165C18[objectIndex];
                if (func_8007223C(objectIndex, 0x04000000) != 0) {
                    func_80072180();
                }
                if (var_s1->unk_0BC & 0x200) {
                    func_800C9060(var_s2, 0x1900A046U);
                } else {
                    var_s1->statusEffects |= 2;
                }
                temp_s0->unk_0BE[1] = var_s4->rot[1];
                temp_s0->unk_038[1] = (var_s1->unk_094 / 2) + 3.0;
                temp_s0->unk_034 = var_s1->unk_094 + 1.0;
                if (temp_s0->unk_038[1] >= 5.0) {
                    temp_s0->unk_038[1] = 5.0f;
                }
                if (temp_s0->unk_034 >= 4.0) {
                    temp_s0->unk_038[1] = 4.0f;
                }
            }
        }
    }
    if (var_s5 != 0) {
        temp_s0 = &D_80165C18[objectIndex];
        func_800721E8(objectIndex, 0x00000200);
        func_80086F60(objectIndex);
        func_8008B7D4(objectIndex, temp_s0->pos[0], temp_s0->pos[1], temp_s0->pos[2]);
        func_8008B80C(objectIndex, 0.0f, 0.0f, 0.0f);
        func_80086EAC(objectIndex, 2, 0x000A);
        func_800726CC(objectIndex, 0x0000000A);
    }
}

#ifdef MIPS_TO_C
//generated by m2c commit 8267401fa4ef7a38942dcca43353cc1bcc6efabc
extern f32 D_8018D01C;
extern s8 D_8018D198;
extern s8 D_8018D1A8;
extern s8 D_8018D1B8;
static ? D_800E6360;                                /* unable to generate initializer */

void func_80081FF4(s32 objectIndex, s32 arg1) {
    s32 sp2C;
    s16 sp28;
    ? *sp20;
    struct_80165C18_entry *sp18;
    ? *var_a2;
    s16 var_v1;
    s32 var_a0;
    s8 *temp_v0;
    struct_80165C18_entry *temp_a3;
    void *temp_v0_2;

    func_800723A4(objectIndex, 0);
    temp_a3 = &D_80165C18[objectIndex];
    temp_a3->unk_04C = random_int(0x001EU) + 5;
    switch (arg1) {                                 /* irregular */
    case 1:
        var_a2 = &D_8018D198;
        sp28 = 0;
        sp2C = 8;
block_7:
        sp20 = var_a2;
        break;
    case 2:
        var_a2 = &D_8018D1A8;
        sp28 = 0x0018;
        sp2C = 0x0000000B;
        goto block_7;
    case 3:
        var_a2 = &D_8018D1B8;
        sp28 = 0x0039;
        sp2C = 0x0000000C;
        goto block_7;
    }
    sp18 = temp_a3;
    var_v1 = random_int(sp2C & 0xFFFF);
    var_a0 = 0;
    if (sp2C > 0) {
loop_9:
        temp_v0 = var_v1 + sp20;
        var_a0 += 1;
        if (*temp_v0 != 0) {
            var_v1 += 1;
            if (var_v1 == sp2C) {
                var_v1 = 0;
            }
            if (var_a0 != sp2C) {
                goto loop_9;
            }
        } else {
            *temp_v0 = 1;
            temp_a3->unk_0A4 = var_v1;
        }
    }
    temp_v0_2 = (sp28 * 2) + (var_v1 * 6) + &D_800E6360;
    temp_a3->unk_010[0] = (f32) temp_v0_2->unk0 * D_8018D01C;
    temp_a3->unk_010[1] = (f32) ((f64) temp_v0_2->unk2 - 9.0);
    temp_a3->unk_010[2] = (f32) temp_v0_2->unk4;
}
#else
GLOBAL_ASM("asm/non_matchings/code_80071F00/func_80081FF4.s")
#endif

void func_800821AC(s32 objectIndex, s32 arg1) {
    if (D_80165C18[objectIndex].unk_0A6 != 0) {
        func_80081AFC(objectIndex, arg1);
        func_80081A88(objectIndex);
        func_80081D34(objectIndex);
    }
}

void func_800821FC(void) {
    s32 var_s1;
    s32 var_s2;
    s32 stackPadding;

    for (var_s1 = 0; var_s1 < D_8018D1C8; var_s1++) {
        var_s2 = D_80183EA0[var_s1];
        if (D_80165C18[var_s2].unk_0A6 == 0) {
            if (func_8008A8B0(8, 9) != 0) {
                func_80081FF4(var_s2, 1);
            }
        } else {
            func_800821AC(var_s2, 1);
        }
    }

    for (var_s1 = 0; var_s1 < D_8018D1D0; var_s1++) {
        var_s2 = D_80183F28[var_s1];
        if (D_80165C18[var_s2].unk_0A6 == 0) {
            if (func_8008A8B0(0x0010, 0x0013) != 0) {
                func_80081FF4(var_s2, 2);
            }
        } else {
            func_800821AC(var_s2, 2);
        }
    }

    for (var_s1 = 0; var_s1 < D_8018D1D8; var_s1++) {
        var_s2 = D_8018BFA8[var_s1];
        if (D_80165C18[var_s2].unk_0A6 == 0) {
            if (func_8008A8B0(0x0011, 0x0014) != 0) {
                func_80081FF4(var_s2, 3);
            }
        } else {
            func_800821AC(var_s2, 3);
        }
    }

    for (var_s1 = 0; var_s1 < D_8018C3F0_SIZE; var_s1++) {
        var_s2 = D_8018C3F0[var_s1];
        if (D_80165C18[var_s2].unk_0A6 != 0) {
            func_80081790(var_s2);
        }
    }
}

#ifdef MIPS_TO_C
//generated by m2c commit 8267401fa4ef7a38942dcca43353cc1bcc6efabc
extern ? d_course_koopa_troopa_beach_unk4;
extern ? d_course_koopa_troopa_beach_unk_data5;
extern f32 D_8018D01C;
extern s32 gGamestate;
static ? D_800E6034;                                /* unable to generate initializer */
static ? D_800E60F0;                                /* unable to generate initializer */
static ? D_800E61B4;                                /* unable to generate initializer */
static ? D_800E6280;                                /* unable to generate initializer */
static s32 D_800E633C[4] = { (s32) &D_800E6034, (s32) &D_800E60F0, (s32) &D_800E61B4, (s32) &D_800E6280 };

void func_8008241C(s32 objectIndex, s32 arg1) {
    s16 sp22;
    u16 sp20;
    f64 var_f10;
    f64 var_f8;
    s32 temp_f4;
    s32 temp_v0;
    s32 temp_v0_2;
    struct_80165C18_entry *temp_s0;

    temp_s0 = &D_80165C18[objectIndex];
    temp_s0->unk_0D8 = 1;
    temp_s0->unk_070 = (s32) &d_course_koopa_troopa_beach_unk4;
    temp_s0->unk_074 = (s32) &d_course_koopa_troopa_beach_unk_data5;
    temp_s0->unk_0DD = 1;
    temp_s0->sizeScaling = 0.2f;
    temp_v0 = random_int(0x00C8U);
    var_f8 = (f64) temp_v0;
    if (temp_v0 < 0) {
        var_f8 += 4294967296.0;
    }
    sp22 = (s16) (s32) (var_f8 + -100.0);
    sp20 = random_int(0x0014U);
    temp_v0_2 = random_int(0x00C8U);
    var_f10 = (f64) temp_v0_2;
    if (temp_v0_2 < 0) {
        var_f10 += 4294967296.0;
    }
    temp_f4 = (s32) (var_f10 + -100.0);
    if (gGamestate == 9) {
        func_8008B7D4(objectIndex, (f32) ((f64) sp22 + -360.0), (f32) ((f64) (s16) sp20 + 60.0), (f32) ((f64) (s16) temp_f4 + -1300.0));
    } else if ((u8) temp_s0->unk_0D5 != 0) {
        func_8008B7D4(objectIndex, (f32) (((f64) sp22 + 328.0) * (f64) D_8018D01C), (f32) ((f64) (s16) sp20 + 20.0), (f32) ((f64) (s16) temp_f4 + 2541.0));
    } else {
        func_8008B7D4(objectIndex, (f32) (((f64) sp22 + -985.0) * (f64) D_8018D01C), (f32) ((f64) (s16) sp20 + 15.0), (f32) ((f64) (s16) temp_f4 + 1200.0));
    }
    func_8008B888(objectIndex, 0U, 0U, 0U);
    temp_s0->unk_034 = 1.0f;
    func_80086EF0(objectIndex);
    temp_s0->unk_080 = D_800E633C[arg1 % 4];
    func_800721C0(objectIndex, 0x00000800);
    func_80072488(objectIndex);
}
#else
GLOBAL_ASM("asm/non_matchings/code_80071F00/func_8008241C.s")
#endif

void func_80082714(s32 objectIndex, s32 arg1) {
    switch(D_80165C18[objectIndex].unk_0A6) {
    case 1:
        func_8008241C(objectIndex , arg1);
        break;
    case 0:
    default:
        break;
    }
}

void func_8008275C(s32 objectIndex) {
    s32 stackPadding;
    switch (D_80165C18[objectIndex].unk_0DD) {                              /* irregular */
    case 1:
        func_8008B78C(objectIndex);
        func_8008BF18(objectIndex);
        break;
    case 2:
        func_8008B78C(objectIndex);
        vec3f_copy(D_80165C18[objectIndex].unk_01C, D_80165C18[objectIndex].pos);
        func_8000D940(D_80165C18[objectIndex].unk_010, &D_80165C18[objectIndex].unk_0C6, D_80165C18[objectIndex].unk_034, 0.0f, 0);
        D_80165C18[objectIndex].unk_028[0] *= 2.0;
        D_80165C18[objectIndex].unk_028[1] *= 2.5;
        D_80165C18[objectIndex].unk_028[2] *= 2.0;
        func_8008BF18(objectIndex);
        D_80165C18[objectIndex].unk_0BE[1] = get_angle_between_points(D_80165C18[objectIndex].unk_01C, D_80165C18[objectIndex].pos);
        break;
    }
    func_800873F4(objectIndex);
}

#ifdef MIPS_TO_C
//generated by m2c commit eefca95b040d7ee0c617bc58f9ac6cd1cf7bce87 on Aug-17-2023
extern s16 D_80165900;
extern s8 D_80165908;
extern s8 D_80165A90;
extern s32 D_80183F2C;
extern s16 gCutsceneShotTimer;

void func_80082870(void) {
    s32 *var_s4;
    s32 temp_s0;
    s32 var_s3;
    struct_80165C18_entry *temp_s1;

    var_s4 = D_80183F28;
    var_s3 = 0;
    do {
        temp_s0 = *var_s4;
        temp_s1 = &D_80165C18[temp_s0];
        if (temp_s1->unk_0A6 != 0) {
            func_80082714(temp_s0, var_s3);
            func_8008275C(temp_s0);
            if (func_80072320(temp_s0, 2) != 0) {
                func_800722CC(temp_s0, 2);
                if (D_80165A90 != 0) {
                    D_80165A90 = 0;
                    D_80183E40->unk0 = 0.0f;
                    D_80183E40->unk4 = 0.0f;
                    D_80183E40->unk8 = 0.0f;
                    if (gGamestate != 9) {
                        func_800C98B8(temp_s1->pos, D_80183E40, 0x19017043U);
                    } else if (gCutsceneShotTimer < 0x97) {
                        func_800C98B8(D_80165C18[D_80183F2C].pos, D_80183E40, 0x19017043U);
                    }
                }
            }
        }
        var_s3 += 1;
        var_s4 += 4;
    } while (var_s3 != 0x0000000A);
    if (D_80165900 != 0) {
        D_80165900 -= 1;
    } else {
        if (gGamestate != 9) {
            D_80165900 = 0x003C;
        } else {
            D_80165900 = 0x000F;
        }
        if ((D_80165908 != 0) && (D_80165A90 == 0)) {
            D_80165A90 = 1;
        }
    }
    D_80165908 = 0;
}
#else
GLOBAL_ASM("asm/non_matchings/code_80071F00/func_80082870.s")
#endif

void init_ktb_crab(s32 objectIndex) {
    struct_80165C18_entry *object;

    func_80073444(objectIndex, d_course_koopa_troopa_beach_crab_tlut, d_course_koopa_troopa_beach_crab_frames, 0x40U, (u16) 0x00000040);
    object = &D_80165C18[objectIndex];
    object->sizeScaling = 0.15f;
    object->unk_0D2 = 0;
    func_80072488(objectIndex);
    object->unk_0C8 = 1;
    func_800721C0(objectIndex, 0x04000420);
    func_80086EAC(objectIndex, 0, 1);
    func_8008B80C(objectIndex, 0.0f, 0.0f, 0.0f);
    func_8008B8BC(objectIndex, 0U, 0U, 0x8000U);
    object->unk_034 = 1.5f;
    func_800721C0(objectIndex, 0x00000200);
}

void func_80082B34(s32 objectIndex, s32 unused) {
    switch (D_80165C18[objectIndex].unk_0A6) {                               /* irregular */
    case 0:
        break;
    case 1:
        init_ktb_crab(objectIndex);
        break;
    case 2:
        func_80072E54(objectIndex, 0, 3, 1, 2, -1);
        break;
    case 3:
        func_80072E54(objectIndex, 4, 6, 1, 2, -1);
        break;
    }
    if (D_80165C18[objectIndex].unk_0A6 >= 2) {
        func_80073514(objectIndex);
    }
}

void func_80082C30(s32 objectIndex) {
    switch (D_80165C18[objectIndex].unk_0AE) {
    case 1:
        if (func_80087A0C(objectIndex, D_80165C18[objectIndex].unk_010[0], D_80165C18[objectIndex].unk_01C[0], D_80165C18[objectIndex].unk_010[2], D_80165C18[objectIndex].unk_01C[2]) != 0) {
            func_800726CC(objectIndex, 3);
            func_80086FD4(objectIndex);
        }
        break;
    case 2:
        if (func_80087104(objectIndex, 0x003CU) != 0) {
            D_80165C18[objectIndex].unk_034 = 0.8f;
            func_800726CC(objectIndex, 2);
            func_80086FD4(objectIndex);
        }
        break;
    case 3:
        if (func_80087954(objectIndex, 0x0000003C) != 0) {
            func_80086FD4(objectIndex);
            func_800726CC(objectIndex, 3);
        }
        break;
    case 4:
        if (func_80087104(objectIndex, 0x003CU) != 0) {
            func_800726CC(objectIndex, 2);
            func_80086FD4(objectIndex);
        }
        break;
    case 5:
        if (func_8008789C(objectIndex, 0x0000003C) != 0) {
            func_800726CC(objectIndex, 3);
            func_8008701C(objectIndex, 2);
        }
        break;
    }
    func_8008BF18(objectIndex);
    if (func_8007223C(objectIndex, 0x00040000) != 0) {
        func_80088538(objectIndex);
        D_80165C18[objectIndex].pos[1] = (f32) (D_80165C18[objectIndex].unk_044 + 2.5);
    }
}

void func_80082E18(s32 objectIndex) {
    if (D_80165C18[objectIndex].unk_0A6 >= 2) {
        func_80089F24(objectIndex);
    }
}

void func_80082E5C(void) {
    s32 temp_s0;
    s32 var_s1;

    for (var_s1 = 0; var_s1 < NUM_CRABS; var_s1++) {
        temp_s0 = D_80183EA0[var_s1];
        if (D_80165C18[temp_s0].unk_0A6 != 0) {
            func_80082B34(temp_s0, var_s1);
            func_8008A6DC(temp_s0, 500.0f);
            func_80082C30(temp_s0);
            func_80082E18(temp_s0);
        }
    }
}

#ifdef NON_MATCHING
// https://decomp.me/scratch/RquH0
// Gollygee I sure love register allocation :^)
void func_80082F1C(s32 objectIndex, s32 arg1) {
    D_80165C18[objectIndex].unk_070 = d_course_yoshi_valley_unk5;
    D_80165C18[objectIndex].unk_074 = d_course_yoshi_valley_unk4;
    D_80165C18[objectIndex].sizeScaling = 0.027f;
    func_80072488(objectIndex);
    func_8008B7D4(objectIndex, D_800E5DF4[arg1].pos[0] * D_8018D01C, D_800E5DF4[arg1].pos[1], D_800E5DF4[arg1].pos[2]);
    func_8008B80C(objectIndex, 0.0f, 0.0f, 0.0f);
    func_8008B888(objectIndex, 0U, D_800E5DF4[arg1].rot, 0U);
}
#else
GLOBAL_ASM("asm/non_matchings/code_80071F00/func_80082F1C.s")
#endif

void func_80083018(s32 objectIndex, s32 arg1) {
    switch(D_80165C18[objectIndex].unk_0A6) {
    case 1:
        func_80082F1C(objectIndex , arg1);
        break;
    case 0:
    default:
        break;
    }
}

void func_80083060(s32 arg0) {
    func_8008BF18(arg0);
}

void func_80083080(void) {
    s32 objectIndex;
    s32 var_s1;

    for (var_s1 = 0; var_s1 < NUM_YV_FLAG_POLES; var_s1++) {
        objectIndex = D_80183EA0[var_s1];
        if (D_80165C18[objectIndex].unk_0A6 != 0) {
            func_80083018(objectIndex, var_s1);
            func_80083060(objectIndex);
        }
    }
}

void func_8008311C(s32 objectIndex, s32 arg1) {
    struct_80165C18_entry *temp_s0;

    func_80073444(objectIndex, d_course_yoshi_valley_hedgehog_tlut, d_course_yoshi_valley_hedgehog, 0x40U, (u16) 0x00000040);
    temp_s0 = &D_80165C18[objectIndex];
    temp_s0->activeTLUT = d_course_yoshi_valley_hedgehog_tlut;
    temp_s0->activeTexture = d_course_yoshi_valley_hedgehog;
    temp_s0->unk_074 = D_0D0060B0;
    temp_s0->sizeScaling = 0.2f;
    temp_s0->unk_0D2 = 0;
    func_80072488(objectIndex);
    func_8008B80C(objectIndex, 0.0f, 0.0f, 0.0f);
    func_8008B8BC(objectIndex, 0U, 0U, 0x8000U);
    temp_s0->unk_034 = ((arg1 % 6) * 0.1) + 0.5;
    func_80086E70(objectIndex);
    func_800721C0(objectIndex, 0x04000600);
    temp_s0->unk_0C8 = 2;
}

void func_80083248(s32 objectIndex) {
    switch (D_80165C18[objectIndex].unk_0AE) {
    case 0:
        break;
    case 1:
        if (func_80087A0C(objectIndex, D_80165C18[objectIndex].unk_010[0], D_80165C18[objectIndex].unk_09C, D_80165C18[objectIndex].unk_010[2], D_80165C18[objectIndex].unk_09E) != 0) {
            func_80086FD4(objectIndex);
        }
        break;
    case 2:
        func_800871AC(objectIndex, 0x0000003C);
        break;
    case 3:
        if (func_80087A0C(objectIndex, D_80165C18[objectIndex].unk_09C, D_80165C18[objectIndex].unk_010[0], D_80165C18[objectIndex].unk_09E, D_80165C18[objectIndex].unk_010[2]) != 0) {
            func_80086FD4(objectIndex);
        }
        break;
    case 4:
        if (func_80087060(objectIndex, 0x0000003C) != 0) {
            func_8008701C(objectIndex, 1);
        }
        break;
    }
    func_8008BF18(objectIndex);
    if (func_8007223C(objectIndex, 0x00200000) != 0) {
        if (func_8007223C(objectIndex, 0x00400000) != 0) {
            func_8008861C(objectIndex);
        }
        D_80165C18[objectIndex].pos[1] = D_80165C18[objectIndex].unk_044 + 6.0;
    }
}

void func_800833D0(s32 objectIndex, s32 arg1) {
    switch (D_80165C18[objectIndex].unk_0A6) {                              /* irregular */
    case 0:
        break;
    case 1:
        func_8008311C(objectIndex, arg1);
        break;
    case 2:
        func_80072D3C(objectIndex, 0, 1, 4, -1);
        break;
    }
    if (D_80165C18[objectIndex].unk_0D2 == 0) {
        D_80165C18[objectIndex].unk_074 = D_0D0060B0;
    } else {
        D_80165C18[objectIndex].unk_074 = D_0D006130;
    }
}

void func_80083474(s32 objectIndex) {
    if (D_80165C18[objectIndex].unk_0A6 >= 2) {
        func_80089F24(objectIndex);
    }
}

void func_800834B8(void) {
    s32 temp_s1;
    s32 var_s0;

    for (var_s0 = 0; var_s0 < 0xF; var_s0++) {
        temp_s1 = D_80183F28[var_s0];
        func_800833D0(temp_s1, var_s0);
        func_80083248(temp_s1);
        func_80083474(temp_s1);
    }
    func_80072120(D_80183F28, 0x0000000F);
}

void func_80083538(s32 objectIndex, Vec3f arg1, s32 arg2, s32 arg3) {
    struct_80165C18_entry *temp_s0;

    func_800723A4(objectIndex, 0);
    temp_s0 = &D_80165C18[objectIndex];
    temp_s0->activeTexture = d_course_frappe_snowland_snow;
    temp_s0->textureList = d_course_frappe_snowland_snow;
    temp_s0->activeTLUT = d_course_frappe_snowland_snow_tlut;
    temp_s0->tlutList = d_course_frappe_snowland_snow_tlut;
    temp_s0->sizeScaling = random_int(0x0064U);
    temp_s0->sizeScaling = (temp_s0->sizeScaling * 0.001) + 0.05;
    temp_s0->unk_038[1] = random_int(0x0014U);
    temp_s0->unk_038[1] = (temp_s0->unk_038[1] * 0.5) + 2.6;
    temp_s0->unk_034 = random_int(0x000AU);
    temp_s0->unk_034 = (temp_s0->unk_034 *0.1) + 4.5;
    temp_s0->unk_0BE[1] = (arg2 << 0x10) / arg3;
    temp_s0->unk_010[0] = arg1[0];
    temp_s0->unk_010[1] = arg1[1];
    temp_s0->unk_010[2] = arg1[2];
    temp_s0->unk_0A0 = random_int(0x4000U) + 0x1000;
}

void func_800836F0(Vec3f arg0) {
    s32 temp_v0;
    s32 var_s0;

    for (var_s0 = 0; var_s0 < D_8018D3BC; var_s0++) {
        temp_v0 = func_80072044(&D_8018C3F0[0], &D_80183E4C, D_8018C3F0_SIZE);
        if (temp_v0 == -1) break;
        func_80083538(temp_v0, arg0, var_s0, D_8018D3BC);
    }
}

void func_8008379C(s32 objectIndex) {
    switch (D_80165C18[objectIndex].unk_0A6) {
    case 0:
        break;
    case 1:
        if (func_80087E08(objectIndex, D_80165C18[objectIndex].unk_038[1], 0.74f, D_80165C18[objectIndex].unk_034, D_80165C18[objectIndex].unk_0BE[1], 0x00000064) != 0) {
            func_80072488(objectIndex);
        }
        break;
    case 2:
        func_80086F60(objectIndex);
        func_80072428(objectIndex);
        break;
    }
    func_8008BF18(objectIndex);
    D_80165C18[objectIndex].unk_0B2[2] += D_80165C18[objectIndex].unk_0A0;
}

void func_80083868(s32 objectIndex) {
    struct_80165C18_entry *temp_s0;

    func_80073444(objectIndex, d_course_frappe_snowland_snowman_tlut, d_course_frappe_snowland_snowman_head, 0x40U, (u16) 0x00000040);
    temp_s0 = &D_80165C18[objectIndex];
    temp_s0->unk_074 = D_0D0061B0;
    temp_s0->sizeScaling = 0.1f;
    temp_s0->unk_0D2 = 0;
    func_80072488(objectIndex);
    func_8008B80C(objectIndex, 0.0f, 0.0f, 0.0f);
    temp_s0->unk_0B2[0] = 0;
    temp_s0->unk_0B2[1] = 0;
    temp_s0->unk_0B2[2] = 0x8000;
    temp_s0->unk_0A0 = random_int(0x2000U) - 0x1000;
    func_80086E70(objectIndex);
    temp_s0->unk_034 = 1.5f;
    func_800721C0(objectIndex, 0x00000200);
}

void func_80083948(s32 objectIndex) {
    switch (D_80165C18[objectIndex].unk_0AE) {
    case 1:
        func_80086FD4(objectIndex);
        break;
    case 2:
        func_800871AC(objectIndex, 0x00000014);
        break;
    case 3:
        func_8008701C(objectIndex, 1);
        break;
    case 10:
        func_80087C48(objectIndex, 10.0f, 0.5f, 0x0000000A);
        break;
    case 11:
        func_80087D24(objectIndex, 0.0f, 0.2f, -7.0f);
        break;
    case 20:
        if (f32_step_up_towards(&D_80165C18[objectIndex].unk_028[1], 0.0f, 0.2f) != 0) {
            func_80073800(objectIndex, 0);
            func_8008701C(objectIndex, 1);
        }
        break;
    case 0:
    default:
        break;
    }
    func_8008BF18(objectIndex);
    func_80073D0C(objectIndex, &D_80165C18[objectIndex].unk_0A0, -0x00001000, 0x00001000, 0x00000400, 1, -1);
    D_80165C18[objectIndex].unk_0B2[2] = D_80165C18[objectIndex].unk_0A0 + 0x8000;
}

void func_80083A94(s32 objectIndex) {
    switch (D_80165C18[objectIndex].unk_0A6) {
    case 0:
        break;
    case 1:
        func_80083868(objectIndex);
        break;
    }
    if (D_80165C18[objectIndex].unk_0A6 >= 2) {
        func_80073514(objectIndex);
    }
    func_80083948(objectIndex);
}

void func_80083B0C(s32 objectIndex) {
    func_80073444(objectIndex, d_course_frappe_snowland_snowman_tlut, d_course_frappe_snowland_snowman_body, 0x40U, (u16) 0x00000040);
    D_80165C18[objectIndex].unk_074 = D_0D0060B0;
    D_80165C18[objectIndex].sizeScaling = 0.1f;
    D_80165C18[objectIndex].unk_0D2 = 0;
    func_80072488(objectIndex);
    func_8008B80C(objectIndex, 0.0f, 0.0f, 0.0f);
    D_80165C18[objectIndex].unk_0B2[0] = 0;
    D_80165C18[objectIndex].unk_0B2[1] = 0;
    D_80165C18[objectIndex].unk_0B2[2] = 0x8000;
    D_80165C18[objectIndex].unk_0C8 = 2;
    D_80165C18[objectIndex].unk_034 = 1.5f;
    func_800721C0(objectIndex, 0x04000210);
}

void func_80083BE4(s32 arg0) {
    func_8008BF18(arg0);
}

void func_80083C04(s32 objectIndex) {
    struct_80165C18_entry *temp_s1;

    temp_s1 = &D_80165C18[objectIndex];
    switch (temp_s1->unk_0A6) {
    case 0:
        break;
    case 1:
        func_80083B0C(objectIndex);
        break;
    case 2:
        func_8007278C(objectIndex, 0x00000096);
        break;
    case 10:
        if (func_8007278C(objectIndex, 0x0000012C) != 0) {
            func_800722A4(objectIndex, 2);
        }
        break;
    case 11:
        if (func_8007278C(objectIndex, 0x0000000A) != 0) {
            func_800721C0(objectIndex, 0x00000010);
            temp_s1->sizeScaling = 0.001f;
        }
        break;
    case 12:
        if (func_80074118(objectIndex, &temp_s1->sizeScaling, 0.001f, 0.1f, 0.0025f, 0, 0) != 0) {
            func_80072488(objectIndex);
        }
        break;
    case 13:
        func_800726CC(objectIndex, 2);
        func_800721E8(objectIndex, 0x00001000);
        break;
    }
    if (temp_s1->unk_0A6 >= 2) {
        func_80073514(objectIndex);
    }
    func_80083BE4(objectIndex);
}

void func_80083D60(void) {
    s32 var_s0;
    s32 var_s3;
    s32 var_s4;
    s32 temp_a0;
    struct_80165C18_entry *temp_s1;

    for (var_s0 = 0; var_s0 < D_8018C3F0_SIZE; var_s0++) {
        temp_a0 = D_8018C3F0[var_s0];

        if (temp_a0 == -1) continue;

        if (D_80165C18[temp_a0].unk_0A6 == 0) continue;
        func_8008379C(temp_a0);
        if (D_80165C18[temp_a0].unk_0A6 != 0) continue;
        func_80072100(&D_8018C3F0[var_s0]);
        if (var_s0) {} // ??
    }

    for (var_s0 = 0; var_s0 < 19; var_s0++) {
        var_s4 = D_80183EA0[var_s0];
        var_s3 = D_80183F28[var_s0];
        func_80083A94(var_s3);
        func_80083C04(var_s4);
        if (func_80072270(var_s4, 0x00001000) != 0) {
            temp_s1 = &D_80165C18[var_s4];
            if ((func_8008A8B0(temp_s1->unk_0D5 - 1, temp_s1->unk_0D5 + 1) != 0) && (func_80089B50(var_s4) != 0)) {
                func_800721C0(var_s4, 0x00001000);
                func_800721E8(var_s4, 0x00000010);
                func_800726CC(var_s4, 0x0000000A);
                func_8008701C(var_s3, 0x0000000A);
                func_800836F0(temp_s1->pos);
            }
        } else if (func_80072320(var_s4, 2) != 0) {
            func_800722CC(var_s4, 2);
            func_8008701C(var_s3, 0x00000014);
        }
    }
}

void func_80083F18(s32 objectIndex) {
    switch (D_80165C18[objectIndex].unk_0A6) {
    case 0:
        break;
    case 1:
        if (func_80087E08(objectIndex, D_80165C18[objectIndex].unk_038[1], 0.12f, D_80165C18[objectIndex].unk_034, D_80165C18[objectIndex].unk_0BE[1], 0x00000064) != 0) {
            func_80072488(objectIndex);
        }
        func_8008BF18(objectIndex);
        break;
    case 2:
        func_80086F60(objectIndex);
        func_80072428(objectIndex);
        break;
    }
}

void func_80083FD0(s32 objectIndex, s32 arg1, s32 playerId) {
    struct_80165C18_entry *temp_s0;
    Player *sp20;

    temp_s0 = &D_80165C18[objectIndex];
    sp20 = &gPlayerOne[playerId];
    temp_s0->unk_084[7] = playerId;
    func_800723A4(objectIndex, 0);
    temp_s0->activeTLUT = d_course_sherbet_land_ice;
    temp_s0->tlutList   = d_course_sherbet_land_ice;
    temp_s0->sizeScaling = ((f32) random_int(0x01F4U) * 0.0002) + 0.04;
    temp_s0->unk_038[1]  = ((f32) random_int(0x0032U) * 0.05)   + 1.0;
    temp_s0->unk_034     = ((f32) random_int(0x000AU) * 0.1)    + 1.0;
    temp_s0->unk_0BE[1] = D_801657A2 * arg1;
    temp_s0->unk_010[0] = (sp20->pos[0] + random_int(0x0014U)) - 10.0f;
    temp_s0->unk_010[1] = (sp20->pos[1] - 10.0) + random_int(0x000AU);
    temp_s0->unk_010[2] = (sp20->pos[2] + random_int(0x0014U)) - 10.0f;
}

void func_8008421C(s32 arg0, s32 playerId) {
    s32 temp_v0;
    s32 var_s0;

    for (var_s0 = 0; var_s0 < D_8018D3C0; var_s0++) {
        temp_v0 = func_80072044(D_8018C3F0, &D_80183E4C, D_8018C3F0_SIZE);
        if (temp_v0 == -1) break;
        func_80083FD0(temp_v0, var_s0, playerId);
    }
}

void func_800842C8(void) {
    s32 var_s2;
    s32 var_s1;

    D_80165834[0] += 0x200;
    D_80165834[1] += 0x400;
    func_800419F8();
    D_8016582C[0] += 0x2000;
    D_8016582C[1] += 0x1000;
    D_8016582C[2] += 0x1800;
    for (var_s1 = 0; var_s1 < gPlayerCountSelection1; var_s1++) {
        var_s2 = D_80183DB8[var_s1];
        if (func_80072320(var_s2, 0x00000020) != 0) {
            func_800722CC(var_s2, 0x00000020);
            func_8008421C(var_s2, var_s1);
        }
    }
    for (var_s1 = 0; var_s1 < D_8018C3F0_SIZE; var_s1++) {
        var_s2 = D_8018C3F0[var_s1];
        if (var_s2 != -1) {
            if (D_80165C18[var_s2].unk_0A6 != 0) {
                func_80083F18(var_s2);
                if (D_80165C18[var_s2].unk_0A6 == 0) {
                    func_80072100(&D_8018C3F0[var_s1]);
                }
            }
        }
    }
}

#ifdef MIPS_TO_C
//generated by m2c commit eefca95b040d7ee0c617bc58f9ac6cd1cf7bce87 on Aug-10-2023
extern Gfx d_course_sherbet_land_unk_data1;
extern Vtx d_course_sherbet_land_unk_data11;
static s16 D_800E659C[4];                           /* unable to generate initializer */
static s16 D_800E6668[4];                           /* unable to generate initializer */
static s16 (*D_800E672C[2])[4] = { (s16 (*)[4]) D_800E659C, (s16 (*)[4]) D_800E6668 };

void func_80084430(s32 objectIndex, s32 arg1) {
    struct_80165C18_entry *temp_s0;

    temp_s0 = &D_80165C18[objectIndex];
    temp_s0->unk_0D8 = 0;
    temp_s0->unk_070 = &d_course_sherbet_land_unk_data1;
    temp_s0->unk_074 = &d_course_sherbet_land_unk_data11;
    temp_s0->unk_0C8 = 0x000C;
    temp_s0->unk_09C = 1;
    temp_s0->sizeScaling = 0.2f;
    func_8008B7D4(objectIndex, (f32) ((f64) D_8018D01C * -383.0), 2.0f, -690.0f);
    func_8008B888(objectIndex, 0U, 0U, 0U);
    temp_s0->unk_0DD = 1;
    func_80086EF0(objectIndex);
    temp_s0->unk_080 = *D_800E672C;
    func_800721C0(objectIndex, 0x04000800);
    temp_s0->unk_0A4 = func_80004EAC(&d_course_sherbet_land_unk_data11, 0);
    func_80072488(objectIndex);
}
#else
GLOBAL_ASM("asm/non_matchings/code_80071F00/func_80084430.s")
#endif

void func_8008453C(s32 objectIndex, s32 arg1) {
    switch (D_80165C18[objectIndex].unk_0A6) {                              /* irregular */
    case 0:
        break;
    case 1:
        if (gPlayerCountSelection1 == 1) {
            func_80084430(objectIndex, arg1);
        }
        break;
    case 2:
        func_80072E54(objectIndex, 0, D_80165C18[objectIndex].unk_0A4, 1, 0, -1);
        break;
    }
}

void func_800845C8(s32 objectIndex, s32 arg1) {
    struct_80165C18_entry *temp_s0;

    temp_s0 = &D_80165C18[objectIndex];
    temp_s0->unk_0D8 = 0;
    temp_s0->unk_070 = d_course_sherbet_land_unk_data1;
    temp_s0->unk_074 = d_course_sherbet_land_unk_data11;
    temp_s0->unk_0C8 = 4;
    temp_s0->unk_09C = 2;
    temp_s0->unk_04C = random_int(0x012CU);
    func_800721C0(objectIndex, 0x04000220);
    if ((arg1 > 0) && (arg1 < 9)) {
        if ((arg1 == 1) || (arg1 == 2)) {
            func_8008B7D4(objectIndex, D_8018D01C * -2960.0, -80.0f, 1521.0f);
            temp_s0->unk_0C6 = 0x0150;
            temp_s0->unk_01C[1] = 100.0f;
        } else if ((arg1 == 3) || (arg1 == 4)) {
            func_8008B7D4(objectIndex, D_8018D01C * -2490.0, -80.0f, 1612.0f);
            temp_s0->unk_0C6 = 0x0100;
            temp_s0->unk_01C[1] = 80.0f;
        } else if ((arg1 == 5) || (arg1 == 6)) {
            func_8008B7D4(objectIndex, D_8018D01C * -2098.0, -80.0f, 1624.0f);
            temp_s0->unk_0C6 = 0xFF00;
            temp_s0->unk_01C[1] = 80.0f;
        } else if ((arg1 == 7) || (arg1 == 8)) {
            func_8008B7D4(objectIndex, D_8018D01C * -2080.0, -80.0f, 1171.0f);
            temp_s0->unk_0C6 = 0x0150;
            temp_s0->unk_01C[1] = 80.0f;
        }
        temp_s0->unk_0C4 = (arg1 << 0xF) & 0xFFFF;
        temp_s0->unk_044 = -80.0f;
        temp_s0->sizeScaling = 0.08f;
        temp_s0->unk_0DD = 2;
        func_800722A4(objectIndex, 8);
    } else if ((arg1 > 8) && (arg1 < 15)) {
        switch (arg1) {                             /* irregular */
        case 9:
            if (gGamestate != 9) {
                func_8008B7D4(objectIndex, D_8018D01C * 146.0, 0.0f, -380.0f);
            } else {
                func_8008B7D4(objectIndex, D_8018D01C * 380.0, 0.0f, -535.0f);
                temp_s0->sizeScaling = 0.15f;
            }
            temp_s0->unk_0C6 = 0x9000;
            if (gIsMirrorMode != 0) {
                temp_s0->unk_0C6 -= 0x4000;
            }
            temp_s0->unk_0DD = 3;
            break;
        case 10:
            func_8008B7D4(objectIndex, D_8018D01C * 380.0, 0.0f, -766.0f);
            temp_s0->unk_0C6 = 0x5000;
            if (gIsMirrorMode != 0) {
                temp_s0->unk_0C6 += 0x8000;
            }
            temp_s0->unk_0DD = 4;
            break;
        case 11:
            func_8008B7D4(objectIndex, D_8018D01C * -2300.0, 0.0f, -210.0f);
            temp_s0->unk_0C6 = 0xC000;
            temp_s0->unk_0DD = 6;
            if (gIsMirrorMode != 0) {
                temp_s0->unk_0C6 += 0x8000;
            }
            break;
        case 12:
            func_8008B7D4(objectIndex, D_8018D01C * -2500.0, 0.0f, -250.0f);
            temp_s0->unk_0C6 = 0x4000;
            temp_s0->unk_0DD = 6;
            if (gIsMirrorMode != 0) {
                temp_s0->unk_0C6 += 0x8000;
            }
            break;
        case 13:
            func_8008B7D4(objectIndex, D_8018D01C * -535.0, 0.0f, 875.0f);
            temp_s0->unk_0C6 = 0x8000;
            temp_s0->unk_0DD = 6;
            if (gIsMirrorMode != 0) {
                temp_s0->unk_0C6 -= 0x4000;
            }
            break;
        case 14:
            func_8008B7D4(objectIndex, D_8018D01C * -250.0, 0.0f, 953.0f);
            temp_s0->unk_0C6 = 0x9000;
            temp_s0->unk_0DD = 6;
            if (gIsMirrorMode != 0) {
                temp_s0->unk_0C6 -= 0x4000;
            }
            break;
        default:
            break;
        }
        func_8008B888(objectIndex, 0U, temp_s0->unk_0C6 + 0x8000, 0U);
        temp_s0->unk_044 = 5.0f;
        temp_s0->sizeScaling = 0.04f;
        func_800722A4(objectIndex, 0x00000014);
    }
    func_80086EF0(objectIndex);
    temp_s0->unk_034 = 0.0f;
    temp_s0->unk_0A4 = func_80004EAC(d_course_sherbet_land_unk_data11, 0);
    func_80072488(objectIndex);
}

void func_80084B7C(s32 objectIndex, s32 arg1) {
    struct_80165C18_entry *temp_s0;

    temp_s0 = &D_80165C18[objectIndex];
    switch (temp_s0->unk_0A6) {
    case 0:
        break;
    case 1:
        func_800845C8(objectIndex, arg1);
        break;
    case 2:
        func_80072E54(objectIndex, 0, (s32) temp_s0->unk_0A4, (s32) temp_s0->unk_09C, 0, -1);
        if (func_80072354(objectIndex, 0x00000020) != 0) {
            if (temp_s0->unk_084[6] == 0) {
                temp_s0->unk_084[6] = random_int(0x005AU) + 0x5A;
                func_800722A4(objectIndex, 0x00000080);
            } else {
                temp_s0->unk_084[6]--;
            }
        }
        break;
    case 3:
        func_80072E54(objectIndex, 0, temp_s0->unk_0A4, 1, 0, 0);
        break;
    case 4:
        func_800722CC(objectIndex, 2);
        func_80072488(objectIndex);
        break;
    }
    if (func_80072320(objectIndex, 0x00000020) != 0) {
        if (temp_s0->unk_084[6] == 0) {
            func_800722A4(objectIndex, 0x00000080);
            temp_s0->unk_084[6] = 0x0010;
        } else {
            temp_s0->unk_084[6]--;
        }
    }
    if (func_80072320(objectIndex, 0x00000080) != 0) {
        func_800722CC(objectIndex, 0x00000080);
        if (func_80072320(objectIndex, 0x00000010) != 0) {
            func_800C98B8(temp_s0->pos, temp_s0->unk_038, 0x19007049U);
        } else {
            func_800C98B8(temp_s0->pos, temp_s0->unk_038, 0x19007017U);
        }
    }
}

void func_80084D2C(s32 objectIndex, s32 arg1) {
    f32 sp24;

    switch (D_80165C18[objectIndex].unk_0AE) {
    case 0:
        break;
    case 1:
        D_80165C18[objectIndex].unk_0BE[1] = func_800417B4(D_80165C18[objectIndex].unk_0BE[1], D_80165C18[objectIndex].unk_0C6);
        if (D_80165C18[objectIndex].unk_0BE[1] == D_80165C18[objectIndex].unk_0C6) {
            D_80165C18[objectIndex].unk_09C = 4;
            D_80165C18[objectIndex].unk_034 = 0.4f;
            func_80086FD4(objectIndex);
        }
        break;
    case 2:
        f32_step_towards(&D_80165C18[objectIndex].unk_034, 0.8f, 0.02f);
        if (func_80087060(objectIndex, 0x0000000F) != 0) {
            func_800722A4(objectIndex, 1);
            func_800722A4(objectIndex, 2);
            D_80165C18[objectIndex].unk_09C = 1;
            D_80165C18[objectIndex].unk_0D8 = 1;
            D_80165C18[objectIndex].unk_0D2 = 0;
            D_80165C18[objectIndex].unk_0A4 = func_80004EAC(d_course_sherbet_land_unk_data11, D_80165C18[objectIndex].unk_0D8);
            func_800726CC(objectIndex, 3);
            func_80086FD4(objectIndex);
            if (func_80072354(objectIndex, 0x00000020) != 0) {
                func_800722A4(objectIndex, 0x00000080);
            }
        }
        break;
    case 3:
        switch (arg1) {                             /* switch 1; irregular */
        case 0:                                     /* switch 1 */
            sp24 = 1.0f;
            break;
        case 1:                                     /* switch 1 */
            sp24 = 1.5f;
            break;
        case 2:                                     /* switch 1 */
            sp24 = 2.0f;
            break;
        case 3:                                     /* switch 1 */
            sp24 = 2.5f;
            break;
        }
        f32_step_towards(&D_80165C18[objectIndex].unk_034, sp24, 0.15f);
        if ((func_80072354(objectIndex, 2) != 0) && (sp24 == D_80165C18[objectIndex].unk_034)) {
            func_80086FD4(objectIndex);
        }
        break;
    case 4:
        if (func_80087060(objectIndex, 0x0000001E) != 0) {
            func_800722CC(objectIndex, 1);
            func_80086FD4(objectIndex);
        }
        break;
    case 5:
        f32_step_towards(&D_80165C18[objectIndex].unk_034, 0.4f, 0.2f);
        if (func_80087060(objectIndex, 0x0000000A) != 0) {
            func_800722A4(objectIndex, 2);
            D_80165C18[objectIndex].unk_0D8 = 2;
            D_80165C18[objectIndex].unk_0D2 = 0;
            D_80165C18[objectIndex].unk_0A4 = func_80004EAC(d_course_sherbet_land_unk_data11, D_80165C18[objectIndex].unk_0D8);
            func_800726CC(objectIndex, 3);
            func_80086FD4(objectIndex);
        }
        break;
    case 6:
        if (func_80072354(objectIndex, 2) != 0) {
            D_80165C18[objectIndex].unk_0D8 = 0;
            D_80165C18[objectIndex].unk_0D2 = 0;
            D_80165C18[objectIndex].unk_0A4 = func_80004EAC(d_course_sherbet_land_unk_data11, D_80165C18[objectIndex].unk_0D8);
            D_80165C18[objectIndex].unk_0C6 += 0x8000;
            func_800726CC(objectIndex, 2);
            func_8008701C(objectIndex, 1);
        }
        break;
    }
    func_8008781C(objectIndex);
    func_8008BF18(objectIndex);
}

void func_80085024(void) {

}

void func_8008502C(s32 objectIndex, UNUSED s32 arg1) {
    func_80088038(objectIndex, D_80165C18[objectIndex].unk_01C[1], D_80165C18[objectIndex].unk_0C6);
    func_8008BF18(objectIndex);
    func_800873F4(objectIndex);
}

void func_80085080(s32 arg0) {
    func_8008B78C(arg0);
    func_8008BF18(arg0);
    func_800873F4(arg0);
}

void func_800850B0(s32 objectIndex, s32 arg1) {
    struct_80165C18_entry *temp_s0;

    temp_s0 = &D_80165C18[objectIndex];
    switch (temp_s0->unk_0DD) {
    case 1:
        func_80085080(objectIndex);
        break;
    case 2:
        func_8008502C(objectIndex, arg1);
        break;
    case 3:
        func_80084D2C(objectIndex, 0);
        break;
    case 4:
        func_80084D2C(objectIndex, 1);
        break;
    case 5:
        func_80084D2C(objectIndex, 2);
        break;
    case 6:
        func_80084D2C(objectIndex, 3);
        break;
    }
    if (func_80072320(objectIndex, 0x00000020) != 0) {
        if (func_80072320(objectIndex, 0x00000040) != 0) {
            func_800722CC(objectIndex, 0x00000040);
            temp_s0->unk_084[6] = 0;
            temp_s0->unk_084[7] = 0x0096;
        }
        if (temp_s0->unk_084[7] == 0) {
            func_800722CC(objectIndex, 0x00000020);
        } else {
            temp_s0->unk_084[7]--;
            temp_s0->unk_0B2[0] = temp_s0->unk_0BE[0];
            temp_s0->unk_0B2[1] += 0x2000;
            temp_s0->unk_0B2[2] = temp_s0->unk_0BE[2];
        }
    } else {
        temp_s0->unk_0B2[0] = temp_s0->unk_0BE[0];
        temp_s0->unk_0B2[1] = temp_s0->unk_0BE[1];
        temp_s0->unk_0B2[2] = temp_s0->unk_0BE[2];
    }
}

void func_80085214(void) {
    s32 var_s2;
    s32 temp_s0;
    s32 var_s1;

    for (var_s1 = 0; var_s1 < 0xF; var_s1++) {
        temp_s0 = D_80183EA0[var_s1];
        if (D_80165C18[temp_s0].unk_0A6 != 0) {
            if (var_s1 == 0) {
                func_8008453C(temp_s0, var_s1);
            } else {
                func_80084B7C(temp_s0, var_s1);
            }
            func_800850B0(temp_s0, var_s1);
        }
        if (func_80072320(temp_s0, 1) != 0) {
            func_80089820(temp_s0, 1.75f, 1.5f, 0x1900A046U);
        } else if (func_80072320(temp_s0, 8) != 0) {
            func_80089820(temp_s0, 1.3f, 1.0f, 0x1900A046U);
        } else {
            func_80089820(temp_s0, 1.5f, 1.25f, 0x1900A046U);
        }
        if ((func_8007223C(temp_s0, 0x02000000) != 0) && (func_80072354(temp_s0, 0x00000020) != 0)) {
            func_800722A4(temp_s0, 0x00000060);
            func_800721E8(temp_s0, 0x02000000);
        }
    }
}

void func_800853DC(s32 objectIndex) {
    D_80165C18[objectIndex].sizeScaling = 1.0f;
    D_80165C18[objectIndex].unk_070 = d_course_luigi_raceway_dl_F960;
    if (gGamestate != 9) {
        func_8008B7D4(objectIndex, D_8018D01C * -176.0, 0.0f, -2323.0f);
        func_8008B80C(objectIndex, 0.0f, 300.0f, 0.0f);
    } else {
        func_8008B7D4(objectIndex, D_8018D01C * -1250.0, 0.0f, 1110.0f);
        func_8008B80C(objectIndex, 0.0f, 300.0f, 0.0f);
    }
    func_8008B844(objectIndex);
    func_800886F4(objectIndex);
    func_80086EF0(objectIndex);
    D_80165C18[objectIndex].unk_038[1] = -2.0f;
    func_802A14BC(0.0f, 0.0f, 0.0f);
    func_80072488(objectIndex);
}

void func_80085534(s32 objectIndex) {
    switch (D_80165C18[objectIndex].unk_0AE) {
    case 1:
        if (D_80165C18[objectIndex].unk_028[1] <= 18.0) {
            func_80086FD4(objectIndex);
        }
        break;
    case 2:
        f32_step_towards(&D_80165C18[objectIndex].unk_038[1], 0.0f, 0.05f);
        if (D_80165C18[objectIndex].unk_038[1] == 0.0) {
            func_80086FD4(objectIndex);
        }
        break;
    case 3:
        func_800871AC(objectIndex, 1);
        break;
    case 4:
        f32_step_towards(&D_80165C18[objectIndex].unk_038[1], 1.0f, 0.05f);
        if (D_80165C18[objectIndex].unk_038[1] == 1.0) {
            func_80086FD4(objectIndex);
        }
        break;
    case 5:
        func_800871AC(objectIndex, 0x0000005A);
        break;
    case 6:
        f32_step_towards(&D_80165C18[objectIndex].unk_038[1], 0.0f, 0.05f);
        if (D_80165C18[objectIndex].unk_038[1] == 0.0) {
            func_80086FD4(objectIndex);
        }
        break;
    case 7:
        f32_step_towards(&D_80165C18[objectIndex].unk_038[1], -1.0f, 0.05f);
        if (D_80165C18[objectIndex].unk_038[1] == -1.0) {
            func_80086FD4(objectIndex);
        }
        break;
    case 8:
        func_800871AC(objectIndex, 0x0000005A);
        break;
    case 9:
        f32_step_towards(&D_80165C18[objectIndex].unk_038[1], 0.0f, 0.05f);
        if (func_80087060(objectIndex, 0x0000005A) != 0) {
            func_8008701C(objectIndex, 3);
        }
        break;
    }
    func_800877C4(objectIndex);
    D_80165C18[objectIndex].unk_0BE[1] += 0x100;
}

void func_80085768(s32 objectIndex) {
    switch (D_80165C18[objectIndex].unk_0A6) {                              /* irregular */
    case 1:
        func_800853DC(objectIndex);
        break;
    case 0:
    case 2:
        break;
    }
}

void func_800857C0(void) {
    s32 objectIndex;

    objectIndex = D_80183EA0[0];
    if (D_80165C18[objectIndex].unk_0A6 != 0) {
        func_80085768(objectIndex);
        func_80085534(objectIndex);
        func_8008BF18(objectIndex);
        if (D_80165C18[objectIndex].unk_0A6 >= 2) {
            D_802BA05C->pos[0] = D_80165C18[objectIndex].pos[0];
            D_802BA05C->pos[1] = D_80165C18[objectIndex].pos[1] - 10.0;
            D_802BA05C->pos[2] = D_80165C18[objectIndex].pos[2];
        }
    }
}

void func_80085878(s32 objectIndex, s32 arg1) {
    struct TrackWayPoint *temp_v0;
    struct_80165C18_entry *temp_s0;

    temp_s0 = &D_80165C18[objectIndex];
    temp_s0->unk_0D8 = 1;
    temp_s0->unk_070 = d_rainbow_road_unk4;
    temp_s0->unk_074 = d_rainbow_road_unk3;
    temp_s0->sizeScaling = 0.03f;
    temp_s0->unk_0C8 = 0x000A;
    func_800721C0(objectIndex, 0x04000200);
    temp_s0->unk_084[8] = (arg1 * 0x12C) + 0x1F4;
    func_8008B7D4(objectIndex, 0.0f, -15.0f, 0.0f);
    temp_v0 = &D_80164490[(u16)temp_s0->unk_084[8]];
    func_8008B80C(objectIndex, temp_v0->wayPointX, temp_v0->wayPointY, temp_v0->wayPointZ);
    func_8008B888(objectIndex, 0U, 0U, 0U);
    temp_s0->unk_034 = 4.0f;
    temp_s0->unk_0A4 = func_80004EAC(d_rainbow_road_unk3, 0);
    func_80072488(objectIndex);
}

void func_800859C8(s32 objectIndex, s32 arg1) {
    struct_80165C18_entry *temp_s0;

    temp_s0 = &D_80165C18[objectIndex];
    switch (temp_s0->unk_0A6) {                              /* irregular */
    case 0:
        break;
    case 1:
        func_80085878(objectIndex, arg1);
        break;
    case 2:
        func_80072E54(objectIndex, 0, (s32) temp_s0->unk_0A4, 1, 0, -1);
        break;
    }
    if (D_8018D40C == 0) {
        func_800C98B8(temp_s0->pos, temp_s0->unk_038, 0x19018057U);
    }
    func_80074344(objectIndex, &temp_s0->unk_044, -0.8f, 0.8f, 0.03f, 0, -1);
}

void func_80085AA8(void) {
    s32 temp_s2;
    s32 var_s4;
    struct_80165C18_entry *temp_s0;

    for (var_s4 = 0; var_s4 < 3; var_s4++) {
        temp_s2 = D_80183F28[var_s4];
        temp_s0 = &D_80165C18[temp_s2];
        if (temp_s0->unk_0A6 != 0) {
            func_800859C8(temp_s2, var_s4);
            vec3f_copy(temp_s0->unk_01C, temp_s0->unk_028);
            func_8000D940(temp_s0->unk_028, &temp_s0->unk_084[8], temp_s0->unk_034, temp_s0->unk_044, 0);
            temp_s0->unk_0BE[1] = get_angle_between_points(temp_s0->unk_01C, temp_s0->unk_028);
            func_8008BF18(temp_s2);
            func_80089CBC(temp_s2, 30.0f);
        }
    }
}

void func_80085BB4(s32 objectIndex) {
    D_80165C18[objectIndex].sizeScaling = 8.0f;
    func_8008B80C(objectIndex, 0.0f, 0.0f, 0.0f);
    func_8008B8BC(objectIndex, 0U, 0U, 0x8000U);
    func_80072488(objectIndex);
}

void func_80085C20(s32 objectIndex) {
    func_8008B7D4(objectIndex, D_8018D01C * -1431.0, 827.0f, -2957.0f);
    func_80073444(objectIndex, d_course_rainbow_road_neon_mushroom_tlut_list, d_course_rainbow_road_neon_mushroom, 0x40U, (u16) 0x00000040);
    func_80085BB4(objectIndex);
}

void func_80085CA0(s32 objectIndex) {
    switch (D_80165C18[objectIndex].unk_0A6) {
    case 1:
        func_80085C20(objectIndex);
        break;
    case 2:
        func_80072E54(objectIndex, 0, 4, 1, 0x0000000C, 5);
        break;
    case 3:
        func_80072D3C(objectIndex, 3, 4, 4, 0x0000000A);
        break;
    case 4:
        func_8007278C(objectIndex, 0x00000014);
        break;
    case 5:
        func_80072E54(objectIndex, 0, 4, 1, 0x0000000C, 5);
        break;
    case 6:
        func_8007278C(objectIndex, 0x00000014);
        break;
    case 7:
        func_80072D3C(objectIndex, 3, 4, 0, 0x00000014);
        break;
    case 8:
        func_800726CC(objectIndex, 2);
        break;
    case 0:
    default:
        break;
    }
}

void func_80085DB8(s32 objectIndex) {
    func_8008B7D4(objectIndex, D_8018D01C * 799.0, 1193.0f, -5891.0f);
    func_80073444(objectIndex, d_course_rainbow_road_neon_mario_tlut_list, d_course_rainbow_road_neon_mario, 0x40U, (u16) 0x00000040);
    func_80085BB4(objectIndex);
}

void func_80085E38(s32 objectIndex) {
    switch (D_80165C18[objectIndex].unk_0A6) {
    case 1:
        func_80085DB8(objectIndex);
        break;
    case 2:
        func_80072E54(objectIndex, 0, 4, 1, 0x0000000C, 1);
        break;
    case 3:
        func_80072D3C(objectIndex, 3, 4, 0x0000000C, 1);
        break;
    case 4:
        func_80072B48(objectIndex, 0x0000000C);
        break;
    case 5:
        func_800726CC(objectIndex, 2);
        break;
    case 0:
    default:
        break;
    }
}

void func_80085EF8(s32 objectIndex) {
    func_8008B7D4(objectIndex, D_8018D01C * -2013.0, 555.0f, 0.0f);
    func_80073444(objectIndex, d_course_rainbow_road_neon_boo_tlut_list, d_course_rainbow_road_neon_boo, 0x40U, (u16) 0x00000040);
    func_80085BB4(objectIndex);
}

void func_80085F74(s32 objectIndex) {
    switch (D_80165C18[objectIndex].unk_0A6) {
    case 1:
        func_80085EF8(objectIndex);
        break;
    case 2:
        func_80072E54(objectIndex, 0, 4, 1, 5, 1);
        break;
    case 3:
        func_8007278C(objectIndex, 0x0000001E);
        break;
    case 4:
        func_80072C00(objectIndex, 4, 0, 7);
        break;
    case 5:
        func_8007278C(objectIndex, 0x0000001E);
        break;
    case 6:
        func_80072F88(objectIndex, 3, 0, 1, 5, 1);
        break;
    case 7:
        func_80072B48(objectIndex, 0x0000000F);
        break;
    case 8:
        func_800726CC(objectIndex, 2);
        break;
    case 0:
    default:
        break;
    }
}

#ifdef NON_MATCHING
/**
 * arg1 is pushed onto the stack prior to func_8008B7D4, which is correct.
 * But then it get popped back into v0 when its supposed to be popped into t0.
 * I really, really don't get why that's happening and the permuter hasn't found anything
**/
extern Vec3f D_800E6734[];                               /* unable to generate initializer */

void func_80086074(s32 objectIndex, s32 arg1) {
    func_8008B7D4(objectIndex, D_800E6734[arg1][0] * D_8018D01C, D_800E6734[arg1][1], D_800E6734[arg1][2]);
    func_80073444(objectIndex, d_course_rainbow_road_static_tluts[arg1], d_course_rainbow_road_static_textures[arg1], 64, 64);
    func_80085BB4(objectIndex);
}
#else
GLOBAL_ASM("asm/non_matchings/code_80071F00/func_80086074.s")
#endif

void func_80086110(s32 objectIndex, s32 arg1) {
    switch (D_80165C18[objectIndex].unk_0A6) {
    case 1:
        func_80086074(objectIndex, arg1);
        break;
    case 0:
        break;
    }
}

void func_80086158(s32 objectIndex, s32 arg1) {
    switch (arg1) {                                 /* irregular */
    case 0:
        func_80085CA0(objectIndex);
        break;
    case 1:
        func_80085E38(objectIndex);
        break;
    case 2:
        func_80085F74(objectIndex);
        break;
    }
    if (arg1 >= 3) {
        func_80086110(objectIndex, arg1 - 3);
    }
}

void func_800861E0(void) {
    s32 temp_s0;
    s32 var_s2;

    for (var_s2 = 0; var_s2 < NUM_NEON_SIGNS; var_s2++) {
        temp_s0 = D_80183EA0[var_s2];
        if (D_80165C18[temp_s0].unk_0A6 != 0) {
            func_80086158(temp_s0, var_s2);
            if (D_80165C18[temp_s0].unk_0A6 >= 2) {
                func_800734DC(temp_s0);
                func_8008BF18(temp_s0);
            }
        }
    }
}

void func_8008629C(s32 objectIndex, s32 arg1) {
    switch (arg1) {                                 /* irregular */
    case 0:
        D_80165C18[objectIndex].unk_070 = D_0B0075F0;
        D_80165C18[objectIndex].unk_04C = 0x00000038;
        break;
    case 1:
        D_80165C18[objectIndex].unk_070 = D_0B008040;
        D_80165C18[objectIndex].unk_04C = 0x0000002B;
        break;
    case 2:
        D_80165C18[objectIndex].unk_070 = D_0B008A90;
        D_80165C18[objectIndex].unk_04C = 0x0000001E;
        break;
    default:
        break;
    }
    D_80165C18[objectIndex].sizeScaling = 1.0f;
    func_8008B7D4(objectIndex, D_800E634C[0][0] - 1.5, D_800E634C[0][1], D_800E634C[0][2]);
    func_8008B80C(objectIndex, 0.0f, -10.0f, 0.0f);
    func_8008B888(objectIndex, 0U, 0xF8E4U, 0U);
    D_80165C18[objectIndex].unk_048 = 0;
    func_80072488(objectIndex);
}

void func_80086424(s32 objectIndex) {
    switch (D_80165C18[objectIndex].unk_0AE) {
    case 0:
        break;
    case 1:
        D_80165C18[objectIndex].unk_038[1] = 0.75f;
        func_80086FD4(objectIndex);
        break;
    case 2:
        if (D_80165C18[objectIndex].unk_028[1] >= -2.0) {
            D_80165C18[objectIndex].unk_038[1] -= 0.1;
        }
        func_800877C4(objectIndex);
        if (D_80165C18[objectIndex].unk_028[1] >= 0.0) {
            D_80165C18[objectIndex].unk_028[1] = 0.0f;
            D_80165C18[objectIndex].unk_038[1] = 0.0f;
            func_80086F60(objectIndex);
        }
        break;
    }
    func_8008BF18(objectIndex);
}

void func_80086528(s32 objectIndex, s32 arg1) {
    switch (D_80165C18[objectIndex].unk_0A6) {                              /* irregular */
    case 1:
        func_8008629C(objectIndex, arg1);
        break;
    case 2:
        if (func_8007278C(objectIndex, D_80165C18[objectIndex].unk_04C) != 0) {
            func_80091440(arg1);
            func_80086E70(objectIndex);
            func_80072488(objectIndex);
        }
        break;
    case 0:
        break;
    case 3:
        if (D_80165C18[objectIndex].unk_0AE == 0) {
            D_80165C18[objectIndex].unk_048 = 1;
            func_80072488(objectIndex);
        }
        break;
    }
}

#ifdef MIPS_TO_C
//generated by m2c commit eefca95b040d7ee0c617bc58f9ac6cd1cf7bce87 on Aug-10-2023
extern s16 D_8016347C;
extern s8 D_801658C6;
extern ? D_80183EAC;

void func_80086604(void) {
    s32 *var_s1;
    s32 *var_s1_2;
    s32 temp_s0;
    s32 var_s2;

    if ((D_8016347C != 0) && (D_802874D8.unk1D < 3)) {
        var_s1 = D_80183EA0;
        if (D_801658C6 == 0) {
            do {
                func_800723A4(*var_s1, 0);
                var_s1 += 4;
            } while (var_s1 != &D_80183EAC);
            D_801658C6 = 1;
        }
    }
    var_s1_2 = D_80183EA0;
    var_s2 = 0;
    do {
        temp_s0 = *var_s1_2;
        if (D_80165C18[temp_s0].unk_0A6 != 0) {
            func_80086528(temp_s0, var_s2);
            func_80086424(temp_s0);
        }
        var_s2 += 1;
        var_s1_2 += 4;
    } while (var_s2 != 3);
}
#else
GLOBAL_ASM("asm/non_matchings/code_80071F00/func_80086604.s")
#endif

void func_80086700(s32 objectIndex) {
    if (gCCSelection < CC_150) {
        switch (D_802874D8.unk1D) {                       /* switch 1; irregular */
        case 0:                                     /* switch 1 */
            D_80165C18[objectIndex].unk_070 = D_0B0069D8;
            break;
        case 1:                                     /* switch 1 */
            D_80165C18[objectIndex].unk_070 = D_0B006A78;
            break;
        case 2:                                     /* switch 1 */
            D_80165C18[objectIndex].unk_070 = D_0B006B18;
            break;
        default:                                    /* switch 1 */
            break;
        }
    } else {
        switch (D_802874D8.unk1D) {                       /* irregular */
        case 0:
            D_80165C18[objectIndex].unk_070 = D_0B006A28;
            break;
        case 1:
            D_80165C18[objectIndex].unk_070 = D_0B006AC8;
            break;
        case 2:
            D_80165C18[objectIndex].unk_070 = D_0B006B68;
            break;
        default:
            break;
        }
    }
    D_80165C18[objectIndex].sizeScaling = 0.005f;
    func_8008B7D4(objectIndex, D_80165C18[D_80183F28[0]].pos[0], D_80165C18[D_80183F28[0]].pos[1] + 16.0, D_80165C18[D_80183F28[0]].pos[2]);
    func_8008B80C(objectIndex, 0.0f, 0.0f, 0.0f);
    func_8008B888(objectIndex, 0U, 0U, 0U);
    D_80165C18[objectIndex].unk_084[1] = 0x0200;
    func_80072488(objectIndex);
    func_80086E70(objectIndex);
}

#ifdef MIPS_TO_C
//generated by m2c commit 8267401fa4ef7a38942dcca43353cc1bcc6efabc
extern s8 D_801658D6;
extern s8 D_801658F4;

void func_80086940(s32 objectIndex) {
    s8 temp_v0;
    struct_80165C18_entry *temp_s0;
    u16 temp_t8;

    temp_s0 = &D_80165C18[objectIndex];
    temp_t8 = (u16) temp_s0->unk_0AE;
    switch (temp_t8) {
    case 1:
        func_80086FD4(objectIndex);
        break;
    case 2:
        f32_step_towards(&temp_s0->sizeScaling, 0.025f, 0.001f);
        func_80087C48(objectIndex, 6.0f, 0.1f, 0x000000C8);
        if ((f64) temp_s0->unk_038[1] <= 0.0) {
            func_8008701C(objectIndex, 3);
        }
        break;
    case 3:
        func_800871AC(objectIndex, 0x00000064);
        break;
    case 4:
        D_801658D6 = 1;
        temp_s0->unk_038[1] = -0.4f;
        func_80086FD4(objectIndex);
        temp_s0->unk_010[1] = 90.0f;
        temp_s0->unk_028[1] = 60.0f;
        switch (D_802874D8.unk1D) {
        case 1:                                     /* switch 1 */
            temp_s0->unk_010[0] = (f32) ((f64) temp_s0->unk_010[0] - 3.0);
            temp_s0->unk_010[2] = (f32) ((f64) temp_s0->unk_010[2] + 15.0);
            break;
        case 2:                                     /* switch 1 */
            temp_s0->unk_010[0] = (f32) ((f64) temp_s0->unk_010[0] - 2.0);
            temp_s0->unk_010[2] = (f32) ((f64) temp_s0->unk_010[2] - 15.0);
            break;
        }
        break;
    case 5:
        if ((f64) temp_s0->unk_028[1] <= 8.0) {
            f32_step_towards(&temp_s0->unk_038[1], -0.1f, -0.01f);
        }
        func_800877C4(objectIndex);
        if ((f64) temp_s0->unk_028[1] <= 0.0) {
            func_80086FD4(objectIndex);
        }
        break;
    case 6:
        if (func_800871AC(objectIndex, 0x00000041) != 0) {
            D_801658F4 = 1;
        }
        break;
    case 7:
        if (func_800871AC(objectIndex, 0x00000064) != 0) {
            func_8009265C();
            func_80086F60(objectIndex);
        }
        break;
    }
    if (D_801658D6 != 0) {
        temp_s0->unk_0BE[1] = 0xE800;
        temp_s0->unk_0BE[2] = 0xDA00;
        temp_s0->unk_0BE[0] += 0x400;
    } else {
        temp_s0->unk_0BE[0] += 0x400;
        temp_s0->unk_0BE[1] -= 0x200;
    }
    func_8008BF18(objectIndex);
}
#else
GLOBAL_ASM("asm/non_matchings/code_80071F00/func_80086940.s")
#endif

void func_80086C14(s32 objectIndex) {
    switch (D_80165C18[objectIndex].unk_0A6) {                              /* irregular */
    case 1:
        func_80086700(objectIndex);
        break;
    case 0:
    case 2:
        break;
    }
}

void func_80086C6C(s32 objectIndex) {
    Vec3f sp24;

    sp24[0] = (D_80165C18[objectIndex].pos[0] - 5.0f) + random_int(0x000AU);
    sp24[2] = (D_80165C18[objectIndex].pos[2] - 5.0f) + random_int(0x000AU);
    if (D_801658F4 != 0) {
        sp24[1] = D_80165C18[objectIndex].pos[1] + 14.0;
    } else {
        sp24[1] = D_80165C18[objectIndex].pos[1] - 2.0;
    }
    func_800773D8(sp24, (s32) D_801658F4);
}

#ifdef MIPS_TO_C
//generated by m2c commit eefca95b040d7ee0c617bc58f9ac6cd1cf7bce87 on Aug-10-2023
extern s32 D_8016559C;
extern s8 D_801658DC;
extern ? D_80165CBE;
extern s32 D_80183EAC;

void func_80086D80(void) {
    s32 temp_s2;
    s32 var_s0;

    if ((D_801658CE != 0) && (D_801658DC == 0)) {
        func_800723A4(D_80183EAC, 0);
        D_801658DC = 1;
    }
    temp_s2 = D_80183EAC;
    if (*(&D_80165CBE + (temp_s2 * 0xE0)) != 0) {
        func_80086C14(temp_s2);
        func_80086940(temp_s2);
        var_s0 = 0;
        if (D_801658F4 != 0) {
            if (D_8016559C == 0) {
                func_80086C6C(temp_s2);
            }
        } else {
            do {
                func_80086C6C(temp_s2);
                var_s0 += 1;
            } while (var_s0 != 2);
        }
    }
}
#else
GLOBAL_ASM("asm/non_matchings/code_80071F00/func_80086D80.s")
#endif
