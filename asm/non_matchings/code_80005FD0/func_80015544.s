.section .late_rodata

glabel D_800ED218
.double 3000.0

.section .text

glabel func_80015544
/* 016144 80015544 00045840 */  sll   $t3, $a0, 1
/* 016148 80015548 3C0C8016 */  lui   $t4, %hi(gNearestWaypointByPlayerId) # 0x8016
/* 01614C 8001554C 018B6021 */  addu  $t4, $t4, $t3
/* 016150 80015550 958C4438 */  lhu   $t4, %lo(gNearestWaypointByPlayerId)($t4) # 0x4438($t4)
/* 016154 80015554 00077040 */  sll   $t6, $a3, 1
/* 016158 80015558 3C028016 */  lui   $v0, %hi(gWaypointCountByPathIndex) # 0x8016
/* 01615C 8001555C 004E1021 */  addu  $v0, $v0, $t6
/* 016160 80015560 944245C8 */  lhu   $v0, %lo(gWaypointCountByPathIndex)($v0) # 0x45c8($v0)
/* 016164 80015564 258D000A */  addiu $t5, $t4, 0xa
/* 016168 80015568 00067880 */  sll   $t7, $a2, 2
/* 01616C 8001556C 01A2001A */  div   $zero, $t5, $v0
/* 016170 80015570 3C018016 */  lui   $at, %hi(D_80164688)
/* 016174 80015574 44856000 */  mtc1  $a1, $f12
/* 016178 80015578 002F0821 */  addu  $at, $at, $t7
/* 01617C 8001557C 27BDFFC0 */  addiu $sp, $sp, -0x40
/* 016180 80015580 E42C4688 */  swc1  $f12, %lo(D_80164688)($at)
/* 016184 80015584 AFA60048 */  sw    $a2, 0x48($sp)
/* 016188 80015588 00C0C025 */  move  $t8, $a2
/* 01618C 8001558C 0006C840 */  sll   $t9, $a2, 1
/* 016190 80015590 3C098016 */  lui   $t1, %hi(gNearestWaypointByCameraId) # $t1, 0x8016
/* 016194 80015594 01E04025 */  move  $t0, $t7
/* 016198 80015598 25294668 */  addiu $t1, %lo(gNearestWaypointByCameraId) # addiu $t1, $t1, 0x4668
/* 01619C 8001559C 00007010 */  mfhi  $t6
/* 0161A0 800155A0 00073400 */  sll   $a2, $a3, 0x10
/* 0161A4 800155A4 AFBF0014 */  sw    $ra, 0x14($sp)
/* 0161A8 800155A8 AFA40040 */  sw    $a0, 0x40($sp)
/* 0161AC 800155AC 03291821 */  addu  $v1, $t9, $t1
/* 0161B0 800155B0 00805025 */  move  $t2, $a0
/* 0161B4 800155B4 00067C03 */  sra   $t7, $a2, 0x10
/* 0161B8 800155B8 14400002 */  bnez  $v0, .L800155C4
/* 0161BC 800155BC 00000000 */   nop   
/* 0161C0 800155C0 0007000D */  break 7
.L800155C4:
/* 0161C4 800155C4 2401FFFF */  li    $at, -1
/* 0161C8 800155C8 14410004 */  bne   $v0, $at, .L800155DC
/* 0161CC 800155CC 3C018000 */   lui   $at, 0x8000
/* 0161D0 800155D0 15A10002 */  bne   $t5, $at, .L800155DC
/* 0161D4 800155D4 00000000 */   nop   
/* 0161D8 800155D8 0006000D */  break 6
.L800155DC:
/* 0161DC 800155DC 44056000 */  mfc1  $a1, $f12
/* 0161E0 800155E0 A46E0000 */  sh    $t6, ($v1)
/* 0161E4 800155E4 01E03025 */  move  $a2, $t7
/* 0161E8 800155E8 31C4FFFF */  andi  $a0, $t6, 0xffff
/* 0161EC 800155EC AFA30028 */  sw    $v1, 0x28($sp)
/* 0161F0 800155F0 AFA8002C */  sw    $t0, 0x2c($sp)
/* 0161F4 800155F4 0C002EF6 */  jal   func_8000BBD8
/* 0161F8 800155F8 AFA7004C */   sw    $a3, 0x4c($sp)
/* 0161FC 800155FC 3C028016 */  lui   $v0, %hi(D_80162FA0) # $v0, 0x8016
/* 016200 80015600 8FA8002C */  lw    $t0, 0x2c($sp)
/* 016204 80015604 24422FA0 */  addiu $v0, %lo(D_80162FA0) # addiu $v0, $v0, 0x2fa0
/* 016208 80015608 8FA7004C */  lw    $a3, 0x4c($sp)
/* 01620C 8001560C 8FA30028 */  lw    $v1, 0x28($sp)
/* 016210 80015610 C44C0000 */  lwc1  $f12, ($v0)
/* 016214 80015614 C4400008 */  lwc1  $f0, 8($v0)
/* 016218 80015618 3C188016 */  lui   $t8, %hi(D_801645F8) # $t8, 0x8016
/* 01621C 8001561C 3C198016 */  lui   $t9, %hi(D_80164638) # $t9, 0x8016
/* 016220 80015620 271845F8 */  addiu $t8, %lo(D_801645F8) # addiu $t8, $t8, 0x45f8
/* 016224 80015624 27394638 */  addiu $t9, %lo(D_80164638) # addiu $t9, $t9, 0x4638
/* 016228 80015628 3C0A8016 */  lui   $t2, %hi(D_80164550) # 0x8016
/* 01622C 8001562C 01182021 */  addu  $a0, $t0, $t8
/* 016230 80015630 01192821 */  addu  $a1, $t0, $t9
/* 016234 80015634 00074880 */  sll   $t1, $a3, 2
/* 016238 80015638 846B0000 */  lh    $t3, ($v1)
/* 01623C 8001563C 01495021 */  addu  $t2, $t2, $t1
/* 016240 80015640 E48C0000 */  swc1  $f12, ($a0)
/* 016244 80015644 E4A00000 */  swc1  $f0, ($a1)
/* 016248 80015648 8D4A4550 */  lw    $t2, %lo(D_80164550)($t2) # 0x4550($t2)
/* 01624C 8001564C 000B60C0 */  sll   $t4, $t3, 3
/* 016250 80015650 3C01403E */  li    $at, 0x403E0000 # 2.968750
/* 016254 80015654 014C6821 */  addu  $t5, $t2, $t4
/* 016258 80015658 85AE0002 */  lh    $t6, 2($t5)
/* 01625C 8001565C 44813800 */  mtc1  $at, $f7
/* 016260 80015660 44803000 */  mtc1  $zero, $f6
/* 016264 80015664 448E2000 */  mtc1  $t6, $f4
/* 016268 80015668 44060000 */  mfc1  $a2, $f0
/* 01626C 8001566C AFA50020 */  sw    $a1, 0x20($sp)
/* 016270 80015670 46802420 */  cvt.s.w $f16, $f4
/* 016274 80015674 AFA40024 */  sw    $a0, 0x24($sp)
/* 016278 80015678 460080A1 */  cvt.d.s $f2, $f16
/* 01627C 8001567C 46261200 */  add.d $f8, $f2, $f6
/* 016280 80015680 F7A20018 */  sdc1  $f2, 0x18($sp)
/* 016284 80015684 0C0AB870 */  jal   func_802AE1C0
/* 016288 80015688 462043A0 */   cvt.s.d $f14, $f8
/* 01628C 8001568C 3C014034 */  li    $at, 0x40340000 # 2.812500
/* 016290 80015690 D7A20018 */  ldc1  $f2, 0x18($sp)
/* 016294 80015694 44815800 */  mtc1  $at, $f11
/* 016298 80015698 44805000 */  mtc1  $zero, $f10
/* 01629C 8001569C 46000321 */  cvt.d.s $f12, $f0
/* 0162A0 800156A0 3C0B8016 */  lui   $t3, %hi(cameras) # $t3, 0x8016
/* 0162A4 800156A4 462A1481 */  sub.d $f18, $f2, $f10
/* 0162A8 800156A8 8FA40024 */  lw    $a0, 0x24($sp)
/* 0162AC 800156AC 8FA50020 */  lw    $a1, 0x20($sp)
/* 0162B0 800156B0 8FA8002C */  lw    $t0, 0x2c($sp)
/* 0162B4 800156B4 4632603C */  c.lt.d $f12, $f18
/* 0162B8 800156B8 3C01800F */  lui   $at, %hi(D_800ED218)
/* 0162BC 800156BC 256B46F0 */  addiu $t3, %lo(cameras) # addiu $t3, $t3, 0x46f0
/* 0162C0 800156C0 45030008 */  bc1tl .L800156E4
/* 0162C4 800156C4 3C014024 */   li    $at, 0x40240000 # 2.562500
/* 0162C8 800156C8 D424D218 */  ldc1  $f4, %lo(D_800ED218)($at)
/* 0162CC 800156CC 3C014024 */  li    $at, 0x40240000 # 2.562500
/* 0162D0 800156D0 462C203E */  c.le.d $f4, $f12
/* 0162D4 800156D4 00000000 */  nop   
/* 0162D8 800156D8 4502000C */  bc1fl .L8001570C
/* 0162DC 800156DC 44819800 */   mtc1  $at, $f19
/* 0162E0 800156E0 3C014024 */  li    $at, 0x40240000 # 2.562500
.L800156E4:
/* 0162E4 800156E4 44813800 */  mtc1  $at, $f7
/* 0162E8 800156E8 44803000 */  mtc1  $zero, $f6
/* 0162EC 800156EC 3C0F8016 */  lui   $t7, %hi(D_80164618) # $t7, 0x8016
/* 0162F0 800156F0 25EF4618 */  addiu $t7, %lo(D_80164618) # addiu $t7, $t7, 0x4618
/* 0162F4 800156F4 46261200 */  add.d $f8, $f2, $f6
/* 0162F8 800156F8 010F1821 */  addu  $v1, $t0, $t7
/* 0162FC 800156FC 462042A0 */  cvt.s.d $f10, $f8
/* 016300 80015700 10000009 */  b     .L80015728
/* 016304 80015704 E46A0000 */   swc1  $f10, ($v1)
/* 016308 80015708 44819800 */  mtc1  $at, $f19
.L8001570C:
/* 01630C 8001570C 44809000 */  mtc1  $zero, $f18
/* 016310 80015710 3C188016 */  lui   $t8, %hi(D_80164618) # $t8, 0x8016
/* 016314 80015714 27184618 */  addiu $t8, %lo(D_80164618) # addiu $t8, $t8, 0x4618
/* 016318 80015718 46326100 */  add.d $f4, $f12, $f18
/* 01631C 8001571C 01181821 */  addu  $v1, $t0, $t8
/* 016320 80015720 462021A0 */  cvt.s.d $f6, $f4
/* 016324 80015724 E4660000 */  swc1  $f6, ($v1)
.L80015728:
/* 016328 80015728 8FB90048 */  lw    $t9, 0x48($sp)
/* 01632C 8001572C 44804000 */  mtc1  $zero, $f8
/* 016330 80015730 3C018016 */  lui   $at, %hi(D_80164648)
/* 016334 80015734 00194880 */  sll   $t1, $t9, 2
/* 016338 80015738 00280821 */  addu  $at, $at, $t0
/* 01633C 8001573C 01394823 */  subu  $t1, $t1, $t9
/* 016340 80015740 000948C0 */  sll   $t1, $t1, 3
/* 016344 80015744 E4284648 */  swc1  $f8, %lo(D_80164648)($at)
/* 016348 80015748 C48A0000 */  lwc1  $f10, ($a0)
/* 01634C 8001574C 01394823 */  subu  $t1, $t1, $t9
/* 016350 80015750 000948C0 */  sll   $t1, $t1, 3
/* 016354 80015754 012B1021 */  addu  $v0, $t1, $t3
/* 016358 80015758 E44A0000 */  swc1  $f10, ($v0)
/* 01635C 8001575C C4720000 */  lwc1  $f18, ($v1)
/* 016360 80015760 E4520004 */  swc1  $f18, 4($v0)
/* 016364 80015764 C4A40000 */  lwc1  $f4, ($a1)
/* 016368 80015768 E4440008 */  swc1  $f4, 8($v0)
/* 01636C 8001576C 8FBF0014 */  lw    $ra, 0x14($sp)
/* 016370 80015770 27BD0040 */  addiu $sp, $sp, 0x40
/* 016374 80015774 03E00008 */  jr    $ra
/* 016378 80015778 00000000 */   nop   
