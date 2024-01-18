/**
 * @file
 * @copyright (C)2015, LINKO SEMICONDUCTOR Co.ltd
 * @brief 文件名称： lks32mc07x_exti.c\n
 * 文件标识： 无 \n
 * 内容摘要： EXTI外设驱动程序 \n
 * 其它说明： 无 \n
 *@par
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2023年2月28日 <td>1.0    <td>cakezhang     <td>创建
 * </table>
 */
#include "lks32mc07x_exti.h"
#include "lks32mc07x.h"

/**
 *@brief @b 函数名称:   void EXTI_Trigger_Config(GPIO_TypeDef *GPIOx, uint32_t GPIO_PinSource, uint16_t EXTI_Trigger)
 *@brief @b 功能描述:   GPIO外部触发极性选择
 *@see被引用内容：       GPIO_TypeDef
 *@param输入参数：
                        GPIOx:GPIO对象可选(GPIO0~GPIO3) \n
                        GPIO_PadSource:指定的PadSource可选(GPIO_PinSource_0~GPIO_PinSource_15) \n
                        EXTI_Trigger:指定的触发极性 @see EXTI_Trigger参数来源：EXTIMode_TypeDef
 *@param输出参数：      无
 *@return返 回 值：     无
 *@note其它说明：       无
 *@warning             无
 *@par 示例代码：
 *@code
        EXTI_Trigger_Config(GPIO0,GPIO_PinSource_0,EXTI_Trigger_Negedge);//P0.0信号下降沿触发外部中断事件
  @endcode
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author      <th>Description
 * <tr><td>2023年2月23日 <td>1.0       <td>cakezhang        <td>创建
 * </table>
 */
void EXTI_Trigger_Config(GPIO_TypeDef *GPIOx, uint32_t GPIO_PinSource, uint16_t EXTI_Trigger)
{
    if (GPIOx == GPIO0)
    {
        EXTI->IE = EXTI->IE | 0x01;

        if (GPIO_PinSource == 0)
        {
            EXTI->CR0 = (EXTI->CR0 & 0xfffc) | EXTI_Trigger;
        }
        else if (GPIO_PinSource == 1)
        {
            EXTI->CR0 = (EXTI->CR0 & 0xfff3) | (EXTI_Trigger << 2);
        }
        else if (GPIO_PinSource == 2)
        {
            EXTI->CR1 = (EXTI->CR0 & 0xffcf) | (EXTI_Trigger << 4);
        }
        else if (GPIO_PinSource == 3)
        {
            EXTI->CR0 = (EXTI->CR0 & 0xff3f) | (EXTI_Trigger << 6);
        }
        else if (GPIO_PinSource == 6)
        {
            EXTI->CR0 = (EXTI->CR0 & 0xfcff) | (EXTI_Trigger << 8);
        }
        else if (GPIO_PinSource == 11)
        {
            EXTI->CR0 = (EXTI->CR0 & 0xf3ff) | (EXTI_Trigger << 10);
        }
        else if (GPIO_PinSource == 14)
        {
            EXTI->CR0 = (EXTI->CR0 & 0xcfff) | (EXTI_Trigger << 12);
        }
        else if (GPIO_PinSource == 15)
        {
            EXTI->CR0 = (EXTI->CR0 & 0x3fff) | (EXTI_Trigger << 14);
        }
        else
        {
            return;
        }
    }

    if (GPIOx == GPIO1)
    {
        EXTI->IE = EXTI->IE | 0x02;

        if (GPIO_PinSource == 0)
        {
            EXTI->CR1 = (EXTI->CR1 & 0xfffc) | EXTI_Trigger;
        }
        else if (GPIO_PinSource == 1)
        {
            EXTI->CR1 = (EXTI->CR1 & 0xfff3) | (EXTI_Trigger << 2);
        }
        else if (GPIO_PinSource == 10)
        {
            EXTI->CR1 = (EXTI->CR1 & 0xffcf) | (EXTI_Trigger << 4);
        }
        else
        {
            return;
        }
    }

    if (GPIOx == GPIO2)
    {
        EXTI->IE = EXTI->IE | 0x04;

        if (GPIO_PinSource == 2)
        {
            EXTI->CR1 = (EXTI->CR1 & 0xff3f) | (EXTI_Trigger << 6);
        }
        else if (GPIO_PinSource == 4)
        {
            EXTI->CR1 = (EXTI->CR1 & 0xfcff) | (EXTI_Trigger << 8);
        }
        else if (GPIO_PinSource == 7)
        {
            EXTI->CR1 = (EXTI->CR1 & 0xf3ff) | (EXTI_Trigger << 10);
        }
        else if (GPIO_PinSource == 12)
        {
            EXTI->CR1 = (EXTI->CR1 & 0xcfff) | (EXTI_Trigger << 12);
        }
        else if (GPIO_PinSource == 15)
        {
            EXTI->CR1 = (EXTI->CR1 & 0x3fff) | (EXTI_Trigger << 14);
        }
        else
        {
            return;
        }
    }
}

