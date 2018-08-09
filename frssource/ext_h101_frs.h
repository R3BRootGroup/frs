/********************************************************
 *
 * Structure for ext_data_fetch_event() filling.
 *
 * Do not edit - automatically generated.
 */

#ifndef __GUARD_H101_FRS_EXT_H101_FRS_H__
#define __GUARD_H101_FRS_EXT_H101_FRS_H__

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

typedef struct EXT_STR_h101_FRS_t
{
  /* RAW */
  uint32_t FreeTrig /* [-1,-1] */;
  uint32_t AccTrig /* [-1,-1] */;
  uint32_t Spill /* [-1,-1] */;
  uint32_t ClockoneHz /* [-1,-1] */;
  uint32_t ClocktenHz /* [-1,-1] */;
  uint32_t DeadTime /* [-1,-1] */;
  uint32_t ClockhundredHz /* [-1,-1] */;
  uint32_t SCI1L /* [-1,-1] */;
  uint32_t SCI1R /* [-1,-1] */;
  uint32_t SCI2L /* [-1,-1] */;
  uint32_t SCI2R /* [-1,-1] */;
  uint32_t SCI3L /* [-1,-1] */;
  uint32_t SCI3R /* [-1,-1] */;
  uint32_t SCI4L /* [-1,-1] */;
  uint32_t SCI4R /* [-1,-1] */;
  uint32_t SCI5L /* [-1,-1] */;
  uint32_t SCI5R /* [-1,-1] */;
  uint32_t ICNewCurrent /* [-1,-1] */;
  uint32_t Seeold /* [-1,-1] */;
  uint32_t Seenew /* [-1,-1] */;
  uint32_t ICOldCurrent /* [-1,-1] */;
  uint32_t ICCounter /* [-1,-1] */;
  uint32_t SCIN1 /* [-1,-1] */;
  uint32_t SCIN2 /* [-1,-1] */;
  uint32_t SCIN3 /* [-1,-1] */;
  uint32_t StartExt /* [-1,-1] */;
  uint32_t StopExt /* [-1,-1] */;
  uint32_t SC1LdE /* [0,65535] */;
  uint32_t SC1RdE /* [0,65535] */;
  uint32_t SC1Lt /* [0,16777215] */;
  uint32_t SC1Rt /* [0,16777215] */;
  uint32_t SC2LdE /* [0,65535] */;
  uint32_t SC2RdE /* [0,65535] */;
  uint32_t SC2Lt /* [0,16777215] */;
  uint32_t SC2Rt /* [0,16777215] */;
  uint32_t SC3LdE /* [0,65535] */;
  uint32_t SC3RdE /* [0,65535] */;
  uint32_t SC3Lt /* [0,16777215] */;
  uint32_t SC3Rt /* [0,16777215] */;
  uint32_t SC4LdE /* [0,65535] */;
  uint32_t SC4RdE /* [0,65535] */;
  uint32_t SC4Lt /* [0,16777215] */;
  uint32_t SC4Rt /* [0,16777215] */;
  uint32_t SC5LdE /* [0,65535] */;
  uint32_t SC5RdE /* [0,65535] */;
  uint32_t SC5Lt /* [0,16777215] */;
  uint32_t SC5Rt /* [0,16777215] */;
  uint32_t MUS1A1 /* [0,65535] */;
  uint32_t MUS1A2 /* [0,65535] */;
  uint32_t MUS1A3 /* [0,65535] */;
  uint32_t MUS1A4 /* [0,65535] */;
  uint32_t MUS1A5 /* [0,65535] */;
  uint32_t MUS1A6 /* [0,65535] */;
  uint32_t MUS1A7 /* [0,65535] */;
  uint32_t MUS1A8 /* [0,65535] */;
  uint32_t MUS2A1 /* [0,65535] */;
  uint32_t MUS2A2 /* [0,65535] */;
  uint32_t MUS2A3 /* [0,65535] */;
  uint32_t MUS2A4 /* [0,65535] */;
  uint32_t MUS2A5 /* [0,65535] */;
  uint32_t MUS2A6 /* [0,65535] */;
  uint32_t MUS2A7 /* [0,65535] */;
  uint32_t MUS2A8 /* [0,65535] */;
  uint32_t TPC1A1 /* [0,65535] */;
  uint32_t TPC1A2 /* [0,65535] */;
  uint32_t TPC1A3 /* [0,65535] */;
  uint32_t TPC1A4 /* [0,65535] */;
  uint32_t TPC1AL1 /* [0,65535] */;
  uint32_t TPC1AL2 /* [0,65535] */;
  uint32_t TPC1AR1 /* [0,65535] */;
  uint32_t TPC1AR2 /* [0,65535] */;
  uint32_t TPC1DT1 /* [0,65535] */;
  uint32_t TPC1DT2 /* [0,65535] */;
  uint32_t TPC1DT3 /* [0,65535] */;
  uint32_t TPC1DT4 /* [0,65535] */;
  uint32_t TPC1LT1 /* [0,65535] */;
  uint32_t TPC1LT2 /* [0,65535] */;
  uint32_t TPC1RT1 /* [0,65535] */;
  uint32_t TPC1RT2 /* [0,65535] */;
  uint32_t TPC2A1 /* [0,65535] */;
  uint32_t TPC2A2 /* [0,65535] */;
  uint32_t TPC2A3 /* [0,65535] */;
  uint32_t TPC2A4 /* [0,65535] */;
  uint32_t TPC2AL1 /* [0,65535] */;
  uint32_t TPC2AL2 /* [0,65535] */;
  uint32_t TPC2AR1 /* [0,65535] */;
  uint32_t TPC2AR2 /* [0,65535] */;
  uint32_t TPC2DT1 /* [0,65535] */;
  uint32_t TPC2DT2 /* [0,65535] */;
  uint32_t TPC2DT3 /* [0,65535] */;
  uint32_t TPC2DT4 /* [0,65535] */;
  uint32_t TPC2LT1 /* [0,65535] */;
  uint32_t TPC2LT2 /* [0,65535] */;
  uint32_t TPC2RT1 /* [0,65535] */;
  uint32_t TPC2RT2 /* [0,65535] */;
  uint32_t TPC3A1 /* [0,65535] */;
  uint32_t TPC3A2 /* [0,65535] */;
  uint32_t TPC3A3 /* [0,65535] */;
  uint32_t TPC3A4 /* [0,65535] */;
  uint32_t TPC3AL1 /* [0,65535] */;
  uint32_t TPC3AL2 /* [0,65535] */;
  uint32_t TPC3AR1 /* [0,65535] */;
  uint32_t TPC3AR2 /* [0,65535] */;
  uint32_t TPC3DT1 /* [0,65535] */;
  uint32_t TPC3DT2 /* [0,65535] */;
  uint32_t TPC3DT3 /* [0,65535] */;
  uint32_t TPC3DT4 /* [0,65535] */;
  uint32_t TPC3LT1 /* [0,65535] */;
  uint32_t TPC3LT2 /* [0,65535] */;
  uint32_t TPC3RT1 /* [0,65535] */;
  uint32_t TPC3RT2 /* [0,65535] */;
  uint32_t TPC4A1 /* [0,65535] */;
  uint32_t TPC4A2 /* [0,65535] */;
  uint32_t TPC4A3 /* [0,65535] */;
  uint32_t TPC4A4 /* [0,65535] */;
  uint32_t TPC4AL1 /* [0,65535] */;
  uint32_t TPC4AL2 /* [0,65535] */;
  uint32_t TPC4AR1 /* [0,65535] */;
  uint32_t TPC4AR2 /* [0,65535] */;
  uint32_t TPC4DT1 /* [0,65535] */;
  uint32_t TPC4DT2 /* [0,65535] */;
  uint32_t TPC4DT3 /* [0,65535] */;
  uint32_t TPC4DT4 /* [0,65535] */;
  uint32_t TPC4LT1 /* [0,65535] */;
  uint32_t TPC4LT2 /* [0,65535] */;
  uint32_t TPC4RT1 /* [0,65535] */;
  uint32_t TPC4RT2 /* [0,65535] */;

} EXT_STR_h101_FRS;

