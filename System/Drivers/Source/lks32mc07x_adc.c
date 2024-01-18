/**
 * @file 
 * @copyright (C)2015, LINKO SEMICONDUCTOR Co.ltd
 * @brief 文件名称： lks32mc07x_adc.c\n
 * 文件标识： 无 \n
 * 内容摘要： ADC外设驱动程序 \n
 * 其它说明： 无 \n
 *@par 修改日志:
 * <table>
 * <tr><th>Date	       <th>Version   <th>Author  <th>Description
 * <tr><td>2023年2月27日 <td>1.0     <td>ZhuJie     <td>创建
 * </table>
 */
#include "lks32mc07x_adc.h"
#include "lks32mc07x_sys.h"

/**
 *@brief @b 函数名称:   void ADC_Init(ADC_TypeDef* ADCx, ADC_InitTypeDef* ADC_InitStruct)
 *@brief @b 功能描述:   ADC初始化函数
 *@see被引用内容：      SYS_AnalogModuleClockCmd()
 *@param输入参数：      ADCx：ADC0 , ADC_InitTypeDef *ADC_InitTypeDef
 *@param输出参数：      无
 *@return返 回 值：     无
 *@note其它说明：       无
 *@warning             无
 *@par 示例代码：
 *@code
			ADC_InitTypeDef ADC_InitStructure;
			ADC_StructInit(&ADC_InitStructure);                            // 初始化结构体
			ADC_InitStructure.ADC_CLK_DIV  = ADC_Clock_48M;                // ADC时钟选择48MHz
			ADC_InitStructure.Align = ADC_LEFT_ALIGN;                      // ADC数据输出左对齐
			ADC_InitStructure.Trigger_Mode = ADC_2SEG_TRG;                 // 设置ADC转换模式为双段式采样
			ADC_InitStructure.FirSeg_Ch = ADC_2_TIMES_SAMPLE;              // 第一段共采样2个通道
			ADC_InitStructure.SecSeg_Ch = ADC_2_TIMES_SAMPLE;              // 第二段共采样2个通道
			ADC_InitStructure.ThrSeg_Ch  = 0;                              // 第三段共采样0个通道
			ADC_InitStructure.FouSeg_Ch = 0;                               // 第四段共采样0个通道
			ADC_InitStructure.RefVol = RefVol_2V4;                         // ADC基准电压2.4V
			ADC_InitStructure.Gain0 = 0x0;                                 // ADC_DAT0-ADC_DAT9 (BIT0~BIT9)采样保持电路增益设置2/3
			ADC_InitStructure.Gain1 = 0x0;                                 // ADC_DAT10-ADC_DAT19(BIT10~BIT19)采样保持电路增益设置2/3
			ADC_InitStructure.Con_Sample = DISABLE;                        // 关闭连续采样
			// 打开 UTIMER T0 T1 硬件触发采样
			ADC_InitStructure.MCPWM_Trigger_En  = ADC_MCPWM_T0_TRG|ADC_MCPWM_T1_TRG;// 开启UTIMER硬件第一段和第二段触发采样
			ADC_InitStructure.UTIMER_Trigger_En = DISABLE;                 // 关闭UTIMER硬件触发采样
			ADC_InitStructure.Trigger_Cnt = 0;                             // 发生(Trigger_Cnt+1)次触发事件执行一段转换动作
			ADC_InitStructure.IE = ADC_EOS0_IRQ_EN | ADC_EOS1_IRQ_EN;      // ADC第一、二段采样结束中断使能
			ADC_Init(ADC0, &ADC_InitStructure);
  @endcode
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author      <th>Description
 * <tr><td>2015年11月26日 <td>1.0     <td>Howlet Li       <td>创建
 * </table>
 */
