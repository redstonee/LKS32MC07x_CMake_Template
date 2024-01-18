/**
 * @file
 * @copyright (C)2015, LINKO SEMICONDUCTOR Co.ltd
 * @brief 文件名称： lks32mc07x_tim.h\n
 * 文件标识： 无 \n
 * 内容摘要： TIM驱动头文件 \n
 * 其它说明： 无 \n
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2023年2月22日 <td>1.0      <td>HungMG     <td>创建
 * </table>
 */
#ifndef __lks32mc07x_TIM_H
#define __lks32mc07x_TIM_H

/* Includes
 * ------------------------------------------------------------------*/
#include "lks32mc07x.h"

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

  typedef struct
  {
    __IO uint32_t CFG;  /**<定时器配置寄存器*/
    __IO uint32_t TH;   /**<定时器计数门限寄存器*/
    __IO uint32_t CNT;  /**<定时器计数值寄存器*/
    __IO uint32_t CMP0; /**<定时器比较/捕获寄存器 0*/
    __IO uint32_t CMP1; /**<定时器比较/捕获寄存器 1*/
    __IO uint32_t EVT;  /**<定时器外部事件选择寄存器*/
    __IO uint32_t FLT;  /**<定时器滤波控制寄存器*/
    __IO uint32_t IE;   /**<定时器中断使能寄存器*/
    __IO uint32_t IF;   /**<定时器中断标志寄存器*/
    __IO uint32_t IO;   /**<定时器IO控制寄存器*/
  } TIM_TimerTypeDef;

/**
 * TIMER0结构体基地址定义
 */
#define UTIMER0 ((TIM_TimerTypeDef *)TIMER0_BASE)
/**
 * TIMER1结构体基地址定义
 */
#define UTIMER1 ((TIM_TimerTypeDef *)TIMER1_BASE)
/**
 * TIMER2结构体基地址定义
 */
#define UTIMER2 ((TIM_TimerTypeDef *)TIMER2_BASE)
/**
 * TIMER3结构体基地址定义
 */
#define UTIMER3 ((TIM_TimerTypeDef *)TIMER3_BASE)

  /**
   * @brief 中断使能配置定义
   */
  typedef enum
  {
    Timer_IRQEna_None = 0,     /**< 关闭所有中断*/
    Timer_IRQEna_CH0 = BIT0,   /**< 通道 0 中断*/
    Timer_IRQEna_CH1 = BIT1,   /**< 通道 1 中断*/
    Timer_IRQEna_ZC = BIT2,    /**< 计数器过 0 中断*/
    Timer0_IRQEna_FAIL = BIT3, /**< 定时器0，FAIL事件中断*/

    Timer_IRQEna_CH0_RE = BIT8,    /**< 通道0比较/捕获DMA请求使能*/
    Timer_IRQEna_CH1_RE = BIT9,    /**< 通道1比较/捕获DMA请求使能*/
    Timer_IRQEna_ZC_RE = BIT10,    /**< 计数器过0 DMA请求使能*/
    Timer0_IRQEna_FAIL_RE = BIT11, /**< 定时器0，FAIL事件DMA请求使能*/

    Timer_IRQEna_All = 0xf /**< 开启所有中断*/
  } Timer_IRQEnaDef;

/*中断标志定义*/
#define TIMER_IF_CH0 BIT0  /**< Timer0 CH0中断，比较或捕获中断*/
#define TIMER_IF_CH1 BIT1  /**< Timer0 CH1中断，比较或捕获中断*/
#define TIMER_IF_ZERO BIT2 /**< Timer0 过零中断*/
#define TIMER_IF_FAIL BIT3 /**< Fail 事件中断标志*/

#define TIMER_CLK_DIV1 0x00   /**< Timer计数器频率1分频*/
#define TIMER_CLK_DIV2 0x01   /**< Timer计数器频率2分频*/
#define TIMER_CLK_DIV4 0x02   /**< Timer计数器频率4分频*/
#define TIMER_CLK_DIV8 0x03   /**< Timer计数器频率8分频*/
#define TIMER_CLK_DIV16 0x04  /**< Timer计数器频率16分频*/
#define TIMER_CLK_DIV32 0x05  /**< Timer计数器频率32分频*/
#define TIMER_CLK_DIV64 0x06  /**< Timer计数器频率64分频*/
#define TIMER_CLK_DIV128 0x07 /**< Timer计数器频率128分频*/

