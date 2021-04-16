/**
 ******************************************************************************
 * @file      AFN10.c
 * @brief     C Source file of AFN10.c.
 * @details   This file including all API functions's implement of AFN10.c.
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
 * @brief   ����ӽڵ����������ַ���
 * @param[in]   dir         : ���䷽��:1����(ģ��->������)" 0����(������->ģ��)
 * @param[in]  *pin         : ���뱨��
 * @param[in]   len         : Ӧ�ò㱨�ĳ���
 * @param[in]  *pcb         : �ص�����
 * @param[in]  *pline_head  : ÿ����ʼ����ַ���
 * @param[in]  *pline_end   : ÿ�н�������ַ���
 *
 * @return  0 : �����ɹ�
 * @return -1 : ����ʧ��
 ******************************************************************************
 */
static int
AFN10_FN01(unsigned char dir,
        const unsigned char *pin,
        int len,
        pcallback pcb,
        const char *pline_head,
        const char *pline_end)
{
    pcb(pline_head);
    pcb("�ӽڵ�����");
    pcb(pline_end);
    if (dir == 0)   //����
    {
        pcb(pline_head);
        pcb("�����ݵ�Ԫ");
        pcb(pline_end);
    }
    else    //����
    {
        CHK_APP_LEN(len, 4);
        sprintf(buf, "%s�ӽڵ�������[%02X %02X]:%d%s", pline_head,
                pin[0], pin[1], pin[0] | ((int)pin[1] << 8), pline_end);
        pcb(buf);
        sprintf(buf, "%s·��֧�����ӽڵ�����[%02x %02x]:%d%s", pline_head,
                pin[2], pin[3], pin[2] | ((int)pin[3] << 8), pline_end);
        pcb(buf);
    }

    return 0;
}

/**
 ******************************************************************************
 * @brief   ����ӽڵ���Ϣ�����ַ���
 * @param[in]   dir         : ���䷽��:1����(ģ��->������)" 0����(������->ģ��)
 * @param[in]  *pin         : ���뱨��
 * @param[in]   len         : Ӧ�ò㱨�ĳ���
 * @param[in]  *pcb         : �ص�����
 * @param[in]  *pline_head  : ÿ����ʼ����ַ���
 * @param[in]  *pline_end   : ÿ�н�������ַ���
 *
 * @return  0 : �����ɹ�
 * @return -1 : ����ʧ��
 ******************************************************************************
 */
static int
AFN10_FN02(unsigned char dir,
        const unsigned char *pin,
        int len,
        pcallback pcb,
        const char *pline_head,
        const char *pline_end)
{
    int i;
    const char * const type[] =
    {
        "͸������",
        "DL/T645-1997",
        "DL/T645-2007",
        "DL/T698.45",
    };

    pcb(pline_head);
    pcb("�ӽڵ���Ϣ");
    pcb(pline_end);
    if (dir == 0)   //����
    {
        sprintf(buf, "%s�ӽڵ���ʼ���[%02X %02X]:%d%s", pline_head,
                pin[0], pin[1], pin[0] | ((int)pin[1] << 8), pline_end);
        pcb(buf);
        sprintf(buf, "%s�ӽڵ�����[%02x]:%d%s", pline_head, pin[2], pin[2], pline_end);
        pcb(buf);
    }
    else    //����
    {
        sprintf(buf, "%s�ӽڵ�������[%02X %02X]:%d%s", pline_head,
                pin[0], pin[1], pin[0] | ((int)pin[1] << 8), pline_end);
        pcb(buf);
        sprintf(buf, "%s����Ӧ��Ĵӽڵ�����:%d%s", pline_head, pin[2], pline_end);
        pcb(buf);
        if (len < (pin[2] * 8 + 3))
        {
            sprintf(buf, "%s���뱨�ĳ��Ȳ������ʧ��!%s", pline_head,  pline_end);
            pcb(buf);
            return -1;
        }

        for (i = 0; i < pin[2]; i++)
        {
            sprintf(buf, "%s�ӽڵ�%d��ַ:[%02X %02X %02X %02X %02X %02X]%s",
                    pline_head, i, pin[i * 8 + 3], pin[i * 8 + 4],
                    pin[i * 8 + 5], pin[i * 8 + 6], pin[i * 8 + 7],
                    pin[i * 8 + 8], pline_end);
            pcb(buf);

            sprintf(buf, "%s�м̼���:%d%s", pline_head, pin[i * 8 + 9] & 0x0f, pline_end);
            pcb(buf);
            sprintf(buf, "%s�����ź�Ʒ��:%d%s", pline_head, pin[i * 8 + 9] >> 4, pline_end);
            pcb(buf);
            sprintf(buf, "%s��λ[%d]:%s%s", pline_head, pin[i * 8 + 10] & 0x07,
                    "(D8 D9 D10��\"1\"���α�ʾ��1 2 3��)", pline_end);
            pcb(buf);
            sprintf(buf, "%sͨ��Э������[%d]:%s%s",
                    pline_head, (pin[i * 8 + 10] >> 3) & 0x07,
                    (((pin[i * 8 + 10] >> 3) & 0x07) < 4) ? type[(pin[i * 8 + 10] >> 3) & 0x07] : "����",
                    pline_end);
            pcb(buf);
        }
    }

    return 0;
}

