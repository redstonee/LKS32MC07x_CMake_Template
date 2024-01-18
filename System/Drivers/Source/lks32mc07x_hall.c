/**
 * @file
 * @copyright (C)2015, LINKO SEMICONDUCTOR Co.ltd
 * @brief 文件名称： lks32mc07x_hall.c\n
 * 文件标识： 无 \n
 * 内容摘要： HALL外设驱动程序 \n
 * 其它说明： 无 \n
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2023年02月23日 <td>1.0     <td>Olive Wang      <td>创建
 * </table>
 */
#include "lks32mc07x_hall.h"
#include "lks32mc07x_lib.h"
/**
 *@brief @b 函数名称:   void HALL_Init(HALL_InitTypeDef* HALL_InitStruct)
 *@brief @b 功能描述:   HALL初始化函数
 *@see被引用内容：      无
 *@param输入参数：      HALL_InitTypeDef HALL_InitStruct
 *@param输出参数：      无
 *@return返 回 值：     无
 *@note其它说明：       无
 *@warning             无
 *@par 示例代码：
 *@code
      HALL_InitTypeDef HALL_InitStruct;

    HALL_StructInit(&HALL_InitStruct);

    HALL_InitStruct.FilterLen = 512;                //Hall信号数字滤波长度 512个时钟周期
    HALL_InitStruct.ClockDivision = HALL_CLK_DIV8;   //设置Hall模块时钟分频系数
    HALL_InitStruct.Filter75_Ena = DISABLE;         // Hall信号滤波方式，7判5模式或者全1有效模式
    HALL_InitStruct.HALL_Ena = ENABLE;              // 模块使能
    HALL_InitStruct.Capture_IRQ_Ena = ENABLE;       // 捕捉中断使能
    HALL_InitStruct.OverFlow_IRQ_Ena = ENABLE;      // 超时中断使能
    HALL_InitStruct.CountTH = 960000;              // Hall模块计数模值，计数超过模值会产生超时中断
        HALL_InitStruct.softIE = ENABLE;								// 软件中断失能
    HALL_Init(&HALL_InitStruct);

  @endcode
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author      <th>Description
 * <tr><td>2023年02月23日 <td>1.0       <td>Olive Wang           <td>创建
 * </table>
 */
void HALL_Init(HALL_InitTypeDef *HALL_InitStruct)
{
    HALL->CFG = (HALL_InitStruct->FilterLen) | (HALL_InitStruct->ClockDivision << 16) | (HALL_InitStruct->Filter75_Ena << 20) | (HALL_InitStruct->HALL_Ena << 24) | (HALL_InitStruct->Capture_IRQ_Ena << 28) | (HALL_InitStruct->OverFlow_IRQ_Ena << 29) | (HALL_InitStruct->softIE << 30);
    HALL->TH = HALL_InitStruct->CountTH;
    HALL->INFO = 0;
}

/**
 *@brief @b 函数名称:   void HALL_StructInit(HALL_InitTypeDef* HALL_InitStruct)
 *@brief @b 功能描述:   HALL结构体初始化
 *@see被引用内容：       无
 *@param输入参数：       HALL_InitTypeDef  HALL_InitStruct
 *@param输出参数：       无
 *@return返 回 值：      无
 *@note其它说明：        无
 *@warning              无
 *@par 示例代码：
 *@code
            HALL_InitTypeDef HALL_InitStruct;
            HALL_StructInit(&HALL_InitStruct); //初始化结构体
  @endcode
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2023年02月23日 <td>1.0      <td>Olive Wang     <td>创建
 * </table>
 */
void HALL_StructInit(HALL_InitTypeDef *HALL_InitStruct)
{
    HALL_InitStruct->FilterLen = 1023;
    HALL_InitStruct->ClockDivision = HALL_CLK_DIV1;
    HALL_InitStruct->Filter75_Ena = ENABLE;
    HALL_InitStruct->HALL_Ena = ENABLE;
    HALL_InitStruct->Capture_IRQ_Ena = ENABLE;
    HALL_InitStruct->OverFlow_IRQ_Ena = DISABLE;
    HALL_InitStruct->CountTH = 1000;
    HALL_InitStruct->softIE = DISABLE;
}

