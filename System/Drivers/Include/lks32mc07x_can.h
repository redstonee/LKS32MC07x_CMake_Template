/**
 * @file
 * @copyright (C)2015, LINKO SEMICONDUCTOR Co.ltd
 * @brief 文件名称： LKS32MC07x_can.h\n
 * 文件标识： 无 \n
 * 内容摘要： CAN外设驱动程序 \n
 * 其它说明： 无 \n
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2023年2月22日 <td>1.0     <td>HuangMG    <td>创建
 * </table>
 */
#ifndef _LKS32MC07X_CAN_H_
#define _LKS32MC07X_CAN_H_

///< Includes ------------------------------------------------------------------
#include "lks32mc07x_lib.h"

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

	typedef struct
	{
		u32 id;		/**<接收ID号 */
		u8 len;		/**<接收数据长度 */
		u8 ide;		/**<接收数据类型0标准/1扩展帧 */
		u8 rtr;		/**<接收数据类型0数据帧/1远程帧*/
		u8 TX[8];	/**<数据发生缓冲区 */
		u8 RX[8];	/**<接收数据缓冲区*/
		u32 rx_sta; /**<接收错误标志位*/
	} can_parameter;

	extern can_parameter can_par;

	void CAN_Init(u8 BTR3, u8 BTR2, u8 BTR1, u8 BTR0);
	u8 My_CAN_Send_Msg(u32 id, u8 ide, u8 rtr, u8 *msg, u8 len);
	void ID0_Filter(u32 id, u32 MASK, u8 ide);
	void ID1_Filter(u32 id, u32 MASK, u8 ide);
	void ID2_Filter(u32 id, u32 MASK, u8 ide);
	void ID3_Filter(u32 id, u32 MASK, u8 ide);
	u8 CAN_Receive_Msg(u32 *id, u8 *len, u8 *ide, u8 *rtr, u8 *buf);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif
