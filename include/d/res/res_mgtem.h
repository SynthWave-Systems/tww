#ifndef RES_MGTEM_H
#define RES_MGTEM_H

#include "global.h"

#if VERSION == VERSION_JPN
enum MGTEM_RES_FILE_ID { // IDs and indexes are synced
    /* SCRN */
    MGTEM_BLO_SHIP_RACE2=0x4,
    
    /* TIMG */
    MGTEM_BTI_MT_SHIPFONT_A=0x7,
    MGTEM_BTI_MT_SHIPFONT_C_BIG=0x8,
    MGTEM_BTI_MT_SHIPFONT_D=0x9,
    MGTEM_BTI_MT_SHIPFONT_E=0xA,
    MGTEM_BTI_MT_SHIPFONT_EX=0xB,
    MGTEM_BTI_MT_SHIPFONT_E_BIG=0xC,
    MGTEM_BTI_MT_SHIPFONT_F_BIG=0xD,
    MGTEM_BTI_MT_SHIPFONT_G=0xE,
    MGTEM_BTI_MT_SHIPFONT_G_BIG=0xF,
    MGTEM_BTI_MT_SHIPFONT_I=0x10,
    MGTEM_BTI_MT_SHIPFONT_L=0x11,
    MGTEM_BTI_MT_SHIPFONT_M=0x12,
    MGTEM_BTI_MT_SHIPFONT_N=0x13,
    MGTEM_BTI_MT_SHIPFONT_O=0x14,
    MGTEM_BTI_MT_SHIPFONT_P_BIG=0x15,
    MGTEM_BTI_MT_SHIPFONT_R_BIG=0x16,
    MGTEM_BTI_MT_SHIPFONT_T=0x17,
    MGTEM_BTI_MT_SHIPFONT_T_BIG=0x18,
    MGTEM_BTI_MT_SHIPFONT_U=0x19,
    MGTEM_BTI_MT_SHIPFONT_Y_BIG=0x1A,
};
#elif VERSION == VERSION_USA
enum MGTEM_RES_FILE_ID { // IDs and indexes are synced
    /* SCRN */
    MGTEM_BLO_SHIP_RACE2=0x4,
    
    /* TIMG */
    MGTEM_BTI_MT_SHIPFONT_A=0x7,
    MGTEM_BTI_MT_SHIPFONT_APOSTROPHE=0x8,
    MGTEM_BTI_MT_SHIPFONT_C_BIG=0x9,
    MGTEM_BTI_MT_SHIPFONT_D=0xA,
    MGTEM_BTI_MT_SHIPFONT_E=0xB,
    MGTEM_BTI_MT_SHIPFONT_EX=0xC,
    MGTEM_BTI_MT_SHIPFONT_E_BIG=0xD,
    MGTEM_BTI_MT_SHIPFONT_F_BIG=0xE,
    MGTEM_BTI_MT_SHIPFONT_G=0xF,
    MGTEM_BTI_MT_SHIPFONT_G_BIG=0x10,
    MGTEM_BTI_MT_SHIPFONT_I=0x11,
    MGTEM_BTI_MT_SHIPFONT_L=0x12,
    MGTEM_BTI_MT_SHIPFONT_M=0x13,
    MGTEM_BTI_MT_SHIPFONT_N=0x14,
    MGTEM_BTI_MT_SHIPFONT_O=0x15,
    MGTEM_BTI_MT_SHIPFONT_P=0x16,
    MGTEM_BTI_MT_SHIPFONT_P_BIG=0x17,
    MGTEM_BTI_MT_SHIPFONT_R_BIG=0x18,
    MGTEM_BTI_MT_SHIPFONT_S=0x19,
    MGTEM_BTI_MT_SHIPFONT_T=0x1A,
    MGTEM_BTI_MT_SHIPFONT_T_BIG=0x1B,
    MGTEM_BTI_MT_SHIPFONT_U=0x1C,
    MGTEM_BTI_MT_SHIPFONT_Y_BIG=0x1D,
};
#elif VERSION == VERSION_PAL
enum MGTEM_RES_FILE_ID { // IDs and indexes are synced
    /* SCRN */
    MGTEM_BLO_SHIP_RACE2_0=0x4,
    MGTEM_BLO_SHIP_RACE2_1=0x5,
    MGTEM_BLO_SHIP_RACE2_2=0x6,
    MGTEM_BLO_SHIP_RACE2_3=0x7,
    MGTEM_BLO_SHIP_RACE2_4=0x8,
    
