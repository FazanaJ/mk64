glabel func_8001BE78
/* 01CA78 8001BE78 27BDFF80 */  addiu $sp, $sp, -0x80
/* 01CA7C 8001BE7C AFBF004C */  sw    $ra, 0x4c($sp)
/* 01CA80 8001BE80 AFBE0048 */  sw    $fp, 0x48($sp)
/* 01CA84 8001BE84 AFB70044 */  sw    $s7, 0x44($sp)
/* 01CA88 8001BE88 AFB60040 */  sw    $s6, 0x40($sp)
/* 01CA8C 8001BE8C AFB5003C */  sw    $s5, 0x3c($sp)
/* 01CA90 8001BE90 AFB40038 */  sw    $s4, 0x38($sp)
/* 01CA94 8001BE94 AFB30034 */  sw    $s3, 0x34($sp)
/* 01CA98 8001BE98 AFB20030 */  sw    $s2, 0x30($sp)
/* 01CA9C 8001BE9C AFB1002C */  sw    $s1, 0x2c($sp)
/* 01CAA0 8001BEA0 AFB00028 */  sw    $s0, 0x28($sp)
/* 01CAA4 8001BEA4 F7B60020 */  sdc1  $f22, 0x20($sp)
/* 01CAA8 8001BEA8 0C003D8A */  jal   func_8000F628
/* 01CAAC 8001BEAC F7B40018 */   sdc1  $f20, 0x18($sp)
/* 01CAB0 8001BEB0 3C0144FA */  li    $at, 0x44FA0000 # 2000.000000
/* 01CAB4 8001BEB4 3C168016 */  lui   $s6, %hi(gPathIndexByPlayerId) # $s6, 0x8016
/* 01CAB8 8001BEB8 3C148016 */  lui   $s4, %hi(D_801634F8) # $s4, 0x8016
/* 01CABC 8001BEBC 3C138016 */  lui   $s3, %hi(gNearestWaypointByPlayerId) # $s3, 0x8016
/* 01CAC0 8001BEC0 3C178016 */  lui   $s7, %hi(D_80164550) # $s7, 0x8016
/* 01CAC4 8001BEC4 3C1E8016 */  lui   $fp, %hi(D_80164590) # $fp, 0x8016
/* 01CAC8 8001BEC8 3C028016 */  lui   $v0, %hi(D_80163410) # $v0, 0x8016
/* 01CACC 8001BECC 4481B000 */  mtc1  $at, $f22
/* 01CAD0 8001BED0 4480A000 */  mtc1  $zero, $f20
/* 01CAD4 8001BED4 24423410 */  addiu $v0, %lo(D_80163410) # addiu $v0, $v0, 0x3410
/* 01CAD8 8001BED8 27DE4590 */  addiu $fp, %lo(D_80164590) # addiu $fp, $fp, 0x4590
/* 01CADC 8001BEDC 26F74550 */  addiu $s7, %lo(D_80164550) # addiu $s7, $s7, 0x4550
/* 01CAE0 8001BEE0 26734438 */  addiu $s3, %lo(gNearestWaypointByPlayerId) # addiu $s3, $s3, 0x4438
/* 01CAE4 8001BEE4 269434F8 */  addiu $s4, %lo(D_801634F8) # addiu $s4, $s4, 0x34f8
/* 01CAE8 8001BEE8 26D645B0 */  addiu $s6, %lo(gPathIndexByPlayerId) # addiu $s6, $s6, 0x45b0
/* 01CAEC 8001BEEC 00009025 */  move  $s2, $zero
/* 01CAF0 8001BEF0 0000A825 */  move  $s5, $zero
.L8001BEF4:
/* 01CAF4 8001BEF4 3C0E800E */  lui   $t6, %hi(gPlayerOne)
/* 01CAF8 8001BEF8 8DCEC4DC */  lw    $t6, %lo(gPlayerOne)($t6)
/* 01CAFC 8001BEFC 24010001 */  li    $at, 1
/* 01CB00 8001BF00 24190006 */  li    $t9, 6
/* 01CB04 8001BF04 02AE8821 */  addu  $s1, $s5, $t6
/* 01CB08 8001BF08 962F0000 */  lhu   $t7, ($s1)
/* 01CB0C 8001BF0C 31F8DFFF */  andi  $t8, $t7, 0xdfff
/* 01CB10 8001BF10 A6380000 */  sh    $t8, ($s1)
/* 01CB14 8001BF14 A6D20000 */  sh    $s2, ($s6)
/* 01CB18 8001BF18 E694000C */  swc1  $f20, 0xc($s4)
/* 01CB1C 8001BF1C E6940004 */  swc1  $f20, 4($s4)
/* 01CB20 8001BF20 1240000B */  beqz  $s2, .L8001BF50
/* 01CB24 8001BF24 E6940000 */   swc1  $f20, ($s4)
/* 01CB28 8001BF28 1241000B */  beq   $s2, $at, .L8001BF58
/* 01CB2C 8001BF2C 24080001 */   li    $t0, 1
/* 01CB30 8001BF30 24010002 */  li    $at, 2
/* 01CB34 8001BF34 1241000A */  beq   $s2, $at, .L8001BF60
/* 01CB38 8001BF38 24090006 */   li    $t1, 6
/* 01CB3C 8001BF3C 24010003 */  li    $at, 3
/* 01CB40 8001BF40 12410009 */  beq   $s2, $at, .L8001BF68
/* 01CB44 8001BF44 240A0001 */   li    $t2, 1
/* 01CB48 8001BF48 10000009 */  b     .L8001BF70
/* 01CB4C 8001BF4C 966B0000 */   lhu   $t3, ($s3)
.L8001BF50:
/* 01CB50 8001BF50 10000006 */  b     .L8001BF6C
/* 01CB54 8001BF54 A6790000 */   sh    $t9, ($s3)
.L8001BF58:
/* 01CB58 8001BF58 10000004 */  b     .L8001BF6C
/* 01CB5C 8001BF5C A6680000 */   sh    $t0, ($s3)
.L8001BF60:
/* 01CB60 8001BF60 10000002 */  b     .L8001BF6C
/* 01CB64 8001BF64 A6690000 */   sh    $t1, ($s3)
.L8001BF68:
/* 01CB68 8001BF68 A66A0000 */  sh    $t2, ($s3)
.L8001BF6C:
/* 01CB6C 8001BF6C 966B0000 */  lhu   $t3, ($s3)
.L8001BF70:
/* 01CB70 8001BF70 8EED0000 */  lw    $t5, ($s7)
/* 01CB74 8001BF74 4600B386 */  mov.s $f14, $f22
/* 01CB78 8001BF78 000B60C0 */  sll   $t4, $t3, 3
/* 01CB7C 8001BF7C 018D8021 */  addu  $s0, $t4, $t5
/* 01CB80 8001BF80 860E0000 */  lh    $t6, ($s0)
/* 01CB84 8001BF84 448E2000 */  mtc1  $t6, $f4
/* 01CB88 8001BF88 00000000 */  nop
/* 01CB8C 8001BF8C 468021A0 */  cvt.s.w $f6, $f4
/* 01CB90 8001BF90 E6260014 */  swc1  $f6, 0x14($s1)
/* 01CB94 8001BF94 86180004 */  lh    $t8, 4($s0)
/* 01CB98 8001BF98 860F0000 */  lh    $t7, ($s0)
/* 01CB9C 8001BF9C AFA20054 */  sw    $v0, 0x54($sp)
/* 01CBA0 8001BFA0 44985000 */  mtc1  $t8, $f10
/* 01CBA4 8001BFA4 448F4000 */  mtc1  $t7, $f8
/* 01CBA8 8001BFA8 468052A0 */  cvt.s.w $f10, $f10
/* 01CBAC 8001BFAC 46804320 */  cvt.s.w $f12, $f8
/* 01CBB0 8001BFB0 44065000 */  mfc1  $a2, $f10
/* 01CBB4 8001BFB4 0C0AB870 */  jal   func_802AE1C0
/* 01CBB8 8001BFB8 00000000 */   nop
/* 01CBBC 8001BFBC C6300070 */  lwc1  $f16, 0x70($s1)
/* 01CBC0 8001BFC0 02202025 */  move  $a0, $s1
/* 01CBC4 8001BFC4 00002825 */  move  $a1, $zero
/* 01CBC8 8001BFC8 46100480 */  add.s $f18, $f0, $f16
/* 01CBCC 8001BFCC E6320018 */  swc1  $f18, 0x18($s1)
/* 01CBD0 8001BFD0 86190004 */  lh    $t9, 4($s0)
/* 01CBD4 8001BFD4 44992000 */  mtc1  $t9, $f4
/* 01CBD8 8001BFD8 00000000 */  nop
/* 01CBDC 8001BFDC 468021A0 */  cvt.s.w $f6, $f4
/* 01CBE0 8001BFE0 E626001C */  swc1  $f6, 0x1c($s1)
/* 01CBE4 8001BFE4 8FC80000 */  lw    $t0, ($fp)
/* 01CBE8 8001BFE8 85090000 */  lh    $t1, ($t0)
/* 01CBEC 8001BFEC 0C00DA03 */  jal   func_8003680C
/* 01CBF0 8001BFF0 A629002E */   sh    $t1, 0x2e($s1)
/* 01CBF4 8001BFF4 8FA20054 */  lw    $v0, 0x54($sp)
/* 01CBF8 8001BFF8 26520001 */  addiu $s2, $s2, 1
/* 01CBFC 8001BFFC 24010004 */  li    $at, 4
/* 01CC00 8001C000 26B50DD8 */  addiu $s5, $s5, 0xdd8
/* 01CC04 8001C004 26D60002 */  addiu $s6, $s6, 2
/* 01CC08 8001C008 26940010 */  addiu $s4, $s4, 0x10
/* 01CC0C 8001C00C 26730002 */  addiu $s3, $s3, 2
/* 01CC10 8001C010 26F70004 */  addiu $s7, $s7, 4
/* 01CC14 8001C014 27DE0004 */  addiu $fp, $fp, 4
/* 01CC18 8001C018 24420002 */  addiu $v0, $v0, 2
/* 01CC1C 8001C01C 1641FFB5 */  bne   $s2, $at, .L8001BEF4
/* 01CC20 8001C020 A440FFFE */   sh    $zero, -2($v0)
/* 01CC24 8001C024 8FBF004C */  lw    $ra, 0x4c($sp)
/* 01CC28 8001C028 D7B40018 */  ldc1  $f20, 0x18($sp)
/* 01CC2C 8001C02C D7B60020 */  ldc1  $f22, 0x20($sp)
/* 01CC30 8001C030 8FB00028 */  lw    $s0, 0x28($sp)
/* 01CC34 8001C034 8FB1002C */  lw    $s1, 0x2c($sp)
/* 01CC38 8001C038 8FB20030 */  lw    $s2, 0x30($sp)
/* 01CC3C 8001C03C 8FB30034 */  lw    $s3, 0x34($sp)
/* 01CC40 8001C040 8FB40038 */  lw    $s4, 0x38($sp)
/* 01CC44 8001C044 8FB5003C */  lw    $s5, 0x3c($sp)
/* 01CC48 8001C048 8FB60040 */  lw    $s6, 0x40($sp)
/* 01CC4C 8001C04C 8FB70044 */  lw    $s7, 0x44($sp)
/* 01CC50 8001C050 8FBE0048 */  lw    $fp, 0x48($sp)
/* 01CC54 8001C054 03E00008 */  jr    $ra
/* 01CC58 8001C058 27BD0080 */   addiu $sp, $sp, 0x80
