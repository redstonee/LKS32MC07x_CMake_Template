/**
 * @file
 * @defgroup crc
 * @brief        CRC库函数
 * @author       YangZJ
 * @date         2023-01-02
 * @{
 */
#include "lks32mc07x_crc.h"
static u32 CRC_XOROUT = 0;

/**
 * @brief CRC计算初始化
 */
void CRC_Init(CRC_TypeDef *CRCx, CRC_InitTypeDef *this)
{
    if (this->WIDTH > 3)
    {
        switch (this->WIDTH)
        {
        case 7:
            this->WIDTH = CRC_WIDTH_7;
            break;
        case 8:
            this->WIDTH = CRC_WIDTH_8;
            break;
        case 16:
            this->WIDTH = CRC_WIDTH_16;
            break;
        case 32:
            this->WIDTH = CRC_WIDTH_32;
            break;
        default:
            this->WIDTH = CRC_WIDTH_8;
            break;
        }
    }
    CRC_Enable(CRCx);
    SYS_SoftResetModule(SYS_Module_CRC0);
    CRC0_CR = (u32)(this->REFOUT << 12) | (u32)(this->REFIN << 8) | (u32)(this->WIDTH << 4);
    CRC0_CR |= BIT0; // 复位
    CRC0_POL = this->POLY;
    CRC0_INIT = this->INIT;
    CRC_XOROUT = this->XOROUT;
}
/**
 * @brief CRC初始化结构体初始化
 */
void CRC_StructInit(CRC_InitTypeDef *this)
{
    this->POLY = 7;            // 多项式
    this->INIT = 0;            // 初始值
    this->XOROUT = 0;          // 结果异或值
    this->REFIN = 0;           // 输入数据反转
    this->REFOUT = 0;          // 输出数据反转
    this->WIDTH = CRC_WIDTH_8; // 宽度
}
/**
 * @brief CRC计算
 */
u32 CRC_Calc(CRC_TypeDef *CRCx, u8 *data, u32 len)
{
    u32 val;
    if (len == 0)
    {
        return 0;
    }
    else
    {
        while ((len--) != 0)
        {
            REG8(&CRCx->DR) = *data;
            data++;
        }
    }
    val = (REG32(&CRCx->DR)) ^ CRC_XOROUT;
    return val;
}
/**
 * @brief CRC计算接口
 */
