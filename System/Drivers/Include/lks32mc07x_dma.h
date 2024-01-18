 /**
 * @file 
 * @copyright (C)2015, LINKO SEMICONDUCTOR Co.ltd
 * @brief 文件名称： lks32mc07x_dma.h\n
 * 文件标识： 无 \n
 * 内容摘要： DMA外设驱动程序头文件 \n
 * 其它说明： 无 \n
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2023年2月11日 <td>1.1     <td>ywx   <td>修改
 * </table>
 */
 
#ifndef __lks32mc07x_dma_H
#define __lks32mc07x_dma_H

#include "lks32mc07x_lib.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus


/** 
 *@brief DMA通道相关寄存器对象定义
 */
typedef struct
{
    __IO uint32_t CCR;  /**< DMA 通道配置寄存器*/
    __IO uint32_t REN;/**< DMA 请求使能寄存器*/
    __IO uint32_t CTMS;/**< DMA传输次数设置寄存器*/
    __IO uint32_t SADR;/**< DMA 源地址设置寄存器*/
    __IO uint32_t DADR;/**< DMA 目的地址设置*/
} DMA_RegTypeDef;

/** 
 *@brief DMA控制状态寄存器对象定义
 */
typedef struct
{
    __IO u32 CTRL;/**< DMA 控制寄存器*/
    __IO u32 IE;/**< DMA 中断使能寄存器*/
    __IO u32 IF;/**< DMA 中断标志寄存器*/
} DMA_MODULERegTypeDef;

/**
 * DAM通道0 1 2 3结构体基地址定义
 */
#define DMA_CHN0 ((DMA_RegTypeDef *) 0x40011200)
#define DMA_CHN1 ((DMA_RegTypeDef *) (DMA0_BASE + 0x20))
#define DMA_CHN2 ((DMA_RegTypeDef *) (DMA0_BASE + 0x40))
#define DMA_CHN3 ((DMA_RegTypeDef *) (DMA0_BASE + 0x60))
#define DMA_TOP ((DMA_MODULERegTypeDef *)(DMA0_BASE + 0x80))


/**
 * DAM搬运使能源定义
 */
typedef union
{
    u32 R;
    struct
    {
        u16 ADC0_EN         :1 ;    // BIT0
        u16 ADC1_EN         :1 ;    // BIT1
        u16                 :1 ;    // BIT2
        u16 DSP_EN          :1 ;    // BIT3
        u16 TIMER0_EN       :1 ;    // BIT4
        u16 TIMER1_EN       :1 ;    // BIT5
        u16 TIMER2_EN       :1 ;    // BIT6
        u16 TIMER3_EN       :1 ;    // BIT7
        u16                 :1 ;    // BIT8
        u16                 :1 ;    // BIT9
        u16 SPI_RX_EN       :1 ;    // BIT10
        u16 SPI_TX_EN       :1 ;    // BIT11
        u16 MCPWM_RE0_EN    :1 ;    // BIT12
        u16 MCPWM_RE1_EN    :1 ;    // BIT13
        u16 I2C0_RX_EN      :1 ;    // BIT14
        u16 I2C0_TX_EN      :1 ;    // BIT15
        u16 UART0_RX_EN     :1 ;    // BIT16
        u16 UART0_TX_EN     :1 ;    // BIT17
        u16 UART1_RX_EN     :1 ;    // BIT18
        u16 UART1_TX_EN     :1 ;    // BIT19
        u16                 :1 ;    // BIT20
        u16                 :1 ;    // BIT21
        u16                 :1 ;    // BIT22
        u16                 :1 ;    // BIT23
        u16 HALL0_EN        :1 ;    // BIT24
        u16 SIF_EN          :1 ;    // BIT25
        u16 CMP_EN          :1 ;    // BIT26
        u16                 :1 ;    // BIT27
        u16                 :1 ;    // BIT28
        u16 GPIO_EN         :1 ;    // BIT29
        u16                 :1 ;    // BIT30
        u16 SW_TRIG_EN      :1 ;    // BIT31
    } B               ;   
} stru_DMA_REN;

/** 
 *@brief DMA初始化结构体句柄，初始化时请定义该句柄，并用其它地址来传参
 */
typedef struct
{
    u8  IRQ_EN          ;
    u8  SBTW            ;   // 源地址访问位宽 0: Byte 1: Halfword 2: Word
    u8  DBTW            ;   // 目的地址访问位宽  0: Byte  1: Halfword  2: Word
    u8  SINC            ;   // 源地址递增使能
    u8  DINC            ;   // 目的地址地政使能
    u8  CIRC            ;   // 循环模式使能
    u8  RMODE           ;   // 多轮传输使能，多个DMA 请求完成传输
    u8  EN              ;   // 通道使能
    u8  TMS             ;   // DMA 通道 x 数据搬运次数。
    u32 SADR            ;   // DMA 通道 x 源地址
    u32 DADR            ;   // DMA 通道 x 目的地址
    stru_DMA_REN REN    ;   // DMA 请求使能
} DMA_InitTypeDef;


