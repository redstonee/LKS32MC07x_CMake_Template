/**
 * @file
 * @copyright (C)2015, LINKO SEMICONDUCTOR Co.ltd
 * @brief 文件名称： LKS32MC07x_mcpwm.h\n
 * 文件标识： 无 \n
 * 内容摘要： MCPWM外设驱动程序 \n
 * 其它说明： 无 \n
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2023年3月06日 <td>1.0      <td>Zhujie    <td>创建
 * </table>
 */

#ifndef __LKS08X_PWM_H
#define __LKS08X_PWM_H

/* Includes
 * ------------------------------------------------------------------*/
#include "lks32mc07x_lib.h"

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

  typedef struct
  {
    __IO u32 TH00; /**< 偏移地址: 0x00 MCPWM CH0_P 比较门限值寄存器*/
    __IO u32 TH01; /**< 偏移地址: 0x04 MCPWM CH0_N 比较门限值寄存器*/
    __IO u32 TH10; /**< 偏移地址: 0x08 MCPWM CH1_P 比较门限值寄存器*/
    __IO u32 TH11; /**< 偏移地址: 0x0C MCPWM CH1_N 比较门限值寄存器*/

    __IO u32 TH20; /**< 偏移地址: 0x10 MCPWM CH2_P 比较门限值寄存器*/
    __IO u32 TH21; /**< 偏移地址: 0x14 MCPWM CH2_N 比较门限值寄存器*/
    __IO u32 TH30; /**< 偏移地址: 0x18 MCPWM CH3_P 比较门限值寄存器*/
    __IO u32 TH31; /**< 偏移地址: 0x1C MCPWM CH3_N 比较门限值寄存器*/

    __IO u32 TH40; /**< 偏移地址: 0x20 MCPWM CH4_P 比较门限值寄存器*/
    __IO u32 TH41; /**< 偏移地址: 0x24 MCPWM CH4_N 比较门限值寄存器*/
    __IO u32 TH50; /**< 偏移地址: 0x28 MCPWM CH5_P 比较门限值寄存器*/
    __IO u32 TH51; /**< 偏移地址: 0x2C MCPWM CH5_N 比较门限值寄存器*/

    __IO u32 TMR0; /**< 偏移地址: 0x30 ADC 采样定时器比较门限 0 寄存器*/
    __IO u32 TMR1; /**< 偏移地址: 0x34 ADC 采样定时器比较门限 1 寄存器*/
    __IO u32 TMR2; /**< 偏移地址: 0x38 ADC 采样定时器比较门限 2 寄存器*/
    __IO u32 TMR3; /**< 偏移地址: 0x3C ADC 采样定时器比较门限 3 寄存器*/

    __IO u32 TH0;  /**< 偏移地址: 0x40 MCPWM 时基 0 门限值寄存器*/
    __IO u32 TH1;  /**< 偏移地址: 0x44 MCPWM 时基 1 门限值寄存器*/
    __IO u32 CNT0; /**< 偏移地址: 0x48 MCPWM 时基 0 计数器寄存器*/
    __IO u32 CNT1; /**< 偏移地址: 0x4C MCPWM 时基 1 计数器寄存器*/

    __IO u32 UPDATE; /**< 偏移地址: 0x50 MCPWM 加载控制寄存器*/
    __IO u32 FCNT;   /**< 偏移地址: 0x54 MCPWM FAIL 时刻 CNT 值*/
    __IO u32 EVT0;   /**< 偏移地址: 0x58 MCPWM 时基 0 外部触发*/
    __IO u32 EVT1;   /**< 偏移地址: 0x5C MCPWM 时基 1 外部触发*/

    __IO u32
        DTH00; /**< 偏移地址: 0x60 MCPWM CH0/1/2 N 通道死区宽度控制寄存器*/
    __IO u32
        DTH01; /**< 偏移地址: 0x64 MCPWM CH0/1/2 P 通道死区宽度控制寄存器*/
    __IO u32
        DTH10; /**< 偏移地址: 0x68 MCPWM CH3/4/5 N 通道死区宽度控制寄存器*/
    __IO u32
        DTH11; /**< 偏移地址: 0x6C MCPWM CH3/4/5 P 通道死区宽度控制寄存器*/

    __IO u32 FLT;   /**< 偏移地址: 0x70 MCPWM 滤波时钟分频寄存器*/
    __IO u32 SDCFG; /**< 偏移地址: 0x74 MCPWM 加载配置寄存器*/
    __IO u32 AUEN;  /**< 偏移地址: 0x78 MCPWM 自动更新使能寄存器*/
    __IO u32 TCLK;  /**< 偏移地址: 0x7C MCPWM 时钟分频控制寄存器*/

    __IO u32 IE0; /**< 偏移地址: 0x80 MCPWM 时基 0 中断控制寄存器*/
    __IO u32 IF0; /**< 偏移地址: 0x84 MCPWM 时基 0 中断标志位寄存器*/
    __IO u32 IE1; /**< 偏移地址: 0x88 MCPWM 中断控制寄存器*/
    __IO u32 IF1; /**< 偏移地址: 0x8C MCPWM 中断标志位寄存器*/

    __IO u32 EIE; /**< 偏移地址: 0x90 MCPWM 异常中断控制寄存器*/
    __IO u32 EIF; /**< 偏移地址: 0x94 MCPWM 异常中断标志位寄存器*/
    __IO u32 RE;  /**< 偏移地址: 0x98 MCPWM DMA 请求控制寄存器*/
    __IO u32 PP;  /**< 偏移地址: 0x9C MCPWM 推挽模式使能寄存器*/

    __IO u32 IO01; /**< 偏移地址: 0xA0 MCPWM CH0 CH1 IO 控制寄存器*/
    __IO u32 IO23; /**< 偏移地址: 0xA4 MCPWM CH2 CH3 IO 控制寄存器*/
    __IO u32 IO45; /**< 偏移地址: 0xA8 MCPWM CH4 CH5 IO 控制寄存器*/
    __IO u32 null; /**< 偏移地址: 0xAC 地址对齐*/

    __IO u32 FAIL012; /**< 偏移地址: 0xB0 MCPWM CH0 CH1 CH2 短路控制寄存器*/
    __IO u32 FAIL345; /**< 偏移地址: 0xB4 MCPWM CH3 CH4 CH5 短路控制寄存器*/
    __IO u32 CH_DEF; /**< 偏移地址: 0xB8 MCPWM 短路保护通道输出默认值*/
    __IO u32 CH_MSK; /**< 偏移地址: 0xBC MCPWM 通道屏蔽寄存器*/

    __IO u32 PRT;      /**< 偏移地址: 0xC0 MCPWM 保护寄存器*/
    __IO u32 STT_HYST; /**< 偏移地址: 0xC8 MCPWM 状态停留延时寄存器*/
    __IO u32 ZCS_DELAY; /**< 偏移地址: 0xCC MCPWM ZCS 状态延时寄存器*/
  } MCPWM_TypeDef;

