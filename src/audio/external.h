#ifndef AUDIO_EXTERNAL_H
#define AUDIO_EXTERNAL_H

#include "common_structs.h"
#include "camera.h"

#define ADSR_STATE_DISABLED 0
#define ADSR_STATE_INITIAL 1
#define ADSR_STATE_START_LOOP 2
#define ADSR_STATE_LOOP 3
#define ADSR_STATE_FADE 4
#define ADSR_STATE_HANG 5
#define ADSR_STATE_DECAY 6
#define ADSR_STATE_RELEASE 7
#define ADSR_STATE_SUSTAIN 8

#define ADSR_ACTION_RELEASE 0x10
#define ADSR_ACTION_DECAY 0x20
#define ADSR_ACTION_HANG 0x40

#define ADSR_DISABLE 0
#define ADSR_HANG -1
#define ADSR_GOTO -2
#define ADSR_RESTART -3

// Sequence arguments, passed to seq_player_play_sequence. seqId may be bit-OR'ed with
// SEQ_VARIATION; this will load the same sequence, but set a variation
// bit which may be read by the sequence script.
#define SEQUENCE_ARGS(priority, seqId) ((priority << 8) | seqId)

#define SOUND_MODE_STEREO           0
#define SOUND_MODE_MONO             3
#define SOUND_MODE_HEADSET          1

#define SEQ_PLAYER_LEVEL            0  // Level background music
#define SEQ_PLAYER_ENV              1  // Misc music like the puzzle jingle
#define SEQ_PLAYER_SFX              2  // Sound effects

#define SOUND_BANK_UNK0  0
#define SOUND_BANK_UNK1  1
#define SOUND_BANK_UNK2  2
#define SOUND_BANK_UNK3  3
#define SOUND_BANK_UNK4  4
#define SOUND_BANK_UNK5  5
#define SOUND_BANK_COUNT 6

// Almost certainly an expanded version of struct Sound from SM64
struct Unk_8018FC20 {
    /* 0x00 */ u32 soundBits;
    /* 0x04 */ f32 *position;
    /* 0x08 */ u8  cameraId; // playerId? some indicator of "who" the sound is desitned for
    /* 0x09 */ // u8  compilerPadding0[3];
	/* 0x0C */ f32 *unk0C;
	/* 0x10 */ f32 *unk10;
	/* 0x14 */ u8  *unk14;
}; // size = 0x18

struct Unk_800E9F7C {
	/* 0x00 */ Vec3f pos;
	/* 0x0C */ f32 unk_0C;
	/* 0x10 */ f32 unk_10;
	/* 0x14 */ s8 unk_14;
	/* 0x15 */ // s8 comilerPadding[3];
	/* 0x18 */ f32 unk_18;
	/* 0x1C */ f32 unk_1C;
	/* 0x20 */ f32 unk_20;
	/* 0x24 */ f32 unk_24;
	/* 0x28 */ f32 unk_28;
	/* 0x2C */ f32 unk_2C;
	/* 0x30 */ f32 unk_30;
	/* 0x34 */ f32 unk_34;
	/* 0x38 */ f32 unk_38;
} ; // size = 0x3C

// I'm speculating that this struct has something to do with
// the doppler effect that happens to some sounds
struct Unk_8018EFD8 {
	// Pointers to a position
	/* 0x00 */ f32 *posX;
	/* 0x04 */ f32 *posY;
	/* 0x08 */ f32 *posZ;
	// Pointers to a velocity
	/* 0x0C */ f32 *velX;
	/* 0x10 */ f32 *velY;
	/* 0x14 */ f32 *velZ;
	/* 0x18 */ Vec3f unk18;
	/* 0x24 */ f32 *unk24; // Some type of multiplier/scalar
	// Indexes in D_8018EFD8, not really sure what they're for though
	/* 0x28 */ u8 cameraId; // playerId? some indicator of "who" the sound is desitned for
	/* 0x29 */ u8 prev;
	/* 0x2A */ u8 next;
	/* 0x2B */ // u8 compilerPadding00;
	/* 0x2C */ f32 unk2C;
	/* 0x30 */ u8 unk30;
	/* 0x31 */ // u8 compilerPadding01[3];
	/* 0x34 */ f32 unk34;
	/* 0x38 */ u32 soundBits;
}; // size = 0x3C

// This is almost certainly an expanded version of SoundCharacteristics from SM64
struct Unk_80191420 {
	// These f32 pointers appear to point to the `Vec3f unk18` members in a struct Unk_8018EFD8
	/* 0x00 */ f32 *unk00;
	/* 0x04 */ f32 *unk04;
	/* 0x08 */ f32 *unk08;
	/* 0x0C */ u8 cameraId; // playerId? some indicator of "who" the sound is desitned for
	/* 0x0D */ // u8 compilerPadding0[3];
	/* 0x10 */ f32 *unk10;
	/* 0x14 */ f32 *unk14;
	/* 0x18 */ s8  *unk18;
	/* 0x1C */ f32 distance; // XZ distance from the camera
	/* 0x20 */ u32 priority;
	/* 0x24 */ u32 soundBits;
	/* 0x28 */ u8  soundStatus;
	/* 0x29 */ u8  freshness;
	/* 0x2A */ u8  prev;
	/* 0x2B */ u8  next;
	/* 0x2C */ u8 unk2C;
}; // size = 0x30

