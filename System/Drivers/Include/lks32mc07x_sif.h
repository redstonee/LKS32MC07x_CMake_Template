/**
 * @file
 * @copyright (C)2015, LINKO SEMICONDUCTOR Co.ltd
 * @brief 文件名称： lks32mc07x_sif.h\n
 * 文件标识： 无 \n
 * 内容摘要： SIF驱动头文件 \n
 * 其它说明： 无 \n
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2023年2月12日 <td>1.1     <td>myx   <td>修改
 * </table>
 */
#ifndef _CONNIE_SIF_H_
#define _CONNIE_SIF_H_

#include "lks32mc07x_lib.h"

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

    typedef struct
    {
        uint8_t SIF_DONE;       /* 传输完成后默认电平 1：高电平 0：低电平 */
        uint8_t SIF_SYNC;       /* 同步信号默认电平 1：高电平 0：低电平 */
        uint8_t SIF_SYNC_PULSE; /* 同步信号是否有电平反转 1：有 0：无 */
        uint8_t SIF_DONE_VLD;   /* 有无结束信号 1：有 0：无 */
        uint8_t SIF_SYNC_VLD;   /* 有无同步信号 1：有 0：无 */
        uint8_t SIF_RATIO;      /* 数据占空比 1：3：1  0：2：1 */
        uint8_t SIF_MSB;        /* 数据传送顺序 1：高字节在前 0：低字节在前 */
        uint8_t SIF_EN;         /* SIF模块使能，高有效 */
        uint16_t SIF_TOSC;      /* 时基设置 SIF_TOSC+1 333NS为单位 最大 4096 * 333 = 1364US */
        uint16_t SIF_TSTH1;     /* 同步时长 （SIF_TSTH1 +1） * SIF_TOSC 最大1024 * SIF_TOSC * 32 */
        uint8_t SIF_TDTH1;      /* 结束信号时长 （SIF_TDTH1 + 1）MS */
        uint8_t SIF_IRQ_IF;     /* SIF中断标志位 1：有 0：无 */
        uint8_t SIF_DMA_EN;     /* DMA 传输使能  高有效 */
        uint8_t SIF_IRQ_EN;     /* SIF中断使能 高有效 */

    } SIF_InitTypeDef;

    typedef struct
    {
        __IO uint32_t SIFx_CFG;
        __IO uint32_t SIFx_TOSC;
        __IO uint32_t SIFx_TSTH1;
        __IO uint32_t SIFx_TDTH1;
        __IO uint32_t SIFx_IRQ;

    } SIF_RegTypeDef;

/*中断使能定义*/
#define SIF_IE_Enable BIT0  ///< SIF中断使能开关。默认值为0
#define SIF_DMA_Enable BIT1 ///< SIF DMA请求使能开关。默认值为0

#define SIF0 ((SIF_RegTypeDef *)(SIF0_BASE))

/*中断标志定义*/
#define SPI_IF_CLEAR BIT4 ///< SPI传输，完成事件。高电平有效，写1清除。

    void SIF_StructInit(SIF_InitTypeDef *SIFInitStruct);
    void SIF_Init(SIF_RegTypeDef *SIFx, SIF_InitTypeDef *SIFInitStruct);
    void SIF_Timebase_set(u32 tosc);
    void SIF_TH_set(u32 tsh, u32 tdh);
    void SIF_Senddata(u8 Data);
    void SIF_DMA_IsEnable(u8 state);
    void SIF_Irq_IsEnable(u8 state);
    void SIF_Clear_Irq(void);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif
