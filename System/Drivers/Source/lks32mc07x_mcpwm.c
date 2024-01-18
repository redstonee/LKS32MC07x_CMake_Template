/**
 * @file
 * @copyright (C)2015, LINKO SEMICONDUCTOR Co.ltd
 * @brief 文件名称： lks32mc07x_mcpwm.c\n
 * 文件标识： 无 \n
 * 内容摘要： MCPWM外设驱动程序 \n
 * 其它说明： 无 \n
 *@par 修改日志:
 * <table>
 * <tr><th>Date	       <th>Version   <th>Author  <th>Description
 * <tr><td>2023年3月06日 <td>1.0     <td>Zhujie     <td>创建
 * </table>
 */
#include "lks32mc07x_MCPWM.h"
#include "lks32mc07x.h"
#include "lks32mc07x_sys.h"
#include "string.h"

/**
 *@brief @b 函数名称:   void MCPWM_StructInit(MCPWM_InitTypeDef* MCPWM_InitStruct)
 *@brief @b 功能描述:   MCPWM结构体初始化
 *@see被引用内容：       无
 *@param输入参数：       MCPWM_InitTypeDef *MCPWM_InitStruct
 *@param输出参数：      无
 *@return返 回 值：     无
 *@note其它说明：       无
 *@warning             无
 *@par 示例代码：
 *@code
			MCPWM_InitTypeDef MCPWM_InitStructure;
			MCPWM_StructInit(&MCPWM_InitStructure);//初始化MCPWM相关结构体
  @endcode
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author      <th>Description
 * <tr><td>2019年05月21日 <td>1.0     <td>Howlet      <td>创建
 * </table>
 */
void MCPWM_StructInit(MCPWM_InitTypeDef *MCPWM_InitStruct)
{
	memset(MCPWM_InitStruct, 0, sizeof(MCPWM_InitTypeDef));
}

/**
 *@brief @b 函数名称:   void MCPWM_Init(MCPWM_InitTypeDef *MCPWM_InitStruct)
 *@brief @b 功能描述:   MCPWM初始化函数
 *@see被引用内容：      SYS_ModuleClockCmd()
 *@param输入参数：      MCPWM_InitTypeDef *MCPWM_InitStruct
 *@param输出参数：      无
 *@return返 回 值：     无
 *@note其它说明：       无
 *@warning              无
 *@par 示例代码：
 *@code
			MCPWM_InitTypeDef MCPWM_InitStructure;
			MCPWM_StructInit(&MCPWM_InitStructure);//初始化MCPWM相关结构体
			MCPWM_InitStructure.MCLK_EN = ENABLE;
			MCPWM_InitStructure.CLK_DIV = 0;
			MCPWM_InitStructure.CMP_FLT_CLKDIV = 12;
			MCPWM_InitStructure.BASE_CNT0_EN = ENABLE;
			MCPWM_InitStructure.TH0 = PWM_PERIOD0;
			MCPWM_InitStructure.TH00 = -(PWM_PERIOD0 >> 2);
						MCPWM_InitStructure.TH01 = (PWM_PERIOD0 >> 2);
						MCPWM_InitStructure.TH10 = -(PWM_PERIOD0 >> 2);
						MCPWM_InitStructure.TH11 = (PWM_PERIOD0 >> 2);
						MCPWM_InitStructure.TH20 = -(PWM_PERIOD0 >> 2);
						MCPWM_InitStructure.TH21 = (PWM_PERIOD0 >> 2);

						MCPWM_InitStructure.MCPWM_WorkModeCH0 = MCPWM0_CENTRAL_PWM_MODE;
						MCPWM_InitStructure.MCPWM_WorkModeCH1 = MCPWM0_CENTRAL_PWM_MODE;
						MCPWM_InitStructure.MCPWM_WorkModeCH2 = MCPWM0_CENTRAL_PWM_MODE;
						MCPWM_InitStructure.DeadTimeCH012N = DEADTIME;
						MCPWM_InitStructure.DeadTimeCH012P = DEADTIME;
						MCPWM_InitStructure.CMP_CTRL_CNT0  = DISABLE ;
						MCPWM_InitStructure.EVT_CNT0_EN    = DISABLE ;
						MCPWM_InitStructure.EVT0           = DISABLE ;

						MCPWM_InitStructure.TR0_UP_INTV     = DISABLE;
						MCPWM_InitStructure.TR0_T0_UpdateEN = ENABLE ;
						MCPWM_InitStructure.TR0_T1_UpdateEN = DISABLE ;
						MCPWM_InitStructure.TR0_AEC         = DISABLE;

						MCPWM_InitStructure.T0_Update0_INT_EN = DISABLE;
						MCPWM_InitStructure.T1_Update0_INT_EN = ENABLE ;
						MCPWM_InitStructure.Update1_INT_EN = ENABLE;
			MCPWM_InitStructure.CH0N_Polarity_INV = DISABLE;
						MCPWM_InitStructure.CH0P_Polarity_INV = DISABLE;
						MCPWM_InitStructure.CH1N_Polarity_INV = DISABLE;
						MCPWM_InitStructure.CH1P_Polarity_INV = DISABLE;
						MCPWM_InitStructure.CH2N_Polarity_INV = DISABLE;
						MCPWM_InitStructure.CH2P_Polarity_INV = DISABLE;

						MCPWM_InitStructure.Switch_CH0N_CH0P =  DISABLE;
						MCPWM_InitStructure.Switch_CH1N_CH1P =  DISABLE;
						MCPWM_InitStructure.Switch_CH2N_CH2P =  DISABLE;
						MCPWM_InitStructure.CH0P_default_output = MCPWM0_LOW_LEVEL;
						MCPWM_InitStructure.CH0N_default_output = MCPWM0_LOW_LEVEL;
						MCPWM_InitStructure.CH1P_default_output = MCPWM0_LOW_LEVEL;
						MCPWM_InitStructure.CH1N_default_output = MCPWM0_LOW_LEVEL;
						MCPWM_InitStructure.CH2P_default_output = MCPWM0_LOW_LEVEL;
						MCPWM_InitStructure.CH2N_default_output = MCPWM0_LOW_LEVEL;
			MCPWM_Init(&MCPWM_InitStructure);

  @endcode
 *@par 修改日志:
 * <table>
 * <tr><th>Date	          <th>Version  <th>Author      <th>Description
 * <tr><td>2023年03月06日 <td>1.0      <td>Zhujie      <td>创建
 * </table>
 */
