/**
 * @file
 * @copyright (C)2015, LINKO SEMICONDUCTOR Co.ltd
 * @brief 文件名称： lks32mc07x_tim.c\n
 * 文件标识： 无 \n
 * 内容摘要： 定时器外设驱动程序 \n
 * 其它说明： 无 \n
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2023年2月22日 <td>1.0     <td>HungMG       <td>创建
 * </table>
 */
#include "lks32mc07x_tim.h"
#include "lks32mc07x_sys.h"

/**
 *@brief @b 函数名称:   void TIM_TimerInit(TIM_TimerTypeDef *TIMERx, TIM_TimerInitTypeDef *TIM_InitStruct)
 *@brief @b 功能描述:   定时器初始化函数
 *@see被引用内容：      SYS_ModuleClockCmd()
 *@param输入参数：      TIMERx：UTIMER0/UTIMER0/UTIMER0/UTIMER0 \n
                        TIM_TimerInitTypeDef  *TIM_TimerInitStruct
 *@param输出参数：      无
 *@return返 回 值：     无
 *@note其它说明：       无
 *@warning             无
 *@par 示例代码：
 *@code
                    事例1比较模式配置：
                        TIM_TimerInitTypeDef TIM_InitStruct;
                        TIM_TimerStrutInit(&TIM_InitStruct);                   // Timer结构体初始化
                        TIM_InitStruct.Timer_CH0_WorkMode = TIMER_OPMode_CMP; // 设置Timer CH0 为比较模式
                        TIM_InitStruct.Timer_CH0Output = 0;                   // 计数器回零时，比较模式输出极性控制
                        TIM_InitStruct.Timer_CH1_WorkMode = TIMER_OPMode_CMP; // 设置Timer CH1 为比较模式
                        TIM_InitStruct.Timer_CH1Output = 0;                   // 计数器回零时，比较模式输出极性控制
                        TIM_InitStruct.Timer_TH = 48000;    				  // 定时器计数门限初始值48000
                        TIM_InitStruct.Timer_CMP0 = 24000;  				  // 设置比较模式的CH0比较初始值24000
                        TIM_InitStruct.Timer_CMP1 = 24000;  				  // 设置比较模式的CH1比较初始值24000
                        TIM_InitStruct.Timer_ClockDiv = TIMER_CLK_DIV1;       // 设置Timer模块时钟2分频系数
                        TIM_InitStruct.Timer_IRQEna = Timer_IRQEna_CH0 | Timer_IRQEna_CH1 | Timer_IRQEna_ZC; // 开启Timer模块比较中断和过零中断
                        TIM_TimerInit(UTIMER0, &TIM_InitStruct);
                        TIM_TimerCmd(UTIMER0, ENABLE);                        //定时器2模块使能
                    事例2捕获模式配置：
                        TIM_TimerInitTypeDef TIM_InitStruct;
                        TIM_TimerStrutInit(&TIM_InitStruct);                   // Timer结构体初始化
                        TIM_InitStruct.Timer_SRC0 = CAP_SRC_TCH1;             // 定时器0通道0捕获定时器0通道1的输入信号
                        TIM_InitStruct.Timer_CH0_WorkMode = TIMER_OPMode_CAP; // 设置Timer CH0为捕获模式
                        TIM_InitStruct.Timer_CAP0_CLR_EN =ENABLE;             // 当发生CAP0捕获事件时，清零Timer计数器
                        TIM_InitStruct.Timer_CH0_RE_CAP_EN = ENABLE;          // 使能Timer通道0上升沿捕获
                        TIM_InitStruct.Timer_CH0_FE_CAP_EN = DISABLE;         // 关闭Timer通道0下降沿捕获

                        TIM_InitStruct.Timer_SRC1 = CAP_SRC_TCH1;             // 定时器0通道1捕获定时器0通道1的输入信号
                        TIM_InitStruct.Timer_CH1_WorkMode = TIMER_OPMode_CAP; // 设置Timer CH1为捕获模式
                        TIM_InitStruct.Timer_CAP1_CLR_EN = DISABLE;           // 当发生CAP1捕获事件时，清零Timer计数器
                        TIM_InitStruct.Timer_CH1_RE_CAP_EN = DISABLE;         // 使能Timer通道1上升沿捕获
                        TIM_InitStruct.Timer_CH1_FE_CAP_EN = ENABLE;          // 关闭Timer通道1下降沿捕获

                        TIM_InitStruct.Timer_TH = 96000000;    				  // 定时器计数门限初始值96000000
                        TIM_InitStruct.Timer_FLT = 0;  						  // 设置捕捉模式或编码器模式下对应通道的数字滤波值
                        TIM_InitStruct.Timer_ClockDiv = TIMER_CLK_DIV1;       // 设置Timer模块时钟2分频系数
                        TIM_InitStruct.Timer_IRQEna = Timer_IRQEna_ZC;        // 开启Timer模块过零中断
                        TIM_TimerInit(UTIMER3, &TIM_InitStruct);
                        TIM_TimerCmd(UTIMER3, ENABLE);                        // Timer3 模块使能
  @endcode
 *@par 修改日志: 去除定时器使能接口
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author      <th>Description
 * <tr><td>2023年2月22日 <td>1.0        <td>HungMG        <td>创建
 * </table>
 */