#define MCPWM0 ((MCPWM_TypeDef *)MCPWM0_BASE)

  typedef struct
  {
    uint16_t TH0; /**< MCPWM时基0计数器门限值（PWM周期）*/
    uint16_t TH1; /**< MCPWM时基1计数器门限值（PWM周期）*/

    uint16_t TH00; /**< MCPWM时基0 CH0P比较门限值（PWM占空比）*/
    uint16_t TH01; /**< MCPWM时基0 CH0N比较门限值（PWM占空比）*/
    uint16_t TH10; /**< MCPWM时基0 CH1P比较门限值（PWM占空比）*/
    uint16_t TH11; /**< MCPWM时基0 CH1N比较门限值（PWM占空比）*/
    uint16_t TH20; /**< MCPWM时基0 CH2P比较门限值（PWM占空比）*/
    uint16_t TH21; /**< MCPWM时基0 CH2N比较门限值（PWM占空比）*/

    uint16_t TH30; /**< MCPWM时基1 CH3P比较门限值（PWM占空比）*/
    uint16_t TH31; /**< MCPWM时基1 CH3N比较门限值（PWM占空比）*/
    uint16_t TH40; /**< MCPWM时基1 CH4P比较门限值（PWM占空比）*/
    uint16_t TH41; /**< MCPWM时基1 CH4N比较门限值（PWM占空比）*/
    uint16_t TH50; /**< MCPWM时基1 CH5P比较门限值（PWM占空比）*/
    uint16_t TH51; /**< MCPWM时基1 CH5N比较门限值（PWM占空比）*/

    uint8_t CMP_CTRL_CNT1; /**< 比较器控制计数器1使能 */
    uint8_t CMP_CTRL_CNT0; /**< 比较器控制计数器0使能 */

    uint8_t BASE_CNT1_EN; /**< MCPWM 计数器1使能开关 */
    uint8_t BASE_CNT0_EN; /**< MCPWM 计数器0使能开关 */

    uint8_t EVT_CNT1_EN; /**<*< MCPWM 计数器1外部触发使能 */
    uint8_t EVT_CNT0_EN; /**< MCPWM 计数器0外部触发使能 */

    uint8_t TMR3_TB; /**< MCPWM TMR3时基（计数器）选择 0：时基0；1：时基1 */
    uint8_t TMR2_TB; /**< MCPWM TMR2时基（计数器）选择 0：时基0；1：时基1 */

    uint8_t ZCS_EN; /**< 使能ZCS事件检测 高有效 */

    uint8_t MCLK_EN; /**< MCPWM 时钟使能开关 */
    uint8_t CLK_DIV; /**< MCPWM 分频系数 */

    uint16_t MCPWM_WorkModeCH0; /**< MCPWM CH0工作模式：边沿对齐/中心对齐 */
    uint16_t MCPWM_WorkModeCH1; /**< MCPWM CH1工作模式：边沿对齐/中心对齐 */
    uint16_t MCPWM_WorkModeCH2; /**< MCPWM CH2工作模式：边沿对齐/中心对齐 */
    uint16_t MCPWM_WorkModeCH3; /**< MCPWM CH3工作模式：边沿对齐/中心对齐 */
    uint16_t MCPWM_WorkModeCH4; /**< MCPWM CH4工作模式：边沿对齐/中心对齐 */
    uint16_t MCPWM_WorkModeCH5; /**< MCPWM CH5工作模式：边沿对齐/中心对齐 */

    uint16_t TMR0; /**< PWM触发ADC事件0，时间点设置 */
    uint16_t TMR1; /**< PWM触发ADC事件1，时间点设置 */
    uint16_t TMR2; /**< PWM触发ADC事件2，时间点设置 */
    uint16_t TMR3; /**< PWM触发ADC事件3，时间点设置 */

    uint16_t DeadTimeCH012N; /**< CH0N、CH1N、Ch2N死区时间设置　*/
    uint16_t DeadTimeCH012P; /**< CH0P、CH1P、Ch2P死区时间设置*/
    uint16_t DeadTimeCH345N; /**< CH3N、CH4N、Ch5N死区时间设置*/
    uint16_t DeadTimeCH345P; /**< CH3P、CH4P、Ch5P死区时间设置*/

    uint16_t EVT0; /**< 外部事件触发MCPWM_CNT0 (时基0)从0开始使能 */
    uint16_t EVT1; /**< 外部事件触发MCPWM_CNT1 (时基1)从0开始使能 */

    uint8_t CH0N_Polarity_INV; /**< CH0N输出极性取反，0:正常输出；1:取反输出 */
    uint8_t CH0P_Polarity_INV; /**< CH0P输出极性取反，0:正常输出；1:取反输出 */
    uint8_t CH1N_Polarity_INV; /**< CH1N输出极性取反，0:正常输出；1:取反输出 */
    uint8_t CH1P_Polarity_INV; /**< CH1P输出极性取反，0:正常输出；1:取反输出 */
    uint8_t CH2N_Polarity_INV; /**< CH2N输出极性取反，0:正常输出；1:取反输出 */
    uint8_t CH2P_Polarity_INV; /**< CH2P输出极性取反，0:正常输出；1:取反输出 */
    uint8_t CH3N_Polarity_INV; /**< CH3N输出极性取反，0:正常输出；1:取反输出 */
    uint8_t CH3P_Polarity_INV; /**< CH3P输出极性取反，0:正常输出；1:取反输出 */
    uint8_t CH4N_Polarity_INV; /**< CH4N输出极性取反，0:正常输出；1:取反输出 */
    uint8_t CH4P_Polarity_INV; /**< CH4P输出极性取反，0:正常输出；1:取反输出 */
    uint8_t CH5N_Polarity_INV; /**< CH5N输出极性取反，0:正常输出；1:取反输出 */
    uint8_t CH5P_Polarity_INV; /**< CH5P输出极性取反，0:正常输出；1:取反输出 */

    uint8_t CH0P_SCTRLP; /**< 当CH0_PS = 1时，输出到CH0_P通道的值*/
    uint8_t CH0N_SCTRLN; /**< 当CH0_NS = 1时，输出到CH0_N通道的值*/
    uint8_t CH1P_SCTRLP; /**< 当CH1_PS = 1时，输出到CH1_P通道的值*/
    uint8_t CH1N_SCTRLN; /**< 当CH1_NS = 1时，输出到CH1_N通道的值*/
    uint8_t CH2P_SCTRLP; /**< 当CH2_PS = 1时，输出到CH2_P通道的值*/
    uint8_t CH2N_SCTRLN; /**< 当CH2_NS = 1时，输出到CH2_N通道的值*/
    uint8_t CH3P_SCTRLP; /**< 当CH3_PS = 1时，输出到CH3_P通道的值*/
    uint8_t CH3N_SCTRLN; /**< 当CH3_NS = 1时，输出到CH3_N通道的值*/
    uint8_t CH4P_SCTRLP; /**< 当CH4_PS = 1时，输出到CH4_P通道的值*/
    uint8_t CH4N_SCTRLN; /**< 当CH4_NS = 1时，输出到CH4_N通道的值*/
    uint8_t CH5P_SCTRLP; /**< 当CH5_PS = 1时，输出到CH5_P通道的值*/
    uint8_t CH5N_SCTRLN; /**< 当CH5_NS = 1时，输出到CH5_N通道的值*/

    uint8_t
        CH0_PS; /**<
                   CH0_P信号来源，1：来自CH0_SCTRLP；0：来自MCPWM实际运行计数器*/
    uint8_t
        CH0_NS; /**<
                   CH0_N信号来源，1：来自CH0_SCTRLN；0：来自MCPWM实际运行计数器*/
    uint8_t
        CH1_PS; /**<
                   CH1_P信号来源，1：来自CH1_SCTRLP；0：来自MCPWM实际运行计数器*/
    uint8_t
        CH1_NS; /**<
                   CH1_N信号来源，1：来自CH1_SCTRLN；0：来自MCPWM实际运行计数器*/
    uint8_t
        CH2_PS; /**<
                   CH2_P信号来源，1：来自CH2_SCTRLP；0：来自MCPWM实际运行计数器*/
    uint8_t
        CH2_NS; /**<
                   CH2_N信号来源，1：来自CH2_SCTRLN；0：来自MCPWM实际运行计数器*/
    uint8_t
        CH3_PS; /**<
                   CH3_P信号来源，1：来自CH3_SCTRLP；0：来自MCPWM实际运行计数器*/
    uint8_t
        CH3_NS; /**<
                   CH3_N信号来源，1：来自CH3_SCTRLN；0：来自MCPWM实际运行计数器*/
    uint8_t
        CH4_PS; /**<
                   CH4_P信号来源，1：来自CH4_SCTRLP；0：来自MCPWM实际运行计数器*/
    uint8_t
        CH4_NS; /**<
                   CH4_N信号来源，1：来自CH4_SCTRLN；0：来自MCPWM实际运行计数器*/
    uint8_t
        CH5_PS; /**<
                   CH5_P信号来源，1：来自CH5_SCTRLP；0：来自MCPWM实际运行计数器*/
    uint8_t
        CH5_NS; /**<
                   CH5_N信号来源，1：来自CH5_SCTRLN；0：来自MCPWM实际运行计数器*/

    uint8_t Switch_CH0N_CH0P; /**< 交换CH0N, CH0P信号输出使能开关 */
    uint8_t Switch_CH1N_CH1P; /**< 交换CH1N, CH1P信号输出使能开关 */
    uint8_t Switch_CH2N_CH2P; /**< 交换CH2N, CH2P信号输出使能开关 */
    uint8_t Switch_CH3N_CH3P; /**< 交换CH3N, CH3P信号输出使能开关 */
    uint8_t Switch_CH4N_CH4P; /**< 交换CH2N, CH2P信号输出使能开关 */
    uint8_t Switch_CH5N_CH5P; /**< 交换CH3N, CH3P信号输出使能开关 */

    uint8_t TR0_UP_INTV;     /**< MCPWM_CNT0 更新间隔 T0/T1事件次数 */
    uint8_t TR0_T0_UpdateEN; /**< MCPWM_CNT0 T0事件更新使能 */
    uint8_t TR0_T1_UpdateEN; /**< MCPWM_CNT0 T1事件更新使能 */
    uint8_t TR0_AEC;         /**< MCPWM
                                更新事件是否自动清除Fail0和Fail1事件（恢复CH0CH1CH2输出）
                                1：使能 */

    uint8_t TR1_UP_INTV;     /**< MCPWM_CNT1 更新间隔 T0/T1事件次数 */
    uint8_t TR1_T0_UpdateEN; /**< MCPWM_CNT1 T0事件更新使能 */
    uint8_t TR1_T1_UpdateEN; /**< MCPWM_CNT1 T1事件更新使能 */
    uint8_t TR1_AEC;         /**< MCPWM
                                更新事件是否自动清除Fail2和Fail3事件（恢复CH3CH4CH5输出）
                                1：使能 */

    uint8_t FAIL0_INPUT_EN; /**< FAIL0 输入功能使能 */
    uint8_t FAIL1_INPUT_EN; /**< FAIL1 输入功能使能 */
    uint8_t
        FAIL_0CAP; /**< FAIL01事件发生时 将MCPWM0_CNT0值存入MCPWM0_FCNT 使能 */
    uint8_t FAIL0_Signal_Sel; /**< FAIL0 信号选择，比较器0或GPIO */
    uint8_t FAIL1_Signal_Sel; /**< FAIL1 信号选择，比较器0或GPIO */
    uint8_t FAIL0_Polarity; /**< FAIL0 信号极性设置，高有效或低有效 */
    uint8_t FAIL1_Polarity; /**< FAIL1 信号极性设置，高有效或低有效 */
    uint8_t HALT_PRT0; /**<  MCU进入HALT状态, MCPWM(CH0CH1CH2)信号是否正常输出
                          1正常输出；0强制输出保护值 */

    uint8_t FAIL2_INPUT_EN; /**< FAIL2 输入功能使能 */
    uint8_t FAIL3_INPUT_EN; /**< FAIL3 输入功能使能 */
    uint8_t FAIL_1CAP; /**< FAIL23事件发生时 将MCPWM0_CNT1值存入MCPWM0_FCNT */
    uint8_t FAIL2_Signal_Sel; /**< FAIL2
                                 信号选择，比较器0或GPIO或CLUOUT0或CLUOUT1 */
    uint8_t FAIL3_Signal_Sel; /**< FAIL3
                                 信号选择，比较器1或GPIO或CLUOUT2或CLUOUT3 */
    uint8_t FAIL2_Polarity; /**< FAIL2 信号极性设置，高有效或低有效 */
    uint8_t FAIL3_Polarity; /**< FAIL3 信号极性设置，高有效或低有效 */
    uint8_t HALT_PRT1; /**< MCU进入HALT状态, MCPWM(CH3CH4CH5)信号是否正常输出
                          1正常输出；0强制输出保护值 */

    uint8_t CH0P_default_output; /**< CH0P
                                    MOE为0时或发生FAIL事件时，默认电平输出 */
    uint8_t CH0N_default_output; /**< CH0N
                                    MOE为0时或发生FAIL事件时，默认电平输出 */
    uint8_t CH1P_default_output; /**< CH1P
                                    MOE为0时或发生FAIL事件时，默认电平输出 */
    uint8_t CH1N_default_output; /**< CH1N
                                    MOE为0时或发生FAIL事件时，默认电平输出 */
    uint8_t CH2P_default_output; /**< CH2P
                                    MOE为0时或发生FAIL事件时，默认电平输出 */
    uint8_t CH2N_default_output; /**< CH2N
                                    MOE为0时或发生FAIL事件时，默认电平输出 */
    uint8_t CH3P_default_output; /**< CH3P
                                    MOE为0时或发生FAIL事件时，默认电平输出 */
    uint8_t CH3N_default_output; /**< CH3N
                                    MOE为0时或发生FAIL事件时，默认电平输出 */
    uint8_t CH4P_default_output; /**< CH4P
                                    MOE为0时或发生FAIL事件时，默认电平输出 */
    uint8_t CH4N_default_output; /**< CH4N
                                    MOE为0时或发生FAIL事件时，默认电平输出 */
    uint8_t CH5P_default_output; /**< CH5P
                                    MOE为0时或发生FAIL事件时，默认电平输出 */
    uint8_t CH5N_default_output; /**< CH5N
                                    MOE为0时或发生FAIL事件时，默认电平输出 */

    uint8_t CH0N_FAIL_EN; /**< CH0N通道FAIL事件使能
                             1：MOE为0时或发生FAIL事件时，输出默认电平；0：输出不受影响
                           */
    uint8_t CH0P_FAIL_EN; /**< CH0P通道FAIL事件使能
                             1：MOE为0时或发生FAIL事件时，输出默认电平；0：输出不受影响
                           */
    uint8_t CH1N_FAIL_EN; /**< CH1N通道FAIL事件使能
                             1：MOE为0时或发生FAIL事件时，输出默认电平；0：输出不受影响
                           */
    uint8_t CH1P_FAIL_EN; /**< CH1P通道FAIL事件使能
                             1：MOE为0时或发生FAIL事件时，输出默认电平；0：输出不受影响
                           */
    uint8_t CH2N_FAIL_EN; /**< CH2N通道FAIL事件使能
                             1：MOE为0时或发生FAIL事件时，输出默认电平；0：输出不受影响
                           */
    uint8_t CH2P_FAIL_EN; /**< CH2P通道FAIL事件使能
                             1：MOE为0时或发生FAIL事件时，输出默认电平；0：输出不受影响
                           */
    uint8_t CH3N_FAIL_EN; /**< CH3N通道FAIL事件使能
                             1：MOE为0时或发生FAIL事件时，输出默认电平；0：输出不受影响
                           */
    uint8_t CH3P_FAIL_EN; /**< CH3P通道FAIL事件使能
                             1：MOE为0时或发生FAIL事件时，输出默认电平；0：输出不受影响
                           */
    uint8_t CH4N_FAIL_EN; /**< CH4N通道FAIL事件使能
                             1：MOE为0时或发生FAIL事件时，输出默认电平；0：输出不受影响
                           */
    uint8_t CH4P_FAIL_EN; /**< CH4P通道FAIL事件使能
                             1：MOE为0时或发生FAIL事件时，输出默认电平；0：输出不受影响
                           */
    uint8_t CH5N_FAIL_EN; /**< CH5N通道FAIL事件使能
                             1：MOE为0时或发生FAIL事件时，输出默认电平；0：输出不受影响
                           */
    uint8_t CH5P_FAIL_EN; /**< CH5P通道FAIL事件使能
                             1：MOE为0时或发生FAIL事件时，输出默认电平；0：输出不受影响
                           */

    uint8_t T0_Update0_INT_EN; /**< MCPWM0_CNT0 计数到-MCPWMTH
                                  (T0更新事件)中断使能 */
    uint8_t T1_Update0_INT_EN; /**< MCPWM0_CNT0 计数到0 (T1更新事件)中断使能 */

    uint8_t TMR0_Match0_INT_EN; /**< MCPWM0_CNT0 计数到 MCPWM0_TMR0
                                   产生的计数事件匹配事件中断使能 */
    uint8_t TMR1_Match0_INT_EN; /**< MCPWM0_CNT0 计数到 MCPWM0_TMR1
                                   产生的计数事件匹配事件中断使能 */
    uint8_t TMR2_Match0_INT_EN; /**< MCPWM0_CNT0 计数到 MCPWM0_TMR2
                                   产生的计数事件匹配事件中断使能 */
    uint8_t TMR3_Match0_INT_EN; /**< MCPWM0_CNT0 计数到 MCPWM0_TMR3
                                   产生的计数事件匹配事件中断使能 */

    uint8_t TH00_Match0_INT_EN; /**< MCPWM0_CNT0 计数到 MCPWM0_TH00
                                   产生的计数事件匹配事件中断使能 */
    uint8_t TH01_Match0_INT_EN; /**< MCPWM0_CNT0 计数到 MCPWM0_TH01
                                   产生的计数事件匹配事件中断使能 */
    uint8_t TH10_Match0_INT_EN; /**< MCPWM0_CNT0 计数到 MCPWM0_TH10
                                   产生的计数事件匹配事件中断使能 */
    uint8_t TH11_Match0_INT_EN; /**< MCPWM0_CNT0 计数到 MCPWM0_TH11
                                   产生的计数事件匹配事件中断使能 */
    uint8_t TH20_Match0_INT_EN; /**< MCPWM0_CNT0 计数到 MCPWM0_TH20
                                   产生的计数事件匹配事件中断使能 */
    uint8_t TH21_Match0_INT_EN; /**< MCPWM0_CNT0 计数到 MCPWM0_TH21
                                   产生的计数事件匹配事件中断使能 */

    uint8_t Update0_INT_EN; /**< MCPWM0_CNT0 计数器0更新中断使能 */

    uint8_t T0_Update1_INT_EN; /**< MCPWM0_CNT0 计数到-MCPWMTH
                                  (T0更新事件)中断使能 */
    uint8_t T1_Update1_INT_EN; /**< MCPWM0_CNT0 计数到0 (T1更新事件)中断使能 */

    uint8_t TMR0_Match1_INT_EN; /**< MCPWM0_CNT0 计数到 MCPWM0_TMR0
                                   产生的计数事件匹配事件中断使能 */
    uint8_t TMR1_Match1_INT_EN; /**< MCPWM0_CNT0 计数到 MCPWM0_TMR1
                                   产生的计数事件匹配事件中断使能 */
    uint8_t TMR2_Match1_INT_EN; /**< MCPWM0_CNT0 计数到 MCPWM0_TMR2
                                   产生的计数事件匹配事件中断使能 */
    uint8_t TMR3_Match1_INT_EN; /**< MCPWM0_CNT0 计数到 MCPWM0_TMR3
                                   产生的计数事件匹配事件中断使能 */

    uint8_t TH00_Match1_INT_EN; /**< MCPWM0_CNT0 计数到 MCPWM0_TH00
                                   产生的计数事件匹配事件中断使能 */
    uint8_t TH01_Match1_INT_EN; /**< MCPWM0_CNT0 计数到 MCPWM0_TH01
                                   产生的计数事件匹配事件中断使能 */
    uint8_t TH10_Match1_INT_EN; /**< MCPWM0_CNT0 计数到 MCPWM0_TH10
                                   产生的计数事件匹配事件中断使能 */
    uint8_t TH11_Match1_INT_EN; /**< MCPWM0_CNT0 计数到 MCPWM0_TH11
                                   产生的计数事件匹配事件中断使能 */
    uint8_t TH20_Match1_INT_EN; /**< MCPWM0_CNT0 计数到 MCPWM0_TH20
                                   产生的计数事件匹配事件中断使能 */
    uint8_t TH21_Match1_INT_EN; /**< MCPWM0_CNT0 计数到 MCPWM0_TH21
                                   产生的计数事件匹配事件中断使能 */

    uint8_t Update1_INT_EN; /**< MCPWM0_CNT0 计数器0更新中断使能 */

    uint8_t FAIL0_INT_EN; /* FAIL0事件中断使能 */
    uint8_t FAIL1_INT_EN; /* FAIL1事件中断使能 */
    uint8_t FAIL2_INT_EN; /* FAIL0事件中断使能 */
    uint8_t FAIL3_INT_EN; /* FAIL1事件中断使能 */

    uint8_t IO_CMP_FLT_CLKDIV; /**<  GPIO或CMP信号输入滤波时钟设置1-16 */

    uint8_t ZCS0_INT_EN; /**<  ZCS0事件中断使能 数字电源应用 */
    uint8_t ZCS1_INT_EN; /**<  ZCS1事件中断使能 数字电源应用 */

    uint8_t IO0_PPE; /**<  IO0推挽模式使能：1使能，0关闭 */
    uint8_t IO1_PPE; /**<  IO1推挽模式使能：1使能，0关闭 */
    uint8_t IO2_PPE; /**<  IO2推挽模式使能：1使能，0关闭 */
    uint8_t IO3_PPE; /**<  IO3推挽模式使能：1使能，0关闭 */
    uint8_t IO4_PPE; /**<  IO4推挽模式使能：1使能，0关闭 */
    uint8_t IO5_PPE; /**<  IO5推挽模式使能：1使能，0关闭 */

    uint8_t TR1_T1_RE1; /**< MCPWM_CNT1  计数到0 (T1)       事件 DMA请求1
                           使能：1使能，0关闭 */
    uint8_t TR1_T0_RE1; /**< MCPWM_CNT1  计数到-MCPWM_TH(T0)事件 DMA请求1
                           使能：1使能，0关闭 */
    uint8_t TR0_T1_RE1; /**< MCPWM_CNT0  计数到0 (T1)       事件 DMA请求1
                           使能：1使能，0关闭 */
    uint8_t TR0_T0_RE1; /**< MCPWM_CNT0  计数到-MCPWM_TH(T0)事件 DMA请求1
                           使能：1使能，0关闭 */
    uint8_t TMR3_RE1; /**< MCPWM_CNT01 计数到MCPWM_TMR3   事件 DMA请求1
                         使能：1使能，0关闭 */
    uint8_t TMR2_RE1; /**< MCPWM_CNT01 计数到MCPWM_TMR2   事件 DMA请求1
                         使能：1使能，0关闭 */
    uint8_t TMR1_RE1; /**< MCPWM_CNT01 计数到MCPWM_TMR1   事件 DMA请求1
                         使能：1使能，0关闭 */
    uint8_t TMR0_RE1; /**< MCPWM_CNT01 计数到MCPWM_TMR0   事件 DMA请求1
                         使能：1使能，0关闭 */

    uint8_t TR1_T1_RE0; /**< MCPWM_CNT1  计数到0 (T1)       事件 DMA请求0
                           使能：1使能，0关闭 */
    uint8_t TR1_T0_RE0; /**< MCPWM_CNT1  计数到-MCPWM_TH(T0)事件 DMA请求0
                           使能：1使能，0关闭 */
    uint8_t TR0_T1_RE0; /**< MCPWM_CNT0  计数到0 (T1)       事件 DMA请求0
                           使能：1使能，0关闭 */
    uint8_t TR0_T0_RE0; /**< MCPWM_CNT0  计数到-MCPWM_TH(T0)事件 DMA请求0
                           使能：1使能，0关闭 */
    uint8_t TMR3_RE0; /**< MCPWM_CNT01 计数到MCPWM_TMR3   事件 DMA请求0
                         使能：1使能，0关闭 */
    uint8_t TMR2_RE0; /**< MCPWM_CNT01 计数到MCPWM_TMR2   事件 DMA请求0
                         使能：1使能，0关闭 */
    uint8_t TMR1_RE0; /**< MCPWM_CNT01 计数到MCPWM_TMR1   事件 DMA请求0
                         使能：1使能，0关闭 */
    uint8_t TMR0_RE0; /**< MCPWM_CNT01 计数到MCPWM_TMR0   事件 DMA请求0
                         使能：1使能，0关闭 */

    uint16_t STT_HYST; /**<  状态切换延时，12位无符号数 */
    uint16_t ZCS_DELAY; /**<  ZCS状态停留时间，15位无符号数 数字电源应用 */

    uint32_t AUEN; /**<  自动更新使能 */
  } MCPWM_InitTypeDef;

