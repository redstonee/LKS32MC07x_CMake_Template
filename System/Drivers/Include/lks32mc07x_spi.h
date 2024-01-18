/*******************************************************************************
 * 版权所有 (C)2015, LINKO SEMICONDUCTOR Co.ltd
 *
 * 文件名称lks32mc07x8x_spi.h
 * 文件标识：
 * 内容摘要： SPI驱动头文件
 * 其它说明： 无
 * 当前版本： V 1.0
 * 作    者：
 * 完成日期：
 *
 * 修改记录1：
 * 修改日期：
 * 版 本 号：V 1.0
 * 修 改 人：
 * 修改内容：创建
 *
 * 修改记录2：
 * 修改日期：
 * 版 本 号：
 * 修 改 人：
 * 修改内容：
 *
 *******************************************************************************/

#ifndef __lks32mc07x_SPI_H
#define __lks32mc07x_SPI_H

/* Includes ------------------------------------------------------------------*/
#include "lks32mc07x.h"
#include "basic.h"

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

   typedef enum
   {
      SPI_Master = 0x01, /* Master Mode */
      SPI_Slave = 0x00   /* Slave Mode */
   } SPI_Mode;

   typedef enum
   {
      SPI_Full = 0x0,    /* 开启全双工模式 */
      SPI_Half_Tx = 0x2, /* 开启半双工模式 仅发送 */
      SPI_Half_Rx = 0x3  /* 开启半双工模式 仅接受 */
   } SPI_Duplex;

   /**
    *@brief SPI寄存器结构体句柄
    */
   typedef struct
   {
      __IO uint32_t CFG;     /**< SPI控制寄存器 */
      __IO uint32_t IE;      /**< SPI中断寄存器 */
      __IO uint32_t BAUD;    /**< SPI波特率控制寄存器 */
      __IO uint32_t TX_DATA; /**< SPI发送数据寄存器 */
      __IO uint32_t RX_DATA; /**< SPI接收数据寄存器 */
      __IO uint32_t SIZE;    /**< SPI传输数据长度寄存器 */
   } SPI_TypeDef;

#define SPI0 ((SPI_TypeDef *)SPI0_BASE)

   typedef struct
   {
      SPI_Duplex Duplex; /**< 数据传输模式选择，全双工0x00, 半双工仅发送0x10, 半双工仅接收0x11 模式选择  */
      uint8_t CS;        /**< 从设备下片选信号来源：0，恒为0；1，来源于主设备 */
      SPI_Mode Mode;     /**< 主从模式选择：0，从模式；1，主模式 */
      uint8_t CPHA;      /**< 相位选择：0对应时钟从默认电平到第一个跳变边沿为采样数据时刻；1对应发送数据时刻 */
      uint8_t CPOL;      /**< 极性选择：0对应默认时钟电平为低电平；1对应默认时钟为高电平 */
      uint8_t ENDIAN;    /**< 传输顺序选择：0对应MSB高位先传输；1对应LSB低位先传输 */
      uint8_t EN;        /**< 模块使能：1 开启模块 */

      uint8_t IRQEna; /**< 中断使能 */
      uint8_t Trig;   /**< 传输触发方式选择 1：外部触发；0内部自动执行（仅主模式有效） */

      uint8_t TRANS_MODE; /**< 数据搬移方式选择 0：DMA搬运；1MCU搬运 */
      uint16_t BaudRate;  /**< 波特率设置 取值范围3-4095 */

      uint8_t ByteLength; /**< 数据长度 */
   } SPI_InitTypeDef;

#define SPI_FIRSTSEND_LSB 1 /**< 低位先传 */
#define SPI_FIRSTSEND_MSB 0 /**< 高位先传 */

#define SPI_DMA_ENABLE 0  /**< 使能DMA搬运 */
#define SPI_DMA_DISABLE 1 /**< 禁止DMA搬运 */

/*中断使能定义*/
#define SPI_IRQEna_Enable BIT7   /**<中断使能定义，SPI中断使能 */
#define SPI_IRQEna_TranDone BIT6 /**<中断使能定义，传输完成中断 */
#define SPI_IRQEna_SSErr BIT5    /**<中断使能定义，传输异常事件中断 */
#define SPI_IRQEna_DataOver BIT4 /**<中断使能定义，传输溢出事件中断 */

/*中断标志定义*/
#define SPI_IF_TranDone BIT2 /**<中断标志定义，传输完成中断标志位 */
#define SPI_IF_SSErr BIT1    /**<中断标志定义，传输异常中断标志位 */
#define SPI_IF_DataOver BIT0 /**<中断标志定义，传输溢出中断标志位 */

   void SPI_Init(SPI_TypeDef *SPIx, SPI_InitTypeDef *SPI_InitStruct);
   void SPI_StructInit(SPI_InitTypeDef *SPI_InitStruct);

   void SPI_SendData(SPI_TypeDef *SPIx, uint8_t n);
   uint8_t SPI_ReadData(SPI_TypeDef *SPIx);

   uint8_t SPI_GetIRQFlag(SPI_TypeDef *SPIx, u8 IRQ_Flag);
   void SPI_ClearIRQFlag(SPI_TypeDef *SPIx, u8 IRQ_Flag);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif /*__lks32mc07x_SPI_H */

/************************ (C) COPYRIGHT LINKO SEMICONDUCTOR *****END OF FILE****/