#define CAP_SRC_TCH0 0X00  /**< 捕获定时器对应通道0输入信号*/
#define CAP_SRC_TCH1 0X01  /**< 捕获定时器对应通道1输入信号*/
#define CAP_SRC_CLU0 0X02  /**< 捕获CLU0输出信号*/
#define CAP_SRC_CLU1 0X03  /**< 捕获CLU1输出信号*/
#define CAP_SRC_CLU2 0X04  /**< 捕获CLU2输出信号*/
#define CAP_SRC_CLU3 0X05  /**< 捕获CLU3输出信号*/
#define CAP_SRC_CMP0 0X06  /**< 捕获比较器0输出信号*/
#define CAP_SRC_CMP1 0X07  /**< 捕获比较器1输出信号*/
#define CAP_SRC_CMP2 0X08  /**< 捕获比较器2输出信号*/
#define CAP_SRC_CHXOR 0X09 /**< 捕获Timer通道0和1的异或信号*/

#define TIMER_POL_HIGH 0x01 /**< 比较模式下的输出高电平*/
#define TIMER_POL_LOW 0x00  /**< 比较模式下的输出低电平*/

#define TIMER_OPMode_CAP ((uint32_t)0x0000001) /**< 捕获模式*/
#define TIMER_OPMode_CMP ((uint32_t)0x0000000) /**< 比较模式*/

#define TIMER0_EVT_CH0 0x00  /**< TIMER0通道0*/
#define TIMER0_EVT_CH1 0x01  /**< TIMER0通道1*/
#define TIMER1_EVT_CH0 0x02  /**< TIMER1通道0*/
#define TIMER1_EVT_CH1 0x03  /**< TIMER1通道1*/
#define TIMER2_EVT_CH0 0x04  /**< TIMER2通道0*/
#define TIMER2_EVT_CH1 0x05  /**< TIMER2通道1*/
#define TIMER3_EVT_CH0 0x06  /**< TIMER3通道0*/
#define TIMER3_EVT_CH1 0x07  /**< TIMER3通道1*/
#define TIMER_EVT_CLU0 0x08  /**< CLU0 输出信号*/
#define TIMER_EVT_CLU1 0x09  /**< CLU1 输出信号*/
#define TIMER_EVT_CLU2 0x0A  /**< CLU2 输出信号*/
#define TIMER_EVT_CLU3 0x0B  /**< CLU3 输出信号*/
#define TIMER_EVT_TADC0 0x0C /**< MCPWM TADC[0]比较事件*/
#define TIMER_EVT_TADC1 0x0D /**< MCPWM TADC[1]比较事件*/
#define TIMER_EVT_TADC2 0x0E /**< MCPWM TADC[2]比较事件*/
#define TIMER_EVT_TADC3 0x0F /**< MCPWM TADC[3]比较事件*/

