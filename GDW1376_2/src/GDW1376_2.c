/**
 ******************************************************************************
 * @file      GDW1376_2.c
 * @brief     C Source file of GDW1376_2.c.
 * @details   This file including all API functions's implement of GDW1376_2.c.
 * @copyright
 ******************************************************************************
 */
 
/*-----------------------------------------------------------------------------
 Section: Includes
 ----------------------------------------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include "types.h"
#include "maths.h"
#include "../inc/GDW1376_2.h"
#include "chkfrm.h"
#include "AFN.h"
#include "lib.h"

/*-----------------------------------------------------------------------------
 Section: Type Definitions
 ----------------------------------------------------------------------------*/
#pragma pack(push, 1)
typedef struct
{
    unsigned char type:6;       /**< ͨѶ��ʽ */
    unsigned char dir:1;        /**< ����λ,0-����, 1-���� */
    unsigned char prm:1;        /**< ����λ,1-����, 0-�Ӷ� */
} ctrl_t;
#pragma pack(pop)

/*-----------------------------------------------------------------------------
 Section: Constant Definitions
 ----------------------------------------------------------------------------*/
#define VER_STR         "v0.0.1"    /**< �汾�ַ��� */
#define CHANGE_LOG  \
        "-----------------------------------\n"\
        "2014��2��24��:��ɽ������\n"\
        ""

/*-----------------------------------------------------------------------------
 Section: Global Variables
 ----------------------------------------------------------------------------*/
/* NONE */

/*-----------------------------------------------------------------------------
 Section: Local Variables
 ----------------------------------------------------------------------------*/
static int user_data_pos = 0;
//static unsigned char AFN = 0;
//static unsigned int fn = 0;

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
 * @brief   ���ԭʼ����
 * @param[in]  *pin         : ���뱨��
 * @param[in]   len         : ���뱨�ĳ���
 * @param[in]  *pcb         : �ص�����
 * @param[in]  *pline_head  : ÿ����ʼ����ַ���
 * @param[in]  *pline_end   : ÿ�н�������ַ���
 *
 * @return  None
 ******************************************************************************
 */
static void
print_org(const unsigned char *pin,
        unsigned int len,
        pcallback pcb,
        const char *pline_head,
        const char *pline_end)
{
    int i;

    pcb(pline_head);
    pcb("--------------------ԭʼ����---------------------");
    pcb(pline_end);
    pcb(pline_head);
    for (i = 0; i < len; i++)
    {
        sprintf(buf, "%02X ", pin[i]);
        pcb(buf);
        if (((i + 1) % 16) == 0)
        {
            pcb(pline_end);
            pcb(pline_head);
        }
    }
    pcb(pline_end);
    pcb(pline_head);
    pcb("-------------------------------------------------");
    pcb(pline_end);
}

/**
 ******************************************************************************
 * @brief   ��ȡͨ�ŷ�ʽ����
 * @param[in]  commtype : ͨ�ŷ�ʽֵ
 *
 * @retval  ͨ�ŷ�ʽ�����ַ���
 ******************************************************************************
 */
static const char *
get_commtype_str(unsigned char commtype)
{
    if (commtype > 63)
    {
        return "��Чͨ�ŷ�ʽ";
    }

    switch (commtype)
    {
    	case 0:
    	    return "����";
        case 1:
            return "����ʽ·���ز�ͨ��";
        case 2:
            return "�ֲ�ʽ·���ز�ͨ��";
        case 3:
            return "����ز�ͨ��";
        case 10:
            return "΢��������ͨ��";
        case 20:
            return "��̫��ͨ��";
        default:
            break;
    }
    return "����";
}

/**
 ******************************************************************************
 * @brief   ��ȡ���ܱ�ͨ������
 * @param[in]  value : ���ܱ�ͨ������ֵ
 *
 * @retval  ���ܱ�ͨ������
 ******************************************************************************
 */
static const char *
get_meter_comm_type(unsigned char value)
{
    if (value > 15)
    {
        return "��Ч�ĵ��ܱ�ͨ������ֵ";
    }

    switch (value)
    {
        case 1:
            return "�����ŵ�Ϊ���๩��,�߼��ŵ�Ϊ���ŵ�";
        case 2:
            return "�����ŵ�Ϊ���๩��,�߼��ŵ�Ϊ���ŵ�";
        case 3:
            return "�����ŵ�Ϊ���๩��,�߼��ŵ�Ϊ���ŵ�";
        case 4:
            return "�����ŵ�Ϊ���๩��,�߼��ŵ�Ϊ���ŵ�";
        default:
            break;
    }
    return "����";
}

