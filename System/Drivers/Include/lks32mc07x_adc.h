/**
 * @file 
 * @copyright (C)2015, LINKO SEMICONDUCTOR Co.ltd
 * @brief 文件名称： LKS32MC07x_adc.h\n
 * 文件标识： 无 \n
 * 内容摘要： ADC外设驱动程序 \n
 * 其它说明： 无 \n
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2023年2月22日 <td>1.0     <td>zhujie    <td>创建
 * </table>
 */
#ifndef _CONNIE_ADC_H_
#define _CONNIE_ADC_H_


/* Includes ------------------------------------------------------------------*/
#include "lks32mc07x.h"
#include "basic.h"

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

typedef struct
{
    __IO uint32_t DAT0      ;   /**< 偏移地址: 0x00 ADCx 第 0 次常规采样数据*/
    __IO uint32_t DAT1      ;   /**< 偏移地址: 0x04 ADCx 第 1 次常规采样数据*/
    __IO uint32_t DAT2      ;   /**< 偏移地址: 0x08 ADCx 第 2 次常规采样数据*/
    __IO uint32_t DAT3      ;   /**< 偏移地址: 0x0C ADCx 第 3 次常规采样数据*/
																/**<                                      */
    __IO uint32_t DAT4      ;   /**< 偏移地址: 0x10 ADCx 第 4 次常规采样数据*/
    __IO uint32_t DAT5      ;   /**< 偏移地址: 0x14 ADCx 第 5 次常规采样数据*/
    __IO uint32_t DAT6      ;   /**< 偏移地址: 0x18 ADCx 第 6 次常规采样数据*/
    __IO uint32_t DAT7      ;   /**< 偏移地址: 0x1C ADCx 第 7 次常规采样数据*/
																/**<                                      */
    __IO uint32_t DAT8      ;   /**< 偏移地址: 0x20 ADCx 第 8 次常规采样数据*/
    __IO uint32_t DAT9      ;   /**< 偏移地址: 0x24 ADCx 第 9 次常规采样数据*/
    __IO uint32_t DAT10     ;   /**< 偏移地址: 0x28 ADCx 第 10 次常规采样数据 */
    __IO uint32_t DAT11     ;   /**< 偏移地址: 0x2C ADCx 第 11 次常规采样数据 */
										
    __IO uint32_t DAT12     ;   /**< 偏移地址: 0x30 ADCx 第 12 次常规采样数据*/ 
    __IO uint32_t DAT13     ;   /**< 偏移地址: 0x34 ADCx 第 13 次常规采样数据 */
    __IO uint32_t IDAT0     ;   /**< 偏移地址: 0x38 ADCx 第 0 次空闲采样数据*/  
    __IO uint32_t IDAT1     ;   /**< 偏移地址: 0x3C ADCx 第 1 次空闲采样数据*/
															
    __IO uint32_t ICHN      ;   /**< 偏移地址: 0x40 ADCx 空闲采样通道配置*/
    __IO uint32_t null      ;   /**< 偏移地址: 0x44 地址对齐，无意义*/
    __IO uint32_t null1     ;   /**< 偏移地址: 0x48 地址对齐，无意义*/
    __IO uint32_t null2     ;   /**< 偏移地址: 0x4C 地址对齐，无意义*/
													
    __IO uint32_t CHN0      ;   /**< 偏移地址: 0x50 ADCx 第 0~ 3 次常规采样输入信号选择 Signal 0 Signal 0 Signal 0 Signal 0 Signal 0 Signal 0*/
    __IO uint32_t CHN1      ;   /**< 偏移地址: 0x54 ADCx 第 4~ 7 次常规采样输入信号选择*/
    __IO uint32_t CHN2      ;   /**< 偏移地址: 0x58 ADCx 第 8~11 次常规采样输入信号选择*/
    __IO uint32_t CHN3      ;   /**< 偏移地址: 0x5C ADCx 第 12~15 次常规采样输入信号选择*/
																
    __IO uint32_t CHNT      ;   /**< 偏移地址: 0x60 ADCx 各种触发模式下采样次数*/
    __IO uint32_t GAIN      ;   /**< 偏移地址: 0x64 ADCx 增益选择*/
    __IO uint32_t null3     ;   /**< 偏移地址: 0x68 地址对齐，无意义*/
    __IO uint32_t null4     ;   /**< 偏移地址: 0x6C 地址对齐，无意义*/
																
    __IO uint32_t null5     ;   /**< 偏移地址: 0x70 地址对齐，无意义*/
    __IO uint32_t CFG       ;   /**< 偏移地址: 0x74 ADCx 模式配置*/
    __IO uint32_t TRIG      ;   /**< 偏移地址: 0x78 ADCx 采样触发配置*/
    __IO uint32_t SWT       ;   /**< 偏移地址: 0x7C ADCx 软件触发*/
															
    __IO uint32_t DC0       ;   /**< 偏移地址: 0x80 ADCx 增益为 0 时 DC offset*/
    __IO uint32_t AMC0      ;   /**< 偏移地址: 0x84 ADCx 增益为 0 时增益校正系数*/
    __IO uint32_t DC1       ;   /**< 偏移地址: 0x88 ADCx 增益为 1 时 DC offset*/
    __IO uint32_t AMC1      ;   /**< 偏移地址: 0x8C ADCx 增益为 1 时增益校正系数*/
													
    __IO uint32_t IE        ;   /**< 偏移地址: 0x90 ADCx 中断使能*/
    __IO uint32_t IF        ;   /**< 偏移地址: 0x94 ADCx 中断标志*/
    __IO uint32_t null6     ;   /**< 偏移地址: 0x98 地址对齐，无意义*/
    __IO uint32_t null7     ;   /**< 偏移地址: 0x9C 地址对齐，无意义*/
															
    __IO uint32_t null8     ;   /**< 偏移地址: 0xA0 地址对齐，无意义*/
    __IO uint32_t null9     ;   /**< 偏移地址: 0xA4 地址对齐，无意义*/
    __IO uint32_t null10    ;   /**< 偏移地址: 0xA8 地址对齐，无意义*/
    __IO uint32_t null11    ;   /**< 偏移地址: 0xAC 地址对齐，无意义*/
											
    __IO uint32_t null12    ;   /**< 偏移地址: 0xB0 地址对齐，无意义*/
    __IO uint32_t null13    ;   /**< 偏移地址: 0xB4 地址对齐，无意义*/
    __IO uint32_t null14    ;   /**< 偏移地址: 0xB8 地址对齐，无意义*/
    __IO uint32_t null15    ;   /**< 偏移地址: 0xBC 地址对齐，无意义*/
															
    __IO uint32_t null16    ;   /**< 偏移地址: 0xCC 地址对齐，无意义*/
    __IO uint32_t LTH       ;   /**< 偏移地址: 0xC4 ADCx 数据低阈值*/
    __IO uint32_t HTH       ;   /**< 偏移地址: 0xC8 ADCx 数据高阈值*/
    __IO uint32_t GEN       ;   /**< 偏移地址: 0xCC ADCx 阈值监测使能*/
} ADC_TypeDef;

