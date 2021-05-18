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
 * @brief   ��ѯ�ӽڵ�ID����Ϣ
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
AFN10_FN07(unsigned char dir,
        const unsigned char *pin,
        int len,
        pcallback pcb,
        const char *pline_head,
        const char *pline_end)
{
    int i, moduleid ;
    const char * const idformat[] =
    {
        "��ϸ�ʽ",
        "BCD",
        "BIN",
        "ASCII",
    };

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
        sprintf(buf, "%s����Ӧ��Ĵӽڵ�����n:%d%s", pline_head, pin[2], pline_end);
        pcb(buf);
        if (len < (pin[2] * (11 + pin[12]) + 3)) //���ݲ��ֳ���
        {
            sprintf(buf, "%s���뱨�ĳ��Ȳ������ʧ��!%s", pline_head,  pline_end);
            pcb(buf);
            return -1;
        }

        for (i = 0; i < pin[2]; i++)
        {
            sprintf(buf, "%s�ӽڵ�%d��ַ:[%02X %02X %02X %02X %02X %02X]%s",
                    pline_head, i, pin[i * 12 + 3], pin[i * 12 + 4],
                    pin[i * 12 + 5], pin[i * 12 + 6], pin[i * 12 + 7],
                    pin[i * 12 + 8], pline_end);
            pcb(buf);

            sprintf(buf, "%s�ӽڵ�%d��ַ����:%d%s", pline_head, i+1, pin[i * 8 + 9], pline_end);
            pcb(buf);
            moduleid = (pin[i * 8 + 11] << 8) | pin[i * 8 + 10];
            sprintf(buf, "%s�ӽڵ�%dģ�鳧�̴���:%d%s", pline_head, i+1, moduleid, pline_end);
            pcb(buf);
            sprintf(buf, "%s�ӽڵ�%dģ��ID�ų���:%d%s", pline_head, i+1,pin[i * 8 + 12], pline_end);
            pcb(buf);
            sprintf(buf, "%s�ӽڵ�%dģ��ID�Ÿ�ʽ:%d%s", pline_head, i+1,pin[i * 8 + 13], pline_end);
            pcb(buf);

            sprintf(buf, "%s�ӽڵ�%dģ��ID�Ÿ�ʽ:%s%s", pline_head, pin[i * 8 + 13],
                    (pin[0] < 4) ? idformat[pin[i * 8 + 13]] : "����",
                    pline_end);
            pcb(buf);
            sprintf(buf, "%s�ӽڵ�%dģ��ID��:%d%s", pline_head, i+1, pin[i * 8 + 14], pline_end);
            pcb(buf);
        }
    }

    return 0;
}

