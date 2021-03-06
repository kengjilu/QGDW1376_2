/**
 ******************************************************************************
 * @file      AFN.c
 * @brief     C Source file of AFN.c.
 * @details   This file including all API functions's implement of AFN.c.
 * @copyright
 ******************************************************************************
 */
 
/*-----------------------------------------------------------------------------
 Section: Includes
 ----------------------------------------------------------------------------*/
#include "AFN.h"
#include "../inc/GDW1376_2.h"

/*-----------------------------------------------------------------------------
 Section: Type Definitions
 ----------------------------------------------------------------------------*/
/* NONE */

/*-----------------------------------------------------------------------------
 Section: Constant Definitions
 ----------------------------------------------------------------------------*/
/* NONE */ 

/*-----------------------------------------------------------------------------
 Section: Global Variables
 ----------------------------------------------------------------------------*/
/* NONE */

/*-----------------------------------------------------------------------------
 Section: Local Variables
 ----------------------------------------------------------------------------*/
/* NONE */

/*-----------------------------------------------------------------------------
 Section: Local Function Prototypes
 ----------------------------------------------------------------------------*/
/* NONE */

/*-----------------------------------------------------------------------------
 Section: Global Function Prototypes
 ----------------------------------------------------------------------------*/
extern int
print_AFN00(unsigned char dir,
        const unsigned char *pin,
        int len,
        pcallback pcb,
        const char *pline_head,
        const char *pline_end);

extern int
print_AFN01(unsigned char dir,
        const unsigned char *pin,
        int len,
        pcallback pcb,
        const char *pline_head,
        const char *pline_end);

extern int
print_AFN02(unsigned char dir,
        const unsigned char *pin,
        int len,
        pcallback pcb,
        const char *pline_head,
        const char *pline_end);

extern int
print_AFN03(unsigned char dir,
        const unsigned char *pin,
        int len,
        pcallback pcb,
        const char *pline_head,
        const char *pline_end);

extern int
print_AFN04(unsigned char dir,
        const unsigned char *pin,
        int len,
        pcallback pcb,
        const char *pline_head,
        const char *pline_end);

extern int
print_AFN05(unsigned char dir,
        const unsigned char *pin,
        int len,
        pcallback pcb,
        const char *pline_head,
        const char *pline_end);

extern int
print_AFN06(unsigned char dir,
        const unsigned char *pin,
        int len,
        pcallback pcb,
        const char *pline_head,
        const char *pline_end);

extern int
print_AFN10(unsigned char dir,
        const unsigned char *pin,
        int len,
        pcallback pcb,
        const char *pline_head,
        const char *pline_end);

extern int
print_AFN11(unsigned char dir,
        const unsigned char *pin,
        int len,
        pcallback pcb,
        const char *pline_head,
        const char *pline_end);

extern int
print_AFN12(unsigned char dir,
        const unsigned char *pin,
        int len,
        pcallback pcb,
        const char *pline_head,
        const char *pline_end);

extern int
print_AFN13(unsigned char dir,
        const unsigned char *pin,
        int len,
        pcallback pcb,
        const char *pline_head,
        const char *pline_end);

extern int
print_AFN14(unsigned char dir,
        const unsigned char *pin,
        int len,
        pcallback pcb,
        const char *pline_head,
        const char *pline_end);

extern int
print_AFN15(unsigned char dir,
        const unsigned char *pin,
        int len,
        pcallback pcb,
        const char *pline_head,
        const char *pline_end);

extern int
print_AFNf0(unsigned char dir,
        const unsigned char *pin,
        int len,
        pcallback pcb,
        const char *pline_head,
        const char *pline_end);

extern int
print_AFNf1(unsigned char dir,
        const unsigned char *pin,
        int len,
        pcallback pcb,
        const char *pline_head,
        const char *pline_end);

/*-----------------------------------------------------------------------------
 Section: Function Definitions
 ----------------------------------------------------------------------------*/
/**
 ******************************************************************************
 * @brief   ????????????????????
 * @param[in]   dir         : ????????:1????(????->??????)" 0????(??????->????)
 * @param[in]  *pin         : ????????
 * @param[in]   len         : ??????????????
 * @param[in]  *pcb         : ????????
 * @param[in]  *pline_head  : ??????????????????
 * @param[in]  *pline_end   : ??????????????????
 *
 * @return  0 : ????????
 * @return -1 : ????????
 ******************************************************************************
 */
int
print_AFN(unsigned char dir,
        const unsigned char *pin,
        int len,
        pcallback pcb,
        const char *pline_head,
        const char *pline_end)
{
    switch (pin[0]) //AFN
    {
        case 0x00:  //????/????
            return print_AFN00(dir, pin + 1, len - 1, pcb, pline_head, pline_end);
        case 0x01:  //??????
            return print_AFN01(dir, pin + 1, len - 1, pcb, pline_head, pline_end);
        case 0x02:  //????????
            return print_AFN02(dir, pin + 1, len - 1, pcb, pline_head, pline_end);
        case 0x03:  //????????
            return print_AFN03(dir, pin + 1, len - 1, pcb, pline_head, pline_end);
        case 0x04:  //????????
            return print_AFN04(dir, pin + 1, len - 1, pcb, pline_head, pline_end);
        case 0x05:  //????????
            return print_AFN05(dir, pin + 1, len - 1, pcb, pline_head, pline_end);
        case 0x06:  //????????
            return print_AFN06(dir, pin + 1, len - 1, pcb, pline_head, pline_end);
        case 0x10:  //????????
            return print_AFN10(dir, pin + 1, len - 1, pcb, pline_head, pline_end);
        case 0x11:  //????????
            return print_AFN11(dir, pin + 1, len - 1, pcb, pline_head, pline_end);
        case 0x12:  //????????
            return print_AFN12(dir, pin + 1, len - 1, pcb, pline_head, pline_end);
        case 0x13:  //????????????
            return print_AFN13(dir, pin + 1, len - 1, pcb, pline_head, pline_end);
        case 0x14:  //????????????
            return print_AFN14(dir, pin + 1, len - 1, pcb, pline_head, pline_end);
        case 0x15:  //????????
            return print_AFN15(dir, pin + 1, len - 1, pcb, pline_head, pline_end);
        case 0xf0:  //????????
            return print_AFNf0(dir, pin + 1, len - 1, pcb, pline_head, pline_end);
        case 0xf1:  //????????
            return print_AFNf1(dir, pin + 1, len - 1, pcb, pline_head, pline_end);
        default:
            break;
    }
    return -1;
}

/*---------------------------------AFN.c-------------------------------------*/
