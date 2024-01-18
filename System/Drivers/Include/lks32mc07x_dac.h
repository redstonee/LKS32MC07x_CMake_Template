/**
 * @file 
 * @copyright (C)2015, LINKO SEMICONDUCTOR Co.ltd
 * @brief 文件名称： lks32mc07x_dac.h\n
 * 文件标识： 无 \n
 * 内容摘要： DAC外设驱动程序头文件 \n
 * 其它说明： 无 \n
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2023年3月22日 <td>1.0     <td>Olive Wang    <td>创建
 * </table>
 */ 
#ifndef _LKS32MC07X_DAC_H_
#define _LKS32MC07X_DAC_H_
/* Includes ------------------------------------------------------------------*/

#include "lks32mc07x_lib.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

typedef struct
{
	    /**
     * @brief DAC输出档位：1，1.2V；0，4.85V
     * @see DAC_RANGE_1V2
     * @see DAC_RANGE_4V85
     */
	uint8_t DAC_GAIN;   /**< DAC输出档位：1:1.2V；0:4.85V  */	             
	uint8_t DACOUT_EN;  /**< DAC输出使能：DISABLE，不使能；ENABLE，使能 */
	int8_t  DAC_STEP;   /**< 步进值， 3bit 有符号数，范围-4~3*/
	uint8_t TIG_CH_EN;  /**< UTIMER0/1/2/3触发步进使能,DISABLE，不使能；ENABLE，使能*/

} DAC_InitTypeDef;

/* ------------------------------DAC操作相关定义 ------------------------------ */
#define DAC_RANGE_4V85    0      	/**< DAC 4.85V量程 */
#define DAC_RANGE_1V2     1      	/**< DAC 1.2V量程 */
 
#define DAC_Channel_0    0			  	/**< DAC 通道0 */
#define DAC_Channel_1    1			 		/**< DAC 通道1*/

#define  DAC0_UTIMER0_TRG_EN    BIT0  /**< TIMER0 过零事件触发 DAC0 步进使能，高有效,DISABLE，不使能；ENABLE，使能*/ 
#define  DAC0_UTIMER1_TRG_EN    BIT1	 /**< TIMER1 过零事件触发 DAC0 步进使能，高有效,DISABLE，不使能；ENABLE，使能*/ 
#define  DAC0_UTIMER2_TRG_EN    BIT2  /**< TIMER2 过零事件触发 DAC0 步进使能，高有效,DISABLE，不使能；ENABLE，使能*/ 
#define  DAC0_UTIMER3_TRG_EN    BIT3  /**< TIMER3 过零事件触发 DAC0 步进使能，高有效,DISABLE，不使能；ENABLE，使能*/ 

#define  DAC1_UTIMER0_TRG_EN    BIT8  /**< TIMER0 过零事件触发 DAC1 步进使能，高有效,DISABLE，不使能；ENABLE，使能*/ 
#define  DAC1_UTIMER1_TRG_EN    BIT9  /**< TIMER1 过零事件触发 DAC1 步进使能，高有效,DISABLE，不使能；ENABLE，使能*/ 
#define  DAC1_UTIMER2_TRG_EN    BIT10 /**< TIMER2 过零事件触发 DAC1 步进使能，高有效,DISABLE，不使能；ENABLE，使能*/ 
#define  DAC1_UTIMER3_TRG_EN    BIT11 /**< TIMER3 过零事件触发 DAC1 步进使能，高有效,DISABLE，不使能；ENABLE，使能*/ 

void DAC_StructInit(DAC_InitTypeDef* DAC_InitStruct);										/* DAC结构体初始化 */
void DAC_Init(uint8_t DAC_Channel,DAC_InitTypeDef* DAC_InitStruct);      /* DAC初始化 */
void DAC_OutputValue(uint8_t DAC_Channel,uint32_t DACValue);             /* DAC输出数值设置--数字量 */
void DAC_OutputVoltage(uint8_t DAC_Channel,uint16_t DACVoltage);         /* DAC输出模拟量数值设置--模拟量 */
void DAC_Cmd(uint8_t DAC_Channel,FuncState state);												/* DAC通道时钟使能*/

#ifdef __cplusplus
}
#endif // __cplusplus

#endif /*__lks32mc07x_OPA_H */
/************************ (C) COPYRIGHT LINKO SEMICONDUCTOR *****END OF FILE****/