/**
 *@brief @b 函数名称:   u8 EXTI_GetIRQFlag(GPIO_TypeDef *GPIOx, uint32_t GPIO_PinSource)
 *@brief @b 功能描述:   读取外部中断标志位
 *@see被引用内容：       无
 *@param输入参数：
                        GPIOx:GPIO对象可选(GPIO0~GPIO3) \n
                        GPIO_PadSource:指定的PadSource可选(GPIO_PinSource_0~GPIO_PinSource_15)
 *@param输出参数：      无
 *@return返 回 值：     中断标志，高有效
 *@note其它说明：       无
 *@warning             无
 *@par 示例代码：
 *@code
        if(EXTI_GetIRQFlag(GPIO0,GPIO_PinSource_0))//获取P0.0外部中断标志位
        {
        }
  @endcode
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author      <th>Description
 * <tr><td>2023年2月23日 <td>1.0       <td>cakezhang        <td>创建
 * </table>
 */
u8 EXTI_GetIRQFlag(GPIO_TypeDef *GPIOx, uint32_t GPIO_PinSource)
{
    if (GPIOx == GPIO0)
    {
        if (GPIO_PinSource == 0)
        {
            if (EXTI_IF & 0x01)
            {
                return 1;
            }
            else
            {
                return 0;
            }
        }
        else if (GPIO_PinSource == 1)
        {
            if (EXTI_IF & 0x02)
            {
                return 1;
            }
            else
            {
                return 0;
            }
        }
        else if (GPIO_PinSource == 2)
        {
            if (EXTI_IF & 0x04)
            {
                return 1;
            }
            else
            {
                return 0;
            }
        }
        else if (GPIO_PinSource == 3)
        {
            if (EXTI_IF & 0x08)
            {
                return 1;
            }
            else
            {
                return 0;
            }
        }
        else if (GPIO_PinSource == 6)
        {
            if (EXTI_IF & 0x10)
            {
                return 1;
            }
            else
            {
                return 0;
            }
        }
        else if (GPIO_PinSource == 11)
        {
            if (EXTI_IF & 0x20)
            {
                return 1;
            }
            else
            {
                return 0;
            }
        }
        else if (GPIO_PinSource == 14)
        {
            if (EXTI_IF & 0x40)
            {
                return 1;
            }
            else
            {
                return 0;
            }
        }
        else if (GPIO_PinSource == 15)
        {
            if (EXTI_IF & 0x80)
            {
                return 1;
            }
            else
            {
                return 0;
            }
        }
        else
        {
            return 0;
        }
    }

    else if (GPIOx == GPIO1)
    {
        if (GPIO_PinSource == 0)
        {
            if (EXTI_IF & 0x100)
            {
                return 1;
            }
            else
            {
                return 0;
            }
        }
        else if (GPIO_PinSource == 1)
        {
            if (EXTI_IF & 0x200)
            {
                return 1;
            }
            else
            {
                return 0;
            }
        }
        else if (GPIO_PinSource == 10)
        {
            if (EXTI_IF & 0x400)
            {
                return 1;
            }
            else
            {
                return 0;
            }
        }
        else
        {
            return 0;
        }
    }

    else if (GPIOx == GPIO2)
    {
        if (GPIO_PinSource == 2)
        {
            if (EXTI_IF & 0x800)
            {
                return 1;
            }
            else
            {
                return 0;
            }
        }
        else if (GPIO_PinSource == 4)
        {
            if (EXTI_IF & 0x1000)
            {
                return 1;
            }
            else
            {
                return 0;
            }
        }
        else if (GPIO_PinSource == 7)
        {
            if (EXTI_IF & 0x2000)
            {
                return 1;
            }
            else
            {
                return 0;
            }
        }
        else if (GPIO_PinSource == 12)
        {
            if (EXTI_IF & 0x4000)
            {
                return 1;
            }
            else
            {
                return 0;
            }
        }
        else if (GPIO_PinSource == 15)
        {
            if (EXTI_IF & 0x8000)
            {
                return 1;
            }
            else
            {
                return 0;
            }
        }
        else
        {
            return 0;
        }
    }
    else
    {
        return 0;
    }
}