u32 CRC_CalcCommon(CRC_TypeDef *CRCx, u8 *data, u32 len, u16 CRC_MODEL_x)
{
    u32 val;
    CRC_InitTypeDef CRC_InitStruct;
    switch (CRC_MODEL_x)
    {
    case CRC_MODEL_CRC_8: //  8   07          00          00          false   false

        CRC_InitStruct.WIDTH = CRC_WIDTH_8; // 宽度
        CRC_InitStruct.POLY = 0x07;         // 多项式
        CRC_InitStruct.INIT = 0x00;         // 初始值
        CRC_InitStruct.XOROUT = 0x00;       // 结果异或值
        CRC_InitStruct.REFIN = DISABLE;     // 输入数据反转
        CRC_InitStruct.REFOUT = DISABLE;    // 输出数据反转
        CRC_Init(CRCx, &CRC_InitStruct);
        break;
    case CRC_MODEL_CRC_8_ITU:               // 8   07          00          55          false   false
        CRC_InitStruct.WIDTH = CRC_WIDTH_8; // 宽度
        CRC_InitStruct.POLY = 0x07;         // 多项式
        CRC_InitStruct.INIT = 0x00;         // 初始值
        CRC_InitStruct.XOROUT = 0x55;       // 结果异或值
        CRC_InitStruct.REFIN = DISABLE;     // 输入数据反转
        CRC_InitStruct.REFOUT = DISABLE;    // 输出数据反转
        CRC_Init(CRCx, &CRC_InitStruct);
        break;
    case CRC_MODEL_CRC_8_ROHC: //  8   07          FF          00          true    true

        CRC_InitStruct.WIDTH = CRC_WIDTH_8; // 宽度
        CRC_InitStruct.POLY = 0x07;         // 多项式
        CRC_InitStruct.INIT = 0xff;         // 初始值
        CRC_InitStruct.XOROUT = 0x00;       // 结果异或值
        CRC_InitStruct.REFIN = ENABLE;      // 输入数据反转
        CRC_InitStruct.REFOUT = ENABLE;     // 输出数据反转
        CRC_Init(CRCx, &CRC_InitStruct);
        break;
    case CRC_MODEL_CRC_8_MAXIMx: //  8   31          00          00          true    true

        CRC_InitStruct.WIDTH = CRC_WIDTH_8; // 宽度
        CRC_InitStruct.POLY = 0x31;         // 多项式
        CRC_InitStruct.INIT = 0x00;         // 初始值
        CRC_InitStruct.XOROUT = 0x00;       // 结果异或值
        CRC_InitStruct.REFIN = ENABLE;      // 输入数据反转
        CRC_InitStruct.REFOUT = ENABLE;     // 输出数据反转
        CRC_Init(CRCx, &CRC_InitStruct);
        break;
    case CRC_MODEL_CRC_16_IBMx1: //  16  8005        0000        0000        true    true

        CRC_InitStruct.WIDTH = CRC_WIDTH_16; // 宽度
        CRC_InitStruct.POLY = 0x8005;        // 多项式
        CRC_InitStruct.INIT = 0x0000;        // 初始值
        CRC_InitStruct.XOROUT = 0x0000;      // 结果异或值
        CRC_InitStruct.REFIN = ENABLE;       // 输入数据反转
        CRC_InitStruct.REFOUT = ENABLE;      // 输出数据反转
        CRC_Init(CRCx, &CRC_InitStruct);
        break;
    case CRC_MODEL_CRC_16_MAXIM: //  16  8005        0000        FFFF        true    true

        CRC_InitStruct.WIDTH = CRC_WIDTH_16; // 宽度
        CRC_InitStruct.POLY = 0x8005;        // 多项式
        CRC_InitStruct.INIT = 0x0000;        // 初始值
        CRC_InitStruct.XOROUT = 0xffff;      // 结果异或值
        CRC_InitStruct.REFIN = ENABLE;       // 输入数据反转
        CRC_InitStruct.REFOUT = ENABLE;      // 输出数据反转
        CRC_Init(CRCx, &CRC_InitStruct);
        break;
    case CRC_MODEL_CRC_16_USBx1: //  16  8005        FFFF        FFFF        true    true

        CRC_InitStruct.WIDTH = CRC_WIDTH_16; // 宽度
        CRC_InitStruct.POLY = 0x8005;        // 多项式
        CRC_InitStruct.INIT = 0xffff;        // 初始值
        CRC_InitStruct.XOROUT = 0xffff;      // 结果异或值
        CRC_InitStruct.REFIN = ENABLE;       // 输入数据反转
        CRC_InitStruct.REFOUT = ENABLE;      // 输出数据反转
        CRC_Init(CRCx, &CRC_InitStruct);
        break;
    case CRC_MODEL_CRC_16_MODBU: //  16  8005        FFFF        0000        true    true

        CRC_InitStruct.WIDTH = CRC_WIDTH_16; // 宽度
        CRC_InitStruct.POLY = 0x8005;        // 多项式
        CRC_InitStruct.INIT = 0xffff;        // 初始值
        CRC_InitStruct.XOROUT = 0x0000;      // 结果异或值
        CRC_InitStruct.REFIN = ENABLE;       // 输入数据反转
        CRC_InitStruct.REFOUT = ENABLE;      // 输出数据反转
        CRC_Init(CRCx, &CRC_InitStruct);
        break;
    case CRC_MODEL_CRC_16_CCITT: //  16  1021        0000        0000        true    true

        CRC_InitStruct.WIDTH = CRC_WIDTH_16; // 宽度
        CRC_InitStruct.POLY = 0x1021;        // 多项式
        CRC_InitStruct.INIT = 0x0000;        // 初始值
        CRC_InitStruct.XOROUT = 0x0000;      // 结果异或值
        CRC_InitStruct.REFIN = ENABLE;       // 输入数据反转
        CRC_InitStruct.REFOUT = ENABLE;      // 输出数据反转
        CRC_Init(CRCx, &CRC_InitStruct);
        break;
    case CRC_MODEL_CRC_16_CCITT_FALSE: //  16  1021        FFFF        0000        false   false

        CRC_InitStruct.WIDTH = CRC_WIDTH_16; // 宽度
        CRC_InitStruct.POLY = 0x1021;        // 多项式
        CRC_InitStruct.INIT = 0xffff;        // 初始值
        CRC_InitStruct.XOROUT = 0x0000;      // 结果异或值
        CRC_InitStruct.REFIN = DISABLE;      // 输入数据反转
        CRC_InitStruct.REFOUT = DISABLE;     // 输出数据反转
        CRC_Init(CRCx, &CRC_InitStruct);
        break;
    case CRC_MODEL_CRC_16_X25: //  16  1021        FFFF        FFFF        true    true

        CRC_InitStruct.WIDTH = CRC_WIDTH_16; // 宽度
        CRC_InitStruct.POLY = 0x1021;        // 多项式
        CRC_InitStruct.INIT = 0xffff;        // 初始值
        CRC_InitStruct.XOROUT = 0xffff;      // 结果异或值
        CRC_InitStruct.REFIN = ENABLE;       // 输入数据反转
        CRC_InitStruct.REFOUT = ENABLE;      // 输出数据反转
        CRC_Init(CRCx, &CRC_InitStruct);
        break;
    case CRC_MODEL_CRC_16_XMODEM: //  16  1021        0000        0000        false   false

        CRC_InitStruct.WIDTH = CRC_WIDTH_16; // 宽度
        CRC_InitStruct.POLY = 0x1021;        // 多项式
        CRC_InitStruct.INIT = 0x0000;        // 初始值
        CRC_InitStruct.XOROUT = 0x0000;      // 结果异或值
        CRC_InitStruct.REFIN = DISABLE;      // 输入数据反转
        CRC_InitStruct.REFOUT = DISABLE;     // 输出数据反转
        CRC_Init(CRCx, &CRC_InitStruct);
        break;
    case CRC_MODEL_CRC_16_DNP: //  16  3D65        0000        FFFF        true    true

        CRC_InitStruct.WIDTH = CRC_WIDTH_16; // 宽度
        CRC_InitStruct.POLY = 0x3d65;        // 多项式
        CRC_InitStruct.INIT = 0x0000;        // 初始值
        CRC_InitStruct.XOROUT = 0xffff;      // 结果异或值
        CRC_InitStruct.REFIN = ENABLE;       // 输入数据反转
        CRC_InitStruct.REFOUT = ENABLE;      // 输出数据反转
        CRC_Init(CRCx, &CRC_InitStruct);
        break;
    case CRC_MODEL_CRC_32: //  32  04C11DB7    FFFFFFFF    FFFFFFFF    true    true

        CRC_InitStruct.WIDTH = CRC_WIDTH_32; // 宽度
        CRC_InitStruct.POLY = 0x04C11DB7;    // 多项式
        CRC_InitStruct.INIT = 0xFFFFFFFF;    // 初始值
        CRC_InitStruct.XOROUT = 0xFFFFFFFF;  // 结果异或值
        CRC_InitStruct.REFIN = ENABLE;       // 输入数据反转
        CRC_InitStruct.REFOUT = ENABLE;      // 输出数据反转
        CRC_Init(CRCx, &CRC_InitStruct);
        break;
    case CRC_MODEL_CRC_32_MPEG_2: //  32  04C11DB7    FFFFFFFF    00000000    false   false

        CRC_InitStruct.WIDTH = CRC_WIDTH_32; // 宽度
        CRC_InitStruct.POLY = 0x04C11DB7;    // 多项式
        CRC_InitStruct.INIT = 0xFFFFFFFF;    // 初始值
        CRC_InitStruct.XOROUT = 0x00000000;  // 结果异或值
        CRC_InitStruct.REFIN = DISABLE;      // 输入数据反转
        CRC_InitStruct.REFOUT = DISABLE;     // 输出数据反转
        CRC_Init(CRCx, &CRC_InitStruct);
        break;
    }
    val = CRC_Calc(CRCx, data, len);
    if (CRC_InitStruct.REFOUT)
    {
        switch (CRC_InitStruct.WIDTH)
        {
        case CRC_WIDTH_8:
            val >>= 24;
            break;
        case CRC_WIDTH_16:
            val >>= 16;
            break;
        }
    }
    return val;
}
/**
 * @brief CRC模块时钟使能
 */
void CRC_Enable(CRC_TypeDef *CRCx)
{
    if (CRCx == CRC0)
    {
        SYS_ModuleClockCmd(SYS_Module_CRC0, ENABLE);
    }
}
/**
 * @brief CRC模块时钟关闭
 */
void CRC_Disable(CRC_TypeDef *CRCx)
{
    if (CRCx == CRC0)
    {
        SYS_ModuleClockCmd(SYS_Module_CRC0, DISABLE);
    }
}

/*! @} */
