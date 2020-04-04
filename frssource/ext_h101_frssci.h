/********************************************************
 *
 * Structure for ext_data_fetch_event() filling.
 *
 * Do not edit - automatically generated.
 */

#ifndef __GUARD_H101_FRSSCI_EXT_H101_FRSSCI_H__
#define __GUARD_H101_FRSSCI_EXT_H101_FRSSCI_H__

#ifndef __CINT__
# include <stdint.h>
#else
/* For CINT (old version trouble with stdint.h): */
# ifndef uint32_t
typedef unsigned int uint32_t;
typedef          int  int32_t;
# endif
#endif
#ifndef EXT_STRUCT_CTRL
# define EXT_STRUCT_CTRL(x)
#endif

/********************************************************
 *
 * Plain structure (layout as ntuple/root file):
 */

typedef struct EXT_STR_h101_frssci_t
{
  /* RAW */
  uint32_t FRSSCI1TFM /* [1,2] */;
  uint32_t FRSSCI1TFMI[2 EXT_STRUCT_CTRL(FRSSCI1TFM)] /* [1,2] */;
  uint32_t FRSSCI1TFME[2 EXT_STRUCT_CTRL(FRSSCI1TFM)] /* [1,60] */;
  uint32_t FRSSCI1TF /* [0,60] */;
  uint32_t FRSSCI1TFv[60 EXT_STRUCT_CTRL(FRSSCI1TF)] /* [0,65535] */;
  uint32_t FRSSCI1TCM /* [1,2] */;
  uint32_t FRSSCI1TCMI[2 EXT_STRUCT_CTRL(FRSSCI1TCM)] /* [1,2] */;
  uint32_t FRSSCI1TCME[2 EXT_STRUCT_CTRL(FRSSCI1TCM)] /* [1,60] */;
  uint32_t FRSSCI1TC /* [0,60] */;
  uint32_t FRSSCI1TCv[60 EXT_STRUCT_CTRL(FRSSCI1TC)] /* [0,65535] */;
  uint32_t FRSSCI2TFM /* [1,2] */;
  uint32_t FRSSCI2TFMI[2 EXT_STRUCT_CTRL(FRSSCI2TFM)] /* [1,2] */;
  uint32_t FRSSCI2TFME[2 EXT_STRUCT_CTRL(FRSSCI2TFM)] /* [1,60] */;
  uint32_t FRSSCI2TF /* [0,60] */;
  uint32_t FRSSCI2TFv[60 EXT_STRUCT_CTRL(FRSSCI2TF)] /* [0,65535] */;
  uint32_t FRSSCI2TCM /* [1,2] */;
  uint32_t FRSSCI2TCMI[2 EXT_STRUCT_CTRL(FRSSCI2TCM)] /* [1,2] */;
  uint32_t FRSSCI2TCME[2 EXT_STRUCT_CTRL(FRSSCI2TCM)] /* [1,60] */;
  uint32_t FRSSCI2TC /* [0,60] */;
  uint32_t FRSSCI2TCv[60 EXT_STRUCT_CTRL(FRSSCI2TC)] /* [0,65535] */;
  uint32_t FRSSCI3TFM /* [1,2] */;
  uint32_t FRSSCI3TFMI[2 EXT_STRUCT_CTRL(FRSSCI3TFM)] /* [1,2] */;
  uint32_t FRSSCI3TFME[2 EXT_STRUCT_CTRL(FRSSCI3TFM)] /* [1,60] */;
  uint32_t FRSSCI3TF /* [0,60] */;
  uint32_t FRSSCI3TFv[60 EXT_STRUCT_CTRL(FRSSCI3TF)] /* [0,65535] */;
  uint32_t FRSSCI3TCM /* [1,2] */;
  uint32_t FRSSCI3TCMI[2 EXT_STRUCT_CTRL(FRSSCI3TCM)] /* [1,2] */;
  uint32_t FRSSCI3TCME[2 EXT_STRUCT_CTRL(FRSSCI3TCM)] /* [1,60] */;
  uint32_t FRSSCI3TC /* [0,60] */;
  uint32_t FRSSCI3TCv[60 EXT_STRUCT_CTRL(FRSSCI3TC)] /* [0,65535] */;

} EXT_STR_h101_frssci;

