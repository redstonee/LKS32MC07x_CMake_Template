/**
 * @file
 * @copyright (C)2015, LINKO SEMICONDUCTOR Co.ltd
 * @brief 文件名称： lks32mc07x_exti.h\n
 * 文件标识： 无 \n
 * 内容摘要： EXTI外部中断驱动头文件 \n
 * 其它说明： 无 \n
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2023年2月28日 <td>1.0       <td>cakezhang        <td>创建
 * </table>
 */
#ifndef __lks32mc07x_EXTI_H
#define __lks32mc07x_EXTI_H

/* Includes
 * ------------------------------------------------------------------*/
#include "basic.h"
#include "lks32mc07x.h"
#include "lks32mc07x_gpio.h"

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

  /**
   *@brief EXTI寄存器结构体句柄
   */
  typedef struct
  {
    __IO uint32_t CR0;
    __IO uint32_t CR1;
    __IO uint32_t IE;
    __IO uint32_t IF;
  } EXTI_TypeDef;

  /**
   * EXTI结构体基地址定义
   */
#ifndef EXTI
#define EXTI ((EXTI_TypeDef *)EXTI_BASE)
#endif

  /**
   * EXTI触发信号定义
   */
  typedef enum
  {
    EXTI_Trigger_None = 0x00,    /**< 不触发*/
    EXTI_Trigger_Negedge = 0x01, /**< 下降沿触发*/
    EXTI_Trigger_Posedge = 0x02, /**< 上升沿触发*/
    EXTI_Trigger_Edge = 0x03     /**< 上升沿、下降沿均触发*/
  } EXTIMode_TypeDef;

  uint32_t EXTI_ReadIFFlag (EXTI_TypeDef *EXTIx);
  void EXTI_ResetIF (EXTI_TypeDef *EXTIx, uint32_t temp);

  void EXTI_Trigger_Config (GPIO_TypeDef *GPIOx, uint32_t GPIO_PinSource,
                            uint16_t EXTI_Trigger);
  void EXTI_ClearIRQFlag (GPIO_TypeDef *GPIOx, uint32_t GPIO_PinSource);
  u8 EXTI_GetIRQFlag (GPIO_TypeDef *GPIOx, uint32_t GPIO_PinSource);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif /*__lks32mc07x_EXTI_H */

/************************ (C) COPYRIGHT LINKO SEMICONDUCTOR *****END OF
 * FILE****/
