glabel func_800AA2EC
/* 0AAEEC 800AA2EC 3C0E8019 */  lui   $t6, %hi(gMainMenuSelectionDepth) # $t6, 0x8019
/* 0AAEF0 800AA2F0 81CEEDED */  lb    $t6, %lo(gMainMenuSelectionDepth)($t6)
/* 0AAEF4 800AA2F4 27BDFFD8 */  addiu $sp, $sp, -0x28
/* 0AAEF8 800AA2F8 AFBF001C */  sw    $ra, 0x1c($sp)
/* 0AAEFC 800AA2FC 25CFFFFF */  addiu $t7, $t6, -1
/* 0AAF00 800AA300 2DE10008 */  sltiu $at, $t7, 8
/* 0AAF04 800AA304 AFA40028 */  sw    $a0, 0x28($sp)
/* 0AAF08 800AA308 102000AB */  beqz  $at, .L800AA5B8
/* 0AAF0C 800AA30C 00004825 */   move  $t1, $zero
/* 0AAF10 800AA310 000F7880 */  sll   $t7, $t7, 2
/* 0AAF14 800AA314 3C01800F */  lui   $at, %hi(jpt_800F2580)
/* 0AAF18 800AA318 002F0821 */  addu  $at, $at, $t7
/* 0AAF1C 800AA31C 8C2F2580 */  lw    $t7, %lo(jpt_800F2580)($at)
/* 0AAF20 800AA320 01E00008 */  jr    $t7
/* 0AAF24 800AA324 00000000 */   nop   
glabel L800AA328
/* 0AAF28 800AA328 8FB80028 */  lw    $t8, 0x28($sp)
/* 0AAF2C 800AA32C 100000A2 */  b     .L800AA5B8
/* 0AAF30 800AA330 AF000004 */   sw    $zero, 4($t8)
glabel L800AA334
/* 0AAF34 800AA334 8FB90028 */  lw    $t9, 0x28($sp)
/* 0AAF38 800AA338 3C028019 */  lui   $v0, %hi(D_8018EDF3) # $v0, 0x8019
/* 0AAF3C 800AA33C 8F2A0004 */  lw    $t2, 4($t9)
/* 0AAF40 800AA340 5540009E */  bnel  $t2, $zero, .L800AA5BC
/* 0AAF44 800AA344 8FBF001C */   lw    $ra, 0x1c($sp)
/* 0AAF48 800AA348 8042EDF3 */  lb    $v0, %lo(D_8018EDF3)($v0)
/* 0AAF4C 800AA34C 24010001 */  li    $at, 1
/* 0AAF50 800AA350 3C0B800F */  lui   $t3, %hi((D_800E86AC - 1)) # 0x800f
/* 0AAF54 800AA354 14410098 */  bne   $v0, $at, .L800AA5B8
/* 0AAF58 800AA358 01625821 */   addu  $t3, $t3, $v0
/* 0AAF5C 800AA35C 816B86AB */  lb    $t3, %lo((D_800E86AC - 1))($t3) # -0x7955($t3)
/* 0AAF60 800AA360 24010001 */  li    $at, 1
/* 0AAF64 800AA364 3C03800F */  lui   $v1, %hi(gControllerPak1State) # $v1, 0x800f
/* 0AAF68 800AA368 15610093 */  bne   $t3, $at, .L800AA5B8
/* 0AAF6C 800AA36C 246386F8 */   addiu $v1, %lo(gControllerPak1State) # addiu $v1, $v1, -0x7908
/* 0AAF70 800AA370 806C0000 */  lb    $t4, ($v1)
/* 0AAF74 800AA374 3C048019 */  lui   $a0, %hi(gControllerPak1FileHandle) # $a0, 0x8019
/* 0AAF78 800AA378 2484E868 */  addiu $a0, %lo(gControllerPak1FileHandle) # addiu $a0, $a0, -0x1798
/* 0AAF7C 800AA37C 1180001F */  beqz  $t4, .L800AA3FC
/* 0AAF80 800AA380 3C05800F */   lui   $a1, %hi(gCompanyCode) # $a1, 0x800f
/* 0AAF84 800AA384 3C0D800F */  lui   $t5, %hi(gExtCode) # $t5, 0x800f
/* 0AAF88 800AA388 3C0E8019 */  lui   $t6, %hi(gControllerPak1FileNote) # $t6, 0x8019
/* 0AAF8C 800AA38C 25CEEB84 */  addiu $t6, %lo(gControllerPak1FileNote) # addiu $t6, $t6, -0x147c
/* 0AAF90 800AA390 25AD2E74 */  addiu $t5, %lo(gExtCode) # addiu $t5, $t5, 0x2e74
/* 0AAF94 800AA394 3C06800F */  lui   $a2, %hi(gGameCode) # $a2, 0x800f
/* 0AAF98 800AA398 3C07800F */  lui   $a3, %hi(gGameName) # $a3, 0x800f
/* 0AAF9C 800AA39C 24E72E64 */  addiu $a3, %lo(gGameName) # addiu $a3, $a3, 0x2e64
/* 0AAFA0 800AA3A0 8CC686F4 */  lw    $a2, %lo(gGameCode)($a2)
/* 0AAFA4 800AA3A4 AFAD0010 */  sw    $t5, 0x10($sp)
/* 0AAFA8 800AA3A8 AFAE0014 */  sw    $t6, 0x14($sp)
/* 0AAFAC 800AA3AC 94A586F0 */  lhu   $a1, %lo(gCompanyCode)($a1)
/* 0AAFB0 800AA3B0 0C033E20 */  jal   osPfsFindFile
/* 0AAFB4 800AA3B4 AFA90020 */   sw    $t1, 0x20($sp)
/* 0AAFB8 800AA3B8 3C03800F */  lui   $v1, %hi(gControllerPak1State) # $v1, 0x800f
/* 0AAFBC 800AA3BC 246386F8 */  addiu $v1, %lo(gControllerPak1State) # addiu $v1, $v1, -0x7908
/* 0AAFC0 800AA3C0 8FA80028 */  lw    $t0, 0x28($sp)
/* 0AAFC4 800AA3C4 10400008 */  beqz  $v0, .L800AA3E8
/* 0AAFC8 800AA3C8 8FA90020 */   lw    $t1, 0x20($sp)
/* 0AAFCC 800AA3CC 24010002 */  li    $at, 2
/* 0AAFD0 800AA3D0 10410009 */  beq   $v0, $at, .L800AA3F8
/* 0AAFD4 800AA3D4 24010005 */   li    $at, 5
/* 0AAFD8 800AA3D8 10410008 */  beq   $v0, $at, .L800AA3FC
/* 0AAFDC 800AA3DC 00000000 */   nop   
/* 0AAFE0 800AA3E0 10000006 */  b     .L800AA3FC
/* 0AAFE4 800AA3E4 A0600000 */   sb    $zero, ($v1)
.L800AA3E8:
/* 0AAFE8 800AA3E8 240F0001 */  li    $t7, 1
/* 0AAFEC 800AA3EC AD0F0004 */  sw    $t7, 4($t0)
/* 0AAFF0 800AA3F0 10000002 */  b     .L800AA3FC
/* 0AAFF4 800AA3F4 24090001 */   li    $t1, 1
.L800AA3F8:
/* 0AAFF8 800AA3F8 A0600000 */  sb    $zero, ($v1)
.L800AA3FC:
/* 0AAFFC 800AA3FC 5520006F */  bnel  $t1, $zero, .L800AA5BC
/* 0AB000 800AA400 8FBF001C */   lw    $ra, 0x1c($sp)
/* 0AB004 800AA404 80780000 */  lb    $t8, ($v1)
/* 0AB008 800AA408 17000055 */  bnez  $t8, .L800AA560
/* 0AB00C 800AA40C 00000000 */   nop   
/* 0AB010 800AA410 0C02D6CB */  jal   check_for_controller_pak
/* 0AB014 800AA414 00002025 */   move  $a0, $zero
/* 0AB018 800AA418 14400004 */  bnez  $v0, .L800AA42C
/* 0AB01C 800AA41C 8FA80028 */   lw    $t0, 0x28($sp)
/* 0AB020 800AA420 24190002 */  li    $t9, 2
/* 0AB024 800AA424 10000064 */  b     .L800AA5B8
/* 0AB028 800AA428 AD190004 */   sw    $t9, 4($t0)
.L800AA42C:
/* 0AB02C 800AA42C 3C048015 */  lui   $a0, %hi(gSIEventMesgQueue) # $a0, 0x8015
/* 0AB030 800AA430 3C058019 */  lui   $a1, %hi(gControllerPak1FileHandle) # $a1, 0x8019
/* 0AB034 800AA434 24A5E868 */  addiu $a1, %lo(gControllerPak1FileHandle) # addiu $a1, $a1, -0x1798
/* 0AB038 800AA438 2484F0B8 */  addiu $a0, %lo(gSIEventMesgQueue) # addiu $a0, $a0, -0xf48
/* 0AB03C 800AA43C 0C0339C8 */  jal   osPfsInit
/* 0AB040 800AA440 00003025 */   move  $a2, $zero
/* 0AB044 800AA444 3C03800F */  lui   $v1, %hi(gControllerPak1State) # $v1, 0x800f
/* 0AB048 800AA448 246386F8 */  addiu $v1, %lo(gControllerPak1State) # addiu $v1, $v1, -0x7908
/* 0AB04C 800AA44C 10400013 */  beqz  $v0, .L800AA49C
/* 0AB050 800AA450 8FA80028 */   lw    $t0, 0x28($sp)
/* 0AB054 800AA454 24010001 */  li    $at, 1
/* 0AB058 800AA458 1041000A */  beq   $v0, $at, .L800AA484
/* 0AB05C 800AA45C 240A0002 */   li    $t2, 2
/* 0AB060 800AA460 24010004 */  li    $at, 4
/* 0AB064 800AA464 1041000B */  beq   $v0, $at, .L800AA494
/* 0AB068 800AA468 240C0003 */   li    $t4, 3
/* 0AB06C 800AA46C 2401000A */  li    $at, 10
/* 0AB070 800AA470 10410006 */  beq   $v0, $at, .L800AA48C
/* 0AB074 800AA474 240B0003 */   li    $t3, 3
/* 0AB078 800AA478 2401000B */  li    $at, 11
/* 0AB07C 800AA47C 14410005 */  bne   $v0, $at, .L800AA494
/* 0AB080 800AA480 00000000 */   nop   
.L800AA484:
/* 0AB084 800AA484 1000004C */  b     .L800AA5B8
/* 0AB088 800AA488 AD0A0004 */   sw    $t2, 4($t0)
.L800AA48C:
/* 0AB08C 800AA48C 1000004A */  b     .L800AA5B8
/* 0AB090 800AA490 AD0B0004 */   sw    $t3, 4($t0)
.L800AA494:
/* 0AB094 800AA494 10000048 */  b     .L800AA5B8
/* 0AB098 800AA498 AD0C0004 */   sw    $t4, 4($t0)
.L800AA49C:
/* 0AB09C 800AA49C 240D0001 */  li    $t5, 1
/* 0AB0A0 800AA4A0 A06D0000 */  sb    $t5, ($v1)
/* 0AB0A4 800AA4A4 3C0E800F */  lui   $t6, %hi(gExtCode) # $t6, 0x800f
/* 0AB0A8 800AA4A8 3C0F8019 */  lui   $t7, %hi(gControllerPak1FileNote) # $t7, 0x8019
/* 0AB0AC 800AA4AC 25EFEB84 */  addiu $t7, %lo(gControllerPak1FileNote) # addiu $t7, $t7, -0x147c
/* 0AB0B0 800AA4B0 25CE2E74 */  addiu $t6, %lo(gExtCode) # addiu $t6, $t6, 0x2e74
/* 0AB0B4 800AA4B4 3C048019 */  lui   $a0, %hi(gControllerPak1FileHandle) # $a0, 0x8019
/* 0AB0B8 800AA4B8 3C05800F */  lui   $a1, %hi(gCompanyCode) # $a1, 0x800f
/* 0AB0BC 800AA4BC 3C06800F */  lui   $a2, %hi(gGameCode) # $a2, 0x800f
/* 0AB0C0 800AA4C0 3C07800F */  lui   $a3, %hi(gGameName) # $a3, 0x800f
/* 0AB0C4 800AA4C4 24E72E64 */  addiu $a3, %lo(gGameName) # addiu $a3, $a3, 0x2e64
/* 0AB0C8 800AA4C8 8CC686F4 */  lw    $a2, %lo(gGameCode)($a2)
/* 0AB0CC 800AA4CC 94A586F0 */  lhu   $a1, %lo(gCompanyCode)($a1)
/* 0AB0D0 800AA4D0 2484E868 */  addiu $a0, %lo(gControllerPak1FileHandle) # addiu $a0, $a0, -0x1798
/* 0AB0D4 800AA4D4 AFAE0010 */  sw    $t6, 0x10($sp)
/* 0AB0D8 800AA4D8 0C033E20 */  jal   osPfsFindFile
/* 0AB0DC 800AA4DC AFAF0014 */   sw    $t7, 0x14($sp)
/* 0AB0E0 800AA4E0 14400004 */  bnez  $v0, .L800AA4F4
/* 0AB0E4 800AA4E4 8FA80028 */   lw    $t0, 0x28($sp)
/* 0AB0E8 800AA4E8 24180001 */  li    $t8, 1
/* 0AB0EC 800AA4EC 10000032 */  b     .L800AA5B8
/* 0AB0F0 800AA4F0 AD180004 */   sw    $t8, 4($t0)
.L800AA4F4:
/* 0AB0F4 800AA4F4 3C048019 */  lui   $a0, %hi(gControllerPak1FileHandle) # $a0, 0x8019
/* 0AB0F8 800AA4F8 3C058019 */  lui   $a1, %hi(gControllerPak1NumFilesUsed) # $a1, 0x8019
/* 0AB0FC 800AA4FC 3C068019 */  lui   $a2, %hi(gControllerPak1MaxWriteableFiles) # $a2, 0x8019
/* 0AB100 800AA500 24C6EB7C */  addiu $a2, %lo(gControllerPak1MaxWriteableFiles) # addiu $a2, $a2, -0x1484
/* 0AB104 800AA504 24A5EB78 */  addiu $a1, %lo(gControllerPak1NumFilesUsed) # addiu $a1, $a1, -0x1488
/* 0AB108 800AA508 0C033A38 */  jal   osPfsNumFiles
/* 0AB10C 800AA50C 2484E868 */   addiu $a0, %lo(gControllerPak1FileHandle) # addiu $a0, $a0, -0x1798
/* 0AB110 800AA510 10400004 */  beqz  $v0, .L800AA524
/* 0AB114 800AA514 8FA80028 */   lw    $t0, 0x28($sp)
/* 0AB118 800AA518 24190003 */  li    $t9, 3
/* 0AB11C 800AA51C 10000026 */  b     .L800AA5B8
/* 0AB120 800AA520 AD190004 */   sw    $t9, 4($t0)
.L800AA524:
/* 0AB124 800AA524 3C048019 */  lui   $a0, %hi(gControllerPak1FileHandle) # $a0, 0x8019
/* 0AB128 800AA528 3C058019 */  lui   $a1, %hi(gControllerPak1NumPagesFree) # $a1, 0x8019
/* 0AB12C 800AA52C 24A5EB80 */  addiu $a1, %lo(gControllerPak1NumPagesFree) # addiu $a1, $a1, -0x1480
/* 0AB130 800AA530 0C033B48 */  jal   osPfsFreeBlocks
/* 0AB134 800AA534 2484E868 */   addiu $a0, %lo(gControllerPak1FileHandle) # addiu $a0, $a0, -0x1798
/* 0AB138 800AA538 3C038019 */  lui   $v1, %hi(gControllerPak1NumPagesFree) # $v1, 0x8019
/* 0AB13C 800AA53C 2463EB80 */  addiu $v1, %lo(gControllerPak1NumPagesFree) # addiu $v1, $v1, -0x1480
/* 0AB140 800AA540 10400004 */  beqz  $v0, .L800AA554
/* 0AB144 800AA544 8FA80028 */   lw    $t0, 0x28($sp)
/* 0AB148 800AA548 240A0003 */  li    $t2, 3
/* 0AB14C 800AA54C 1000001A */  b     .L800AA5B8
/* 0AB150 800AA550 AD0A0004 */   sw    $t2, 4($t0)
.L800AA554:
/* 0AB154 800AA554 8C6B0000 */  lw    $t3, ($v1)
/* 0AB158 800AA558 000B6203 */  sra   $t4, $t3, 8
/* 0AB15C 800AA55C AC6C0000 */  sw    $t4, ($v1)
.L800AA560:
/* 0AB160 800AA560 3C0D8019 */  lui   $t5, %hi(gControllerPak1MaxWriteableFiles) # $t5, 0x8019
/* 0AB164 800AA564 3C0E8019 */  lui   $t6, %hi(gControllerPak1NumFilesUsed) # $t6, 0x8019
/* 0AB168 800AA568 8DCEEB78 */  lw    $t6, %lo(gControllerPak1NumFilesUsed)($t6)
/* 0AB16C 800AA56C 8DADEB7C */  lw    $t5, %lo(gControllerPak1MaxWriteableFiles)($t5)
/* 0AB170 800AA570 3C038019 */  lui   $v1, %hi(gControllerPak1NumPagesFree) # $v1, 0x8019
/* 0AB174 800AA574 2463EB80 */  addiu $v1, %lo(gControllerPak1NumPagesFree) # addiu $v1, $v1, -0x1480
/* 0AB178 800AA578 01AE082A */  slt   $at, $t5, $t6
/* 0AB17C 800AA57C 14200004 */  bnez  $at, .L800AA590
/* 0AB180 800AA580 8FB80028 */   lw    $t8, 0x28($sp)
/* 0AB184 800AA584 240F0005 */  li    $t7, 5
/* 0AB188 800AA588 1000000B */  b     .L800AA5B8
/* 0AB18C 800AA58C AF0F0004 */   sw    $t7, 4($t8)
.L800AA590:
/* 0AB190 800AA590 8C790000 */  lw    $t9, ($v1)
/* 0AB194 800AA594 8FAB0028 */  lw    $t3, 0x28($sp)
/* 0AB198 800AA598 8FAD0028 */  lw    $t5, 0x28($sp)
/* 0AB19C 800AA59C 2B210079 */  slti  $at, $t9, 0x79
/* 0AB1A0 800AA5A0 14200003 */  bnez  $at, .L800AA5B0
/* 0AB1A4 800AA5A4 240A0001 */   li    $t2, 1
/* 0AB1A8 800AA5A8 10000003 */  b     .L800AA5B8
/* 0AB1AC 800AA5AC AD6A0004 */   sw    $t2, 4($t3)
.L800AA5B0:
/* 0AB1B0 800AA5B0 240C0005 */  li    $t4, 5
/* 0AB1B4 800AA5B4 ADAC0004 */  sw    $t4, 4($t5)
.L800AA5B8:
/* 0AB1B8 800AA5B8 8FBF001C */  lw    $ra, 0x1c($sp)
.L800AA5BC:
/* 0AB1BC 800AA5BC 27BD0028 */  addiu $sp, $sp, 0x28
/* 0AB1C0 800AA5C0 03E00008 */  jr    $ra
/* 0AB1C4 800AA5C4 00000000 */   nop   

