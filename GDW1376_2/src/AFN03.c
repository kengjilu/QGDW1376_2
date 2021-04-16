/**
 ******************************************************************************
 * @file      AFN03.c
 * @brief     C Source file of AFN03.c.
 * @details   This file including all API functions's implement of AFN03.c.
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
 * @brief   ������̴���Ͱ汾��Ϣ�����ַ���
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
AFN03_FN01(unsigned char dir,
        const unsigned char *pin,
        int len,
        pcallback pcb,
        const char *pline_head,
        const char *pline_end)
{
    pcb(pline_head);
    pcb("���̴���Ͱ汾��Ϣ");
    pcb(pline_end);
    if (dir == 0)   //����
    {
        CHK_APP_LEN(len, 0);
    }
    else    //����
    {
        CHK_APP_LEN(len, 9);

        sprintf(buf, "%s  ���̴���[%02X %02X]:%c%c%s", pline_head, pin[0], pin[1], pin[0], pin[1], pline_end);
        pcb(buf);
        sprintf(buf, "%s  оƬ����[%02X %02X]:%c%c%s", pline_head, pin[2], pin[3], pin[2], pin[3], pline_end);
        pcb(buf);
        sprintf(buf, "%s  �汾����[%02X %02X %02X]:%02x��%02x��%02x��%s", pline_head, pin[6], pin[5], pin[4], pin[6], pin[5], pin[4], pline_end);
        pcb(buf);
        sprintf(buf, "%s  �汾[%02X %02X]:%02x.%02x%s", pline_head, pin[7], pin[8], pin[7], pin[8], pline_end);
        pcb(buf);
    }

    return ERR_NONE;
}

/**
 ******************************************************************************
 * @brief   �������ֵ�����ַ���
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
AFN03_FN02(unsigned char dir,
        const unsigned char *pin,
        int len,
        pcallback pcb,
        const char *pline_head,
        const char *pline_end)
{
    pcb(pline_head);
    pcb("����ֵ");
    pcb(pline_end);
    if (dir == 0)   //����
    {
        CHK_APP_LEN(len, 0);
    }
    else    //����
    {
        CHK_APP_LEN(len, 1);
        sprintf(buf, "%s����ֵ:%d%s", pline_head, pin[0] & 0x0f, pline_end);
        pcb(buf);
    }

    return 0;
}

/**
 ******************************************************************************
 * @brief   ����ӽڵ�������Ϣ�����ַ���
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
AFN03_FN03(unsigned char dir,
        const unsigned char *pin,
        int len,
        pcallback pcb,
        const char *pline_head,
        const char *pline_end)
{
    int i;

    pcb(pline_head);
    pcb("�ӽڵ�������Ϣ");
    pcb(pline_end);
    if (dir == 0)   //����
    {
        CHK_APP_LEN(len, 2);
        sprintf(buf, "%s��ʼ�ڵ�ָ��:%d%s", pline_head, pin[0], pline_end);
        pcb(buf);
        sprintf(buf, "%s��ȡ�ڵ������N<=16:%d%s", pline_head, pin[1], pline_end);
        pcb(buf);
    }
    else    //����
    {
        CHK_APP_LEN(len, 2 + pin[1] * 8);
        sprintf(buf, "%s�������Ĵӽڵ�������:%d%s", pline_head, pin[0], pline_end);
        pcb(buf);
        sprintf(buf, "%s�������ı�֡����Ĵӽڵ�����:%d%s", pline_head, pin[1], pline_end);
        pcb(buf);

        for (i = 0; i < pin[1]; i++)
        {
            sprintf(buf, "%s�ӽڵ��ַ%d:[%02X %02X %02X %02X %02X %02X]%s",
                    pline_head, i, pin[i * 8 + 2], pin[i * 8 + 3],
                    pin[i * 8 + 4], pin[i * 8 + 5], pin[i * 8 + 6],
                    pin[i * 8 + 7], pline_end);
            pcb(buf);

            sprintf(buf, "%s�м̼���:%d%s", pline_head, pin[i * 8 + 8] & 0x0f, pline_end);
            pcb(buf);
            sprintf(buf, "%s�����ź�Ʒ��:%d%s", pline_head, pin[i * 8 + 8] >> 4, pline_end);
            pcb(buf);
            sprintf(buf, "%s��������:%d%s", pline_head, pin[i * 8 + 9] & 0x0f, pline_end);
            pcb(buf);
        }
    }

    return 0;
}

/**
 ******************************************************************************
 * @brief   ������ڵ��ַ�����ַ���
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
AFN03_FN04(unsigned char dir,
        const unsigned char *pin,
        int len,
        pcallback pcb,
        const char *pline_head,
        const char *pline_end)
{
    pcb(pline_head);
    pcb("���ڵ��ַ");
    pcb(pline_end);
    if (dir == 0)   //����
    {
        CHK_APP_LEN(len, 0);
    }
    else    //����
    {
        CHK_APP_LEN(len, 6);
        sprintf(buf, "%s���ڵ��ַ:[%02X %02X %02X %02X %02X %02X]%s",
                pline_head, pin[0], pin[1], pin[2], pin[3], pin[4], pin[5],
                pline_end);
        pcb(buf);
    }

    return 0;
}

/**
 ******************************************************************************
 * @brief   ������ڵ�״̬�ֺ�ͨ�����ʽ����ַ���
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
AFN03_FN05(unsigned char dir,
        const unsigned char *pin,
        int len,
        pcallback pcb,
        const char *pline_head,
        const char *pline_end)
{
    int i;
    const char * const mode[] =
    {
        "00ͨ��ģ������ֳ���ģʽ��֧��",
        "01ͨ��ģ���֧�ּ����������ĳ���ģʽ",
        "10ͨ��ģ���֧��·�������ĳ���ģʽ",
        "11��Ч",
    };
    const char * const feature[] =
    {
        "΢��������",
        "���๩�絥�ഫ��",
        "���๩�����ഫ��",
        "���๩�����ഫ��",
    };

    pcb(pline_head);
    pcb("���ڵ�״̬�ֺ�ͨ������");
    pcb(pline_end);
    if (dir == 0)   //����
    {
        CHK_APP_LEN(len, 0);
    }
    else    //����
    {
        sprintf(buf, "%s���ڳ���ģʽ[%d]:%s%s", pline_head, pin[0] >> 6,
                mode[pin[0] >> 6], pline_end);
        pcb(buf);
        sprintf(buf, "%s���ڳ���ģʽ[%d]:%s%s", pline_head, (pin[0] >> 4) & 0x03,
                feature[(pin[0] >> 4) & 0x03], pline_end);
        pcb(buf);
        sprintf(buf, "%s��������:%d%s", pline_head, pin[0] & 0x0f, pline_end);
        pcb(buf);
        sprintf(buf, "%s�ŵ�����:%d%s", pline_head, pin[1] & 0x0f, pline_end);
        pcb(buf);
        if (((pin[0] & 0x0f) * 2 + 2) > len)
        {
            return -1;
        }
        for (i = 0; i < (pin[0] & 0x0f); i++)
        {
            sprintf(buf, "%sͨ������[%02X %02X]:%d%s%s", pline_head,
                    pin[i*2 + 2], pin[i*2 + 2 + 1],
                    pin[i*2 + 2] | ((int)(pin[i*2 + 2 + 1] & 0x7f) << 8),
                    (pin[i*2 + 2 + 1] & 0x80) ? "kbit/s" : "bit/s",pline_end);
            pcb(buf);
        }
    }

    return 0;
}

/**
 ******************************************************************************
 * @brief   ������ڵ����״̬�����ַ���
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
AFN03_FN06(unsigned char dir,
        const unsigned char *pin,
        int len,
        pcallback pcb,
        const char *pline_head,
        const char *pline_end)
{
    pcb(pline_head);
    pcb("���ڵ����״̬");
    pcb(pline_end);
    if (dir == 0)   //����
    {
        CHK_APP_LEN(len, 1);
        sprintf(buf, "%s����ʱ��:%d min(ָ�ȴ���ѯִ�е�ʱ��)%s",
                pline_head, pin[0], pline_end);
        pcb(buf);
    }
    else    //����
    {
        CHK_APP_LEN(len, 1);
        sprintf(buf, "%s���ڵ����״̬[%d]:%s����%s", pline_head, pin[0],
                pin[0] ? "��" : "û��", pline_end);
        pcb(buf);
    }

    return 0;
}

/**
 ******************************************************************************
 * @brief   �����ȡ�ӽڵ������ʱʱ������ַ���
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
AFN03_FN07(unsigned char dir,
        const unsigned char *pin,
        int len,
        pcallback pcb,
        const char *pline_head,
        const char *pline_end)
{
    pcb(pline_head);
    pcb("��ȡ�ӽڵ������ʱʱ��");
    pcb(pline_end);
    if (dir == 0)   //����
    {
        CHK_APP_LEN(len, 0);
    }
    else    //����
    {
        CHK_APP_LEN(len, 1);
        sprintf(buf, "%s���ʱʱ��[%02X]:%ds%s", pline_head,
                pin[0], pin[0], pline_end);
        pcb(buf);
    }

    return 0;
}

/**
 ******************************************************************************
 * @brief   �����ѯ����ͨ�Ų��������ַ���
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
AFN03_FN08(unsigned char dir,
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
    pcb("��ѯ����ͨ�Ų���");
    pcb(pline_end);
    if (dir == 0)   //����
    {
        CHK_APP_LEN(len, 0);
    }
    else    //����
    {
        CHK_APP_LEN(len, 2);
        sprintf(buf, "%s�����ŵ���0~63[%02X]:%d%s", pline_head, pin[0],
                pin[0], pline_end);
        pcb(buf);
        sprintf(buf, "%s�������ڵ㷢�书��[%02X]:%s%s", pline_head, pin[1],
                (pin[1] < 4) ? pwr[pin[1]] : "��Ч", pline_end);
        pcb(buf);
    }

    return 0;
}

/**
 ******************************************************************************
 * @brief   �����ѯ�ӽڵ�ͨ����ʱ�����ַ���
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
AFN03_FN09(unsigned char dir,
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
    pcb("��ѯ�ӽڵ�ͨ����ʱ");
    pcb(pline_end);
    if (dir == 0)   //����
    {
        sprintf(buf, "%sͨ��Э������[%d]:%s%s",
                pline_head, pin[0],
                (pin[0] < 4) ? type[pin[0]] : "��Ч",
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
        sprintf(buf, "%s�㲥ͨ���ӳ�ʱ��[%02X %02X]:%ds%s", pline_head,
                pin[0], pin[1], pin[0] | ((int)pin[1] << 8), pline_end);
        pcb(buf);
        sprintf(buf, "%sͨ��Э������[%d]:%s%s",
                pline_head, pin[2],
                (pin[2] < 4) ? type[pin[2]] : "��Ч",
                pline_end);
        pcb(buf);

        sprintf(buf, "%s���ĳ���L:%d%s", pline_head, pin[3], pline_end);
        pcb(buf);

        pcb(pline_head);
        pcb(" ��������:");
        pcb(pline_end);
        pcb(pline_head);
        for (i = 0; i < pin[3]; i++)
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

    return 0;
}

/**
 ******************************************************************************
 * @brief   �������ͨ��ģ������ģʽ��Ϣ�����ַ���
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
AFN03_FN10(unsigned char dir,
        const unsigned char *pin,
        int len,
        pcallback pcb,
        const char *pline_head,
        const char *pline_end)
{
    int i;

    pcb(pline_head);
    pcb("����ͨ��ģ������ģʽ��Ϣ");
    pcb(pline_end);
    if (dir == 0)   //����
    {
        CHK_APP_LEN(len, 0);
    }
    else    //����
    {
        CHK_APP_LEN(len, 39 + 2 * (pin[3] & 0x0f));
        /* 1. ͨ�ŷ�ʽ */
        sprintf(buf, "%sͨ�ŷ�ʽ[%d]:", pline_head, pin[0] & 0x0f);
        pcb(buf);
        switch (pin[0] & 0x0f)
        {
            case 1:
                pcb("խ���������ز�ͨ��");
                break;
            case 2:
                pcb("����������ز�ͨ��");
                break;
            case 3:
                pcb("΢��������ͨ��");
                break;
            default:
                pcb("��������");
                break;
        }
        pcb(pline_end);
        /* 2. ·�ɹ���ʽ */
        sprintf(buf, "%s·�ɹ���ʽ [%d]:%s%s", pline_head, (BITS(pin[0], 4)),
                (BITS(pin[0], 4)) ? "�㲥����Ҫ���ݱ����е��ŵ���ʶ���������"
                        : "ִ�й㲥�����Ҫ�ŵ���ʶ", pline_end);
        pcb(buf);
        /* 3. �ӽڵ���Ϣģʽ */
        sprintf(buf, "%s�ӽڵ���Ϣģʽ[%d]:%s%s", pline_head, (BITS(pin[0], 5)),
                (BITS(pin[0], 5)) ? "��ʾ��Ҫ�·��ӽڵ���Ϣ"
                        : "��ʾ����Ҫ�·��ӽڵ���Ϣ", pline_end);
        pcb(buf);
        /* 4. ���ڳ���ģʽ */
        sprintf(buf, "%s���ڳ���ģʽ[%d]:", pline_head, pin[0] >> 6u);
        pcb(buf);
        switch (pin[0] >> 6u)
        {
            case 1:
                pcb("��ʾͨ��ģ���֧�ּ����������ĳ���ģʽ");
                break;
            case 2:
                pcb("��ʾͨ��ģ���֧��·�������ĳ���ģʽ");
                break;
            case 3:
                pcb("��ʾͨ��ģ������ֳ���ģʽ��֧��");
                break;
            default:
                pcb("��������");
                break;
        }
        pcb(pline_end);
        /*
         * 5. ������ʱ����֧��
         *   ��D2��D1��D0������λ��ʾ���ֱ����㲥���ӽڵ��ء�·�����������
         *   ��������֧���������ṩ������ʱ�����������
         *   1 ��ʾ֧���ṩ������ʱ����
         *   0 ��ʾ��֧��
         */
        sprintf(buf, "%s������ʱ����֧��[%d]:%s", pline_head, pin[1] & 0x03, pline_end);
        pcb(buf);
        sprintf(buf, "%s          �㲥:%s%s", pline_head, BITS(pin[1], 2) ? "֧��" : "��֧��", pline_end);
        pcb(buf);
        sprintf(buf, "%s    �ӽڵ���:%s%s", pline_head, BITS(pin[1], 1) ? "֧��" : "��֧��", pline_end);
        pcb(buf);
        sprintf(buf, "%s  ·����������:%s%s", pline_head, BITS(pin[1], 0) ? "֧��" : "��֧��", pline_end);
        pcb(buf);
        /*
         * 6. ʧ�ܽڵ��л�����ʽ
         *   D3��1 ��ʾͨ��ģ�������л������ڵ�
         *   D4��1 ��ʾ����������֪ͨͨ��ģ���л������ڵ�
         */
        sprintf(buf, "%sʧ�ܽڵ��л�����ʽ[%d]:", pline_head, (pin[1] >> 3) & 0x03);
        pcb(buf);
        switch ((pin[1] >> 3) & 0x03)
        {
            case 1:
                pcb("��ʾͨ��ģ�������л������ڵ�");
                break;
            case 2:
                pcb("��ʾ����������֪ͨͨ��ģ���л������ڵ�");
                break;
            default:
                pcb("����");
                break;
        }
        pcb(pline_end);
        /*
         * 7. �㲥����ȷ�Ϸ�ʽ
         *   0 ��ʾ�㲥�����ڱ���ͨ��ģ��ִ�й㲥ͨ�Ź�����Ϻ󷵻�ȷ�ϱ���
         *   1 ��ʾ�㲥�����ڱ����ŵ�ִ�й㲥ͨ��֮ǰ�ͷ���ȷ�ϱ��ģ�
         *     ��Ҫ�������ȴ���ʱ����ȷ�ϱ��ĵ�"�ȴ�ִ��ʱ��"��Ϣ������
         */
        sprintf(buf, "%s�㲥����ȷ�Ϸ�ʽ[%d]:%s%s", pline_head, (BITS(pin[1], 5)),
                (BITS(pin[1], 5)) ? "�㲥�����ڱ����ŵ�ִ�й㲥ͨ��֮ǰ�ͷ���ȷ�ϱ�����Ҫ�������ȴ���ʱ����ȷ�ϱ��ĵ�\"�ȴ�ִ��ʱ��\"��Ϣ������"
                        : "�㲥�����ڱ���ͨ��ģ��ִ�й㲥ͨ�Ź�����Ϻ󷵻�ȷ�ϱ���", pline_end);
        pcb(buf);
        /*
         * 8. �㲥�����ŵ�ִ�з�ʽ
         *   0 ��ʾִ�й㲥�����Ҫ�ŵ���ʶ
         *   1 ��ʾ�㲥����Ҫ���ݱ����е��ŵ���ʶ���������
         *   ����ȡֵ����
         */
        sprintf(buf, "%s�㲥�����ŵ�ִ�з�ʽ[%d]:", pline_head, pin[1] >> 6);
        pcb(buf);
        switch (pin[1] >> 6)
        {
            case 0:
                pcb("��ʾִ�й㲥�����Ҫ�ŵ���ʶ");
                break;
            case 1:
                pcb("��ʾ�㲥����Ҫ���ݱ����е��ŵ���ʶ���������");
                break;
            default:
                pcb("����");
                break;
        }
        pcb(pline_end);
        /* 9. �ŵ����� */
        sprintf(buf, "%s�ŵ�����[%d]%s", pline_head, pin[2] & 0x1f, pline_end);
        pcb(buf);
        /*
         * 10. ��ѹ����������Ϣ(�����ڴ��й����߼��ŵ��ĵ�ѹ�������ز���Ч)
         *   ��D7��D6��D5������λ��ʾ���ֱ��ʾA B C����ĵ�����Ϣ
         *   0 ��ʾδ���� 1 ��ʾ����
         */
        sprintf(buf, "%s��ѹ����������Ϣ[%d]%s", pline_head, pin[2] >> 5, pline_end);
        pcb(buf);
        sprintf(buf, "  A��:%s", BITS(pin[2], 7) ? "����" : "δ����");
        pcb(buf);
        sprintf(buf, "  B��:%s", BITS(pin[2], 6) ? "����" : "δ����");
        pcb(buf);
        sprintf(buf, "  C��:%s%s", BITS(pin[2], 5) ? "����" : "δ����", pline_end);
        pcb(buf);
        /* 11. ��������n */
        sprintf(buf, "%s��������n[%d]%s", pline_head, (pin[3] & 0x0f), pline_end);
        pcb(buf);
        /* 12. �ӽڵ������ʱʱ�� */
        sprintf(buf, "%s�ӽڵ������ʱʱ��[%02X]:%ds%s", pline_head,
                pin[6], pin[6], pline_end);
        pcb(buf);
        /* 13. �㲥�������ʱʱ�� */
        sprintf(buf, "%s�㲥�������ʱʱ��[%02X %02X]:%ds%s", pline_head,
                pin[7], pin[8], (pin[8] << 8) | pin[7], pline_end);
        pcb(buf);
        /* 14. ���֧�ֵı��ĳ��� */
        sprintf(buf, "%s���֧�ֵı��ĳ���[%02X %02X]:%d%s", pline_head,
                pin[9], pin[10], (pin[10] << 8) | pin[9], pline_end);
        pcb(buf);
        /* 15. �ļ�����֧�ֵ���󵥸����ݰ����� */
        sprintf(buf, "%s�ļ�����֧�ֵ���󵥸����ݰ�����[%02X %02X]:%d%s", pline_head,
                pin[11], pin[12], (pin[12] << 8) | pin[11], pline_end);
        pcb(buf);
        /* 16. ���������ȴ�ʱ�� */
        sprintf(buf, "%s���������ȴ�ʱ��[%02X]:%ds%s", pline_head,
                pin[13], pin[13], pline_end);
        pcb(buf);
        /* 17. ���ڵ��ַ */
        sprintf(buf, "%s���ڵ��ַ:[%02X %02X %02X %02X %02X %02X]%s",
                pline_head, pin[14], pin[15], pin[16], pin[17], pin[18], pin[19],
                pline_end);
        pcb(buf);
        /* 18. ֧�����ӽڵ����� */
        sprintf(buf, "%s֧�����ӽڵ�����[%02X %02X]:%d%s", pline_head,
                pin[20], pin[21], (pin[21] << 8) | pin[20], pline_end);
        pcb(buf);
        /* 18. ��ǰ�ӽڵ����� */
        sprintf(buf, "%s��ǰ�ӽڵ�����[%02X %02X]:%d%s", pline_head,
                pin[22], pin[23], (pin[23] << 8) | pin[22], pline_end);
        pcb(buf);
        /* 19. ͨ��ģ��ʹ�õ�Э�鷢������(BCD) YYMMDD */
        sprintf(buf, "%sͨ��ģ��ʹ�õ�Э�鷢������[%02X %02X %02X]:%02X-%02X-%02X%s", pline_head,
                pin[24], pin[25], pin[26], pin[24], pin[25], pin[26], pline_end);
        pcb(buf);
        /* 20. ͨ��ģ��ʹ�õ�Э����󱸰�����(BCD) YYMMDD */
        sprintf(buf, "%sͨ��ģ��ʹ�õ�Э����󱸰�����[%02X %02X %02X]:%02X-%02X-%02X%s", pline_head,
                pin[27], pin[28], pin[29], pin[27], pin[28], pin[29], pline_end);
        pcb(buf);
        /* 21. ͨ��ģ�鳧�̴��뼰�汾��Ϣ */
        sprintf(buf, "%s  ���̴���[%02X %02X]:%c%c%s", pline_head, pin[31], pin[30], pin[31], pin[30], pline_end);
        pcb(buf);
        sprintf(buf, "%s  оƬ����[%02X %02X]:%c%c%s", pline_head, pin[33], pin[32], pin[33], pin[32], pline_end);
        pcb(buf);
        sprintf(buf, "%s  �汾����[%02X %02X %02X]:%02x��%02x��%02x��%s", pline_head, pin[36], pin[35], pin[34], pin[36], pin[35], pin[34], pline_end);
        pcb(buf);
        sprintf(buf, "%s  �汾[%02X %02X]:%02x.%02x%s", pline_head, pin[37], pin[38], pin[37], pin[38], pline_end);
        pcb(buf);

        for (i = 0; i < (pin[3] & 0x0f); i++)
        {
            sprintf(buf, "%sͨ������[%02X %02X]:%d%s%s", pline_head,
                    pin[i*2 + 39], pin[i*2 + 39 + 1],
                    pin[i*2 + 39] | ((int)(pin[i*2 + 39 + 1] & 0x7f) << 8),
                    (pin[i*2 + 39 + 1] & 0x80) ? "kbit/s" : "bit/s",pline_end);
            pcb(buf);
        }
    }

    return 0;
}