/* MCPWM输出 对齐方式 */
#define MCPWM0_CENTRAL_PWM_MODE 0 /**<  中心对齐PWM模式 */
#define MCPWM0_EDGE_PWM_MODE 1    /**<  边沿对齐PWM模式 */

#define MCPWM0_HIGH_LEVEL 1 /**< 高电平 */
#define MCPWM0_LOW_LEVEL 0  /**< 高电平 */

#define MCPWM0_HIGH_LEVEL_ACTIVE 0 /**< 高电平有效 */
#define MCPWM0_LOW_LEVEL_ACTIVE 1  /**< 低电平有效 */

#define MCPWM0_FAIL_SEL_CMP 1 /**< Fail事件来源比较器 */
#define MCPWM0_FAIL_SEL_IO 0  /**< Fail事件来源比较器 */

/* MCPWM0_AUEN  MCPWM 自动更新使能寄存器 */
#define MCPWM0_TH00_AUPDATE BIT0 /**< MCPWM_TH00 自动加载使能 */
#define MCPWM0_TH01_AUPDATE BIT1 /**< MCPWM_TH01 自动加载使能 */
#define MCPWM0_TH10_AUPDATE BIT2 /**< MCPWM_TH10 自动加载使能 */
#define MCPWM0_TH11_AUPDATE BIT3 /**< MCPWM_TH11 自动加载使能 */
#define MCPWM0_TH20_AUPDATE BIT4 /**< MCPWM_TH20 自动加载使能 */
#define MCPWM0_TH21_AUPDATE BIT5 /**< MCPWM_TH21 自动加载使能 */
#define MCPWM0_TMR0_AUPDATE BIT8 /**< MCPWM_TMR0 自动加载使能 */
#define MCPWM0_TMR1_AUPDATE BIT9 /**< MCPWM_TMR1 自动加载使能 */
#define MCPWM0_TH0_AUPDATE BIT10 /**< MCPWM_TH0 自动加载使能  */
#define MCPWM0_CNT0_AUPDAT BIT11 /**< MCPWM_CNT0 自动加载使能 */

