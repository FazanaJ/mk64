glabel func_8006F8CC
/* 0704CC 8006F8CC 3C078019 */  lui   $a3, %hi(D_8018EDFC) # $a3, 0x8019
/* 0704D0 8006F8D0 24E7EDFC */  addiu $a3, %lo(D_8018EDFC) # addiu $a3, $a3, -0x1204
/* 0704D4 8006F8D4 80EE0000 */  lb    $t6, ($a3)
/* 0704D8 8006F8D8 27BDFFE8 */  addiu $sp, $sp, -0x18
/* 0704DC 8006F8DC AFBF0014 */  sw    $ra, 0x14($sp)
/* 0704E0 8006F8E0 15C00045 */  bnez  $t6, .L8006F9F8
/* 0704E4 8006F8E4 3C028016 */   lui   $v0, %hi(D_80165800) # 0x8016
/* 0704E8 8006F8E8 3C058016 */  lui   $a1, %hi(D_801657E4) # $a1, 0x8016
/* 0704EC 8006F8EC 24A557E4 */  addiu $a1, %lo(D_801657E4) # addiu $a1, $a1, 0x57e4
/* 0704F0 8006F8F0 24030001 */  li    $v1, 1
/* 0704F4 8006F8F4 3C028016 */  lui   $v0, %hi(D_80165800) # $v0, 0x8016
/* 0704F8 8006F8F8 A0E30000 */  sb    $v1, ($a3)
/* 0704FC 8006F8FC A0A00000 */  sb    $zero, ($a1)
/* 070500 8006F900 3C018016 */  lui   $at, %hi(D_801657E6) # $at, 0x8016
/* 070504 8006F904 24425800 */  addiu $v0, %lo(D_80165800) # addiu $v0, $v0, 0x5800
/* 070508 8006F908 A02057E6 */  sb    $zero, %lo(D_801657E6)($at)
/* 07050C 8006F90C A0430001 */  sb    $v1, 1($v0)
/* 070510 8006F910 804F0001 */  lb    $t7, 1($v0)
/* 070514 8006F914 3C068016 */  lui   $a2, %hi(D_801657F0) # $a2, 0x8016
/* 070518 8006F918 3C088016 */  lui   $t0, %hi(D_801657E8) # $t0, 0x8016
/* 07051C 8006F91C 250857E8 */  addiu $t0, %lo(D_801657E8) # addiu $t0, $t0, 0x57e8
/* 070520 8006F920 24C657F0 */  addiu $a2, %lo(D_801657F0) # addiu $a2, $a2, 0x57f0
/* 070524 8006F924 A0C00000 */  sb    $zero, ($a2)
/* 070528 8006F928 A1030000 */  sb    $v1, ($t0)
/* 07052C 8006F92C 3C048019 */  lui   $a0, %hi(D_8018EDF3) # $a0, 0x8019
/* 070530 8006F930 A04F0000 */  sb    $t7, ($v0)
/* 070534 8006F934 8084EDF3 */  lb    $a0, %lo(D_8018EDF3)($a0)
/* 070538 8006F938 24010004 */  li    $at, 4
/* 07053C 8006F93C 3C18800E */  lui   $t8, %hi(gModeSelection) # $t8, 0x800e
/* 070540 8006F940 14810012 */  bne   $a0, $at, .L8006F98C
/* 070544 8006F944 24070003 */   li    $a3, 3
/* 070548 8006F948 8F18C53C */  lw    $t8, %lo(gModeSelection)($t8)
/* 07054C 8006F94C 24070003 */  li    $a3, 3
/* 070550 8006F950 3C018016 */  lui   $at, %hi(D_801657F8) # $at, 0x8016
/* 070554 8006F954 10F80008 */  beq   $a3, $t8, .L8006F978
/* 070558 8006F958 00000000 */   nop   
/* 07055C 8006F95C A0A30000 */  sb    $v1, ($a1)
/* 070560 8006F960 A0C30000 */  sb    $v1, ($a2)
/* 070564 8006F964 A02357F8 */  sb    $v1, %lo(D_801657F8)($at)
/* 070568 8006F968 A0400001 */  sb    $zero, 1($v0)
/* 07056C 8006F96C 80590001 */  lb    $t9, 1($v0)
/* 070570 8006F970 1000001C */  b     .L8006F9E4
/* 070574 8006F974 A0590000 */   sb    $t9, ($v0)
.L8006F978:
/* 070578 8006F978 3C018016 */  lui   $at, %hi(D_801657F8) # $at, 0x8016
/* 07057C 8006F97C A02057F8 */  sb    $zero, %lo(D_801657F8)($at)
/* 070580 8006F980 80490001 */  lb    $t1, 1($v0)
/* 070584 8006F984 10000017 */  b     .L8006F9E4
/* 070588 8006F988 A0490000 */   sb    $t1, ($v0)
.L8006F98C:
/* 07058C 8006F98C 14E40004 */  bne   $a3, $a0, .L8006F9A0
/* 070590 8006F990 3C018016 */   lui   $at, %hi(D_801657F8) # $at, 0x8016
/* 070594 8006F994 A1000000 */  sb    $zero, ($t0)
/* 070598 8006F998 10000012 */  b     .L8006F9E4
/* 07059C 8006F99C A02357F8 */   sb    $v1, %lo(D_801657F8)($at)
.L8006F9A0:
/* 0705A0 8006F9A0 24010002 */  li    $at, 2
/* 0705A4 8006F9A4 1481000F */  bne   $a0, $at, .L8006F9E4
/* 0705A8 8006F9A8 3C0A800E */   lui   $t2, %hi(gModeSelection) # $t2, 0x800e
/* 0705AC 8006F9AC 8D4AC53C */  lw    $t2, %lo(gModeSelection)($t2)
/* 0705B0 8006F9B0 240C0041 */  li    $t4, 65
/* 0705B4 8006F9B4 240D00B4 */  li    $t5, 180
/* 0705B8 8006F9B8 10EA0006 */  beq   $a3, $t2, .L8006F9D4
/* 0705BC 8006F9BC 00000000 */   nop   
/* 0705C0 8006F9C0 A0400001 */  sb    $zero, 1($v0)
/* 0705C4 8006F9C4 804B0001 */  lb    $t3, 1($v0)
/* 0705C8 8006F9C8 A0A30000 */  sb    $v1, ($a1)
/* 0705CC 8006F9CC A0C30000 */  sb    $v1, ($a2)
/* 0705D0 8006F9D0 A04B0000 */  sb    $t3, ($v0)
.L8006F9D4:
/* 0705D4 8006F9D4 3C028019 */  lui   $v0, %hi(D_8018D2D8) # $v0, 0x8019
/* 0705D8 8006F9D8 2442D2D8 */  addiu $v0, %lo(D_8018D2D8) # addiu $v0, $v0, -0x2d28
/* 0705DC 8006F9DC A44C0000 */  sh    $t4, ($v0)
/* 0705E0 8006F9E0 A44D0002 */  sh    $t5, 2($v0)
.L8006F9E4:
/* 0705E4 8006F9E4 0C01BE09 */  jal   func_8006F824
/* 0705E8 8006F9E8 00002025 */   move  $a0, $zero
/* 0705EC 8006F9EC 3C068016 */  lui   $a2, %hi(D_801657F0) # $a2, 0x8016
/* 0705F0 8006F9F0 1000001F */  b     .L8006FA70
/* 0705F4 8006F9F4 24C657F0 */   addiu $a2, %lo(D_801657F0) # addiu $a2, $a2, 0x57f0
.L8006F9F8:
/* 0705F8 8006F9F8 3C0E8016 */  lui   $t6, %hi(D_80165808) # $t6, 0x8016
/* 0705FC 8006F9FC 81CE5808 */  lb    $t6, %lo(D_80165808)($t6)
/* 070600 8006FA00 3C058016 */  lui   $a1, %hi(D_801657E4) # $a1, 0x8016
/* 070604 8006FA04 24A557E4 */  addiu $a1, %lo(D_801657E4) # addiu $a1, $a1, 0x57e4
/* 070608 8006FA08 3C0F8016 */  lui   $t7, %hi(D_80165810) # $t7, 0x8016
/* 07060C 8006FA0C A0AE0000 */  sb    $t6, ($a1)
/* 070610 8006FA10 81EF5810 */  lb    $t7, %lo(D_80165810)($t7)
/* 070614 8006FA14 3C188016 */  lui   $t8, %hi(D_80165820) # $t8, 0x8016
/* 070618 8006FA18 83185820 */  lb    $t8, %lo(D_80165820)($t8)
/* 07061C 8006FA1C 3C068016 */  lui   $a2, %hi(D_801657F0) # $a2, 0x8016
/* 070620 8006FA20 3C018016 */  lui   $at, %hi(D_801657E6) # $at, 0x8016
/* 070624 8006FA24 24C657F0 */  addiu $a2, %lo(D_801657F0) # addiu $a2, $a2, 0x57f0
/* 070628 8006FA28 A02F57E6 */  sb    $t7, %lo(D_801657E6)($at)
/* 07062C 8006FA2C 3C198016 */  lui   $t9, %hi(D_80165818) # $t9, 0x8016
/* 070630 8006FA30 A0D80000 */  sb    $t8, ($a2)
/* 070634 8006FA34 83395818 */  lb    $t9, %lo(D_80165818)($t9)
/* 070638 8006FA38 3C088016 */  lui   $t0, %hi(D_801657E8) # $t0, 0x8016
/* 07063C 8006FA3C 250857E8 */  addiu $t0, %lo(D_801657E8) # addiu $t0, $t0, 0x57e8
/* 070640 8006FA40 3C098016 */  lui   $t1, %hi(D_80165828) # $t1, 0x8016
/* 070644 8006FA44 A1190000 */  sb    $t9, ($t0)
/* 070648 8006FA48 81295828 */  lb    $t1, %lo(D_80165828)($t1)
/* 07064C 8006FA4C 3C038016 */  lui   $v1, %hi(D_80165832) # $v1, 0x8016
/* 070650 8006FA50 3C018016 */  lui   $at, %hi(D_801657F8) # $at, 0x8016
/* 070654 8006FA54 24635832 */  addiu $v1, %lo(D_80165832) # addiu $v1, $v1, 0x5832
/* 070658 8006FA58 A02957F8 */  sb    $t1, %lo(D_801657F8)($at)
/* 07065C 8006FA5C 806A0000 */  lb    $t2, ($v1)
/* 070660 8006FA60 806B0001 */  lb    $t3, 1($v1)
/* 070664 8006FA64 24425800 */  addiu $v0, $v0, %lo(D_80165800) # 0x5800
/* 070668 8006FA68 A04A0000 */  sb    $t2, ($v0)
/* 07066C 8006FA6C A04B0001 */  sb    $t3, 1($v0)
.L8006FA70:
/* 070670 8006FA70 3C0C800E */  lui   $t4, %hi(gDemoMode) # $t4, 0x800e
/* 070674 8006FA74 958CC51C */  lhu   $t4, %lo(gDemoMode)($t4)
/* 070678 8006FA78 51800003 */  beql  $t4, $zero, .L8006FA88
/* 07067C 8006FA7C 8FBF0014 */   lw    $ra, 0x14($sp)
/* 070680 8006FA80 A0C00000 */  sb    $zero, ($a2)
/* 070684 8006FA84 8FBF0014 */  lw    $ra, 0x14($sp)
.L8006FA88:
/* 070688 8006FA88 27BD0018 */  addiu $sp, $sp, 0x18
/* 07068C 8006FA8C 03E00008 */  jr    $ra
/* 070690 8006FA90 00000000 */   nop   
