/**
 * @file
 * @copyright (C)2015, LINKO SEMICONDUCTOR Co.ltd
 * @brief 文件名称： lks32mc07x_can.c\n
 * 文件标识： 无 \n
 * 内容摘要： CAN外设驱动程序 \n
 * 其它说明： 无 \n
 *@par 修改日志:
 * <table>
 * <tr><th>Date	       <th>Version   <th>Author  <th>Description
 * <tr><td>2023年2月23日 <td>1.0     <td>HuangMG     <td>创建
 * </table>
 */
#include "lks32mc07x_can.h"
#include "lks32mc07x_sys.h"
#include "string.h"

can_parameter can_par =
	{
		0x00,
		0x00,
		0x00,
		0x00,
		{0, 0},
		{0, 0},
		0x00,
};

/*******************************************************************************
函数名称: void CAN_Initl(u8 BTR3,u8 BTR2,u8 BTR1,u8 BTR0)
功能描述: CAN初始化函数,采用2.0B协议
操作的表:

	输入参数: BTR0    S_SEG_1:段时间段 1 时间单元设定
		   BTR1    S_SEG_2：段时间段 2 时间单元设定
		   BTR2    S_SJW ： 再同步补偿宽度时间设定
					 BTR3    S_PRESC ：TQ 预分频率设定值
输出参数: 无
返回值:   无
其它说明:
修改日期     版本号     修改人    修改内容
-----------------------------------------------------------------------------
2023/02/13   V1.0     HuangMG     创建
*******************************************************************************/
/**
 *@brief @b 函数名称:   void CAN_Init(u8 BTR3,u8 BTR2,u8 BTR1,u8 BTR0)
 *@brief @b 功能描述:   CAN初始化函数,采用2.0B协议
 *@see被调用函数：      无
 *@param输入参数：
   波特率    AN_SBAUD.PRESC[7:0]   CAN_SBAUD.SJW[6:0]  CAN_SBAUD.SEG2[6:0] CAN_SBAUD.SEG1[7:0] Sample Poin\n
	1Mbps             0x05                0x02                0x05               0x08             63% \n
	800Kbps           0x0B                0x01                0x03               0x04             60% \n
	666Kbps           0x0B                0x01                0x03               0x06             67% \n
	500Kbps           0x0B                0x02                0x05               0x08             63% \n
	400Kbps           0x0B                0x02                0x06               0x0B             65% \n
	250Kbps           0x17                0x02                0x05               0x08             63% \n
	200Kbps           0x17                0x02                0x06               0x0B             65% \n
	125Kbps           0x2F                0x02                0x05               0x08             63% \n
	100Kbps           0x2F                0x02                0x06               0x0B             65% \n
	80Kbps            0x35                0x02                0x06               0x0B             65% \n
	50Kbps            0x5F                0x02                0x06               0x0B             65% \n
	40Kbps            0x77                0x02                0x06               0x0B             65% \n
	25Kbps            0xBF                0x02                0x06               0x0B             65% \n
	20Kbps            0xEF                0x02                0x06               0x0B             65% \n
	10Kbps            0xEF                0x06                0x0D               0x18             65% \n
	05Kbps            0xEF                0x0D                0x1B               0x32             65%
 *@param输出参数：      无
 *@return返 回 值：     无
 *@note其它说明：       无
 *@warning             无
 *@par 示例代码：
 *@code
			 CAN_Init(0x0B,0x02,0x05,0x08);    //CAN波特率500Khz
  @endcode
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author      <th>Description
 * <tr><td>2023年2月23日  <td>1.0      <td>HuangMG        <td>创建
 * </table>
 */