void TIM_TimerInit(TIM_TimerTypeDef *TIMERx, TIM_TimerInitTypeDef *TIM_InitStruct)
{
    if (TIMERx == UTIMER0)
    {
        SYS_ModuleClockCmd(SYS_Module_TIMER0, ENABLE);
    }
    else if (TIMERx == UTIMER1)
    {
        SYS_ModuleClockCmd(SYS_Module_TIMER1, ENABLE);
    }
    else if (TIMERx == UTIMER2)
    {
        SYS_ModuleClockCmd(SYS_Module_TIMER2, ENABLE);
    }
    else if (TIMERx == UTIMER3)
    {
        SYS_ModuleClockCmd(SYS_Module_TIMER3, ENABLE);
    }

    TIM_TimerCmd(TIMERx, TIM_InitStruct->Timer_EN);

    TIMERx->CFG = (u32)(TIM_InitStruct->Timer_CAP1_CLR_EN << 29) | (u32)(TIM_InitStruct->Timer_CAP0_CLR_EN << 28) | (u32)(TIM_InitStruct->Timer0_UPDATE << 27) | (u32)(TIM_InitStruct->Timer0_SHADOW << 26) | (u32)(TIM_InitStruct->Timer_ONE_TRIG << 25) | (u32)(TIM_InitStruct->Timer_CENTER << 24) | (u32)(TIM_InitStruct->Timer_DIR << 23) | (u32)(TIM_InitStruct->Timer_ClockDiv << 20) | (u32)(TIM_InitStruct->Timer_ETON << 19) | (u32)(TIM_InitStruct->Timer_GATE_EN << 18) | (u32)(TIM_InitStruct->Timer_RL_EN << 17) | (u32)(TIM_InitStruct->Timer_XCLK_EN << 16) | (u32)(TIM_InitStruct->Timer_SRC1 << 12) | (u32)(TIM_InitStruct->Timer_CH1Output << 11) | (u32)(TIM_InitStruct->Timer_CH1_WorkMode << 10) | (u32)(TIM_InitStruct->Timer_CH1_FE_CAP_EN << 9) | (u32)(TIM_InitStruct->Timer_CH1_RE_CAP_EN << 8) | (u32)(TIM_InitStruct->Timer_SRC0 << 4) | (u32)(TIM_InitStruct->Timer_CH0Output << 3) | (u32)(TIM_InitStruct->Timer_CH0_WorkMode << 2) | (u32)(TIM_InitStruct->Timer_CH0_FE_CAP_EN << 1) | (u32)(TIM_InitStruct->Timer_CH0_RE_CAP_EN);
    TIMERx->TH = TIM_InitStruct->Timer_TH;
    TIMERx->CMP0 = TIM_InitStruct->Timer_CMP0;
    TIMERx->CMP1 = TIM_InitStruct->Timer_CMP1;
    TIMERx->EVT = TIM_InitStruct->Timer_EVT;
    TIMERx->FLT = TIM_InitStruct->Timer_FLT;
    TIMERx->IE = TIM_InitStruct->Timer_IRQEna;

    TIMERx->IO = TIM_InitStruct->Timer0_CH1_DEFAULT << 9 | TIM_InitStruct->Timer0_CH0_DEFAULT << 8 | TIM_InitStruct->Timer0_HALT_PRT << 7 | TIM_InitStruct->Timer0_FAIL_SEL << 2 | TIM_InitStruct->Timer0_FAIL_POL << 1 | TIM_InitStruct->Timer0_FAIL_EN;
}