/**
 ******************************************************************************
 * @brief   ���ָ���ӽڵ����һ���м�·����Ϣ�����ַ���
 * @param[in]   dir         : ���䷽��:1����(ģ��->������)" 0����(������->ģ��)
 * @param[in]  *pin         : ���뱨��
 * @param[in]   len         : Ӧ�ò㱨�ĳ���
 * @param[in]  *pcb         : �ص�����
 * @param[in]  *pline_head  : ÿ����ʼ����ַ���
 * @param[in]  *pline_end   : ÿ�н�������ַ���
 *
 * @return  0 : �����ɹ�
 * @return -1 : ����ʧ��
 ******************************************************************************
 */
static int
AFN10_FN03(unsigned char dir,
        const unsigned char *pin,
        int len,
        pcallback pcb,
        const char *pline_head,
        const char *pline_end)
{
    int i;
    const char * const type[] =
    {
        "͸������",
        "DL/T645-1997",
        "DL/T645-2007",
        "DL/T698.45",
    };

    pcb(pline_head);
    pcb("ָ���ӽڵ����һ���м�·����Ϣ");
    pcb(pline_end);
    if (dir == 0)   //����
    {
        CHK_APP_LEN(len, 6);
        sprintf(buf, "%s�ӽڵ��ַ:[%02X %02X %02X %02X %02X %02X]%s",
                pline_head, pin[0], pin[1], pin[2], pin[3], pin[4], pin[5],
                pline_end);
        pcb(buf);
    }
    else    //����
    {
        sprintf(buf, "%s�ṩ·�ɵĴӽڵ�������:%d%s", pline_head, pin[0], pline_end);
        pcb(buf);
        if (len < (pin[0] * 8 + 1))
        {
            sprintf(buf, "%s���뱨�ĳ��Ȳ������ʧ��!%s", pline_head,  pline_end);
            pcb(buf);
            return -1;
        }

        for (i = 0; i < pin[0]; i++)
        {
            sprintf(buf, "%s�ṩ·�ɵĴӽڵ�%d��ַ:[%02X %02X %02X %02X %02X %02X]%s",
                    pline_head, i, pin[i * 8 + 1], pin[i * 8 + 2],
                    pin[i * 8 + 3], pin[i * 8 + 4],
                    pin[i * 8 + 5], pin[i * 8 + 6], pline_end);
            pcb(buf);

            sprintf(buf, "%s�м̼���:%d%s", pline_head, pin[i * 8 + 7] & 0x0f, pline_end);
            pcb(buf);
            sprintf(buf, "%s�����ź�Ʒ��:%d%s", pline_head, pin[i * 8 + 7] >> 4, pline_end);
            pcb(buf);
            sprintf(buf, "%s��λ[%d]:%s%s", pline_head, pin[i * 8 + 8] & 0x07,
                    "(D8 D9 D10��\"1\"���α�ʾ��1 2 3��)", pline_end);
            pcb(buf);
            sprintf(buf, "%sͨ��Э������[%d]:%s%s",
                    pline_head, (pin[i * 8 + 8] >> 3) & 0x07,
                    (((pin[i * 8 + 8] >> 3) & 0x07) < 4) ? type[(pin[i * 8 + 8] >> 3) & 0x07] : "����",
                    pline_end);
            pcb(buf);
        }
    }

    return 0;
}