    /* TIMG */
    MGTEM_BTI_MT_SHIPFONT_A=0xB,
    MGTEM_BTI_MT_SHIPFONT_A2=0xC,
    MGTEM_BTI_MT_SHIPFONT_APOSTROPHE=0xD,
    MGTEM_BTI_MT_SHIPFONT_A_BIG=0xE,
    MGTEM_BTI_MT_SHIPFONT_B=0xF,
    MGTEM_BTI_MT_SHIPFONT_C=0x10,
    MGTEM_BTI_MT_SHIPFONT_C_BIG=0x11,
    MGTEM_BTI_MT_SHIPFONT_D=0x12,
    MGTEM_BTI_MT_SHIPFONT_D_BIG=0x13,
    MGTEM_BTI_MT_SHIPFONT_E=0x14,
    MGTEM_BTI_MT_SHIPFONT_E2=0x15,
    MGTEM_BTI_MT_SHIPFONT_EX=0x16,
    MGTEM_BTI_MT_SHIPFONT_EX2=0x17,
    MGTEM_BTI_MT_SHIPFONT_E_BIG=0x18,
    MGTEM_BTI_MT_SHIPFONT_F_BIG=0x19,
    MGTEM_BTI_MT_SHIPFONT_G=0x1A,
    MGTEM_BTI_MT_SHIPFONT_G_BIG=0x1B,
    MGTEM_BTI_MT_SHIPFONT_H=0x1C,
    MGTEM_BTI_MT_SHIPFONT_H_BIG=0x1D,
    MGTEM_BTI_MT_SHIPFONT_I=0x1E,
    MGTEM_BTI_MT_SHIPFONT_I_BIG=0x1F,
    MGTEM_BTI_MT_SHIPFONT_K_BIG=0x20,
    MGTEM_BTI_MT_SHIPFONT_L=0x21,
    MGTEM_BTI_MT_SHIPFONT_L_BIG=0x22,
    MGTEM_BTI_MT_SHIPFONT_M=0x23,
    MGTEM_BTI_MT_SHIPFONT_M_BIG=0x24,
    MGTEM_BTI_MT_SHIPFONT_N=0x25,
    MGTEM_BTI_MT_SHIPFONT_O=0x26,
    MGTEM_BTI_MT_SHIPFONT_O_BIG=0x27,
    MGTEM_BTI_MT_SHIPFONT_P=0x28,
    MGTEM_BTI_MT_SHIPFONT_P_BIG=0x29,
    MGTEM_BTI_MT_SHIPFONT_R=0x2A,
    MGTEM_BTI_MT_SHIPFONT_R_BIG=0x2B,
    MGTEM_BTI_MT_SHIPFONT_S=0x2C,
    MGTEM_BTI_MT_SHIPFONT_T=0x2D,
    MGTEM_BTI_MT_SHIPFONT_T_BIG=0x2E,
    MGTEM_BTI_MT_SHIPFONT_U=0x2F,
    MGTEM_BTI_MT_SHIPFONT_V=0x30,
    MGTEM_BTI_MT_SHIPFONT_V_BIG=0x31,
    MGTEM_BTI_MT_SHIPFONT_Y_BIG=0x32,
    MGTEM_BTI_MT_SHIPFONT_Z=0x33,
    MGTEM_BTI_MT_SHIPFONT_Z_BIG=0x34,
};
#endif

#endif /* RES_MGTEM_H */