/**
 ******************************************************************************
 * @brief   ��ȡ���ܱ�ͨ������
 * @param[in]  value : ���ܱ�ͨ������ֵ
 *
 * @retval  ���ܱ�ͨ������
 ******************************************************************************
 */
static const char *
get_errcode_type(unsigned char value)
{
    if (value > 15)
    {
        return "��Ч";
    }

    switch (value)
    {
        case 0:
            return "δ����";
        case 1:
            return "RS����";
        default:
            break;
    }
    return "����";
}

/**
 ******************************************************************************
 * @brief   ��ȡAFN����
 * @param[in]  afn : AFNֵ
 *
 * @retval  AFN����
 ******************************************************************************
 */
static const char *
get_AFN_name(unsigned char afn)
{
    switch (afn)
    {
        case 0x00:
            return "ȷ��/����";
        case 0x01:
            return "��ʼ��";
        case 0x02:
            return "����ת��";
        case 0x03:
            return "��ѯ����";
        case 0x04:
            return "��·�ӿڼ��";
        case 0x05:
            return "��������";
        case 0x06:
            return "�����ϱ�";
        case 0x10:
            return "·�ɲ�ѯ";
        case 0x11:
            return "·������";
        case 0x12:
            return "·�ɿ���";
        case 0x13:
            return "·������ת��";
        case 0x14:
            return "·�����ݳ���";
        case 0x15:
            return "�ļ�����";
        case 0xf0:
            return "�ڲ�����";
        case 0xf1:
            return "��������";
        default:
            break;
    }
    return "����";
}
/**
 ******************************************************************************
 * @brief   ������Ľṹ����
 * @param[in]  *pin        : ���뱨��
 * @param[in]   len        : ���뱨�ĳ���
 * @param[in]  *pcb        : �ص�����
 * @param[in]  *pline_head : ÿ����ʼ����ַ���
 * @param[in]  *pline_end  : ÿ�н�������ַ���
 *
 * @return  None
 ******************************************************************************
 */
