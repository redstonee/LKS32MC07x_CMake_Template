/**
 * @file
 * @copyright (C)2015, LINKO SEMICONDUCTOR Co.ltd
 * @brief 文件名称： LKS32MC07x_dac.c\n
 * 文件标识： 无 \n
 * 内容摘要： DAC外设驱动程序 \n
 * 其它说明： 无 \n
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2023年3月22日 <td>1.0     <td>Olive Wang      <td>创建
 * </table>
 */

#include "lks32mc07x_dac.h"
#include "string.h"
/**
 *@brief @b 函数名称:   void DAC_StructInit(DAC_InitTypeDef* DAC_InitStruct)
 *@brief @b 功能描述:   DAC结构体初始化
 *@see被调用函数：       无
 *@param输入参数：      ADC_InitTypeDef
 *@param输出参数：      无
 *@return返 回 值：     无
 *@note其它说明：       无
 *@warning             无
 *@par 示例代码：
 *@code
		   DAC_StructInit DAC_InitStructure;
		   DAC_StructInit(&DAC_InitStructure); //初始化结构体
  @endcode
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2023年2月22日 <td>1.0     <td>Olive Wang      <td>创建
 * </table>
 */
void DAC_StructInit(DAC_InitTypeDef *DAC_InitStruct)
{
	memset(DAC_InitStruct, 0, sizeof(DAC_InitTypeDef));
}

/**
 *@brief @b 函数名称:   void DAC_init(uint8_t DAC_Channel,DAC_InitTypeDef* DAC_InitStruct)
 *@brief @b 功能描述:   DAC初始化函数
*@param输入参数：       DAC_Channel:DAC_Channel_0/DAC_Channel_1,DAC_InitTypeDef
 *@param输出参数：      无
 *@return返 回 值：     无
 *@note其它说明：       无
 *@warning             无
 *@par 示例代码：
 *@code
			  DAC_InitTypeDef DAC_InitStructure;
			  DAC_StructInit(&DAC_InitStructure);
			  DAC_InitStructure.DAC_GAIN = DAC_RANGE_1V2;//DAC量程为1.2V
			  DAC_InitStructure.DACOUT_EN = DISABLE ;    //DAC通过IO P0[0]输出
				DAC_InitStre.TIG_CH_EN = DISABLE; 		  	//失能UTIMER触发
				DAC_InitStre.DAC_STEP = 0;						  	//步进值为0
			  DAC_Init(DAC_Channel_0,&DAC_InitStructure);              // DAC初始化
  @endcode
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author      <th>Description
 * <tr><td>2023年2月22日 <td>1.0     <td>Olive Wang      <td>创建
 * </table>
 */

void DAC_Init(uint8_t DAC_Channel, DAC_InitTypeDef *DAC_InitStruct)
{
	SYS_WR_PROTECT = 0x7a83;									   /* 解锁寄存器写保护 */
	SYS_AFE_REG1 &= ~((u32)0x01 << (6 + DAC_Channel));			   /* DAC增益寄存器清零 */
	SYS_AFE_REG1 |= DAC_InitStruct->DAC_GAIN << (6 + DAC_Channel); /* 设置DAC满量程为1.2V 或4.8V*/

	if (DAC_Channel_0 == DAC_Channel)
	{
		if (((SYS_AFE_REG1 >> 6) & 0x01) == DAC_RANGE_1V2)
		{ /* 加载DAC 1.2V量程校正值 */
			SYS_AFE_DAC0_DC = Read_Trim(0x0000145C);
			SYS_AFE_DAC0_AMC = Read_Trim(0x00001458);
		}
		else if (((SYS_AFE_REG1 >> 6) & 0x01) == DAC_RANGE_4V85)
		{ /* 加载DAC 4.85V量程校正值 */
			SYS_AFE_DAC0_DC = Read_Trim(0x00001454);
			SYS_AFE_DAC0_AMC = Read_Trim(0x00001450);
		}
		SYS_AFE_DAC_CTRL |= (DAC_InitStruct->DAC_STEP << 4) | (DAC_InitStruct->TIG_CH_EN);
		SYS_AFE_REG3 |= DAC_InitStruct->DACOUT_EN << 11; /* DAC输出配置 */
	}
	else if (DAC_Channel_1 == DAC_Channel)
	{
		if (((SYS_AFE_REG1 >> 7) & 0x01) == DAC_RANGE_1V2)
		{ /* 加载DAC 1.2V量程校正值 */
			SYS_AFE_DAC1_DC = Read_Trim(0x0000146C);
			SYS_AFE_DAC1_AMC = Read_Trim(0x00001468);
		}
		else if (((SYS_AFE_REG1 >> 7) & 0x01) == DAC_RANGE_4V85)
		{ /* 加载DAC 4.85V量程校正值 */
			SYS_AFE_DAC1_DC = Read_Trim(0x00001464);
			SYS_AFE_DAC1_AMC = Read_Trim(0x00001460);
		}
		SYS_AFE_DAC_CTRL |= (DAC_InitStruct->DAC_STEP << 12) | (DAC_InitStruct->TIG_CH_EN << 8);
		SYS_AFE_REG3 |= DAC_InitStruct->DACOUT_EN << 15; /* DAC输出配置 */
	}
	SYS_WR_PROTECT = 0xffff; /* 锁定寄存器写保护 */
}
/**
 *@brief @b 函数名称:   void DAC_OutputValue(uint8_t DAC_Channel,uint32_t DACValue)
 *@brief @b 功能描述:   DAC输出数字量数值设置
 *@see被调用函数：       无
 *@param输入参数：       DAC_Channel：DAC_Channel_0/DAC_Channel_1，DACValue:DAC输出电压对应数字量
 *@param输出参数：       无
 *@return返 回 值：      无
 *@note其它说明：        无
 *@warning              无
 *@par 示例代码：
 *@code
		   DAC_OutputValue(DAC_Channel_0,2048);//DAC输出2048*1.2/4096 = 0.6V
  @endcode
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2023年2月22日 <td>1.0     <td>Olive Wang      <td>创建
 * </table>
 */