/**
 ******************************************************************************
 * @brief   �������ͨ��ģ��AFN���������ַ���
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
AFN03_FN11(unsigned char dir,
        const unsigned char *pin,
        int len,
        pcallback pcb,
        const char *pline_head,
        const char *pline_end)
{
    int cnt = 0;
    int i;

    pcb(pline_head);
    pcb("����ͨ��ģ��AFN����");
    pcb(pline_end);
    if (dir == 0)   //����
    {
        CHK_APP_LEN(len, 1);
        sprintf(buf, "%sAFN������[0x%02X]:%d%s",
                pline_head, pin[0], pin[0], pline_end);
        pcb(buf);
    }
    else    //����
    {
        CHK_APP_LEN(len, 1 + 32);
        sprintf(buf, "%sAFN������[0x%02X]:%d%s",
                pline_head, pin[0], pin[0], pline_end);
        pcb(buf);
        sprintf(buf, "%s֧��FN:", pline_head);
        pcb(buf);
        for (i = 0; i < 32 * 8; i++)
        {
            if (BITS(pin[1 + i / 8], i))
            {
                if (!(cnt % 10))
                {
                    sprintf(buf, "%s  ", pline_end);
                    pcb(buf);
                }
                sprintf(buf, "F%d��", i + 1);
                pcb(buf);
                cnt++;
            }
        }
        pcb(pline_end);
    }

    return 0;
}

/**
 ******************************************************************************
 * @brief   �����ѯ��ǿ���޽����ַ���
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
AFN03_FN100(unsigned char dir,
        const unsigned char *pin,
        int len,
        pcallback pcb,
        const char *pline_head,
        const char *pline_end)
{
    pcb(pline_head);
    pcb("��ѯ��ǿ����");
    pcb(pline_end);
    if (dir == 0)   //����
    {
        CHK_APP_LEN(len, 0);
    }
    else    //����
    {
        CHK_APP_LEN(len, 1);
        sprintf(buf, "%s��ǿ����[0x%02X]:%d(ȡֵ50~120,Ĭ��96)%s",
                pline_head, pin[0], pin[0], pline_end);
        pcb(buf);
    }

    return 0;
}

/**
 ******************************************************************************
 * @brief   �����ѯ���ݽ����ַ���
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
print_AFN03(unsigned char dir,
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
        case 1: //���̴���Ͱ汾��Ϣ
            return AFN03_FN01(dir, pin + 2, len - 2, pcb, pline_head, pline_end);
        case 2: //����ֵ
            return AFN03_FN02(dir, pin + 2, len - 2, pcb, pline_head, pline_end);
        case 3: //�ӽڵ�������Ϣ
            return AFN03_FN03(dir, pin + 2, len - 2, pcb, pline_head, pline_end);
        case 4: //���ڵ��ַ
            return AFN03_FN04(dir, pin + 2, len - 2, pcb, pline_head, pline_end);
        case 5: //���ڵ�״̬�ֺ�ͨ������
            return AFN03_FN05(dir, pin + 2, len - 2, pcb, pline_head, pline_end);
        case 6: //���ڵ����״̬
            return AFN03_FN06(dir, pin + 2, len - 2, pcb, pline_head, pline_end);
        case 7: //��ȡ�ӽڵ������ʱʱ��
            return AFN03_FN07(dir, pin + 2, len - 2, pcb, pline_head, pline_end);
        case 8: //��ѯ����ͨ�Ų���
            return AFN03_FN08(dir, pin + 2, len - 2, pcb, pline_head, pline_end);
        case 9: //��ѯ�ӽڵ�ͨ����ʱ
            return AFN03_FN09(dir, pin + 2, len - 2, pcb, pline_head, pline_end);
        case 10: //����ͨ��ģ������ģʽ��Ϣ
            return AFN03_FN10(dir, pin + 2, len - 2, pcb, pline_head, pline_end);
        case 11: //����ͨ��ģ��AFN����
            return AFN03_FN11(dir, pin + 2, len - 2, pcb, pline_head, pline_end);
//        case 12: //todo: ѯ�������ڵ�ͨ��ģ�� ID����Ϣ
//            return AFN03_FN12(dir, pin + 2, len - 2, pcb, pline_head, pline_end);
//        case 16: //todo: ��ѯ����ز�ͨ�Ų���
//            return AFN03_FN16(dir, pin + 2, len - 2, pcb, pline_head, pline_end);
        case 100: //��ѯ��ǿ����
            return AFN03_FN100(dir, pin + 2, len - 2, pcb, pline_head, pline_end);
        default:
            break;
    }

    pcb(pline_head);
    pcb("ERROR:��֧�ֵ�FN!");
    pcb(pline_end);

    return -ERR_AFN_FN;
}

/*--------------------------------AFN03.c------------------------------------*/