/**
 *@brief @b 函数名称:   void TIM_TimerStrutInit(TIM_TimerInitTypeDef *TIM_InitStruct)
 *@brief @b 功能描述:   定时器结构体初始化
 *@see被引用内容：      无
 *@param输入参数：      TIM_TimerInitTypeDef  *TIM_InitStruct
 *@param输出参数：      无
 *@return返 回 值：     无
 *@note其它说明：       无
 *@warning             无
 *@par 示例代码：
 *@code
                TIM_TimerInitTypeDef TIM_InitStruct;
          TIM_TimerStrutInit(&TIM_InitStruct);  // Timer结构体初始化
  @endcode
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author      <th>Description
 * <tr><td>2023年2月22日 <td>1.0        <td>HungMG        <td>创建
 * </table>
 */
void TIM_TimerStrutInit(TIM_TimerInitTypeDef *TIM_InitStruct)
{
    TIM_InitStruct->Timer_CAP1_CLR_EN = DISABLE;
    TIM_InitStruct->Timer_CAP0_CLR_EN = DISABLE;

    TIM_InitStruct->Timer_ONE_TRIG = DISABLE;

    TIM_InitStruct->Timer_CENTER = 0;

    TIM_InitStruct->Timer_DIR = 0;

    TIM_InitStruct->Timer_ClockDiv = TIMER_CLK_DIV1;
    TIM_InitStruct->Timer_ETON = 0;
    TIM_InitStruct->Timer_GATE_EN = 0;
    TIM_InitStruct->Timer_RL_EN = 0;
    TIM_InitStruct->Timer_XCLK_EN = 0;

    TIM_InitStruct->Timer_SRC1 = 0;
    TIM_InitStruct->Timer_CH1Output = 0;
    TIM_InitStruct->Timer_CH1_WorkMode = 0;
    TIM_InitStruct->Timer_CH1_FE_CAP_EN = 0;
    TIM_InitStruct->Timer_CH1_RE_CAP_EN = 0;

    TIM_InitStruct->Timer_SRC0 = 0;
    TIM_InitStruct->Timer_CH0Output = 0;
    TIM_InitStruct->Timer_CH0_WorkMode = 0;
    TIM_InitStruct->Timer_CH0_FE_CAP_EN = 0;
    TIM_InitStruct->Timer_CH0_RE_CAP_EN = 0;

    TIM_InitStruct->Timer_TH = 0;
    TIM_InitStruct->Timer_CNT = 0;
    TIM_InitStruct->Timer_CMP0 = 0;
    TIM_InitStruct->Timer_CMP1 = 0;

    TIM_InitStruct->Timer_EVT = 0;
    TIM_InitStruct->Timer_FLT = 0;

    TIM_InitStruct->Timer_IRQEna = 0;

    TIM_InitStruct->Timer0_UPDATE = 0;
    TIM_InitStruct->Timer0_SHADOW = 0;

    TIM_InitStruct->Timer0_CH0_DEFAULT = 0;
    TIM_InitStruct->Timer0_CH1_DEFAULT = 0;
    TIM_InitStruct->Timer0_HALT_PRT = 0;
    TIM_InitStruct->Timer0_FAIL_SEL = 0;
    TIM_InitStruct->Timer0_FAIL_POL = 0;
    TIM_InitStruct->Timer0_FAIL_EN = 0;
}

/**
 *@brief @b 函数名称:  void TIM_TimerCmd(TIM_TimerTypeDef *TIMERx, FuncState state)
 *@brief @b 功能描述:   定时器TIMERx使能和停止
 *@see被引用内容：      无
 *@param输入参数：      TIMERx：UTIMER0/UTIMER0/UTIMER0/UTIMER0 \n
                        FuncState state：使能与失能
 *@param输出参数：      无
 *@return返 回 值：     无
 *@note其它说明：       无
 *@warning             无
 *@par 示例代码：
 *@code
                TIM_TimerCmd(UTIMER0, ENABLE); // Timer0模块使能
  @endcode
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author      <th>Description
 * <tr><td>2023年2月22日 <td>1.0       <td>HungMG         <td>创建
 * </table>
 */
void TIM_TimerCmd(TIM_TimerTypeDef *TIMERx, FuncState state)
{
    if (state != DISABLE)
    {
        TIMERx->CFG |= BIT31;
    }
    else
    {
        TIMERx->CFG &= ~BIT31;
    }
}

/**
 *@brief @b 函数名称:   void TIM_CMP0(TIM_TimerTypeDef *TIMERx, uint32_t temp)
 *@brief @b 功能描述:   写入定时器通道0比较值
 *@see被引用内容：      无
 *@param输入参数：      TIMERx：UTIMER0/UTIMER0/UTIMER0/UTIMER0 \n
 *                     temp：比较数值
 *@param输出参数：      无
 *@return返 回 值：     无
 *@note其它说明：       无
 *@warning              无
 *@par 示例代码：
 *@code
                    TIM_CMP0(UTIMER0，2000); //设定定时器0通道0比较值为2000
  @endcode
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author      <th>Description
 * <tr><td>2023年2月22日 <td>1.0        <td>HungMG        <td>创建
 * </table>
 */
void TIM_CMP0(TIM_TimerTypeDef *TIMERx, uint32_t temp)
{
    TIMERx->CMP0 = temp;
}

/**
 *@brief @b 函数名称:   void TIM_CMP1(TIM_TimerTypeDef *TIMERx, uint32_t temp)
 *@brief @b 功能描述:   写入定时器通道1比较值
 *@see被引用内容：      无
 *@param输入参数：      TIMERx：UTIMER0/UTIMER0/UTIMER0/UTIMER0 \n
 *                     temp：比较数值
 *@param输出参数：      无
 *@return返 回 值：     无
 *@note其它说明：       无
 *@warning              无
 *@par 示例代码：
 *@code
                    TIM_CMP1(UTIMER0 ，2000); //设定定时器0通道1比较值为2000
  @endcode
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author      <th>Description
 * <tr><td>2023年2月22日 <td>1.0        <td>HungMG        <td>创建
 * </table>
 */
void TIM_CMP1(TIM_TimerTypeDef *TIMERx, uint32_t temp)
{

    TIMERx->CMP1 = temp;
}

/**
 *@brief @b 函数名称:   u32 TIM_Timer_GetCMPT0(TIM_TimerTypeDef *TIMERx)
 *@brief @b 功能描述:   获取定时器通道0捕获值
 *@see被引用内容：       无
 *@param输入参数：      TIMERx：UTIMER0/UTIMER0/UTIMER0/UTIMER0
 *@param输出参数：      无
 *@return返 回 值：     定时器通道0捕获值
 *@note其它说明：       当定时器发生捕获事件时，将捕获时刻的cnt值存储到该寄存器中
 *@warning              无
 *@par 示例代码：
 *@code
                    uint32_t TIMER0_CAPValue = 0;
                    TIMER0_CAPValue = TIM_Timer_GetCMPT0(UTIMER0); //获取定时器0捕获值
  @endcode
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author      <th>Description
 * <tr><td>2023年2月22日 <td>1.0        <td>HungMG        <td>创建
 * </table>
 */
u32 TIM_Timer_GetCMPT0(TIM_TimerTypeDef *TIMERx)
{
    return TIMERx->CMP0;
}

/**
 *@brief @b 函数名称:   u32 TIM_Timer_GetCMPT1(TIM_TimerTypeDef *TIMERx)
 *@brief @b 功能描述:   获取定时器通道1捕获值
 *@see被引用内容：      无
 *@param输入参数：      TIMERx：UTIMER0/UTIMER0/UTIMER0/UTIMER0
 *@param输出参数：      无
 *@return返 回 值：     定时器通道1捕获值
 *@note其它说明：       当定时器发生捕获事件时，将捕获时刻的cnt值存储到该寄存器中
 *@warning              无
 *@par 示例代码：
 *@code
                    uint32_t TIMER0_CAPValue = 0;
                    TIMER0_CAPValue = TIM_Timer_GetCMPT1(UTIMER0); //获取定时器0捕获值
  @endcode
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author      <th>Description
 * <tr><td>2023年2月22日 <td>1.0        <td>HungMG        <td>创建
 * </table>
 */
u32 TIM_Timer_GetCMPT1(TIM_TimerTypeDef *TIMERx)
{
    return TIMERx->CMP1;
}

