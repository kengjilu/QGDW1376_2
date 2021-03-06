/**
 ******************************************************************************
 * @file      AFN13.c
 * @brief     C Source file of AFN13.c.
 * @details   This file including all API functions's implement of AFN13.c.
 * @copyright
 ******************************************************************************
 */
 
/*-----------------------------------------------------------------------------
 Section: Includes
 ----------------------------------------------------------------------------*/
#include <stdio.h>
#include "../inc/GDW1376_2.h"
#include "types.h"
#include "lib.h"
#include "maths.h"

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
/* NONE */

/*-----------------------------------------------------------------------------
 Section: Function Definitions
 ----------------------------------------------------------------------------*/
/**
 ******************************************************************************
 * @brief   ????????????????????????
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
static int
AFN13_FN01(unsigned char dir,
        const unsigned char *pin,
        int len,
        pcallback pcb,
        const char *pline_head,
        const char *pline_end)
{
    int i;
    int pos = 0;
    const char * const type[] =
    {
        "????????",
        "DL/T645-1997",
        "DL/T645-2007",
        "DL/T698.45",
    };

    pcb(pline_head);
    pcb("??????????");
    pcb(pline_end);
    if (dir == 0)   //????
    {
        sprintf(buf, "%s????????????[%d]:%s%s", pline_head, pin[0],
                (pin[0] < 4) ? type[pin[0]] : "????",
                pline_end);
        pcb(buf);

        sprintf(buf, "%s????????????????[%d]:", pline_head, pin[1]);
        pcb(buf);
        switch (pin[1])
        {
            case 0:
                pcb("??????????????????????,????????????????????????????????");
                break;
            case 1:
                pcb("??????????????????????,????????????????????????????????");
                pcb(pline_end);
                pcb(pline_head);
                pcb("??????????????,????????????????????,??????????????????????????;");
                break;
            default:
                pcb("????");
                break;
        }
        pcb(pline_end);

        sprintf(buf, "%s??????????????????[%02X]:%d%s", pline_head, pin[2], pin[2], pline_end);
        pcb(buf);
        if (len < (pin[2] * 6 + 3))
        {
            sprintf(buf, "%s????????????????????????!%s", pline_head,  pline_end);
            pcb(buf);
            return -1;
        }
        for (i = 0; i < pin[2]; i++)
        {
            sprintf(buf, "%s??????????????%d????:[%02X %02X %02X %02X %02X %02X]%s",
                    pline_head, i, pin[i * 6 + 3], pin[i * 6 + 4],
                    pin[i * 6 + 5], pin[i * 6 + 6], pin[i * 6 + 7],
                    pin[i * 6 + 8], pline_end);
            pcb(buf);
        }
        pos = i * 6 + 3;
        sprintf(buf, "%s????????L[%02X]:%d%s", pline_head, pin[pos], pin[pos], pline_end);
        pcb(buf);

        pcb(pline_head);
        pcb(" ????????:");
        pcb(pline_end);
        pcb(pline_head);
        for (i = 0; i < pin[pos]; i++)
        {
            sprintf(buf, "%02X ", pin[i + pos + 1]);
            pcb(buf);
            if (((i + 1) % 16) == 0)
            {
                pcb(pline_end);
                pcb(pline_head);
            }
        }
        pcb(pline_end);

    }
    else    //????
    {
        sprintf(buf, "%s????????????????????????[%02x %02x]:%ds%s", pline_head,
                pin[0], pin[1], pin[0] | ((int)pin[1] << 8), pline_end);
        pcb(buf);
        sprintf(buf, "%s????????????[%d]:%s%s", pline_head, pin[2],
                (pin[2] < 4) ? type[pin[2]] : "????",
                pline_end);
        pcb(buf);
        sprintf(buf, "%s????????L:%d%s", pline_head, pin[3], pline_end);
        pcb(buf);

        pcb(pline_head);
        pcb(" ????????:");
        pcb(pline_end);
        pcb(pline_head);
        for (i = 0; i < pin[3]; i++)
        {
            sprintf(buf, "%02X ", pin[i + pos + 4]);
            pcb(buf);
            if (((i + 1) % 16) == 0)
            {
                pcb(pline_end);
                pcb(pline_head);
            }
        }
        pcb(pline_end);
    }

    return 0;
}

/**
 ******************************************************************************
 * @brief   ??????????????????????????
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
print_AFN13(unsigned char dir,
        const unsigned char *pin,
        int len,
        pcallback pcb,
        const char *pline_head,
        const char *pline_end)
{
    unsigned char DT1 = pin[0];
    unsigned char DT2 = pin[1];
    int fn = get_clear_fn(&DT1, &DT2);

    switch (fn)
    {
        case 1: //??????????
            return AFN13_FN01(dir, pin + 2, len - 2, pcb, pline_head, pline_end);
        default:
            break;
    }

    pcb(pline_head);
    pcb("ERROR:????????FN!");
    pcb(pline_end);

    return -ERR_AFN_FN;
}

/*--------------------------------AFN13.c------------------------------------*/