/**
 *@brief @b 函数名称:   void EXTI_ClearIRQFlag(GPIO_TypeDef *GPIOx, uint32_t GPIO_PinSource)
 *@brief @b 功能描述:   清除外部中断标志位
 *@see被引用内容：       无
 *@param输入参数：
                        GPIOx:GPIO对象可选(GPIO0~GPIO3) \n
                        GPIO_PadSource:指定的PadSource可选(GPIO_PinSource_0~GPIO_PinSource_15)
 *@param输出参数：      无
 *@return返 回 值：     无
 *@note其它说明：       无
 *@warning             无
 *@par 示例代码：
 *@code
        if(EXTI_GetIRQFlag(GPIO0,GPIO_PinSource_0))//获取P0.0外部中断标志位
        {
            EXTI_ClearIRQFlag(GPIO0,GPIO_PinSource_0);//清除P0.0外部中断标志位
        }
  @endcode
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author      <th>Description
 * <tr><td>2023年2月23日 <td>1.0       <td>cakezhang        <td>创建
 * </table>
 */
void EXTI_ClearIRQFlag(GPIO_TypeDef *GPIOx, uint32_t GPIO_PinSource)
{
    if (GPIOx == GPIO0)
    {
        if (GPIO_PinSource == 0)
        {
            EXTI_IF = 0x01;
        }
        else if (GPIO_PinSource == 1)
        {
            EXTI_IF = 0x02;
        }
        else if (GPIO_PinSource == 2)
        {
            EXTI_IF = 0x04;
        }
        else if (GPIO_PinSource == 3)
        {
            EXTI_IF = 0x08;
        }
        else if (GPIO_PinSource == 6)
        {
            EXTI_IF = 0x10;
        }
        else if (GPIO_PinSource == 11)
        {
            EXTI_IF = 0x20;
        }
        else if (GPIO_PinSource == 14)
        {
            EXTI_IF = 0x40;
        }
        else if (GPIO_PinSource == 15)
        {
            EXTI_IF = 0x80;
        }
    }

    if (GPIOx == GPIO1)
    {
        if (GPIO_PinSource == 0)
        {
            EXTI_IF = 0x100;
        }
        else if (GPIO_PinSource == 1)
        {
            EXTI_IF = 0x200;
        }
        else if (GPIO_PinSource == 10)
        {
            EXTI_IF = 0x400;
        }
    }

    if (GPIOx == GPIO2)
    {
        if (GPIO_PinSource == 2)
        {
            EXTI_IF = 0x800;
        }
        else if (GPIO_PinSource == 4)
        {
            EXTI_IF = 0x1000;
        }
        else if (GPIO_PinSource == 7)
        {
            EXTI_IF = 0x2000;
        }
        else if (GPIO_PinSource == 12)
        {
            EXTI_IF = 0x4000;
        }
        else if (GPIO_PinSource == 15)
        {
            EXTI_IF = 0x8000;
        }
    }
}
/************************ (C) COPYRIGHT LINKO SEMICONDUCTOR *****END OF FILE****/