/**
 *@brief @b 函数名称:   void TIM_ClearIRQFlag(TIM_TimerTypeDef *TIMERx ,uint32_t tempFlag)
 *@brief @b 功能描述:   清除TIM中断标志
 *@see被引用内容：      无
 *@param输入参数：      TIMERx：UTIMER0/UTIMER0/UTIMER0/UTIMER0 \n
                        timer_if：
 * <table>              <tr><th>Timer_IRQEna_CH0_RE    <td>通道0比较/捕获DMA请求使能
                        <tr><th>Timer_IRQEna_CH1_RE    <td>通道1比较/捕获DMA请求使能
                        <tr><th>Timer_IRQEna_ZC_RE     <td>计数器过0 DMA请求使能
                        <tr><th>Timer0_IRQEna_FAIL_RE  <td>定时器0，FAIL事件DMA请求使能
                        <tr><th>Timer_IRQEna_CH1       <td>Timer CH1中断，比较或捕获中断
                        <tr><th>Timer_IRQEna_CH0       <td>Timer CH0中断，比较或捕获中断
                        <tr><th>Timer_IRQEna_ZC        <td>Timer 过零中断
 * </table>
 *@param输出参数：      无
 *@return返 回 值：     无
 *@note其它说明：       无
 *@warning             无
 *@par 示例代码：
 *@code
                     if(TIM_GetIRQFlag(UTIMER0,Timer_IRQEna_CH0)) //判断UTimer0的CH0是否发生比较中断
                {
                    TIM_ClearIRQFlag(UTIMER0,Timer_IRQEna_CH0); //清除UTimer0通道0比较中断标志位
                }
  @endcode
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author      <th>Description
 * <tr><td>2023年2月22日 <td>1.0        <td>HungMG        <td>创建
 * </table>
 */
void TIM_ClearIRQFlag(TIM_TimerTypeDef *TIMERx, uint32_t tempFlag)
{
    TIMERx->IF = tempFlag;
}

/**
 *@brief @b 函数名称:   u16 TIM_GetIRQFlag(TIM_TimerTypeDef *UTIMERx, u32 TIMER_IF_x)
 *@brief @b 功能描述:   获取TIM中断标志
 *@see被引用内容：      无
 *@param输入参数：      TIMERx：UTIMER0/UTIMER0/UTIMER0/UTIMER0 \n
                        TIMER_IF_x：
 * <table>              <tr><th>TIMER_IF_CH1   <td>Timer CH1中断，比较或捕获中断
                        <tr><th>TIMER_IF_CH0   <td>Timer CH0中断，比较或捕获中断
                        <tr><th>TIMER_IF_ZERO  <td>Timer 过零中断
 * </table>
 *@param输出参数：      无
 *@return返 回 值：     0或1，对应中断标志置位返回1，未置位返回0
 *@note其它说明：       无
 *@warning             只有对应中断使能后，改为才能读取，如果对应中断未使能，读取结果一直为0
 *@par 示例代码：
 *@code
                     if(TIM_GetIRQFlag(UTIMER0,TIMER_IF_CH0)) //判断UTimer0的CH0是否发生比较中断
                {
                }
  @endcode
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author      <th>Description
 * <tr><td>2023年2月22日 <td>1.0        <td>HungMG        <td>创建
 * </table>
 */
