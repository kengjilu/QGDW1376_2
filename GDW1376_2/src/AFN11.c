/**
 ******************************************************************************
 * @file      AFN11.c
 * @brief     C Source file of AFN11.c.
 * @details   This file including all API functions's implement of AFN11.c.
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
 * @brief   �����Ӵӽڵ�����ַ���
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
AFN11_FN01(unsigned char dir,
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
    pcb("��Ӵӽڵ�");
    pcb(pline_end);
    if (dir == 0)   //����
    {
        sprintf(buf, "%s�ӽڵ������:%d%s", pline_head, pin[0], pline_end);
        pcb(buf);
        if (len < (pin[0] * 7 + 1))
        {
            sprintf(buf, "%s���뱨�ĳ��Ȳ������ʧ��!%s", pline_head,  pline_end);
            pcb(buf);
            return -1;
        }
        for (i = 0; i < pin[0]; i++)
        {
            sprintf(buf, "%s�ӽڵ�%d��ַ:[%02X %02X %02X %02X %02X %02X]%s",
                    pline_head, i, pin[i * 7 + 1], pin[i * 7 + 2],
                    pin[i * 7 + 3], pin[i * 7 + 4], pin[i * 7 + 5],
                    pin[i * 7 + 6], pline_end);
            pcb(buf);
            sprintf(buf, "%sͨ��Э������[%d]:%s%s",
                    pline_head, pin[i * 7 + 7],
                    (pin[i * 7 + 7] < 4) ? type[pin[i * 7 + 7]] : "����",
                    pline_end);
            pcb(buf);
        }
    }
    else    //����
    {
        //��
    }

    return 0;
}

/**
 ******************************************************************************
 * @brief   ���ɾ���ӽڵ�����ַ���
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
AFN11_FN02(unsigned char dir,
        const unsigned char *pin,
        int len,
        pcallback pcb,
        const char *pline_head,
        const char *pline_end)
{
    int i;

    pcb(pline_head);
    pcb("ɾ���ӽڵ�");
    pcb(pline_end);
    if (dir == 0)   //����
    {
        sprintf(buf, "%s�ӽڵ������:%d%s", pline_head, pin[0], pline_end);
        pcb(buf);
        if (len < (pin[0] * 6 + 1))
        {
            sprintf(buf, "%s���뱨�ĳ��Ȳ������ʧ��!%s", pline_head,  pline_end);
            pcb(buf);
            return -1;
        }
        for (i = 0; i < pin[0]; i++)
        {
            sprintf(buf, "%s�ӽڵ�%d��ַ:[%02X %02X %02X %02X %02X %02X]%s",
                    pline_head, i, pin[i * 6 + 1], pin[i * 6 + 2],
                    pin[i * 6 + 3], pin[i * 6 + 4], pin[i * 6 + 5],
                    pin[i * 6 + 6], pline_end);
            pcb(buf);
        }
    }
    else    //����
    {
        //��
    }

    return 0;
}

/**
 ******************************************************************************
 * @brief   ������ôӽڵ�̶��м�·�������ַ���
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
AFN11_FN03(unsigned char dir,
        const unsigned char *pin,
        int len,
        pcallback pcb,
        const char *pline_head,
        const char *pline_end)
{
    int i;

    pcb(pline_head);
    pcb("���ôӽڵ�̶��м�·��");
    pcb(pline_end);
    if (dir == 0)   //����
    {
        sprintf(buf, "%s�ӽڵ��ַ:[%02X %02X %02X %02X %02X %02X]%s",
                pline_head, pin[0], pin[1], pin[2], pin[3], pin[4], pin[5],
                pline_end);
        pcb(buf);
        sprintf(buf, "%s�м̼���[%d]%s", pline_head, pin[6], pline_end);
        pcb(buf);
        if (len < (pin[6] * 6 + 7))
        {
            sprintf(buf, "%s���뱨�ĳ��Ȳ������ʧ��!%s", pline_head,  pline_end);
            pcb(buf);
            return -1;
        }
        for (i = 0; i < pin[6]; i++)
        {
            sprintf(buf, "%s��%d���м̴ӽڵ��ַ:[%02X %02X %02X %02X %02X %02X]%s",
                    pline_head, i, pin[i * 6 + 7], pin[i * 6 + 8],
                    pin[i * 6 + 9], pin[i * 6 + 10], pin[i * 6 + 11],
                    pin[i * 6 + 12], pline_end);
            pcb(buf);
        }
    }
    else    //����
    {
        //��
    }

    return 0;
}

/**
 ******************************************************************************
 * @brief   �������·�ɹ���ģʽ�����ַ���
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
AFN11_FN04(unsigned char dir,
        const unsigned char *pin,
        int len,
        pcallback pcb,
        const char *pline_head,
        const char *pline_end)
{
    pcb(pline_head);
    pcb("����·�ɹ���ģʽ");
    pcb(pline_end);
    if (dir == 0)   //����
    {
        sprintf(buf, "%s����״̬��[%02x]:%d%s", pline_head, pin[0], pin[0], pline_end);
        pcb(buf);
        sprintf(buf, "%s-����״̬[%d]:%s%s", pline_head, BITS(pin[0], 0),
                BITS(pin[0], 0) ? "ѧϰ" : "����", pline_end);
        pcb(buf);
        sprintf(buf, "%s-ע������״̬[%d]:%s����%s", pline_head, BITS(pin[0], 1),
                BITS(pin[0], 1) ? "��" : "", pline_end);
        pcb(buf);
        sprintf(buf, "%s-�������[%d]:%s", pline_head, pin[0] >> 4, pline_end);
        pcb(buf);

        sprintf(buf, "%sͨ������:%d%s%s", pline_head,
                pin[1] | ((int)(pin[2] & 0x7f) << 8),
                (pin[2] & 0x80) ? "kbit/s" : "bit/s", pline_end);
        pcb(buf);
    }
    else    //����
    {
        //��
    }

    return 0;
}

/**
 ******************************************************************************
 * @brief   �������ӽڵ�����ע������ַ���
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
AFN11_FN05(unsigned char dir,
        const unsigned char *pin,
        int len,
        pcallback pcb,
        const char *pline_head,
        const char *pline_end)
{
    pcb(pline_head);
    pcb("����ӽڵ�����ע��");
    pcb(pline_end);
    if (dir == 0)   //����
    {
        sprintf(buf, "%s��ʼʱ��:%02X��%02X��%02X�� %02Xʱ%02X��%02X��%s",
                pline_head, pin[5], pin[4], pin[3], pin[2], pin[1], pin[0],
                pline_end);
        pcb(buf);
        sprintf(buf, "%s����ʱ��[%02x %02x]:%d min%s", pline_head,
                pin[6], pin[7], pin[6] | ((int)pin[7] << 8), pline_end);
        pcb(buf);
        sprintf(buf, "%s�ӽڵ��ط�����[%02x]:%d min%s", pline_head,
                pin[8], pin[8], pline_end);
        pcb(buf);
        sprintf(buf, "%s����ȴ�ʱ��Ƭ����[%02x]:%d (ʱ��Ƭָ150ms)%s",
                pline_head, pin[9], pin[9], pline_end);
        pcb(buf);
    }
    else    //����
    {
        //��
    }

    return 0;
}

/**
 ******************************************************************************
 * @brief   �����ֹ�ӽڵ�����ע������ַ���
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
AFN11_FN06(unsigned char dir,
        const unsigned char *pin,
        int len,
        pcallback pcb,
        const char *pline_head,
        const char *pline_end)
{
    pcb(pline_head);
    pcb("��ֹ�ӽڵ�����ע��");
    pcb(pline_end);
    if (dir == 0)   //����
    {
        pcb(pline_head);
        pcb("�����ݵ�Ԫ");
        pcb(pline_end);
    }
    else    //����
    {
        //��
    }

    return 0;
}

/**
 ******************************************************************************
 * @brief   ���·�����ý����ַ���
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
print_AFN11(unsigned char dir,
        const unsigned char *pin,
        int len,
        pcallback pcb,
        const char *pline_head,
        const char *pline_end)
{
    unsigned char DT1 = pin[0];
    unsigned char DT2 = pin[1];
    int fn = get_clear_fn(&DT1, &DT2);

    if (dir)
    {
        pcb(pline_head);
        pcb("ERROR:���б���Ϊȷ��/���ϱ���,���5.5.1");
        pcb(pline_end);
        return -1;
    }

    switch (fn)
    {
        case 1: //��Ӵӽڵ�
            return AFN11_FN01(dir, pin + 2, len - 2, pcb, pline_head, pline_end);
        case 2: //ɾ���ӽڵ�
            return AFN11_FN02(dir, pin + 2, len - 2, pcb, pline_head, pline_end);
        case 3: //���ôӽڵ�̶��м�·��
            return AFN11_FN03(dir, pin + 2, len - 2, pcb, pline_head, pline_end);
        case 4: //����·�ɹ���ģʽ
            return AFN11_FN04(dir, pin + 2, len - 2, pcb, pline_head, pline_end);
        case 5: //����ӽڵ�����ע��
            return AFN11_FN05(dir, pin + 2, len - 2, pcb, pline_head, pline_end);
        case 6: //��ֹ�ӽڵ�����ע��
            return AFN11_FN06(dir, pin + 2, len - 2, pcb, pline_head, pline_end);
//        case 100: //todo: ���������ģ
//            return AFN11_FN100(dir, pin + 2, len - 2, pcb, pline_head, pline_end);
//        case 101: //todo: ��������ά������
//            return AFN11_FN101(dir, pin + 2, len - 2, pcb, pline_head, pline_end);
//        case 102: //todo: ��������
//            return AFN11_FN102(dir, pin + 2, len - 2, pcb, pline_head, pline_end);
        default:
            break;
    }

    pcb(pline_head);
    pcb("ERROR:��֧�ֵ�FN!");
    pcb(pline_end);

    return -ERR_AFN_FN;
}

/*--------------------------------AFN11.c------------------------------------*/
