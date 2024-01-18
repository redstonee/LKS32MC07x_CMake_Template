/**
 * @file
 * @copyright (C)2015, LINKO SEMICONDUCTOR Co.ltd
 * @brief 文件名称： lks32mc07x_opa.h\n
 * 文件标识： 无 \n
 * 内容摘要： OPA驱动头文件 \n
 * 其它说明： 无 \n
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2023年02月22日 <td>1.0     <td>Olive Wang      <td>创建
 * </table>
 */
#ifndef __LKS32MC07x_OPA_H
#define __LKS32MC07x_OPA_H

/* Includes ------------------------------------------------------------------*/
#include "lks32mc07x_lib.h"

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

   typedef enum
   {
      OPA0 = 0, /**< OPA0模块*/
      OPA1 = 1, /**< OPA1模块*/
      OPA2 = 2, /**< OPA2模块*/
      OPA3 = 3  /**< OPA3模块*/
   } enumOPA;

   /**
    *@brief OPA初始化结构体句柄，初始化时请定义该句柄，并用其它地址来传参
    */
   typedef struct
   {
      /**
       * @brief 运放偏置电流调节 \n
       * @see PGA_IT_1   \n
       * @see PGA_IT_1P2  \n
       * @see PGA_IT_1P5    \n
       * @see PGA_IT_DISABLE
       */
      uint32_t OPA_IT;    /**< 运放偏置电流调节*/
                          /**
                           * @brief 运放闭环增益 \n
                           * @see PGA_GAIN_32   \n
                           * @see PGA_GAIN_16  \n
                           * @see PGA_GAIN_8    \n
                           * @see PGA_GAIN_4
                           */
      uint32_t OPA_Gain;  /**< 运放闭环增益*/
      uint32_t OPA_CLEna; /**< 运放闭环使能:Enable,Disable*/
   } OPA_InitTypeDef;

/* ------------------------------PGA操作相关定义 ------------------------------ */
#define PGA_GAIN_32 0x00 /**< 反馈电阻320k:10k */
#define PGA_GAIN_16 0x01 /**< 反馈电阻160k:10k */
#define PGA_GAIN_8 0x02  /**< 反馈电阻80k:10k */
#define PGA_GAIN_4 0x03  /**< 反馈电阻40k:10k */

#define PGA_IT_1 0x00       /**< opa偏置电流调节x1*/
#define PGA_IT_1P2 0x01     /**< opa偏置电流调节x1.2*/
#define PGA_IT_1P5 0x02     /**< opa偏置电流调节x1.5*/
#define PGA_IT_DISABLE 0x03 /**< opa偏置电流调节禁止*/

   void OPA_Init(enumOPA opa, OPA_InitTypeDef *OPA_InitStruct); /*opa初始化*/
   void OPA_StructInit(OPA_InitTypeDef *OPA_InitStruct);        /*opa结构体初始化*/
   void OPA_OUT(enumOPA opa, FuncState state);                  /*opa输出到IO配置*/

#ifdef __cplusplus
}
#endif // __cplusplus

#endif /*__lks32mc07x_OPA_H */

/************************ (C) COPYRIGHT LINKO SEMICONDUCTOR *****END OF FILE****/