u16 TIM_GetIRQFlag(TIM_TimerTypeDef *UTIMERx, u32 TIMER_IF_x)
{
    if (UTIMERx->IF & UTIMERx->IE & TIMER_IF_x)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/**
 *@brief @b 函数名称:   u16 TIM_GetFlag(TIM_TimerTypeDef *UTIMERx, u32 TIMER_IF_x)
 *@brief @b 功能描述:   获取TIM中断标志
 *@see被引用内容：      无
 *@param输入参数：      TIMERx：UTIMER0/UTIMER0/UTIMER0/UTIMER0 \n
                        TIMER_IF_x：
 * <table>              <tr><th>TIMER_IF_CH1   <td>Timer CH1中断，比较或捕获中断
                        <tr><th>TIMER_IF_CH0   <td>Timer CH0中断，比较或捕获中断
                        <tr><th>TIMER_IF_ZERO  <td>Timer 过零中断
 * </table>
 *@param输出参数：      无
 *@return返 回 值：     0或1，对应中断标志置位返回1，未置位返回0
 *@note其它说明：       无
 *@warning             不需要对应中断使能后，就可以读取对应中断标志位
 *@par 示例代码：
 *@code
                     if(TIM_GetFlag(UTIMER0,TIMER_IF_CH0)) //判断UTimer0的CH0是否发生比较中断
                {
                }
  @endcode
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author      <th>Description
 * <tr><td>2023年2月22日 <td>1.0        <td>HungMG        <td>创建
 * </table>
 */
u16 TIM_GetFlag(TIM_TimerTypeDef *UTIMERx, u32 TIMER_IF_x)
{
    if (UTIMERx->IF & TIMER_IF_x)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/**
 *@brief @b 函数名称:   uint32_t TIM_Timer_GetCount(TIM_TimerTypeDef *TIMERx)
 *@brief @b 功能描述:   获取Timer计数值
 *@see被引用内容：      无
 *@param输入参数：      TIMERx：UTIMER0/UTIMER0/UTIMER0/UTIMER0
 *@param输出参数：      无
 *@return返 回 值：     无
 *@note其它说明：       无
 *@warning             无
 *@par 示例代码：
 *@code
                    uint32_t TIMER0_Value = 0;
                    TIMER0_Value = TIM_Timer_GetCount(UTIMER0); //获取定时器0计数值
  @endcode
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author      <th>Description
 * <tr><td>2023年2月22日 <td>1.0        <td>HungMG        <td>创建
 * </table>
 */
uint32_t TIM_Timer_GetCount(TIM_TimerTypeDef *TIMERx)
{
    return TIMERx->CNT;
}

/**
 *@brief @b 函数名称:   void TIM_Enable(TIM_TimerTypeDef *UTIMERx)
 *@brief @b 功能描述:   定时器时钟使能函数
 *@see被引用内容：      无
 *@param输入参数：      TIMERx：UTIMER0/UTIMER0/UTIMER0/UTIMER0
 *@param输出参数：      无
 *@return返 回 值：     无
 *@note其它说明：       无
 *@warning             无
 *@par 示例代码：
 *@code
                   TIM_Enable(UTIMER0); //定时器0时钟使能
  @endcode
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author      <th>Description
 * <tr><td>2023年2月22日 <td>1.0        <td>HungMG        <td>创建
 * </table>
 */
void TIM_Enable(TIM_TimerTypeDef *UTIMERx)
{
    if (UTIMERx == UTIMER0)
    {
        SYS_ModuleClockCmd(SYS_Module_TIMER0, ENABLE);
    }
    else if (UTIMERx == UTIMER1)
    {
        SYS_ModuleClockCmd(SYS_Module_TIMER1, ENABLE);
    }
    else if (UTIMERx == UTIMER2)
    {
        SYS_ModuleClockCmd(SYS_Module_TIMER2, ENABLE);
    }
    else if (UTIMERx == UTIMER3)
    {
        SYS_ModuleClockCmd(SYS_Module_TIMER3, ENABLE);
    }
}
/**
 *@brief @b 函数名称:   void TIM_Disable(TIM_TimerTypeDef *UTIMERx)
 *@brief @b 功能描述:   定时器时钟失能函数
 *@see被引用内容：      无
 *@param输入参数：      TIMERx：UTIMER0/UTIMER0/UTIMER0/UTIMER0
 *@param输出参数：      无
 *@return返 回 值：     无
 *@note其它说明：       无
 *@warning             无
 *@par 示例代码：
 *@code
                   TIM_Disable(UTIMER0); //定时器0时钟失能
  @endcode
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author      <th>Description
 * <tr><td>2023年2月22日 <td>1.0        <td>HungMG        <td>创建
 * </table>
 */
void TIM_Disable(TIM_TimerTypeDef *UTIMERx)
{
    if (UTIMERx == UTIMER0)
    {
        SYS_ModuleClockCmd(SYS_Module_TIMER0, DISABLE);
    }
    else if (UTIMERx == UTIMER1)
    {
        SYS_ModuleClockCmd(SYS_Module_TIMER1, DISABLE);
    }
    else if (UTIMERx == UTIMER2)
    {
        SYS_ModuleClockCmd(SYS_Module_TIMER2, DISABLE);
    }
    else if (UTIMERx == UTIMER3)
    {
        SYS_ModuleClockCmd(SYS_Module_TIMER3, DISABLE);
    }
}

/************************ (C) COPYRIGHT LINKO SEMICONDUCTOR *****END OF FILE****/