#define ADC0         ((ADC_TypeDef *) ADC0_BASE)
#define ADC1         ((ADC_TypeDef *) ADC1_BASE)

typedef struct
{
    u16 IE          ;           /**< 中断使能*/
    u16 RE          ;           /**< DMA请求使能*/
    u16 NSMP        ;           /**< 两段采样使能*/
    u16 DATA_ALIGN  ;           /**< DAT右对齐使能*/
    u16 CSMP        ;           /**< 连续采样使能*/
    u16 TCNT        ;           /**< 触发一次采样所需的事件数*/
    u16 TROVS       ;           /**< 手动触发过采样使能，开启后一次采样需要多次触发*/
    u16 OVSR        ;           /**< 过采样率*/
    u16 TRIG        ;           /**< 触发信号*/
    u16 S1          ;           /**< 第一段常规采样次数*/
    u16 S2          ;           /**< 第二段常规采样次数*/
    u16 IS1         ;           /**< 空闲采样次数*/
    u16 GAIN        ;           /**< 低增益（7.2V量程）使能*/
    u16 LTH         ;           /**< ADC 模拟看门狗 0 下阈值*/
    u16 HTH         ;           /**< ADC 模拟看门狗 0 上阈值*/
    u16 GEN         ;           /**< ADC 模拟看门狗 0 对应使能位*/
} ADC_InitTypeDef;


#define ADC_ISF_RE      BIT15   /**< 空闲采样完成 DMA 请求使能*/
#define ADC_HERR_RE     BIT14   /**< 硬件触发发生在非空闲状态 DMA 请求使能*/
#define ADC_SERR_RE     BIT13   /**< 软件触发发生在非空闲状态 DMA 请求使能*/
#define ADC_AWD0_RE     BIT10   /**< 阈值监测 0 超限 DMA 请求使能*/
#define ADC_SF2_RE      BIT9    /**< 第二段采样完成 DMA 请求使能*/
#define ADC_SF1_RE      BIT8    /**< 第一段采样完成 DMA 请求使能*/
        