/* 0AB1C8 800AA5C8 27BDFFD8 */  addiu $sp, $sp, -0x28
/* 0AB1CC 800AA5CC AFBF001C */  sw    $ra, 0x1c($sp)
/* 0AB1D0 800AA5D0 AFB00018 */  sw    $s0, 0x18($sp)
/* 0AB1D4 800AA5D4 AFA5002C */  sw    $a1, 0x2c($sp)
/* 0AB1D8 800AA5D8 8C820008 */  lw    $v0, 8($a0)
/* 0AB1DC 800AA5DC 8C830000 */  lw    $v1, ($a0)
/* 0AB1E0 800AA5E0 00057600 */  sll   $t6, $a1, 0x18
/* 0AB1E4 800AA5E4 000E2E03 */  sra   $a1, $t6, 0x18
/* 0AB1E8 800AA5E8 00808025 */  move  $s0, $a0
/* 0AB1EC 800AA5EC 10400006 */  beqz  $v0, .L800AA608
/* 0AB1F0 800AA5F0 2463FFD5 */   addiu $v1, $v1, -0x2b
/* 0AB1F4 800AA5F4 24010002 */  li    $at, 2
/* 0AB1F8 800AA5F8 10410015 */  beq   $v0, $at, .L800AA650
/* 0AB1FC 800AA5FC 00A02025 */   move  $a0, $a1
/* 0AB200 800AA600 10000022 */  b     .L800AA68C
/* 0AB204 800AA604 8FBF001C */   lw    $ra, 0x1c($sp)
.L800AA608:
/* 0AB208 800AA608 00A02025 */  move  $a0, $a1
/* 0AB20C 800AA60C 0C02ABF3 */  jal   func_800AAFCC
/* 0AB210 800AA610 AFA30024 */   sw    $v1, 0x24($sp)
/* 0AB214 800AA614 0440001C */  bltz  $v0, .L800AA688
/* 0AB218 800AA618 8FA30024 */   lw    $v1, 0x24($sp)
/* 0AB21C 800AA61C 24180002 */  li    $t8, 2
/* 0AB220 800AA620 0003C880 */  sll   $t9, $v1, 2
/* 0AB224 800AA624 3C04800F */  lui   $a0, %hi(D_800E8340) # 0x800f
/* 0AB228 800AA628 AE180008 */  sw    $t8, 8($s0)
/* 0AB22C 800AA62C 00992021 */  addu  $a0, $a0, $t9
/* 0AB230 800AA630 0C026455 */  jal   segmented_to_virtual_dupe_2
/* 0AB234 800AA634 8C848340 */   lw    $a0, %lo(D_800E8340)($a0) # -0x7cc0($a0)
/* 0AB238 800AA638 8E040018 */  lw    $a0, 0x18($s0)
/* 0AB23C 800AA63C 00002825 */  move  $a1, $zero
/* 0AB240 800AA640 0C026965 */  jal   func_8009A594
/* 0AB244 800AA644 00403025 */   move  $a2, $v0
/* 0AB248 800AA648 10000010 */  b     .L800AA68C
/* 0AB24C 800AA64C 8FBF001C */   lw    $ra, 0x1c($sp)
.L800AA650:
/* 0AB250 800AA650 0C02ABF3 */  jal   func_800AAFCC
/* 0AB254 800AA654 AFA30024 */   sw    $v1, 0x24($sp)
/* 0AB258 800AA658 0441000B */  bgez  $v0, .L800AA688
/* 0AB25C 800AA65C 8FA30024 */   lw    $v1, 0x24($sp)
/* 0AB260 800AA660 00034080 */  sll   $t0, $v1, 2
/* 0AB264 800AA664 3C04800F */  lui   $a0, %hi(D_800E8320) # 0x800f
/* 0AB268 800AA668 AE000008 */  sw    $zero, 8($s0)
/* 0AB26C 800AA66C 00882021 */  addu  $a0, $a0, $t0
/* 0AB270 800AA670 0C026455 */  jal   segmented_to_virtual_dupe_2
/* 0AB274 800AA674 8C848320 */   lw    $a0, %lo(D_800E8320)($a0) # -0x7ce0($a0)
/* 0AB278 800AA678 8E040018 */  lw    $a0, 0x18($s0)
/* 0AB27C 800AA67C 00002825 */  move  $a1, $zero
/* 0AB280 800AA680 0C026965 */  jal   func_8009A594
/* 0AB284 800AA684 00403025 */   move  $a2, $v0
.L800AA688:
/* 0AB288 800AA688 8FBF001C */  lw    $ra, 0x1c($sp)
.L800AA68C:
/* 0AB28C 800AA68C 8FB00018 */  lw    $s0, 0x18($sp)
/* 0AB290 800AA690 27BD0028 */  addiu $sp, $sp, 0x28
/* 0AB294 800AA694 03E00008 */  jr    $ra
/* 0AB298 800AA698 00000000 */   nop   
