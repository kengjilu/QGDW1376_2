/**
 ******************************************************************************
 * @file      AFN06.c
 * @brief     C Source file of AFN06.c.
 * @details   This file including all API functions's implement of AFN06.c.
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
 * @brief   ����ϱ��ӽڵ���Ϣ�����ַ���
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
AFN06_FN01(unsigned char dir,
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
    pcb("�ϱ��ӽڵ���Ϣ");
    pcb(pline_end);
    if (dir == 0)   //����
    {
        //��
    }
    else    //����
    {
        sprintf(buf, "%s�ϱ��ӽڵ������:%d%s", pline_head, pin[0], pline_end);
        pcb(buf);

        if (len < (pin[0] * 9 + 1))
        {
            pcb(pline_head);
            pcb("ERROR:��������!");
            pcb(pline_end);
            return -1;
        }
        for (i = 0; i < pin[0]; i++)
        {
            sprintf(buf, "%s�ӽڵ�%d��ַ:[%02X %02X %02X %02X %02X %02X]%s",
                    pline_head, i, pin[9*i + 1], pin[9*i + 2], pin[9*i + 3],
                    pin[9*i + 4], pin[9*i + 5], pin[9*i + 6],
                    pline_end);
            pcb(buf);
            sprintf(buf, "%s�ӽڵ�%dͨ��Э������[%d]:%s%s",
                    pline_head, i, pin[9*i + 7],
                    (pin[9*i + 7] < 4) ? type[pin[9*i + 7]] : "����",
                    pline_end);
            pcb(buf);
            sprintf(buf, "%s�ӽڵ�%d���[%02X %02X]:%d%s", pline_head, i,
                    pin[9*i + 8], pin[9*i + 9],
                    pin[9*i + 8] | ((int)pin[9*i + 9] << 8), pline_end);
            pcb(buf);
        }
    }

    return 0;
}

/**
 ******************************************************************************
 * @brief   ����ϱ��������ݽ����ַ���
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
AFN06_FN02(unsigned char dir,
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
    pcb("�ϱ���������");
    pcb(pline_end);
    if (dir == 0)   //����
    {
        //��
    }
    else    //����
    {
        sprintf(buf, "%s�ӽڵ����[%02X %02X]:%d%s", pline_head,
                pin[0], pin[1],
                pin[0] | ((int)pin[1] << 8), pline_end);
        pcb(buf);
        sprintf(buf, "%s�ӽڵ�ͨ��Э������[%d]:%s%s",
                pline_head, pin[2],
                (pin[2] < 4) ? type[pin[2]] : "����",
                pline_end);
        pcb(buf);
        sprintf(buf, "%s��ǰ���ı���ͨ������ʱ��[%02X %02X]:%ds%s", pline_head,
                pin[3], pin[4],
                pin[3] | ((int)pin[4] << 8), pline_end);
        pcb(buf);
        sprintf(buf, "%s���ĳ���L:%d%s", pline_head, pin[5], pline_end);
        pcb(buf);

        pcb(pline_head);
        pcb(" ��������:");
        pcb(pline_end);
        pcb(pline_head);
        for (i = 0; i < pin[5]; i++)
        {
            sprintf(buf, "%02X ", pin[i + 6]);
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
 * @brief   ����ϱ�·�ɹ����䶯��Ϣ�����ַ���
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
AFN06_FN03(unsigned char dir,
        const unsigned char *pin,
        int len,
        pcallback pcb,
        const char *pline_head,
        const char *pline_end)
{
    pcb(pline_head);
    pcb("�ϱ�·�ɹ����䶯��Ϣ");
    pcb(pline_end);
    if (dir == 0)   //����
    {
        //��
    }
    else    //����
    {
        sprintf(buf, "%s·�ɹ�������䶯����[%d]:%s%s", pline_head, pin[0],
                (pin[0] == 1) ? "�����������" : ((pin[0] == 2) ? "�ѱ��������":"����"), pline_end);
        pcb(buf);
    }

    return 0;
}

/**
 ******************************************************************************
 * @brief   ����ϱ��ӽڵ���Ϣ���豸���ͽ����ַ���
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
AFN06_FN04(unsigned char dir,
        const unsigned char *pin,
        int len,
        pcallback pcb,
        const char *pline_head,
        const char *pline_end)
{
    int i;
    pcb(pline_head);
    pcb("�ϱ��ӽڵ���Ϣ���豸����");
    pcb(pline_end);
    if (dir == 0)   //����
    {
        //��
    }
    else    //���� todo: �������������
    {
        sprintf(buf, "%s�ϱ��ӽڵ������:%d%s", pline_head, pin[0], pline_end);
        pcb(buf);

        //�ӽڵ�ͨ�ŵ�ַ6�ֽ�
        sprintf(buf, "%s�ӽڵ�1ͨ�ŵ�ַ:[%02X %02X %02X %02X %02X %02X]%s",
                pline_head, pin[1],pin[2], pin[3],  pin[4], pin[5], pin[6], pline_end);
        pcb(buf);

        sprintf(buf, "%s�ӽڵ�1ͨ��Э������:%d(%s)%s", pline_head, pin[7],
                (pin[7] == 0) ? "͸������" : (pin[7] == 1) ? "DL/T645-1997" : (pin[7] == 2) ? "DL/T645-2007" : (pin[7] == 3) ? "DL/T698.45" : "����",
                pline_end); //00: ͸������ 01:645-97 02:645-07 03~FF:����
        pcb(buf);

        sprintf(buf, "%s�ӽڵ�1���:%d%s", pline_head, (pin[8] << 8) | pin[9], pline_end);
        pcb(buf);

        sprintf(buf, "%s�ӽڵ�1�豸����:%d(%s)%s", pline_head, pin[10], (pin[10] == 0) ? "�ɼ���" : (pin[10] == 1) ? "���ܱ�" : "����", pline_end);
        pcb(buf);

        sprintf(buf, "%s�ӽڵ�1�½Ӵӽڵ�����M:%d%s", pline_head, pin[11], pline_end);
        pcb(buf);

        for (i = 0; i < pin[12]; i++)
        {
            sprintf(buf, "%s�½Ӵӽڵ�%dͨ�ŵ�ַ:[%02X %02X %02X %02X %02X %02X]%s",
                    pline_head, i, pin[i * 7 + 13], pin[i * 7 + 14],
                    pin[i * 7 + 15], pin[i * 7 + 16], pin[i * 7 + 17],
                    pin[i * 7 + 18], pline_end);
            pcb(buf);

            sprintf(buf, "%s�½Ӵӽڵ�%dͨ��Э������:%d(%s)%s", pline_head, i, pin[i * 7 + 19],
                    (pin[i * 7 + 19] == 0) ? "͸������" : (pin[i * 7 + 19] == 1) ? "645-97" : (pin[i * 7 + 19] == 2) ? "645-07" : (pin[i * 7 + 19] == 3) ? "698.45" : "����",
                    pline_end); //00: ͸������ 01:645-97 02:645-07 03~FF:����
            pcb(buf);
        }
    }

    return 0;
}

/**
 ******************************************************************************
 * @brief   ����ϱ��ӽڵ��¼������ַ���
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
AFN06_FN05(unsigned char dir,
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
    pcb("�ϱ��ӽڵ��¼�");
    pcb(pline_end);
    if (dir == 0)   //����
    {
        //��
    }
    else    //����
    {
        sprintf(buf, "%s�ӽڵ��豸����[%d]:%s%s", pline_head, pin[0],
                (pin[0] == 0) ? "�ɼ���" : ((pin[0] == 1) ? "���ܱ�":"����"), pline_end);
        pcb(buf);
        sprintf(buf, "%s�ӽڵ�ͨ��Э������[%d]:%s%s",
                pline_head, pin[1],
                (pin[1] < 4) ? type[pin[1]] : "����",
                pline_end);
        pcb(buf);
        sprintf(buf, "%s���ĳ���L:%d%s", pline_head, pin[2], pline_end);
        pcb(buf);

        pcb(pline_head);
        pcb(" ��������:");
        pcb(pline_end);
        pcb(pline_head);
        for (i = 0; i < pin[2]; i++)
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
 * @brief   ��������ϱ������ַ���
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
print_AFN06(unsigned char dir,
        const unsigned char *pin,
        int len,
        pcallback pcb,
        const char *pline_head,
        const char *pline_end)
{
    unsigned char DT1 = pin[0];
    unsigned char DT2 = pin[1];
    int fn = get_clear_fn(&DT1, &DT2);

    if (!dir)
    {
        pcb(pline_head);
        pcb("ERROR:AFN(06H)�����ϱ������б���");
        pcb(pline_end);
        return -1;
    }

    switch (fn)
    {
        case 1: //�ϱ��ӽڵ���Ϣ
            return AFN06_FN01(dir, pin + 2, len - 2, pcb, pline_head, pline_end);
        case 2: //�ϱ���������
            return AFN06_FN02(dir, pin + 2, len - 2, pcb, pline_head, pline_end);
        case 3: //�ϱ�·�ɹ����䶯��Ϣ
            return AFN06_FN03(dir, pin + 2, len - 2, pcb, pline_head, pline_end);
        case 4: //�ϱ��ӽڵ���Ϣ���豸����
            return AFN06_FN04(dir, pin + 2, len - 2, pcb, pline_head, pline_end);
        case 5: //�ϱ��ӽڵ��¼�
            return AFN06_FN05(dir, pin + 2, len - 2, pcb, pline_head, pline_end);
        default:
            break;
    }

    pcb(pline_head);
    pcb("ERROR:��֧�ֵ�FN!");
    pcb(pline_end);

    return -ERR_AFN_FN;
}

/*--------------------------------AFN06.c------------------------------------*/