/**
 ******************************************************************************
 * @brief   ���·������״̬�����ַ���
 * @param[in]   dir         : ���䷽��:1����(ģ��->������)" 0����(������->ģ��)
 * @param[in]  *pin         : ���뱨��
 * @param[in]   len         : Ӧ�ò㱨�ĳ���
 * @param[in]  *pcb         : �ص�����
 * @param[in]  *pline_head  : ÿ����ʼ����ַ���
 * @param[in]  *pline_end   : ÿ�н�������ַ���
 *
 * @return  0 : �����ɹ�
 * @return -1 : ����ʧ��
 ******************************************************************************
 */
static int
AFN10_FN04(unsigned char dir,
        const unsigned char *pin,
        int len,
        pcallback pcb,
        const char *pline_head,
        const char *pline_end)
{
    int i;
    const char * const work_step[] =
    {
        "����",   //0
        "��ʼ״̬",
        "ֵ��",
        "�м�",
        "���״̬",
        "�㲥״̬", //5
        "�㲥�ж����",
        "��������Ϣ",
        "����",
    };

    pcb(pline_head);
    pcb("·������״̬");
    pcb(pline_end);
    if (dir == 0)   //����
    {
        pcb(pline_head);
        pcb("�����ݵ�Ԫ");
        pcb(pline_end);
    }
    else    //����
    {
        CHK_APP_LEN(len, 16);
        sprintf(buf, "%s ����״̬��[%02x]:%d%s", pline_head, pin[0], pin[0], pline_end);
        pcb(buf);
        sprintf(buf, "%s ·����ɱ�־[%d]:·��ѧϰ%s���%s", pline_head, BITS(pin[0], 0),
                BITS(pin[0], 0) ? "" : "δ", pline_end);
        pcb(buf);
        sprintf(buf, "%s ������־[%d]:%s����%s", pline_head, BITS(pin[0], 1),
                BITS(pin[0], 0) ? "����" : "ֹͣ", pline_end);
        pcb(buf);
        sprintf(buf, "%s �ϱ��¼���־[%d]:%s�ӽڵ��ϱ��¼�%s", pline_head, BITS(pin[0], 2),
                BITS(pin[0], 2) ? "��" : "��", pline_end);
        pcb(buf);
        sprintf(buf, "%s �������[%d]:%s", pline_head, pin[0] >> 4, pline_end);
        pcb(buf);

        sprintf(buf, "%s �ӽڵ�������[%02X %02X]:%d%s", pline_head,
                pin[1], pin[2], pin[1] | ((int)pin[2] << 8), pline_end);
        pcb(buf);
        sprintf(buf, "%s �ѳ��ӽڵ�����[%02X %02X]:%d%s", pline_head,
                pin[3], pin[4], pin[3] | ((int)pin[4] << 8), pline_end);
        pcb(buf);
        sprintf(buf, "%s �м̳����ӽڵ�����[%02X %02X]:%d%s", pline_head,
                pin[5], pin[6], pin[5] | ((int)pin[6] << 8), pline_end);
        pcb(buf);
        sprintf(buf, "%s ��������[%02x]:%d%s", pline_head, pin[7], pin[7], pline_end);
        pcb(buf);
        sprintf(buf, "%s ����״̬[%d]:%s%s", pline_head, BITS(pin[7], 0),
                BITS(pin[7], 0) ? "ѧϰ" : "����", pline_end);
        pcb(buf);
        sprintf(buf, "%s ע������״̬[%d]:%s����%s", pline_head, BITS(pin[7], 1),
                BITS(pin[7], 1) ? "" : "��", pline_end);
        pcb(buf);

        sprintf(buf, "%s ͨ������[%02X %02X]:%d%s", pline_head,
                pin[8], pin[9], pin[8] | ((int)pin[9] << 8), pline_end);
        pcb(buf);

        for (i = 1; i < 4; i++)
        {
            sprintf(buf, "%s ��%d�м̼���[%02x]:%d%s", pline_head, i, pin[9 + i], pin[9 + i] & 0x0f, pline_end);
            pcb(buf);
        }

        for (i = 1; i < 4; i++)
        {
            sprintf(buf, "%s ��%d��������[%02x]:%s%s", pline_head, i, pin[12 + i],
                    (pin[12 + i] < 9) ? work_step[pin[12 + i]] : "����", pline_end);
            pcb(buf);
        }
    }

    return 0;
}

