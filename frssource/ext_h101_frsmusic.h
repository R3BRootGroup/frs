/******************************************************************************
 *   Copyright (C) 2019 GSI Helmholtzzentrum für Schwerionenforschung GmbH    *
 *   Copyright (C) 2019 Members of R3B Collaboration                          *
 *                                                                            *
 *             This software is distributed under the terms of the            *
 *                 GNU General Public Licence (GPL) version 3,                *
 *                    copied verbatim in the file "LICENSE".                  *
 *                                                                            *
 * In applying this license GSI does not waive the privileges and immunities  *
 * granted to it by virtue of its status as an Intergovernmental Organization *
 * or submit itself to any jurisdiction.                                      *
 ******************************************************************************/

/********************************************************
 *
 * Structure for ext_data_fetch_event() filling.
 *
 * Do not edit - automatically generated.
 */

#ifndef __GUARD_H101_FRSMUSIC_EXT_H101_FRSMUSIC_H__
#define __GUARD_H101_FRSMUSIC_EXT_H101_FRSMUSIC_H__

#ifndef __CINT__
#include <stdint.h>
#else
/* For CINT (old version trouble with stdint.h): */
#ifndef uint32_t
typedef unsigned int uint32_t;
typedef int int32_t;
#endif
#endif
#ifndef EXT_STRUCT_CTRL
#define EXT_STRUCT_CTRL(x)
#endif

/********************************************************
 *
 * Plain structure (layout as ntuple/root file):
 */

typedef struct EXT_STR_h101_FRSMUSIC_t
{
    /* RAW */
    uint32_t MUS1A /* [0,8] */;
    uint32_t MUS1AI[8 EXT_STRUCT_CTRL(MUS1A)] /* [1,8] */;
    uint32_t MUS1Av[8 EXT_STRUCT_CTRL(MUS1A)] /* [0,65535] */;
    uint32_t MUS2A /* [0,8] */;
    uint32_t MUS2AI[8 EXT_STRUCT_CTRL(MUS2A)] /* [1,8] */;
    uint32_t MUS2Av[8 EXT_STRUCT_CTRL(MUS2A)] /* [0,65535] */;

} EXT_STR_h101_FRSMUSIC;

/********************************************************
 *
 * Structure with multiple levels of arrays (partially)
 * recovered (recommended):
 */

typedef struct EXT_STR_h101_FRSMUSIC_onion_t
{
    /* RAW */
    struct
    {
        uint32_t A;
        uint32_t AI[8 /* A */];
        uint32_t Av[8 /* A */];
    } MUS[2];

} EXT_STR_h101_FRSMUSIC_onion;

/*******************************************************/

#define EXT_STR_h101_FRSMUSIC_ITEMS_INFO(ok, si, offset, struct_t, printerr)                          \
    do                                                                                                \
    {                                                                                                 \
        ok = 1;                                                                                       \
        /* RAW */                                                                                     \
        EXT_STR_ITEM_INFO_LIM(ok, si, offset, struct_t, printerr, MUS1A, UINT32, "MUS1A", 8);         \
        EXT_STR_ITEM_INFO_ZZP(ok, si, offset, struct_t, printerr, MUS1AI, UINT32, "MUS1AI", "MUS1A"); \
        EXT_STR_ITEM_INFO_ZZP(ok, si, offset, struct_t, printerr, MUS1Av, UINT32, "MUS1Av", "MUS1A"); \
        EXT_STR_ITEM_INFO_LIM(ok, si, offset, struct_t, printerr, MUS2A, UINT32, "MUS2A", 8);         \
        EXT_STR_ITEM_INFO_ZZP(ok, si, offset, struct_t, printerr, MUS2AI, UINT32, "MUS2AI", "MUS2A"); \
        EXT_STR_ITEM_INFO_ZZP(ok, si, offset, struct_t, printerr, MUS2Av, UINT32, "MUS2Av", "MUS2A"); \
                                                                                                      \
    } while (0);

/********************************************************
 *
 * For internal use by the network data reader:
 * (version checks, etc)
 */

typedef struct EXT_STR_h101_FRSMUSIC_layout_t
{
    uint32_t _magic;
    uint32_t _size_info;
    uint32_t _size_struct;
    uint32_t _size_struct_onion;
    uint32_t _pack_list_items;

    uint32_t _num_items;
    struct
    {
        uint32_t _offset;
        uint32_t _size;
        uint32_t _xor;
        const char* _name;
    } _items[1];
    uint32_t _pack_list[40];
} EXT_STR_h101_FRSMUSIC_layout;

#define EXT_STR_h101_FRSMUSIC_LAYOUT_INIT                                                                 \
    { 0x57e65c96,                                                                                         \
      sizeof(EXT_STR_h101_FRSMUSIC_layout),                                                               \
      sizeof(EXT_STR_h101_FRSMUSIC),                                                                      \
      sizeof(EXT_STR_h101_FRSMUSIC_onion),                                                                \
      40,                                                                                                 \
      1,                                                                                                  \
      {                                                                                                   \
          { 0, sizeof(EXT_STR_h101_FRSMUSIC), 0x416c16c4, "h101_FRSMUSIC" },                              \
      },                                                                                                  \
      {                                                                                                   \
          0x40000000, 0x40000004, 0xc0000008, 0x00000008, 0x00000002, 0x4000000c, 0x4000002c, 0x40000010, \
          0x40000030, 0x40000014, 0x40000034, 0x40000018, 0x40000038, 0x4000001c, 0x4000003c, 0x40000020, \
          0x40000040, 0x40000024, 0x40000044, 0x40000028, 0x40000048, 0xc000004c, 0x00000008, 0x00000002, \
          0x40000050, 0x40000070, 0x40000054, 0x40000074, 0x40000058, 0x40000078, 0x4000005c, 0x4000007c, \
          0x40000060, 0x40000080, 0x40000064, 0x40000084, 0x40000068, 0x40000088, 0x4000006c, 0x4000008c, \
      } };

#endif /*__GUARD_H101_FRSMUSIC_EXT_H101_FRSMUSIC_H__*/

/*******************************************************/
