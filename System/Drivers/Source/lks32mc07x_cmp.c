/**
 * @file
 * @copyright (C)2015, LINKO SEMICONDUCTOR Co.ltd
 * @brief 文件名称： lks32mc07x_cmp.c\n
 * 文件标识： 无 \n
 * 内容摘要： cmp外设驱动程序 \n
 * 其它说明： 无 \n
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2023年02月22日 <td>1.0     <td>Olive Wang     <td>创建
 * </table>
 */
#include "lks32mc07x_cmp.h"
#include "lks32mc07x.h"
#include "string.h"
#include "lks32mc07x_sys.h"

/**
 *@brief @b 函数名称:   CMP_Init(CMP_InitTypeDef* this)
 *@brief @b 功能描述:   CMP初始化
 *@see被调用函数：      SYS_AnalogModuleClockCmd()
 *@param输入参数：      CMP_InitTypeDef
 *@param输出参数：      无
 *@return返 回 值：     无
 *@note其它说明：       无
 *@warning             无
 *@par 示例代码：
 *@code
  CMP_InitTypeDef CMP_InitStre;
  CMP_StructInit(&CMP_InitStre);

  CMP_InitStre.CLK_COM_DIV = 0;									// 比较器共用滤波时钟分频
  CMP_InitStre.FT = DISABLE;										// 比较器快速比较
  CMP_InitStre.HYS = CMP_HYS_20mV;							// 比较器滞回电压

  CMP_InitStre.CMP0.SELP = CMP0_SELP_IP1; 		  // 比较器0正端信号选择
  CMP_InitStre.CMP0.SELN = CMP_SELN_REF; 				// 比较器0负端信号选择
  CMP_InitStre.CMP0.RE = DISABLE;								// 比较器0DMA失能
  CMP_InitStre.CMP0.POL= CMP_HIGH_LEVEL;				// 比较器0高电平有效
  CMP_InitStre.CMP0.IRQ_TRIG = IRQ_LEVEL_TRIG_MODE; // 比较器0电平触发中断模式
  CMP_InitStre.CMP0.IN_EN = ENABLE; 			 			// 比较器0信号输入使能
  CMP_InitStre.CMP0.IE = ENABLE;  							// 比较器0信号中断使能
  CMP_InitStre.CMP0.FIL_CLK_DIV16 = 2; 					// 即滤波宽度=tclk 周期*16*CMP_FltCnt (CMP_FltCnt分频系数,0~15)
  CMP_InitStre.CMP0.FIL_CLK_DIV2 = 2;  					// 比较器 2/1/0 滤波时钟使能
  CMP_InitStre.CMP0.CLK_EN = ENABLE;						//比较器时钟使能
  CMP_InitStre.CMP0.EN = ENABLE;       				  // 比较器0开关 操作SYS_AFE_REG5

  CMP_Init(&CMP_InitStre);// 比较器初始化
  @endcode
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author      <th>Description
 * <tr><td>2023年02月22日 <td>1.0     <td>Olive Wang       <td>创建
 * </table>
 */