/**
 ******************************************************************************
 * @brief   ���δ�����ɹ��Ĵӽڵ���Ϣ�����ַ���
 * @param[in]   dir         : ���䷽��:1����(ģ��->������)" 0����(������->ģ��)
 * @param[in]  *pin         : ���뱨��
 * @param[in]   len         : Ӧ�ò㱨�ĳ���
 * @param[in]  *pcb         : �ص�����
 * @param[in]  *pline_head  : ÿ����ʼ����ַ���
 * @param[in]  *pline_end   : ÿ�н�������ַ���
 *
 * @return  0 : �����ɹ�
 * @return -1 : ����ʧ��
 ******************************************************************************
 */
static int
AFN10_FN05(unsigned char dir,
        const unsigned char *pin,
        int len,
        pcallback pcb,
        const char *pline_head,
        const char *pline_end)
{
    int i;
    const char * const type[] =
    {
        "͸������",
        "DL/T645-1997",
        "DL/T645-2007",
        "DL/T698.45",
    };

    pcb(pline_head);
    pcb("δ�����ɹ��Ĵӽڵ���Ϣ");
    pcb(pline_end);
    if (dir == 0)   //����
    {
        CHK_APP_LEN(len, 3);
        sprintf(buf, "%s�ӽڵ���ʼ���[%02X %02X]:%d%s", pline_head,
                pin[0], pin[1], pin[0] | ((int)pin[1] << 8), pline_end);
        pcb(buf);
        sprintf(buf, "%s�ӽڵ�����[%02x]:%d%s", pline_head, pin[2], pin[2], pline_end);
        pcb(buf);
    }
    else    //����
    {
        sprintf(buf, "%s�ӽڵ�������[%02X %02X]:%d%s", pline_head,
                pin[0], pin[1], pin[0] | ((int)pin[1] << 8), pline_end);
        pcb(buf);
        sprintf(buf, "%s����Ӧ��Ĵӽڵ�����:%d%s", pline_head, pin[2], pline_end);
        pcb(buf);
        if (len < (pin[2] * 8 + 3))
        {
            sprintf(buf, "%s���뱨�ĳ��Ȳ������ʧ��!%s", pline_head,  pline_end);
            pcb(buf);
            return -1;
        }

        for (i = 0; i < pin[2]; i++)
        {
            sprintf(buf, "%s�ӽڵ�%d��ַ:[%02X %02X %02X %02X %02X %02X]%s",
                    pline_head, i, pin[i * 8 + 3], pin[i * 8 + 4],
                    pin[i * 8 + 5], pin[i * 8 + 6], pin[i * 8 + 7],
                    pin[i * 8 + 8], pline_end);
            pcb(buf);

            sprintf(buf, "%s�м̼���:%d%s", pline_head, pin[i * 8 + 9] & 0x0f, pline_end);
            pcb(buf);
            sprintf(buf, "%s�����ź�Ʒ��:%d%s", pline_head, pin[i * 8 + 9] >> 4, pline_end);
            pcb(buf);
            sprintf(buf, "%s��λ[%d]:%s%s", pline_head, pin[i * 8 + 10] & 0x07,
                    "(D8 D9 D10��\"1\"���α�ʾ��1 2 3��)", pline_end);
            pcb(buf);
            sprintf(buf, "%sͨ��Э������[%d]:%s%s",
                    pline_head, (pin[i * 8 + 10] >> 3) & 0x07,
                    (((pin[i * 8 + 10] >> 3) & 0x07) < 4) ? type[(pin[i * 8 + 10] >> 3) & 0x07] : "����",
                    pline_end);
            pcb(buf);
        }
    }

    return 0;
}