#define ADC_ISF_IE      BIT7    /**< 空闲采样完成中断使能*/
#define ADC_HERR_IE     BIT6    /**< 硬件触发发生在非空闲状态中断使能*/
#define ADC_SERR_IE     BIT5    /**< 软件触发发生在非空闲状态中断使能*/
#define ADC_AWD0_IE     BIT2    /**< 阈值监测 0 超限中断使能*/
#define ADC_SF2_IE      BIT1    /**< 第二段常规采样完成中断使能*/
#define ADC_SF1_IE      BIT0    /**< 第一段常规采样完成中断使能*/


#define ADC_ISF_IF      BIT7    /**< 空闲采样完成中断标志*/
#define ADC_HERR_IF     BIT6    /**< 硬件触发发生在非空闲状态中断标志*/
#define ADC_SERR_IF     BIT5    /**< 软件触发发生在非空闲状态中断标志*/
#define ADC_AWD0_IF     BIT2    /**< 阈值监测 0 超限中断标志*/
#define ADC_SF2_IF      BIT1    /**< 第二段常规采样完成中断标志*/
#define ADC_SF1_IF      BIT0    /**< 第一段常规采样完成中断标志*/
#define ADC_ALL_IF      (0x7f)  /**< ADC全部中断标志位——可用于初始化 */

#define ADC_TRIG_CL_IT3        BIT15  /**< CL_OUTPUT[3]触发 ADC 空闲采样使能，高有效*/
#define ADC_TRIG_CL_IT2        BIT14  /**< CL_OUTPUT[2]触发 ADC 空闲采样使能，高有效*/
#define ADC_TRIG_CL_IT1        BIT13  /**< CL_OUTPUT[1]触发 ADC 空闲采样使能，高有效*/
#define ADC_TRIG_CL_IT0        BIT12  /**< CL_OUTPUT[0]触发 ADC 空闲采样使能，高有效*/
#define ADC_TRIG_CL_NT3        BIT11  /**< CL_OUTPUT[3]触发 ADC 常规采样使能，高有效*/
#define ADC_TRIG_CL_NT2        BIT10  /**< CL_OUTPUT[2]触发 ADC 常规采样使能，高有效*/
#define ADC_TRIG_CL_NT1        BIT9   /**< CL_OUTPUT[1]触发 ADC 常规采样使能，高有效*/
#define ADC_TRIG_CL_NT0        BIT8   /**< CL_OUTPUT[0]触发 ADC 常规采样使能，高有效*/
#define ADC_TRIG_UTIMER2_CMP1  BIT7   /**< UTIMER2 比较事件 1 触发 ADC 常规采样使能，高有效*/
#define ADC_TRIG_UTIMER2_CMP0  BIT6   /**< UTIMER2 比较事件 0 触发 ADC 常规采样使能，高有效*/
#define ADC_TRIG_UTIMER0_CMP1  BIT5   /**< UTIMER0 比较事件 1 触发 ADC 常规采样使能，高有效*/
#define ADC_TRIG_UTIMER0_CMP0  BIT4   /**< UTIMER0 比较事件 0 触发 ADC 常规采样使能，高有效*/
#define ADC_TRIG_MCPWM0_T3     BIT3   /**< MCPWM0 T3 事件触发 ADC 常规采样使能，高有效*/
#define ADC_TRIG_MCPWM0_T2     BIT2   /**< MCPWM0 T2 事件触发 ADC 常规采样使能，高有效*/
#define ADC_TRIG_MCPWM0_T1     BIT1   /**< MCPWM0 T1 事件触发 ADC 常规采样使能，高有效*/
#define ADC_TRIG_MCPWM0_T0     BIT0   /**< MCPWM0 T0 事件触发 ADC 常规采样使能，高有效*/