static void
print_struct(const unsigned char *pin,
        unsigned int len,
        pcallback pcb,
        const char *pline_head,
        const char *pline_end)
{
    int i;

    pcb(pline_head);
    pcb("------------------���Ľṹ����-------------------");
    pcb(pline_end);
    sprintf(buf, "%s���ĳ���:%d bytes%s", pline_head, len, pline_end);
    pcb(buf);
    pcb(pline_head);
    pcb("-------------------------------------------------");
    pcb(pline_end);
    //����
    sprintf(buf, "%s  L = [%02X %02X]  %d%s", pline_head, pin[1], pin[2],
            ((int)pin[1]) | (((int)pin[2]) << 8), pline_end);
    pcb(buf);
    //������
    sprintf(buf, "%s  C = [%02X] DIR =%d %s PRM=%d %s%s", pline_head, pin[3],
            BITS(pin[3], 7),
            BITS(pin[3], 7) ? "����(ģ��->������)" : "����(������->ģ��)",
            BITS(pin[3], 6),
            BITS(pin[3], 6) ? "����" : "�Ӷ�", pline_end);
    pcb(buf);
    sprintf(buf, "%s           TYPE=%d %s%s", pline_head, pin[3] & 0x3f,
            get_commtype_str(pin[3] & 0x3f), pline_end);
    pcb(buf);
    //��Ϣ��R
    sprintf(buf, "%s  R = [%02X %02X %02X %02X %02X %02X]%s", pline_head,
            pin[4], pin[5], pin[6], pin[7], pin[8], pin[9], pline_end);
    pcb(buf);

    if BITS(pin[3], 7)  //����
    {
        sprintf(buf, "%s      ·�ɱ�ʶ[%d]: %s%s", pline_head, pin[4] & 0x1,
                (pin[4] & 0x1) ? "ͨ��ģ�鲻��·�ɻ�������·ģʽ"
                        : "ͨ��ģ���·�ɻ�����·��ģʽ", pline_end);
        pcb(buf);
        sprintf(buf, "%s      ͨ��ģ���ʶ[%d]: %s%s", pline_head, (pin[4] >> 2) & 0x1,
                ( (pin[4] >> 2) & 0x1) ? "�Դӽڵ����" : "�����ڵ����", pline_end);
        pcb(buf);
        sprintf(buf, "%s      �м̼���[%d]: %s%s", pline_head, pin[4] >> 4,
                (pin[4] >> 4) ? "" : "���м�", pline_end);
        pcb(buf);
        sprintf(buf, "%s      �ŵ���ʶ[%d]: ��%d�ŵ�%s", pline_head, pin[5] & 0x0f,
                pin[5] & 0x0f, pline_end);
        pcb(buf);
        if (pin[6] & 0x0f)
        {
            sprintf(buf, "%s      ʵ�����߱�ʶ[%d]: ��%d��%s", pline_head, pin[6] & 0x0f,
                    pin[6] & 0x0f, pline_end);
        }
        else
        {
            sprintf(buf, "%s      ʵ�����߱�ʶ[0]: ��ȷ��%s", pline_head, pline_end);
        }
        pcb(buf);
        sprintf(buf, "%s      ���ܱ�ͨ������[%d]: %s%s", pline_head, pin[6] >> 8,
                get_meter_comm_type(pin[6] >> 8), pline_end);
        pcb(buf);
        sprintf(buf, "%s      ĩ�������ź�Ʒ��(0��1���)[%d]%s", pline_head,
                pin[7] & 0x0f, pline_end);
        pcb(buf);
        sprintf(buf, "%s      ĩ��Ӧ���ź�Ʒ��(0��1���)[%d]%s", pline_head,
                pin[7] >> 4, pline_end);
        pcb(buf);
        sprintf(buf, "%s      �¼���ʶ[%d]: %s%s", pline_head, pin[8] & 0x01,
                (pin[8] & 0x01) ? "���¼��ϱ�" : "���¼��ϱ�", pline_end);
        pcb(buf);
        sprintf(buf, "%s      �������к�[%d]%s", pline_head, pin[9], pline_end);
        pcb(buf);
    }
    else    //����
    {
        sprintf(buf, "%s      ·�ɱ�ʶ[%d]: %s%s", pline_head, pin[4] & 0x1,
                (pin[4] & 0x1) ? "ͨ��ģ�鲻��·�ɻ�������·ģʽ"
                        : "ͨ��ģ���·�ɻ�����·��ģʽ", pline_end);
        pcb(buf);
        sprintf(buf, "%s      �����ڵ��ʶ[%d]: %s���ӽڵ�%s", pline_head, BITS(pin[4], 1),
                BITS(pin[4], 1) ? "��" : "��", pline_end);
        pcb(buf);
        sprintf(buf, "%s      ͨ��ģ���ʶ[%d]: %s%s", pline_head, BITS(pin[4], 2),
                BITS(pin[4], 2) ? "�Դӽڵ����" : "�����ڵ����", pline_end);
        pcb(buf);
        sprintf(buf, "%s      ��ͻ���[%d]: %s���г�ͻ���%s", pline_head, BITS(pin[4], 3),
                BITS(pin[4], 3) ? "Ҫ" : "��", pline_end);
        pcb(buf);
        sprintf(buf, "%s      �м̼���[%d]: %s%s", pline_head, pin[4] >> 4,
                (pin[4] >> 4) ? "" : "���м�", pline_end);
        pcb(buf);
        if (pin[5] & 0x0f)
        {
            sprintf(buf, "%s      �ŵ���ʶ[%d]: ��%d�ŵ�%s", pline_head, pin[5] & 0x0f,
                    pin[5] & 0x0f, pline_end);
        }
        else
        {
            sprintf(buf, "%s      �ŵ���ʶ[%d]: �����ŵ�%s", pline_head,
                    pin[5] & 0x0f, pline_end);
        }
        pcb(buf);
        sprintf(buf, "%s      ��������ʶ[%d]: %s%s", pline_head, pin[5] >> 4,
                get_errcode_type(pin[5] >> 4), pline_end);
        pcb(buf);
        sprintf(buf, "%s      Ԥ��Ӧ���ֽ���[%02X]:%d%s", pline_head, pin[6], pin[6], pline_end);
        pcb(buf);
        sprintf(buf, "%s      ͨ������[%d]: %s%s%s", pline_head, pin[7] | (int)((pin[8] & 0x7f) << 8),
                (pin[7] | (int)((pin[8] & 0x7f) << 8)) ? "" : "Ĭ������",
                (pin[8] & 0x80) ? "kbit/s" : "bit/s", pline_end);
        pcb(buf);
        sprintf(buf, "%s      �������к�[%d]%s", pline_head, pin[9], pline_end);
        pcb(buf);
    }
    //��ַ��A
    if (pin[4] & 0x4)   //��Ϣ���"ͨ��ģ��� ʶ"Ϊ0ʱ,�޵�ַ��A
    {
        sprintf(buf, "%s  Դ��ַ  A1 = [%02X %02X %02X %02X %02X %02X]%s", pline_head,
                pin[10], pin[11], pin[12], pin[13], pin[14], pin[15], pline_end);
        pcb(buf);

        i = 0;
        if (!BITS(pin[3], 7))  //���б��Ĳ����м̵�ַ
        {
            for (i = 0; i < (pin[4] >> 4); i++)
            {
                sprintf(buf, "%s  �м̵�ַA2 = [%02X %02X %02X %02X %02X %02X]%s", pline_head,
                        pin[16 + i * 6], pin[17 + i * 6], pin[18 + i * 6],
                        pin[19 + i * 6], pin[20 + i * 6], pin[21 + i * 6], pline_end);
                pcb(buf);
            }
        }
        sprintf(buf, "%s  Ŀ�ĵ�ַA3 = [%02X %02X %02X %02X %02X %02X]%s", pline_head,
                pin[16 + i * 6], pin[17 + i * 6], pin[18 + i * 6],
                pin[19 + i * 6], pin[20 + i * 6], pin[21 + i * 6], pline_end);
        pcb(buf);
        user_data_pos = 22 + i * 6;
    }
    else
    {
        sprintf(buf, "%s  A = ��Ϣ���\"ͨ��ģ���ʶ\"Ϊ0ʱ,�޵�ַ��A%s",
                pline_head, pline_end);
        pcb(buf);
        user_data_pos = 10;
    }

    //Ӧ������
    sprintf(buf, "%sDAT = [", pline_head);
    pcb(buf);
    for (i = 0; i < len - user_data_pos - 3; i++)
    {
        sprintf(buf, "%02X ", pin[i + user_data_pos]);
        pcb(buf);
        if (((i + 1) % 16) == 0)
        {
            sprintf(buf, "%s%s       ", pline_end, pline_head);
            pcb(buf);
        }
    }
    sprintf(buf, "%02X]%s%s      AFN=[%02X] %s%s", pin[i + user_data_pos],
            pline_end, pline_head, pin[user_data_pos],
            get_AFN_name(pin[user_data_pos]), pline_end);
    pcb(buf);

    sprintf(buf, "%s      FN =[%02X %02X]: %d%s", pline_head,
            pin[user_data_pos + 1], pin[user_data_pos + 2],
            get_fn(pin[user_data_pos + 1], pin[user_data_pos + 2]), pline_end);
    pcb(buf);

    //CS
    sprintf(buf, "%s CS = [%02X]%s", pline_head, pin[len - 2], pline_end);
    pcb(buf);
    pcb(pline_head);
    pcb("-------------------------------------------------");
    pcb(pline_end);
}

