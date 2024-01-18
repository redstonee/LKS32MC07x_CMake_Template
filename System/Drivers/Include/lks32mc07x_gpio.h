/**
 * @file
 * @copyright (C)2015, LINKO SEMICONDUCTOR Co.ltd
 * @brief 文件名称： lks32mc07x_gpio.h\n
 * 文件标识： 无 \n
 * 内容摘要： GPIO外设驱动程序头文件 \n
 * 其它说明： 无 \n
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2023年2月21日     <td>1.0     <td>cakezhang      <td>创建
 * </table>
 */
#ifndef __lks32mc07x_GPIO_H
#define __lks32mc07x_GPIO_H

///< Includes ------------------------------------------------------------------*/
#include "lks32mc07x.h"

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

   /**
    *@brief GPIO寄存器结构体句柄
    */
   typedef struct
   {
      __IO uint32_t PIE;   /*!< 0x00 GPIO x 输入使能*/
      __IO uint32_t POE;   /*!< 0x04 GPIO x 输出使能*/
      __IO uint32_t PDI;   /*!< 0x08 GPIO x 输入数据*/
      __IO uint32_t PDO;   /*!< 0x0C GPIO x 输出数据*/
      __IO uint32_t PUE;   /*!< 0x10 GPIO x 上拉使能*/
      __IO uint32_t null;  /*!< 0x14 结构体地址对齐，无意义*/
      __IO uint32_t PODE;  /*!< 0x18 GPIO x 开漏使能*/
      __IO uint32_t PFLT;  /*!< 0x1c GPIO x 滤波使能*/
      __IO uint32_t F3210; /*!< 0x20 GPIO x [3:0]功能选择*/
      __IO uint32_t F7654; /*!< 0x24 GPIO x [7:4]功能选择*/
      __IO uint32_t FBA98; /*!< 0x28 GPIO x [11:8]功能选择*/
      __IO uint32_t FFEDC; /*!< 0x2C GPIO x [15:12]功能选择*/
      __IO uint32_t BSRR;  /*!< 0x30 GPIO x 位操作寄存器*/
      __IO uint32_t BRR;   /*!< 0x34 GPIO x 位清零寄存器*/
   } GPIO_TypeDef;

/**
 * GPIO0结构体基地址定义
 */
#define GPIO0 ((GPIO_TypeDef *)GPIO0_BASE)

/**
 * GPIO1结构体基地址定义
 */
#define GPIO1 ((GPIO_TypeDef *)GPIO1_BASE)

/**
 * GPIO2结构体基地址定义
 */
#define GPIO2 ((GPIO_TypeDef *)GPIO2_BASE)

/**
 * GPIO3结构体基地址定义
 */
#define GPIO3 ((GPIO_TypeDef *)GPIO3_BASE)

   /**
    *@brief GPIO模式选择枚举
    */
   typedef enum
   {
      GPIO_Mode_IN = 0x00,  /*!< GPIO 输入&高阻，模拟和数字同时生效*/
      GPIO_Mode_OUT = 0x01, /*!< GPIO 输出*/
      GPIO_Mode_ANA = 0x02, /*!< GPIO 高阻*/
      GPIO_Mode_IO = 0x03
   } GPIOMode_TypeDef;

   /**
    *@brief GPIO输出模式选择枚举
    */
   typedef enum
   {
      GPIO_PuPd_NOPULL = 0x00, /*!< 高阻态 */
      GPIO_PuPd_UP = 0x01,     /*!< 上拉 */
   } GPIOPuPd_TypeDef;

   /**
    *@brief GPIO寄存器写入量枚举
    */
   typedef enum
   {
      Bit_RESET = 0,
      Bit_SET
   } BitAction;

   /**
    *@brief  GPIO功能配置结构体句柄
    */
   typedef struct
   {
      u32 GPIO_Pin;    ///< 要配置的引脚
      u32 GPIO_Mode;   ///< GPIO模式
      u32 GPIO_PuPd;   ///< 上拉使能
      u32 GPIO_PODEna; ///< 开漏使能
      u32 GPIO_PFLT;
   } GPIO_InitTypeDef;

#define AF0_GPIO 0    /*!< GPIO复用功能0，模拟功能 */
#define AF1_SYSAF 1   /*!< GPIO复用功能1，SYS_AF、CMP、CLOCK等数字信号输出功能 */
#define AF2_HALL 2    /*!< GPIO复用功能2，HALL功能 */
#define AF3_MCPWM 3   /*!< GPIO复用功能3，MCPWM功能 */
#define AF4_UART 4    /*!< GPIO复用功能4，UART功能 */
#define AF5_SPI 5     /*!< GPIO复用功能5，SPI功能 */
#define AF6_I2C 6     /*!< GPIO复用功能6，I2C功能 */
#define AF7_TIMER01 7 /*!< GPIO复用功能7，Timer0、Timer1功能 */
#define AF8_TIMER23 8 /*!< GPIO复用功能8，Timer2、Timer3、QEP0、QEP1功能 */
#define AF9_DEBUG 9   /*!< GPIO复用功能9，ADC trigger debug功能 */
#define AF10_CAN 10   /*!< GPIO复用功能10，CAN功能 */
#define AF11_SIF 11   /*!< GPIO复用功能11，SIF功能 */
#define AF12_CL 12    /*!< GPIO复用功能12，CL功能 */