void DAC_OutputValue(uint8_t DAC_Channel, uint32_t DACValue)
{
	DACValue &= 0xFFF; // 判断DACValue不大于4095

	if (DAC_Channel_0 == DAC_Channel)
	{
		SYS_AFE_DAC0 = DACValue;
	}
	else if (DAC_Channel_1 == DAC_Channel)
	{
		SYS_AFE_DAC1 = DACValue;
	}
}
/**
 *@brief @b 函数名称:   void DAC_OutputVoltage(uint8_t DAC_Channel,uint32_t DACVoltage)
 *@brief @b 功能描述:   DAC输出模拟量数值设置
 *@see被调用函数：       无
 *@param输入参数：       DAC_Channel：DAC_Channel_0/DAC_Channel_1，DACVoltage:DAC输出电压对应数字量
 *@param输出参数：       无
 *@return返 回 值：      无
 *@note其它说明：        输入变量DACVoltage为Q12格式，即输出1V对应DACVoltage = 1<<12 = 4096
 *@warning              无
 *@par 示例代码：
 *@code
		   DAC_OutputVoltage(DAC_Channel_0,BIT12 * 0.6);//DAC输出0.6V
  @endcode
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2023年2月22日 <td>1.0     <td>Olive Wang      <td>创建
 * </table>
 */

void DAC_OutputVoltage(uint8_t DAC_Channel, uint16_t DACVoltage)
{
	u32 temp = 0;
	u32 range = 0;

	if (((SYS_AFE_REG1 >> (6 + DAC_Channel)) & 0x01) == DAC_RANGE_1V2)
	{ /* 加载DAC 1.2V量程校正值 */
		range = (uint16_t)((1.0 / 1.2) * BIT12);
	}
	else if (((SYS_AFE_REG1 >> (6 + DAC_Channel)) & 0x01) == DAC_RANGE_4V85)
	{ /* 加载DAC 4.85V量程校正值 */
		range = (uint16_t)((1.0 / 4.85) * BIT12);
	}

	temp = (DACVoltage * range + BIT11) >> 12;
	temp &= 0xFFF; // 最大值4095限制

	if (DAC_Channel_0 == DAC_Channel)
	{
		SYS_AFE_DAC0 = temp;
	}
	else if (DAC_Channel_1 == DAC_Channel)
	{
		SYS_AFE_DAC1 = temp;
	}
}
/**
 *@brief @b 函数名称:   void DAC_Cmd(uint8_t DAC_Channel,FuncState state)
 *@brief @b 功能描述:   DAC外设使能
 *@see被调用函数：       无
 *@param输入参数：       DAC_Channel：通道DAC_Channel_0/DAC_Channel_1，state：ENABLE/DISABLE
 *@param输出参数：       无
 *@return返 回 值：      无
 *@note其它说明：        无
 *@warning              无
 *@par 示例代码：
 *@code
		  DAC_Cmd(DAC_Channel_0,ENABLE);
  @endcode
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2023年2月22日 <td>1.0     <td>Olive Wang      <td>创建
 * </table>
 */

void DAC_Cmd(uint8_t DAC_Channel, FuncState state)
{
	if (DAC_Channel_0 == DAC_Channel)
	{
		SYS_AnalogModuleClockCmd(SYS_AnalogModule_DAC0, state); /* DAC0 时钟使能 */
	}
	else if (DAC_Channel_1 == DAC_Channel)
	{
		SYS_AnalogModuleClockCmd(SYS_AnalogModule_DAC1, state); /* DAC1 时钟使能 */
	}
}

/************************ (C) COPYRIGHT LINKO SEMICONDUCTOR *****END OF FILE****/