/**
 ******************************************************************************
 * @brief   GDW1376_2���Ľ���
 * @param[in]  *pin        : ���뱨��
 * @param[in]   len        : ���뱨�ĳ���
 * @param[in]  *pcb        : �ص�����
 * @param[in]  *pline_head : ÿ����ʼ����ַ���
 * @param[in]  *pline_end  : ÿ�н�������ַ���
 *
 * @retval  -1  : ��������
 * @retval   0  : �����ɹ�
 ******************************************************************************
 */
int
GDW1376_2_parse(const unsigned char *pin,
        unsigned int len,
        pcallback pcb,
        const char *pline_head,
        const char *pline_end)
{
    int ret;

    //1. �������
    if ((pin == NULL) || (pcb == NULL))
    {
        return -ERR_INPUT;
    }

    //2. ���ļ��
    ret = chkfrm_GDW1376_2(pin, len);
    if (ret)
    {
        return ret;
    }

    //3. ����Ĭ�Ͻ�������
    pline_head = (pline_head == NULL) ? "" : pline_head;
    pline_end = (pline_end == NULL) ? "\n" : pline_end;

    //4. ���ԭʼ����
    print_org(pin, len, pcb, pline_head, pline_end);

    //5. �ṹ����
    print_struct(pin, len, pcb, pline_head, pline_end);

    //6. �����û�������
    ret = print_AFN(BITS(pin[3], 7), pin + user_data_pos,
            len - user_data_pos - 2, pcb, pline_head, pline_end);

    pcb(pline_head);
    if (!ret)
        pcb("-------------------�����ɹ�----------------------");
    else
        pcb("-------------------����ʧ��----------------------");

    pcb(pline_end);

    return ret;
}