struct Unk_800EA06C {
	/* 0x00 */ Vec3f unk00;
	/* 0x0C */ u8 unk0C;
	/* 0x0D */ // u8 compilerPadding0[3];
};

void func_800C94A4(u8);
void func_800CADD0(u8, f32);
void func_800C13F0(void);
void func_800C13FC(OSMesg);
f32  func_800C1480(u8, u8);
s8   func_800C15D0(u8, u8, u8);
f32  func_800C1934(u8, u8);
struct Unk_8018EFD8 *func_800C1C88(u8, Vec3f, Vec3f, f32*, u8, u32);
void func_800C1DA4(Camera*, Vec3s, struct Unk_8018EFD8*);
void func_800C1E2C(Camera*, Vec3f, struct Unk_8018EFD8*);
void func_800C1F8C(void);

f32 *func_800C21E8(Vec3f, u32);
void func_800C2274(s32);
void func_800C2474(void);
void func_800C284C(u8, u8, u8, s32);

void func_800C3724(void);
void func_800C3448(u32);
void func_800C3478(void);
u16  func_800C3508(s32);
u8   func_800C357C(s32);
void func_800C35E8(u8);
void func_800C36C4(s32, u32, u8, s8);
void func_800C3F70(void);

void func_800C400C(void);
void func_800C4084(u16);
void play_sound(u32, f32*, u8, f32*, f32*, u8*);
void func_800C41CC(u8, struct Unk_80191420*);
void func_800C4398(void);
void func_800C473C(u8, u8);
void func_800C4888(u8);
void func_800C4FE4(u8);

void func_800C5278(u8);
void func_800C5384(u8, f32*);
void func_800C54B8(u8, s32);
void func_800C550C(s32);
void func_800C5578(Vec3f, u32);
u8   func_800C56F0(u32);
void func_800C5848(void);
void func_800C58B8(u8, u8, u16);
void func_800C5968(u8);
void func_800C59C4(void);
void func_800C5A3C(void);
void func_800C5BD0(void);
void func_800C5C40(void);
void func_800C5CB8(void);
void func_800C5D04(u8);
void func_800C5E38(u8);

void func_800C6108(u8);
void func_800C64A0(u8);
void func_800C6758(u8);
void func_800C683C(u8);

void func_800C70A8(u8);
void func_800C76C0(u8);

void func_800C847C(u8);
void func_800C86D8(u8);
void func_800C8770(u8);
void func_800C8920(void);
void func_800C89E4(void);
void func_800C8AE4(void);
void func_800C8C7C(u8);
void func_800C8CCC(void);
void play_sound2(s32);
void func_800C8EAC(u16);
void func_800C8EF8(u16);
void func_800C8F44(u8);
void func_800C8F80(u8, u32);

void func_800C9018(u8, s32);
void func_800C9060(u8, u32);
void func_800C90F4(u8, u32);
void func_800C9250(u8);
void func_800C92CC(u8, u32);
void func_800C94A4(u8);
void func_800C97C4(u8);
void func_800C98B8(Vec3f, Vec3f, u32);
void func_800C99E0(Vec3f, s32);
void func_800C9A88(u8);
void func_800C9D0C(u8);
void func_800C9D80(Vec3f, Vec3f, u32);
void func_800C9EF4(Vec3f, u32);
void func_800C9F90(u8);

void func_800CA008(u8, u8);
void func_800CA0A0(void);
void func_800CA0B8(void);
void func_800CA0CC(void);
void func_800CA0E4(void);
void func_800CA118(u8);
void func_800CA24C(u8);
void func_800CA270(void);
void func_800CA288(u8, s8);
void func_800CA2B8(u8);
void func_800CA2E4(u8, s8);
void func_800CA30C(u8);
void func_800CA330(u8);
void func_800CA388(u8);
void func_800CA414(u16, u16);
void func_800CA49C(u8);
void func_800CA59C(u8);
void func_800CA984(u8);
void func_800CAACC(u8);
void func_800CAB4C(u8);
void func_800CAC08(void);
void func_800CAC60(s32);
void func_800CAD40(s32);
void func_800CAEC4(u8, f32);
void func_800CAFC0(u8);

void func_800CB134(void);
void func_800CB14C(void);
void func_800CB2C4(void);
void func_800CBC24(void);

// Based on SM64, this should be part of data.c's BSS section. Somehow.
extern s32 gAudioErrorFlags;