#define MCPWM0_TH30_AUPDATE BIT16    /**< MCPWM_TH00 自动加载使能 */
#define MCPWM0_TH31_AUPDATE BIT17    /**< MCPWM_TH01 自动加载使能 */
#define MCPWM0_TH40_AUPDATE BIT18    /**< MCPWM_TH10 自动加载使能 */
#define MCPWM0_TH41_AUPDATE BIT19    /**< MCPWM_TH11 自动加载使能 */
#define MCPWM0_TH50_AUPDATE BIT20    /**< MCPWM_TH20 自动加载使能 */
#define MCPWM0_TH51_AUPDATE BIT20    /**< MCPWM_TH21 自动加载使能 */
#define MCPWM0_TMR2_AUPDATE BIT24    /**< MCPWM_TMR0 自动加载使能 */
#define MCPWM0_TMR3_AUPDATE BIT25    /**< MCPWM_TMR1 自动加载使能 */
#define MCPWM0_TH1_AUPDATE BIT26     /**< MCPWM_TH0 自动加载使能  */
#define MCPWM0_CNT1_AUPDAT BIT27     /**< MCPWM_CNT0 自动加载使能 */
#define MCPWM0_ALL_AUPDAT 0xffffffff /**< 全部自动加载使能 */

#define MCPWM0CNT0_T0_IRQ_IF BIT0 /**< 计数器0计数值回到-MCPWM_TH中断标志位 \
                                   */