#define DMA_TCIE                 BIT0       /* 传输完成中断使能，高有效 */   
#define DMA_TEIE                 BIT1       /* 错误中断使能，高有效 */

#define PERI2MEMORY              0          /* 外设至内存 */
#define MEMORY2PERI              1          /* 内存至外设 */

#define DMA_BYTE_TRANS           0          /* 访问位宽， 0:byte */
#define DMA_HALFWORD_TRANS       1          /* 访问位宽， 1:half-word */
#define DMA_WORD_TRANS           2          /* 访问位宽， 2:word */ 

/** 
 *@brief DMA搬运触发源位宏定义
 */
#define DMA_REQ_SW BIT31        /*  SW        触发*/
#define DMA_REQ_GPIO BIT29      /*  GPIO      触发*/  
#define DMA_REQ_CMP BIT26       /*  CMP       触发*/
#define DMA_REQ_SIF BIT25       /*  HALL1     触发*/
#define DMA_REQ_HALL BIT24      /*  HALL0     触发*/  
#define DMA_REQ_UART1_TX BIT1   /*  UART1_TX  触发*/
#define DMA_REQ_UART1_RX BIT1   /*  UART1_RX  触发*/
#define DMA_REQ_UART0_TX BIT1   /*  UART0_TX  触发*/
#define DMA_REQ_UART0_RX BIT1   /*  UART0_RX  触发*/
#define DMA_REQ_I2C0_TX BIT15   /*  I2C0_TX   触发*/
#define DMA_REQ_I2C0_RX BIT14   /*  I2C0_RX   触发*/
#define DMA_REQ_MCPWM1 BIT13    /*  MCPWM1    触发*/
#define DMA_REQ_MCPWM0 BIT12    /*  MCPWM0    触发*/
#define DMA_REQ_SPI_TX BIT11    /*  SPI1_TX   触发*/
#define DMA_REQ_SPI_RX BIT10    /*  SPI1_RX   触发*/
#define DMA_REQ_TIMER4 BIT7     /*  TIMER4    触发*/
#define DMA_REQ_TIMER3 BIT6     /*  TIMER3    触发*/
#define DMA_REQ_TIMER2 BIT5     /*  TIMER2    触发*/
#define DMA_REQ_TIMER1 BIT4     /*  TIMER1    触发*/
#define DMA_REQ_TIMER0 BIT3     /*  TIMER0    触发*/
#define DMA_REQ_DSP BIT2        /*  ADC2      触发*/
#define DMA_REQ_ADC1 BIT1       /*  ADC1      触发*/
#define DMA_REQ_ADC0 BIT0       /*  ADC0      触发*/

/** 
 *@brief DMA中断标志位MASK
 */
#define DMA_IF_CH0 BIT0
#define DMA_IF_CH1 BIT1
#define DMA_IF_CH2 BIT2
#define DMA_IF_CH3 BIT3

/** 
 *@brief DMA中断使能位MASK
 */
#define DMA_IE_CH0 BIT0
#define DMA_IE_CH1 BIT1
#define DMA_IE_CH2 BIT2
#define DMA_IE_CH3 BIT3


void DMA_Init(DMA_RegTypeDef *DMAx, DMA_InitTypeDef *DMAInitStruct);
void DMA_StructInit(DMA_InitTypeDef *DMAInitStruct);
u32 DMA_GetIRQFlag(u32 DMA_IF_x);
void DMA_ClearIRQFlag(u32 DMA_IF_x);
u32 DMA_GetFlag(u32 DMA_IF_x);


void DMA_Enable(void);
void DMA_Disable(void);
void DMA_SetAddr(DMA_RegTypeDef *DMA_CHx, u32 addr1, u32 addr2);
void DMA_SetLength(DMA_RegTypeDef *DMA_CHx, u32 len);
void DMA_Trigger(DMA_RegTypeDef *DMA_CHx);
void DMA_SetRequest(DMA_RegTypeDef *DMA_CHx, u32 DMA_REQ_x);
void DMA_CHx_EN(DMA_RegTypeDef *DMAx,u32 Channel_EN);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif /*__lks32mc08x_dma_H */



/************************ (C) COPYRIGHT LINKO SEMICONDUCTOR *****END OF FILE****/