#define ADC_CHANNEL_0   0x0     /**< OPA0 输出  ADC0和ADC1通道0-9共用*/
#define ADC_CHANNEL_1   0x1     /**< OPA1 输出  ADC0和ADC1通道0-9共用*/
#define ADC_CHANNEL_2   0x2     /**< OPA2 输出  ADC0和ADC1通道0-9共用*/
#define ADC_CHANNEL_3   0x3     /**< OPA3 输出  ADC0和ADC1通道0-9共用*/
#define ADC_CHANNEL_4   0x4     /**< ADC01_CH4  ADC0和ADC1通道0-9共用*/
#define ADC_CHANNEL_5   0x5     /**< ADC01_CH5  ADC0和ADC1通道0-9共用*/
#define ADC_CHANNEL_6   0x6     /**< ADC01_CH6  ADC0和ADC1通道0-9共用*/
#define ADC_CHANNEL_7   0x7     /**< ADC01_CH7  ADC0和ADC1通道0-9共用*/
#define ADC_CHANNEL_8   0x8     /**< ADC01_CH8  ADC0和ADC1通道0-9共用*/
#define ADC_CHANNEL_9   0x9     /**< ADC01_CH9  ADC0和ADC1通道0-9共用*/
#define ADC_CHANNEL_10  0xA     /**< ADC0_CH10  ADC1_CH10  ADC0和ADC1通道对应IO口不同*/
#define ADC_CHANNEL_11  0xB     /**< ADC0_CH11  ADC1_CH11  ADC0和ADC1通道对应IO口不同*/
#define ADC_CHANNEL_12  0xC     /**< ADC0_CH12  ADC1_CH12  ADC0和ADC1通道对应IO口不同*/
#define ADC_CHANNEL_13  0xD     /**< ADC0_CH13  ADC1_CH13  ADC0和ADC1通道对应IO口不同*/
#define ADC_CHANNEL_14  0xE     /**< ADC0通道14对应DAC0输出 ADC1通道14对应温度传感器  */
#define ADC_CHANNEL_15  0xF     /**< ADC0通道15对应DAC1输出 ADC1通道15对应内部地 AVSS */

/** ADC采样通道序号*/ 
typedef enum {
	CHN0 = 0, /**< 第0次采样通道序号*/
  CHN1,     /**< 第1次采样通道序号*/
  CHN2,     /**< 第2次采样通道序号*/
  CHN3,     /**< 第3次采样通道序号*/
  CHN4,     /**< 第4次采样通道序号*/
  CHN5,     /**< 第5次采样通道序号*/
  CHN6,     /**< 第6次采样通道序号*/
  CHN7,     /**< 第7次采样通道序号*/
  CHN8,     /**< 第8次采样通道序号*/
  CHN9,     /**< 第9次采样通道序号*/
	CHN10,    /**< 第10次采样通道序号*/
  CHN11,    /**< 第11次采样通道序号*/
  CHN12,    /**< 第12次采样通道序号*/
  CHN13,    /**< 第13次采样通道序号*/
  CHN14,    /**< 第14次采样通道序号*/
  CHN15,    /**< 第15次采样通道序号*/
} CHNx;
/** ADC数据寄存器序号*/ 
typedef enum {
  DAT0 = 0,  /**< 第0次采样信号对应结果寄存器序号*/
  DAT1,      /**< 第1次采样信号对应结果寄存器序号*/
  DAT2,      /**< 第2次采样信号对应结果寄存器序号*/
  DAT3,      /**< 第3次采样信号对应结果寄存器序号*/
  DAT4,      /**< 第4次采样信号对应结果寄存器序号*/
  DAT5,      /**< 第5次采样信号对应结果寄存器序号*/
  DAT6,      /**< 第6次采样信号对应结果寄存器序号*/
  DAT7,      /**< 第7次采样信号对应结果寄存器序号*/
  DAT8,      /**< 第8次采样信号对应结果寄存器序号*/
  DAT9,      /**< 第9次采样信号对应结果寄存器序号*/
  DAT10,     /**< 第10次采样信号对应结果寄存器序号*/
  DAT11,     /**< 第11次采样信号对应结果寄存器序号*/
  DAT12,     /**< 第12次采样信号对应结果寄存器序号*/
  DAT13,     /**< 第13次采样信号对应结果寄存器序号*/
  DAT14,     /**< 第14次采样信号对应结果寄存器序号*/
  DAT15,     /**< 第15次采样信号对应结果寄存器序号*/
} DATx;

	/*定义ADC增益序号*/
typedef enum 
{
		ADC_GAIN3V6 = 0,     /**< 3.6V 量程 */
		ADC_GAIN7V2 = 1,     /**< 7.2V 量程 */
}ADC_GAINx; 

void ADC_Init(ADC_TypeDef* ADCx, ADC_InitTypeDef* ADC_InitStruct);
void ADC_StructInit(ADC_InitTypeDef* ADC_InitStruct);
u16 ADC_GetIRQFlag(ADC_TypeDef *ADCx, uint16_t INT_flag);
void ADC_ClearIRQFlag(ADC_TypeDef *ADCx, uint16_t INT_flag);
void ADC_CHN_GAIN_CFG(ADC_TypeDef *ADCx,CHNx CHNum,u8 nChannel, ADC_GAINx GAIN3V6_or_7V2);
s16 ADC_GetConversionValue(ADC_TypeDef *ADCx,DATx DATNum);
void ADC_SoftTrgEN(ADC_TypeDef *ADCx, FuncState state);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif /*_CONNIE_ADC_H_ */



/************************ (C) COPYRIGHT LINKO SEMICONDUCTOR *****END OF FILE****/