#define MCPWM0CNT0_T1_IRQ_IF BIT1 /**< 计数器0计数值回到0中断标志位 */
#define MCPWM0CNT0_TH00_IRQ_IF                                                \
  BIT2 /**< 计数器0计数值回到MCPWM_TH00中断标志位 */
#define MCPWM0CNT0_TH01_IRQ_IF                                                \
  BIT3 /**< 计数器0计数值回到MCPWM_TH01中断标志位 */
#define MCPWM0CNT0_TH10_IRQ_IF                                                \
  BIT4 /**< 计数器0计数值回到MCPWM_TH10中断标志位 */
#define MCPWM0CNT0_TH11_IRQ_IF                                                \
  BIT5 /**< 计数器0计数值回到MCPWM_TH11中断标志位 */
#define MCPWM0CNT0_TH20_IRQ_IF                                                \
  BIT6 /**< 计数器0计数值回到MCPWM_TH20中断标志位 */
#define MCPWM0CNT0_TH21_IRQ_IF                                                \
  BIT7 /**< 计数器0计数值回到MCPWM_TH21中断标志位 */

#define MCPWM0CNT0_TMR0_IRQ_IF                                                \
  BIT10 /**< 计数器0计数值回到MCPWM_TMR0中断标志位 */
#define MCPWM0CNT0_TMR1_IRQ_IF                                                \
  BIT11 /**< 计数器0计数值回到MCPWM_TMR1中断标志位 */