/********************************************************
 *
 * Structure with multiple levels of arrays (partially)
 * recovered (recommended):
 */

typedef struct EXT_STR_h101_frssci_onion_t
{
  /* RAW */
  struct {
    uint32_t TFM;
    uint32_t TFMI[2 /* TFM */];
    uint32_t TFME[2 /* TFM */];
    uint32_t TF;
    uint32_t TFv[60 /* TF */];
    uint32_t TCM;
    uint32_t TCMI[2 /* TCM */];
    uint32_t TCME[2 /* TCM */];
    uint32_t TC;
    uint32_t TCv[60 /* TC */];
  } FRSSCI[3];

} EXT_STR_h101_frssci_onion;

/*******************************************************/

#define EXT_STR_h101_frssci_ITEMS_INFO(ok,si,offset,struct_t,printerr) do { \
  ok = 1; \
  /* RAW */ \
  EXT_STR_ITEM_INFO_LIM(ok,si,offset,struct_t,printerr,\
                     FRSSCI1TFM,                      UINT32,\
                    "FRSSCI1TFM",2); \
  EXT_STR_ITEM_INFO_ZZP(ok,si,offset,struct_t,printerr,\
                     FRSSCI1TFMI,                     UINT32,\
                    "FRSSCI1TFMI",                     "FRSSCI1TFM"); \
  EXT_STR_ITEM_INFO_ZZP(ok,si,offset,struct_t,printerr,\
                     FRSSCI1TFME,                     UINT32,\
                    "FRSSCI1TFME",                     "FRSSCI1TFM"); \
  EXT_STR_ITEM_INFO_LIM(ok,si,offset,struct_t,printerr,\
                     FRSSCI1TF,                       UINT32,\
                    "FRSSCI1TF",60); \
  EXT_STR_ITEM_INFO_ZZP(ok,si,offset,struct_t,printerr,\
                     FRSSCI1TFv,                      UINT32,\
                    "FRSSCI1TFv",                      "FRSSCI1TF"); \
  EXT_STR_ITEM_INFO_LIM(ok,si,offset,struct_t,printerr,\
                     FRSSCI1TCM,                      UINT32,\
                    "FRSSCI1TCM",2); \
  EXT_STR_ITEM_INFO_ZZP(ok,si,offset,struct_t,printerr,\
                     FRSSCI1TCMI,                     UINT32,\
                    "FRSSCI1TCMI",                     "FRSSCI1TCM"); \
  EXT_STR_ITEM_INFO_ZZP(ok,si,offset,struct_t,printerr,\
                     FRSSCI1TCME,                     UINT32,\
                    "FRSSCI1TCME",                     "FRSSCI1TCM"); \
  EXT_STR_ITEM_INFO_LIM(ok,si,offset,struct_t,printerr,\
                     FRSSCI1TC,                       UINT32,\
                    "FRSSCI1TC",60); \
  EXT_STR_ITEM_INFO_ZZP(ok,si,offset,struct_t,printerr,\
                     FRSSCI1TCv,                      UINT32,\
                    "FRSSCI1TCv",                      "FRSSCI1TC"); \
  EXT_STR_ITEM_INFO_LIM(ok,si,offset,struct_t,printerr,\
                     FRSSCI2TFM,                      UINT32,\
                    "FRSSCI2TFM",2); \
  EXT_STR_ITEM_INFO_ZZP(ok,si,offset,struct_t,printerr,\
                     FRSSCI2TFMI,                     UINT32,\
                    "FRSSCI2TFMI",                     "FRSSCI2TFM"); \
  EXT_STR_ITEM_INFO_ZZP(ok,si,offset,struct_t,printerr,\
                     FRSSCI2TFME,                     UINT32,\
                    "FRSSCI2TFME",                     "FRSSCI2TFM"); \
  EXT_STR_ITEM_INFO_LIM(ok,si,offset,struct_t,printerr,\
                     FRSSCI2TF,                       UINT32,\
                    "FRSSCI2TF",60); \
  EXT_STR_ITEM_INFO_ZZP(ok,si,offset,struct_t,printerr,\
                     FRSSCI2TFv,                      UINT32,\
                    "FRSSCI2TFv",                      "FRSSCI2TF"); \
  EXT_STR_ITEM_INFO_LIM(ok,si,offset,struct_t,printerr,\
                     FRSSCI2TCM,                      UINT32,\
                    "FRSSCI2TCM",2); \
  EXT_STR_ITEM_INFO_ZZP(ok,si,offset,struct_t,printerr,\
                     FRSSCI2TCMI,                     UINT32,\
                    "FRSSCI2TCMI",                     "FRSSCI2TCM"); \
  EXT_STR_ITEM_INFO_ZZP(ok,si,offset,struct_t,printerr,\
                     FRSSCI2TCME,                     UINT32,\
                    "FRSSCI2TCME",                     "FRSSCI2TCM"); \
  EXT_STR_ITEM_INFO_LIM(ok,si,offset,struct_t,printerr,\
                     FRSSCI2TC,                       UINT32,\
                    "FRSSCI2TC",60); \
  EXT_STR_ITEM_INFO_ZZP(ok,si,offset,struct_t,printerr,\
                     FRSSCI2TCv,                      UINT32,\
                    "FRSSCI2TCv",                      "FRSSCI2TC"); \
  EXT_STR_ITEM_INFO_LIM(ok,si,offset,struct_t,printerr,\
                     FRSSCI3TFM,                      UINT32,\
                    "FRSSCI3TFM",2); \
  EXT_STR_ITEM_INFO_ZZP(ok,si,offset,struct_t,printerr,\
                     FRSSCI3TFMI,                     UINT32,\
                    "FRSSCI3TFMI",                     "FRSSCI3TFM"); \
  EXT_STR_ITEM_INFO_ZZP(ok,si,offset,struct_t,printerr,\
                     FRSSCI3TFME,                     UINT32,\
                    "FRSSCI3TFME",                     "FRSSCI3TFM"); \
  EXT_STR_ITEM_INFO_LIM(ok,si,offset,struct_t,printerr,\
                     FRSSCI3TF,                       UINT32,\
                    "FRSSCI3TF",60); \
  EXT_STR_ITEM_INFO_ZZP(ok,si,offset,struct_t,printerr,\
                     FRSSCI3TFv,                      UINT32,\
                    "FRSSCI3TFv",                      "FRSSCI3TF"); \
  EXT_STR_ITEM_INFO_LIM(ok,si,offset,struct_t,printerr,\
                     FRSSCI3TCM,                      UINT32,\
                    "FRSSCI3TCM",2); \
  EXT_STR_ITEM_INFO_ZZP(ok,si,offset,struct_t,printerr,\
                     FRSSCI3TCMI,                     UINT32,\
                    "FRSSCI3TCMI",                     "FRSSCI3TCM"); \
  EXT_STR_ITEM_INFO_ZZP(ok,si,offset,struct_t,printerr,\
                     FRSSCI3TCME,                     UINT32,\
                    "FRSSCI3TCME",                     "FRSSCI3TCM"); \
  EXT_STR_ITEM_INFO_LIM(ok,si,offset,struct_t,printerr,\
                     FRSSCI3TC,                       UINT32,\
                    "FRSSCI3TC",60); \
  EXT_STR_ITEM_INFO_ZZP(ok,si,offset,struct_t,printerr,\
                     FRSSCI3TCv,                      UINT32,\
                    "FRSSCI3TCv",                      "FRSSCI3TC"); \
  \
} while (0);

