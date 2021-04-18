/**
 ******************************************************************************
 * @file      AFN00.c
 * @brief     C Source file of AFN00.c.
 * @details   This file including all API functions's implement of AFN00.c.
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
 * @brief   ���ȷ�Ͻ����ַ���
 * @param[in]   dir         : ���䷽��:1����(ģ��->������)" 0����(������->ģ��)
 * @param[in]  *pin         : ���뱨��
 * @param[in]   len         : Ӧ�ò㱨�ĳ���
 * @param[in]  *pcb         : �ص�����
 * @param[in]  *pline_head  : ÿ����ʼ����ַ���
 * @param[in]  *pline_end   : ÿ�н�������ַ���
 *
 * @retval  ����������
 ******************************************************************************
 */
static int
AFN00_FN01(unsigned char dir,
        const unsigned char *pin,
        int len,
        pcallback pcb,
        const char *pline_head,
        const char *pline_end)
{
    int i;

    CHK_APP_LEN(len, 6);

    pcb(pline_head);
    pcb("ȷ�ϱ���:");
    pcb(pline_end);
    sprintf(buf, "%s����ִ��״̬[%d]:%s����%s", pline_head, BITS(pin[0], 0),
            BITS(pin[0], 0) ? "��" : "δ", pline_end);
    pcb(buf);

    pcb(pline_head);
    pcb("�ŵ�״̬: ");
    for (i = 1; i < 8; i++)
    {
        sprintf(buf, "%d:%s ", i, BITS(pin[0], i) ? "��" : "æ");
        pcb(buf);
    }
    pcb(pline_end);
    for (i = 0; i < 8; i++)
    {
        sprintf(buf, "%d:%s ", i + 8, BITS(pin[1], i) ? "��" : "æ");
        pcb(buf);
    }
    pcb(pline_end);
    for (i = 0; i < 8; i++)
    {
        sprintf(buf, "%d:%s ", i + 16, BITS(pin[2], i) ? "��" : "æ");
        pcb(buf);
    }
    pcb(pline_end);
    for (i = 0; i < 8; i++)
    {
        sprintf(buf, "%d:%s ", i + 24, BITS(pin[3], i) ? "��" : "æ");
        pcb(buf);
    }
    pcb(pline_end);

    sprintf(buf, "%s�ȴ�ʱ��(��λs):%d%s", pline_head,
            pin[4] | (((int)pin[5]) << 8), pline_end);
    pcb(buf);
    pcb(pline_end);

    return ERR_NONE;
}

/**
 ******************************************************************************
 * @brief   ������Ͻ����ַ���
 * @param[in]   dir         : ���䷽��:1����(ģ��->������)" 0����(������->ģ��)
 * @param[in]  *pin         : ���뱨��
 * @param[in]   len         : Ӧ�ò㱨�ĳ���
 * @param[in]  *pcb         : �ص�����
 * @param[in]  *pline_head  : ÿ����ʼ����ַ���
 * @param[in]  *pline_end   : ÿ�н�������ַ���
 *
 * @retval  ����������
 ******************************************************************************
 */
static int
AFN00_FN02(unsigned char dir,
        const unsigned char *pin,
        int len,
        pcallback pcb,
        const char *pline_head,
        const char *pline_end)
{
    const char * const err_str[] =
    {
        "ͨ�ų�ʱ",
        "��Ч���ݵ�Ԫ",
        "���ȴ�",
        "У�����",
        "��Ϣ�಻����",
        "��ʽ����", //5
        "����ظ�",
        "��Ų�����",
        "���Ӧ�ò���Ӧ��",
        "���ڵ�æ",
        "���ڵ㲻֧�ִ�����",    //10
        "�ӽڵ㲻Ӧ��",
        "�ӽڵ㲻������",
    };

    pcb(pline_head);
    sprintf(buf, "���ϱ���[%02X(%d)]:", pin[0], pin[0]);
    pcb(buf);
    CHK_APP_LEN(len, 1);

    if (pin[0] < 13)
    {
        pcb(err_str[pin[0]]);
    }
    else
    {
        switch (pin[0])
        {
        case 109:
            pcb("������󲢷���");
            break;
        case 110:
            pcb("�������� Q/GDW10376.2֡�������ĵ��Э�鱨��");
            break;
        case 111:
            pcb("���ڳ����ñ�");
            break;
        default:
            pcb("����");
            break;
        }
    }
    pcb(pline_end);

    return ERR_NONE;
}

/**
 ******************************************************************************
 * @brief   ���ȷ��/���Ͻ����ַ���
 * @param[in]   dir         : ���䷽��:1����(ģ��->������)" 0����(������->ģ��)
 * @param[in]  *pin         : ���뱨��
 * @param[in]   len         : Ӧ�ò㱨�ĳ���
 * @param[in]  *pcb         : �ص�����
 * @param[in]  *pline_head  : ÿ����ʼ����ַ���
 * @param[in]  *pline_end   : ÿ�н�������ַ���
 *
 * @retval  ����������
 ******************************************************************************
 */
int
print_AFN00(unsigned char dir,
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
        case 1: //ȷ��
            return AFN00_FN01(dir, pin + 2, len - 2, pcb, pline_head, pline_end);
        case 2: //����
            return AFN00_FN02(dir, pin + 2, len - 2, pcb, pline_head, pline_end);
        default:
            break;
    }

    pcb(pline_head);
    pcb("ERROR:��֧�ֵ�FN!");
    pcb(pline_end);

    return -ERR_AFN_FN;
}

/*--------------------------------AFN00.c------------------------------------*/
