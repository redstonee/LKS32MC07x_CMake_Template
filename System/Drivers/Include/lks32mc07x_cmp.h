/**
 * @file 
 * @copyright (C)2015, LINKO SEMICONDUCTOR Co.ltd
 * @brief 文件名称： lks32mc07x_cmp.h\n
 * 文件标识： 无 \n
 * 内容摘要： CMP外设驱动程序头文件 \n
 * 其它说明： 无 \n
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author        <th>Description
 * <tr><td>2023年02月22日 <td>1.0     <td>Olive Wang          <td>创建
 * </table>
 */
#ifndef __lks32mc07x_CMP_H
#define __lks32mc07x_CMP_H
#include "lks32mc07x.h"
#include "basic.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/** 
 *@brief CMP初始化结构体句柄，初始化时请定义该句柄，并用其它地址来传参
 */
typedef struct
{
    u16 SELP;             /**< 比较器信号正端选择*/
	        /**
     * @brief 比较器 信号负端选择
     * @see CMP_SELN_IN 			            
     * @see CMP_SELN_REF 			           
     * @see CMP_SELN_DAC0 		           
     * @see CMP0_SELN_HALL0_MID
		 * @see CMP1_SELN_HALL1_MID
	   * @see CMP2_SELN_DAC1
     */    
    u16 SELN;   					/**< 比较器信号负端选择*/
	   /**
     * @brief CMP 滤波时钟频率Freq(CMP_Filter) = (Freq(MCLK)/2^FIL_CLK_DIV2)/(FIL_CLK_DIV16+1) ，
     * 其中MCLK 为系统的主时钟，通常为 96MHz 全速时钟。需要注意的是，产生 CMP 滤波时钟需要使能CLK_EN。
     */
		u32 FIL_CLK_DIV16;    /**< 比较器012滤波系数，赋值范围0-0xF */
    u32 FIL_CLK_DIV2;     /**< 比较器012滤波系数，0x0:1分频，0x1:2分频,0x2:4分频,0x3:8分频，0x4:16分频，0x5:32分频,0x6:64分频,0x7:128分频*/
	  /**
     * @brief 比较器输出极性选择
     * @see CMP_HIGH_LEVEL 			            
     * @see CMP_LOW_LEVEL 			           
     */    
  	u16 POL;        			/**< 比较器有效输出极性选择*/
	 	 /**
     * @brief 比较器开窗极性选择
     * @see W_PWM_HIGH_LEVEL 			            
     * @see W_PWM_LOW_LEVEL 			           
     */  
	  u16 W_PWM_POL;  			/**< 比较器开窗 PWM 信号极性选择,比较器 0/1 */
		/**
     * @brief 比较器触发中断方式选择
     * @see IRQ_LEVEL_TRIG_MODE 			            
     * @see IRQ_EDGE_TRIG_MODE 			           
     */  
  	u16 IRQ_TRIG;   			/**< 比较器边沿/电平触发中断选择*/
    FuncState CLK_EN;     /**< 比较器时钟使能，DISABLE:失能，ENABLE：使能*/
		FuncState EN;			    /**< 比较器使能\n DISABLE:失能，ENABLE：使能*/
    FuncState IE;         /**< 比较器中断使能，DISABLE:失能，ENABLE：使能*/
    FuncState RE;         /**< 比较器DMA 请求使能，DISABLE:失能，ENABLE：使能*/
    FuncState IN_EN;      /**< 比较器信号输入使能，DISABLE:失能，ENABLE：使能*/
    FuncState CHN3P_PWM_EN; /**< MCPWM 模块 CHN3_P 通道使能比较器 0/1 开窗，DISABLE:失能，ENABLE：使能*/
    FuncState CHN2P_PWM_EN; /**< MCPWM 模块 CHN2_P 通道使能比较器 0/1 开窗，DISABLE:失能，ENABLE：使能*/
    FuncState CHN1P_PWM_EN; /**< MCPWM 模块 CHN1_P 通道使能比较器 0/1 开窗，DISABLE:失能，ENABLE：使能*/
    FuncState CHN0P_PWM_EN; /**< MCPWM 模块 CHN0_P 通道使能比较器 0/1 开窗，DISABLE:失能，ENABLE：使能*/
} CMP_SingleTypeDef;
typedef struct
{
		 /**
     * @brief 比较器回差选择
     * @see CMP_HYS_20mV 			            
     * @see CMP_HYS_0mV 			           
     */  
		u8 HYS;                 /**< 比较器回差选择*/
		FuncState FT;           /**< 比较器快速比较使能  DISABLE/ENABLE*/
		u32 CLK_COM_DIV;        /**< 比较器共用分频系数，取值0-4*/
    CMP_SingleTypeDef CMP0; /**< CMP0配置*/
    CMP_SingleTypeDef CMP1; /**< CMP1配置*/
    CMP_SingleTypeDef CMP2; /**< CMP2配置*/

} CMP_InitTypeDef;
/** 
 *@brief CMP寄存器结构体句柄
 */