#define MCPWM0CNT0_TMR2_IRQ_IF                                                \
  BIT12 /**< 计数器0计数值回到MCPWM_TMR2中断标志位 */
#define MCPWM0CNT0_TMR3_IRQ_IF                                                \
  BIT13 /**< 计数器0计数值回到MCPWM_TMR3中断标志位 */
#define MCPWM0CNT0_UP_IRQ_IF BIT14 /**< 计数器0更新中断标志位 */

#define MCPWM0CNT1_T0_IRQ_IF BIT0 /**< 计数器0计数值回到-MCPWM_TH中断标志位 \
                                   */
#define MCPWM0CNT1_T1_IRQ_IF BIT1 /**< 计数器0计数值回到0中断标志位 */
#define MCPWM0CNT1_TH30_IRQ_IF                                                \
  BIT2 /**< 计数器0计数值回到MCPWM_TH00中断标志位 */
#define MCPWM0CNT1_TH31_IRQ_IF                                                \
  BIT3 /**< 计数器0计数值回到MCPWM_TH01中断标志位 */
#define MCPWM0CNT1_TH40_IRQ_IF                                                \
  BIT4 /**< 计数器0计数值回到MCPWM_TH10中断标志位 */
#define MCPWM0CNT1_TH41_IRQ_IF                                                \
  BIT5 /**< 计数器0计数值回到MCPWM_TH11中断标志位 */
