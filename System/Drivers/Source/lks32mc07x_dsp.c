/**
 * @file
 * @copyright (C)2015, LINKO SEMICONDUCTOR Co.ltd
 * @brief 文件名称： lks32mc07x_dsp.c\n
 * 文件标识： 无 \n
 * 内容摘要： DSP驱动程序 \n
 * 其它说明： 无 \n
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2015年11月5日 <td>1.0     <td>Howlet      <td>创建
 * </table>
 *@par 修改日志:DSP调用函数内增加中断打断重新复位DSP功能
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2023年2月12日 <td>2.0     <td>ywx   <td>修改
 * </table>
 */

#include "lks32mc07x_dsp.h"

/**
 *@brief 辅助变量，为了在多个中断中同时使用dsp
 */
static volatile u16 dsp_num;

/**
 *@brief @b 函数名称:   void DSP_Init(void)
 *@brief @b 功能描述:   DSP使能和关闭
 *@see被引用内容：       SYS_ModuleClockCmd()
 *@param输入参数：       无
 *@param输出参数：      无
 *@return返 回 值：     无
 *@note其它说明：       无
 *@warning             无
 *@par 示例代码：
 *@code
  @endcode
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author      <th>Description
 * <tr><td>2023年2月12日 <td>2.0     <td>ywx   <td>修改
 * </table>
 */
void DSP_Init(void)
{
    SYS_ModuleClockCmd(SYS_Module_DSP0, ENABLE); /* DSP时钟使能*/
}

/**
 *@brief @b 函数名称:   s16 DSP0_sin(u16 angle)
 *@brief @b 功能描述:   DSP sin计算函数
 *@see被引用内容：
 *@param输入参数：      angle： 输入角度
 *@param输出参数：      无
 *@return返 回 值：     sin角度值
 *@note其它说明：       无
 *@warning             无
 *@par 示例代码：
 *@code
  @endcode
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author      <th>Description
 * <tr><td>2023年2月12日 <td>2.0     <td>ywx   <td>修改
 * </table>
 */
s16 DSP0_sin(u16 angle)
{
    u16 dsp_num_val;
    s16 answer;
    do
    {
        dsp_num++;
        dsp_num_val = dsp_num;
        SYS_SoftResetModule(SYS_Module_DSP0);
        DSP_REG->SC = BIT2 | BIT1;
        DSP_REG->THETA = angle;
        answer = DSP_REG->SIN;
    } while (dsp_num_val != dsp_num);
    return answer;
}

/**
 *@brief @b 函数名称:  s16 DSP0_cos(u16 angle)
 *@brief @b 功能描述:   DSP cos计算函数
 *@see被引用内容：
 *@param输入参数：      angle： 输入角度
 *@param输出参数：      无
 *@return返 回 值：     cos角度值
 *@note其它说明：       无
 *@warning             无
 *@par 示例代码：
 *@code
  @endcode
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author      <th>Description
 * <tr><td>2023年2月12日 <td>2.0     <td>ywx   <td>修改
 * </table>
 */
s16 DSP0_cos(u16 angle)
{
    u16 dsp_num_val;
    s16 answer;
    do
    {
        dsp_num++;
        dsp_num_val = dsp_num;
        SYS_SoftResetModule(SYS_Module_DSP0);
        DSP_REG->SC = BIT2 | BIT1;
        DSP_REG->THETA = angle;
        answer = DSP_REG->COS;
    } while (dsp_num_val != dsp_num);
    return answer;
}

/**
 *@brief @b 函数名称:  s16 u16 DSP0_rms(s16 a,s16 b)
 *@brief @b 功能描述:   DSP 除法求余数计算函数
 *@see被引用内容：
 *@param输入参数：      a： 被除数
 *                     b:除数
 *@param输出参数：      无
 *@return返 回 值：     两数的余数
 *@note其它说明：       无
 *@warning             无
 *@par 示例代码：
 *@code
  @endcode
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author      <th>Description
 * <tr><td>2023年2月12日 <td>2.0     <td>ywx   <td>修改
 * </table>
 */
