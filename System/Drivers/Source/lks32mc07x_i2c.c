/**
 * @file
 * @defgroup i2c
 * @brief        i2c库函数
 * @author       YangZJ
 * @date         2023-01-02
 * @{
 */
#include "lks32mc07x_i2c.h"
#include "lks32mc07x_sys.h"
#include "lks32mc07x_dma.h"

/**
 * @brief    I2C初始化
 * @param I2C_InitStruct I2C配置结构体
 * @par 更新记录  V1.0  2021/11/10  YangZJ  创建
 */
void I2C_Init(I2C_TypeDef *I2Cx, I2C_InitTypeDef *I2C_InitStruct)
{
    SYS_ModuleClockCmd(SYS_Module_I2C0, ENABLE);
    SYS_SoftResetModule(SYS_Module_I2C0);

    {
        u32 BaudRate;
        BaudRate = ((u32)48000000 + ((I2C_InitStruct->BaudRate * 17) >> 1)) / (I2C_InitStruct->BaudRate * 17) - 1;
        SYS_WR_PROTECT = 0x7A83; // 解除系统寄存器写保护
        SYS_CLK_DIV0 = BaudRate;
        SYS_WR_PROTECT = 0; // 解除系统寄存器写保护
    }
    I2Cx->ADDR = (I2C_InitStruct->ADRCMP << 7);
    I2Cx->CFG = (I2C_InitStruct->IE << 7) | (I2C_InitStruct->TC_IE << 6) |
                (I2C_InitStruct->BUS_ERR_IE << 5) | (I2C_InitStruct->STOP_IE << 4) |
                (I2C_InitStruct->MST_MODE << 1) | (I2C_InitStruct->SLV_MODE);
    I2Cx->SCR = 0;
    I2Cx->DATA = 0;
    I2Cx->MSCR = 0;
    I2Cx->BCR = (I2C_InitStruct->BURST_NACK << 7) | (I2C_InitStruct->BURST_ADDR_CMP << 6) |
                (I2C_InitStruct->BUSRT_EN << 5);
}
/**
 * @brief    I2C结构体初始化
 * @param I2C_InitStruct I2C配置结构体
 * @par 更新记录  V1.0  2021/11/10  YangZJ  创建
 */
void I2C_StructInit(I2C_InitTypeDef *I2C_InitStruct)
{
    I2C_InitStruct->ADRCMP = DISABLE;         //  I2C 硬件地址比较使能开关，只有在 DMA 模式下开启才有效。
    I2C_InitStruct->MST_MODE = DISABLE;       //  I2C 主模式使能
    I2C_InitStruct->SLV_MODE = DISABLE;       //  I2C 从模式使能
    I2C_InitStruct->BUSRT_EN = DISABLE;       //  I2C DMA传输使能
    I2C_InitStruct->BaudRate = 100000;        //  I2C 波特率
    I2C_InitStruct->IE = DISABLE;             //  I2C 中断使能
    I2C_InitStruct->TC_IE = DISABLE;          //  I2C 数据传输完成中断使能
    I2C_InitStruct->BUS_ERR_IE = DISABLE;     //  I2C 总线错误事件中断使能
    I2C_InitStruct->STOP_IE = DISABLE;        //  I2C STOP 事件中断使能
    I2C_InitStruct->BURST_NACK = DISABLE;     //  I2C 传输，NACK 事件中断使能
    I2C_InitStruct->BURST_ADDR_CMP = DISABLE; //  I2C 传输，硬件地址匹配中断使能
}
/**
 * @brief    读I2C总线状态
 * @param I2C_InitStruct I2C配置结构体
 * @par 更新记录  V1.0  2021/11/10  YangZJ  创建
 */
u8 I2c_ReadBusState(I2C_TypeDef *I2Cx, u16 n)
{
    if (I2Cx->SCR & n)
    {
        return ENABLE;
    }
    else
    {
        return DISABLE;
    }
}
/**
 * @brief    I2C总线状态复位
 * @param I2C_InitStruct I2C配置结构体
 * @par 更新记录  V1.0  2021/11/10  YangZJ  创建
 */
void I2c_ClearBusState(I2C_TypeDef *I2Cx, u16 n)
{
    I2Cx->SCR &= ~n;
}
/**
 * @brief    I2C发送数据
 * @par 更新记录  V1.0  2016/05/21  YangZJ  创建
 */
void I2C_SendData(I2C_TypeDef *I2Cx, u8 n)
{
    I2Cx->DATA = n;
}

/**
 * @brief    I2C读缓冲区数据
 * @param I2C_TypeDef *I2Cx
 * @return 缓冲区数据
 * @par 更新记录  V1.0  2016/05/21  YangZJ  创建
 */
u8 I2C_ReadData(I2C_TypeDef *I2Cx)
{
    return (u8)I2Cx->DATA;
}