void ADC_Init(ADC_TypeDef* ADCx, ADC_InitTypeDef* this)
{
    SYS_AnalogModuleClockCmd(SYS_AnalogModule_ADC,ENABLE);// ADC模块使能

    ADCx->IE   = this->IE | this->RE;
    ADCx->CHNT =   (this->IS1   << 8 ) | (this->S2          << 4) \
                 | (this->S1    << 0 );
    ADCx->TRIG = this->TRIG;
    ADCx->CFG  =   (this->NSMP  << 12) | (this->DATA_ALIGN  << 10) \
                 | (this->CSMP  << 8 ) | (this->TCNT        << 4 ) \
                 | (this->TROVS << 3 ) | (this->OVSR        << 0 ) ;

		ADCx->LTH = this->LTH;
    ADCx->HTH = this->HTH;
    ADCx->GEN = this->GEN;
								 

			  ADC0->DC0  = Read_Trim(0x00001420) ;  /* 3.6V量程对应DC offset    */ 
        ADC0->AMC0 = Read_Trim(0x00001424) ;  /* 3.6V量程对应增益校正系数 */		
			  ADC0->DC1  = Read_Trim(0x00001428) ;  /* 7.2V量程对应DC offset    */
        ADC0->AMC1 = Read_Trim(0x0000142c) ;  /* 7.2V量程对应增益校正系数 */	
			
			  ADC1->DC0  = Read_Trim(0x00001430) ;  /* 3.6V量程对应DC offset    */ 
        ADC1->AMC0 = Read_Trim(0x00001434) ;  /* 3.6V量程对应增益校正系数 */		
			  ADC1->DC1  = Read_Trim(0x00001438) ;  /* 7.2V量程对应DC offset    */
        ADC1->AMC1 = Read_Trim(0x0000143c) ;  /* 7.2V量程对应增益校正系数 */
    					 
}

/**
 *@brief @b 函数名称:   void ADC_StructInit(ADC_InitTypeDef* ADC_InitStruct)
 *@brief @b 功能描述:   ADC结构体初始化
 *@see被引用内容：      无
 *@param输入参数：      ADC_InitTypeDef *ADC_InitStruct
 *@param输出参数：      无
 *@return返 回 值：     无
 *@note其它说明：       无
 *@warning             无
 *@par 示例代码：
 *@code
		   ADC_InitTypeDef ADC_InitStructure;
		   ADC_StructInit(&ADC_InitStructure); //初始化结构体
  @endcode
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2015年11月26日 <td>1.0     <td>Howlet     <td>修改
 * </table>
 */
void ADC_StructInit(ADC_InitTypeDef* this)
{
    this->IE         = 0    ;   // 中断使能
    this->RE         = 0    ;   // DMA请求使能
    this->NSMP       = 0    ;   // 两段采样使能
    this->DATA_ALIGN = 0    ;   // DAT对齐方式
    this->CSMP       = 0    ;   // 连续采样使能
    this->TCNT       = 0    ;   // 触发一次采样所需的事件数
    this->TROVS      = 0    ;   // 过采样触发模式
    this->OVSR       = 0    ;   // 过采样率
    this->TRIG       = 0    ;   // 触发信号
    this->S1         = 1    ;   // 第一段常规采样次数
    this->S2         = 1    ;   // 第二段常规采样次数
    this->IS1        = 1    ;   // 空闲采样次数
	  this->GAIN       = 0    ;   // 量程默认3.6V
}

/**
 *@brief @b 函数名称:   void ADC_ClearIRQFlag(ADC_TypeDef* ADCx, uint16_t INT_flag)
 *@brief @b 功能描述:   ADC中断标志位清零
 *@see被引用内容：      无
 *@param输入参数：
 * <table>              <tr><td>ADCx：    <td> ADC0
 *                      <tr><td>INT_flag: 					 <td> ADC中断标志
 * 											<tr><th>ADC_ISF_IF    			 <td>空闲采样完成中断标志 \n
 * 											<tr><th>ADC_HERR_IF          <td>硬件触发发生在非空闲状态中断标志 \n
 * 											<tr><th>ADC_SERR_IF          <td>软件触发发生在非空闲状态中断标志 \n
 * 											<tr><th>ADC_AWD0_IF          <td>阈值监测 0 超限中断标志 \n
 * 											<tr><th>ADC_SF2_IF           <td>第二段扫描结束中断标志 \n
 * 											<tr><th>ADC_SF1_IF           <td>第一段扫描结束中断标志 \n
 * 											<tr><th>ADC_ALL_IF           <td>所有ADC中断标志 \n
 * </table>
 *@param输出参数：   无
 *@return返 回 值：  无
 *@note其它说明：    无
 *@warning          无
 *@par 示例代码：
 *@code
		   if(ADC_GetIRQFlag(ADC0,ADC_EOS0_IRQ_IF))//获取第一段扫描结束中断标志
		   {
			    ADC_ClearIRQFlag(ADC0,ADC_EOS0_IRQ_IF)//第一段扫描结束中断标志
		   }
  @endcode
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2023年02月27日 <td>1.0     <td>Zhu Jie      <td>创建
 * </table>
 */
