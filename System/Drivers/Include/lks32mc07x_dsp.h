 /**
 * @file 
 * @copyright (C)2015, LINKO SEMICONDUCTOR Co.ltd
 * @brief 文件名称： lks32mc07x_dsp.h\n
 * 文件标识： 无 \n
 * 内容摘要： DSP驱动头文件 \n
 * 其它说明： 无 \n
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2018年07月25日 <td>1.0     <td>Howlet      <td>创建
 * </table>
 */

#ifndef _CONNIE_DSP_H_
#define _CONNIE_DSP_H_


/* Includes ------------------------------------------------------------------*/
#include "lks32mc07x_lib.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/** 
 *@brief DSP寄存器结构体句柄
 */

typedef struct {
__IO u32  SC             ;// 0x00)
__IO u32  THETA          ;// 0x04)
__IO u32  X              ;// 0x08)
__IO u32  Y              ;// 0x0C)
__IO u32  SIN            ;// 0x10)
__IO u32  COS            ;// 0x14)
__IO u32  MOD            ;// 0x18)
__IO u32  ARCTAN         ;// 0x1C)
__IO u32  DID            ;// 0x20)
__IO u32  DIS            ;// 0x24)
__IO u32  QUO            ;// 0x28)
__IO u32  REM            ;// 0x2C)
__IO u32  RAD            ;// 0x30)
__IO u32  SQRT           ;// 0x34)
__IO u32  PC             ;// 0x38)
}DSP_Typedef;
/** 
 *@brief DSP基地址
 */
#define DSP_REG  ((DSP_Typedef*)(DSP0_REG_BASE + 0x00))

void DSP_Init(void);
s16 DSP_arctan(s16 x,s16 y);
s32 DSP0_div(s32 a,s32 b);
s16 DSP0_sin(u16 angle);
s16 DSP0_cos(u16 angle);
u16 DSP0_rms(s16 a,s16 b);
s16 DSP0_mod(s32 x,s16 y);
u16 DSP0_sqrt(u32 val);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif
/************************ (C) COPYRIGHT LINKO SEMICONDUCTOR *****END OF FILE****/

