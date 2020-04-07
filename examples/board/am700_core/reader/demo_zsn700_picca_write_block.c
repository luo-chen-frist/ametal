/*******************************************************************************
*                                 AMetal
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2018 Guangzhou ZHIYUAN Electronics Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
*******************************************************************************/

/**
 * \file
 * \brief zsn700_readerд�����ݣ�ͨ�������ӿ�ʵ��
 *
 * - �������裺
 *   1. ��ȷ���Ӳ����úô��ڡ�
 *   2. ��ȷ���Ӻ����ߡ�
 *   3. ��A�࿨�������߸�Ӧ����
 *
 * - ʵ������
 *   1. ������ԿA�Կ�Ƭָ���Ŀ������֤�������֤��ͨ�����ӡkey A authent failed��
 *   2. �����֤�ɹ����򽫻�����������д��ָ���Ŀ����ջ��������ٽ����е����ݶ�ȡ�����������д�������
 *      һ�£�����д���ݳɹ���
 *
 * \par Դ����
 * \snippet demo_zsn700_reader_picca_write_block.c src_zsn700_reader_picca_write_block
 *
 * \internal
 * \par Modification history
 * - 1.00 17-11-21  sdq, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_if_zsn700_reader_picca_write_block
 * \copydoc demo_zsn700_reader_picca_write_block.c
 */

/** [src_zsn700_reader_picca_write_block] */
#include "am_vdebug.h"
#include "am_delay.h"
#include "am_zsn700_reader.h"
#include "am_zsn700_reader_reg.h"
#include "am_hwconf_zsn700_reader.h"
 
/**
 * \brief A�࿨д������
 */
void demo_zsn700_reader_picca_write_block (void)
{
    uint8_t tag_type[2]  = { 0 };      /* ATQA */
    uint8_t uid[10]      = { 0 };      /* UID */
    uint8_t uid_real_len =   0;        /* ���յ���UID�ĳ��� */
    uint8_t sak[3]       = { 0 };      /* SAK */
    uint8_t keya[6]      = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff};  /* ��֤��ԿA */
    uint8_t buff[16]     = { 0 };         /* ���ڴ洢�����ݵĻ����� */
    uint8_t i;
    uint8_t blocknum = 10;            /* Ҫ��д�Ŀ� */
    am_zsn700_reader_handle_t handle = am_zsn700_reader_inst_init();
    while (1) {

        /* Ѱ����δ���ߣ�halt���Ŀ� */
        if (AM_ZSN700_READER_STATUS_SUCCESS == am_zsn700_reader_picca_active\
                                         (handle,
                                          AM_ZSN700_READER_PICCA_REQ_IDLE,
                                          tag_type,
                                          uid,
                                          &uid_real_len,
                                          sak)) {
            am_kprintf("actived\n");

            /* ��֤A��Կ */
            if (AM_ZSN700_READER_STATUS_SUCCESS == am_zsn700_reader_picca_authent\
                                             (handle,
                                              AM_ZSN700_READER_IC_KEY_TYPE_A,
                                              uid,
                                              keya,
                                              blocknum)) {
                /* д������ */
                for (i = 0; i < sizeof(buff); i++) {
                    buff[i] = i;
                }
                /* д������ */
                am_zsn700_reader_picca_write(handle, blocknum, buff);

                /* ��ջ����� */
                for (i = 0; i < sizeof(buff); i++) {
                    buff[i] = 0;
                }

                /* �������� */
                am_zsn700_reader_picca_read(handle, blocknum, buff);

                am_kprintf("block%d: ", blocknum);
                for (i = 0; i < 16; i++) {
                    am_kprintf("%x ", buff[i]);
                }
                am_kprintf("\n");

            } else {
                am_kprintf("key A authent failed\n\n");
            }
        }
        am_mdelay(200);
    }
}

/** [src_zsn700_reader_picca_write_block] */

/* end of file */