void CMP_Init(CMP_InitTypeDef *this)
{
  SYS_WR_PROTECT = 0x7A83;

  SYS_AFE_REG1 |= this->FT; /* 快速比较，Enable后 30nS */

  SYS_AFE_REG2 |= (this->CMP2.SELP << 14);

  SYS_AFE_REG3 |= (this->CMP1.SELP << 12) | (this->CMP1.SELN << 4) | (this->CMP0.SELP << 8) | (this->CMP0.SELN << 2) |
                  (this->HYS << 7) | (this->CMP2.SELN);

  SYS_AFE_REG5 |= (this->CMP2.EN << 11) | (this->CMP1.EN << 7) | (this->CMP0.EN << 6);

  SYS_WR_PROTECT = 0x0000;

  CMP->IE = (this->CMP2.RE << 10) | (this->CMP1.RE << 9) | (this->CMP0.RE << 8) |
            (this->CMP2.IE << 2) | (this->CMP1.IE << 1) | (this->CMP0.IE); // 中断

  CMP->TCLK = (this->CLK_COM_DIV << 24) |
              (this->CMP2.FIL_CLK_DIV16 << 20) | (this->CMP2.FIL_CLK_DIV2 << 16) |
              (this->CMP1.FIL_CLK_DIV16 << 12) | (this->CMP1.FIL_CLK_DIV2 << 8) |
              (this->CMP0.FIL_CLK_DIV16 << 4) | (this->CMP0.FIL_CLK_DIV2) |
              (this->CMP2.CLK_EN << 19) | (this->CMP1.CLK_EN << 11) | (this->CMP0.CLK_EN << 3);

  CMP->CFG = (this->CMP2.IRQ_TRIG << 10) |
             (this->CMP2.IN_EN << 9) | (this->CMP2.POL << 8) |
             (this->CMP1.W_PWM_POL << 7) | (this->CMP1.IRQ_TRIG << 6) |
             (this->CMP1.IN_EN << 5) | (this->CMP1.POL << 4) |
             (this->CMP0.W_PWM_POL << 3) | (this->CMP0.IRQ_TRIG << 2) |
             (this->CMP0.IN_EN << 1) | (this->CMP0.POL);

  CMP->BLCWIN = (this->CMP1.CHN3P_PWM_EN << 7) | (this->CMP1.CHN2P_PWM_EN << 6) |
                (this->CMP1.CHN1P_PWM_EN << 5) | (this->CMP1.CHN0P_PWM_EN << 4) |
                (this->CMP0.CHN3P_PWM_EN << 3) | (this->CMP0.CHN2P_PWM_EN << 2) |
                (this->CMP0.CHN1P_PWM_EN << 1) | (this->CMP0.CHN0P_PWM_EN);

  CMP->IF = 3; // 清零标志位
}

/**
 *@brief @b 函数名称:   void CMP_StructInit(CMP_InitTypeDef* CMP_InitStruct)
 *@brief @b 功能描述:   ADC结构体初始化
 *@see被调用函数：       无
 *@param输入参数：       CMP_InitTypeDef
 *@param输出参数：      无
 *@return返 回 值：     无
 *@note其它说明：       无
 *@warning             无
 *@par 示例代码：
 *@code
            CMP_StructInit CMP_InitStructure;
        CMP_StructInit(&CMP_InitStructure); //初始化结构体
  @endcode
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author      <th>Description
 * <tr><td>2023年02月22日 <td>1.0     <td>Olive Wang       <td>创建
 * </table>
 */
void CMP_StructInit(CMP_InitTypeDef *CMP_InitStruct)
{

  memset(CMP_InitStruct, 0, sizeof(CMP_InitTypeDef));
}

/**
 *@brief @b 函数名称:  void CMP_Cmd(u8 CMP_CHN_x,FuncState state)
 *@brief @b 功能描述:   CMP时钟使能
 *@see被调用函数：       无
 *@param输入参数：       CMP_CHN_x：CMP_CHN_0/CMP_CHN_1/CMP_CHN_2,state：ENABLE/DISABLE
 *@param输出参数：      无
 *@return返 回 值：     无
 *@note其它说明：       无
 *@warning             无
 *@par 示例代码：
 *@code
            CMP_Cmd(CMP_CHN_0,ENABLE);//CMP0使能
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author      <th>Description
 * <tr><td>2023年02月22日 <td>1.0     <td>Olive Wang       <td>创建
 * </table>
 */
void CMP_Cmd(u8 CMP_CHN_x, FuncState state)
{
  if (CMP_CHN_0 == CMP_CHN_x)
  {
    SYS_AnalogModuleClockCmd(SYS_AnalogModule_CMP0, state); // CMP0使能
  }
  else if (CMP_CHN_1 == CMP_CHN_x)
  {
    SYS_AnalogModuleClockCmd(SYS_AnalogModule_CMP1, state); // CMP1使能
  }
  else if (CMP_CHN_2 == CMP_CHN_x)
  {
    SYS_AnalogModuleClockCmd(SYS_AnalogModule_CMP2, state); // CMP2使能
  }
  SYS_ModuleClockCmd(SYS_Module_CMP, state); // 数字电路时钟使能
}