extern s8 D_8018EF10;
extern struct Unk_8018EFD8 D_8018EFD8[];
// These are indexes for D_8018EFD8, but their purpose is unknown
extern u8 D_8018FB90;
extern u8 D_8018FB91;
extern Camera *D_8018FB98[4];
extern Vec3f D_8018FBA8[4];
extern Vec3f D_8018FBD8[4];
extern u8 D_8018FC08;

extern struct Unk_80191420 sSoundBanks[SOUND_BANK_COUNT][20];
extern u8 sSoundBankUsedListBack[SOUND_BANK_COUNT];
extern u8 sSoundBankFreeListFront[SOUND_BANK_COUNT];
extern u8 sNumSoundsInBank[SOUND_BANK_COUNT];
extern u8 sNumProcessedSoundRequests;
extern u8 sSoundRequestCount;
extern struct Unk_8018FC20 sSoundRequests[0x100];

extern u8  D_80192CC6[];
extern u32 D_80192CD0[];

// Data entries
extern u8  D_800E9DA0;
extern f32 D_800E9DC4[4];// = { 1.0f, 1.0f, 1.0f, 1.0f };
extern f32 D_800E9DD4[4];// = { 0.0f, 0.0f, 0.0f, 0.0f };
extern f32 D_800E9DE4[4];// = { 0.0f, 0.0f, 0.0f, 0.0f };
extern f32 D_800E9DF4[8];// = { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };
extern s32 D_800E9E14[4];// = { 0, 0, 0, 0 };
extern s32 D_800E9E24[4];// = { 0, 0, 0, 0 };
extern s32 D_800E9E34[8];
extern f32 D_800E9E54[4];// = { 0.0f, 0.0f, 0.0f, 0.0f }; /* const */
extern f32 D_800E9E64[4];// = { 0.0f, 0.0f, 0.0f, 0.0f };
extern s32 D_800E9E74[4];// = { 0, 0, 0, 0 };          /* const */
extern s32 D_800E9E84[4];
extern u32 D_800E9E94[4];
extern s32 D_800E9EA4[4];// = { 0, 0, 0, 0 };
extern f32 D_800E9EB4[4];// = { 0.0f, 0.0f, 0.0f, 0.0f };
extern f32 D_800E9EC4[4];// = { 0.0f, 0.0f, 0.0f, 0.0f };
extern f32 D_800E9ED4[4];// = { 0.0f, 0.0f, 0.0f, 0.0f };
extern f32 D_800E9EE4[4];// = { 0.0f, 0.0f, 0.0f, 0.0f };
extern f32 D_800E9EF4[4];
extern f32 D_800E9F04[4];// = { 1.0f, 1.0f, 1.0f, 1.0f };
extern f32 D_800E9F14[4];// = { 1.0f, 1.0f, 1.0f, 1.0f }; /* const */
extern u8  D_800E9F24[8];// = { 0, 0, 0, 0, 0, 0, 0, 0 };
extern u8  D_800E9F2C[8];// = { 0, 0, 0, 0, 0, 0, 0, 0 };
extern f32 D_800E9F34[8];// = { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f }; /* const */
extern f32 D_800E9F54[4];// = { 1.0f, 1.0f, 1.0f, 1.0f }; /* const */
extern u8  D_800E9F74[4];
extern u8  D_800E9F78[4];
extern struct Unk_800E9F7C D_800E9F7C[4];
extern u8  D_800E9F90[];
extern struct Unk_800EA06C D_800EA06C[8];
extern u8  D_800EA0EC[];
extern u8  D_800EA0F0;// = 0;
extern u8  D_800EA0F4;
extern u8  D_800EA104;
extern u8  D_800EA108;// = 0;
extern u8  D_800EA10C[];
extern f32 D_800EA110[4];// = { 0.0f, 0.0f, 0.0f, 0.0f };
extern f32 D_800EA120[4];
extern f32 D_800EA130[4];
extern f32 D_800EA150;// = 1.4f;
extern u8  D_800EA154[];
extern u16 D_800EA15C;
extern u16 D_800EA160;
extern u8  D_800EA164;
extern s8  D_800EA168;
extern u8  D_800EA170[];
extern u16 D_800EA174;// = 0;
extern f32 D_800EA178;
extern f32 D_800EA17C;
extern u16 D_800EA180;// = 0;                          /* const */
extern u16 D_800EA184;
extern u8 D_800EA1C0;// = 0;
// Most similar to gGlobalSoundSource from SM64, but I don't know if its really
// a sound source, its usage makes it look like a 0'd Vec3f for general usage
extern Vec3f D_800EA1C8;// = {0.0f, 0.0f, 0.0f}
extern Vec3f D_800EA1D4;
extern u8 D_800EA1DC;// = 0;
extern u8 D_800EA1E4;
extern u8 D_800EA1E8;
extern u8 D_800EA244;

extern s8 D_800EA16C;

extern OSMesgQueue *D_800EA3B0;
extern OSMesgQueue *D_800EA3B4;

#endif