/**
 * @brief    I2C清除中断
 操作的表：
 输出参数：
 * @par 更新记录  V1.0  2022/08/30  YangZJ  创建
*/
void I2C_ClearIRQFlag(I2C_TypeDef *I2Cx, u16 I2C_IF_x)
{
    switch (I2C_IF_x)
    {
    case I2C_IF_TC: // 传输完成中断
        I2Cx->SCR &= ~BIT0;
        break;
    case I2C_IF_BUS_ERR: // 总线错误中断
        I2Cx->SCR &= ~BIT7;
        break;
    case I2C_IF_STOP: // STOP事件中断
        I2Cx->SCR &= ~BIT5;
        break;
    case I2C_IF_NACK: // NACK事件中断
        I2Cx->SCR &= ~BIT1;
        break;
    case I2C_IF_ADDR_CMP: // 硬件地址比较中断

        break;
    default:
        break;
    }
}
/**
 * @brief    I2C获取当前中断状态
 操作的表：
 输出参数：
 * @par 更新记录  V1.0  2022/08/30  YangZJ  创建
*/
u8 I2C_GetIRQFlag(I2C_TypeDef *I2Cx, u16 I2C_IF_x)
{
    switch (I2C_IF_x)
    {
    case I2C_IF_TC: // 传输完成中断
        if ((I2Cx->CFG & BIT7) == 0)
        {
            return 0;
        }
        if ((I2Cx->CFG & BIT6) == 0)
        {
            return 0;
        }
        if (I2Cx->SCR & BIT0)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    case I2C_IF_BUS_ERR: // 总线错误中断
        if ((I2Cx->CFG & BIT7) == 0)
        {
            return 0;
        }
        if ((I2Cx->CFG & BIT5) == 0)
        {
            return 0;
        }
        if (I2Cx->SCR & BIT7)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    case I2C_IF_STOP: // STOP事件中断
        if ((I2Cx->CFG & BIT7) == 0)
        {
            return 0;
        }
        if ((I2Cx->CFG & BIT4) == 0)
        {
            return 0;
        }
        if (I2Cx->SCR & BIT5)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    case I2C_IF_NACK: // NACK事件中断
        if ((I2Cx->CFG & BIT7) == 0)
        {
            return 0;
        }
        if ((I2Cx->BCR & BIT7) == 0)
        {
            return 0;
        }
        if (I2Cx->SCR & BIT1)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    case I2C_IF_ADDR_CMP: // 硬件地址匹配中断
        if ((I2Cx->CFG & BIT7) == 0)
        {
            return 0;
        }
        if ((I2Cx->BCR & BIT6) == 0)
        {
            return 0;
        }
        if (I2Cx->SCR & BIT3)
        {
            if ((u32)(I2Cx->DATA >> 1) == (I2Cx->ADDR & 0x7f))
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
    default:
        return 0;
    }
}
/**
 * @brief    I2C清除中断
 * @param I2C_TypeDef *I2Cx
 * @par 更新记录  V1.0  2022/08/30  YangZJ  创建
 */
u8 I2C_GetFlag(I2C_TypeDef *I2Cx, u16 I2C_IF_x)
{
    switch (I2C_IF_x)
    {
    case I2C_IF_TC: // 传输完成中断
        if (I2Cx->SCR & BIT0)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    case I2C_IF_BUS_ERR: // 总线错误中断
        if (I2Cx->SCR & BIT7)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    case I2C_IF_STOP: // STOP事件中断
        if (I2Cx->SCR & BIT5)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    case I2C_IF_NACK: // NACK事件中断
        if (I2Cx->SCR & BIT1)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    case I2C_IF_ADDR_CMP: // 硬件地址匹配中断
        if (I2Cx->SCR & BIT3)
        {
            if ((u32)(I2Cx->DATA >> 1) == (I2Cx->ADDR & 0x7f))
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
    default:
        return 0;
    }
}

/**
 * @brief    I2C模块使能
 * @param I2C_TypeDef *I2Cx
 * @par 更新记录  V1.0  2022/08/30  YangZJ  创建
 */
void I2C_Enable(I2C_TypeDef *I2Cx)
{
    if (I2Cx == I2C0)
    {
        SYS_ModuleClockCmd(SYS_Module_I2C0, ENABLE);
    }
}
/**
 * @brief    I2C模块关闭
 * @param I2C_TypeDef *I2Cx
 * @par 更新记录  V1.0  2022/08/30  YangZJ  创建
 */
void I2C_Disable(I2C_TypeDef *I2Cx)
{
    if (I2Cx == I2C0)
    {
        SYS_ModuleClockCmd(SYS_Module_I2C0, DISABLE);
    }
}

/**
 * @brief    设置I2C模块的波特率
 * @param BaudRate 波特率
 * @par 更新记录  V1.0  2022/08/30  YangZJ  创建
 */
void I2C_SetBaudRate(u32 BaudRate)
{
    u32 div;
    div = ((u32)48000000 + ((BaudRate * 17) >> 1)) / (BaudRate * 17) - 1;
    SYS_WR_PROTECT = 0x7A83;
    SYS_CLK_DIV0 = div;
    SYS_WR_PROTECT = 0;
}

/*! @} */