void MCPWM_Init(MCPWM_InitTypeDef *MCPWM_InitStruct)
{
	SYS_ModuleClockCmd(SYS_Module_MCPWM0, ENABLE); // MCPWM时钟使能

	MCPWM0_PRT = 0x0000DEAD; /*enter password to unlock write protection */

	MCPWM0_TCLK = MCPWM_InitStruct->CLK_DIV | (MCPWM_InitStruct->MCLK_EN << 2) | (MCPWM_InitStruct->ZCS_EN << 3) | (MCPWM_InitStruct->TMR2_TB << 4) | (MCPWM_InitStruct->TMR3_TB << 5) | (MCPWM_InitStruct->BASE_CNT0_EN << 6) | (MCPWM_InitStruct->BASE_CNT1_EN << 7) | (MCPWM_InitStruct->EVT_CNT0_EN << 8) | (MCPWM_InitStruct->EVT_CNT1_EN << 9) | (MCPWM_InitStruct->CMP_CTRL_CNT0 << 10) | (MCPWM_InitStruct->CMP_CTRL_CNT1 << 11);

	MCPWM0_TMR0 = MCPWM_InitStruct->TMR0;
	MCPWM0_TMR1 = MCPWM_InitStruct->TMR1;
	MCPWM0_TMR2 = MCPWM_InitStruct->TMR2;
	MCPWM0_TMR3 = MCPWM_InitStruct->TMR3;

	MCPWM0_TH0 = MCPWM_InitStruct->TH0;
	MCPWM0_TH1 = MCPWM_InitStruct->TH1;

	MCPWM0_SDCFG = MCPWM_InitStruct->TR0_UP_INTV | (MCPWM_InitStruct->TR0_T0_UpdateEN << 4) | (MCPWM_InitStruct->TR0_T1_UpdateEN << 5) | (MCPWM_InitStruct->TR0_AEC << 6) | (MCPWM_InitStruct->TR1_UP_INTV << 8) | (MCPWM_InitStruct->TR1_T0_UpdateEN << 12) | (MCPWM_InitStruct->TR1_T1_UpdateEN << 13) | (MCPWM_InitStruct->TR1_AEC << 14);

	MCPWM0_DTH00 = MCPWM_InitStruct->DeadTimeCH012N;
	MCPWM0_DTH01 = MCPWM_InitStruct->DeadTimeCH012P;
	MCPWM0_DTH10 = MCPWM_InitStruct->DeadTimeCH345N;
	MCPWM0_DTH11 = MCPWM_InitStruct->DeadTimeCH345P;

	MCPWM0_EIF = 0xffff;
	MCPWM0_IE0 = MCPWM_InitStruct->T0_Update0_INT_EN | (MCPWM_InitStruct->T1_Update0_INT_EN << 1) | (MCPWM_InitStruct->TH00_Match0_INT_EN << 2) | (MCPWM_InitStruct->TH01_Match0_INT_EN << 3) | (MCPWM_InitStruct->TH10_Match0_INT_EN << 4) | (MCPWM_InitStruct->TH11_Match0_INT_EN << 5) | (MCPWM_InitStruct->TH20_Match0_INT_EN << 6) | (MCPWM_InitStruct->TH21_Match0_INT_EN << 7) | (MCPWM_InitStruct->TMR0_Match0_INT_EN << 10) | (MCPWM_InitStruct->TMR1_Match0_INT_EN << 11) | (MCPWM_InitStruct->TMR2_Match0_INT_EN << 12) | (MCPWM_InitStruct->TMR3_Match0_INT_EN << 13) | (MCPWM_InitStruct->Update0_INT_EN << 14);

	MCPWM0_IE1 = MCPWM_InitStruct->T0_Update1_INT_EN | (MCPWM_InitStruct->T1_Update1_INT_EN << 1) | (MCPWM_InitStruct->TH00_Match1_INT_EN << 2) | (MCPWM_InitStruct->TH01_Match1_INT_EN << 3) | (MCPWM_InitStruct->TH10_Match1_INT_EN << 4) | (MCPWM_InitStruct->TH11_Match1_INT_EN << 5) | (MCPWM_InitStruct->TH20_Match1_INT_EN << 6) | (MCPWM_InitStruct->TH21_Match1_INT_EN << 7) | (MCPWM_InitStruct->TMR0_Match1_INT_EN << 10) | (MCPWM_InitStruct->TMR1_Match1_INT_EN << 11) | (MCPWM_InitStruct->TMR2_Match1_INT_EN << 12) | (MCPWM_InitStruct->TMR3_Match1_INT_EN << 13) | (MCPWM_InitStruct->Update1_INT_EN << 14);

	MCPWM0_EIE = (MCPWM_InitStruct->FAIL0_INT_EN << 4) | (MCPWM_InitStruct->FAIL1_INT_EN << 5) | (MCPWM_InitStruct->FAIL2_INT_EN << 6) | (MCPWM_InitStruct->FAIL3_INT_EN << 7) | (MCPWM_InitStruct->ZCS0_INT_EN << 8) | (MCPWM_InitStruct->ZCS1_INT_EN << 9);

	MCPWM0_UPDATE = 0xffff; /* write whatever value to trigger update */

	MCPWM0_EVT0 = MCPWM_InitStruct->EVT0;

	MCPWM0_EVT1 = MCPWM_InitStruct->EVT1;

	MCPWM0_FLT = MCPWM_InitStruct->IO_CMP_FLT_CLKDIV;

	MCPWM0_RE = MCPWM_InitStruct->TMR0_RE0 | (MCPWM_InitStruct->TMR1_RE0 << 1) | (MCPWM_InitStruct->TMR2_RE0 << 2) | (MCPWM_InitStruct->TMR3_RE0 << 3) | (MCPWM_InitStruct->TR0_T0_RE0 << 4) | (MCPWM_InitStruct->TR0_T1_RE0 << 5) | (MCPWM_InitStruct->TR1_T0_RE0 << 6) | (MCPWM_InitStruct->TR1_T1_RE0 << 7) | (MCPWM_InitStruct->TMR0_RE1 << 8) | (MCPWM_InitStruct->TMR1_RE1 << 9) | (MCPWM_InitStruct->TMR2_RE1 << 10) | (MCPWM_InitStruct->TMR3_RE1 << 11) | (MCPWM_InitStruct->TR0_T0_RE1 << 12) | (MCPWM_InitStruct->TR0_T1_RE1 << 13) | (MCPWM_InitStruct->TR1_T0_RE1 << 14) | (MCPWM_InitStruct->TR1_T1_RE1 << 15);

	MCPWM0_PP = MCPWM_InitStruct->IO0_PPE | (MCPWM_InitStruct->IO1_PPE << 1) | (MCPWM_InitStruct->IO2_PPE << 2) | (MCPWM_InitStruct->IO3_PPE << 3) | (MCPWM_InitStruct->IO4_PPE << 4) | (MCPWM_InitStruct->IO5_PPE << 5);

	MCPWM0_IO01 = MCPWM_InitStruct->CH0N_Polarity_INV | (MCPWM_InitStruct->CH0P_Polarity_INV << 1) | (MCPWM_InitStruct->CH0_NS << 2) | (MCPWM_InitStruct->CH0_PS << 3) | (MCPWM_InitStruct->CH0N_SCTRLN << 4) | (MCPWM_InitStruct->CH0P_SCTRLP << 5) | (MCPWM_InitStruct->Switch_CH0N_CH0P << 6) | (MCPWM_InitStruct->MCPWM_WorkModeCH0 << 7) | (MCPWM_InitStruct->CH1N_Polarity_INV << 8) | (MCPWM_InitStruct->CH1P_Polarity_INV << 9) | (MCPWM_InitStruct->CH1_NS << 10) | (MCPWM_InitStruct->CH1_PS << 11) | (MCPWM_InitStruct->CH1N_SCTRLN << 12) | (MCPWM_InitStruct->CH1P_SCTRLP << 13) | (MCPWM_InitStruct->Switch_CH1N_CH1P << 14) | (MCPWM_InitStruct->MCPWM_WorkModeCH1 << 15);

	MCPWM0_IO23 = MCPWM_InitStruct->CH2N_Polarity_INV | (MCPWM_InitStruct->CH2P_Polarity_INV << 1) | (MCPWM_InitStruct->CH2_NS << 2) | (MCPWM_InitStruct->CH2_PS << 3) | (MCPWM_InitStruct->CH2N_SCTRLN << 4) | (MCPWM_InitStruct->CH2P_SCTRLP << 5) | (MCPWM_InitStruct->Switch_CH2N_CH2P << 6) | (MCPWM_InitStruct->MCPWM_WorkModeCH2 << 7) | (MCPWM_InitStruct->CH3N_Polarity_INV << 8) | (MCPWM_InitStruct->CH3P_Polarity_INV << 9) | (MCPWM_InitStruct->CH3_NS << 10) | (MCPWM_InitStruct->CH3_PS << 11) | (MCPWM_InitStruct->CH3N_SCTRLN << 12) | (MCPWM_InitStruct->CH3P_SCTRLP << 13) | (MCPWM_InitStruct->Switch_CH3N_CH3P << 14) | (MCPWM_InitStruct->MCPWM_WorkModeCH3 << 15);

	MCPWM0_IO45 = MCPWM_InitStruct->CH4N_Polarity_INV | (MCPWM_InitStruct->CH4P_Polarity_INV << 1) | (MCPWM_InitStruct->CH4_NS << 2) | (MCPWM_InitStruct->CH4_PS << 3) | (MCPWM_InitStruct->CH4N_SCTRLN << 4) | (MCPWM_InitStruct->CH4P_SCTRLP << 5) | (MCPWM_InitStruct->Switch_CH4N_CH4P << 6) | (MCPWM_InitStruct->MCPWM_WorkModeCH4 << 7) | (MCPWM_InitStruct->CH5N_Polarity_INV << 8) | (MCPWM_InitStruct->CH5P_Polarity_INV << 9) | (MCPWM_InitStruct->CH5_NS << 10) | (MCPWM_InitStruct->CH5_PS << 11) | (MCPWM_InitStruct->CH5N_SCTRLN << 12) | (MCPWM_InitStruct->CH5P_SCTRLP << 13) | (MCPWM_InitStruct->Switch_CH5N_CH5P << 14) | (MCPWM_InitStruct->MCPWM_WorkModeCH5 << 15);

	MCPWM0_TH00 = MCPWM_InitStruct->TH00;
	MCPWM0_TH01 = MCPWM_InitStruct->TH01;
	MCPWM0_TH10 = MCPWM_InitStruct->TH10;
	MCPWM0_TH11 = MCPWM_InitStruct->TH11;
	MCPWM0_TH20 = MCPWM_InitStruct->TH20;
	MCPWM0_TH21 = MCPWM_InitStruct->TH21;
	MCPWM0_TH30 = MCPWM_InitStruct->TH30;
	MCPWM0_TH31 = MCPWM_InitStruct->TH31;
	MCPWM0_TH40 = MCPWM_InitStruct->TH40;
	MCPWM0_TH41 = MCPWM_InitStruct->TH41;
	MCPWM0_TH50 = MCPWM_InitStruct->TH50;
	MCPWM0_TH51 = MCPWM_InitStruct->TH51;

	MCPWM0_FAIL012 = (MCPWM_InitStruct->FAIL0_Polarity << 2) | (MCPWM_InitStruct->FAIL1_Polarity << 3) | (MCPWM_InitStruct->FAIL0_INPUT_EN << 4) | (MCPWM_InitStruct->FAIL1_INPUT_EN << 5) | (MCPWM_InitStruct->HALT_PRT0 << 7) | (MCPWM_InitStruct->FAIL0_Signal_Sel << 8) | (MCPWM_InitStruct->FAIL1_Signal_Sel << 10) | (MCPWM_InitStruct->FAIL_0CAP << 15);

	MCPWM0_FAIL345 = (MCPWM_InitStruct->FAIL2_Polarity << 2) | (MCPWM_InitStruct->FAIL3_Polarity << 3) | (MCPWM_InitStruct->FAIL2_INPUT_EN << 4) | (MCPWM_InitStruct->FAIL3_INPUT_EN << 5) | (MCPWM_InitStruct->HALT_PRT1 << 7) | (MCPWM_InitStruct->FAIL2_Signal_Sel << 8) | (MCPWM_InitStruct->FAIL3_Signal_Sel << 10) | (MCPWM_InitStruct->FAIL_1CAP << 15);

	MCPWM0_CH_DEF = MCPWM_InitStruct->CH0N_default_output | (MCPWM_InitStruct->CH0P_default_output << 1) | (MCPWM_InitStruct->CH1N_default_output << 2) | (MCPWM_InitStruct->CH1P_default_output << 3) | (MCPWM_InitStruct->CH2N_default_output << 4) | (MCPWM_InitStruct->CH2P_default_output << 5) | (MCPWM_InitStruct->CH3N_default_output << 6) | (MCPWM_InitStruct->CH3P_default_output << 7) | (MCPWM_InitStruct->CH4N_default_output << 8) | (MCPWM_InitStruct->CH4P_default_output << 9) | (MCPWM_InitStruct->CH5N_default_output << 10) | (MCPWM_InitStruct->CH5P_default_output << 11);

	MCPWM0_CH_MASK = MCPWM_InitStruct->CH0N_FAIL_EN | (MCPWM_InitStruct->CH0P_FAIL_EN << 1) | (MCPWM_InitStruct->CH1N_FAIL_EN << 2) | (MCPWM_InitStruct->CH1P_FAIL_EN << 3) | (MCPWM_InitStruct->CH2N_FAIL_EN << 4) | (MCPWM_InitStruct->CH2P_FAIL_EN << 5) | (MCPWM_InitStruct->CH3N_FAIL_EN << 6) | (MCPWM_InitStruct->CH3P_FAIL_EN << 7) | (MCPWM_InitStruct->CH4N_FAIL_EN << 8) | (MCPWM_InitStruct->CH4P_FAIL_EN << 9) | (MCPWM_InitStruct->CH5N_FAIL_EN << 10) | (MCPWM_InitStruct->CH5P_FAIL_EN << 11);

	MCPWM0_PRT = 0x0000CAFE; /* write any value other than 0xDEAD to enable write protection */
}
/**
 *@brief @b 函数名称:   void PWMOutputs(FuncState t_state)
 *@brief @b 功能描述:   MCPWM波形输出使能与失能函数
 *@see被引用内容：      无
 *@param输入参数：      FuncState t_state ENABLE：使能 ， DISABLE:使能
 *@param输出参数：      无
 *@return返 回 值：     无
 *@note其它说明：       无
 *@warning             无
 *@par 示例代码：
 *@code
		   PWMOutputs(ENABLE) //使能MCPWM输出
  @endcode
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2019年05月21日 <td>1.0     <td>Howlet      <td>创建
 * <tr><td>2023年03月06日 <td>2.0     <td>Zhujie      <td>修改
 * </table>
 */