/**
 ******************************************************************************
 * @brief   GDW1376_2���Ľ���(�ַ���)
 * @param[in]  *phex       : ���뱨��
 * @param[in]  *pcb        : �ص�����
 * @param[in]  *pline_head : ÿ����ʼ����ַ���
 * @param[in]  *pline_end  : ÿ�н�������ַ���
 *
 * @retval  -1  : ��������
 * @retval   0  : �����ɹ�
 ******************************************************************************
 */
int
GDW1376_2_parse_str(const char *phex,
        pcallback pcb,
        const char *pline_head,
        const char *pline_end)
{
    unsigned char inbuf[2048];
    int inlen = txt_to_buf(phex, strlen(phex), inbuf, sizeof(inbuf));
    return GDW1376_2_parse(inbuf, inlen, pcb, pline_head, pline_end);
}

/**
 ******************************************************************************
 * @brief   ��ȡ������Ϣ
 * @param[in]  errid : ����ID,GDW1376_2_parse�ķ���ֵ
 *
 * @retval  ������Ϣ�ַ���
 ******************************************************************************
 */
const char *
GDW1376_2_error(int errid)
{
    const char * const perror[] =
    {
        "������ȷ",
        "�����������",
        "���뱨��ͷ��0x68",
        "���뱨�ĳ�����Ч",
        "���뱨��β��0x16",
        "����cs����",
        "��֧�ֵ�FN",
        "Ӧ������LEN����",
    };

    errid = (errid < 0) ? -errid : errid;

    if ((errid >= 0) && (errid < ARRAY_SIZE(perror)))
    {
        return perror[errid];
    }

    return "ERR:������Ч��ID";
}

/**
 ******************************************************************************
 * @brief   ��ȡ�汾�ַ���
 * @retval  �汾�ַ����׵�ַ
 ******************************************************************************
 */
const char *
GDW1376_2_ver_str(void)
{
    return VER_STR;
}

/**
 ******************************************************************************
 * @brief   ��ȡ�޸���־
 * @retval  �汾�ַ����׵�ַ
 ******************************************************************************
 */
const char *
GDW1376_2_changelog(void)
{
    return CHANGE_LOG;
}

static int pos = 0;
static char py_out[1024*8];
static void
py_print_cb(const char *pstr)
{
    strncpy(py_out + pos, pstr, sizeof(py_out) - pos - 1);
    pos += strlen(pstr);
}

/**
 ******************************************************************************
 * @brief   GDW1376_2���Ľ���(pyʹ��)
 * @param[in]  *phex       : ���뱨��
 * @param[out] *pout       : �������
 * @param[in]  len         : ������Ļ��泤��
 *
 * @retval  -1  : ��������
 * @retval   0  : �����ɹ�
 ******************************************************************************
 */
int
GDW1376_2_parse_foy_py(const char *phex,
        char *pout,
        int len)
{
    unsigned char inbuf[4096];
    int inlen = txt_to_buf(phex, strlen(phex), inbuf, sizeof(inbuf));
    memset(py_out, 0x00, sizeof(py_out));
    int ret = GDW1376_2_parse(inbuf, inlen, py_print_cb, "", "\n");
    strncpy(pout, py_out, len);
    if (ret)
    {
        int slen = strlen(pout);
        strncpy(pout + slen, GDW1376_2_error(ret), len - slen);
    }
    pos = 0;
    return ret;
}

/*------------------------------GDW1376_2.c----------------------------------*/
