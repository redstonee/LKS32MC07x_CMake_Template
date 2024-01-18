/**
 * @file
 * @copyright (C)2015, LINKO SEMICONDUCTOR Co.ltd
 * @brief 文件名称： LKS32MC07x_sif.c\n
 * 文件标识： 无 \n
 * 内容摘要： SIF外设驱动程序 \n
 * 其它说明： 无 \n
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2023年2月12日 <td>1.1     <td>myx   <td>修改
 * </table>
 */
#include "lks32mc07x_sif.h"

void SIF_StructInit(SIF_InitTypeDef *SIFInitStruct)
{
	memset(SIFInitStruct, 0, sizeof(SIF_InitTypeDef));
}

/**
 *@brief @b 函数名称:   void SIF_Init(SIF_RegTypeDef *SIFx, SIF_InitTypeDef *SIFInitStruct)
 *@brief @b 功能描述:   SIF初始化函数
 *@see被引用内容：
 *@param输入参数：       SIFx：SIF , SIF_InitTypeDef *SIF_InitStruct
 *@param输出参数：       无
 *@return返 回 值：      无
 *@note其它说明：        无
 *@warning              无
 *@par 示例代码：
 *@code
	SIF_InitTypeDef SIF_InitStruct;
	SIF_StructInit(&SIF_InitStruct);

	SIF_InitStruct.SIF_DONE = DISABLE;			// 传输完成后默认低电平
	SIF_InitStruct.SIF_SYNC = DISABLE;			// 同步信号默认低电平
	SIF_InitStruct.SIF_SYNC_PULSE = ENABLE;		// 同步信号有电平反转
	SIF_InitStruct.SIF_DONE_VLD = DISABLE;		// 无结束信号
	SIF_InitStruct.SIF_SYNC_VLD = ENABLE;		// 有同步信号
	SIF_InitStruct.SIF_RATIO = DISABLE;			// 数据占空比 2：1
	SIF_InitStruct.SIF_MSB = ENABLE;			// 数据传送顺序 高字节在前
	SIF_InitStruct.SIF_EN = ENABLE;				// SIF模块使能
	SIF_InitStruct.SIF_TOSC = 46;				// 时基设置 47 * 333 = 15.67US
	SIF_InitStruct.SIF_TSTH1 = 999;				// 同步时长 1000 * SIF_TOSC * 32
	SIF_InitStruct.SIF_TDTH1 = 0;				// 结束信号时长 1MS
	SIF_InitStruct.SIF_IRQ_IF = ENABLE;			// 有SIF中断标志位
	SIF_InitStruct.SIF_DMA_EN = ENABLE;			// DMA传输使能
	SIF_InitStruct.SIF_IRQ_EN = DISABLE;		// SIF中断关闭

	SIF_Init(SIF0, &SIF_InitStruct);

  @endcode
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author      <th>Description
 * <tr><td>2023年2月12日 <td>1.1     <td>ywx   <td>修改
 * </table>
 */

void SIF_Init(SIF_RegTypeDef *SIFx, SIF_InitTypeDef *SIFInitStruct)
{
	SIFx->SIFx_TOSC = SIFInitStruct->SIF_TOSC;
	SIFx->SIFx_TSTH1 = SIFInitStruct->SIF_TSTH1;
	SIFx->SIFx_TDTH1 = SIFInitStruct->SIF_TDTH1;
	SIFx->SIFx_IRQ = (SIFInitStruct->SIF_IRQ_EN << 0) | (SIFInitStruct->SIF_DMA_EN << 1) | (SIFInitStruct->SIF_IRQ_IF << 4);

	SIFx->SIFx_CFG = (SIFInitStruct->SIF_EN << 0) | (SIFInitStruct->SIF_MSB << 1) | (SIFInitStruct->SIF_RATIO << 2) |
					 (SIFInitStruct->SIF_SYNC_VLD << 3) | (SIFInitStruct->SIF_DONE_VLD << 4) |
					 (SIFInitStruct->SIF_SYNC_PULSE << 5) | (SIFInitStruct->SIF_SYNC << 6) | (SIFInitStruct->SIF_DONE << 7);

	SYS_ModuleClockCmd(SYS_Module_SIF0, ENABLE); // HALL时钟使能
}

