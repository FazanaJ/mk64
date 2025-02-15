#ifndef ACTORS_EXTENDED_H
#define ACTORS_EXTENDED_H

#include "common_structs.h"
#include "actor_types.h"

void func_802B0210(Collision*, Collision*);
void func_802B02B4(struct ShellActor*, s32);
void func_802B039C(struct BananaActor*);
void func_802B0464(s16);
void func_802B04E8(struct BananaActor*, s16);
void func_802B0570(struct BananaActor*);
void func_802B0648(struct BananaBunchParent*);
void func_802B0788(s16, struct BananaBunchParent*, Player*);
s32  func_802B09C0(s16);
void update_actor_banana_bunch(struct BananaBunchParent*);
s32  func_802B0E14(s16);
void update_actor_triple_shell(TripleShellParent*, s16);
s32  func_802B17F4(Player*);
s32  func_802B18E4(Player*, s16);
s32  func_802B19EC(TripleShellParent*, Player*, s16, u16);
s32  func_802B1C9C(Player*);
s32  func_802B1E48(Player*);
void func_802B1FFC(Player*);
void update_actor_banana(struct BananaActor*);
void func_802B2914(struct BananaBunchParent*, Player*, s16);
s32  func_802B2C40(Player*);
s32  func_802B2D70(Player*);
void func_802B2EBC(Player*);
void func_802B2FA0(Player*);
void func_802B30EC(void);
void update_actor_green_shell(struct ShellActor*);
void func_802B3B44(struct ShellActor*);
void func_802B3E7C(struct ShellActor*, Player*);
s16  func_802B3FD0(Player*, struct ShellActor*);
void func_802B4104(struct ShellActor*);
void update_actor_red_blue_shell(struct ShellActor*);
void func_802B4E30(struct Actor*);

// audio/external.c
extern void func_800CAB4C(u8);

extern f32 D_802B9F68;

extern s16 gPlayerBalloonCount[];

#endif // ACTORS_EXTENDED_H