#define MCPWM0CNT1_TH50_IRQ_IF                                                \
  BIT6 /**< 计数器0计数值回到MCPWM_TH20中断标志位 */
#define MCPWM0CNT1_TH51_IRQ_IF                                                \
  BIT7 /**< 计数器0计数值回到MCPWM_TH21中断标志位 */

#define MCPWM0CNT1_TMR2_IRQ_IF                                                \
  BIT12 /**< 计数器0计数值回到MCPWM_TMR2中断标志位 */
#define MCPWM0CNT1_TMR3_IRQ_IF                                                \
  BIT13 /**< 计数器0计数值回到MCPWM_TMR3中断标志位 */
#define MCPWM0CNT1_UP_IRQ_IF BIT14 /**< 计数器0更新中断标志位 */

#define MCPWM0_FAIL0_IRQ_IF BIT19 /**< MCPWMCH0_P和CH0N同时有效中断标志位 */
#define MCPWM0_FAIL1_IRQ_IF BIT20 /**< MCPWMCH0_P和CH0N同时有效中断标志位 */
#define MCPWM0_FAIL2_IRQ_IF BIT21 /**< MCPWMCH0_P和CH0N同时有效中断标志位 */
#define MCPWM0_FAIL3_IRQ_IF BIT22 /**< MCPWMCH0_P和CH0N同时有效中断标志位 */
#define MCPWM0_ZCS0_IRQ_IF BIT23 /**< MCPWMCH0_P和CH0N同时有效中断标志位 */
#define MCPWM0_ZCS1_IRQ_IF BIT24 /**< MCPWMCH0_P和CH0N同时有效中断标志位 */

  /**< 定义MCPWM定时器序号*/
  typedef enum
  {
    MCPWM0CNT0 = 0, /**< MCPWM0计数器0 */
    MCPWM0CNT1 = 1, /**< MCPWM0计数器1 */
  } MCPWM0CNTx;

  void MCPWM_Init (MCPWM_InitTypeDef *MCPWM_InitStruct);
  void MCPWM_StructInit (MCPWM_InitTypeDef *MCPWM_InitStruct);
  void PWMOutputs (FuncState t_state);
  void MCPWM_ClearIRQFlag (MCPWM0CNTx CNTx, uint32_t INT_flag);
  u16 MCPWM_GetIRQFlag (MCPWM0CNTx CNTx, uint32_t INT_flag);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif /*__CHANHOM_PWM_H */

/************************ (C) COPYRIGHT LINKO SEMICONDUCTOR *****END OF
 * FILE****/