/**
 *@brief @b 函数名称:   uint32_t HALL_GetFilterValue(void)
 *@brief @b 功能描述:   取得HALL值，滤波结果
 *@see被引用内容：       无
 *@param输入参数：       无
 *@param输出参数：       无
 *@return返 回 值：      经过滤波的HALL信号结果值，前三位有效，其它位恒为0
 *@note其它说明：        无
 *@warning              无
 *@par 示例代码：
 *@code
            uint32_t HALL_Value = 0;
            HALL_Value = HALL_GetFilterValue();//读取经过滤波的HALL结果值
  @endcode
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2023年02月23日 <td>1.0      <td>Olive Wang     <td>创建
 * </table>
 */
uint32_t HALL_GetFilterValue(void)
{
    return (HALL->INFO & 0x07);
}

/**
 *@brief @b 函数名称:   uint32_t HALL_GetCaptureValue(void)
 *@brief @b 功能描述:   取得HALL值，未滤波结果，即采样的原始HALL状态值
 *@see被引用内容：       无
 *@param输入参数：       无
 *@param输出参数：       无
 *@return返 回 值：      未滤波的HALL信号结果值，前三位有效，其它位恒为0
 *@note其它说明：        无
 *@warning              无
 *@par 示例代码：
 *@code
            uint32_t HALL_Value = 0;
            HALL_Value = HALL_GetCaptureValue();//读取未滤波的HALL结果值
  @endcode
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2023年02月23日 <td>1.0      <td>Olive Wang     <td>创建
 * </table>
 */
uint32_t HALL_GetCaptureValue(void)
{
    return (HALL->INFO >> 8) & 0x07;
}

/**
 *@brief @b 函数名称:   uint32_t HALL_GetCount(void)
 *@brief @b 功能描述:   读取实时HALL计数器值
 *@see被引用内容：       无
 *@param输入参数：       无
 *@param输出参数：       无
 *@return返 回 值：      实时HALL计数器值
 *@note其它说明：        无
 *@warning              无
 *@par 示例代码：
 *@code
            uint32_t HALL_Value = 0;
            HALL_Value = HALL_GetCount();//读取实时HALL计数器值
  @endcode
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2023年02月23日 <td>1.0      <td>Olive Wang     <td>创建
 * </table>
 */
uint32_t HALL_GetCount(void)
{
    return HALL->CNT;
}

/**
 *@brief @b 函数名称:   uint32_t HALL_IsCaptureEvent(void)
 *@brief @b 功能描述:   读取是否发生捕获事件标志
 *@see被引用内容：       无
 *@param输入参数：       无
 *@param输出参数：       无
 *@return返 回 值：     捕获事件标志，为HALL_CAPTURE_EVENT即对应标志位置位，为0即对应标志位未置位
 *@note其它说明：        无
 *@warning              无
 *@par 示例代码：
 *@code
            if(HALL_CAPTURE_EVENT == HALL_IsCaptureEvent())//读取HALL信号变化标志位
            {
            }
  @endcode
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2023年02月23日  <td>1.0     <td>Olive Wang     <td>创建
 * </table>
 */
uint32_t HALL_IsCaptureEvent(void)
{
    return (HALL->INFO & HALL_CAPTURE_EVENT);
}

/**
 *@brief @b 函数名称:   uint32_t HALL_IsCaptureEvent(void)
 *@brief @b 功能描述:   读取是否发生计时溢出事件标志
 *@see被引用内容：       无
 *@param输入参数：       无
 *@param输出参数：       无
 *@return返 回 值：     捕获事件标志，为HALL_OVERFLOW_EVENT即对应标志位置位，为0即对应标志位未置位
 *@note其它说明：        无
 *@warning              无
 *@par 示例代码：
 *@code
            if( HALL_OVERFLOW_EVENT == HALL_IsOverFlowEvent())//读取计时溢出标志位
            {
            }
  @endcode
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2023年02月23日  <td>1.0     <td>Olive Wang     <td>创建
 * </table>
 */