/********************************************************
 *
 * For internal use by the network data reader:
 * (version checks, etc)
 */

typedef struct EXT_STR_h101_frssci_layout_t
{
  uint32_t _magic;
  uint32_t _size_info;
  uint32_t _size_struct;
  uint32_t _size_struct_onion;
  uint32_t _pack_list_items;

  uint32_t _num_items;
  struct {
    uint32_t _offset;
    uint32_t _size;
    uint32_t _xor;
    const char *_name;
  } _items[1];
  uint32_t _pack_list[422];
} EXT_STR_h101_frssci_layout;

#define EXT_STR_h101_frssci_LAYOUT_INIT { \
  0x57e65c96, \
  sizeof(EXT_STR_h101_frssci_layout), \
  sizeof(EXT_STR_h101_frssci), \
  sizeof(EXT_STR_h101_frssci_onion), \
  422, \
  1, \
  { \
    { 0, sizeof(EXT_STR_h101_frssci), 0x62678572, "h101_frssci" }, \
  }, \
  { \
    0x40000000, 0x40000004, 0xc0000008, 0x00000002, \
    0x00000002, 0x4000000c, 0x40000014, 0x40000010, \
    0x40000018, 0xc000001c, 0x0000003c, 0x00000001, \
    0x40000020, 0x40000024, 0x40000028, 0x4000002c, \
    0x40000030, 0x40000034, 0x40000038, 0x4000003c, \
    0x40000040, 0x40000044, 0x40000048, 0x4000004c, \
    0x40000050, 0x40000054, 0x40000058, 0x4000005c, \
    0x40000060, 0x40000064, 0x40000068, 0x4000006c, \
    0x40000070, 0x40000074, 0x40000078, 0x4000007c, \
    0x40000080, 0x40000084, 0x40000088, 0x4000008c, \
    0x40000090, 0x40000094, 0x40000098, 0x4000009c, \
    0x400000a0, 0x400000a4, 0x400000a8, 0x400000ac, \
    0x400000b0, 0x400000b4, 0x400000b8, 0x400000bc, \
    0x400000c0, 0x400000c4, 0x400000c8, 0x400000cc, \
    0x400000d0, 0x400000d4, 0x400000d8, 0x400000dc, \
    0x400000e0, 0x400000e4, 0x400000e8, 0x400000ec, \
    0x400000f0, 0x400000f4, 0x400000f8, 0x400000fc, \
    0x40000100, 0x40000104, 0x40000108, 0x4000010c, \
    0xc0000110, 0x00000002, 0x00000002, 0x40000114, \
    0x4000011c, 0x40000118, 0x40000120, 0xc0000124, \
    0x0000003c, 0x00000001, 0x40000128, 0x4000012c, \
    0x40000130, 0x40000134, 0x40000138, 0x4000013c, \
    0x40000140, 0x40000144, 0x40000148, 0x4000014c, \
    0x40000150, 0x40000154, 0x40000158, 0x4000015c, \
    0x40000160, 0x40000164, 0x40000168, 0x4000016c, \
    0x40000170, 0x40000174, 0x40000178, 0x4000017c, \
    0x40000180, 0x40000184, 0x40000188, 0x4000018c, \
    0x40000190, 0x40000194, 0x40000198, 0x4000019c, \
    0x400001a0, 0x400001a4, 0x400001a8, 0x400001ac, \
    0x400001b0, 0x400001b4, 0x400001b8, 0x400001bc, \
    0x400001c0, 0x400001c4, 0x400001c8, 0x400001cc, \
    0x400001d0, 0x400001d4, 0x400001d8, 0x400001dc, \
    0x400001e0, 0x400001e4, 0x400001e8, 0x400001ec, \
    0x400001f0, 0x400001f4, 0x400001f8, 0x400001fc, \
    0x40000200, 0x40000204, 0x40000208, 0x4000020c, \
    0x40000210, 0x40000214, 0xc0000218, 0x00000002, \
    0x00000002, 0x4000021c, 0x40000224, 0x40000220, \
    0x40000228, 0xc000022c, 0x0000003c, 0x00000001, \
    0x40000230, 0x40000234, 0x40000238, 0x4000023c, \
    0x40000240, 0x40000244, 0x40000248, 0x4000024c, \
    0x40000250, 0x40000254, 0x40000258, 0x4000025c, \
    0x40000260, 0x40000264, 0x40000268, 0x4000026c, \
    0x40000270, 0x40000274, 0x40000278, 0x4000027c, \
    0x40000280, 0x40000284, 0x40000288, 0x4000028c, \
    0x40000290, 0x40000294, 0x40000298, 0x4000029c, \
    0x400002a0, 0x400002a4, 0x400002a8, 0x400002ac, \
    0x400002b0, 0x400002b4, 0x400002b8, 0x400002bc, \
    0x400002c0, 0x400002c4, 0x400002c8, 0x400002cc, \
    0x400002d0, 0x400002d4, 0x400002d8, 0x400002dc, \
    0x400002e0, 0x400002e4, 0x400002e8, 0x400002ec, \
    0x400002f0, 0x400002f4, 0x400002f8, 0x400002fc, \
    0x40000300, 0x40000304, 0x40000308, 0x4000030c, \
    0x40000310, 0x40000314, 0x40000318, 0x4000031c, \
    0xc0000320, 0x00000002, 0x00000002, 0x40000324, \
    0x4000032c, 0x40000328, 0x40000330, 0xc0000334, \
    0x0000003c, 0x00000001, 0x40000338, 0x4000033c, \
    0x40000340, 0x40000344, 0x40000348, 0x4000034c, \
    0x40000350, 0x40000354, 0x40000358, 0x4000035c, \
    0x40000360, 0x40000364, 0x40000368, 0x4000036c, \
    0x40000370, 0x40000374, 0x40000378, 0x4000037c, \
    0x40000380, 0x40000384, 0x40000388, 0x4000038c, \
    0x40000390, 0x40000394, 0x40000398, 0x4000039c, \
    0x400003a0, 0x400003a4, 0x400003a8, 0x400003ac, \
    0x400003b0, 0x400003b4, 0x400003b8, 0x400003bc, \
    0x400003c0, 0x400003c4, 0x400003c8, 0x400003cc, \
    0x400003d0, 0x400003d4, 0x400003d8, 0x400003dc, \
    0x400003e0, 0x400003e4, 0x400003e8, 0x400003ec, \
    0x400003f0, 0x400003f4, 0x400003f8, 0x400003fc, \
    0x40000400, 0x40000404, 0x40000408, 0x4000040c, \
    0x40000410, 0x40000414, 0x40000418, 0x4000041c, \
    0x40000420, 0x40000424, 0xc0000428, 0x00000002, \
    0x00000002, 0x4000042c, 0x40000434, 0x40000430, \
    0x40000438, 0xc000043c, 0x0000003c, 0x00000001, \
    0x40000440, 0x40000444, 0x40000448, 0x4000044c, \
    0x40000450, 0x40000454, 0x40000458, 0x4000045c, \
    0x40000460, 0x40000464, 0x40000468, 0x4000046c, \
    0x40000470, 0x40000474, 0x40000478, 0x4000047c, \
    0x40000480, 0x40000484, 0x40000488, 0x4000048c, \
    0x40000490, 0x40000494, 0x40000498, 0x4000049c, \
    0x400004a0, 0x400004a4, 0x400004a8, 0x400004ac, \
    0x400004b0, 0x400004b4, 0x400004b8, 0x400004bc, \
    0x400004c0, 0x400004c4, 0x400004c8, 0x400004cc, \
    0x400004d0, 0x400004d4, 0x400004d8, 0x400004dc, \
    0x400004e0, 0x400004e4, 0x400004e8, 0x400004ec, \
    0x400004f0, 0x400004f4, 0x400004f8, 0x400004fc, \
    0x40000500, 0x40000504, 0x40000508, 0x4000050c, \
    0x40000510, 0x40000514, 0x40000518, 0x4000051c, \
    0x40000520, 0x40000524, 0x40000528, 0x4000052c, \
    0xc0000530, 0x00000002, 0x00000002, 0x40000534, \
    0x4000053c, 0x40000538, 0x40000540, 0xc0000544, \
    0x0000003c, 0x00000001, 0x40000548, 0x4000054c, \
    0x40000550, 0x40000554, 0x40000558, 0x4000055c, \
    0x40000560, 0x40000564, 0x40000568, 0x4000056c, \
    0x40000570, 0x40000574, 0x40000578, 0x4000057c, \
    0x40000580, 0x40000584, 0x40000588, 0x4000058c, \
    0x40000590, 0x40000594, 0x40000598, 0x4000059c, \
    0x400005a0, 0x400005a4, 0x400005a8, 0x400005ac, \
    0x400005b0, 0x400005b4, 0x400005b8, 0x400005bc, \
    0x400005c0, 0x400005c4, 0x400005c8, 0x400005cc, \
    0x400005d0, 0x400005d4, 0x400005d8, 0x400005dc, \
    0x400005e0, 0x400005e4, 0x400005e8, 0x400005ec, \
    0x400005f0, 0x400005f4, 0x400005f8, 0x400005fc, \
    0x40000600, 0x40000604, 0x40000608, 0x4000060c, \
    0x40000610, 0x40000614, 0x40000618, 0x4000061c, \
    0x40000620, 0x40000624, 0x40000628, 0x4000062c, \
    0x40000630, 0x40000634, \
  } \
};

#endif/*__GUARD_H101_FRSSCI_EXT_H101_FRSSCI_H__*/

/*******************************************************/