void CAN_Init(u8 BTR3, u8 BTR2, u8 BTR1, u8 BTR0)
{
	SYS_WR_PROTECT = 0x7a83; // 关闭写保护

	SYS_SFT_RST |= BIT19;  // 复位CAN
	SYS_SFT_RST &= ~BIT19; // 释放CAN复位

	SYS_CLK_FEN |= BIT19; // 使能CAN时钟

	CAN_CFG_STAT |= 1 << 7; // 复位模式

	CAN_ACFEN = 0x00;											  // 关闭ID滤波功能
	CAN_SBAUD = BTR0 | (BTR1 << 8) | (BTR2 << 16) | (BTR3 << 24); // 波特率设置
	CAN_CFG_STAT &= ~(1 << 7);									  // 正常输出模式
	CAN_TCMD = 0x00;
	CAN_RTIE |= 1 << 7;	  // RFIFO有新的数据被接收到，中断源使能
	CAN_RTIE |= 1 << 1;	  // 错误中断使能
	SYS_WR_PROTECT = 0x0; // 打开写保护
}

/**
 *@brief @b 函数名称:   u8 My_CAN_Send_Msg(u32 id,u8 ide,u8 rtr, u8 *msg,u8 len)
 *@brief @b 功能描述:   CAN轮询发送数据程序  采用2.0B协议
 *@see被调用函数：       无
 *@param输入参数：
 *                      id: 发送id \n
 *                      ide: 标准/扩展帧
 *		                  rtr：远程帧/数据帧 \n
 *		                  *msg: 发送的数据
 *                      len:发送字节长度 \n
 *@param输出参数：       无
 *@return返 回 值：      0：发送成功 !0：发送失败
 *@note其它说明：
 *                      1、id:标准ID(11位)/扩展ID(11位+18位) \n
 *                      2、ide:0,标准帧;1,扩展帧 \n
 *                      3、rtr:0,数据帧;1,远程帧。
 *@warning              无
 *@par 示例代码：
 *@code
	  示例1：
			  u8 Can_TX[8] = {0x81, 0x23, 0x33, 0x44, 0x15, 0x26, 0x37, 0x48};
		   // 发送数据 ID:0x03,标准帧,数据帧，数据，数据长度8字节
			   My_CAN_Send_Msg(0x5A, 0, 0, Can_TX, 8);
	  示例2：
		   u8 Can_TX[8] = {0x81, 0x23, 0x33, 0x44, 0x15, 0x26, 0x37, 0x48};
		   // 发送数据 ID:0x03,扩展帧,数据帧，数据，数据长度8字节
			   My_CAN_Send_Msg(0X10005A5A, 1, 0, Can_TX, 8);
  @endcode
 *@par 修改日志:增加自测模式发送数据功能
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author     <th>Description
 * <tr><td>2023年2月23日  <td>1.0      <td>HuangMG        <td>创建
 * </table>
 */
u8 My_CAN_Send_Msg(u32 id, u8 ide, u8 rtr, u8 *msg, u8 len)
{
	u8 frame_inf = 0;
	u16 i = 0;
	CAN_CFG_STAT &= ~(1 << 7); // 正常输出模式
	if (!(CAN_TCMD & BIT4))	   // 本CAN设备，发送空闲
	{
		frame_inf |= ide << 7;	 // 0标准/1扩展帧
		frame_inf |= rtr << 6;	 // 0,数据帧;1,遥控帧
		frame_inf |= len << 0;	 // 发送数据长度
		CAN_TBUF_01 = frame_inf; // 发送TX帧信息
		if (0 == ide)			 // 标准帧
		{
			id &= 0x7ff;
			// 发送接收寄存器1
			CAN_TBUF_00 = id;												  // TX ID
			CAN_TBUF_02 = msg[0] | msg[1] << 8 | msg[2] << 16 | msg[3] << 24; // TX DATA0123
			CAN_TBUF_03 = msg[4] | msg[5] << 8 | msg[6] << 16 | msg[7] << 24; // TX DATA4567
		}
		else // 扩展帧
		{
			id &= 0X1FFFFFFF;
			// 发送接收寄存器1
			CAN_TBUF_00 = id;												  // TX ID
			CAN_TBUF_02 = msg[0] | msg[1] << 8 | msg[2] << 16 | msg[3] << 24; // TX DATA0123
			CAN_TBUF_03 = msg[4] | msg[5] << 8 | msg[6] << 16 | msg[7] << 24; // TX DATA4567
		}
		CAN_TCMD |= 1 << 4;		// CAN 发送传输请求
		while (CAN_TCMD & BIT4) // 最近一次是否传输完成
		{
			if ((i++) >= 0xfff)
			{
				return 0xff; // 发送失败
			}
		};
		return 0; // 发送完成
	}
	else // TFIFO非空
	{
		return 0xff; // 发送失败
	}
}

