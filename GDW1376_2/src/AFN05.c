/**
 ******************************************************************************
 * @file      AFN05.c
 * @brief     C Source file of AFN05.c.
 * @details   This file including all API functions's implement of AFN05.c.
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
 * @brief   ����������ڵ��ַ�����ַ���
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
AFN05_FN01(unsigned char dir,
        const unsigned char *pin,
        int len,
        pcallback pcb,
        const char *pline_head,
        const char *pline_end)
{
    pcb(pline_head);
    pcb("�������ڵ��ַ");
    pcb(pline_end);
    if (dir == 0)   //����
    {
        CHK_APP_LEN(len, 6);
        sprintf(buf, "%s���ڵ��ַ:[%02X %02X %02X %02X %02X %02X]%s",
                pline_head, pin[0], pin[1], pin[2], pin[3], pin[4], pin[5],
                pline_end);
        pcb(buf);
    }
    else    //����
    {
        //��
    }

    return ERR_NONE;
}

/**
 ******************************************************************************
 * @brief   �������ӽڵ��ϱ������ַ���
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
AFN05_FN02(unsigned char dir,
        const unsigned char *pin,
        int len,
        pcallback pcb,
        const char *pline_head,
        const char *pline_end)
{
    pcb(pline_head);
    pcb("����ӽڵ��ϱ�");
    pcb(pline_end);
    if (dir == 0)   //����
    {
        CHK_APP_LEN(len, 1);
        sprintf(buf, "%s�¼��ϱ�״̬��־[%d]:%s%s", pline_head, pin[0],
                pin[0] ? "����" : "��ֹ", pline_end);
        pcb(buf);
    }
    else    //����
    {
        //��
    }

    return ERR_NONE;
}

/**
 ******************************************************************************
 * @brief   ��������㲥�����ַ���
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
AFN05_FN03(unsigned char dir,
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
        "��λʶ����",
        //todo: "DL/T698.45",
    };

    pcb(pline_head);
    pcb("�����㲥");
    pcb(pline_end);
    if (dir == 0)   //����
    {
        sprintf(buf, "%s������[%d]:%s%s",
                pline_head, pin[0],
                (pin[0] < 4) ? type[pin[0]] : "����",
                pline_end);
        pcb(buf);

        sprintf(buf, "%s���ĳ���L:%d%s", pline_head, pin[1], pline_end);
        pcb(buf);

        pcb(pline_head);
        pcb(" ��������:");
        pcb(pline_end);
        pcb(pline_head);
        for (i = 0; i < pin[1]; i++)
        {
            sprintf(buf, "%02X ", pin[i + 2]);
            pcb(buf);
            if (((i + 1) % 16) == 0)
            {
                pcb(pline_end);
                pcb(pline_head);
            }
        }
        pcb(pline_end);
    }
    else    //����
    {
        //��
    }

    return ERR_NONE;
}

/**
 ******************************************************************************
 * @brief   ������ôӽڵ������ʱʱ������ַ���
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
AFN05_FN04(unsigned char dir,
        const unsigned char *pin,
        int len,
        pcallback pcb,
        const char *pline_head,
        const char *pline_end)
{
    pcb(pline_head);
    pcb("���ôӽڵ������ʱʱ��");
    pcb(pline_end);
    if (dir == 0)   //����
    {
        CHK_APP_LEN(len, 1);
        sprintf(buf, "%s���ʱʱ��[%02X]:%ds%s", pline_head,
                pin[0], pin[0], pline_end);
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
 * @brief   �����������ͨ�Ų��������ַ���
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
AFN05_FN05(unsigned char dir,
        const unsigned char *pin,
        int len,
        pcallback pcb,
        const char *pline_head,
        const char *pline_end)
{
    const char * const pwr[] =
    {
        "00��߷��书��",
        "01�θ߷��书��",
        "02�εͷ��书��",
        "03��ͷ��书��",
    };

    pcb(pline_head);
    pcb("��������ͨ�Ų���");
    pcb(pline_end);
    if (dir == 0)   //����
    {
        CHK_APP_LEN(len, 2);
        sprintf(buf, "%s�����ŵ���[%02X]:", pline_head, pin[0]);
        pcb(buf);
        if (pin[0] < 64)
        {
            sprintf(buf, "%d��", pin[0]);
        }
        else if (pin[0] < 254)
        {
            sprintf(buf, "����");
        }
        else if (pin[0] == 254)
        {
            sprintf(buf, "�Զ�ѡ��");
        }
        else    //255
        {
            sprintf(buf, "���ֲ���");
        }
        pcb(buf);
        pcb(pline_end);

        sprintf(buf, "%s�������ڵ㷢�书��[%02X]:%s%s", pline_head, pin[1],
                (pin[1] < 4) ? pwr[pin[1]] : ((pin[1] == 254) ? "���ֲ���" : "����"), pline_end);
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
 * @brief   �������/��ֹ̨���ϱ�
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
AFN05_FN06(unsigned char dir,
        const unsigned char *pin,
        int len,
        pcallback pcb,
        const char *pline_head,
        const char *pline_end)
{
    pcb(pline_head);
    pcb("����/��ֹ̨���ϱ�"); //0��ֹ��1����
    pcb(pline_end);
    if (dir == 0)   //����
    {
        CHK_APP_LEN(len, 1);
        sprintf(buf, "%s̨��ʶ��ʹ�ܱ�־[%d]:%s%s", pline_head, pin[0],
                (pin[0] == 0) ? "����" : "��ֹ", pline_end);
        pcb(buf);
    }
    else    //����
    {
        //��
    }

    return ERR_NONE;
}

/**
 ******************************************************************************
 * @brief   ���ÿ���ز�ͨ�Ų���
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
AFN05_FN16(unsigned char dir,
        const unsigned char *pin,
        int len,
        pcallback pcb,
        const char *pline_head,
        const char *pline_end)
{
    const char * const type[] =
    {
        "1.953~11.96MHz",
        "2.441~5.615MHz",
        "0.781~2.930MHz",
        "1.758~2.930MHz",
    };

    if (dir == 0)   //����
    {
        CHK_APP_LEN(len, 1);  //���͵�����������һ�ֽ�
        sprintf(buf, "%s���ÿ���ز�ͨ�Ų���[%d]:%s%s", pline_head, pin[0],
                (pin[0] < 4) ? type[pin[0]] : "��Ч", pline_end);

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
 * @brief   ������ó�ǿ���޽����ַ���
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
AFN05_FN100(unsigned char dir,
        const unsigned char *pin,
        int len,
        pcallback pcb,
        const char *pline_head,
        const char *pline_end)
{
    pcb(pline_head);
    pcb("���ó�ǿ����");
    pcb(pline_end);
    if (dir == 0)   //���� todo
    {
        CHK_APP_LEN(len, 1);
        sprintf(buf, "%s���ʱʱ��[%02X]:%ds%s", pline_head,
                pin[0], pin[0], pline_end);
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
 * @brief   ����������Ľڵ�ʱ������ַ���
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
AFN05_FN101(unsigned char dir,
        const unsigned char *pin,
        int len,
        pcallback pcb,
        const char *pline_head,
        const char *pline_end)
{
    pcb(pline_head);
    pcb("�������Ľڵ�ʱ��");
    pcb(pline_end);
    if (dir == 0)   //���� todo
    {
        CHK_APP_LEN(len, 1);
        sprintf(buf, "%s���ʱʱ��[%02X]:%ds%s", pline_head,
                pin[0], pin[0], pline_end);
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
 * @brief   ���������������ַ���
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
print_AFN05(unsigned char dir,
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
        case 1: //�������ڵ��ַ
            return AFN05_FN01(dir, pin + 2, len - 2, pcb, pline_head, pline_end);
        case 2: //����ӽڵ��ϱ�
            return AFN05_FN02(dir, pin + 2, len - 2, pcb, pline_head, pline_end);
        case 3: //�����㲥
            return AFN05_FN03(dir, pin + 2, len - 2, pcb, pline_head, pline_end);
        case 4: //���ôӽڵ������ʱʱ��
            return AFN05_FN04(dir, pin + 2, len - 2, pcb, pline_head, pline_end);
        case 5: //��������ͨ�Ų���
            return AFN05_FN05(dir, pin + 2, len - 2, pcb, pline_head, pline_end);
        case 6: //����/��ֹ̨��ʶ��
            return AFN05_FN06(dir, pin + 2, len - 2, pcb, pline_head, pline_end);
        case 16: //���ÿ���ز�ͨ�Ų���
            return AFN05_FN16(dir, pin + 2, len - 2, pcb, pline_head, pline_end);
        case 100: //���ó�ǿ����
            return AFN05_FN100(dir, pin + 2, len - 2, pcb, pline_head, pline_end);
        case 101: //�������Ľڵ�ʱ��
            return AFN05_FN101(dir, pin + 2, len - 2, pcb, pline_head, pline_end);
        default:
            break;
    }

    pcb(pline_head);
    pcb("ERROR:��֧�ֵ�FN!");
    pcb(pline_end);

    return -ERR_AFN_FN;
}

/*--------------------------------AFN05.c------------------------------------*/