typedef struct
{
    __IO u32 IE;      /**< 比较器中断使能寄存器*/
    __IO u32 IF;      /**< 比较器中断标志寄存器*/
    __IO u32 TCLK;    /**< 比较器分频时钟控制寄存器*/
    __IO u32 CFG;     /**< 比较器控制寄存器*/
    __IO u32 BLCWIN;  /**< 比较器开窗控制寄存器*/
    __IO u32 DATA;    /**< 比较器输出数值寄存器*/
}CMP_TypeDef;
/**
 * CMP结构体基地址定义
 */
#define CMP  ((CMP_TypeDef*)CMP_BASE)

//比较器信号N端选择
#define CMP_SELN_IN 			   		0      		 /**< N端输入 */
#define CMP_SELN_REF 			   		1      		 /**< N端内部参考REF输入 */
#define CMP_SELN_DAC0 		   		2      		 /**< N端内部DAC0输入 */
#define CMP0_SELN_HALL0_MID  		3          /**< CMP0-N端反电势过零中点输入 */
#define CMP1_SELN_HALL1_MID  		3          /**< CMP1-N端反电势过零中点输入 */
#define CMP2_SELN_DAC1 		    	3      		 /**< CMP2-N端内部DAC1输入 */

//比较器0 P端选择
#define CMP0_SELP_IP0            0        /**< P端IP0输入 */
#define CMP0_SELP_OPA0_IP        1        /**< P端OPA0 IP输入*/
#define CMP0_SELP_OPA0_OUT       2        /**< P端OPA0 OUT */
#define CMP0_SELP_OPA1_OUT       3        /**< P端OPA1 OUT */
#define CMP0_SELP_IP1            4        /**< P端IP1输入 */
#define CMP0_SELP_IP2            5        /**< P端IP2输入 */
#define CMP0_SELP_IP3            6        /**< P端IP3输入 */
#define CMP0_SELP_IP4            7        /**< P端IP4输入*/ 

//比较器1 P端选择
#define CMP1_SELP_IP0            0        /**< P端IP0输入 */
#define CMP1_SELP_OPA3_IP        1        /**< P端OPA3 IP输入*/
#define CMP1_SELP_OPA2_OUT       2        /**< P端OPA2 OUT */
#define CMP1_SELP_OPA3_OUT       3        /**< P端OPA3 OUT */
#define CMP1_SELP_IP1            4        /**< P端IP1输入 */
#define CMP1_SELP_IP2            5        /**< P端IP2输入 */
#define CMP1_SELP_IP3            6        /**< P端IP3输入 */
#define CMP1_SELP_DAC0           7        /**< P端DAC0输入*/ 

//比较器2 P端选择
#define CMP2_SELP_IP0            0        /**< P端IP0输入 */
#define CMP2_SELP_IP1            1        /**< P端IP1输入 */
#define CMP2_SELP_OPA2_OUT       2        /**< P端OPA2 OUT */
#define CMP2_SELP_OPA3_OUT       3        /**< P端OPA3 OUT */

//有效极性选择
#define  CMP_HIGH_LEVEL  			0						/**高电平输出有效 */
#define  CMP_LOW_LEVEL  			1 					/**低电平输出有效 */

//开窗 PWM 信号极性选择
#define  IRQ_LEVEL_TRIG_MODE   0		/**< 电平触发中断模式 */
#define  IRQ_EDGE_TRIG_MODE    1  	/**< 边沿触发中断模式 */

//开窗 PWM 信号极性选择
#define  W_PWM_HIGH_LEVEL    1		/**< 比较器开窗高电平有效*/
#define  W_PWM_LOW_LEVEL     0		/**< 比较器开窗低电平有效*/

//比较通道选择
#define CMP_CHN_0 			0					/**< 通道0*/
#define CMP_CHN_1 			1					/**< 通道1*/
#define CMP_CHN_2 			2					/**< 通道2*/

/**< 比较器回差选择*/
#define CMP_HYS_20mV            0        /**< 20mV*/
#define CMP_HYS_0mV             1        /**< 0mV*/

void CMP_StructInit(CMP_InitTypeDef* CMP_InitStruct);/* CMP结构体初始化*/
void CMP_Init(CMP_InitTypeDef* CMP_InitStruct);/* CMP初始化*/
void CMP_Cmd(u8 CMP_CHN_x,FuncState state);/*CMP使能 */
void CMP_ClearIRQFlag(u8 CMP_CHN_x);    /* 清CMP中断 */
u8 CMP_GetIRQFlag(u8 CMP_CHN_x);        /* 读CMP中断 */
uint8_t CMP_GetFilterValue(void);/*读取滤波后的比较器值*/
uint8_t CMP_GetValue(void);/*读取未滤波的比较器值*/

#ifdef __cplusplus
}
#endif // __cplusplus

#endif /*__lks32mc07x_OPA_H */
/************************ (C) COPYRIGHT LINKO SEMICONDUCTOR **********************/
/* ------------------------------END OF FILE------------------------------------ */