/*******************************************************************************
 函数名称：    void SoftDelay(void)
 功能描述：    软件延时函数
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2020/8/5      V1.0           Howlet Li          创建
 *******************************************************************************/
static void Delay(u32 cnt)
{
	volatile u32 t_cnt;

	for (t_cnt = 0; t_cnt < cnt; t_cnt++)
	{
		__NOP();
	}
}

/**
 *@brief @b 函数名称:   void ID0_Filter(u32 id, u32 MASK, u8 ide)
 *@brief @b 功能描述:   CAN ID0滤波设置 采用2.0B协议
 *@see被调用函数：       无
 *@param输入参数：
 *                      id：ID值 \n
 *                      MASK：ID屏蔽位\n
 *		                ide:0,标准帧;1,扩展帧，为0 11位ID长度 为1 29位ID长度，
 *@param输出参数：       无
 *@return返 回 值：      无
 *@note其它说明：        无
 *@warning              无
 *@par 示例代码：
 *@code
			 ID0_Filter(0x02,0x000,1);    //开启ID0接收滤波，接收id=0x02，扩展帧
  @endcode
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author     <th>Description
 * <tr><td>2023年2月23日  <td>1.0      <td>HuangMG        <td>创建
 * </table>
 */
void ID0_Filter(u32 id, u32 MASK, u8 ide)
{
	CAN_CFG_STAT |= 1 << 7; // 复位模式

	CAN_ACFEN |= BIT0;		  // ACF0 is Enabled
	CAN_ACFCTRL = 0x00000020; // SELMASK==1 MASK
	CAN_ACF |= BIT30;
	if (ide == 0)
	{
		CAN_ACF &= ~BIT29; // 接收标准帧
	}
	else
	{
		CAN_ACF |= BIT29; // 接收扩展帧
	}
	CAN_ACF &= ~0x1FFFFFFF;
	CAN_ACF |= (MASK & 0x1FFFFFFF); // ACF0 Mask Disabled, All bits should be compared
	CAN_ACFCTRL = 0x00;				// ID滤波器地址 指向 ACF_0
	CAN_ACF &= ~0x1FFFFFFF;
	CAN_ACF |= (id & 0x1FFFFFFF); // ACF0 ID Enabled
	Delay(100);
	CAN_CFG_STAT &= ~(1 << 7); // 正常输出模式
}
/**
 *@brief @b 函数名称:   void ID1_Filter(u32 id, u32 MASK, u8 ide)
 *@brief @b 功能描述:   CAN ID1滤波设置 采用2.0B协议
 *@see被调用函数：       无
 *@param输入参数：
 *                      id：ID值 \n
 *                      MASK：ID屏蔽位\n
 *		                ide:0,标准帧;1,扩展帧，为0 11位ID长度 为1 29位ID长度，
 *@param输出参数：       无
 *@return返 回 值：      无
 *@note其它说明：        无
 *@warning              无
 *@par 示例代码：
 *@code
			 ID1_Filter(0x02,0x000,1);    //开启ID0接收滤波，接收id=0x02，扩展帧
  @endcode
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author     <th>Description
 * <tr><td>2023年2月23日  <td>1.0      <td>HuangMG        <td>创建
 * </table>
 */
void ID1_Filter(u32 id, u32 MASK, u8 ide)
{
	CAN_CFG_STAT |= 1 << 7; // 复位模式

	CAN_ACFEN |= BIT1;		  // ACF1 is Enabled
	CAN_ACFCTRL = 0x00000021; // SELMASK==1 MASK
	CAN_ACF |= BIT30;
	if (ide == 0)
	{
		CAN_ACF &= ~BIT29; // 接收标准帧
	}
	else
	{
		CAN_ACF |= BIT29; // 接收扩展帧
	}
	CAN_ACF &= ~0x1FFFFFFF;
	CAN_ACF |= (MASK & 0x1FFFFFFF); // ACF0 Mask Disabled, All bits should be compared
	CAN_ACFCTRL = 0x01;				// SELMASK==0 ID
	CAN_ACF &= ~0x1FFFFFFF;
	CAN_ACF |= (id & 0x1FFFFFFF); // ACF0 ID Enabled
	Delay(100);
	CAN_CFG_STAT &= ~(1 << 7); // 正常输出模式
}
/**
 *@brief @b 函数名称:   void ID2_Filter(u32 id, u32 MASK, u8 ide)
 *@brief @b 功能描述:   CAN ID2滤波设置 采用2.0B协议
 *@see被调用函数：       无
 *@param输入参数：
 *                      id：ID值 \n
 *                      MASK：ID屏蔽位\n
 *		                ide:0,标准帧;1,扩展帧，为0 11位ID长度 为1 29位ID长度，
 *@param输出参数：       无
 *@return返 回 值：      无
 *@note其它说明：        无
 *@warning              无
 *@par 示例代码：
 *@code
			 ID2_Filter(0x02,0x000,1);    //开启ID0接收滤波，接收id=0x02，扩展帧
  @endcode
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author     <th>Description
 * <tr><td>2023年2月23日  <td>1.0      <td>HuangMG        <td>创建
 * </table>
 */
void ID2_Filter(u32 id, u32 MASK, u8 ide)
{
	CAN_CFG_STAT |= 1 << 7; // 复位模式

	CAN_ACFEN |= BIT2;		  // ACF2 is Enabled
	CAN_ACFCTRL = 0x00000022; // SELMASK==1 MASK
	CAN_ACF |= BIT30;
	if (ide == 0)
	{
		CAN_ACF &= ~BIT29; // 接收标准帧
	}
	else
	{
		CAN_ACF |= BIT29; // 接收扩展帧
	}
	CAN_ACF &= ~0x1FFFFFFF;
	CAN_ACF |= (MASK & 0x1FFFFFFF); // ACF0 Mask Disabled, All bits should be compared
	CAN_ACFCTRL = 0x02;				// SELMASK==0 ID
	CAN_ACF &= ~0x1FFFFFFF;
	CAN_ACF |= (id & 0x1FFFFFFF); // ACF2 ID Enabled
	Delay(100);
	CAN_CFG_STAT &= ~(1 << 7); // 正常输出模式
}

/**
 *@brief @b 函数名称:   void ID3_Filter(u32 id, u32 MASK, u8 ide)
 *@brief @b 功能描述:   CAN ID3滤波设置 采用2.0B协议
 *@see被调用函数：       无
 *@param输入参数：
 *                      id：ID值 \n
 *                      MASK：ID屏蔽位\n
 *		                ide:0,标准帧;1,扩展帧，为0 11位ID长度 为1 29位ID长度，
 *@param输出参数：       无
 *@return返 回 值：      无
 *@note其它说明：        无
 *@warning              无
 *@par 示例代码：
 *@code
			 ID3_Filter(0x02,0x000,1);    //开启ID0接收滤波，接收id=0x02，扩展帧
  @endcode
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author     <th>Description
 * <tr><td>2023年2月23日  <td>1.0      <td>HuangMG        <td>创建
 * </table>
 */
