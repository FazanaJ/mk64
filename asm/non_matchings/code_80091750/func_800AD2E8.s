glabel func_800AD2E8
/* 0ADEE8 800AD2E8 27BDFFD0 */  addiu $sp, $sp, -0x30
/* 0ADEEC 800AD2EC AFBF0024 */  sw    $ra, 0x24($sp)
/* 0ADEF0 800AD2F0 AFB00020 */  sw    $s0, 0x20($sp)
/* 0ADEF4 800AD2F4 8C820004 */  lw    $v0, 4($a0)
/* 0ADEF8 800AD2F8 00808025 */  move  $s0, $a0
/* 0ADEFC 800AD2FC 2C410020 */  sltiu $at, $v0, 0x20
/* 0ADF00 800AD300 1020030C */  beqz  $at, .L800ADF34
/* 0ADF04 800AD304 00027080 */   sll   $t6, $v0, 2
/* 0ADF08 800AD308 3C01800F */  lui   $at, %hi(jpt_800F2750)
/* 0ADF0C 800AD30C 002E0821 */  addu  $at, $at, $t6
/* 0ADF10 800AD310 8C2E2750 */  lw    $t6, %lo(jpt_800F2750)($at)
/* 0ADF14 800AD314 01C00008 */  jr    $t6
/* 0ADF18 800AD318 00000000 */   nop
glabel L800AD31C
/* 0ADF1C 800AD31C 240FFF60 */  li    $t7, -160
/* 0ADF20 800AD320 24180001 */  li    $t8, 1
/* 0ADF24 800AD324 AE0F000C */  sw    $t7, 0xc($s0)
/* 0ADF28 800AD328 AE180004 */  sw    $t8, 4($s0)
/* 0ADF2C 800AD32C 3C028019 */  lui   $v0, %hi(D_8018D9BC) # $v0, 0x8019
/* 0ADF30 800AD330 2442D9BC */  addiu $v0, %lo(D_8018D9BC) # addiu $v0, $v0, -0x2644
/* 0ADF34 800AD334 3C19800F */  lui   $t9, %hi(gGP1stPlaceReward) # $t9, 0x800f
/* 0ADF38 800AD338 83390B18 */  lb    $t9, %lo(gGP1stPlaceReward)($t9)
/* 0ADF3C 800AD33C 8C480000 */  lw    $t0, ($v0)
/* 0ADF40 800AD340 3C09800F */  lui   $t1, %hi(gGP2ndPlaceReward) # $t1, 0x800f
/* 0ADF44 800AD344 3C0B800F */  lui   $t3, %hi(gGP3rdPlaceReward) # $t3, 0x800f
/* 0ADF48 800AD348 A1190000 */  sb    $t9, ($t0)
/* 0ADF4C 800AD34C 8C4A0000 */  lw    $t2, ($v0)
/* 0ADF50 800AD350 81290B19 */  lb    $t1, %lo(gGP2ndPlaceReward)($t1)
/* 0ADF54 800AD354 3C0D800F */  lui   $t5, %hi(gGP4thPlaceReward) # $t5, 0x800f
/* 0ADF58 800AD358 A1490001 */  sb    $t1, 1($t2)
/* 0ADF5C 800AD35C 8C4C0000 */  lw    $t4, ($v0)
/* 0ADF60 800AD360 816B0B1A */  lb    $t3, %lo(gGP3rdPlaceReward)($t3)
/* 0ADF64 800AD364 A18B0002 */  sb    $t3, 2($t4)
/* 0ADF68 800AD368 8C4E0000 */  lw    $t6, ($v0)
/* 0ADF6C 800AD36C 81AD0B1B */  lb    $t5, %lo(gGP4thPlaceReward)($t5)
/* 0ADF70 800AD370 A1CD0003 */  sb    $t5, 3($t6)
/* 0ADF74 800AD374 8E0F000C */  lw    $t7, 0xc($s0)
/* 0ADF78 800AD378 100002EE */  b     .L800ADF34
/* 0ADF7C 800AD37C AE0F0020 */   sw    $t7, 0x20($s0)
glabel L800AD380
/* 0ADF80 800AD380 8E040020 */  lw    $a0, 0x20($s0)
/* 0ADF84 800AD384 3C188019 */  lui   $t8, %hi(D_8018D9D8) # $t8, 0x8019
/* 0ADF88 800AD388 24050010 */  li    $a1, 16
/* 0ADF8C 800AD38C AE04000C */  sw    $a0, 0xc($s0)
/* 0ADF90 800AD390 8318D9D8 */  lb    $t8, %lo(D_8018D9D8)($t8)
/* 0ADF94 800AD394 3C02800E */  lui   $v0, %hi(D_800DC5EC) # $v0, 0x800e
/* 0ADF98 800AD398 3C0B8019 */  lui   $t3, %hi(D_8018EDF5) # $t3, 0x8019
/* 0ADF9C 800AD39C 13000003 */  beqz  $t8, .L800AD3AC
/* 0ADFA0 800AD3A0 3C0F800E */   lui   $t7, %hi(D_800DC5EC) # $t7, 0x800e
/* 0ADFA4 800AD3A4 10000001 */  b     .L800AD3AC
/* 0ADFA8 800AD3A8 24050020 */   li    $a1, 32
.L800AD3AC:
/* 0ADFAC 800AD3AC 00853021 */  addu  $a2, $a0, $a1
/* 0ADFB0 800AD3B0 04C3000D */  bgezl $a2, .L800AD3E8
/* 0ADFB4 800AD3B4 AE000020 */   sw    $zero, 0x20($s0)
/* 0ADFB8 800AD3B8 AE060020 */  sw    $a2, 0x20($s0)
/* 0ADFBC 800AD3BC 8C42C5EC */  lw    $v0, %lo(D_800DC5EC)($v0)
/* 0ADFC0 800AD3C0 3C03800E */  lui   $v1, %hi(D_800DC5F0) # $v1, 0x800e
/* 0ADFC4 800AD3C4 84590030 */  lh    $t9, 0x30($v0)
/* 0ADFC8 800AD3C8 03254021 */  addu  $t0, $t9, $a1
/* 0ADFCC 800AD3CC A4480030 */  sh    $t0, 0x30($v0)
/* 0ADFD0 800AD3D0 8C63C5F0 */  lw    $v1, %lo(D_800DC5F0)($v1)
/* 0ADFD4 800AD3D4 84690030 */  lh    $t1, 0x30($v1)
/* 0ADFD8 800AD3D8 01255023 */  subu  $t2, $t1, $a1
/* 0ADFDC 800AD3DC 100002D5 */  b     .L800ADF34
/* 0ADFE0 800AD3E0 A46A0030 */   sh    $t2, 0x30($v1)
/* 0ADFE4 800AD3E4 AE000020 */  sw    $zero, 0x20($s0)
.L800AD3E8:
/* 0ADFE8 800AD3E8 AE00000C */  sw    $zero, 0xc($s0)
/* 0ADFEC 800AD3EC 816BEDF5 */  lb    $t3, %lo(D_8018EDF5)($t3)
/* 0ADFF0 800AD3F0 24010009 */  li    $at, 9
/* 0ADFF4 800AD3F4 3C0C8016 */  lui   $t4, %hi(D_80162DF8) # $t4, 0x8016
/* 0ADFF8 800AD3F8 15610007 */  bne   $t3, $at, .L800AD418
/* 0ADFFC 800AD3FC AE0B0004 */   sw    $t3, 4($s0)
/* 0AE000 800AD400 8D8C2DF8 */  lw    $t4, %lo(D_80162DF8)($t4)
/* 0AE004 800AD404 24010001 */  li    $at, 1
/* 0AE008 800AD408 256DFFFF */  addiu $t5, $t3, -1
/* 0AE00C 800AD40C 15810002 */  bne   $t4, $at, .L800AD418
/* 0AE010 800AD410 00000000 */   nop
/* 0AE014 800AD414 AE0D0004 */  sw    $t5, 4($s0)
.L800AD418:
/* 0AE018 800AD418 8DEFC5EC */  lw    $t7, %lo(D_800DC5EC)($t7)
/* 0AE01C 800AD41C 240E00F0 */  li    $t6, 240
/* 0AE020 800AD420 3C19800E */  lui   $t9, %hi(D_800DC5F0) # $t9, 0x800e
/* 0AE024 800AD424 A5EE0030 */  sh    $t6, 0x30($t7)
/* 0AE028 800AD428 8F39C5F0 */  lw    $t9, %lo(D_800DC5F0)($t9)
/* 0AE02C 800AD42C 24180050 */  li    $t8, 80
/* 0AE030 800AD430 100002C0 */  b     .L800ADF34
/* 0AE034 800AD434 A7380030 */   sh    $t8, 0x30($t9)
glabel L800AD438
/* 0AE038 800AD438 0C02D148 */  jal   func_800B4520
/* 0AE03C 800AD43C 00000000 */   nop
/* 0AE040 800AD440 144002BC */  bnez  $v0, .L800ADF34
/* 0AE044 800AD444 3C03800E */   lui   $v1, %hi(gControllerOne) # $v1, 0x800e
/* 0AE048 800AD448 8C63C4BC */  lw    $v1, %lo(gControllerOne)($v1)
/* 0AE04C 800AD44C 94650006 */  lhu   $a1, 6($v1)
/* 0AE050 800AD450 9468000C */  lhu   $t0, 0xc($v1)
/* 0AE054 800AD454 00A82025 */  or    $a0, $a1, $t0
/* 0AE058 800AD458 30890800 */  andi  $t1, $a0, 0x800
/* 0AE05C 800AD45C 51200027 */  beql  $t1, $zero, .L800AD4FC
/* 0AE060 800AD460 30980400 */   andi  $t8, $a0, 0x400
/* 0AE064 800AD464 8E020004 */  lw    $v0, 4($s0)
/* 0AE068 800AD468 3C0B8016 */  lui   $t3, %hi(D_80162DF8) # $t3, 0x8016
/* 0AE06C 800AD46C 28410006 */  slti  $at, $v0, 6
/* 0AE070 800AD470 14200021 */  bnez  $at, .L800AD4F8
/* 0AE074 800AD474 244AFFFF */   addiu $t2, $v0, -1
/* 0AE078 800AD478 AE0A0004 */  sw    $t2, 4($s0)
/* 0AE07C 800AD47C 8D6B2DF8 */  lw    $t3, %lo(D_80162DF8)($t3)
/* 0AE080 800AD480 24010001 */  li    $at, 1
/* 0AE084 800AD484 3C044900 */  lui   $a0, (0x49008000 >> 16) # lui $a0, 0x4900
/* 0AE088 800AD488 15610004 */  bne   $t3, $at, .L800AD49C
/* 0AE08C 800AD48C 24010009 */   li    $at, 9
/* 0AE090 800AD490 15410002 */  bne   $t2, $at, .L800AD49C
/* 0AE094 800AD494 254CFFFF */   addiu $t4, $t2, -1
/* 0AE098 800AD498 AE0C0004 */  sw    $t4, 4($s0)
.L800AD49C:
/* 0AE09C 800AD49C 0C032384 */  jal   play_sound2
/* 0AE0A0 800AD4A0 34848000 */   ori   $a0, (0x49008000 & 0xFFFF) # ori $a0, $a0, 0x8000
/* 0AE0A4 800AD4A4 C6040024 */  lwc1  $f4, 0x24($s0)
/* 0AE0A8 800AD4A8 3C01800F */  lui   $at, %hi(D_800F27D0)
/* 0AE0AC 800AD4AC D42627D0 */  ldc1  $f6, %lo(D_800F27D0)($at)
/* 0AE0B0 800AD4B0 46002021 */  cvt.d.s $f0, $f4
/* 0AE0B4 800AD4B4 3C014010 */  li    $at, 0x40100000 # 2.250000
/* 0AE0B8 800AD4B8 4626003C */  c.lt.d $f0, $f6
/* 0AE0BC 800AD4BC 240DFFFF */  li    $t5, -1
/* 0AE0C0 800AD4C0 3C0E800E */  lui   $t6, %hi(gControllerOne) # $t6, 0x800e
/* 0AE0C4 800AD4C4 45020008 */  bc1fl .L800AD4E8
/* 0AE0C8 800AD4C8 AE0D0008 */   sw    $t5, 8($s0)
/* 0AE0CC 800AD4CC 44814800 */  mtc1  $at, $f9
/* 0AE0D0 800AD4D0 44804000 */  mtc1  $zero, $f8
/* 0AE0D4 800AD4D4 00000000 */  nop
/* 0AE0D8 800AD4D8 46280280 */  add.d $f10, $f0, $f8
/* 0AE0DC 800AD4DC 46205420 */  cvt.s.d $f16, $f10
/* 0AE0E0 800AD4E0 E6100024 */  swc1  $f16, 0x24($s0)
/* 0AE0E4 800AD4E4 AE0D0008 */  sw    $t5, 8($s0)
.L800AD4E8:
/* 0AE0E8 800AD4E8 8DCEC4BC */  lw    $t6, %lo(gControllerOne)($t6)
/* 0AE0EC 800AD4EC 95C50006 */  lhu   $a1, 6($t6)
/* 0AE0F0 800AD4F0 95CF000C */  lhu   $t7, 0xc($t6)
/* 0AE0F4 800AD4F4 00AF2025 */  or    $a0, $a1, $t7
.L800AD4F8:
/* 0AE0F8 800AD4F8 30980400 */  andi  $t8, $a0, 0x400
.L800AD4FC:
/* 0AE0FC 800AD4FC 53000033 */  beql  $t8, $zero, .L800AD5CC
/* 0AE100 800AD500 30AF9000 */   andi  $t7, $a1, 0x9000
/* 0AE104 800AD504 8E020004 */  lw    $v0, 4($s0)
/* 0AE108 800AD508 3C088016 */  lui   $t0, %hi(D_80162DF8) # $t0, 0x8016
/* 0AE10C 800AD50C 2841000A */  slti  $at, $v0, 0xa
/* 0AE110 800AD510 1020002D */  beqz  $at, .L800AD5C8
/* 0AE114 800AD514 24590001 */   addiu $t9, $v0, 1
/* 0AE118 800AD518 AE190004 */  sw    $t9, 4($s0)
/* 0AE11C 800AD51C 8D082DF8 */  lw    $t0, %lo(D_80162DF8)($t0)
/* 0AE120 800AD520 24010001 */  li    $at, 1
/* 0AE124 800AD524 3C0A8016 */  lui   $t2, %hi(D_80162DD4) # $t2, 0x8016
/* 0AE128 800AD528 15010005 */  bne   $t0, $at, .L800AD540
/* 0AE12C 800AD52C 3C044900 */   lui   $a0, (0x49008000 >> 16) # lui $a0, 0x4900
/* 0AE130 800AD530 24010009 */  li    $at, 9
/* 0AE134 800AD534 17210002 */  bne   $t9, $at, .L800AD540
/* 0AE138 800AD538 27290001 */   addiu $t1, $t9, 1
/* 0AE13C 800AD53C AE090004 */  sw    $t1, 4($s0)
.L800AD540:
/* 0AE140 800AD540 8E020004 */  lw    $v0, 4($s0)
/* 0AE144 800AD544 2401000A */  li    $at, 10
/* 0AE148 800AD548 1441000A */  bne   $v0, $at, .L800AD574
/* 0AE14C 800AD54C 00000000 */   nop
/* 0AE150 800AD550 954A2DD4 */  lhu   $t2, %lo(D_80162DD4)($t2)
/* 0AE154 800AD554 244BFFFE */  addiu $t3, $v0, -2
/* 0AE158 800AD558 3C0C800E */  lui   $t4, %hi(gControllerOne) # $t4, 0x800e
/* 0AE15C 800AD55C 11400005 */  beqz  $t2, .L800AD574
/* 0AE160 800AD560 00000000 */   nop
/* 0AE164 800AD564 AE0B0004 */  sw    $t3, 4($s0)
/* 0AE168 800AD568 8D8CC4BC */  lw    $t4, %lo(gControllerOne)($t4)
/* 0AE16C 800AD56C 10000016 */  b     .L800AD5C8
/* 0AE170 800AD570 95850006 */   lhu   $a1, 6($t4)
.L800AD574:
/* 0AE174 800AD574 0C032384 */  jal   play_sound2
/* 0AE178 800AD578 34848000 */   ori   $a0, (0x49008000 & 0xFFFF) # ori $a0, $a0, 0x8000
/* 0AE17C 800AD57C C6120024 */  lwc1  $f18, 0x24($s0)
/* 0AE180 800AD580 3C01800F */  lui   $at, %hi(D_800F27D8)
/* 0AE184 800AD584 D42427D8 */  ldc1  $f4, %lo(D_800F27D8)($at)
/* 0AE188 800AD588 46009021 */  cvt.d.s $f0, $f18
/* 0AE18C 800AD58C 3C014010 */  li    $at, 0x40100000 # 2.250000
/* 0AE190 800AD590 4624003C */  c.lt.d $f0, $f4
/* 0AE194 800AD594 240D0001 */  li    $t5, 1
/* 0AE198 800AD598 3C0E800E */  lui   $t6, %hi(gControllerOne) # $t6, 0x800e
/* 0AE19C 800AD59C 45020008 */  bc1fl .L800AD5C0
/* 0AE1A0 800AD5A0 AE0D0008 */   sw    $t5, 8($s0)
/* 0AE1A4 800AD5A4 44813800 */  mtc1  $at, $f7
/* 0AE1A8 800AD5A8 44803000 */  mtc1  $zero, $f6
/* 0AE1AC 800AD5AC 00000000 */  nop
/* 0AE1B0 800AD5B0 46260200 */  add.d $f8, $f0, $f6
/* 0AE1B4 800AD5B4 462042A0 */  cvt.s.d $f10, $f8
/* 0AE1B8 800AD5B8 E60A0024 */  swc1  $f10, 0x24($s0)
/* 0AE1BC 800AD5BC AE0D0008 */  sw    $t5, 8($s0)
.L800AD5C0:
/* 0AE1C0 800AD5C0 8DCEC4BC */  lw    $t6, %lo(gControllerOne)($t6)
/* 0AE1C4 800AD5C4 95C50006 */  lhu   $a1, 6($t6)
.L800AD5C8:
/* 0AE1C8 800AD5C8 30AF9000 */  andi  $t7, $a1, 0x9000
.L800AD5CC:
/* 0AE1CC 800AD5CC 11E00259 */  beqz  $t7, .L800ADF34
/* 0AE1D0 800AD5D0 3C18800F */   lui   $t8, %hi(gControllerPak1State) # $t8, 0x800f
/* 0AE1D4 800AD5D4 8E020004 */  lw    $v0, 4($s0)
/* 0AE1D8 800AD5D8 2401000A */  li    $at, 10
/* 0AE1DC 800AD5DC 3C048019 */  lui   $a0, %hi(gControllerPak1FileHandle) # $a0, 0x8019
/* 0AE1E0 800AD5E0 144100A7 */  bne   $v0, $at, .L800AD880
/* 0AE1E4 800AD5E4 2484E868 */   addiu $a0, %lo(gControllerPak1FileHandle) # addiu $a0, $a0, -0x1798
/* 0AE1E8 800AD5E8 C6100024 */  lwc1  $f16, 0x24($s0)
/* 0AE1EC 800AD5EC 3C01800F */  lui   $at, %hi(D_800F27E0)
/* 0AE1F0 800AD5F0 D43227E0 */  ldc1  $f18, %lo(D_800F27E0)($at)
/* 0AE1F4 800AD5F4 46008021 */  cvt.d.s $f0, $f16
/* 0AE1F8 800AD5F8 00001825 */  move  $v1, $zero
/* 0AE1FC 800AD5FC 4632003C */  c.lt.d $f0, $f18
/* 0AE200 800AD600 3C014010 */  li    $at, 0x40100000 # 2.250000
/* 0AE204 800AD604 3C05800F */  lui   $a1, %hi(gCompanyCode) # $a1, 0x800f
/* 0AE208 800AD608 3C06800F */  lui   $a2, %hi(gGameCode) # $a2, 0x800f
/* 0AE20C 800AD60C 45000007 */  bc1f  .L800AD62C
/* 0AE210 800AD610 3C07800F */   lui   $a3, %hi(gGameName) # $a3, 0x800f
/* 0AE214 800AD614 44812800 */  mtc1  $at, $f5
/* 0AE218 800AD618 44802000 */  mtc1  $zero, $f4
/* 0AE21C 800AD61C 00000000 */  nop
/* 0AE220 800AD620 46240180 */  add.d $f6, $f0, $f4
/* 0AE224 800AD624 46203220 */  cvt.s.d $f8, $f6
/* 0AE228 800AD628 E6080024 */  swc1  $f8, 0x24($s0)
.L800AD62C:
/* 0AE22C 800AD62C 831886F8 */  lb    $t8, %lo(gControllerPak1State)($t8)
/* 0AE230 800AD630 3C19800F */  lui   $t9, %hi(gExtCode) # $t9, 0x800f
/* 0AE234 800AD634 27392E74 */  addiu $t9, %lo(gExtCode) # addiu $t9, $t9, 0x2e74
/* 0AE238 800AD638 13000026 */  beqz  $t8, .L800AD6D4
/* 0AE23C 800AD63C 24E72E64 */   addiu $a3, %lo(gGameName) # addiu $a3, $a3, 0x2e64
/* 0AE240 800AD640 3C088019 */  lui   $t0, %hi(gControllerPak1FileNote) # $t0, 0x8019
/* 0AE244 800AD644 2508EB84 */  addiu $t0, %lo(gControllerPak1FileNote) # addiu $t0, $t0, -0x147c
/* 0AE248 800AD648 AFA80014 */  sw    $t0, 0x14($sp)
/* 0AE24C 800AD64C 94A586F0 */  lhu   $a1, %lo(gCompanyCode)($a1)
/* 0AE250 800AD650 8CC686F4 */  lw    $a2, %lo(gGameCode)($a2)
/* 0AE254 800AD654 AFB90010 */  sw    $t9, 0x10($sp)
/* 0AE258 800AD658 0C033E20 */  jal   osPfsFindFile
/* 0AE25C 800AD65C AFA30028 */   sw    $v1, 0x28($sp)
/* 0AE260 800AD660 10400008 */  beqz  $v0, .L800AD684
/* 0AE264 800AD664 8FA30028 */   lw    $v1, 0x28($sp)
/* 0AE268 800AD668 24010002 */  li    $at, 2
/* 0AE26C 800AD66C 10410017 */  beq   $v0, $at, .L800AD6CC
/* 0AE270 800AD670 24010005 */   li    $at, 5
/* 0AE274 800AD674 10410017 */  beq   $v0, $at, .L800AD6D4
/* 0AE278 800AD678 3C01800F */   lui   $at, %hi(gControllerPak1State) # $at, 0x800f
/* 0AE27C 800AD67C 10000015 */  b     .L800AD6D4
/* 0AE280 800AD680 A02086F8 */   sb    $zero, %lo(gControllerPak1State)($at)
.L800AD684:
/* 0AE284 800AD684 0C02D9C2 */  jal   func_800B6708
/* 0AE288 800AD688 00000000 */   nop
/* 0AE28C 800AD68C 3C098019 */  lui   $t1, %hi(gCupSelection) # $t1, 0x8019
/* 0AE290 800AD690 8129EE09 */  lb    $t1, %lo(gCupSelection)($t1)
/* 0AE294 800AD694 3C0B8019 */  lui   $t3, %hi(gCupCourseSelection) # $t3, 0x8019
/* 0AE298 800AD698 816BEE0B */  lb    $t3, %lo(gCupCourseSelection)($t3)
/* 0AE29C 800AD69C 00095080 */  sll   $t2, $t1, 2
/* 0AE2A0 800AD6A0 0C02D8D2 */  jal   func_800B6348
/* 0AE2A4 800AD6A4 014B2021 */   addu  $a0, $t2, $t3
/* 0AE2A8 800AD6A8 244C0011 */  addiu $t4, $v0, 0x11
/* 0AE2AC 800AD6AC AE0C0004 */  sw    $t4, 4($s0)
/* 0AE2B0 800AD6B0 24030001 */  li    $v1, 1
/* 0AE2B4 800AD6B4 3C044900 */  lui   $a0, (0x49008001 >> 16) # lui $a0, 0x4900
/* 0AE2B8 800AD6B8 34848001 */  ori   $a0, (0x49008001 & 0xFFFF) # ori $a0, $a0, 0x8001
/* 0AE2BC 800AD6BC 0C032384 */  jal   play_sound2
/* 0AE2C0 800AD6C0 AFA30028 */   sw    $v1, 0x28($sp)
/* 0AE2C4 800AD6C4 10000003 */  b     .L800AD6D4
/* 0AE2C8 800AD6C8 8FA30028 */   lw    $v1, 0x28($sp)
.L800AD6CC:
/* 0AE2CC 800AD6CC 3C01800F */  lui   $at, %hi(gControllerPak1State) # $at, 0x800f
/* 0AE2D0 800AD6D0 A02086F8 */  sb    $zero, %lo(gControllerPak1State)($at)
.L800AD6D4:
/* 0AE2D4 800AD6D4 14600217 */  bnez  $v1, .L800ADF34
/* 0AE2D8 800AD6D8 3C0D800F */   lui   $t5, %hi(gControllerPak1State) # $t5, 0x800f
/* 0AE2DC 800AD6DC 81AD86F8 */  lb    $t5, %lo(gControllerPak1State)($t5)
/* 0AE2E0 800AD6E0 15A00047 */  bnez  $t5, .L800AD800
/* 0AE2E4 800AD6E4 00000000 */   nop
/* 0AE2E8 800AD6E8 0C02D7CC */  jal   func_800B5F30
/* 0AE2EC 800AD6EC AFA30028 */   sw    $v1, 0x28($sp)
/* 0AE2F0 800AD6F0 244E0003 */  addiu $t6, $v0, 3
/* 0AE2F4 800AD6F4 2DC1000F */  sltiu $at, $t6, 0xf
/* 0AE2F8 800AD6F8 10200017 */  beqz  $at, .L800AD758
/* 0AE2FC 800AD6FC 8FA30028 */   lw    $v1, 0x28($sp)
/* 0AE300 800AD700 000E7080 */  sll   $t6, $t6, 2
/* 0AE304 800AD704 3C01800F */  lui   $at, %hi(jpt_800F27E8)
/* 0AE308 800AD708 002E0821 */  addu  $at, $at, $t6
/* 0AE30C 800AD70C 8C2E27E8 */  lw    $t6, %lo(jpt_800F27E8)($at)
/* 0AE310 800AD710 01C00008 */  jr    $t6
/* 0AE314 800AD714 00000000 */   nop
glabel L800AD718
/* 0AE318 800AD718 240F000B */  li    $t7, 11
/* 0AE31C 800AD71C AE0F0004 */  sw    $t7, 4($s0)
/* 0AE320 800AD720 10000010 */  b     .L800AD764
/* 0AE324 800AD724 24030001 */   li    $v1, 1
glabel L800AD728
/* 0AE328 800AD728 2418000C */  li    $t8, 12
/* 0AE32C 800AD72C AE180004 */  sw    $t8, 4($s0)
/* 0AE330 800AD730 1000000C */  b     .L800AD764
/* 0AE334 800AD734 24030001 */   li    $v1, 1
glabel L800AD738
/* 0AE338 800AD738 2419000B */  li    $t9, 11
/* 0AE33C 800AD73C AE190004 */  sw    $t9, 4($s0)
/* 0AE340 800AD740 10000008 */  b     .L800AD764
/* 0AE344 800AD744 24030001 */   li    $v1, 1
glabel L800AD748
/* 0AE348 800AD748 2408000C */  li    $t0, 12
/* 0AE34C 800AD74C AE080004 */  sw    $t0, 4($s0)
/* 0AE350 800AD750 10000004 */  b     .L800AD764
/* 0AE354 800AD754 24030001 */   li    $v1, 1
.L800AD758:
glabel L800AD758
/* 0AE358 800AD758 2409000C */  li    $t1, 12
/* 0AE35C 800AD75C 24030001 */  li    $v1, 1
/* 0AE360 800AD760 AE090004 */  sw    $t1, 4($s0)
.L800AD764:
glabel L800AD764
/* 0AE364 800AD764 10600006 */  beqz  $v1, .L800AD780
/* 0AE368 800AD768 3C048019 */   lui   $a0, %hi(gControllerPak1FileHandle)
/* 0AE36C 800AD76C 3C044900 */  lui   $a0, (0x4900FF07 >> 16) # $a0, 0x4900
/* 0AE370 800AD770 0C032384 */  jal   play_sound2
/* 0AE374 800AD774 3484FF07 */   ori   $a0, (0x4900FF07 & 0xFFFF) # ori $a0, $a0, 0xff07
/* 0AE378 800AD778 100001EF */  b     .L800ADF38
/* 0AE37C 800AD77C 8FBF0024 */   lw    $ra, 0x24($sp)
.L800AD780:
/* 0AE380 800AD780 3C0A800F */  lui   $t2, %hi(gExtCode) # $t2, 0x800f
/* 0AE384 800AD784 3C0B8019 */  lui   $t3, %hi(gControllerPak1FileNote) # $t3, 0x8019
/* 0AE388 800AD788 256BEB84 */  addiu $t3, %lo(gControllerPak1FileNote) # addiu $t3, $t3, -0x147c
/* 0AE38C 800AD78C 254A2E74 */  addiu $t2, %lo(gExtCode) # addiu $t2, $t2, 0x2e74
/* 0AE390 800AD790 3C05800F */  lui   $a1, %hi(gCompanyCode) # $a1, 0x800f
/* 0AE394 800AD794 3C06800F */  lui   $a2, %hi(gGameCode) # $a2, 0x800f
/* 0AE398 800AD798 3C07800F */  lui   $a3, %hi(gGameName) # $a3, 0x800f
/* 0AE39C 800AD79C 24E72E64 */  addiu $a3, %lo(gGameName) # addiu $a3, $a3, 0x2e64
/* 0AE3A0 800AD7A0 8CC686F4 */  lw    $a2, %lo(gGameCode)($a2)
/* 0AE3A4 800AD7A4 94A586F0 */  lhu   $a1, %lo(gCompanyCode)($a1)
/* 0AE3A8 800AD7A8 AFAA0010 */  sw    $t2, 0x10($sp)
/* 0AE3AC 800AD7AC AFAB0014 */  sw    $t3, 0x14($sp)
/* 0AE3B0 800AD7B0 0C033E20 */  jal   osPfsFindFile
/* 0AE3B4 800AD7B4 2484E868 */   addiu $a0, %lo(gControllerPak1FileHandle) # addiu $a0, $a0, -0x1798
/* 0AE3B8 800AD7B8 14400011 */  bnez  $v0, .L800AD800
/* 0AE3BC 800AD7BC 00000000 */   nop
/* 0AE3C0 800AD7C0 0C02D9C2 */  jal   func_800B6708
/* 0AE3C4 800AD7C4 00000000 */   nop
/* 0AE3C8 800AD7C8 3C0C8019 */  lui   $t4, %hi(gCupSelection) # $t4, 0x8019
/* 0AE3CC 800AD7CC 818CEE09 */  lb    $t4, %lo(gCupSelection)($t4)
/* 0AE3D0 800AD7D0 3C0E8019 */  lui   $t6, %hi(gCupCourseSelection) # $t6, 0x8019
/* 0AE3D4 800AD7D4 81CEEE0B */  lb    $t6, %lo(gCupCourseSelection)($t6)
/* 0AE3D8 800AD7D8 000C6880 */  sll   $t5, $t4, 2
/* 0AE3DC 800AD7DC 0C02D8D2 */  jal   func_800B6348
/* 0AE3E0 800AD7E0 01AE2021 */   addu  $a0, $t5, $t6
/* 0AE3E4 800AD7E4 244F0011 */  addiu $t7, $v0, 0x11
/* 0AE3E8 800AD7E8 3C044900 */  lui   $a0, (0x49008001 >> 16) # lui $a0, 0x4900
/* 0AE3EC 800AD7EC AE0F0004 */  sw    $t7, 4($s0)
/* 0AE3F0 800AD7F0 0C032384 */  jal   play_sound2
/* 0AE3F4 800AD7F4 34848001 */   ori   $a0, (0x49008001 & 0xFFFF) # ori $a0, $a0, 0x8001
/* 0AE3F8 800AD7F8 100001CF */  b     .L800ADF38
/* 0AE3FC 800AD7FC 8FBF0024 */   lw    $ra, 0x24($sp)
.L800AD800:
/* 0AE400 800AD800 3C188019 */  lui   $t8, %hi(gControllerPak1MaxWriteableFiles) # $t8, 0x8019
/* 0AE404 800AD804 3C198019 */  lui   $t9, %hi(gControllerPak1NumFilesUsed) # $t9, 0x8019
/* 0AE408 800AD808 8F39EB78 */  lw    $t9, %lo(gControllerPak1NumFilesUsed)($t9)
/* 0AE40C 800AD80C 8F18EB7C */  lw    $t8, %lo(gControllerPak1MaxWriteableFiles)($t8)
/* 0AE410 800AD810 2408000E */  li    $t0, 14
/* 0AE414 800AD814 3C044900 */  lui   $a0, (0x4900FF07 >> 16) # lui $a0, 0x4900
/* 0AE418 800AD818 0319082A */  slt   $at, $t8, $t9
/* 0AE41C 800AD81C 14200006 */  bnez  $at, .L800AD838
/* 0AE420 800AD820 3C098019 */   lui   $t1, %hi(gControllerPak1NumPagesFree) # $t1, 0x8019
/* 0AE424 800AD824 AE080004 */  sw    $t0, 4($s0)
/* 0AE428 800AD828 0C032384 */  jal   play_sound2
/* 0AE42C 800AD82C 3484FF07 */   ori   $a0, (0x4900FF07 & 0xFFFF) # ori $a0, $a0, 0xff07
/* 0AE430 800AD830 100001C1 */  b     .L800ADF38
/* 0AE434 800AD834 8FBF0024 */   lw    $ra, 0x24($sp)
.L800AD838:
/* 0AE438 800AD838 8D29EB80 */  lw    $t1, %lo(gControllerPak1NumPagesFree)($t1)
/* 0AE43C 800AD83C 3C044900 */  lui   $a0, (0x4900FF07 >> 16) # lui $a0, 0x4900
/* 0AE440 800AD840 240B000E */  li    $t3, 14
/* 0AE444 800AD844 29210079 */  slti  $at, $t1, 0x79
/* 0AE448 800AD848 14200009 */  bnez  $at, .L800AD870
/* 0AE44C 800AD84C 3484FF07 */   ori   $a0, (0x4900FF07 & 0xFFFF) # ori $a0, $a0, 0xff07
/* 0AE450 800AD850 240A0013 */  li    $t2, 19
/* 0AE454 800AD854 3C044900 */  lui   $a0, (0x49008001 >> 16) # lui $a0, 0x4900
/* 0AE458 800AD858 AE0A0004 */  sw    $t2, 4($s0)
/* 0AE45C 800AD85C AE00001C */  sw    $zero, 0x1c($s0)
/* 0AE460 800AD860 0C032384 */  jal   play_sound2
/* 0AE464 800AD864 34848001 */   ori   $a0, (0x49008001 & 0xFFFF) # ori $a0, $a0, 0x8001
/* 0AE468 800AD868 100001B3 */  b     .L800ADF38
/* 0AE46C 800AD86C 8FBF0024 */   lw    $ra, 0x24($sp)
.L800AD870:
/* 0AE470 800AD870 0C032384 */  jal   play_sound2
/* 0AE474 800AD874 AE0B0004 */   sw    $t3, 4($s0)
/* 0AE478 800AD878 100001AF */  b     .L800ADF38
/* 0AE47C 800AD87C 8FBF0024 */   lw    $ra, 0x24($sp)
.L800AD880:
/* 0AE480 800AD880 AE02001C */  sw    $v0, 0x1c($s0)
/* 0AE484 800AD884 3C018019 */  lui   $at, %hi(D_8018EDF5) # $at, 0x8019
/* 0AE488 800AD888 A022EDF5 */  sb    $v0, %lo(D_8018EDF5)($at)
/* 0AE48C 800AD88C 8E0D0010 */  lw    $t5, 0x10($s0)
/* 0AE490 800AD890 240C001E */  li    $t4, 30
/* 0AE494 800AD894 3C044900 */  lui   $a0, (0x49008015 >> 16) # lui $a0, 0x4900
/* 0AE498 800AD898 AE0C0004 */  sw    $t4, 4($s0)
/* 0AE49C 800AD89C 34848015 */  ori   $a0, (0x49008015 & 0xFFFF) # ori $a0, $a0, 0x8015
/* 0AE4A0 800AD8A0 0C032384 */  jal   play_sound2
/* 0AE4A4 800AD8A4 AE0D0020 */   sw    $t5, 0x20($s0)
/* 0AE4A8 800AD8A8 C60A0024 */  lwc1  $f10, 0x24($s0)
/* 0AE4AC 800AD8AC 3C01800F */  lui   $at, %hi(D_800F2828)
/* 0AE4B0 800AD8B0 D4302828 */  ldc1  $f16, %lo(D_800F2828)($at)
/* 0AE4B4 800AD8B4 46005021 */  cvt.d.s $f0, $f10
/* 0AE4B8 800AD8B8 3C014010 */  li    $at, 0x40100000 # 2.250000
/* 0AE4BC 800AD8BC 4630003C */  c.lt.d $f0, $f16
/* 0AE4C0 800AD8C0 00000000 */  nop
/* 0AE4C4 800AD8C4 4502019C */  bc1fl .L800ADF38
/* 0AE4C8 800AD8C8 8FBF0024 */   lw    $ra, 0x24($sp)
/* 0AE4CC 800AD8CC 44819800 */  mtc1  $at, $f19
/* 0AE4D0 800AD8D0 44809000 */  mtc1  $zero, $f18
/* 0AE4D4 800AD8D4 00000000 */  nop
/* 0AE4D8 800AD8D8 46320100 */  add.d $f4, $f0, $f18
/* 0AE4DC 800AD8DC 462021A0 */  cvt.s.d $f6, $f4
/* 0AE4E0 800AD8E0 10000194 */  b     .L800ADF34
/* 0AE4E4 800AD8E4 E6060024 */   swc1  $f6, 0x24($s0)
glabel L800AD8E8
/* 0AE4E8 800AD8E8 3C0E800E */  lui   $t6, %hi(gControllerOne) # $t6, 0x800e
/* 0AE4EC 800AD8EC 8DCEC4BC */  lw    $t6, %lo(gControllerOne)($t6)
/* 0AE4F0 800AD8F0 3C044900 */  lui   $a0, (0x49008002 >> 16) # lui $a0, 0x4900
/* 0AE4F4 800AD8F4 2419000A */  li    $t9, 10
/* 0AE4F8 800AD8F8 95CF0006 */  lhu   $t7, 6($t6)
/* 0AE4FC 800AD8FC 34848002 */  ori   $a0, (0x49008002 & 0xFFFF) # ori $a0, $a0, 0x8002
/* 0AE500 800AD900 31F8D000 */  andi  $t8, $t7, 0xd000
/* 0AE504 800AD904 5300018C */  beql  $t8, $zero, .L800ADF38
/* 0AE508 800AD908 8FBF0024 */   lw    $ra, 0x24($sp)
/* 0AE50C 800AD90C 0C032384 */  jal   play_sound2
/* 0AE510 800AD910 AE190004 */   sw    $t9, 4($s0)
/* 0AE514 800AD914 C6080024 */  lwc1  $f8, 0x24($s0)
/* 0AE518 800AD918 3C01800F */  lui   $at, %hi(D_800F2830)
/* 0AE51C 800AD91C D42A2830 */  ldc1  $f10, %lo(D_800F2830)($at)
/* 0AE520 800AD920 46004021 */  cvt.d.s $f0, $f8
/* 0AE524 800AD924 3C014010 */  li    $at, 0x40100000 # 2.250000
/* 0AE528 800AD928 462A003C */  c.lt.d $f0, $f10
/* 0AE52C 800AD92C 00000000 */  nop
/* 0AE530 800AD930 45020181 */  bc1fl .L800ADF38
/* 0AE534 800AD934 8FBF0024 */   lw    $ra, 0x24($sp)
/* 0AE538 800AD938 44818800 */  mtc1  $at, $f17
/* 0AE53C 800AD93C 44808000 */  mtc1  $zero, $f16
/* 0AE540 800AD940 00000000 */  nop
/* 0AE544 800AD944 46300480 */  add.d $f18, $f0, $f16
/* 0AE548 800AD948 46209120 */  cvt.s.d $f4, $f18
/* 0AE54C 800AD94C 10000179 */  b     .L800ADF34
/* 0AE550 800AD950 E6040024 */   swc1  $f4, 0x24($s0)
glabel L800AD954
/* 0AE554 800AD954 2448FFEF */  addiu $t0, $v0, -0x11
/* 0AE558 800AD958 AE080020 */  sw    $t0, 0x20($s0)
/* 0AE55C 800AD95C 3C098019 */  lui   $t1, %hi(gCupSelection) # $t1, 0x8019
/* 0AE560 800AD960 8129EE09 */  lb    $t1, %lo(gCupSelection)($t1)
/* 0AE564 800AD964 3C0B8019 */  lui   $t3, %hi(gCupCourseSelection) # $t3, 0x8019
/* 0AE568 800AD968 816BEE0B */  lb    $t3, %lo(gCupCourseSelection)($t3)
/* 0AE56C 800AD96C 00095080 */  sll   $t2, $t1, 2
/* 0AE570 800AD970 0C02D8E7 */  jal   func_800B639C
/* 0AE574 800AD974 014B2021 */   addu  $a0, $t2, $t3
/* 0AE578 800AD978 8E0C0020 */  lw    $t4, 0x20($s0)
/* 0AE57C 800AD97C 3C03800E */  lui   $v1, %hi(gControllerOne) # $v1, 0x800e
/* 0AE580 800AD980 104C0040 */  beq   $v0, $t4, .L800ADA84
/* 0AE584 800AD984 00000000 */   nop
/* 0AE588 800AD988 8C63C4BC */  lw    $v1, %lo(gControllerOne)($v1)
/* 0AE58C 800AD98C 946D0006 */  lhu   $t5, 6($v1)
/* 0AE590 800AD990 946E000C */  lhu   $t6, 0xc($v1)
/* 0AE594 800AD994 01AE2025 */  or    $a0, $t5, $t6
/* 0AE598 800AD998 308F0800 */  andi  $t7, $a0, 0x800
/* 0AE59C 800AD99C 51E0001F */  beql  $t7, $zero, .L800ADA1C
/* 0AE5A0 800AD9A0 308B0400 */   andi  $t3, $a0, 0x400
/* 0AE5A4 800AD9A4 8E020004 */  lw    $v0, 4($s0)
/* 0AE5A8 800AD9A8 28410012 */  slti  $at, $v0, 0x12
/* 0AE5AC 800AD9AC 1420001A */  bnez  $at, .L800ADA18
/* 0AE5B0 800AD9B0 2458FFFF */   addiu $t8, $v0, -1
/* 0AE5B4 800AD9B4 3C044900 */  lui   $a0, (0x49008000 >> 16) # lui $a0, 0x4900
/* 0AE5B8 800AD9B8 AE180004 */  sw    $t8, 4($s0)
/* 0AE5BC 800AD9BC 0C032384 */  jal   play_sound2
/* 0AE5C0 800AD9C0 34848000 */   ori   $a0, (0x49008000 & 0xFFFF) # ori $a0, $a0, 0x8000
/* 0AE5C4 800AD9C4 C6060024 */  lwc1  $f6, 0x24($s0)
/* 0AE5C8 800AD9C8 3C01800F */  lui   $at, %hi(D_800F2838)
/* 0AE5CC 800AD9CC D4282838 */  ldc1  $f8, %lo(D_800F2838)($at)
/* 0AE5D0 800AD9D0 46003021 */  cvt.d.s $f0, $f6
/* 0AE5D4 800AD9D4 3C014010 */  li    $at, 0x40100000 # 2.250000
/* 0AE5D8 800AD9D8 4628003C */  c.lt.d $f0, $f8
/* 0AE5DC 800AD9DC 2419FFFF */  li    $t9, -1
/* 0AE5E0 800AD9E0 3C08800E */  lui   $t0, %hi(gControllerOne) # $t0, 0x800e
/* 0AE5E4 800AD9E4 45020008 */  bc1fl .L800ADA08
/* 0AE5E8 800AD9E8 AE190008 */   sw    $t9, 8($s0)
/* 0AE5EC 800AD9EC 44815800 */  mtc1  $at, $f11
/* 0AE5F0 800AD9F0 44805000 */  mtc1  $zero, $f10
/* 0AE5F4 800AD9F4 00000000 */  nop
/* 0AE5F8 800AD9F8 462A0400 */  add.d $f16, $f0, $f10
/* 0AE5FC 800AD9FC 462084A0 */  cvt.s.d $f18, $f16
/* 0AE600 800ADA00 E6120024 */  swc1  $f18, 0x24($s0)
/* 0AE604 800ADA04 AE190008 */  sw    $t9, 8($s0)
.L800ADA08:
/* 0AE608 800ADA08 8D08C4BC */  lw    $t0, %lo(gControllerOne)($t0)
/* 0AE60C 800ADA0C 95090006 */  lhu   $t1, 6($t0)
/* 0AE610 800ADA10 950A000C */  lhu   $t2, 0xc($t0)
/* 0AE614 800ADA14 012A2025 */  or    $a0, $t1, $t2
.L800ADA18:
/* 0AE618 800ADA18 308B0400 */  andi  $t3, $a0, 0x400
.L800ADA1C:
/* 0AE61C 800ADA1C 11600019 */  beqz  $t3, .L800ADA84
/* 0AE620 800ADA20 00000000 */   nop
/* 0AE624 800ADA24 8E020004 */  lw    $v0, 4($s0)
/* 0AE628 800ADA28 3C044900 */  lui   $a0, (0x49008000 >> 16) # lui $a0, 0x4900
/* 0AE62C 800ADA2C 34848000 */  ori   $a0, (0x49008000 & 0xFFFF) # ori $a0, $a0, 0x8000
/* 0AE630 800ADA30 28410012 */  slti  $at, $v0, 0x12
/* 0AE634 800ADA34 10200013 */  beqz  $at, .L800ADA84
/* 0AE638 800ADA38 244C0001 */   addiu $t4, $v0, 1
/* 0AE63C 800ADA3C 0C032384 */  jal   play_sound2
/* 0AE640 800ADA40 AE0C0004 */   sw    $t4, 4($s0)
/* 0AE644 800ADA44 C6040024 */  lwc1  $f4, 0x24($s0)
/* 0AE648 800ADA48 3C01800F */  lui   $at, %hi(D_800F2840)
/* 0AE64C 800ADA4C D4262840 */  ldc1  $f6, %lo(D_800F2840)($at)
/* 0AE650 800ADA50 46002021 */  cvt.d.s $f0, $f4
/* 0AE654 800ADA54 3C014010 */  li    $at, 0x40100000 # 2.250000
/* 0AE658 800ADA58 4626003C */  c.lt.d $f0, $f6
/* 0AE65C 800ADA5C 240D0001 */  li    $t5, 1
/* 0AE660 800ADA60 45020008 */  bc1fl .L800ADA84
/* 0AE664 800ADA64 AE0D0008 */   sw    $t5, 8($s0)
/* 0AE668 800ADA68 44814800 */  mtc1  $at, $f9
/* 0AE66C 800ADA6C 44804000 */  mtc1  $zero, $f8
/* 0AE670 800ADA70 00000000 */  nop
/* 0AE674 800ADA74 46280280 */  add.d $f10, $f0, $f8
/* 0AE678 800ADA78 46205420 */  cvt.s.d $f16, $f10
/* 0AE67C 800ADA7C E6100024 */  swc1  $f16, 0x24($s0)
/* 0AE680 800ADA80 AE0D0008 */  sw    $t5, 8($s0)
.L800ADA84:
/* 0AE684 800ADA84 3C0E800E */  lui   $t6, %hi(gControllerOne) # $t6, 0x800e
/* 0AE688 800ADA88 8DCEC4BC */  lw    $t6, %lo(gControllerOne)($t6)
/* 0AE68C 800ADA8C 3C044900 */  lui   $a0, (0x49008002 >> 16) # lui $a0, 0x4900
/* 0AE690 800ADA90 2418000A */  li    $t8, 10
/* 0AE694 800ADA94 95C50006 */  lhu   $a1, 6($t6)
/* 0AE698 800ADA98 34848002 */  ori   $a0, (0x49008002 & 0xFFFF) # ori $a0, $a0, 0x8002
/* 0AE69C 800ADA9C 30AF4000 */  andi  $t7, $a1, 0x4000
/* 0AE6A0 800ADAA0 11E00005 */  beqz  $t7, .L800ADAB8
/* 0AE6A4 800ADAA4 30B99000 */   andi  $t9, $a1, 0x9000
/* 0AE6A8 800ADAA8 0C032384 */  jal   play_sound2
/* 0AE6AC 800ADAAC AE180004 */   sw    $t8, 4($s0)
/* 0AE6B0 800ADAB0 10000121 */  b     .L800ADF38
/* 0AE6B4 800ADAB4 8FBF0024 */   lw    $ra, 0x24($sp)
.L800ADAB8:
/* 0AE6B8 800ADAB8 5320011F */  beql  $t9, $zero, .L800ADF38
/* 0AE6BC 800ADABC 8FBF0024 */   lw    $ra, 0x24($sp)
/* 0AE6C0 800ADAC0 8E040020 */  lw    $a0, 0x20($s0)
/* 0AE6C4 800ADAC4 3C098019 */  lui   $t1, %hi(D_8018EE10) # $t1, 0x8019
/* 0AE6C8 800ADAC8 2529EE10 */  addiu $t1, %lo(D_8018EE10) # addiu $t1, $t1, -0x11f0
/* 0AE6CC 800ADACC 000441C0 */  sll   $t0, $a0, 7
/* 0AE6D0 800ADAD0 01091021 */  addu  $v0, $t0, $t1
/* 0AE6D4 800ADAD4 904A0004 */  lbu   $t2, 4($v0)
/* 0AE6D8 800ADAD8 240B0019 */  li    $t3, 25
/* 0AE6DC 800ADADC 15400004 */  bnez  $t2, .L800ADAF0
/* 0AE6E0 800ADAE0 00000000 */   nop
/* 0AE6E4 800ADAE4 AE0B0004 */  sw    $t3, 4($s0)
/* 0AE6E8 800ADAE8 10000009 */  b     .L800ADB10
/* 0AE6EC 800ADAEC AE00001C */   sw    $zero, 0x1c($s0)
.L800ADAF0:
/* 0AE6F0 800ADAF0 0C02D8FC */  jal   func_800B63F0
/* 0AE6F4 800ADAF4 00000000 */   nop
/* 0AE6F8 800ADAF8 14400004 */  bnez  $v0, .L800ADB0C
/* 0AE6FC 800ADAFC 240D0014 */   li    $t5, 20
/* 0AE700 800ADB00 240C0010 */  li    $t4, 16
/* 0AE704 800ADB04 10000002 */  b     .L800ADB10
/* 0AE708 800ADB08 AE0C0004 */   sw    $t4, 4($s0)
.L800ADB0C:
/* 0AE70C 800ADB0C AE0D0004 */  sw    $t5, 4($s0)
.L800ADB10:
/* 0AE710 800ADB10 3C044900 */  lui   $a0, (0x49008001 >> 16) # lui $a0, 0x4900
/* 0AE714 800ADB14 0C032384 */  jal   play_sound2
/* 0AE718 800ADB18 34848001 */   ori   $a0, (0x49008001 & 0xFFFF) # ori $a0, $a0, 0x8001
/* 0AE71C 800ADB1C C6120024 */  lwc1  $f18, 0x24($s0)
/* 0AE720 800ADB20 3C01800F */  lui   $at, %hi(D_800F2848)
/* 0AE724 800ADB24 D4242848 */  ldc1  $f4, %lo(D_800F2848)($at)
/* 0AE728 800ADB28 46009021 */  cvt.d.s $f0, $f18
/* 0AE72C 800ADB2C 3C014010 */  li    $at, 0x40100000 # 2.250000
/* 0AE730 800ADB30 4624003C */  c.lt.d $f0, $f4
/* 0AE734 800ADB34 00000000 */  nop
/* 0AE738 800ADB38 450200FF */  bc1fl .L800ADF38
/* 0AE73C 800ADB3C 8FBF0024 */   lw    $ra, 0x24($sp)
/* 0AE740 800ADB40 44813800 */  mtc1  $at, $f7
/* 0AE744 800ADB44 44803000 */  mtc1  $zero, $f6
/* 0AE748 800ADB48 00000000 */  nop
/* 0AE74C 800ADB4C 46260200 */  add.d $f8, $f0, $f6
/* 0AE750 800ADB50 462042A0 */  cvt.s.d $f10, $f8
/* 0AE754 800ADB54 100000F7 */  b     .L800ADF34
/* 0AE758 800ADB58 E60A0024 */   swc1  $f10, 0x24($s0)
glabel L800ADB5C
/* 0AE75C 800ADB5C 8E0E001C */  lw    $t6, 0x1c($s0)
/* 0AE760 800ADB60 24010001 */  li    $at, 1
/* 0AE764 800ADB64 55C10008 */  bnel  $t6, $at, .L800ADB88
/* 0AE768 800ADB68 8E18001C */   lw    $t8, 0x1c($s0)
/* 0AE76C 800ADB6C 0C02DA9A */  jal   func_800B6A68
/* 0AE770 800ADB70 00000000 */   nop
/* 0AE774 800ADB74 10400003 */  beqz  $v0, .L800ADB84
/* 0AE778 800ADB78 240F000F */   li    $t7, 15
/* 0AE77C 800ADB7C 100000ED */  b     .L800ADF34
/* 0AE780 800ADB80 AE0F0004 */   sw    $t7, 4($s0)
.L800ADB84:
/* 0AE784 800ADB84 8E18001C */  lw    $t8, 0x1c($s0)
.L800ADB88:
/* 0AE788 800ADB88 24090011 */  li    $t1, 17
/* 0AE78C 800ADB8C 27190001 */  addiu $t9, $t8, 1
/* 0AE790 800ADB90 2B210002 */  slti  $at, $t9, 2
/* 0AE794 800ADB94 142000E7 */  bnez  $at, .L800ADF34
/* 0AE798 800ADB98 AE19001C */   sw    $t9, 0x1c($s0)
/* 0AE79C 800ADB9C 100000E5 */  b     .L800ADF34
/* 0AE7A0 800ADBA0 AE090004 */   sw    $t1, 4($s0)
glabel L800ADBA4
/* 0AE7A4 800ADBA4 3C03800E */  lui   $v1, %hi(gControllerOne) # $v1, 0x800e
/* 0AE7A8 800ADBA8 8C63C4BC */  lw    $v1, %lo(gControllerOne)($v1)
/* 0AE7AC 800ADBAC 28410015 */  slti  $at, $v0, 0x15
/* 0AE7B0 800ADBB0 94650006 */  lhu   $a1, 6($v1)
/* 0AE7B4 800ADBB4 946A000C */  lhu   $t2, 0xc($v1)
/* 0AE7B8 800ADBB8 00AA2025 */  or    $a0, $a1, $t2
/* 0AE7BC 800ADBBC 308B0800 */  andi  $t3, $a0, 0x800
/* 0AE7C0 800ADBC0 5160001D */  beql  $t3, $zero, .L800ADC38
/* 0AE7C4 800ADBC4 30980400 */   andi  $t8, $a0, 0x400
/* 0AE7C8 800ADBC8 1420001A */  bnez  $at, .L800ADC34
/* 0AE7CC 800ADBCC 244CFFFF */   addiu $t4, $v0, -1
/* 0AE7D0 800ADBD0 3C044900 */  lui   $a0, (0x49008000 >> 16) # lui $a0, 0x4900
/* 0AE7D4 800ADBD4 AE0C0004 */  sw    $t4, 4($s0)
/* 0AE7D8 800ADBD8 0C032384 */  jal   play_sound2
/* 0AE7DC 800ADBDC 34848000 */   ori   $a0, (0x49008000 & 0xFFFF) # ori $a0, $a0, 0x8000
/* 0AE7E0 800ADBE0 C6100024 */  lwc1  $f16, 0x24($s0)
/* 0AE7E4 800ADBE4 3C01800F */  lui   $at, %hi(D_800F2850)
/* 0AE7E8 800ADBE8 D4322850 */  ldc1  $f18, %lo(D_800F2850)($at)
/* 0AE7EC 800ADBEC 46008021 */  cvt.d.s $f0, $f16
/* 0AE7F0 800ADBF0 3C014010 */  li    $at, 0x40100000 # 2.250000
/* 0AE7F4 800ADBF4 4632003C */  c.lt.d $f0, $f18
/* 0AE7F8 800ADBF8 240DFFFF */  li    $t5, -1
/* 0AE7FC 800ADBFC 3C0E800E */  lui   $t6, %hi(gControllerOne) # $t6, 0x800e
/* 0AE800 800ADC00 45020008 */  bc1fl .L800ADC24
/* 0AE804 800ADC04 AE0D0008 */   sw    $t5, 8($s0)
/* 0AE808 800ADC08 44812800 */  mtc1  $at, $f5
/* 0AE80C 800ADC0C 44802000 */  mtc1  $zero, $f4
/* 0AE810 800ADC10 00000000 */  nop
/* 0AE814 800ADC14 46240180 */  add.d $f6, $f0, $f4
/* 0AE818 800ADC18 46203220 */  cvt.s.d $f8, $f6
/* 0AE81C 800ADC1C E6080024 */  swc1  $f8, 0x24($s0)
/* 0AE820 800ADC20 AE0D0008 */  sw    $t5, 8($s0)
.L800ADC24:
/* 0AE824 800ADC24 8DCEC4BC */  lw    $t6, %lo(gControllerOne)($t6)
/* 0AE828 800ADC28 95C50006 */  lhu   $a1, 6($t6)
/* 0AE82C 800ADC2C 95CF000C */  lhu   $t7, 0xc($t6)
/* 0AE830 800ADC30 00AF2025 */  or    $a0, $a1, $t7
.L800ADC34:
/* 0AE834 800ADC34 30980400 */  andi  $t8, $a0, 0x400
.L800ADC38:
/* 0AE838 800ADC38 5300001D */  beql  $t8, $zero, .L800ADCB0
/* 0AE83C 800ADC3C 30AA4000 */   andi  $t2, $a1, 0x4000
/* 0AE840 800ADC40 8E020004 */  lw    $v0, 4($s0)
/* 0AE844 800ADC44 3C044900 */  lui   $a0, (0x49008000 >> 16) # lui $a0, 0x4900
/* 0AE848 800ADC48 34848000 */  ori   $a0, (0x49008000 & 0xFFFF) # ori $a0, $a0, 0x8000
/* 0AE84C 800ADC4C 28410015 */  slti  $at, $v0, 0x15
/* 0AE850 800ADC50 10200016 */  beqz  $at, .L800ADCAC
/* 0AE854 800ADC54 24590001 */   addiu $t9, $v0, 1
/* 0AE858 800ADC58 0C032384 */  jal   play_sound2
/* 0AE85C 800ADC5C AE190004 */   sw    $t9, 4($s0)
/* 0AE860 800ADC60 C60A0024 */  lwc1  $f10, 0x24($s0)
/* 0AE864 800ADC64 3C01800F */  lui   $at, %hi(D_800F2858)
/* 0AE868 800ADC68 D4302858 */  ldc1  $f16, %lo(D_800F2858)($at)
/* 0AE86C 800ADC6C 46005021 */  cvt.d.s $f0, $f10
/* 0AE870 800ADC70 3C014010 */  li    $at, 0x40100000 # 2.250000
/* 0AE874 800ADC74 4630003C */  c.lt.d $f0, $f16
/* 0AE878 800ADC78 24080001 */  li    $t0, 1
/* 0AE87C 800ADC7C 3C09800E */  lui   $t1, %hi(gControllerOne) # $t1, 0x800e
/* 0AE880 800ADC80 45020008 */  bc1fl .L800ADCA4
/* 0AE884 800ADC84 AE080008 */   sw    $t0, 8($s0)
/* 0AE888 800ADC88 44819800 */  mtc1  $at, $f19
/* 0AE88C 800ADC8C 44809000 */  mtc1  $zero, $f18
/* 0AE890 800ADC90 00000000 */  nop
/* 0AE894 800ADC94 46320100 */  add.d $f4, $f0, $f18
/* 0AE898 800ADC98 462021A0 */  cvt.s.d $f6, $f4
/* 0AE89C 800ADC9C E6060024 */  swc1  $f6, 0x24($s0)
/* 0AE8A0 800ADCA0 AE080008 */  sw    $t0, 8($s0)
.L800ADCA4:
/* 0AE8A4 800ADCA4 8D29C4BC */  lw    $t1, %lo(gControllerOne)($t1)
/* 0AE8A8 800ADCA8 95250006 */  lhu   $a1, 6($t1)
.L800ADCAC:
/* 0AE8AC 800ADCAC 30AA4000 */  andi  $t2, $a1, 0x4000
.L800ADCB0:
/* 0AE8B0 800ADCB0 11400009 */  beqz  $t2, .L800ADCD8
/* 0AE8B4 800ADCB4 30AD9000 */   andi  $t5, $a1, 0x9000
/* 0AE8B8 800ADCB8 8E0B0020 */  lw    $t3, 0x20($s0)
/* 0AE8BC 800ADCBC 3C044900 */  lui   $a0, (0x49008002 >> 16) # lui $a0, 0x4900
/* 0AE8C0 800ADCC0 34848002 */  ori   $a0, (0x49008002 & 0xFFFF) # ori $a0, $a0, 0x8002
/* 0AE8C4 800ADCC4 256C0011 */  addiu $t4, $t3, 0x11
/* 0AE8C8 800ADCC8 0C032384 */  jal   play_sound2
/* 0AE8CC 800ADCCC AE0C0004 */   sw    $t4, 4($s0)
/* 0AE8D0 800ADCD0 10000099 */  b     .L800ADF38
/* 0AE8D4 800ADCD4 8FBF0024 */   lw    $ra, 0x24($sp)
.L800ADCD8:
/* 0AE8D8 800ADCD8 51A00097 */  beql  $t5, $zero, .L800ADF38
/* 0AE8DC 800ADCDC 8FBF0024 */   lw    $ra, 0x24($sp)
/* 0AE8E0 800ADCE0 8E0E0004 */  lw    $t6, 4($s0)
/* 0AE8E4 800ADCE4 24010015 */  li    $at, 21
/* 0AE8E8 800ADCE8 240F0019 */  li    $t7, 25
/* 0AE8EC 800ADCEC 15C10015 */  bne   $t6, $at, .L800ADD44
/* 0AE8F0 800ADCF0 3C044900 */   lui   $a0, (0x49008001 >> 16) # lui $a0, 0x4900
/* 0AE8F4 800ADCF4 AE0F0004 */  sw    $t7, 4($s0)
/* 0AE8F8 800ADCF8 AE00001C */  sw    $zero, 0x1c($s0)
/* 0AE8FC 800ADCFC 0C032384 */  jal   play_sound2
/* 0AE900 800ADD00 34848001 */   ori   $a0, (0x49008001 & 0xFFFF) # ori $a0, $a0, 0x8001
/* 0AE904 800ADD04 C6080024 */  lwc1  $f8, 0x24($s0)
/* 0AE908 800ADD08 3C01800F */  lui   $at, %hi(D_800F2860)
/* 0AE90C 800ADD0C D42A2860 */  ldc1  $f10, %lo(D_800F2860)($at)
/* 0AE910 800ADD10 46004021 */  cvt.d.s $f0, $f8
/* 0AE914 800ADD14 3C014010 */  li    $at, 0x40100000 # 2.250000
/* 0AE918 800ADD18 462A003C */  c.lt.d $f0, $f10
/* 0AE91C 800ADD1C 00000000 */  nop
/* 0AE920 800ADD20 45020085 */  bc1fl .L800ADF38
/* 0AE924 800ADD24 8FBF0024 */   lw    $ra, 0x24($sp)
/* 0AE928 800ADD28 44818800 */  mtc1  $at, $f17
/* 0AE92C 800ADD2C 44808000 */  mtc1  $zero, $f16
/* 0AE930 800ADD30 00000000 */  nop
/* 0AE934 800ADD34 46300480 */  add.d $f18, $f0, $f16
/* 0AE938 800ADD38 46209120 */  cvt.s.d $f4, $f18
/* 0AE93C 800ADD3C 1000007D */  b     .L800ADF34
/* 0AE940 800ADD40 E6040024 */   swc1  $f4, 0x24($s0)
.L800ADD44:
/* 0AE944 800ADD44 8E180020 */  lw    $t8, 0x20($s0)
/* 0AE948 800ADD48 3C044900 */  lui   $a0, (0x49008002 >> 16) # lui $a0, 0x4900
/* 0AE94C 800ADD4C 34848002 */  ori   $a0, (0x49008002 & 0xFFFF) # ori $a0, $a0, 0x8002
/* 0AE950 800ADD50 27190011 */  addiu $t9, $t8, 0x11
/* 0AE954 800ADD54 0C032384 */  jal   play_sound2
/* 0AE958 800ADD58 AE190004 */   sw    $t9, 4($s0)
/* 0AE95C 800ADD5C 10000076 */  b     .L800ADF38
/* 0AE960 800ADD60 8FBF0024 */   lw    $ra, 0x24($sp)
glabel L800ADD64
/* 0AE964 800ADD64 8E08001C */  lw    $t0, 0x1c($s0)
/* 0AE968 800ADD68 24010001 */  li    $at, 1
/* 0AE96C 800ADD6C 3C048019 */  lui   $a0, %hi(gControllerPak1FileHandle) # $a0, 0x8019
/* 0AE970 800ADD70 15010020 */  bne   $t0, $at, .L800ADDF4
/* 0AE974 800ADD74 2484E868 */   addiu $a0, %lo(gControllerPak1FileHandle) # addiu $a0, $a0, -0x1798
/* 0AE978 800ADD78 3C09800F */  lui   $t1, %hi(gExtCode) # $t1, 0x800f
/* 0AE97C 800ADD7C 3C0A8019 */  lui   $t2, %hi(gControllerPak1FileNote) # $t2, 0x8019
/* 0AE980 800ADD80 254AEB84 */  addiu $t2, %lo(gControllerPak1FileNote) # addiu $t2, $t2, -0x147c
/* 0AE984 800ADD84 25292E74 */  addiu $t1, %lo(gExtCode) # addiu $t1, $t1, 0x2e74
/* 0AE988 800ADD88 3C05800F */  lui   $a1, %hi(gCompanyCode) # $a1, 0x800f
/* 0AE98C 800ADD8C 3C06800F */  lui   $a2, %hi(gGameCode) # $a2, 0x800f
/* 0AE990 800ADD90 3C07800F */  lui   $a3, %hi(gGameName) # $a3, 0x800f
/* 0AE994 800ADD94 24E72E64 */  addiu $a3, %lo(gGameName) # addiu $a3, $a3, 0x2e64
/* 0AE998 800ADD98 8CC686F4 */  lw    $a2, %lo(gGameCode)($a2)
/* 0AE99C 800ADD9C 94A586F0 */  lhu   $a1, %lo(gCompanyCode)($a1)
/* 0AE9A0 800ADDA0 AFA90010 */  sw    $t1, 0x10($sp)
/* 0AE9A4 800ADDA4 0C033E20 */  jal   osPfsFindFile
/* 0AE9A8 800ADDA8 AFAA0014 */   sw    $t2, 0x14($sp)
/* 0AE9AC 800ADDAC 10400007 */  beqz  $v0, .L800ADDCC
/* 0AE9B0 800ADDB0 240B001A */   li    $t3, 26
/* 0AE9B4 800ADDB4 3C044900 */  lui   $a0, (0x4900FF07 >> 16) # lui $a0, 0x4900
/* 0AE9B8 800ADDB8 AE0B0004 */  sw    $t3, 4($s0)
/* 0AE9BC 800ADDBC 0C032384 */  jal   play_sound2
/* 0AE9C0 800ADDC0 3484FF07 */   ori   $a0, (0x4900FF07 & 0xFFFF) # ori $a0, $a0, 0xff07
/* 0AE9C4 800ADDC4 1000005C */  b     .L800ADF38
/* 0AE9C8 800ADDC8 8FBF0024 */   lw    $ra, 0x24($sp)
.L800ADDCC:
/* 0AE9CC 800ADDCC 0C02D85E */  jal   func_800B6178
/* 0AE9D0 800ADDD0 8E040020 */   lw    $a0, 0x20($s0)
/* 0AE9D4 800ADDD4 10400007 */  beqz  $v0, .L800ADDF4
/* 0AE9D8 800ADDD8 240C001A */   li    $t4, 26
/* 0AE9DC 800ADDDC 3C044900 */  lui   $a0, (0x4900FF07 >> 16) # lui $a0, 0x4900
/* 0AE9E0 800ADDE0 AE0C0004 */  sw    $t4, 4($s0)
/* 0AE9E4 800ADDE4 0C032384 */  jal   play_sound2
/* 0AE9E8 800ADDE8 3484FF07 */   ori   $a0, (0x4900FF07 & 0xFFFF) # ori $a0, $a0, 0xff07
/* 0AE9EC 800ADDEC 10000052 */  b     .L800ADF38
/* 0AE9F0 800ADDF0 8FBF0024 */   lw    $ra, 0x24($sp)
.L800ADDF4:
/* 0AE9F4 800ADDF4 8E0D001C */  lw    $t5, 0x1c($s0)
/* 0AE9F8 800ADDF8 2418000A */  li    $t8, 10
/* 0AE9FC 800ADDFC 25AE0001 */  addiu $t6, $t5, 1
/* 0AEA00 800ADE00 29C10002 */  slti  $at, $t6, 2
/* 0AEA04 800ADE04 1420004B */  bnez  $at, .L800ADF34
/* 0AEA08 800ADE08 AE0E001C */   sw    $t6, 0x1c($s0)
/* 0AEA0C 800ADE0C 10000049 */  b     .L800ADF34
/* 0AEA10 800ADE10 AE180004 */   sw    $t8, 4($s0)
glabel L800ADE14
/* 0AEA14 800ADE14 8E040020 */  lw    $a0, 0x20($s0)
/* 0AEA18 800ADE18 288100F0 */  slti  $at, $a0, 0xf0
/* 0AEA1C 800ADE1C 1020000E */  beqz  $at, .L800ADE58
/* 0AEA20 800ADE20 AE040010 */   sw    $a0, 0x10($s0)
/* 0AEA24 800ADE24 24990010 */  addiu $t9, $a0, 0x10
/* 0AEA28 800ADE28 AE190020 */  sw    $t9, 0x20($s0)
/* 0AEA2C 800ADE2C 3C02800E */  lui   $v0, %hi(D_800DC5EC) # $v0, 0x800e
/* 0AEA30 800ADE30 8C42C5EC */  lw    $v0, %lo(D_800DC5EC)($v0)
/* 0AEA34 800ADE34 3C03800E */  lui   $v1, %hi(D_800DC5F0) # $v1, 0x800e
/* 0AEA38 800ADE38 84480032 */  lh    $t0, 0x32($v0)
/* 0AEA3C 800ADE3C 25090010 */  addiu $t1, $t0, 0x10
/* 0AEA40 800ADE40 A4490032 */  sh    $t1, 0x32($v0)
/* 0AEA44 800ADE44 8C63C5F0 */  lw    $v1, %lo(D_800DC5F0)($v1)
/* 0AEA48 800ADE48 846A0032 */  lh    $t2, 0x32($v1)
/* 0AEA4C 800ADE4C 254BFFF0 */  addiu $t3, $t2, -0x10
/* 0AEA50 800ADE50 10000038 */  b     .L800ADF34
/* 0AEA54 800ADE54 A46B0032 */   sh    $t3, 0x32($v1)
.L800ADE58:
/* 0AEA58 800ADE58 8E0C001C */  lw    $t4, 0x1c($s0)
/* 0AEA5C 800ADE5C 258DFFFB */  addiu $t5, $t4, -5
/* 0AEA60 800ADE60 2DA10005 */  sltiu $at, $t5, 5
/* 0AEA64 800ADE64 10200020 */  beqz  $at, .L800ADEE8
/* 0AEA68 800ADE68 000D6880 */   sll   $t5, $t5, 2
/* 0AEA6C 800ADE6C 3C01800F */  lui   $at, %hi(jpt_800F2868)
/* 0AEA70 800ADE70 002D0821 */  addu  $at, $at, $t5
/* 0AEA74 800ADE74 8C2D2868 */  lw    $t5, %lo(jpt_800F2868)($at)
/* 0AEA78 800ADE78 01A00008 */  jr    $t5
/* 0AEA7C 800ADE7C 00000000 */   nop
glabel L800ADE80
/* 0AEA80 800ADE80 3C018016 */  lui   $at, %hi(D_8015F890) # $at, 0x8016
/* 0AEA84 800ADE84 A420F890 */  sh    $zero, %lo(D_8015F890)($at)
/* 0AEA88 800ADE88 3C018016 */  lui   $at, %hi(D_8015F892) # $at, 0x8016
/* 0AEA8C 800ADE8C 240E0001 */  li    $t6, 1
/* 0AEA90 800ADE90 0C0A40EC */  jal   func_802903B0
/* 0AEA94 800ADE94 A42EF892 */   sh    $t6, %lo(D_8015F892)($at)
/* 0AEA98 800ADE98 10000014 */  b     .L800ADEEC
/* 0AEA9C 800ADE9C 2418001F */   li    $t8, 31
glabel L800ADEA0
/* 0AEAA0 800ADEA0 0C0A40E2 */  jal   func_80290388
/* 0AEAA4 800ADEA4 00000000 */   nop
/* 0AEAA8 800ADEA8 10000010 */  b     .L800ADEEC
/* 0AEAAC 800ADEAC 2418001F */   li    $t8, 31
glabel L800ADEB0
/* 0AEAB0 800ADEB0 0C0A40D8 */  jal   func_80290360
/* 0AEAB4 800ADEB4 00000000 */   nop
/* 0AEAB8 800ADEB8 1000000C */  b     .L800ADEEC
/* 0AEABC 800ADEBC 2418001F */   li    $t8, 31
glabel L800ADEC0
/* 0AEAC0 800ADEC0 0C0A40CE */  jal   func_80290338
/* 0AEAC4 800ADEC4 00000000 */   nop
/* 0AEAC8 800ADEC8 10000008 */  b     .L800ADEEC
/* 0AEACC 800ADECC 2418001F */   li    $t8, 31
glabel L800ADED0
/* 0AEAD0 800ADED0 240F0001 */  li    $t7, 1
/* 0AEAD4 800ADED4 3C018016 */  lui   $at, %hi(D_8015F890) # $at, 0x8016
/* 0AEAD8 800ADED8 A42FF890 */  sh    $t7, %lo(D_8015F890)($at)
/* 0AEADC 800ADEDC 3C018016 */  lui   $at, %hi(D_8015F892) # $at, 0x8016
/* 0AEAE0 800ADEE0 0C0A40EC */  jal   func_802903B0
/* 0AEAE4 800ADEE4 A420F892 */   sh    $zero, %lo(D_8015F892)($at)
.L800ADEE8:
/* 0AEAE8 800ADEE8 2418001F */  li    $t8, 31
.L800ADEEC:
/* 0AEAEC 800ADEEC AE000020 */  sw    $zero, 0x20($s0)
/* 0AEAF0 800ADEF0 AE180004 */  sw    $t8, 4($s0)
/* 0AEAF4 800ADEF4 3C08800E */  lui   $t0, %hi(D_800DC5EC) # $t0, 0x800e
/* 0AEAF8 800ADEF8 8D08C5EC */  lw    $t0, %lo(D_800DC5EC)($t0)
/* 0AEAFC 800ADEFC 2419012C */  li    $t9, 300
/* 0AEB00 800ADF00 3C0A800E */  lui   $t2, %hi(D_800DC5F0) # $t2, 0x800e
/* 0AEB04 800ADF04 A5190032 */  sh    $t9, 0x32($t0)
/* 0AEB08 800ADF08 8D4AC5F0 */  lw    $t2, %lo(D_800DC5F0)($t2)
/* 0AEB0C 800ADF0C 2409FFC4 */  li    $t1, -60
/* 0AEB10 800ADF10 240B0004 */  li    $t3, 4
/* 0AEB14 800ADF14 3C018016 */  lui   $at, %hi(D_8015F894) # $at, 0x8016
/* 0AEB18 800ADF18 A5490032 */  sh    $t1, 0x32($t2)
/* 0AEB1C 800ADF1C A42BF894 */  sh    $t3, %lo(D_8015F894)($at)
/* 0AEB20 800ADF20 0C0328CC */  jal   func_800CA330
/* 0AEB24 800ADF24 24040019 */   li    $a0, 25
/* 0AEB28 800ADF28 10000003 */  b     .L800ADF38
/* 0AEB2C 800ADF2C 8FBF0024 */   lw    $ra, 0x24($sp)
glabel L800ADF30
/* 0AEB30 800ADF30 AE000000 */  sw    $zero, ($s0)
.L800ADF34:
glabel L800ADF34
/* 0AEB34 800ADF34 8FBF0024 */  lw    $ra, 0x24($sp)
.L800ADF38:
/* 0AEB38 800ADF38 8FB00020 */  lw    $s0, 0x20($sp)
/* 0AEB3C 800ADF3C 27BD0030 */  addiu $sp, $sp, 0x30
/* 0AEB40 800ADF40 03E00008 */  jr    $ra
/* 0AEB44 800ADF44 00000000 */   nop