/*GPIO_Pad define*/
#define GPIO_Pin_NONE 0               /*!<GPIO pin脚定义，无pin脚  */
#define GPIO_Pin_0 BIT0               /*!<GPIO pin脚定义，pin_0脚  */
#define GPIO_Pin_1 BIT1               /*!<GPIO pin脚定义，pin_1脚  */
#define GPIO_Pin_2 BIT2               /*!<GPIO pin脚定义，pin_2脚  */
#define GPIO_Pin_3 BIT3               /*!<GPIO pin脚定义，pin_3脚  */
#define GPIO_Pin_4 BIT4               /*!<GPIO pin脚定义，pin_4脚  */
#define GPIO_Pin_5 BIT5               /*!<GPIO pin脚定义，pin_5脚  */
#define GPIO_Pin_6 BIT6               /*!<GPIO pin脚定义，pin_6脚  */
#define GPIO_Pin_7 BIT7               /*!<GPIO pin脚定义，pin_7脚  */
#define GPIO_Pin_8 BIT8               /*!<GPIO pin脚定义，pin_8脚  */
#define GPIO_Pin_9 BIT9               /*!<GPIO pin脚定义，pin_9脚  */
#define GPIO_Pin_10 BIT10             /*!<GPIO pin脚定义，pin_10脚 */
#define GPIO_Pin_11 BIT11             /*!<GPIO pin脚定义，pin_11脚 */
#define GPIO_Pin_12 BIT12             /*!<GPIO pin脚定义，pin_12脚 */
#define GPIO_Pin_13 BIT13             /*!<GPIO pin脚定义，pin_13脚 */
#define GPIO_Pin_14 BIT14             /*!<GPIO pin脚定义，pin_14脚 */
#define GPIO_Pin_15 BIT15             /*!<GPIO pin脚定义，pin_15脚 */
#define GPIO_Pin_ALL (uint32_t)0xFFFF /*!<GPIO pin脚定义，所有pin脚*/

/*GPIO_Pad_sources define*/
#define GPIO_PinSource_0 0   /*!<GPIO pin脚定义，pin_0脚 */
#define GPIO_PinSource_1 1   /*!<GPIO pin脚定义，pin_1脚 */
#define GPIO_PinSource_2 2   /*!<GPIO pin脚定义，pin_2脚 */
#define GPIO_PinSource_3 3   /*!<GPIO pin脚定义，pin_3脚 */
#define GPIO_PinSource_4 4   /*!<GPIO pin脚定义，pin_4脚 */
#define GPIO_PinSource_5 5   /*!<GPIO pin脚定义，pin_5脚 */
#define GPIO_PinSource_6 6   /*!<GPIO pin脚定义，pin_6脚 */
#define GPIO_PinSource_7 7   /*!<GPIO pin脚定义，pin_7脚 */
#define GPIO_PinSource_8 8   /*!<GPIO pin脚定义，pin_8脚 */
#define GPIO_PinSource_9 9   /*!<GPIO pin脚定义，pin_9脚 */
#define GPIO_PinSource_10 10 /*!<GPIO pin脚定义，pin_10脚 */
#define GPIO_PinSource_11 11 /*!<GPIO pin脚定义，pin_11脚 */
#define GPIO_PinSource_12 12 /*!<GPIO pin脚定义，pin_12脚 */
#define GPIO_PinSource_13 13 /*!<GPIO pin脚定义，pin_13脚 */
#define GPIO_PinSource_14 14 /*!<GPIO pin脚定义，pin_14脚 */
#define GPIO_PinSource_15 15 /*!<GPIO pin脚定义，pin_15脚 */

   /* 初始化、配置函数 *********************************/
   void GPIO_Init(GPIO_TypeDef *GPIOx, GPIO_InitTypeDef *GPIO_InitStruct);
   void GPIO_StructInit(GPIO_InitTypeDef *GPIO_InitStruct);

   void GPIO_LockRegister(GPIO_TypeDef *GPIOx);
   void GPIO_UnlockRegister(GPIO_TypeDef *GPIOx);

   /* GPIO读写函数 *************************************/
   uint8_t GPIO_ReadInputDataBit(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
   uint32_t GPIO_ReadInputData(GPIO_TypeDef *GPIOx);
   uint8_t GPIO_ReadOutputDataBit(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
   uint32_t GPIO_ReadOutputData(GPIO_TypeDef *GPIOx);

   void GPIO_SetBits(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
   void GPIO_ResetBits(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
   void GPIO_Write(GPIO_TypeDef *GPIOx, uint32_t Val);
   void GPIO_WriteBit(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, BitAction BitVal);

   /* GPIO功能选择函数 ***************************/
   void GPIO_PinAFConfig(GPIO_TypeDef *GPIOx, uint32_t GPIO_PinSource, uint32_t GPIO_AF);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif /*__lks32mc07x_GPIO_H */

/************************ (C) COPYRIGHT LINKO SEMICONDUCTOR *****END OF FILE****/
