/**
 * @file
 * @defgroup clu
 * @brief        CLU库函数
 * @author       YangZJ
 * @date         2023-02-27
 * @{
 */
#include "lks32mc07x_clu.h"

/**
 * @brief CLU计算初始化
 */
void CLU_Init(CLU_TypeDef *CLUx, u8 CLU_MODEL_CLUx, CLU_InitTypeDef *this)
{
    CLU_Enable(CLUx);
    if ((CLU_MODEL_CLUx & CLU_MODEL_CLU0) != 0)
    {
        if (this->EN == 0)
        {
            CLUx->EN &= ~BIT0;
        }
        else
        {
            CLUx->EN |= BIT0;
        }
        if (this->FIE == 0)
        {
            CLUx->IE &= ~BIT0;
        }
        else
        {
            CLUx->IE |= BIT0;
        }
        if (this->RIE == 0)
        {
            CLUx->IE &= ~BIT1;
        }
        else
        {
            CLUx->IE |= BIT1;
        }
        CLUx->MX = (u32)((CLUx->MX & ~0x000f) | (this->MXA << 4) | (this->MXB));
        CLUx->FN = (u32)((CLUx->FN & ~0x000f) | (this->FN));
        CLUx->CF = (u32)((CLUx->CF & ~0x000f) | (this->OUTSEL << 7) | (this->OEN << 6) | (this->CLKINV << 2) | (this->CLKSEL));
        CLUx->CF |= BIT3;
    }
    if ((CLU_MODEL_CLUx & CLU_MODEL_CLU1) != 0)
    {
        if (this->EN == 0)
        {
            CLUx->EN &= ~BIT1;
        }
        else
        {
            CLUx->EN |= BIT1;
        }
        if (this->FIE == 0)
        {
            CLUx->IE &= ~BIT2;
        }
        else
        {
            CLUx->IE |= BIT2;
        }
        if (this->RIE == 0)
        {
            CLUx->IE &= ~BIT3;
        }
        else
        {
            CLUx->IE |= BIT3;
        }
        CLUx->MX = (u32)((CLUx->MX & ~0x00f0) | (this->MXA << 12) | (this->MXB << 8));
        CLUx->FN = (u32)((CLUx->FN & ~0x00f0) | (this->FN << 8));
        CLUx->CF = (u32)((CLUx->CF & ~0x00f0) | (this->OUTSEL << 15) | (this->OEN << 14) | (this->CLKINV << 10) | (this->CLKSEL << 8));
        CLUx->CF |= BIT11;
    }
    if ((CLU_MODEL_CLUx & CLU_MODEL_CLU2) != 0)
    {
        if (this->EN == 0)
        {
            CLUx->EN &= ~BIT2;
        }
        else
        {
            CLUx->EN |= BIT2;
        }
        if (this->FIE == 0)
        {
            CLUx->IE &= ~BIT4;
        }
        else
        {
            CLUx->IE |= BIT4;
        }
        if (this->RIE == 0)
        {
            CLUx->IE &= ~BIT5;
        }
        else
        {
            CLUx->IE |= BIT5;
        }
        CLUx->MX = (u32)((CLUx->MX & ~0x0f00) | (this->MXA << 20) | (this->MXB << 16));
        CLUx->FN = (u32)((CLUx->FN & ~0x0f00) | (this->FN << 16));
        CLUx->CF = (u32)((CLUx->CF & ~0x0f00) | (this->OUTSEL << 23) | (this->OEN << 22) | (this->CLKINV << 18) | (this->CLKSEL << 16));
        CLUx->CF |= BIT19;
    }
    if ((CLU_MODEL_CLUx & CLU_MODEL_CLU3) != 0)
    {
        if (this->EN == 0)
        {
            CLUx->EN &= ~BIT3;
        }
        else
        {
            CLUx->EN |= BIT3;
        }
        if (this->FIE == 0)
        {
            CLUx->IE &= ~BIT6;
        }
        else
        {
            CLUx->IE |= BIT6;
        }
        if (this->RIE == 0)
        {
            CLUx->IE &= ~BIT7;
        }
        else
        {
            CLUx->IE |= BIT7;
        }
        CLUx->MX = (u32)((CLUx->MX & ~0xf000) | (this->MXA << 28) | (this->MXB << 24));
        CLUx->FN = (u32)((CLUx->FN & ~0xf000) | (this->FN << 24));
        CLUx->CF = (u32)((CLUx->CF & ~0xf000) | (this->OUTSEL << 31) | (this->OEN << 30) | (this->CLKINV << 26) | (this->CLKSEL << 24));
        CLUx->CF |= BIT27;
    }
}
/**
 * @brief CLU初始化结构体初始化
 */
void CLU_StructInit(CLU_InitTypeDef *this)
{
    this->FIE = 0;    ///< 下降沿中断使能
    this->RIE = 0;    ///< 上升沿中断使能
    this->EN = 0;     ///< 模块使能 0关闭模块 1打开模块
    this->MXA = 0;    ///< A输入复用选择 格式 CLU_MXA_CLUa_b a取值范围为[0 1 2 3] 对应不同的CLU b表示选择不同的输入信号
    this->MXB = 0;    ///< B输入复用选择 格式 CLU_MXB_CLUa_b a取值范围为[0 1 2 3] 对应不同的CLU b表示选择不同的输入信号
    this->FN = 0;     ///< 真值表 格式 CLU_FN_x x取值范围为[A NOTA A_NOTB ...]对应为最简与或式下的最小相 例如 y=a+bc+!c 表示为 CLU_FN_A|CLU_FN_B_C|CLU_FN_NOTC
    this->OUTSEL = 0; ///< 输出选择 0: D 触发器输出 1: LUT 输出
    this->OEN = 0;    ///< 输出使能 0: 关闭 1: 使能
    this->CLKINV = 0; ///< D 触发器时钟电平 0: 同相 1: 反向
    this->CLKSEL = 0; ///< D 触发器时钟选择 0x0: 进位输入 0x1: MXA 输入 0x2: ALTCLK0 0x3: ALTCLK1
}
/**
 * @brief CLU模块时钟使能
 */
void CLU_Enable(CLU_TypeDef *CLUx)
{
    SYS_ModuleClockCmd(SYS_Module_CL0, ENABLE);
}
/**
 * @brief CLU模块时钟关闭
 */
void CLU_Disable(CLU_TypeDef *CLUx)
{
    SYS_ModuleClockCmd(SYS_Module_CL0, DISABLE);
}
/**
 * @brief 获取CLU的输出值
 */
u8 CLU_ReadOutVolue(CLU_TypeDef *CLUx, u8 CLU_MODEL_CLUx)
{
    u8 OutVolue;
    if (CLUx->OUT & CLU_MODEL_CLUx)
    {
        OutVolue = 1;
    }
    else
    {
        OutVolue = 0;
    }
    return OutVolue;
}

/*! @} */
