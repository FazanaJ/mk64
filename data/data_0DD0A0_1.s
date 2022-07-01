# Mario Kart 64 (U) disassembly and split file
# generated by n64split v0.4a - N64 ROM splitter

.include "macros.inc"

.section .data

#glabel D_800DC710
#.word D_802D2B80

#glabel D_800DC714
#.word D_802DAB80, 0x00000000, 0x00000000

glabel D_800DC720
.word D_0D008F28, D_0D008F80, D_0D008FB8, D_0D009058
.word D_0D0090B8, D_0D0090F8, D_0D009158, D_0D009188
.word D_0D0091E8, D_0D009210, D_0D009238, D_0D009260
.word D_0D009280, D_0D0092C8, D_0D009310, D_0D008F18
.word D_0D008F18, D_0D008F18, D_0D0093C0, D_0D008F18
.word D_0D008F18, 0x00000000

glabel nullPath
.word 0x80000000, 0x00000000

# segmented address of up to four course paths per course
glabel gCoursePathTable
.word D_06005568, nullPath,   nullPath,   nullPath
.word D_06004480, nullPath,   nullPath,   nullPath
.word D_06004F90, nullPath,   nullPath,   nullPath
.word D_06004578, nullPath,   nullPath,   nullPath
.word D_0600D780, D_0600D9C8, D_0600DC18, D_0600DEA8
.word D_060034A0, nullPath,   nullPath,   nullPath
.word D_0600ADE0, nullPath,   nullPath,   nullPath
.word D_0600B5B8, nullPath,   nullPath,   nullPath
.word D_0600A540, nullPath,   nullPath,   nullPath
.word D_0600EC80, nullPath,   nullPath,   nullPath
.word D_06003B80, nullPath,   nullPath,   nullPath
.word D_06006AC8, nullPath,   nullPath,   nullPath
.word D_06004BF8, nullPath,   nullPath,   nullPath
.word D_060019D0, nullPath,   nullPath,   nullPath
.word D_060056A0, nullPath,   nullPath,   nullPath
.word nullPath,   nullPath,   nullPath,   nullPath
.word nullPath,   nullPath,   nullPath,   nullPath
.word nullPath,   nullPath,   nullPath,   nullPath
.word D_060071F0, nullPath,   nullPath,   nullPath
.word nullPath,   nullPath,   nullPath,   nullPath
.word D_0B008AA8, D_0B008B68, D_0B008C20, D_0B008CE0

glabel D_800DC8D0
.word D_060057B0, nullPath,   nullPath,   nullPath
.word D_060047F0, nullPath,   nullPath,   nullPath
.word D_060051D0, nullPath,   nullPath,   nullPath
.word D_060047F0, nullPath,   nullPath,   nullPath
.word D_0600E150, D_0600F680, D_06010B58, D_06012090
.word D_060036E8, nullPath,   nullPath,   nullPath
.word D_0600B1A8, D_0600C4B0, nullPath,   nullPath
.word D_0600B828, nullPath,   nullPath,   nullPath
.word D_0600A6D0, nullPath,   nullPath,   nullPath
.word D_0600EDE8, nullPath,   nullPath,   nullPath
.word D_06003D30, nullPath,   nullPath,   nullPath
.word D_06006EC0, nullPath,   nullPath,   nullPath
.word D_06004DE8, nullPath,   nullPath,   nullPath
.word D_06001CF8, nullPath,   nullPath,   nullPath
.word D_06005908, nullPath,   nullPath,   nullPath
.word nullPath,   nullPath,   nullPath,   nullPath
.word nullPath,   nullPath,   nullPath,   nullPath
.word nullPath,   nullPath,   nullPath,   nullPath
.word D_06007620, nullPath,   nullPath,   nullPath
.word nullPath,   nullPath,   nullPath,   nullPath
.word nullPath,   nullPath,   nullPath,   nullPath