uint32_t HALL_IsOverFlowEvent(void)
{
    return (HALL->INFO & HALL_OVERFLOW_EVENT);
}

/**
 *@brief @b 函数名称:   uint32_t HALL_ClearIRQFlag(uint32_t tempFlag)
 *@brief @b 功能描述:   清除HALL中断标志位
 *@see被引用内容：       无
 *@param输入参数：
                        tempFlag: \n
 * <table>              <tr><th>HALL_CAPTURE_EVENT   <td>HALL信号变化中断 \n
 *                      <tr><th>HALL_OVERFLOW_EVENT  <td>HALL计数溢出中断
 * </table>
 *@param输出参数：       无
 *@return返 回 值：      无
 *@note其它说明：        无
 *@warning              无
 *@par 示例代码：
 *@code
            if(HALL_GetIRQFlag(HALL_CAPTURE_EVENT))//读取HALL信号变化中断标志位
            {
                HALL_ClearIRQFlag(HALL_CAPTURE_EVENT);//清除HALL信号变化中断标志位
            }
  @endcode
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2023年02月23日  <td>1.0     <td>Olive Wang     <td>创建
 * </table>
 */
void HALL_Clear_IRQ(uint32_t tempFlag)
{
    uint32_t temp = HALL->INFO & tempFlag;
    HALL->INFO = temp;
}
/**
 *@brief @b 函数名称:   uint32_t HALL_GetIRQFlag(uint32_t tempFlag)
 *@brief @b 功能描述:   读取HALL中断标志
 *@see被引用内容：       无
 *@param输入参数：
                        tempFlag: \n
 * <table>              <tr><th>HALL_CAPTURE_EVENT   <td>HALL信号变化中断 \n
 *                      <tr><th>HALL_OVERFLOW_EVENT  <td>HALL计数溢出中断
 * </table>
 *@param输出参数：       无
 *@return返 回 值：      HALL中断标志 为HALL_CAPTURE_EVENT即对应标志位置位，为0即对应标志位未置位
 *@note其它说明：        无
 *@warning              无
 *@par 示例代码：
 *@code
            if(HALL_CAPTURE_EVENT == HALL_GetIRQFlag(HALL_CAPTURE_EVENT))//读取HALL信号变化中断标志位
            {
            }
  @endcode
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2023年02月23日  <td>1.0     <td>Olive Wang     <td>创建
 * </table>
 */

uint32_t HALL_GetIRQFlag(uint32_t tempFlag)
{
    return (HALL->INFO & tempFlag);
}

/**
 *@brief @b 函数名称:   uint32_t HALL_SoftTrigger(void)
 *@brief @b 功能描述:   软件触发HALL信号变化中断
 *@see被引用内容：       无
 *@param输入参数：       无
 *@param输出参数：       无
 *@return返 回 值：      无
 *@note其它说明：        无
 *@warning              无
 *@par 示例代码：
 *@code
                            HALL_SoftTrigger();//软件触发HALL信号变化中断
  @endcode
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2023年02月23日  <td>1.0     <td>Olive Wang     <td>创建
 * </table>
 */

void HALL_SoftTrigger(void)
{
    HALL->INFO |= BIT18;
}
/**
 *@brief @b 函数名称:  void HALL_Cmd(FuncState state)
 *@brief @b 功能描述:   HALL时钟使能
 *@see被引用内容：       无
 *@param输入参数：
                        state: \n
 * <table>              <tr><th>ENABLE   <td>HALL使能 \n
 *                      <tr><th>DISABLE  <td>HALL失能
 * </table>
 *@param输出参数：       无
 *@return返 回 值：     无
 *@note其它说明：        无
 *@warning              无
 *@par 示例代码：
 *@code
                                HALL_Cmd(ENABLE);//HALL使能
  @endcode
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2023年02月23日  <td>1.0     <td>Olive Wang     <td>创建
 * </table>
 */
void HALL_Cmd(FuncState state)
{
    SYS_ModuleClockCmd(SYS_Module_HALL0, state); // HALL时钟使能
}

/************************ (C) COPYRIGHT LINKO SEMICONDUCTOR *****END OF FILE****/