void ADC_ClearIRQFlag(ADC_TypeDef *ADCx, uint16_t INT_flag)
{
	  ADCx->IF = INT_flag;
}

/**
 *@brief @b 函数名称:   uint16_t ADC_GetIRQFlag(ADC_TypeDef* ADCx, uint16_t INT_flag)
 *@brief @b 功能描述:   获取ADC中断标志
 *@see被引用内容：      无
 *@param输入参数：
 * <table>              <tr><td>ADCx：        			 <td> ADC0
 *                      <tr><td>INT_flag: 					 <td> ADC中断标志
 * 											<tr><th>ADC_ISF_IF    			 <td>空闲采样完成中断标志 \n
 * 											<tr><th>ADC_HERR_IF          <td>硬件触发发生在非空闲状态中断标志 \n
 * 											<tr><th>ADC_SERR_IF          <td>软件触发发生在非空闲状态中断标志 \n
 * 											<tr><th>ADC_AWD0_IF          <td>阈值监测 0 超限中断标志 \n
 * 											<tr><th>ADC_SF2_IF           <td>第二段扫描结束中断标志 \n
 * 											<tr><th>ADC_SF1_IF           <td>第一段扫描结束中断标志 \n
 * </table>
 *@param输出参数：   无
 *@return返 回 值：  读对应标志位是否为1，1位置位，0为未置位
 *@note其它说明：    无
 *@warning           只有对应中断使能后，改为才能读取，如果对应中断未使能，读取结果一直为0
 *@par 示例代码：
 *@code
		   if(ADC_GetIRQFlag(ADC0,ADC_SF1_IF))//获取第一段扫描结束中断标志
		   {
			     ADC_ClearIRQFlag(ADC0,ADC_SF1_IF) //第一段扫描结束中断标志
		   }
  @endcode
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2023年02月27日 <td>1.0     <td>Zhu Jie      <td>创建
 * </table>
 */
u16 ADC_GetIRQFlag(ADC_TypeDef *ADCx, uint16_t INT_flag)
{
	u8 ADCIRQFlag = 0;
	if (ADCx->IF & INT_flag & ADCx->IE)
	{
		ADCIRQFlag = 1;
	}
	else
	{
		ADCIRQFlag = 0;
	}
	return ADCIRQFlag;
}

/**
 *@brief @b 函数名称:   void ADC_CHN_GAIN_CFG(ADC_TypeDef *ADCx,CHNx CHNum,u8 passageway, ADC_GAINx GAIN3V6_or_7V2)
 *@brief @b 功能描述:   ADC采样通道设置
 *@see被引用内容：      CHNx
 *@param输入参数：
					             ADCx，07系列有ADC0和ADC1
 *                     CHNum为枚举类型，对应0-15；Channel_0为采样通道序号对应0
 *                     nChannel：ADC_CHANNEL_0 ~ ADC_CHANNEL_15 通道选择
 *                     ADC_GAINx：ADC_GAIN3V6,ADC_GAIN7V2 量程选择
 *@param输出参数：     无
 *@return返 回 值：    无
 *@note其它说明：      无
 *@warning             无
 *@par 示例代码：
 *@code
		   ADC_CHN_GAIN_CFG(ADC0,CHN0,ADC_CHANNEL_9,ADC_GAIN3V6);//配置ADC0第0次采样ADC通道9的信号，选择量程为3.6V
		   ADC_CHN_GAIN_CFG(ADC1,CHN1,ADC_CHANNEL_9,ADC_GAIN7V2);//配置ADC1第1次采样ADC通道9的信号，选择量程为7.2V
  @endcode
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2023年03月9日 <td>1.0     <td>Zhu Jie      <td>创建
 * </table>
 */