glabel D_800DCA20
.hword 0x0030, 0x0035, 0x0035, 0x0035, 0x0035, 0x0035, 0x0035, 0x0035
.hword 0x0030, 0x0030, 0x0028, 0x0035, 0x0035, 0x0026, 0x0035, 0x0035
.hword 0x0035, 0x0035, 0x0035, 0x0028, 0x0035, 0x0000

glabel D_800DCA4C
.float 50.0, 35.0, 35.0, 40.0
.float 35.0, 50.0, 50.0, 50.0
.float 50.0, 50.0, 50.0, 50.0
.float 50.0, 50.0, 50.0, -1.0
.float -1.0, -1.0, 40.0, -1.0
.float 40.0

glabel D_800DCAA0
.float 0.3, 0.3, 0.2, 0.4
.float 0.0, 0.3, 0.5, 0.4
.float 0.7, 0.5, 0.5, 0.3
.float 0.3, 0.4, 0.6, 0.1
.float 0.5, 0.5, 0.1, 0.5
.float 0.5

glabel D_800DCAF4
.hword 0x0014, 0x0005, 0x000a, 0x000f, 0x0014, 0x0019, 0x001e, 0x0023
.hword 0x001e, 0x0019, 0x0032, 0x004b, 0x0064, 0x007d, 0x0096, 0x00af
.hword 0x0028, 0x001e, 0x003c, 0x005a, 0x0078, 0x0096, 0x00b4, 0x00d2
.hword 0x0032, 0x0028, 0x0050, 0x0078, 0x00a0, 0x00c8, 0x00f0, 0x0118

glabel D_800DCB34
.hword 0x0014, 0x0005, 0x000a, 0x000f, 0x0014, 0x0019, 0x001e, 0x0023
.hword 0x001e, 0x0019, 0x002d, 0x0041, 0x005a, 0x0073, 0x008c, 0x00a5
.hword 0x0028, 0x0003, 0x0006, 0x0010, 0x002e, 0x0031, 0x003b, 0x0059
.hword 0x0032, 0x001e, 0x003c, 0x003f, 0x0049, 0x004e, 0x006c, 0x008a
.hword 0x000a, 0x0005, 0x000a, 0x000f, 0x0014, 0x0019, 0x001e, 0x0023
.hword 0x000a, 0x0005, 0x0005, 0x0005, 0x0005, 0x0005, 0x0005, 0x0005
.hword 0x000a, 0x0005, 0x0005, 0x0005, 0x0005, 0x0005, 0x0005, 0x0005
.hword 0x000a, 0x0005, 0x0005, 0x0005, 0x0005, 0x0005, 0x0005, 0x0005

glabel D_800DCBB4
.word D_800DCB34, D_800DCAF4, D_800DCAF4, D_800DCAF4
.word D_800DCAF4, D_800DCAF4, D_800DCAF4, D_800DCAF4
.word D_800DCAF4, D_800DCAF4, D_800DCAF4, D_800DCAF4
.word D_800DCAF4, D_800DCAF4, D_800DCAF4, D_800DCAF4
.word D_800DCAF4, D_800DCAF4, D_800DCAF4, D_800DCAF4
.word D_800DCAF4

.macro Entry800DCC08 h0, h1, f2, f3, f4, f5, f6
.hword \h0, \h1
.float \f2, \f3, \f4, \f5, \f6
.endm