/**
 *@brief @b 函数名称:  void SIF_Timebase_set(u32 tosc)
 *@brief @b 功能描述:   设置SIF传输时基
 *@see被引用内容：
 *@param输入参数：       tosc  ：时基系数
 *@param输出参数：       无
 *@return返 回 值：      无
 *@note其它说明：        无
 *@warning              无
 *@par 示例代码：
 *@code
  @endcode
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2023年2月12日 <td>1.1     <td>ywx   <td>修改
 * </table>
 */
void SIF_Timebase_set(u32 tosc)
{
	SIF0->SIFx_TOSC = tosc;
}

/**
 *@brief @b 函数名称:  void SIF_Timebase_set(u32 tosc)
 *@brief @b 功能描述:   设置信号通信方式
 *@see被引用内容：
 *@param输入参数：       tsh tsl ：同步信号周期
 *                      tdh tdl ：结束信号周期
 *@param输出参数：       无
 *@return返 回 值：      无
 *@note其它说明：        无
 *@warning              无
 *@par 示例代码：
 *@code
  @endcode
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2023年2月12日 <td>1.1     <td>ywx   <td>修改
 * </table>
 */
void SIF_TH_set(u32 tsh, u32 tdh)
{
	SIF0->SIFx_TSTH1 = tsh;
	SIF0->SIFx_TDTH1 = tdh;
}

/**
 *@brief @b 函数名称:  void SIF_Senddata(u8 Data)
 *@brief @b 功能描述:   传输数据设置
 *@see被引用内容：
 *@param输入参数：       Data :传输的数据
 *@param输出参数：       无
 *@return返 回 值：      无
 *@note其它说明：        无
 *@warning              无
 *@par 示例代码：
 *@code
  @endcode
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2023年2月12日 <td>1.1     <td>ywx   <td>修改
 * </table>
 */
void SIF_Senddata(u8 Data)
{
	REG32(SIF0_BASE + 0x14) = Data;
}

/**
 *@brief @b 函数名称:  void SIF_DMA_Enable(void)
 *@brief @b 功能描述:   SIF DMA传输请求使能
 *@see被引用内容：
*@param输入参数：       state : ENABLE/DIABLE
 *@param输出参数：       无
 *@return返 回 值：      无
 *@note其它说明：        无
 *@warning              无
 *@par 示例代码：
 *@code
  @endcode
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2023年2月12日 <td>1.1     <td>ywx   <td>修改
 * </table>
 */
void SIF_DMA_IsEnable(u8 state)
{
	if (state == ENABLE)
	{
		SIF0->SIFx_IRQ |= SIF_DMA_Enable;
	}
	else
	{
		SIF0->SIFx_IRQ &= ~SIF_DMA_Enable;
	}
}

/**
 *@brief @b 函数名称:  void SIF_DMA_Enable(void)
 *@brief @b 功能描述:   SIF DMA传输请求使能
 *@see被引用内容：
*@param输入参数：       state : ENABLE/DIABLE
 *@param输出参数：       无
 *@return返 回 值：      无
 *@note其它说明：        无
 *@warning              无
 *@par 示例代码：
 *@code
  @endcode
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2023年2月12日 <td>1.1     <td>ywx   <td>修改
 * </table>
 */
void SIF_Irq_IsEnable(u8 state)
{
	if (state == ENABLE)
	{
		SIF0->SIFx_IRQ |= SIF_IE_Enable;
	}
	else
	{
		SIF0->SIFx_IRQ &= ~SIF_IE_Enable;
	}
}

/**
 *@brief @b 函数名称:  void SIF_Clear_Irq()
 *@brief @b 功能描述:   清除SIF模块标志位
 *@see被引用内容：
*@param输入参数：        无
 *@param输出参数：       无
 *@return返 回 值：      无
 *@note其它说明：        无
 *@warning              无
 *@par 示例代码：
 *@code
  @endcode
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2023年2月12日 <td>1.1     <td>ywx   <td>修改
 * </table>
 */
void SIF_Clear_Irq(void)
{
	SIF0->SIFx_IRQ |= BIT4;
}
