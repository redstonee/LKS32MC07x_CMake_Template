/**
 * @file
 * @brief        I2C库函数头文件
 * @author       YangZJ
 * @date         2023-01-02
 *  */
#ifndef __lks32mc45x_I2C_H
#define __lks32mc45x_I2C_H
///< Includes ------------------------------------------------------------------
#include "lks32mc07x.h"
#include "lks32mc07x_dma.h"
#include "basic.h"

// I2C_BUS_STATE   I2C总线状态
#define I2C_BUS_STATE_STT_ERR BIT7  ///< 总线错误
#define I2C_BUS_STATE_LOST_ARB BIT6 ///< 总线仲裁丢失
#define I2C_BUS_STATE_STOP_EVT BIT5 ///< STOP事件记录

#define I2C_BUS_STATE_ADDR_DATA BIT3 ///< 正在传输地址数据

#define I2C_BUS_STATE_RX_ACK BIT1 ///< 接收到ACK响应
#define I2C_BUS_STATE_Done BIT0   ///< 传输完成

#define I2C_IF_TC 0       ///< 传输完成中断
#define I2C_IF_BUS_ERR 1  ///< 总线错误中断
#define I2C_IF_STOP 2     ///< STOP事件中断
#define I2C_IF_NACK 3     ///< NACK事件中断
#define I2C_IF_ADDR_CMP 4 ///< 硬件地址匹配中断

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

    typedef struct
    {
        __IO u32 ADDR;  ///< 0x00 I2C 地址寄存器
        __IO u32 CFG;   ///< 0x04 I2C 配置寄存器
        __IO u32 SCR;   ///< 0x08 I2C 状态寄存器
        __IO u32 DATA;  ///< 0x0C I2C 数据寄存器
        __IO u32 MSCR;  ///< 0x10 I2C 主模式寄存器
        __IO u32 BCR;   ///< 0x14 I2C 传输控制寄存器
        __IO u32 BSIZE; ///< 0x18 I2C 传输长度寄存器

    } I2C_TypeDef;

#ifndef I2C0
#define I2C0 ((I2C_TypeDef *)I2C0_BASE)
#endif
    typedef struct
    {
        u32 ADRCMP;         ///< I2C 硬件地址比较使能开关
        u32 MST_MODE;       ///< I2C 主模式使能信号
        u32 SLV_MODE;       ///< I2C 从模式使能信号
        u32 BUSRT_EN;       ///< I2C DMA传输使能
        u32 BaudRate;       ///< I2C 波特率
        u32 IE;             ///< I2C 中断使能信号
        u32 TC_IE;          ///< I2C 数据传输完成中断使能
        u32 BUS_ERR_IE;     ///< I2C 总线错误事件中断使能信号
        u32 STOP_IE;        ///< I2C STOP 事件中断使能信号
        u32 BURST_NACK;     ///< NACK 事件中断使能
        u32 BURST_ADDR_CMP; ///< 硬件地址匹配中断使能
    } I2C_InitTypeDef;

    void I2C_Init(I2C_TypeDef *I2Cx, I2C_InitTypeDef *I2C_InitStruct); ///< I2C初始化
    void I2C_StructInit(I2C_InitTypeDef *I2C_InitStruct);              ///< I2C配置结构体初始化
    void I2C_ClearIRQFlag(I2C_TypeDef *I2Cx, u16 I2C_IF_x);
    u8 I2C_GetIRQFlag(I2C_TypeDef *I2Cx, u16 I2C_IF_x);
    u8 I2C_GetFlag(I2C_TypeDef *I2Cx, u16 I2C_IF_x);

    void I2C_Enable(I2C_TypeDef *I2Cx);
    void I2C_Disable(I2C_TypeDef *I2Cx);
    void I2C_SetBaudRate(u32 BaudRate);

    u8 I2c_ReadBusState(I2C_TypeDef *I2Cx, u16);    ///< 读I2C总线状态
    void I2c_ClearBusState(I2C_TypeDef *I2Cx, u16); ///< I2C总线状态复位
    void I2C_SendData(I2C_TypeDef *I2Cx, u8 n);
    u8 I2C_ReadData(I2C_TypeDef *I2Cx);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif /*__lks32mc03x_I2C_H */
