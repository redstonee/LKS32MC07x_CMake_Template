/**
 * @file
 * @copyright (C)2021, LINKO SEMICONDUCTOR Co.ltd
 * @brief 文件名称： lks32mc07x_uart.h\n
 * 文件标识： 无 \n
 * 内容摘要： UART驱动头文件 \n
 * 其它说明： 无 \n
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2023年2月23日   <td>1.0     <td>cakezhang      <td>创建
 * </table>
 */
#ifndef __lks32mc07x_UART_H
#define __lks32mc07x_UART_H

/* Includes ------------------------------------------------------------------*/
#include "lks32mc07x.h"
#include "basic.h"

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

   /** 串口奇偶校验配置枚举成员*/
   typedef enum
   {
      UART_Parity_NO = 0x00,
      UART_Parity_EVEN = 0x01,
      UART_Parity_ODD = 0x02
   } UART_ParityMode;

   /**
    *@brief UART寄存器结构体句柄
    */
   typedef struct
   {
      __IO uint32_t CTRL; /**<UART控制寄存器*/
      __IO uint32_t DIVH; /**<UART波特率设置高字节寄存器*/
      __IO uint32_t DIVL; /**<UART波特率设置低字节寄存器*/
      __IO uint32_t BUFF; /**<UART收发缓冲寄存器*/
      __IO uint32_t ADR;  /**<485通信地址匹配寄存器*/
      __IO uint32_t STT;  /**<UART状态寄存器*/
      __IO uint32_t RE;   /**<UART DMA 请求使能寄存器*/
      __IO uint32_t IE;   /**<UART中断使能寄存器*/
      __IO uint32_t IF;   /**<UART中断标志寄存器*/
      __IO uint32_t IOC;  /**<UART IO翻转使能*/
   } UART_TypeDef;

/**
 * 串口0结构体基地址定义
 */
#define UART0 ((UART_TypeDef *)UART0_BASE)

/**
 * 串口1结构体基地址定义
 */
#define UART1 ((UART_TypeDef *)UART1_BASE)

   typedef struct
   {
      uint32_t BaudRate; /**<波特率*/
      /**@brief数据长度
       * @see UART_WORDLENGTH_8b
       * @see UART_WORDLENGTH_9b
       */
      uint8_t WordLength;
      /**@brief停止位长度
       * @see UART_STOPBITS_1b
       * @see UART_STOPBITS_2b
       */
      uint8_t StopBits;
      /**@brief发送数据大小端设置
       * @see UART_FIRSTSEND_LSB
       * @see UART_FIRSTSEND_MSB
       */
      uint8_t FirstSend;
      /**@brief奇偶校验
       * @see UART_ParityMode
       */
      UART_ParityMode ParityMode;

      uint8_t MultiDropEna; /**<使能Multi-drop,0:Disable 1:Enable*/
      uint8_t Bit9Value;    /**<Multi-drop Master模式时,第9个数据位值*/
      uint8_t IOFlipEna;    /**<使能IO翻转,0:Disable 1:Enable*/

      uint16_t Match485Addr; /**<用作485通信时的匹配地址*/
      uint8_t IRQEna;        /**<中断使能寄存器*/
      uint8_t DMARE;         /**<DMA 请求使能*/
      uint8_t RXD_INV;       /**< 接收电平取反 */
      uint8_t TXD_INV;       /**< 发送电平取反 */
   } UART_InitTypeDef;

#define UART_WORDLENGTH_8b 0 /**<8bit数据位*/
#define UART_WORDLENGTH_9b 1 /**<9bit数据位*/

#define UART_STOPBITS_1b 0 /**<无停止位*/
#define UART_STOPBITS_2b 1 /**<1bit停止位*/

#define UART_FIRSTSEND_LSB 0 /**<低端先发送*/
#define UART_FIRSTSEND_MSB 1 /**<高端先发送*/

/*中断使能定义*/
#define UART_IRQEna_SendOver BIT0      /**<使能发送完成中断*/
#define UART_IRQEna_RcvOver BIT1       /**<使能接收完成中断*/
#define UART_IRQEna_SendBuffEmpty BIT2 /**<使能发送缓冲区空中断*/
#define UART_IRQEna_StopError BIT3     /**<使能停止位错误*/
#define UART_IRQEna_CheckError BIT4    /**<使能校验错误*/
#define UART_IRQEna_TX_OV BIT5         /**<发送缓冲区溢出中断使能*/
#define UART_IRQEna_RX_OV BIT6         /**<接收缓冲区溢出中断使能*/
#define UART_IRQEna_LBD BIT7           /**<LIN break character 检测中断使能*/
#define UART_IRQEna_IDLE BIT8          /**<空闲帧中断使能*/

#define TX_DMA_RE BIT0     /*发送完成DMA请求使能*/
#define RX_DMA_RE BIT1     /*接收完成DMA请求使能*/
#define TX_BUF_DMA_RE BIT2 /*发送缓冲区空DMA请求使能*/

/*中断标志定义*/
#define UART_IF_SendOver BIT0     /**<发送完成中断标志*/
#define UART_IF_RcvOver BIT1      /**<接收完成中断标志*/
#define UART_IF_SendBufEmpty BIT2 /**<发送缓冲区空中断标志*/
#define UART_IF_StopError BIT3    /**<停止位错误中断标志*/
#define UART_IF_CheckError BIT4   /**<校验错误中断标志 */
#define UART_IF_TX_OV BIT5        /**<发送缓冲区溢出中断标志*/
#define UART_IF_RX_OV BIT6        /**<接收缓冲区溢出中断标志*/
#define UART_IF_LBD BIT7          /**<LIN break character 检测中断标志*/
#define UART_IF_IDLE BIT8         /**<空闲帧中断标志*/

   void UART_Init(UART_TypeDef *UARTx, UART_InitTypeDef *UART_InitStruct);
   void UART_StructInit(UART_InitTypeDef *UART_InitStruct);

   void UART_SendData(UART_TypeDef *UARTx, uint32_t n);
   uint32_t UART_ReadData(UART_TypeDef *UARTx);

   void UART_SendnData(UART_TypeDef *UARTx, char *sendData, uint32_t len);
   void UART_RecvnData(UART_TypeDef *UARTx, char *recvData, uint32_t maxlen);

   void UART_ClearIRQFlag(UART_TypeDef *UARTx, uint32_t tempFlag);

   uint32_t UART_GetIRQFlag(UART_TypeDef *UARTx, uint32_t tempFlag);

   uint8_t UART_SendAddr_485(UART_TypeDef *UARTx, uint8_t n);
   uint8_t UART_SendData_485(UART_TypeDef *UARTx, uint8_t n);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif /*__lks32mc07x_UART_H */

/************************ (C) COPYRIGHT LINKO SEMICONDUCTOR *****END OF FILE****/