/**
 ******************************************************************************
 * @brief   �������ע��Ĵӽڵ���Ϣ�����ַ���
 * @param[in]   dir         : ���䷽��:1����(ģ��->������)" 0����(������->ģ��)
 * @param[in]  *pin         : ���뱨��
 * @param[in]   len         : Ӧ�ò㱨�ĳ���
 * @param[in]  *pcb         : �ص�����
 * @param[in]  *pline_head  : ÿ����ʼ����ַ���
 * @param[in]  *pline_end   : ÿ�н�������ַ���
 *
 * @return  0 : �����ɹ�
 * @return -1 : ����ʧ��
 ******************************************************************************
 */
static int
AFN10_FN06(unsigned char dir,
        const unsigned char *pin,
        int len,
        pcallback pcb,
        const char *pline_head,
        const char *pline_end)
{
    int i;
    const char * const type[] =
    {
        "͸������",
        "DL/T645-1997",
        "DL/T645-2007",
        "DL/T698.45",
    };

    pcb(pline_head);
    pcb("����ע��Ĵӽڵ���Ϣ");
    pcb(pline_end);
    if (dir == 0)   //����
    {
        sprintf(buf, "%s�ӽڵ���ʼ���[%02X %02X]:%d%s", pline_head,
                pin[0], pin[1], pin[0] | ((int)pin[1] << 8), pline_end);
        pcb(buf);
        sprintf(buf, "%s�ӽڵ�����[%02x]:%d%s", pline_head, pin[2], pin[2], pline_end);
        pcb(buf);
    }
    else    //����
    {
        sprintf(buf, "%s�ӽڵ�������[%02X %02X]:%d%s", pline_head,
                pin[0], pin[1], pin[0] | ((int)pin[1] << 8), pline_end);
        pcb(buf);
        sprintf(buf, "%s����Ӧ��Ĵӽڵ�����:%d%s", pline_head, pin[2], pline_end);
        pcb(buf);
        if (len < (pin[2] * 8 + 3))
        {
            sprintf(buf, "%s���뱨�ĳ��Ȳ������ʧ��!%s", pline_head,  pline_end);
            pcb(buf);
            return -1;
        }

        for (i = 0; i < pin[2]; i++)
        {
            sprintf(buf, "%s�ӽڵ�%d��ַ:[%02X %02X %02X %02X %02X %02X]%s",
                    pline_head, i, pin[i * 8 + 3], pin[i * 8 + 4],
                    pin[i * 8 + 5], pin[i * 8 + 6], pin[i * 8 + 7],
                    pin[i * 8 + 8], pline_end);
            pcb(buf);

            sprintf(buf, "%s�м̼���:%d%s", pline_head, pin[i * 8 + 9] & 0x0f, pline_end);
            pcb(buf);
            sprintf(buf, "%s�����ź�Ʒ��:%d%s", pline_head, pin[i * 8 + 9] >> 4, pline_end);
            pcb(buf);
            sprintf(buf, "%s��λ[%d]:%s%s", pline_head, pin[i * 8 + 10] & 0x07,
                    "(D8 D9 D10��\"1\"���α�ʾ��1 2 3��)", pline_end);
            pcb(buf);
            sprintf(buf, "%sͨ��Э������[%d]:%s%s",
                    pline_head, (pin[i * 8 + 10] >> 3) & 0x07,
                    (((pin[i * 8 + 10] >> 3) & 0x07) < 4) ? type[(pin[i * 8 + 10] >> 3) & 0x07] : "����",
                    pline_end);
            pcb(buf);
        }
    }

    return 0;
}