/********************************************************
 *
 * Structure with multiple levels of arrays (partially)
 * recovered (recommended):
 */

typedef struct EXT_STR_h101_FRS_onion_t
{
  /* RAW */
  uint32_t FreeTrig;
  uint32_t AccTrig;
  uint32_t Spill;
  uint32_t ClockoneHz;
  uint32_t ClocktenHz;
  uint32_t DeadTime;
  uint32_t ClockhundredHz;
  struct {
    uint32_t L;
    uint32_t R;
  } SCI[5];
  uint32_t ICNewCurrent;
  uint32_t Seeold;
  uint32_t Seenew;
  uint32_t ICOldCurrent;
  uint32_t ICCounter;
  uint32_t SCIN[3];
  uint32_t StartExt;
  uint32_t StopExt;
  struct {
    uint32_t LdE;
    uint32_t RdE;
    uint32_t Lt;
    uint32_t Rt;
  } SC[5];
  struct {
    uint32_t A[8];
  } MUS[2];
  struct {
    uint32_t A[4];
    uint32_t AL[2];
    uint32_t AR[2];
    uint32_t DT[4];
    uint32_t LT[2];
    uint32_t RT[2];
  } TPC[4];

} EXT_STR_h101_FRS_onion;

/*******************************************************/

#define EXT_STR_h101_FRS_ITEMS_INFO(ok,si,offset,struct_t,printerr) do { \
  ok = 1; \
  /* RAW */ \
  EXT_STR_ITEM_INFO    (ok,si,offset,struct_t,printerr,\
                     FreeTrig,                        UINT32,\
                    "FreeTrig"); \
  EXT_STR_ITEM_INFO    (ok,si,offset,struct_t,printerr,\
                     AccTrig,                         UINT32,\
                    "AccTrig"); \
  EXT_STR_ITEM_INFO    (ok,si,offset,struct_t,printerr,\
                     Spill,                           UINT32,\
                    "Spill"); \
  EXT_STR_ITEM_INFO    (ok,si,offset,struct_t,printerr,\
                     ClockoneHz,                      UINT32,\
                    "ClockoneHz"); \
  EXT_STR_ITEM_INFO    (ok,si,offset,struct_t,printerr,\
                     ClocktenHz,                      UINT32,\
                    "ClocktenHz"); \
  EXT_STR_ITEM_INFO    (ok,si,offset,struct_t,printerr,\
                     DeadTime,                        UINT32,\
                    "DeadTime"); \
  EXT_STR_ITEM_INFO    (ok,si,offset,struct_t,printerr,\
                     ClockhundredHz,                  UINT32,\
                    "ClockhundredHz"); \
  EXT_STR_ITEM_INFO    (ok,si,offset,struct_t,printerr,\
                     SCI1L,                           UINT32,\
                    "SCI1L"); \
  EXT_STR_ITEM_INFO    (ok,si,offset,struct_t,printerr,\
                     SCI1R,                           UINT32,\
                    "SCI1R"); \
  EXT_STR_ITEM_INFO    (ok,si,offset,struct_t,printerr,\
                     SCI2L,                           UINT32,\
                    "SCI2L"); \
  EXT_STR_ITEM_INFO    (ok,si,offset,struct_t,printerr,\
                     SCI2R,                           UINT32,\
                    "SCI2R"); \
  EXT_STR_ITEM_INFO    (ok,si,offset,struct_t,printerr,\
                     SCI3L,                           UINT32,\
                    "SCI3L"); \
  EXT_STR_ITEM_INFO    (ok,si,offset,struct_t,printerr,\
                     SCI3R,                           UINT32,\
                    "SCI3R"); \
  EXT_STR_ITEM_INFO    (ok,si,offset,struct_t,printerr,\
                     SCI4L,                           UINT32,\
                    "SCI4L"); \
  EXT_STR_ITEM_INFO    (ok,si,offset,struct_t,printerr,\
                     SCI4R,                           UINT32,\
                    "SCI4R"); \
  EXT_STR_ITEM_INFO    (ok,si,offset,struct_t,printerr,\
                     SCI5L,                           UINT32,\
                    "SCI5L"); \
  EXT_STR_ITEM_INFO    (ok,si,offset,struct_t,printerr,\
                     SCI5R,                           UINT32,\
                    "SCI5R"); \
  EXT_STR_ITEM_INFO    (ok,si,offset,struct_t,printerr,\
                     ICNewCurrent,                    UINT32,\
                    "ICNewCurrent"); \
  EXT_STR_ITEM_INFO    (ok,si,offset,struct_t,printerr,\
                     Seeold,                          UINT32,\
                    "Seeold"); \
  EXT_STR_ITEM_INFO    (ok,si,offset,struct_t,printerr,\
                     Seenew,                          UINT32,\
                    "Seenew"); \
  EXT_STR_ITEM_INFO    (ok,si,offset,struct_t,printerr,\
                     ICOldCurrent,                    UINT32,\
                    "ICOldCurrent"); \
  EXT_STR_ITEM_INFO    (ok,si,offset,struct_t,printerr,\
                     ICCounter,                       UINT32,\
                    "ICCounter"); \
  EXT_STR_ITEM_INFO    (ok,si,offset,struct_t,printerr,\
                     SCIN1,                           UINT32,\
                    "SCIN1"); \
  EXT_STR_ITEM_INFO    (ok,si,offset,struct_t,printerr,\
                     SCIN2,                           UINT32,\
                    "SCIN2"); \
  EXT_STR_ITEM_INFO    (ok,si,offset,struct_t,printerr,\
                     SCIN3,                           UINT32,\
                    "SCIN3"); \
  EXT_STR_ITEM_INFO    (ok,si,offset,struct_t,printerr,\
                     StartExt,                        UINT32,\
                    "StartExt"); \
  EXT_STR_ITEM_INFO    (ok,si,offset,struct_t,printerr,\
                     StopExt,                         UINT32,\
                    "StopExt"); \
  EXT_STR_ITEM_INFO_LIM(ok,si,offset,struct_t,printerr,\
                     SC1LdE,                          UINT32,\
                    "SC1LdE",65535); \
  EXT_STR_ITEM_INFO_LIM(ok,si,offset,struct_t,printerr,\
                     SC1RdE,                          UINT32,\
                    "SC1RdE",65535); \
  EXT_STR_ITEM_INFO_LIM(ok,si,offset,struct_t,printerr,\
                     SC1Lt,                           UINT32,\
                    "SC1Lt",16777215); \
  EXT_STR_ITEM_INFO_LIM(ok,si,offset,struct_t,printerr,\
                     SC1Rt,                           UINT32,\
                    "SC1Rt",16777215); \
  EXT_STR_ITEM_INFO_LIM(ok,si,offset,struct_t,printerr,\
                     SC2LdE,                          UINT32,\
                    "SC2LdE",65535); \
  EXT_STR_ITEM_INFO_LIM(ok,si,offset,struct_t,printerr,\
                     SC2RdE,                          UINT32,\
                    "SC2RdE",65535); \
  EXT_STR_ITEM_INFO_LIM(ok,si,offset,struct_t,printerr,\
                     SC2Lt,                           UINT32,\
                    "SC2Lt",16777215); \
  EXT_STR_ITEM_INFO_LIM(ok,si,offset,struct_t,printerr,\
                     SC2Rt,                           UINT32,\
                    "SC2Rt",16777215); \
  EXT_STR_ITEM_INFO_LIM(ok,si,offset,struct_t,printerr,\
                     SC3LdE,                          UINT32,\
                    "SC3LdE",65535); \
  EXT_STR_ITEM_INFO_LIM(ok,si,offset,struct_t,printerr,\
                     SC3RdE,                          UINT32,\
                    "SC3RdE",65535); \
  EXT_STR_ITEM_INFO_LIM(ok,si,offset,struct_t,printerr,\
                     SC3Lt,                           UINT32,\
                    "SC3Lt",16777215); \
  EXT_STR_ITEM_INFO_LIM(ok,si,offset,struct_t,printerr,\
                     SC3Rt,                           UINT32,\
                    "SC3Rt",16777215); \
  EXT_STR_ITEM_INFO_LIM(ok,si,offset,struct_t,printerr,\
                     SC4LdE,                          UINT32,\
                    "SC4LdE",65535); \
  EXT_STR_ITEM_INFO_LIM(ok,si,offset,struct_t,printerr,\
                     SC4RdE,                          UINT32,\
                    "SC4RdE",65535); \
  EXT_STR_ITEM_INFO_LIM(ok,si,offset,struct_t,printerr,\
                     SC4Lt,                           UINT32,\
                    "SC4Lt",16777215); \
  EXT_STR_ITEM_INFO_LIM(ok,si,offset,struct_t,printerr,\
                     SC4Rt,                           UINT32,\
                    "SC4Rt",16777215); \
  EXT_STR_ITEM_INFO_LIM(ok,si,offset,struct_t,printerr,\
                     SC5LdE,                          UINT32,\
                    "SC5LdE",65535); \
  EXT_STR_ITEM_INFO_LIM(ok,si,offset,struct_t,printerr,\
                     SC5RdE,                          UINT32,\
                    "SC5RdE",65535); \
  EXT_STR_ITEM_INFO_LIM(ok,si,offset,struct_t,printerr,\
                     SC5Lt,                           UINT32,\
                    "SC5Lt",16777215); \
  EXT_STR_ITEM_INFO_LIM(ok,si,offset,struct_t,printerr,\
                     SC5Rt,                           UINT32,\
                    "SC5Rt",16777215); \
  EXT_STR_ITEM_INFO_LIM(ok,si,offset,struct_t,printerr,\
                     MUS1A1,                          UINT32,\
                    "MUS1A1",65535); \
  EXT_STR_ITEM_INFO_LIM(ok,si,offset,struct_t,printerr,\
                     MUS1A2,                          UINT32,\
                    "MUS1A2",65535); \
  EXT_STR_ITEM_INFO_LIM(ok,si,offset,struct_t,printerr,\
                     MUS1A3,                          UINT32,\
                    "MUS1A3",65535); \
  EXT_STR_ITEM_INFO_LIM(ok,si,offset,struct_t,printerr,\
                     MUS1A4,                          UINT32,\
                    "MUS1A4",65535); \
  EXT_STR_ITEM_INFO_LIM(ok,si,offset,struct_t,printerr,\
                     MUS1A5,                          UINT32,\
                    "MUS1A5",65535); \
  EXT_STR_ITEM_INFO_LIM(ok,si,offset,struct_t,printerr,\
                     MUS1A6,                          UINT32,\
                    "MUS1A6",65535); \
  EXT_STR_ITEM_INFO_LIM(ok,si,offset,struct_t,printerr,\
                     MUS1A7,                          UINT32,\
                    "MUS1A7",65535); \
  EXT_STR_ITEM_INFO_LIM(ok,si,offset,struct_t,printerr,\
                     MUS1A8,                          UINT32,\
                    "MUS1A8",65535); \
  EXT_STR_ITEM_INFO_LIM(ok,si,offset,struct_t,printerr,\
                     MUS2A1,                          UINT32,\
                    "MUS2A1",65535); \
  EXT_STR_ITEM_INFO_LIM(ok,si,offset,struct_t,printerr,\
                     MUS2A2,                          UINT32,\
                    "MUS2A2",65535); \
  EXT_STR_ITEM_INFO_LIM(ok,si,offset,struct_t,printerr,\
                     MUS2A3,                          UINT32,\
                    "MUS2A3",65535); \
  EXT_STR_ITEM_INFO_LIM(ok,si,offset,struct_t,printerr,\
                     MUS2A4,                          UINT32,\
                    "MUS2A4",65535); \
  EXT_STR_ITEM_INFO_LIM(ok,si,offset,struct_t,printerr,\
                     MUS2A5,                          UINT32,\
                    "MUS2A5",65535); \
  EXT_STR_ITEM_INFO_LIM(ok,si,offset,struct_t,printerr,\
                     MUS2A6,                          UINT32,\
                    "MUS2A6",65535); \
  EXT_STR_ITEM_INFO_LIM(ok,si,offset,struct_t,printerr,\
                     MUS2A7,                          UINT32,\
                    "MUS2A7",65535); \
  EXT_STR_ITEM_INFO_LIM(ok,si,offset,struct_t,printerr,\
                     MUS2A8,                          UINT32,\
                    "MUS2A8",65535); \
  EXT_STR_ITEM_INFO_LIM(ok,si,offset,struct_t,printerr,\
                     TPC1A1,                          UINT32,\
                    "TPC1A1",65535); \
  EXT_STR_ITEM_INFO_LIM(ok,si,offset,struct_t,printerr,\
                     TPC1A2,                          UINT32,\
                    "TPC1A2",65535); \
  EXT_STR_ITEM_INFO_LIM(ok,si,offset,struct_t,printerr,\
                     TPC1A3,                          UINT32,\
                    "TPC1A3",65535); \
  EXT_STR_ITEM_INFO_LIM(ok,si,offset,struct_t,printerr,\
                     TPC1A4,                          UINT32,\
                    "TPC1A4",65535); \
  EXT_STR_ITEM_INFO_LIM(ok,si,offset,struct_t,printerr,\
                     TPC1AL1,                         UINT32,\
                    "TPC1AL1",65535); \
  EXT_STR_ITEM_INFO_LIM(ok,si,offset,struct_t,printerr,\
                     TPC1AL2,                         UINT32,\
                    "TPC1AL2",65535); \
  EXT_STR_ITEM_INFO_LIM(ok,si,offset,struct_t,printerr,\
                     TPC1AR1,                         UINT32,\
                    "TPC1AR1",65535); \
  EXT_STR_ITEM_INFO_LIM(ok,si,offset,struct_t,printerr,\
                     TPC1AR2,                         UINT32,\
                    "TPC1AR2",65535); \
  EXT_STR_ITEM_INFO_LIM(ok,si,offset,struct_t,printerr,\
                     TPC1DT1,                         UINT32,\
                    "TPC1DT1",65535); \
  EXT_STR_ITEM_INFO_LIM(ok,si,offset,struct_t,printerr,\
                     TPC1DT2,                         UINT32,\
                    "TPC1DT2",65535); \
  EXT_STR_ITEM_INFO_LIM(ok,si,offset,struct_t,printerr,\
                     TPC1DT3,                         UINT32,\
                    "TPC1DT3",65535); \
  EXT_STR_ITEM_INFO_LIM(ok,si,offset,struct_t,printerr,\
                     TPC1DT4,                         UINT32,\
                    "TPC1DT4",65535); \
  EXT_STR_ITEM_INFO_LIM(ok,si,offset,struct_t,printerr,\
                     TPC1LT1,                         UINT32,\
                    "TPC1LT1",65535); \
  EXT_STR_ITEM_INFO_LIM(ok,si,offset,struct_t,printerr,\
                     TPC1LT2,                         UINT32,\
                    "TPC1LT2",65535); \
  EXT_STR_ITEM_INFO_LIM(ok,si,offset,struct_t,printerr,\
                     TPC1RT1,                         UINT32,\
                    "TPC1RT1",65535); \
  EXT_STR_ITEM_INFO_LIM(ok,si,offset,struct_t,printerr,\
                     TPC1RT2,                         UINT32,\
                    "TPC1RT2",65535); \
  EXT_STR_ITEM_INFO_LIM(ok,si,offset,struct_t,printerr,\
                     TPC2A1,                          UINT32,\
                    "TPC2A1",65535); \
  EXT_STR_ITEM_INFO_LIM(ok,si,offset,struct_t,printerr,\
                     TPC2A2,                          UINT32,\
                    "TPC2A2",65535); \
  EXT_STR_ITEM_INFO_LIM(ok,si,offset,struct_t,printerr,\
                     TPC2A3,                          UINT32,\
                    "TPC2A3",65535); \
  EXT_STR_ITEM_INFO_LIM(ok,si,offset,struct_t,printerr,\
                     TPC2A4,                          UINT32,\
                    "TPC2A4",65535); \
  EXT_STR_ITEM_INFO_LIM(ok,si,offset,struct_t,printerr,\
                     TPC2AL1,                         UINT32,\
                    "TPC2AL1",65535); \
  EXT_STR_ITEM_INFO_LIM(ok,si,offset,struct_t,printerr,\
                     TPC2AL2,                         UINT32,\
                    "TPC2AL2",65535); \
  EXT_STR_ITEM_INFO_LIM(ok,si,offset,struct_t,printerr,\
                     TPC2AR1,                         UINT32,\
                    "TPC2AR1",65535); \
  EXT_STR_ITEM_INFO_LIM(ok,si,offset,struct_t,printerr,\
                     TPC2AR2,                         UINT32,\
                    "TPC2AR2",65535); \
  EXT_STR_ITEM_INFO_LIM(ok,si,offset,struct_t,printerr,\
                     TPC2DT1,                         UINT32,\
                    "TPC2DT1",65535); \
  EXT_STR_ITEM_INFO_LIM(ok,si,offset,struct_t,printerr,\
                     TPC2DT2,                         UINT32,\
                    "TPC2DT2",65535); \
  EXT_STR_ITEM_INFO_LIM(ok,si,offset,struct_t,printerr,\
                     TPC2DT3,                         UINT32,\
                    "TPC2DT3",65535); \
  EXT_STR_ITEM_INFO_LIM(ok,si,offset,struct_t,printerr,\
                     TPC2DT4,                         UINT32,\
                    "TPC2DT4",65535); \
  EXT_STR_ITEM_INFO_LIM(ok,si,offset,struct_t,printerr,\
                     TPC2LT1,                         UINT32,\
                    "TPC2LT1",65535); \
  EXT_STR_ITEM_INFO_LIM(ok,si,offset,struct_t,printerr,\
                     TPC2LT2,                         UINT32,\
                    "TPC2LT2",65535); \
  EXT_STR_ITEM_INFO_LIM(ok,si,offset,struct_t,printerr,\
                     TPC2RT1,                         UINT32,\
                    "TPC2RT1",65535); \
  EXT_STR_ITEM_INFO_LIM(ok,si,offset,struct_t,printerr,\
                     TPC2RT2,                         UINT32,\
                    "TPC2RT2",65535); \
  EXT_STR_ITEM_INFO_LIM(ok,si,offset,struct_t,printerr,\
                     TPC3A1,                          UINT32,\
                    "TPC3A1",65535); \
  EXT_STR_ITEM_INFO_LIM(ok,si,offset,struct_t,printerr,\
                     TPC3A2,                          UINT32,\
                    "TPC3A2",65535); \
  EXT_STR_ITEM_INFO_LIM(ok,si,offset,struct_t,printerr,\
                     TPC3A3,                          UINT32,\
                    "TPC3A3",65535); \
  EXT_STR_ITEM_INFO_LIM(ok,si,offset,struct_t,printerr,\
                     TPC3A4,                          UINT32,\
                    "TPC3A4",65535); \
  EXT_STR_ITEM_INFO_LIM(ok,si,offset,struct_t,printerr,\
                     TPC3AL1,                         UINT32,\
                    "TPC3AL1",65535); \
  EXT_STR_ITEM_INFO_LIM(ok,si,offset,struct_t,printerr,\
                     TPC3AL2,                         UINT32,\
                    "TPC3AL2",65535); \
  EXT_STR_ITEM_INFO_LIM(ok,si,offset,struct_t,printerr,\
                     TPC3AR1,                         UINT32,\
                    "TPC3AR1",65535); \
  EXT_STR_ITEM_INFO_LIM(ok,si,offset,struct_t,printerr,\
                     TPC3AR2,                         UINT32,\
                    "TPC3AR2",65535); \
  EXT_STR_ITEM_INFO_LIM(ok,si,offset,struct_t,printerr,\
                     TPC3DT1,                         UINT32,\
                    "TPC3DT1",65535); \
  EXT_STR_ITEM_INFO_LIM(ok,si,offset,struct_t,printerr,\
                     TPC3DT2,                         UINT32,\
                    "TPC3DT2",65535); \
  EXT_STR_ITEM_INFO_LIM(ok,si,offset,struct_t,printerr,\
                     TPC3DT3,                         UINT32,\
                    "TPC3DT3",65535); \
  EXT_STR_ITEM_INFO_LIM(ok,si,offset,struct_t,printerr,\
                     TPC3DT4,                         UINT32,\
                    "TPC3DT4",65535); \
  EXT_STR_ITEM_INFO_LIM(ok,si,offset,struct_t,printerr,\
                     TPC3LT1,                         UINT32,\
                    "TPC3LT1",65535); \
  EXT_STR_ITEM_INFO_LIM(ok,si,offset,struct_t,printerr,\
                     TPC3LT2,                         UINT32,\
                    "TPC3LT2",65535); \
  EXT_STR_ITEM_INFO_LIM(ok,si,offset,struct_t,printerr,\
                     TPC3RT1,                         UINT32,\
                    "TPC3RT1",65535); \
  EXT_STR_ITEM_INFO_LIM(ok,si,offset,struct_t,printerr,\
                     TPC3RT2,                         UINT32,\
                    "TPC3RT2",65535); \
  EXT_STR_ITEM_INFO_LIM(ok,si,offset,struct_t,printerr,\
                     TPC4A1,                          UINT32,\
                    "TPC4A1",65535); \
  EXT_STR_ITEM_INFO_LIM(ok,si,offset,struct_t,printerr,\
                     TPC4A2,                          UINT32,\
                    "TPC4A2",65535); \
  EXT_STR_ITEM_INFO_LIM(ok,si,offset,struct_t,printerr,\
                     TPC4A3,                          UINT32,\
                    "TPC4A3",65535); \
  EXT_STR_ITEM_INFO_LIM(ok,si,offset,struct_t,printerr,\
                     TPC4A4,                          UINT32,\
                    "TPC4A4",65535); \
  EXT_STR_ITEM_INFO_LIM(ok,si,offset,struct_t,printerr,\
                     TPC4AL1,                         UINT32,\
                    "TPC4AL1",65535); \
  EXT_STR_ITEM_INFO_LIM(ok,si,offset,struct_t,printerr,\
                     TPC4AL2,                         UINT32,\
                    "TPC4AL2",65535); \
  EXT_STR_ITEM_INFO_LIM(ok,si,offset,struct_t,printerr,\
                     TPC4AR1,                         UINT32,\
                    "TPC4AR1",65535); \
  EXT_STR_ITEM_INFO_LIM(ok,si,offset,struct_t,printerr,\
                     TPC4AR2,                         UINT32,\
                    "TPC4AR2",65535); \
  EXT_STR_ITEM_INFO_LIM(ok,si,offset,struct_t,printerr,\
                     TPC4DT1,                         UINT32,\
                    "TPC4DT1",65535); \
  EXT_STR_ITEM_INFO_LIM(ok,si,offset,struct_t,printerr,\
                     TPC4DT2,                         UINT32,\
                    "TPC4DT2",65535); \
  EXT_STR_ITEM_INFO_LIM(ok,si,offset,struct_t,printerr,\
                     TPC4DT3,                         UINT32,\
                    "TPC4DT3",65535); \
  EXT_STR_ITEM_INFO_LIM(ok,si,offset,struct_t,printerr,\
                     TPC4DT4,                         UINT32,\
                    "TPC4DT4",65535); \
  EXT_STR_ITEM_INFO_LIM(ok,si,offset,struct_t,printerr,\
                     TPC4LT1,                         UINT32,\
                    "TPC4LT1",65535); \
  EXT_STR_ITEM_INFO_LIM(ok,si,offset,struct_t,printerr,\
                     TPC4LT2,                         UINT32,\
                    "TPC4LT2",65535); \
  EXT_STR_ITEM_INFO_LIM(ok,si,offset,struct_t,printerr,\
                     TPC4RT1,                         UINT32,\
                    "TPC4RT1",65535); \
  EXT_STR_ITEM_INFO_LIM(ok,si,offset,struct_t,printerr,\
                     TPC4RT2,                         UINT32,\
                    "TPC4RT2",65535); \
  \
} while (0);

/********************************************************
 *
 * For internal use by the network data reader:
 * (version checks, etc)
 */

typedef struct EXT_STR_h101_FRS_layout_t
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
  uint32_t _pack_list[127];
} EXT_STR_h101_FRS_layout;

#define EXT_STR_h101_FRS_LAYOUT_INIT { \
  0x57e65c93, \
  sizeof(EXT_STR_h101_FRS_layout), \
  sizeof(EXT_STR_h101_FRS), \
  sizeof(EXT_STR_h101_FRS_onion), \
  127, \
  1, \
  { \
    { 0, sizeof(EXT_STR_h101_FRS), 0x54410eaa, "h101_FRS" }, \
  }, \
  { \
    0x40000000, 0x40000004, 0x40000008, 0x4000000c, \
    0x40000010, 0x40000014, 0x40000018, 0x4000001c, \
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
    0x40000110, 0x40000114, 0x40000118, 0x4000011c, \
    0x40000120, 0x40000124, 0x40000128, 0x4000012c, \
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
    0x400001f0, 0x400001f4, 0x400001f8, \
  } \
};

#endif/*__GUARD_H101_FRS_EXT_H101_FRS_H__*/

/*******************************************************/