u16 DSP0_rms(s16 a, s16 b)
{
    u16 dsp_num_val;
    u16 answer;
    do
    {
        dsp_num++;
        dsp_num_val = dsp_num;
        SYS_SoftResetModule(SYS_Module_DSP0);
        DSP_REG->DID = a;
        DSP_REG->DIS = b;
        answer = DSP_REG->REM;
    } while (dsp_num_val != dsp_num);
    return answer;
}

/**
 *@brief @b 函数名称:  DSP_arctan(s16 x,s16 y)
 *@brief @b 功能描述:   DSP 反正切计算函数
 *@see被引用内容：
 *@param输入参数：      x：分母
 *                     y:分子
 *@param输出参数：      无
 *@return返 回 值：     反正切值
 *@note其它说明：       无
 *@warning             无
 *@par 示例代码：
 *@code
  @endcode
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author      <th>Description
 * <tr><td>2023年2月12日 <td>2.0     <td>ywx   <td>修改
 * </table>
 */
s16 DSP_arctan(s16 x, s16 y)
{
    u16 dsp_num_val;
    s16 answer;
    do
    {
        dsp_num++;
        dsp_num_val = dsp_num;
        SYS_SoftResetModule(SYS_Module_DSP0);
        DSP_REG->X = x;
        DSP_REG->Y = y;
        answer = DSP_REG->ARCTAN;
    } while (dsp_num_val != dsp_num);
    return answer;
}

/**
 *@brief @b 函数名称: s32 DSP0_div(s32 a,s32 b)
 *@brief @b 功能描述:   DSP 除法计算
 *@see被引用内容：
 *@param输入参数：      x：被除数
 *                     y:除数
 *@param输出参数：      无
 *@return返 回 值：     两数的商
 *@note其它说明：       无
 *@warning             无
 *@par 示例代码：
 *@code
  @endcode
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author      <th>Description
 * <tr><td>2023年2月12日 <td>2.0     <td>ywx   <td>修改
 * </table>
 */
s32 DSP0_div(s32 a, s32 b)
{
    u16 dsp_num_val;
    s32 answer;
    do
    {
        dsp_num++;
        dsp_num_val = dsp_num;
        SYS_SoftResetModule(SYS_Module_DSP0);
        DSP_REG->DID = a;
        DSP_REG->DIS = b;
        answer = DSP_REG->QUO;
    } while (dsp_num_val != dsp_num);
    return answer;
}

/**
 *@brief @b 函数名称: s16 DSP0_mod(s32 x,s16 y)
 *@brief @b 功能描述:   DSP 计算向量的模
 *@see被引用内容：
 *@param输入参数：      x：x轴
 *                     y: y轴
 *@param输出参数：      无
 *@return返 回 值：     向量的模
 *@note其它说明：       无
 *@warning             无
 *@par 示例代码：
 *@code
  @endcode
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author      <th>Description
 * <tr><td>2023年2月12日 <td>2.0     <td>ywx   <td>修改
 * </table>
 */
s16 DSP0_mod(s32 x, s16 y)
{
    u16 dsp_num_val;
    s16 answer;
    do
    {
        dsp_num++;
        dsp_num_val = dsp_num;
        SYS_SoftResetModule(SYS_Module_DSP0);
        DSP_REG->X = x;
        DSP_REG->Y = y;
        answer = DSP_REG->MOD;
    } while (dsp_num_val != dsp_num);
    return answer;
}

/**
 *@brief @b 函数名称: u16 DSP0_sqrt(u32 val)
 *@brief @b 功能描述:   开平方函数
 *@see被引用内容：
 *@param输入参数：      val ：被开方数
 *@param输出参数：      无
 *@return返 回 值：     向量的莫
 *@note其它说明：       无
 *@warning             无
 *@par 示例代码：
 *@code
  @endcode
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author      <th>Description
 * <tr><td>2023年2月12日 <td>2.0     <td>ywx   <td>修改
 * </table>
 */
u16 DSP0_sqrt(u32 val)
{
    u16 dsp_num_val;
    u16 answer;
    do
    {
        dsp_num++;
        dsp_num_val = dsp_num;
        SYS_SoftResetModule(SYS_Module_DSP0);
        DSP_REG->RAD = val;
        answer = DSP_REG->SQRT;
    } while (dsp_num_val != dsp_num);
    return answer;
}