void ADC_CHN_GAIN_CFG(ADC_TypeDef *ADCx,CHNx CHNum,u8 nChannel, ADC_GAINx GAIN3V6_or_7V2)
{
    u8 val;
    u32 reg;
	
	  if(GAIN3V6_or_7V2 == 1)
		{
		    ADCx->GAIN |= (GAIN3V6_or_7V2 << CHNum);
		}
		
    val = CHNum >> 2;
    val &= 3;
    CHNum &= 3;
    CHNum *= 4;
    reg = (&ADCx->CHN0)[val] & ~(0xf<<CHNum);
    (&ADCx->CHN0)[val] = reg | (nChannel << CHNum);
}

/**
 *@brief @b 函数名称:   s16 ADC_GetConversionValue(ADC_TypeDef *ADCx,DATx DATNum)
 *@brief @b 功能描述:   读ADC采样值
 *@see被引用内容：      ADCx：ADC0或ADC1
 *@param输入参数：      DATx：读取第几次采样结果值，取值为0-15
 *@param输出参数：      无
 *@return返 回 值：     对应x次采样结果值
 *@note其它说明：       无
 *@warning             无
 *@par 示例代码：
 *@code
		   s16 ADC_samp0 = 0；
		   ADC_samp0 = ADC_GetConversionValue(ADC0,DAT3);//读取ADC0第3次采样结果
  @endcode
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2023年02月27日 <td>1.0     <td>Zhu Jie      <td>创建
 * </table>
 */
s16 ADC_GetConversionValue(ADC_TypeDef *ADCx,DATx DATNum)
{
		if (DATNum == DAT0)
		{
				return ADCx->DAT0;
		}
		else if (DATNum == DAT1)
		{
				return ADCx->DAT1;
		}
		else if (DATNum == DAT2)
		{
				return ADCx->DAT2;
		}
		else if (DATNum == DAT3)
		{
				return ADCx->DAT3;;
		}
		else if (DATNum == DAT4)
		{
				return ADCx->DAT4;
		}
		else if (DATNum == DAT5)
		{
				return ADCx->DAT5;
		}
		else if (DATNum == DAT6)
		{
				return ADCx->DAT6;
		}
		else if (DATNum == DAT7)
		{
				return ADCx->DAT7;
		}
		else if (DATNum == DAT8)
		{
				return ADCx->DAT8;
		}
		else if (DATNum == DAT9)
		{
				return ADCx->DAT9;
		}
		else if (DATNum == DAT10)
		{
				return ADCx->DAT10;
		}
		else if (DATNum == DAT11)
		{
				return ADCx->DAT11;
		}
		else if (DATNum == DAT12)
		{
				return ADCx->DAT12;
		}
		else if (DATNum == DAT13)
		{
				return ADCx->DAT13;
		}
		else if (DATNum == DAT14)
		{
				return ADCx->IDAT0;
		}
		else if (DATNum == DAT15)
		{
				return ADCx->IDAT1;
		}
		else
		{
				return 0;
		}
}

/**
 *@brief @b 函数名称:   void ADC_SoftTrgEN(ADC_TypeDef* ADCx, FuncState state)
 *@brief @b 功能描述:   ADC采样软件触发使能
 *@see被引用内容：      FuncState
 *@param输入参数：      ADCx，08系列固定选择ADC0
 *                     state：ENABLE触发，DISABLE不触发
 *@param输出参数：      无
 *@return返 回 值：     无
 *@note其它说明：       ADC0_SWT写0x5AA5仅触发一次，完成后自动清零，等待下次软件触发
 *@warning             无
 *@par 示例代码：
 *@code
		  ADC_SoftTrgEN(ADC0，ENABLE);//软件触发一次ADC采样
  @endcode
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2023年02月27日 <td>1.0     <td>Zhu Jie      <td>创建
 * </table>
 */
void ADC_SoftTrgEN(ADC_TypeDef *ADCx, FuncState state)
{
 if (state == ENABLE)
 {
    ADCx->SWT = 0x5AA5;
 }
}

/************************ (C) COPYRIGHT LINKO SEMICONDUCTOR *****END OF FILE****/
