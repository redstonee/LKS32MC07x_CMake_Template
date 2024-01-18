/**
 * @file
 * @copyright (C)2015, LINKO SEMICONDUCTOR Co.ltd
 * @brief 文件名称： lks32mc07x_opa.c\n
 * 文件标识： 无 \n
 * 内容摘要： OPA运放外设驱动程序 \n
 * 其它说明： 无 \n
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2023年02月22日 <td>1.0     <td>Olive Wang      <td>创建
 * </table>
 */
#include "lks32mc07x_opa.h"

/**
 *@brief @b 函数名称:   void OPA_Init(enumOPA opa, OPA_InitTypeDef* OPA_InitStruct)
 *@brief @b 功能描述:   OPA初始化函数
 *@see被引用内容：       无
 *@param输入参数：       enumOPA opa , OPA_InitTypeDef *OPA_InitStruct
 *@param输出参数：       无
 *@return返 回 值：      无
 *@note其它说明：        无
 *@warning              无
 *@par 示例代码：
 *@code
			OPA_InitTypeDef OPA_InitStruct;
			OPA_StructInit(&OPA_InitStruct);
			OPA_InitStruct.OPA_IT = PGA_IT_DISABLE; //opa偏置电流调节禁止
			OPA_InitStruct.OPA_CLEna = ENABLE;     //使能
			OPA_InitStruct.OPA_Gain = PGA_GAIN_4; //增益40k:10k
			OPA_Init(OPA2 ,&OPA_InitStruct);
  @endcode
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author      <th>Description
 * <tr><td>2023年02月22日 <td>1.0       <td>Olive Wang          <td>创建
 * </table>
 */
void OPA_Init(enumOPA opa, OPA_InitTypeDef *OPA_InitStruct)
{
	uint32_t tmp1, tmp2;
	SYS_WR_PROTECT = 0x7a83; /* 解除系统寄存器写保护 */
	tmp1 = SYS_AFE_REG0;
	tmp2 = SYS_AFE_REG5;

	if (opa == OPA0)
	{
		tmp1 &= ~(BIT0 | BIT1);
		tmp1 |= OPA_InitStruct->OPA_Gain;

		tmp2 &= ~BIT2;
		tmp2 |= (OPA_InitStruct->OPA_CLEna << 2);
	}
	else if (opa == OPA1)
	{
		tmp1 &= ~(BIT2 | BIT3);
		tmp1 |= (OPA_InitStruct->OPA_Gain << 2);

		tmp2 &= ~BIT3;
		tmp2 |= (OPA_InitStruct->OPA_CLEna << 3);
	}
	else if (opa == OPA2)
	{
		tmp1 &= ~(BIT4 | BIT5);
		tmp1 |= (OPA_InitStruct->OPA_Gain << 4);

		tmp2 &= ~BIT4;
		tmp2 |= (OPA_InitStruct->OPA_CLEna << 4);
	}
	else if (opa == OPA3)
	{
		tmp1 &= ~(BIT6 | BIT7);
		tmp1 |= (OPA_InitStruct->OPA_Gain << 6);

		tmp2 &= ~BIT5;
		tmp2 |= (OPA_InitStruct->OPA_CLEna << 5);
	}

	tmp1 &= ~(BIT8 | BIT9);
	tmp1 |= (OPA_InitStruct->OPA_IT << 8);

	SYS_AFE_REG0 = tmp1;
	SYS_AFE_REG5 = tmp2;
	SYS_WR_PROTECT = 0x0; /* 开启系统寄存器写保护 */
}

/**
 *@brief @b 函数名称:   void OPA_StructInit(OPA_InitTypeDef* OPA_InitStruct)
 *@brief @b 功能描述:   OPA结构体初始化
 *@see被引用内容：       无
 *@param输入参数：       OPA_InitTypeDef *OPA_InitStruct
 *@param输出参数：       无
 *@return返 回 值：      无
 *@note其它说明：        无
 *@warning              无
 *@par 示例代码：
 *@code
				OPA_InitTypeDef OPA_InitStruct;
				OPA_StructInit(&OPA_InitStruct);       //初始化结构体
  @endcode
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author      <th>Description
 * <tr><td>2023年02月22日 <td>1.0       <td>Olive Wang          <td>创建
 * </table>
 */
void OPA_StructInit(OPA_InitTypeDef *OPA_InitStruct)
{
	OPA_InitStruct->OPA_IT = PGA_IT_DISABLE;
	OPA_InitStruct->OPA_Gain = PGA_GAIN_4;
	OPA_InitStruct->OPA_CLEna = DISABLE;
}
/**
 *@brief @b 函数名称:   void OPA_OUT(enumOPA opa, FuncState state)
 *@brief @b 功能描述:   OPA外部输出，输出到外部P2.7引脚
 *@see被引用内容：       无
 *@param输入参数：       enumOPA opa, FuncState state
 *@param输出参数：       无
 *@return返 回 值：      无
 *@note其它说明：        无
 *@warning              无
 *@par 示例代码：
 *@code
			   OPA_OUT(OPA0,ENABLE); //将OPA0输出通过外部P2.7引脚送出
  @endcode
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author      <th>Description
 * <tr><td>2023年02月22日 <td>1.0       <td>Olive Wang        <td>创建
 * </table>
 */
void OPA_OUT(enumOPA opa, FuncState state)
{
	SYS_WR_PROTECT = 0x7a83; /* 解除系统寄存器写保护 */
	if (state != DISABLE)
	{
		if (opa == OPA0)
		{
			SYS_AFE_REG2 = 0x01;
		}
		else if (opa == OPA1)
		{
			SYS_AFE_REG2 = 0x02;
		}
		else if (opa == OPA2)
		{
			SYS_AFE_REG2 = 0x03;
		}
		else if (opa == OPA3)
		{
			SYS_AFE_REG2 = 0x04;
		}
	}
	else
	{
		SYS_AFE_REG2 = 0x00;
	}
	SYS_WR_PROTECT = 0x0; /* 开启系统寄存器写保护 */
}

/************************ (C) COPYRIGHT LINKO SEMICONDUCTOR *****END OF FILE****/