void PWMOutputs(FuncState t_state)
{
	MCPWM0_PRT = 0xDEAD;

	if (t_state == DISABLE)
	{
		MCPWM0_FAIL012 &= ~BIT6;
		MCPWM0_FAIL345 &= ~BIT6;
	}
	else
	{
		MCPWM0_FAIL012 |= BIT6;
		MCPWM0_FAIL345 |= BIT6;
	}
	MCPWM0_PRT = 0;
}
/**
 *@brief @b 函数名称:   void MCPWM_ClearIRQFlag(uint32_t INT_flag)
 *@brief @b 功能描述:   清除MCPWM中断标志
 *@see被引用内容：      无
 *@param输入参数：
 * <table>             <tr><th> MCPWM0CNTx            <td>MCPWM0CNT0 计数器0
 *                     <tr><th> MCPWM0CNTx            <td>MCPWM0CNT1 计数器1
 *                     <tr><th> MCPWM0CNT0_T0_IRQ_IF       <td>BIT0  <td> 计数器0计数值回到-MCPWM_TH中断标志位
 *                     <tr><th> MCPWM0CNT0_T1_IRQ_IF       <td>BIT1  <td> 计数器0计数值回到0中断标志位
 *                     <tr><th> MCPWM0CNT0_TH00_IRQ_IF     <td>BIT2  <td> 计数器0计数值回到MCPWM_TH00中断标志位
 *                     <tr><th> MCPWM0CNT0_TH01_IRQ_IF     <td>BIT3  <td> 计数器0计数值回到MCPWM_TH01中断标志位
 *                     <tr><th> MCPWM0CNT0_TH10_IRQ_IF     <td>BIT4  <td> 计数器0计数值回到MCPWM_TH10中断标志位
 *                     <tr><th> MCPWM0CNT0_TH11_IRQ_IF     <td>BIT5  <td> 计数器0计数值回到MCPWM_TH11中断标志位
 *                     <tr><th> MCPWM0CNT0_TH20_IRQ_IF     <td>BIT6  <td> 计数器0计数值回到MCPWM_TH20中断标志位
 *                     <tr><th> MCPWM0CNT0_TH21_IRQ_IF     <td>BIT7  <td> 计数器0计数值回到MCPWM_TH21中断标志位
 *                     <tr><th> MCPWM0CNT0_TMR0_IRQ_IF     <td>BIT10  <td> 计数器0计数值回到MCPWM_TMR0中断标志位
 *                     <tr><th> MCPWM0CNT0_TMR1_IRQ_IF     <td>BIT11  <td> 计数器0计数值回到MCPWM_TMR1中断标志位
 *                     <tr><th> MCPWM0CNT0_TMR2_IRQ_IF     <td>BIT12 <td> 计数器0计数值回到MCPWM_TMR2中断标志位
 *                     <tr><th> MCPWM0CNT0_TMR3_IRQ_IF     <td>BIT13 <td> 计数器0计数值回到MCPWM_TMR3中断标志位
 *                     <tr><th> MCPWM0CNT0_UP_IRQ_IF       <td>BIT14 <td> 计数器0更新中断标志位
 *                     <tr><th> MCPWM0CNT1_T0_IRQ_IF       <td>BIT0  <td> 计数器1计数值回到-MCPWM_TH中断标志位
 *                     <tr><th> MCPWM0CNT1_T1_IRQ_IF       <td>BIT1  <td> 计数器1计数值回到0中断标志位
 *                     <tr><th> MCPWM0CNT1_TH30_IRQ_IF     <td>BIT2  <td> 计数器1计数值回到MCPWM_TH30中断标志位
 *                     <tr><th> MCPWM0CNT1_TH31_IRQ_IF     <td>BIT3  <td> 计数器1计数值回到MCPWM_TH31中断标志位
 *                     <tr><th> MCPWM0CNT1_TH40_IRQ_IF     <td>BIT4  <td> 计数器1计数值回到MCPWM_TH40中断标志位
 *                     <tr><th> MCPWM0CNT1_TH41_IRQ_IF     <td>BIT5  <td> 计数器1计数值回到MCPWM_TH41中断标志位
 *                     <tr><th> MCPWM0CNT1_TH50_IRQ_IF     <td>BIT6  <td> 计数器1计数值回到MCPWM_TH50中断标志位
 *                     <tr><th> MCPWM0CNT1_TH51_IRQ_IF     <td>BIT7  <td> 计数器1计数值回到MCPWM_TH51中断标志位
 *                     <tr><th> MCPWM0CNT1_TMR2_IRQ_IF     <td>BIT12 <td> 计数器1计数值回到MCPWM_TMR2中断标志位
 *                     <tr><th> MCPWM0CNT1_TMR3_IRQ_IF     <td>BIT13 <td> 计数器1计数值回到MCPWM_TMR3中断标志位
 *                     <tr><th> MCPWM0CNT1_UP_IRQ_IF       <td>BIT14 <td> 计数器1更新中断标志位
 * </table>
 *@param输出参数：   无
 *@return返 回 值：  无
 *@note其它说明：    无
 *@warning          无
 *@par 示例代码：
 *@code
		   if(MCPWM_GetIRQFlag(MCPWM0CNT0, MCPWM0CNT0_T0_IRQ_IF))//获取计数器0计数值回到-MCPWM_TH中断标志位
		   {
			MCPWM_ClearIRQFlag(MCPWM0CNT0, MCPWM0CNT0_T0_IRQ_IF))//清除计数器0计数值回到-MCPWM_TH中断标志位
		   }
  @endcode
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2023年03月06日 <td>1.0     <td>Zhujie      <td>创建
 * </table>
 */