/**
 *@brief @b 函数名称:   u8 CMP_GetIRQFlag(u8 CMP_CHN_x)
 *@brief @b 功能描述:   读取比较器中断标志
 *@see被调用函数：       无
 *@param输入参数：       CMP_CHN_0，CMP_CHN_1即获取CMP0和CMP1中断标志位
 *@param输出参数：       无
 *@return返 回 值：      TIM中断标志0/1
 *@note其它说明：        无
 *@warning              无
 *@par 示例代码：
 *@code
             if(CMP_GetIRQFlag(CMP1))//获取CMP1中断标志位
              {
                CMP_ClearIRQFlag(CMP1);//清除CMP1中断标志位
              }
  @endcode
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author      <th>Description
 * <tr><td>2023年02月22日 <td>1.0        <td>Olive Wang         <td>创建
 * </table>
 */
u8 CMP_GetIRQFlag(u8 CMP_CHN_x)
{
  if (CMP->IF & (BIT0 << CMP_CHN_x))
  {
    return 1;
  }
  else
  {
    return 0;
  }
}
/**
 *@brief @b 函数名称:   void CMP_ClearIRQFlag(u8 CMP_CHN_x)
 *@brief @b 功能描述:   清除TIM中断标志
 *@see被调用函数：       无
 *@param输入参数：       CMP_CHN_0，CMP_CHN_1即获取CMP0和CMP1中断标志位
 *@param输出参数：       无
 *@return返 回 值：      无
 *@note其它说明：        无
 *@warning              无
 *@par 示例代码：
 *@code
             if(CMP_GetIRQFlag(CMP_CHN_1))//获取CMP1中断标志位
              {
                CMP_ClearIRQFlag(CMP_CHN_1);//清除CMP1中断标志位
              }
  @endcode
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author      <th>Description
 * <tr><td>2023年02月22日 <td>1.0       <td>Olive Wang         <td>创建
 * </table>
 */

void CMP_ClearIRQFlag(u8 CMP_CHN_x)
{
  CMP->IF = (BIT0 << CMP_CHN_x);
}

/**
 *@brief @b 函数名称:   uint8_t CMP_GetFilterValue(void)
 *@brief @b 功能描述:   读取滤波后的CMP值
 *@see被调用函数：       无
 *@param输入参数：       无
 *@param输出参数：       无
 *@return返 回 值：      无
 *@note其它说明：        无
 *@warning              无
 *@par 示例代码：
 *@code
             u8 cmpVal;
              cmpVal = CMP_GetFilterValue();
  @endcode
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author      <th>Description
 * <tr><td>2023年02月22日 <td>1.0       <td>Olive Wang         <td>创建
 * </table>
 */
uint8_t CMP_GetFilterValue(void)
{
  return ((CMP_DATA >> 8) & 0x0007);
}
/**
 *@brief @b 函数名称:   uint8_t CMP_GetValue(void)
 *@brief @b 功能描述:   读取未滤波的CMP值
 *@see被调用函数：       无
 *@param输入参数：       无
 *@param输出参数：       无
 *@return返 回 值：      无
 *@note其它说明：        无
 *@warning              无
 *@par 示例代码：
 *@code
             u8 cmpVal;
              cmpVal = CMP_GetValue();
  @endcode
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author      <th>Description
 * <tr><td>2023年02月22日 <td>1.0       <td>Olive Wang         <td>创建
 * </table>
 */
uint8_t CMP_GetValue(void)
{
  return (CMP_DATA & 0x0007);
}
/************************ (C) COPYRIGHT LINKO SEMICONDUCTOR **********************/
/* ------------------------------END OF FILE------------------------------------ */