void ID3_Filter(u32 id, u32 MASK, u8 ide)
{
	CAN_CFG_STAT |= 1 << 7; // 复位模式

	CAN_ACFEN |= BIT3;		  // ACF3 is Enabled
	CAN_ACFCTRL = 0x00000023; // SELMASK==1 MASK
	CAN_ACF |= BIT30;
	if (ide == 0)
	{
		CAN_ACF &= ~BIT29; // 接收标准帧
	}
	else
	{
		CAN_ACF |= BIT29; // 接收扩展帧
	}
	CAN_ACF &= ~0x1FFFFFFF;
	CAN_ACF |= (MASK & 0x1FFFFFFF); // ACF0 Mask Disabled, All bits should be compared
	CAN_ACFCTRL = 0x03;				// SELMASK==0 ID
	CAN_ACF &= ~0x1FFFFFFF;
	CAN_ACF |= (id & 0x1FFFFFFF); // ACF3 ID Enabled
	Delay(100);
	CAN_CFG_STAT &= ~(1 << 7); // 正常输出模式
}

/**
 *@brief @b 函数名称:   u8 CAN_Receive_Msg(u32* id,u8* len ,u8* ide,u8* rtr,u8 *buf)
 *@brief @b 功能描述:   CAN轮询接收数据程序
 *@see被调用函数：       无
 *@param输入参数：       无
 *@param输出参数：       id:  接收帧id \n
						len: 接收数据长度 \n
 *                      ide: 接收帧的类型，标准/扩展帧 \n
 *		                rtr：接收帧的类型，远程帧/数据帧 \n
 *		                *buf: 接收帧的数据存储缓存区
 *@return返 回 值：      0：接收完成 !0：接收失败
 *@note其它说明：
 *                      1、id:标准ID(11位)/扩展ID(11位+18位) \n
 *                      2、ide:0,标准帧;1,扩展帧 \n
 *                      3、rtr:0,数据帧;1,远程帧。
 *@warning              无
 *@par 示例代码：
 *@code
		 //can_par.id存储接收帧ID，can_par.len接收数据个数
			 can_par.ide存储接收帧类型标准/扩展帧，
			 can_par.rtr存储接收帧类型远程帧/数据帧，can_par.RX存储接收帧数据
		 CAN_Receive_Msg(&( can_par.id),&(can_par.len),&(can_par.ide),&(can_par.rtr),can_par.RX);
  @endcode
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author     <th>Description
 * <tr><td>2023年2月23日  <td>1.0      <td>HuangMG        <td>创建
 * </table>
 */
u8 CAN_Receive_Msg(u32 *id, u8 *len, u8 *ide, u8 *rtr, u8 *buf)
{
	u8 reg_inf;
	u8 tmep = 0;
	if (CAN_RCTRL != 0x00) /*Rx Buffer存有一帧或多帧数据，可以通过 RFIFO 寄存器读取*/
	{
		reg_inf = CAN_RBUF_01;
		if (reg_inf & BIT6)
		{
			*rtr = 1;
		}
		else
		{
			*rtr = 0;
		}
		*len = reg_inf & 0xf;
		if (reg_inf & BIT7) /*扩展帧*/
		{
			*ide = 1;
			*id = CAN_RBUF_00 & 0x1FFFFFFF;
		}
		else
		{ /*标准帧*/
			*ide = 0;
			*id = CAN_RBUF_00 & 0x7ff;
		}
		buf[0] = CAN_RBUF_02;
		buf[1] = CAN_RBUF_02 >> 8;
		buf[2] = CAN_RBUF_02 >> 16;
		buf[3] = CAN_RBUF_02 >> 24;
		buf[4] = CAN_RBUF_03;
		buf[5] = CAN_RBUF_03 >> 8;
		buf[6] = CAN_RBUF_03 >> 16;
		buf[7] = CAN_RBUF_03 >> 24;
		for (tmep = *len; tmep < 8; tmep++)
		{
			buf[tmep] = 0;
		}
		CAN_RCTRL |= BIT4; /*释放 Rx Buffer Slot*/
		return 0;
	}
	return 1;
}