glabel D_800DCC08
Entry800DCC08 0x0028, 0x0003, 0.8333333, 0.0, 0.0, 0.0, 0.0
Entry800DCC08 0x0064, 0x0003, 0.8333333, 0.0, 0.0, 0.0, 0.0
Entry800DCC08 0x0109, 0x0003, 0.8333333, 0.0, 0.0, 0.0, 0.0
Entry800DCC08 0x011d, 0x0001, 0.8333333, 0.0, 0.0, 0.0, 0.0
Entry800DCC08 0x01a4, 0x0001, 0.8333333, 0.0, 0.0, 0.0, 0.0
Entry800DCC08 0x0000, 0x0000, 0.8333333, 0.0, 0.0, 0.0, 0.0
Entry800DCC08 0x0000, 0x0000, 0.8333333, 0.0, 0.0, 0.0, 0.0
Entry800DCC08 0x008c, 0x0003, 0.8333333, 0.0, 0.0, 0.0, 0.0
Entry800DCC08 0x00a5, 0x0001, 0.8333333, 0.0, 0.0, 0.0, 0.0
Entry800DCC08 0x014a, 0x0003, 0.8333333, 0.0, 0.0, 0.0, 0.0
Entry800DCC08 0x0226, 0x0001, 0.8333333, 0.0, 0.0, 0.0, 0.0
Entry800DCC08 0x0253, 0x0003, 0.8333333, 0.0, 0.0, 0.0, 0.0
Entry800DCC08 0x0000, 0x0000, 0.8333333, 0.0, 0.0, 0.0, 0.0
Entry800DCC08 0x0000, 0x0000, 0.8333333, 0.0, 0.0, 0.0, 0.0
Entry800DCC08 0x0032, 0x0003, 0.8333333, 0.0, 0.0, 0.0, 0.0
Entry800DCC08 0x0096, 0x0001, 0.8333333, 0.0, 0.0, 0.0, 0.0
Entry800DCC08 0x00c8, 0x0003, 0.8333333, 0.0, 0.0, 0.0, 0.0
Entry800DCC08 0x0104, 0x0001, 0.8333333, 0.0, 0.0, 0.0, 0.0
Entry800DCC08 0x01b3, 0x0003, 0.8333333, 0.0, 0.0, 0.0, 0.0
Entry800DCC08 0x0000, 0x0000, 0.8333333, 0.0, 0.0, 0.0, 0.0
Entry800DCC08 0x0000, 0x0000, 0.8333333, 0.0, 0.0, 0.0, 0.0
Entry800DCC08 0x006e, 0x0003, 0.8333333, 0.0, 0.0, 0.0, 0.0
Entry800DCC08 0x00be, 0x0001, 0.8333333, 0.0, 0.0, 0.0, 0.0
Entry800DCC08 0x00fa, 0x0003, 0.8333333, 0.0, 0.0, 0.0, 0.0
Entry800DCC08 0x01db, 0x0001, 0.8333333, 0.0, 0.0, 0.0, 0.0
Entry800DCC08 0x0262, 0x0003, 0.8333333, 0.0, 0.0, 0.0, 0.0
Entry800DCC08 0x0000, 0x0000, 0.8333333, 0.0, 0.0, 0.0, 0.0
Entry800DCC08 0x0000, 0x0000, 0.8333333, 0.0, 0.0, 0.0, 0.0
Entry800DCC08 0x0000, 0x0000, 0.8333333, -1533.0, -682.0, -103.0, 0.0
Entry800DCC08 0x000a, 0x0000, 0.8333333, -1565.0, -619.0, -109.0, 0.0
Entry800DCC08 0x0014, 0x0000, 0.8333333, -1529.0, -579.0, -109.0, 0.0
Entry800DCC08 0x001e, 0x0000, 0.8333333, -1588.0, -534.0, -106.0, 0.0
Entry800DCC08 0x0028, 0x0000, 0.8333333, -1598.0, -207.0, -105.0, 0.0
Entry800DCC08 0x0032, 0x0000, 0.8333333, -1646.0, -147.0, -93.0, 0.0
Entry800DCC08 0x003c, 0x0000, 0.8333333, -2532.0, -445.0, -90.0, 0.0
Entry800DCC08 0x0032, 0x0003, 0.8333333, 0.0, 0.0, 0.0, 0.0
Entry800DCC08 0x0064, 0x0001, 0.8333333, 0.0, 0.0, 0.0, 0.0
Entry800DCC08 0x0096, 0x0003, 0.8333333, 0.0, 0.0, 0.0, 0.0
Entry800DCC08 0x0122, 0x0001, 0.8333333, 0.0, 0.0, 0.0, 0.0
Entry800DCC08 0x015e, 0x0003, 0.8333333, 0.0, 0.0, 0.0, 0.0
Entry800DCC08 0x0000, 0x0000, 0.8333333, 0.0, 0.0, 0.0, 0.0
Entry800DCC08 0x0000, 0x0000, 0.8333333, 0.0, 0.0, 0.0, 0.0
Entry800DCC08 0x003c, 0x0001, 0.8333333, 0.0, 0.0, 0.0, 0.0
Entry800DCC08 0x0078, 0x0001, 0.8333333, 0.0, 0.0, 0.0, 0.0
Entry800DCC08 0x00c8, 0x0003, 0.8333333, 0.0, 0.0, 0.0, 0.0
Entry800DCC08 0x0118, 0x0001, 0.8333333, 0.0, 0.0, 0.0, 0.0
Entry800DCC08 0x01b3, 0x0003, 0.8333333, 0.0, 0.0, 0.0, 0.0
Entry800DCC08 0x0000, 0x0000, 0.8333333, 0.0, 0.0, 0.0, 0.0
Entry800DCC08 0x0000, 0x0000, 0.8333333, 0.0, 0.0, 0.0, 0.0
Entry800DCC08 0x0032, 0x0003, 0.8333333, 0.0, 0.0, 0.0, 0.0
Entry800DCC08 0x0064, 0x0003, 0.8333333, 0.0, 0.0, 0.0, 0.0
Entry800DCC08 0x0128, 0x0003, 0.8333333, 0.0, 0.0, 0.0, 0.0
Entry800DCC08 0x0190, 0x0001, 0.8333333, 0.0, 0.0, 0.0, 0.0
Entry800DCC08 0x02ea, 0x0003, 0.8333333, 0.0, 0.0, 0.0, 0.0
Entry800DCC08 0x0000, 0x0000, 0.8333333, 0.0, 0.0, 0.0, 0.0
Entry800DCC08 0x0000, 0x0000, 0.8333333, 0.0, 0.0, 0.0, 0.0
Entry800DCC08 0x0032, 0x0001, 0.8333333, 0.0, 0.0, 0.0, 0.0
Entry800DCC08 0x00c8, 0x0003, 0.8333333, 0.0, 0.0, 0.0, 0.0
Entry800DCC08 0x0131, 0x0001, 0.8333333, 0.0, 0.0, 0.0, 0.0
Entry800DCC08 0x01b8, 0x0003, 0.8333333, 0.0, 0.0, 0.0, 0.0
Entry800DCC08 0x0203, 0x0003, 0.8333333, 0.0, 0.0, 0.0, 0.0
Entry800DCC08 0x0000, 0x0000, 0.8333333, 0.0, 0.0, 0.0, 0.0
Entry800DCC08 0x0000, 0x0000, 0.8333333, 0.0, 0.0, 0.0, 0.0
Entry800DCC08 0x0032, 0x0003, 0.8333333, 0.0, 0.0, 0.0, 0.0
Entry800DCC08 0x008c, 0x0003, 0.8333333, 0.0, 0.0, 0.0, 0.0
Entry800DCC08 0x00e1, 0x0003, 0.8333333, 0.0, 0.0, 0.0, 0.0
Entry800DCC08 0x013c, 0x0003, 0.8333333, 0.0, 0.0, 0.0, 0.0
Entry800DCC08 0x01b2, 0x0003, 0.8333333, 0.0, 0.0, 0.0, 0.0
Entry800DCC08 0x0000, 0x0000, 0.8333333, 0.0, 0.0, 0.0, 0.0
Entry800DCC08 0x0000, 0x0000, 0.8333333, 0.0, 0.0, 0.0, 0.0
Entry800DCC08 0x0032, 0x0003, 0.8333333, 0.0, 0.0, 0.0, 0.0
Entry800DCC08 0x0064, 0x0001, 0.8333333, 0.0, 0.0, 0.0, 0.0
Entry800DCC08 0x0096, 0x0003, 0.8333333, 0.0, 0.0, 0.0, 0.0
Entry800DCC08 0x00c8, 0x0001, 0.8333333, 0.0, 0.0, 0.0, 0.0
Entry800DCC08 0x00fa, 0x0003, 0.8333333, 0.0, 0.0, 0.0, 0.0
Entry800DCC08 0x0000, 0x0000, 0.8333333, 0.0, 0.0, 0.0, 0.0
Entry800DCC08 0x0000, 0x0000, 0.8333333, 0.0, 0.0, 0.0, 0.0
Entry800DCC08 0x0032, 0x0003, 0.8333333, 0.0, 0.0, 0.0, 0.0
Entry800DCC08 0x008a, 0x0001, 0.8333333, 0.0, 0.0, 0.0, 0.0
Entry800DCC08 0x0118, 0x0003, 0.8333333, 0.0, 0.0, 0.0, 0.0
Entry800DCC08 0x0194, 0x0001, 0.8333333, 0.0, 0.0, 0.0, 0.0
Entry800DCC08 0x01fe, 0x0003, 0.8333333, 0.0, 0.0, 0.0, 0.0
Entry800DCC08 0x0000, 0x0000, 0.8333333, 0.0, 0.0, 0.0, 0.0
Entry800DCC08 0x0000, 0x0000, 0.8333333, 0.0, 0.0, 0.0, 0.0
Entry800DCC08 0x0032, 0x0003, 0.8333333, 0.0, 0.0, 0.0, 0.0
Entry800DCC08 0x0064, 0x0001, 0.8333333, 0.0, 0.0, 0.0, 0.0
Entry800DCC08 0x0096, 0x0003, 0.8333333, 0.0, 0.0, 0.0, 0.0
Entry800DCC08 0x00c8, 0x0001, 0.8333333, 0.0, 0.0, 0.0, 0.0
Entry800DCC08 0x00fa, 0x0003, 0.8333333, 0.0, 0.0, 0.0, 0.0
Entry800DCC08 0x0000, 0x0000, 0.8333333, 0.0, 0.0, 0.0, 0.0
Entry800DCC08 0x0000, 0x0000, 0.8333333, 0.0, 0.0, 0.0, 0.0
Entry800DCC08 0x0032, 0x0003, 0.8333333, 0.0, 0.0, 0.0, 0.0
Entry800DCC08 0x0064, 0x0001, 0.8333333, 0.0, 0.0, 0.0, 0.0
Entry800DCC08 0x0096, 0x0003, 0.8333333, 0.0, 0.0, 0.0, 0.0
Entry800DCC08 0x00c8, 0x0001, 0.8333333, 0.0, 0.0, 0.0, 0.0
Entry800DCC08 0x00fa, 0x0003, 0.8333333, 0.0, 0.0, 0.0, 0.0
Entry800DCC08 0x0000, 0x0000, 0.8333333, 0.0, 0.0, 0.0, 0.0
Entry800DCC08 0x0000, 0x0000, 0.8333333, 0.0, 0.0, 0.0, 0.0
Entry800DCC08 0x0032, 0x0003, 0.8333333, 0.0, 0.0, 0.0, 0.0
Entry800DCC08 0x0064, 0x0001, 0.8333333, 0.0, 0.0, 0.0, 0.0
Entry800DCC08 0x0096, 0x0003, 0.8333333, 0.0, 0.0, 0.0, 0.0
Entry800DCC08 0x00c8, 0x0001, 0.8333333, 0.0, 0.0, 0.0, 0.0
Entry800DCC08 0x00fa, 0x0003, 0.8333333, 0.0, 0.0, 0.0, 0.0
Entry800DCC08 0x0000, 0x0000, 0.8333333, 0.0, 0.0, 0.0, 0.0
Entry800DCC08 0x0000, 0x0000, 0.8333333, 0.0, 0.0, 0.0, 0.0
Entry800DCC08 0x0014, 0x0000, 1.0, 0.0, 0.0, 0.0, 0.0
Entry800DCC08 0x0028, 0x0000, 1.0, 0.0, 0.0, 0.0, 0.0
Entry800DCC08 0x003c, 0x0000, 1.0, 0.0, 0.0, 0.0, 0.0
Entry800DCC08 0x0050, 0x0000, 1.0, 0.0, 0.0, 0.0, 0.0
Entry800DCC08 0x0064, 0x0000, 1.0, 0.0, 0.0, 0.0, 0.0
Entry800DCC08 0x0078, 0x0000, 1.0, 0.0, 0.0, 0.0, 0.0
Entry800DCC08 0x008c, 0x0000, 1.0, 0.0, 0.0, 0.0, 0.0
Entry800DCC08 0x0014, 0x0000, 1.0, 0.0, 0.0, 0.0, 0.0
Entry800DCC08 0x0028, 0x0000, 1.0, 0.0, 0.0, 0.0, 0.0
Entry800DCC08 0x003c, 0x0000, 1.0, 0.0, 0.0, 0.0, 0.0
Entry800DCC08 0x0050, 0x0000, 1.0, 0.0, 0.0, 0.0, 0.0
Entry800DCC08 0x0064, 0x0000, 1.0, 0.0, 0.0, 0.0, 0.0
Entry800DCC08 0x0078, 0x0000, 1.0, 0.0, 0.0, 0.0, 0.0
Entry800DCC08 0x008c, 0x0000, 1.0, 0.0, 0.0, 0.0, 0.0
Entry800DCC08 0x0014, 0x0000, 1.0, 0.0, 0.0, 0.0, 0.0
Entry800DCC08 0x0028, 0x0000, 1.0, 0.0, 0.0, 0.0, 0.0
Entry800DCC08 0x003c, 0x0000, 1.0, 0.0, 0.0, 0.0, 0.0
Entry800DCC08 0x0050, 0x0000, 1.0, 0.0, 0.0, 0.0, 0.0
Entry800DCC08 0x0064, 0x0000, 1.0, 0.0, 0.0, 0.0, 0.0
Entry800DCC08 0x0078, 0x0000, 1.0, 0.0, 0.0, 0.0, 0.0
Entry800DCC08 0x008c, 0x0000, 1.0, 0.0, 0.0, 0.0, 0.0
Entry800DCC08 0x0032, 0x0003, 0.8333333, 0.0, 0.0, 0.0, 0.0
Entry800DCC08 0x0064, 0x0001, 0.8333333, 0.0, 0.0, 0.0, 0.0
Entry800DCC08 0x0096, 0x0003, 0.8333333, 0.0, 0.0, 0.0, 0.0
Entry800DCC08 0x00be, 0x0001, 0.8333333, 0.0, 0.0, 0.0, 0.0
Entry800DCC08 0x00fa, 0x0003, 0.8333333, 0.0, 0.0, 0.0, 0.0
Entry800DCC08 0x0000, 0x0000, 0.8333333, 0.0, 0.0, 0.0, 0.0
Entry800DCC08 0x0000, 0x0000, 0.8333333, 0.0, 0.0, 0.0, 0.0
Entry800DCC08 0x0014, 0x0000, 1.0, 0.0, 0.0, 0.0, 0.0
Entry800DCC08 0x0028, 0x0000, 1.0, 0.0, 0.0, 0.0, 0.0
Entry800DCC08 0x003c, 0x0000, 1.0, 0.0, 0.0, 0.0, 0.0
Entry800DCC08 0x0050, 0x0000, 1.0, 0.0, 0.0, 0.0, 0.0
Entry800DCC08 0x0064, 0x0000, 1.0, 0.0, 0.0, 0.0, 0.0
Entry800DCC08 0x0078, 0x0000, 1.0, 0.0, 0.0, 0.0, 0.0
Entry800DCC08 0x008c, 0x0000, 1.0, 0.0, 0.0, 0.0, 0.0
Entry800DCC08 0x0003, 0x0005, 1.250000, 0.0, 0.0, 0.0, 0.0
Entry800DCC08 0x0028, 0x0000, 1.0, 0.0, 0.0, 0.0, 0.0
Entry800DCC08 0x003c, 0x0000, 1.0, 0.0, 0.0, 0.0, 0.0
Entry800DCC08 0x0050, 0x0000, 1.0, 0.0, 0.0, 0.0, 0.0
Entry800DCC08 0x0064, 0x0000, 1.0, 0.0, 0.0, 0.0, 0.0
Entry800DCC08 0x0078, 0x0000, 1.0, 0.0, 0.0, 0.0, 0.0
Entry800DCC08 0x008c, 0x0000, 1.0, 0.0, 0.0, 0.0, 0.0