#define TIMER_CH0_IF BIT0  /**< Timer通道0比较/捕获中断标志*/
#define TIMER_CH1_IF BIT1  /**< Timer通道1比较/捕获中断标志*/
#define TIMER_ZC_IF BIT2   /**< Timer计数器过0中断标志*/
#define TIMER_FAIL_IF BIT3 /**< Timer Fail事件中断标志*/

  typedef struct
  {
    FuncState Timer_EN; /**< 定时器使能，ENABLE使能，DISABLE失能*/
    uint32_t Timer_CAP1_CLR_EN; /**< 当发生CAP1捕获事件时，清零 Timer
                                   计数器，高有效*/
    uint32_t Timer_CAP0_CLR_EN; /**< 当发生CAP0捕获事件时，清零 Timer
                                   计数器，高有效*/

    uint32_t
        Timer_ONE_TRIG; /**<
                           单次发送模式，此位需要在Timer比较模式下使用，且对应定时器使能需设置为0*/

    uint32_t
        Timer_CENTER;   /**<
                        中心计数模式使能,0:Timer向上从0计数至TH，然后回0，或Timer向下
                        从TH计数至0，然后回到TH，1:Timer向上从0计数至TH，然后向下计数至0*/
    uint32_t Timer_DIR; /**< 0:0->TH 递增计数，1：TH->递减计数*/
                        /**
                         * @brief 定时器分频 \n
                         * @see TIM_Clk_Div1 \n
                         * @see TIM_Clk_Div2 \n
                         * @see TIM_Clk_Div4 \n
                         * @see TIM_Clk_Div8 \n
                         * @see TIM_Clk_Div16 \n
                         * @see TIM_Clk_Div32 \n
                         * @see TIM_Clk_Div64 \n
                         * @see TIM_Clk_Div128
                         */
    uint32_t Timer_ClockDiv;
    uint32_t Timer_ETON;    /**< Timer计数器计数外部启动使能,0:
                               自动运行,1:外部事件触发计数*/
    uint32_t Timer_GATE_EN; /**< Timer暂停使能，0：不暂停
                              1:当外部信号为低时，Timer暂停计数，
                              外部信号根据TIMER1_EVT.EVT_SRC 进行选择*/
    uint32_t
        Timer_RL_EN;        /**<
                               Timer重装使能,0：禁用外部事件重装，1：使能外部事件重装*/
    uint32_t Timer_XCLK_EN; /**< Timer时钟源,0: 芯片内部时钟,1:外部时钟*/
                            /**
                             * @brief 定时器分频 \n
                             * @see CAP_SRC_TCH0 \n
                             * @see CAP_SRC_TCH1 \n
                             * @see CAP_SRC_CLU0 \n
                             * @see CAP_SRC_CLU1 \n
                             * @see CAP_SRC_CLU2 \n
                             * @see CAP_SRC_CLU3 \n
                             * @see CAP_SRC_CMP0 \n
                             * @see CAP_SRC_CMP1 \n
                             * @see CAP_SRC_CMP2 \n
                             * @see CAP_SRC_CHXOR
                             */
    uint32_t Timer_SRC1;
    uint32_t
        Timer_CH1Output; /**< Timer 通道1在比较模式下的输出极性控制，当计数器
                            CNT<CMP1时的输出值，0：低电平，1：高电平*/
    uint32_t Timer_CH1_WorkMode; /**< Timer 通道1的工作模式选择,0: 比较模式 ,1:
                                    捕获模式*/
    uint32_t
        Timer_CH1_FE_CAP_EN; /**< Timer通道1下升沿捕获事件使能,1:使能,0:关闭*/
    uint32_t
        Timer_CH1_RE_CAP_EN; /**< Timer通道1上升沿捕获事件使能,1:使能,0:关闭*/
                             /**
                              * @brief 定时器分频 \n
                              * @see CAP_SRC_TCH0 \n
                              * @see CAP_SRC_TCH1 \n
                              * @see CAP_SRC_CLU0 \n
                              * @see CAP_SRC_CLU1 \n
                              * @see CAP_SRC_CLU2 \n
                              * @see CAP_SRC_CLU3 \n
                              * @see CAP_SRC_CMP0 \n
                              * @see CAP_SRC_CMP1 \n
                              * @see CAP_SRC_CMP2 \n
                              * @see CAP_SRC_CHXOR
                              */
    uint32_t Timer_SRC0; /**< Timer 捕获模式通道0信号来源*/
    uint32_t
        Timer_CH0Output; /**< Timer 通道0在比较模式下的输出极性控制，当计数器
                            CNT<CMP1时的输出值，0：低电平，1：高电平*/
    uint32_t Timer_CH0_WorkMode; /**< Timer 通道0的工作模式选择,0: 比较模式 ,1:
                                    捕获模式*/
    uint32_t
        Timer_CH0_FE_CAP_EN; /**< Timer通道0下升沿捕获事件使能,1:使能,0:关闭*/
    uint32_t
        Timer_CH0_RE_CAP_EN; /**< Timer通道0上升沿捕获事件使能,1:使能,0:关闭*/

    uint32_t Timer_TH;   /**< Timer计数器计数门限*/
    uint32_t Timer_CNT;  /**< Timer计数器计数门限*/
    uint32_t Timer_CMP0; /**< 通道0比较捕获寄存器*/
    uint32_t Timer_CMP1; /**< 通道1比较捕获寄存器*/
    /**
     * @brief 定时器分频 \n
     * @see TIMER0_EVT_CH0 \n
     * @see TIMER0_EVT_CH1 \n
     * @see ......      \n
     * @see TIMER_EVT_TADC2 \n
     * @see TIMER_EVT_TADC3
     */
    uint32_t Timer_EVT; /**< Timer外部事件选择*/
    uint32_t
        Timer_FLT; /**<
                      通道0/1信号滤波宽度选择。取值范围0~255,滤波公式=Timer_FLT*8*定时器时钟*/
    /**
     * @brief 定时器中断使能 \n
     * @see Timer_IRQEna_CH0     \n
     * @see Timer_IRQEna_CH1     \n
     * @see Timer_IRQEna_ZC      \n
     * @see Timer0_IRQEna_FAIL   \n
     * @see Timer_IRQEna_CH0_RE  \n
     * @see Timer_IRQEna_CH1_RE  \n
     * @see Timer_IRQEna_ZC_RE   \n
     * @see Timer0_IRQEna_FAIL_RE
     */
    uint32_t Timer_IRQEna; /**< 中断使能*/

    uint32_t Timer0_UPDATE; /**< 软件更新，1：将 TH/CMP0/CMP1
                             的预装载值加载到影子寄存器 STH/SCMP0/SCMP1
                             之中，0：无作用*/
    uint32_t Timer0_SHADOW; /**< 0：软件写入TH/CMP0/CMP1
                             时直接更新对应的影子寄存器，1：启用影子寄存器，
                             软件写入 TH/CMP0/CMP1
                             时进仅仅更新预装载值，当Timer发生过零事件时才将预
                             装载值写入影子寄存器*/
    uint32_t
        Timer0_CH1_DEFAULT; /**< 定时器0发生Fail事件MOE清零后，CH1通道输出值*/
    uint32_t
        Timer0_CH0_DEFAULT; /**< 定时器0发生Fail事件MOE清零后，CH0通道输出值*/
    uint32_t
        Timer0_HALT_PRT; /**< MCU
                            进入HALT状态，Timer输出值选择。1:正常输出；0:输出
                            CH1_DEFAULT 和 CH0_DEFAULT。*/
    uint32_t
        Timer0_FAIL_SEL; /**<
                            FAIL信号选择，0：TIMER0_FAIL，来自GPIO，1：CLU0输出*/
    uint32_t Timer0_FAIL_POL; /**< FAIL信号极性,0：高电平FAIL,1：低电平FAIL*/
    uint32_t Timer0_FAIL_EN; /**< FAIL 信号使能,0：禁用 FAIL,1：使能 FAIL*/
  } TIM_TimerInitTypeDef;

  /*Timer初始化*/
  void TIM_TimerInit (TIM_TimerTypeDef *TIMERx, TIM_TimerInitTypeDef *TIM_InitStruct);
  void TIM_TimerStrutInit (TIM_TimerInitTypeDef *TIM_InitStruct);
  void TIM_TimerCmd (TIM_TimerTypeDef *TIMERx, FuncState state);
  void TIM_CMP0 (TIM_TimerTypeDef *TIMERx, uint32_t temp);
  void TIM_CMP1 (TIM_TimerTypeDef *TIMERx, uint32_t temp);
  u32 TIM_Timer_GetCMPT0 (TIM_TimerTypeDef *TIMERx);
  u32 TIM_Timer_GetCMPT1 (TIM_TimerTypeDef *TIMERx);
  void TIM_ClearIRQFlag (TIM_TimerTypeDef *TIMERx, uint32_t tempFlag);
  u16 TIM_GetIRQFlag (TIM_TimerTypeDef *UTIMERx, u32 TIMER_IF_x);
  u16 TIM_GetFlag (TIM_TimerTypeDef *UTIMERx, u32 TIMER_IF_x);
  uint32_t TIM_Timer_GetCount (TIM_TimerTypeDef *TIMERx);
  void UTIMER_Enable (TIM_TimerTypeDef *UTIMERx);
  void UTIMER_Disable (TIM_TimerTypeDef *UTIMERx);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif /*__lks32mc07x_TIM_H */

/************************ (C) COPYRIGHT LINKO SEMICONDUCTOR *****END OF
 * FILE****/