/**
 ******************************************************************************
 * @brief   �����ѯ�����ģ�����ַ���
 * @param[in]   dir         : ���䷽��:1����(ģ��->������)" 0����(������->ģ��)
 * @param[in]  *pin         : ���뱨��
 * @param[in]   len         : Ӧ�ò㱨�ĳ���
 * @param[in]  *pcb         : �ص�����
 * @param[in]  *pline_head  : ÿ����ʼ����ַ���
 * @param[in]  *pline_end   : ÿ�н�������ַ���
 *
 * @return  0 : �����ɹ�
 * @return -1 : ����ʧ��
 ******************************************************************************
 */
static int
AFN10_FN100(unsigned char dir,
        const unsigned char *pin,
        int len,
        pcallback pcb,
        const char *pline_head,
        const char *pline_end)
{
    pcb(pline_head);
    pcb("��ѯ�����ģ");
    pcb(pline_end);
    if (dir == 0)   //����
    {
        CHK_APP_LEN(len, 0);
    }
    else    //����
    {
        CHK_APP_LEN(len, 2);
        sprintf(buf, "%s�����ģ[%02X %02X]:%d%s", pline_head,
                pin[0], pin[1], pin[0] | ((int)pin[1] << 8), pline_end);
        pcb(buf);
    }

    return 0;
}

/**
 ******************************************************************************
 * @brief   �����ѯ΢�������ߴӽڵ���Ϣ�����ַ���
 * @param[in]   dir         : ���䷽��:1����(ģ��->������)" 0����(������->ģ��)
 * @param[in]  *pin         : ���뱨��
 * @param[in]   len         : Ӧ�ò㱨�ĳ���
 * @param[in]  *pcb         : �ص�����
 * @param[in]  *pline_head  : ÿ����ʼ����ַ���
 * @param[in]  *pline_end   : ÿ�н�������ַ���
 *
 * @return  0 : �����ɹ�
 * @return -1 : ����ʧ��
 ******************************************************************************
 */
static int
AFN10_FN101(unsigned char dir,
        const unsigned char *pin,
        int len,
        pcallback pcb,
        const char *pline_head,
        const char *pline_end)
{
    int i;
    const char * const type[] =
    {
        "͸������",
        "DL/T645-1997",
        "DL/T645-2007",
        "DL/T698.45",
    };

    pcb(pline_head);
    pcb("��ѯ΢�������ߴӽڵ���Ϣ");
    pcb(pline_end);

    if (dir == 0)   //����
    {
        CHK_APP_LEN(len, 0);
    }
    else    //����
    {
        sprintf(buf, "%s�ӽڵ�������[%02X %02X]:%d%s", pline_head,
                pin[0], pin[1], pin[0] | ((int)pin[1] << 8), pline_end);
        pcb(buf);
        sprintf(buf, "%s����Ӧ��Ĵӽڵ�����:%d%s", pline_head, pin[2], pline_end);
        pcb(buf);
        if (len < (pin[2] * 8 + 3))
        {
            sprintf(buf, "%s���뱨�ĳ��Ȳ������ʧ��!%s", pline_head,  pline_end);
            pcb(buf);
            return -1;
        }

        for (i = 0; i < pin[2]; i++)
        {
            sprintf(buf, "%s�ӽڵ�%d��ַ:[%02X %02X %02X %02X %02X %02X]%s",
                    pline_head, i, pin[i * 8 + 3], pin[i * 8 + 4],
                    pin[i * 8 + 5], pin[i * 8 + 6], pin[i * 8 + 7],
                    pin[i * 8 + 8], pline_end);
            pcb(buf);

            sprintf(buf, "%s�м̼���:%d%s", pline_head, pin[i * 8 + 9] & 0x0f, pline_end);
            pcb(buf);
            sprintf(buf, "%s�����ź�Ʒ��:%d%s", pline_head, pin[i * 8 + 9] >> 4, pline_end);
            pcb(buf);
            sprintf(buf, "%s��λ[%d]:%s%s", pline_head, pin[i * 8 + 10] & 0x07,
                    "(D8 D9 D10��\"1\"���α�ʾ��1 2 3��)", pline_end);
            pcb(buf);
            sprintf(buf, "%sͨ��Э������[%d]:%s%s",
                    pline_head, (pin[i * 8 + 10] >> 3) & 0x07,
                    (((pin[i * 8 + 10] >> 3) & 0x07) < 4) ? type[(pin[i * 8 + 10] >> 3) & 0x07] : "����",
                    pline_end);
            pcb(buf);
            sprintf(buf, "%s����汾[%02X %02X %02X]: Ӧ�ó���汾:%02X%02X boot�汾:%02X%s", pline_head,
                    pin[i * 8 + 11], pin[i * 8 + 12], pin[i * 8 + 13],
                    pin[i * 8 + 11], pin[i * 8 + 12], pin[i * 8 + 13],
                    pline_end);
            pcb(buf);
        }
    }

    return 0;
}

