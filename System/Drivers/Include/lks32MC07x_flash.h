/**
 * @file 
 * @copyright (C)2015, LINKO SEMICONDUCTOR Co.ltd
 * @brief 文件名称： LKS32MC07x_flash.h\n
 * 文件标识： 无 \n
 * 内容摘要： FLASH外设驱动程序 \n
 * 其它说明： 无 \n
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2023年2月22日 <td>1.0     <td>HuangMG    <td>创建
 * </table>
 */
#ifndef __lks32mc07x_FLASH__
#define __lks32mc07x_FLASH__
#include "lks32mc07x_lib.h"

#define Flash_MAIN 0x000  /**< Flash的mian区域定义*/
#define Flash_NVR  0x800  /**< Flash的mian区域定义*/

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

extern volatile u32 erase_flag; 
extern volatile u32 progm_flag; 

int ProgramPage(u32 adr, u32 sz, u8 *buf, u16 nvr);
void EraseSector(u32 adr, u16 nvr);
void Read_More_Flash(u32 adr, u32 sz, u32 *buf, u16 nvr);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif

