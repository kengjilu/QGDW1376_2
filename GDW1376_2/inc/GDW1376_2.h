/**
 ******************************************************************************
 * @file       GDW1376_2.h
 * @brief      API include file of GDW1376_2.h.
 * @details    This file including all API functions's declare of GDW1376_2.h.
 * @copyright
 ******************************************************************************
 */
#ifndef GDW1376_2_H_
#define GDW1376_2_H_ 

#ifdef __cplusplus
extern "C"
{
#endif

/*-----------------------------------------------------------------------------
 Section: Includes
 ----------------------------------------------------------------------------*/
/* NONE */

/*-----------------------------------------------------------------------------
 Section: Macro Definitions
 ----------------------------------------------------------------------------*/
#define ERR_NONE            (0)     /**< �޴��� */
#define ERR_INPUT           (1)     /**< ����������� */
#define ERR_CHKFRM_0x68     (2)     /**< ����ͷ0x68 */
#define ERR_CHKFRM_LEN      (3)     /**< ���뱨�ĳ�����Ч */
#define ERR_CHKFRM_0x16     (4)     /**< ����β0x16 */
#define ERR_CHKFRM_cs       (5)     /**< ����cs���� */
#define ERR_AFN_FN          (6)     /**< ��֧�ֵ�FN*/
#define ERR_APP_LEN         (7)     /**< Ӧ������LEN���� */

/*-----------------------------------------------------------------------------
 Section: Type Definitions
 ----------------------------------------------------------------------------*/
typedef void (*pcallback)(const char*);

/*-----------------------------------------------------------------------------
 Section: Globals
 ----------------------------------------------------------------------------*/
/* NONE */

/*-----------------------------------------------------------------------------
 Section: Function Prototypes
 ----------------------------------------------------------------------------*/
extern int
GDW1376_2_parse(const unsigned char *pin,
        unsigned int len,
        pcallback pcb,
        const char *pline_head,
        const char *pline_end);

extern int
GDW1376_2_parse_str(const char *phex,
        pcallback pcb,
        const char *pline_head,
        const char *pline_end);

extern const char *
GDW1376_2_error(int errid);

extern const char *
GDW1376_2_ver_str(void);

extern const char *
GDW1376_2_changelog(void);

#ifdef __cplusplus
}
#endif

#endif /* GDW1376_2_H_ */
/*--------------------------End of GDW1376_2.h-----------------------------*/
