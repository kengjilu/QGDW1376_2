/**
 ******************************************************************************
 * @file      AFNf1.c
 * @brief     C Source file of AFNf1.c.
 * @details   This file including all API functions's implement of AFNf1.c.
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
 * @brief   ????????????????????????????????
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
AFNF1_FN01(unsigned char dir,
        const unsigned char *pin,
        int len,
        pcallback pcb,
        const char *pline_head,
        const char *pline_end)
{
    int i;
    int plen;
    const char * const type[] =
    {
        "????????",
        "DL/T645-1997",
        "DL/T645-2007",
        "DL/T698.45",
    };

    pcb(pline_head);
    pcb("??????????????????");
    pcb(pline_end);

    sprintf(buf, "%s????????????[%d]:%s%s",
            pline_head, pin[0],
            (pin[0] < 4) ? type[pin[0]] : "????",
            pline_end);
    pcb(buf);

    if (dir == 0)   //????
    {
        plen = (pin[3] << 8) | pin[2];
        sprintf(buf, "%s????????L:%d%s", pline_head, plen, pline_end);
        pcb(buf);

        CHK_APP_LEN(len, 4 + plen);

        pcb(pline_head);
        pcb(" ????????:");
        pcb(pline_end);
        pcb(pline_head);
        for (i = 0; i < plen; i++)
        {
            sprintf(buf, "%02X ", pin[i + 4]);
            pcb(buf);
            if (((i + 1) % 16) == 0)
            {
                pcb(pline_end);
                pcb(pline_head);
            }
        }
        pcb(pline_end);
    }
    else //????
    {
        plen = (pin[2] << 8) | pin[1];
        sprintf(buf, "%s????????L:%d%s", pline_head, plen, pline_end);
        pcb(buf);

        CHK_APP_LEN(len, 3 + plen);

        pcb(pline_head);
        pcb(" ????????:");
        pcb(pline_end);
        pcb(pline_head);
        for (i = 0; i < plen; i++)
        {
            sprintf(buf, "%02X ", pin[i + 3]);
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
 * @brief   ??????????????????????
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
print_AFNf1(unsigned char dir,
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
        case 1: //??????????????????
            return AFNF1_FN01(dir, pin + 2, len - 2, pcb, pline_head, pline_end);
        default:
            break;
    }

    pcb(pline_head);
    pcb("ERROR:????????FN!");
    pcb(pline_end);

    return -ERR_AFN_FN;
}

/*--------------------------------AFNf1.c------------------------------------*/