/**
 ******************************************************************************
 * @brief   ���·�ɲ�ѯ�����ַ���
 * @param[in]   dir         : ���䷽��:1����(ģ��->������)" 0����(������->ģ��)
 * @param[in]  *pin         : ���뱨��
 * @param[in]   len         : Ӧ�ò㱨�ĳ���
 * @param[in]  *pcb         : �ص�����
 * @param[in]  *pline_head  : ÿ����ʼ����ַ���
 * @param[in]  *pline_end   : ÿ�н�������ַ���
 *
 * @return  0 : �����ɹ�
 * @return -1 : ����ʧ��
 ******************************************************************************
 */
int
print_AFN10(unsigned char dir,
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
        case 1: //�ӽڵ�����
            return AFN10_FN01(dir, pin + 2, len - 2, pcb, pline_head, pline_end);
        case 2: //�ӽڵ���Ϣ
            return AFN10_FN02(dir, pin + 2, len - 2, pcb, pline_head, pline_end);
        case 3: //ָ���ӽڵ����һ���м�·����Ϣ
            return AFN10_FN03(dir, pin + 2, len - 2, pcb, pline_head, pline_end);
        case 4: //·������״̬
            return AFN10_FN04(dir, pin + 2, len - 2, pcb, pline_head, pline_end);
        case 5: //δ�����ɹ��Ĵӽڵ���Ϣ
            return AFN10_FN05(dir, pin + 2, len - 2, pcb, pline_head, pline_end);
        case 6: //����ע��Ĵӽڵ���Ϣ
            return AFN10_FN06(dir, pin + 2, len - 2, pcb, pline_head, pline_end);
//        case 7: //todo: ��ѯ�ӽڵ�ID����Ϣ
//            return AFN10_FN07(dir, pin + 2, len - 2, pcb, pline_head, pline_end);
//        case 9: //todo: ��ѯ�����ģ
//            return AFN10_FN09(dir, pin + 2, len - 2, pcb, pline_head, pline_end);
//        case 21: //todo: ��ѯ����������Ϣ
//            return AFN10_FN21(dir, pin + 2, len - 2, pcb, pline_head, pline_end);
//        case 31: //todo: ��ѯ��λ��Ϣ
//            return AFN10_FN31(dir, pin + 2, len - 2, pcb, pline_head, pline_end);
//        case 40: //todo: ��ѯID��Ϣ
//            return AFN10_FN40(dir, pin + 2, len - 2, pcb, pline_head, pline_end);
        case 100: //��ѯ�����ģ
            return AFN10_FN100(dir, pin + 2, len - 2, pcb, pline_head, pline_end);
        case 101: //��ѯ΢�������ߴӽڵ���Ϣ
            return AFN10_FN101(dir, pin + 2, len - 2, pcb, pline_head, pline_end);
//        case 104: //todo: ��ѯ������ģ��汾��Ϣ
//            return AFN10_FN104(dir, pin + 2, len - 2, pcb, pline_head, pline_end);
        default:
            break;
    }

    pcb(pline_head);
    pcb("ERROR:��֧�ֵ�FN!");
    pcb(pline_end);

    return -ERR_AFN_FN;
}

/*--------------------------------AFN10.c------------------------------------*/