/**
 ******************************************************************************
 * @brief   ��ѯHPLC�����ģ
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
AFN10_FN09(unsigned char dir,
        const unsigned char *pin,
        int len,
        pcallback pcb,
        const char *pline_head,
        const char *pline_end)
{
    pcb(pline_head);
    pcb("��ѯHPLC�����ģ");
    pcb(pline_end);
    if (dir == 0)   //����
    {
        CHK_APP_LEN(len, 0);
    }
    else    //����
    {
        CHK_APP_LEN(len, 2);
        sprintf(buf, "%sHPLC�����ģ[%02X %02X]:%d%s", pline_head,
                pin[0], pin[1], pin[0] | ((int)pin[1] << 8), pline_end);
        pcb(buf);
    }

    return 0;
}

/**
 ******************************************************************************
 * @brief   ��ѯ����������Ϣ
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
AFN10_FN21(unsigned char dir,
        const unsigned char *pin,
        int len,
        pcallback pcb,
        const char *pline_head,
        const char *pline_end)
{
    int i;
    pcb(pline_head);
    pcb("��ѯ���������ģ");
    pcb(pline_end);
    if (dir == 0)   //����
    {
        CHK_APP_LEN(len, 3); //
        sprintf(buf, "%s�ӽڵ���ʼ���[%02X %02X]:%d%s", pline_head, pin[0], pin[1],
                pin[0] | ((int)pin[1] << 8), pline_end);
        pcb(buf);
        sprintf(buf, "%s�ӽڵ�����[%02X]:%d%s", pline_head, pin[2], pin[2],
                pline_end);
        pcb(buf);
    }
    else    //����
    {
        sprintf(buf, "%s�ӽڵ�������[%02X %02X]:%d%s", pline_head,
                pin[0], pin[1], pin[0] | ((int)pin[1] << 8), pline_end);
        pcb(buf);
        sprintf(buf, "%s�ӽڵ���ʼ���[%02X %02X]:%d%s", pline_head,
                pin[2], pin[3], pin[2] | ((int)pin[2] << 8),pline_end);
        pcb(buf);
        sprintf(buf, "%s����Ӧ��Ľڵ�����:%d%s", pline_head, pin[4], pline_end);
        pcb(buf);
        if (len < (pin[4] * 11 + 5))
        {
            sprintf(buf, "%s���뱨�ĳ��Ȳ������ʧ��!%s", pline_head, pline_end);
            pcb(buf);
            return -1;
        }
        for (i =0; i < pin[4]; i++) //�ڵ����1��ʼ
        {
            sprintf(buf, "%s�ڵ�%d��ַ:[%02X %02X %02X %02X %02X %02X]%s",
                    pline_head, i+1, pin[i * 11 + 5], pin[i * 11 + 6],
                    pin[i * 11 + 7], pin[i * 11 + 8], pin[i * 11 + 9],
                    pin[i * 11 + 10], pline_end);
            pcb(buf);
            sprintf(buf, "%s�ڵ�%d����������Ϣ:[%02X %02X %02X %02X %02X]%s",
                    pline_head, i+1, pin[i * 11 + 11], pin[i * 11 + 12],
                    pin[i * 11 + 13], pin[i * 11 + 14], pin[i * 11 + 15],
                    pline_end);
            pcb(buf);
        }
    }

    return 0;
}

/**
 ******************************************************************************
 * @brief   ��ѯ������Ϣ
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
AFN10_FN31(unsigned char dir,
        const unsigned char *pin,
        int len,
        pcallback pcb,
        const char *pline_head,
        const char *pline_end)
{
    int i;
    pcb(pline_head);
    pcb("��ѯ����");
    pcb(pline_end);
    if (dir == 0)   //����
    {
        CHK_APP_LEN(len, 3);
        sprintf(buf, "%s�ӽڵ���ʼ���[%02X %02X]:%d%s", pline_head,
                pin[0], pin[1], pin[0] | ((int)pin[1] << 8), pline_end);
        pcb(buf);
        sprintf(buf, "%s�ӽڵ�����[%02X]:%d%s", pline_head, pin[2], pin[2], pline_end);
        pcb(buf);
    }
    else    //����
    {
        sprintf(buf, "%s�ӽڵ�������[%02X %02X]:%d%s", pline_head,
                pin[0], pin[1], pin[0] | ((int)pin[1] << 8), pline_end);
        pcb(buf);
        sprintf(buf, "%s�ӽڵ���ʼ���[%02X %02X]:%d%s", pline_head,
                pin[2], pin[3], pin[2] | ((int)pin[2] << 8),pline_end);
        pcb(buf);
        sprintf(buf, "%s����Ӧ��Ľڵ�����:%d%s", pline_head,pin[4], pline_end);
        pcb(buf);
        if (len < (pin[2] * 8 + 3))
        {
            sprintf(buf, "%s���뱨�ĳ��Ȳ������ʧ��!%s", pline_head, pline_end);
            pcb(buf);
            return -1;
        }
        for (i = 0; i < pin[4]; i++)
        {
            sprintf(buf, "%s�ڵ�%d��ַ:[%02X %02X %02X %02X %02X %02X]%s",
                    pline_head, i, pin[i * 8 + 5], pin[i * 8 + 6],
                    pin[i * 8 + 7], pin[i * 8 + 8], pin[i * 8 + 9],
                    pin[i * 8 + 10], pline_end);
            pcb(buf);
            sprintf(buf, "%s�ڵ�%d������Ϣ:[%02X %02X]%s", pline_head, i,
                    pin[i * 8 + 11], pin[i * 8 + 12], pline_end);
            pcb(buf);
        }
    }

    return 0;
}

/**
 ******************************************************************************
 * @brief   ��ˮ�߲�ѯID��Ϣ
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
AFN10_FN40(unsigned char dir,
        const unsigned char *pin,
        int len,
        pcallback pcb,
        const char *pline_head,
        const char *pline_end)
{
    const char * const devtype[] =
    {
        "δ������豸����",
        "������",
        "CCO",
        "���ͨ�ŵ�Ԫ",
        "�м���",
        "II�Ͳɼ���",
        "I�Ͳɼ���",
        "�����ͨ�ŵ�Ԫ",
    };
    const char * const idtype[] =
    {
        "δ�����ID����",
        "оƬID",
        "ģ��ID",
    };

    pcb(pline_head);
    pcb("��ˮ�߲�ѯID��Ϣ");
    pcb(pline_end);
    if (dir == 0)   //����
    {
        CHK_APP_LEN(len, 8);
        sprintf(buf, "%s�豸����[%d]:%s%s", pline_head, pin[0],
               (pin[0] < 8) ? devtype[pin[0]] : "δ������豸����", pline_end);
        pcb(buf);
        sprintf(buf, "%s�ڵ��ַ:[%02X %02X %02X %02X %02X %02X]%s",
                pline_head, pin[1], pin[2],pin[3], pin[4], pin[5],
                pin[6], pline_end);
        pcb(buf);
        sprintf(buf, "%sID����[%d]:%s%s", pline_head, pin[6],
                (pin[0] < 3) ? idtype[pin[6]] : "δ�����ID����", pline_end);
        pcb(buf);
    }
    else    //����
    {
        CHK_APP_LEN(len, 33);//��ΪоƬID��len=33����Ϊģ��ID����ID���ȶ����������ĵ���
        sprintf(buf, "%s�豸����[%d]:%s%s", pline_head, pin[0],
                (pin[0] < 8) ? devtype[pin[0]] : "δ������豸����", pline_end);
        pcb(buf);
        sprintf(buf, "%s�ڵ��ַ:[%02X %02X %02X %02X %02X %02X]%s",
                pline_head, pin[1], pin[2],pin[3], pin[4], pin[5],
                pin[6], pline_end);
        pcb(buf);
        sprintf(buf, "%sID����[%d]:%s%s", pline_head, pin[6],
                (pin[0] < 3) ? idtype[pin[6]] : "δ�����ID����", pline_end);
        pcb(buf);
        sprintf(buf, "%sID����L:%d%s", pline_head, pin[7], pline_end);
        pcb(buf);
        if(pin[0] == 1) //�����оƬID�������Ӧ��ID��Ϣ��ģ��ID��֪���Ǽ����ֽ�376.2Э����δ˵��
        {
            sprintf(buf, "%sID��Ϣ:[%02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X "
                    "%02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X]%s",
                    pline_head, pin[8], pin[9],pin[10], pin[11], pin[12],pin[13],
                    pin[14], pin[15],pin[16], pin[17], pin[18],pin[19],
                    pin[20], pin[21],pin[22], pin[23], pin[24],pin[25],
                    pin[26], pin[27],pin[28], pin[29], pin[30],pin[31],pline_end);
            pcb(buf);
        }
        else
        {
             pcb(pline_head);
             pcb("δ����");
             pcb(pline_end);
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
 * @brief   �����ѯ������ģ��汾��Ϣ�����ַ���
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
AFN10_FN104(unsigned char dir,
        const unsigned char *pin,
        int len,
        pcallback pcb,
        const char *pline_head,
        const char *pline_end)
{
    pcb(pline_head);
    pcb("��ѯ������ģ��汾��Ϣ");
    pcb(pline_end);
    if (dir == 0)   //����
    {
        CHK_APP_LEN(len, 0);
    }
    else    //����
    {
//        CHK_APP_LEN(len, 2);
//        sprintf(buf, "%s�����ģ[%02X %02X]:%d%s", pline_head,
//                pin[0], pin[1], pin[0] | ((int)pin[1] << 8), pline_end);
//        pcb(buf);
        pcb("TOTO: δ�������ݸ�ʽ");
    }

    return 0;
}

/**
 ******************************************************************************
 * @brief   �����ѯ������Ϣ�����ַ���
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
AFN10_FN111(unsigned char dir,
        const unsigned char *pin,
        int len,
        pcallback pcb,
        const char *pline_head,
        const char *pline_end)
{
    int i;

    pcb(pline_head);
    pcb("��ѯ������Ϣ");
    pcb(pline_end);
    if (dir == 0)   //����
    {
        CHK_APP_LEN(len, 0);
    }
    else    //����
    {
        if (len < (pin[0] * 3 + 10))
        {
            pcb(pline_head);
            pcb("ERROR:��������!");
            pcb(pline_end);
            return -1;
        }
        sprintf(buf, "%s������ڵ�������[%02X]:%d%s", pline_head, pin[0], pin[0], pline_end);
        pcb(buf);
        sprintf(buf, "%s���ڵ������ʶ��[%02X %02X %02X]:%d%s", pline_head,
                pin[1], pin[2], pin[3], (pin[1] << 16) | (pin[2] << 8)| pin[3],
                pline_end);
        pcb(buf);
        sprintf(buf, "%s���ڵ��ַ:[%02X %02X %02X %02X %02X %02X]%s",
                pline_head, pin[4], pin[5], pin[6], pin[7], pin[8], pin[9],
                pline_end);
        pcb(buf);
        for (i = 0; i < pin[2]; i++)
        {
            sprintf(buf, "%s�ھ�%d �ڵ������ʶ��[%02X %02X %02X]:%d%s", pline_head, i,
                    pin[10 + i*3], pin[11 + i*3], pin[12 + i*3],
                    (pin[10 + i*3] << 16) | (pin[11 + i*3] << 8)| pin[12 + i*3],
                    pline_end);
            pcb(buf);
        }
    }

    return 0;
}

/**
 ******************************************************************************
 * @brief   �����ѯ����ز�оƬ��Ϣ�����ַ���
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
AFN10_FN112(unsigned char dir,
        const unsigned char *pin,
        int len,
        pcallback pcb,
        const char *pline_head,
        const char *pline_end)
{
    int i;
    const char * const type[] =
    {
        "����",
        "������",
        "����������ͨ�ŵ�Ԫ",
        "������ܱ�ͨ�ŵ�Ԫ",
        "�м���",
        "II�Ͳɼ���",
        "I�Ͳɼ���",
        "������ܱ�ͨ�ŵ�Ԫ",
    };

    pcb(pline_head);
    pcb("��ѯ����ز�оƬ��Ϣ");
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
        if (len < (pin[4] * 33 + 5))
        {
            pcb(pline_head);
            pcb("ERROR:��������!");
            pcb(pline_end);
            return -1;
        }

        sprintf(buf, "%s�ӽڵ�������[%02X %02X]:%d%s", pline_head,
                pin[0], pin[1], pin[0] | ((int)pin[1] << 8), pline_end);
        pcb(buf);
        sprintf(buf, "%s�ڵ���ʼ���[%02X %02X]:%d%s", pline_head,
                pin[2], pin[3], pin[2] | ((int)pin[3] << 8), pline_end);
        pcb(buf);
        sprintf(buf, "%s����Ӧ��Ĵӽڵ�����:%d%s", pline_head, pin[4], pline_end);
        pcb(buf);

        for (i = 0; i < pin[4]; i++)
        {
            pcb(pline_end);
            int pos =  i*33 + 5;
            sprintf(buf, "%s�ڵ�%d ��ַ:[%02X %02X %02X %02X %02X %02X]%s", pline_head, i+1,
                    pin[pos], pin[pos + 1], pin[pos + 2], pin[pos + 3], pin[pos + 4], pin[pos + 5],
                    pline_end);
            pcb(buf);
            sprintf(buf, "%s�ڵ�%d �豸����[%02X]:%s%s", pline_head, i+1, pin[pos + 6],
                    (pin[pos + 6] < 8) ? type[pin[pos + 6]] : "����",  pline_end);
            pcb(buf);
            sprintf(buf, "%s�ڵ�%d ID��Ϣ:[%02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X "
                    "%02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X]%s",
                    pline_head, i+1,
                    pin[pos + 7],  pin[pos + 8],  pin[pos + 9], pin[pos + 10], pin[pos + 11], pin[pos + 12],
                    pin[pos + 13], pin[pos + 14], pin[pos + 15],pin[pos + 16], pin[pos + 17], pin[pos + 18],
                    pin[pos + 19], pin[pos + 20], pin[pos + 21],pin[pos + 22], pin[pos + 23], pin[pos + 24],
                    pin[pos + 25], pin[pos + 26], pin[pos + 27],pin[pos + 28], pin[pos + 29], pin[pos + 30],
                    pline_end);
            pcb(buf);
            sprintf(buf, "%s�ڵ�%d ����汾��Ϣ[%02X %02X]:%d%s", pline_head, i+1,
                    pin[pos + 31], pin[pos + 32], pin[pos + 31] | ((int)pin[pos + 32] << 8), pline_end);
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
        case 7: //todo: ��ѯ�ӽڵ�ID����Ϣ(������)
            return AFN10_FN07(dir, pin + 2, len - 2, pcb, pline_head, pline_end);
        case 9: //��ѯHPLC�����ģ
            return AFN10_FN09(dir, pin + 2, len - 2, pcb, pline_head, pline_end);
        case 21: //��ѯ����������Ϣ
            return AFN10_FN21(dir, pin + 2, len - 2, pcb, pline_head, pline_end);
        case 31: //��ѯ������Ϣ
            return AFN10_FN31(dir, pin + 2, len - 2, pcb, pline_head, pline_end);
        case 40: //��ѯID��Ϣ
            return AFN10_FN40(dir, pin + 2, len - 2, pcb, pline_head, pline_end);
        case 100: //��ѯ���������ģ
            return AFN10_FN100(dir, pin + 2, len - 2, pcb, pline_head, pline_end);
        case 101: //��ѯ΢�������ߴӽڵ���Ϣ
            return AFN10_FN101(dir, pin + 2, len - 2, pcb, pline_head, pline_end);
        case 104: //todo: ��ѯ������ģ��汾��Ϣ(376.2Э����û��)
            return AFN10_FN104(dir, pin + 2, len - 2, pcb, pline_head, pline_end);
        case 111: //��ѯ������Ϣ
            return AFN10_FN111(dir, pin + 2, len - 2, pcb, pline_head, pline_end);
        case 112: //��ѯ����ز�оƬ��Ϣ
            return AFN10_FN112(dir, pin + 2, len - 2, pcb, pline_head, pline_end);
        default:
            break;
    }

    pcb(pline_head);
    pcb("ERROR:��֧�ֵ�FN!");
    pcb(pline_end);

    return -ERR_AFN_FN;
}

/*--------------------------------AFN10.c------------------------------------*/
