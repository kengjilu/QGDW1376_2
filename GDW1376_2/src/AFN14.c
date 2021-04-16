/**
 ******************************************************************************
 * @file      AFN14.c
 * @brief     C Source file of AFN14.c.
 * @details   This file including all API functions's implement of AFN14.c.
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
 * @brief   ���·�����󳭶����ݽ����ַ���
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
AFN14_FN01(unsigned char dir,
        const unsigned char *pin,
        int len,
        pcallback pcb,
        const char *pline_head,
        const char *pline_end)
{   int i=3, j=1, k=1;
    pcb(pline_head);
    pcb("·�����󳭶�����");
    pcb(pline_end);
    if (dir == 0)   //����
    {
        if(pin[0]==0)
        {
            pcb(pline_head);
            pcb("����ʧ��");
            pcb(pline_end);
        }
        else if(pin[0]==1)
        {
            pcb(pline_head);
            pcb("�����ɹ�");
            pcb(pline_end);
            pcb(pline_head);
            pcb("·���������ݳ���L=0,�ӽڵ㸽���ڵ�����n=0");
            pcb(pline_end);
        }
        else if(pin[0]==2)
        {
            switch(pin[1])
            {
                case 0:
                    pcb(pline_head);
                    pcb("��ǰͨ�ŵ�Ӧ�����ݺͱ����ŵ���ͨ����ʱ�޹�");
                    pcb(pline_end);
                    break;
                case 1:
                    pcb(pline_head);
                    pcb("��ǰͨ�ŵ�Ӧ�����ݺͱ����ŵ���ͨ����ʱ���");
                    pcb(pline_end);
                    break;
                default:
                    break;
            }
            sprintf(buf, "%s·���������ݳ���L=%d%s", pline_head, pin[2],pline_end);
            pcb(buf);
            pcb(pline_head);
            pcb("·��������������Ϊ");
            for(i=3; i<(3+pin[2]); i++)
            {
              (void)sprintf(buf, "%02X ", pin[i]);
              pcb(buf);
            }
            if(pin[3+pin[2]]>0)
            {
                pcb(pline_end);
                sprintf(buf, "%s�ӽڵ㸽���ڵ�����n=%d%s", pline_head, pin[3+pin[2]], pline_end);
                pcb(buf);
                for(j=1; j<pin[3+pin[3]]; j++)
                {
                  pcb(pline_head);
                  sprintf(buf, "�ӽڵ㸽���ڵ�%d��ַΪ", j);
                  pcb(buf);
                  for(k=1; k<7; k++)
                  {
                   (void)sprintf(buf, "%02X", pin[4+pin[3]+k]);
                    pcb(buf);
                  }
                   pcb(pline_end);
                }
            }
            else
            {
                pcb(pline_end);
                sprintf(buf, "%s�ӽڵ㸽���ڵ�����n=%d%s", pline_head, pin[3+pin[2]], pline_end);
                pcb(buf);
            }
        }
    }
    else    //����
    {
        sprintf(buf, "%sͨ����λ[%d]:%s%d��%s", pline_head, pin[0],
                (pin[0] == 0) ? "δ֪��," : "", pin[0], pline_end);
        pcb(buf);
        sprintf(buf, "%s�ӽڵ��ַ:[%02X %02X %02X %02X %02X %02X]%s",
                pline_head, pin[1], pin[2], pin[3], pin[4], pin[5], pin[6],
                pline_end);
        pcb(buf);
        sprintf(buf, "%s�ӽڵ����[%02X %02X]:%d%s", pline_head,
                pin[7], pin[8],
                pin[7] | ((int)pin[8] << 8), pline_end);
        pcb(buf);
    }

    return 0;
}

/**
 ******************************************************************************
 * @brief   ���·����������ʱ�ӽ����ַ���
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
AFN14_FN02(unsigned char dir,
        const unsigned char *pin,
        int len,
        pcallback pcb,
        const char *pline_head,
        const char *pline_end)
{
    pcb(pline_head);
    pcb("·����������ʱ��");
    pcb(pline_end);
    if (dir == 0)   //����
    {
        CHK_APP_LEN(len, 6);
        (void)sprintf(buf, "%s%x��%x��%x��%xʱ%x��%x��%s", pline_head, pin[5], pin[4],
                pin[3], pin[2], pin[1], pin[0], pline_end);
        pcb(buf);
    }
    else    //����
    {
        pcb(pline_head);
        pcb("�����ݵ�Ԫ");
        pcb(pline_end);
    }

    return 0;
}

/**
 ******************************************************************************
 * @brief   ���������ͨ����ʱ����ͨ�����ݽ����ַ���
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
AFN14_FN03(unsigned char dir,
        const unsigned char *pin,
        int len,
        pcallback pcb,
        const char *pline_head,
        const char *pline_end)
{
    int i;

    pcb(pline_head);
    pcb("������ͨ����ʱ����ͨ������");
    pcb(pline_end);
    if (dir == 0)   //����
    {
        (void)sprintf(buf, "%s���ݳ���LΪ%x%s", pline_head, pin[0], pline_end);
        pcb(buf);
        pcb(pline_head);
        pcb("����ͨ����������Ϊ");
        for(i=1; i<pin[0]; i++)
        {
            (void)sprintf(buf, "%02X ", pin[i]);
            pcb(buf);
        }
        pcb(pline_end);
    }
    else    //����
    {
        sprintf(buf, "%s�ӽڵ��ַ:[%02X %02X %02X %02X %02X %02X]%s",
                pline_head, pin[0], pin[1], pin[2], pin[3], pin[4], pin[5],
                pline_end);
        pcb(buf);
        sprintf(buf, "%sԤ���ӳ�ʱ��[%02X %02X]:%ds%s", pline_head,
                pin[6], pin[7],
                pin[6] | ((int)pin[7] << 8), pline_end);
        pcb(buf);
        sprintf(buf, "%s������Ϣ����L:%d%s", pline_head, pin[8], pline_end);
        pcb(buf);

        pcb(pline_head);
        pcb(" ��������:");
        pcb(pline_end);
        pcb(pline_head);
        for (i = 0; i < pin[8]; i++)
        {
            sprintf(buf, "%02X ", pin[i + 9]);
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
 * @brief   ���·�����ݳ��������ַ���
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
print_AFN14(unsigned char dir,
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
        case 1: //·�����󳭶�����
            return AFN14_FN01(dir, pin + 2, len - 2, pcb, pline_head, pline_end);
        case 2: //·����������ʱ��
            return AFN14_FN02(dir, pin + 2, len - 2, pcb, pline_head, pline_end);
        case 3: //������ͨ����ʱ����ͨ������
            return AFN14_FN03(dir, pin + 2, len - 2, pcb, pline_head, pline_end);
//        case 4: //todo: ·�����󽻲���Ϣ
//            return AFN14_FN04(dir, pin + 2, len - 2, pcb, pline_head, pline_end);
        default:
            break;
    }

    pcb(pline_head);
    pcb("ERROR:��֧�ֵ�FN!");
    pcb(pline_end);

    return -ERR_AFN_FN;
}

/*--------------------------------AFN14.c------------------------------------*/