void MCPWM_ClearIRQFlag(MCPWM0CNTx CNTx, uint32_t INT_flag)
{
	if (INT_flag <= BIT14)
	{
		if (CNTx == MCPWM0CNT0)
		{
			MCPWM0_IF0 = INT_flag;
		}
		else
		{
			MCPWM0_IF1 = INT_flag;
		}
	}
	else
	{
		MCPWM0_EIF = (INT_flag >> 15);
	}
}
/**
 *@brief @b 函数名称:   u16 MCPWM_GetIRQFlag(MCPWM0CNTx CNTx,uint32_t INT_flag)
 *@brief @b 功能描述:   获取MCPWM中断标志
 *@see被引用内容：      无
 *@param输入参数：
 * <table>             <tr><th> MCPWM0CNTx            <td>MCPWM0CNT0 计数器0
 *                     <tr><th> MCPWM0CNTx            <td>MCPWM0CNT1 计数器1
 *                     <tr><th> MCPWM0CNT0_T0_IRQ_IF       <td>BIT0  <td> 计数器0计数值回到-MCPWM_TH中断标志位
 *                     <tr><th> MCPWM0CNT0_T1_IRQ_IF       <td>BIT1  <td> 计数器0计数值回到0中断标志位
 *                     <tr><th> MCPWM0CNT0_TH00_IRQ_IF     <td>BIT2  <td> 计数器0计数值回到MCPWM_TH00中断标志位
 *                     <tr><th> MCPWM0CNT0_TH01_IRQ_IF     <td>BIT3  <td> 计数器0计数值回到MCPWM_TH01中断标志位
 *                     <tr><th> MCPWM0CNT0_TH10_IRQ_IF     <td>BIT4  <td> 计数器0计数值回到MCPWM_TH10中断标志位
 *                     <tr><th> MCPWM0CNT0_TH11_IRQ_IF     <td>BIT5  <td> 计数器0计数值回到MCPWM_TH11中断标志位
 *                     <tr><th> MCPWM0CNT0_TH20_IRQ_IF     <td>BIT6  <td> 计数器0计数值回到MCPWM_TH20中断标志位
 *                     <tr><th> MCPWM0CNT0_TH21_IRQ_IF     <td>BIT7  <td> 计数器0计数值回到MCPWM_TH21中断标志位
 *                     <tr><th> MCPWM0CNT0_TMR0_IRQ_IF     <td>BIT10  <td> 计数器0计数值回到MCPWM_TMR0中断标志位
 *                     <tr><th> MCPWM0CNT0_TMR1_IRQ_IF     <td>BIT11  <td> 计数器0计数值回到MCPWM_TMR1中断标志位
 *                     <tr><th> MCPWM0CNT0_TMR2_IRQ_IF     <td>BIT12 <td> 计数器0计数值回到MCPWM_TMR2中断标志位
 *                     <tr><th> MCPWM0CNT0_TMR3_IRQ_IF     <td>BIT13 <td> 计数器0计数值回到MCPWM_TMR3中断标志位
 *                     <tr><th> MCPWM0CNT0_UP_IRQ_IF       <td>BIT14 <td> 计数器0更新中断标志位
 *                     <tr><th> MCPWM0CNT1_T0_IRQ_IF       <td>BIT0  <td> 计数器1计数值回到-MCPWM_TH中断标志位
 *                     <tr><th> MCPWM0CNT1_T1_IRQ_IF       <td>BIT1  <td> 计数器1计数值回到0中断标志位
 *                     <tr><th> MCPWM0CNT1_TH30_IRQ_IF     <td>BIT2  <td> 计数器1计数值回到MCPWM_TH30中断标志位
 *                     <tr><th> MCPWM0CNT1_TH31_IRQ_IF     <td>BIT3  <td> 计数器1计数值回到MCPWM_TH31中断标志位
 *                     <tr><th> MCPWM0CNT1_TH40_IRQ_IF     <td>BIT4  <td> 计数器1计数值回到MCPWM_TH40中断标志位
 *                     <tr><th> MCPWM0CNT1_TH41_IRQ_IF     <td>BIT5  <td> 计数器1计数值回到MCPWM_TH41中断标志位
 *                     <tr><th> MCPWM0CNT1_TH50_IRQ_IF     <td>BIT6  <td> 计数器1计数值回到MCPWM_TH50中断标志位
 *                     <tr><th> MCPWM0CNT1_TH51_IRQ_IF     <td>BIT7  <td> 计数器1计数值回到MCPWM_TH51中断标志位
 *                     <tr><th> MCPWM0CNT1_TMR2_IRQ_IF     <td>BIT12 <td> 计数器1计数值回到MCPWM_TMR2中断标志位
 *                     <tr><th> MCPWM0CNT1_TMR3_IRQ_IF     <td>BIT13 <td> 计数器1计数值回到MCPWM_TMR3中断标志位
 *                     <tr><th> MCPWM0CNT1_UP_IRQ_IF       <td>BIT14 <td> 计数器1更新中断标志位
 * </table>
 *@param输出参数：   无
 *@return返 回 值：  读对应标志位是否为1，1位置位，0为未置位
 *@note其它说明：    无
 *@warning           只有对应中断使能后，改为才能读取，如果对应中断未使能，读取结果一直为0
 *@par 示例代码：
 *@code
		   if(MCPWM_GetIRQFlag(MCPWM0CNT0, MCPWM0CNT0_T0_IRQ_IF))//获取计数器0计数值回到-MCPWM_TH中断标志位
		   {
		   }
  @endcode
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2023年03月06日 <td>1.0     <td>Zhujie      <td>创建
 * </table>
 */
u16 MCPWM_GetIRQFlag(MCPWM0CNTx CNTx, uint32_t INT_flag)
{
	u8 MCPWMIRQFlag = 0;
	if (INT_flag <= BIT14)
	{
		if (CNTx)
		{
			if (MCPWM0_IF0 & INT_flag & MCPWM0_IE0)
			{
				MCPWMIRQFlag = 1;
			}
			else
			{
				MCPWMIRQFlag = 0;
			}
		}
		else
		{
			if (MCPWM0_IF1 & INT_flag & MCPWM0_IE1)
			{
				MCPWMIRQFlag = 1;
			}
			else
			{
				MCPWMIRQFlag = 0;
			}
		}
	}
	else
	{
		if (MCPWM0_EIF & (INT_flag >> 15) & MCPWM0_EIE)
		{
			MCPWMIRQFlag = 1;
		}
		else
		{
			MCPWMIRQFlag = 0;
		}
	}
	return MCPWMIRQFlag;
}
/************************ (C) COPYRIGHT LINKO SEMICONDUCTOR *****END OF FILE****/