glabel D_800DD9D0
.hword 0x0258, 0x0001, 0x0001, 0x0001, 0x0001, 0x0000, 0x0000, 0x0000
.hword 0x02bc, 0x0001, 0x0001, 0x0001, 0x0001, 0x0000, 0x0000, 0x0000
.hword 0x030c, 0x0001, 0x0001, 0x0001, 0x0001, 0x0000, 0x0000, 0x0000
.hword 0x02ee, 0x0001, 0x0001, 0x0001, 0x0001, 0x0000, 0x0000, 0x0000
.hword 0x02b2, 0x02a8, 0x02b2, 0x0320, 0x0001, 0x0000, 0x0000, 0x0000
.hword 0x02ee, 0x0001, 0x0001, 0x0001, 0x0001, 0x0000, 0x0000, 0x0000
.hword 0x02bc, 0x0001, 0x0001, 0x0001, 0x0001, 0x0000, 0x0000, 0x0000
.hword 0x03e8, 0x0001, 0x0001, 0x0001, 0x0001, 0x0000, 0x0000, 0x0000
.hword 0x02da, 0x0001, 0x0001, 0x0001, 0x0001, 0x0000, 0x0000, 0x0000
.hword 0x0230, 0x0001, 0x0001, 0x0001, 0x0001, 0x0000, 0x0000, 0x0000
.hword 0x03e8, 0x0001, 0x0001, 0x0001, 0x0001, 0x0000, 0x0000, 0x0000
.hword 0x02bc, 0x0001, 0x0001, 0x0001, 0x0226, 0x0000, 0x0000, 0x0000
.hword 0x02bc, 0x0001, 0x0001, 0x0001, 0x0001, 0x0000, 0x0000, 0x0000
.hword 0x076c, 0x0001, 0x0001, 0x0001, 0x0001, 0x0000, 0x0000, 0x0000
.hword 0x0640, 0x0001, 0x0001, 0x0001, 0x0001, 0x0000, 0x0000, 0x0000
.hword 0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0x0000, 0x0000, 0x0000
.hword 0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0x0000, 0x0000, 0x0000
.hword 0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0x0000, 0x0000, 0x0000
.hword 0x0370, 0x0001, 0x0001, 0x0001, 0x01f4, 0x0000, 0x0000, 0x0000
.hword 0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0x0000, 0x0000, 0x0000
.hword 0x01f4, 0x01f4, 0x01f4, 0x01f4, 0x0001, 0x0000, 0x0000, 0x0000

glabel D_800DDB20
.word 0x00000000

glabel D_800DDB24
.word 0x00000001

.word 0x00000000, 0x00000000

glabel D_800DDB30
.float 0.4, 0.6, 0.275, 0.3

#glabel camera1 # p1 camera struct pointer
#.word cameras

#glabel camera2 # p2 camera struct pointer
#.word D_801647A8

#glabel camera3 # p3 camera struct pointer
#.word D_80164860

#glabel camera4 # p4 camera struct pointer
#.word D_80164918
