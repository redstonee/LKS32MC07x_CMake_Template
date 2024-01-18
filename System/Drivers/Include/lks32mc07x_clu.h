/**
 * @file
 * @brief        CLU库函数头文件
 * @author       YangZJ
 * @date         2023-02-27
 *  */
#ifndef __LKS32MC07x_CLU_H
#define __LKS32MC07x_CLU_H
///< Includes ------------------------------------------------------------------
#include "lks32mc07x.h"
#include "lks32mc07x_sys.h"
#include "string.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus


typedef struct
{
    __IO u32 EN;  ///< 0x00 CL0 使能寄存器
    __IO u32 IE;  ///< 0x04 CL0 中断使能寄存器
    __IO u32 IF;  ///< 0x08 CL0 中断标志寄存器
    __IO u32 OUT; ///< 0x0C CL0 输出寄存器
    __IO u32 MX;  ///< 0x10 CL0 输入多路复选寄存器
    __IO u32 FN;  ///< 0x14 CL0 功能选择寄存器
    __IO u32 CF;  ///< 0x18 CL0 配置寄存器
} CLU_TypeDef;

#ifndef CLU
#define CLU ((CLU_TypeDef *)CL0_BASE)
#endif

typedef struct
{
    u32 EN;     ///< 模块使能 0关闭模块 1打开模块
    u32 FIE;    ///< 下降沿中断使能
    u32 RIE;    ///< 上升沿中断使能
    u32 MXA;    ///< A输入复用选择 格式 CLU_MXA_CLUa_b a取值范围为[0 1 2 3] 对应不同的CLU b表示选择不同的输入信号
    u32 MXB;    ///< B输入复用选择 格式 CLU_MXB_CLUa_b a取值范围为[0 1 2 3] 对应不同的CLU b表示选择不同的输入信号
    u32 FN;     ///< 真值表 格式 CLU_FN_x x取值范围为[A NOTA A_NOTB ...]对应为最简与或式下的最小相 例如 y=a+bc+!c 表示为 CLU_FN_A|CLU_FN_B_C|CLU_FN_NOTC
    u32 OUTSEL; ///< 输出选择 0: D 触发器输出 1: LUT 输出
    u32 OEN;    ///< 输出使能 0: 关闭 1: 使能
    u32 CLKINV; ///< D 触发器时钟电平 0: 同相 1: 反向
    u32 CLKSEL; ///< D 触发器时钟选择 0x0: 进位输入 0x1: MXA 输入 0x2: ALTCLK0 0x3: ALTCLK1
} CLU_InitTypeDef;

#define CLU_MODEL_CLU0 BIT0 ///< CLU0 CL0里面有4个CLU 这里用BIT0 BIT1 BIT2 BIT3做区分 不可修改
#define CLU_MODEL_CLU1 BIT1 ///< CLU1
#define CLU_MODEL_CLU2 BIT2 ///< CLU2
#define CLU_MODEL_CLU3 BIT3 ///< CLU3

#define CLU_MXA_CLU0_CLU0OUT 0       ///< 使用 CLU0OUT 作为CLU0_A的输入
#define CLU_MXA_CLU0_CLU1OUT 1       ///< 使用 CLU1OUT 作为CLU0_A的输入
#define CLU_MXA_CLU0_CLU2OUT 2       ///< 使用 CLU2OUT 作为CLU0_A的输入
#define CLU_MXA_CLU0_CLU3OUT 3       ///< 使用 CLU3OUT 作为CLU0_A的输入
#define CLU_MXA_CLU0_Timer0ch0ovfl 4 ///< 使用 Timer0ch0ovfl 作为CLU0_A的输入
#define CLU_MXA_CLU0_Timer1ch0ovfl 5 ///< 使用 Timer1ch0ovfl 作为CLU0_A的输入
#define CLU_MXA_CLU0_PWM0 6          ///< 使用 PWM0 作为CLU0_A的输入
#define CLU_MXA_CLU0_PWM1 7          ///< 使用 PWM1 作为CLU0_A的输入
#define CLU_MXA_CLU0_P0_0 8          ///< 使用 P0_0 作为CLU0_A的输入
#define CLU_MXA_CLU0_P0_3 9          ///< 使用 P0_3 作为CLU0_A的输入
#define CLU_MXA_CLU0_P0_5 10         ///< 使用 P0_5 作为CLU0_A的输入
#define CLU_MXA_CLU0_P0_7 11         ///< 使用 P0_7 作为CLU0_A的输入
#define CLU_MXA_CLU0_P2_12 12        ///< 使用 P2_12 作为CLU0_A的输入
#define CLU_MXA_CLU0_P0_12 13        ///< 使用 P0_12 作为CLU0_A的输入
#define CLU_MXA_CLU0_P0_14 14        ///< 使用 P0_14 作为CLU0_A的输入
#define CLU_MXA_CLU0_P1_0 15         ///< 使用 P1_0 作为CLU0_A的输入

#define CLU_MXA_CLU1_CLU0OUT 0       ///< 使用 CLU0OUT 作为CLU1_A的输入
#define CLU_MXA_CLU1_CLU1OUT 1       ///< 使用 CLU1OUT 作为CLU1_A的输入
#define CLU_MXA_CLU1_CLU2OUT 2       ///< 使用 CLU2OUT 作为CLU1_A的输入
#define CLU_MXA_CLU1_CLU3OUT 3       ///< 使用 CLU3OUT 作为CLU1_A的输入
#define CLU_MXA_CLU1_Timer0ch1ovfl 4 ///< 使用 Timer0ch1ovfl 作为CLU1_A的输入
#define CLU_MXA_CLU1_Timer1ch1ovfl 5 ///< 使用 Timer1ch1ovfl 作为CLU1_A的输入
#define CLU_MXA_CLU1_PWM2 6          ///< 使用 PWM2 作为CLU1_A的输入
#define CLU_MXA_CLU1_PWM3 7          ///< 使用 PWM3 作为CLU1_A的输入
#define CLU_MXA_CLU1_P0_0 8          ///< 使用 P0_0 作为CLU1_A的输入
#define CLU_MXA_CLU1_P0_2 9          ///< 使用 P0_2 作为CLU1_A的输入
#define CLU_MXA_CLU1_P0_5 10         ///< 使用 P0_5 作为CLU1_A的输入
#define CLU_MXA_CLU1_P0_6 11         ///< 使用 P0_6 作为CLU1_A的输入
#define CLU_MXA_CLU1_P2_12 12        ///< 使用 P2_12 作为CLU1_A的输入
#define CLU_MXA_CLU1_P0_11 13        ///< 使用 P0_11 作为CLU1_A的输入
#define CLU_MXA_CLU1_P0_14 14        ///< 使用 P0_14 作为CLU1_A的输入
#define CLU_MXA_CLU1_P0_15 15        ///< 使用 P0_15 作为CLU1_A的输入

#define CLU_MXA_CLU2_CLU0OUT 0       ///< 使用 CLU0OUT 作为CLU2_A的输入
#define CLU_MXA_CLU2_CLU1OUT 1       ///< 使用 CLU1OUT 作为CLU2_A的输入
#define CLU_MXA_CLU2_CLU2OUT 2       ///< 使用 CLU2OUT 作为CLU2_A的输入
#define CLU_MXA_CLU2_CLU3OUT 3       ///< 使用 CLU3OUT 作为CLU2_A的输入
#define CLU_MXA_CLU2_Timer2ch0ovfl 4 ///< 使用 Timer2ch0ovfl 作为CLU2_A的输入
#define CLU_MXA_CLU2_Timer3ch0ovfl 5 ///< 使用 Timer3ch0ovfl 作为CLU2_A的输入
#define CLU_MXA_CLU2_PWM0 6          ///< 使用 PWM0 作为CLU2_A的输入
#define CLU_MXA_CLU2_PWM2 7          ///< 使用 PWM2 作为CLU2_A的输入
#define CLU_MXA_CLU2_P2_8 8          ///< 使用 P2_8 作为CLU2_A的输入
#define CLU_MXA_CLU2_P1_13 9         ///< 使用 P1_13 作为CLU2_A的输入
#define CLU_MXA_CLU2_P1_15 10        ///< 使用 P1_15 作为CLU2_A的输入
#define CLU_MXA_CLU2_P1_10 11        ///< 使用 P1_10 作为CLU2_A的输入
#define CLU_MXA_CLU2_P2_1 12         ///< 使用 P2_1 作为CLU2_A的输入
#define CLU_MXA_CLU2_P2_4 13         ///< 使用 P2_4 作为CLU2_A的输入
#define CLU_MXA_CLU2_P2_6 14         ///< 使用 P2_6 作为CLU2_A的输入
#define CLU_MXA_CLU2_P2_14 15        ///< 使用 P2_14 作为CLU2_A的输入

#define CLU_MXA_CLU3_CLU0OUT 0       ///< 使用 CLU0OUT 作为CLU3_A的输入
#define CLU_MXA_CLU3_CLU1OUT 1       ///< 使用 CLU1OUT 作为CLU3_A的输入
#define CLU_MXA_CLU3_CLU2OUT 2       ///< 使用 CLU2OUT 作为CLU3_A的输入
#define CLU_MXA_CLU3_CLU3OUT 3       ///< 使用 CLU3OUT 作为CLU3_A的输入
#define CLU_MXA_CLU3_Timer2ch1ovfl 4 ///< 使用 Timer2ch1ovfl 作为CLU3_A的输入
#define CLU_MXA_CLU3_Timer3ch1ovfl 5 ///< 使用 Timer3ch1ovfl 作为CLU3_A的输入
#define CLU_MXA_CLU3_PWM1 6          ///< 使用 PWM1 作为CLU3_A的输入
#define CLU_MXA_CLU3_PWM3 7          ///< 使用 PWM3 作为CLU3_A的输入
#define CLU_MXA_CLU3_P2_8 8          ///< 使用 P2_8 作为CLU3_A的输入
#define CLU_MXA_CLU3_P3_9 9          ///< 使用 P3_9 作为CLU3_A的输入
#define CLU_MXA_CLU3_P1_15 10        ///< 使用 P1_15 作为CLU3_A的输入
#define CLU_MXA_CLU3_P2_0 11         ///< 使用 P2_0 作为CLU3_A的输入
#define CLU_MXA_CLU3_P2_1 12         ///< 使用 P2_1 作为CLU3_A的输入
#define CLU_MXA_CLU3_P2_3 13         ///< 使用 P2_3 作为CLU3_A的输入
#define CLU_MXA_CLU3_P2_6 14         ///< 使用 P2_6 作为CLU3_A的输入
#define CLU_MXA_CLU3_P2_13 15        ///< 使用 P2_13 作为CLU3_A的输入

#define CLU_MXB_CLU0_CLU0OUT 0 ///< 使用 CLU0OUT 作为CLU0_B的输入
#define CLU_MXB_CLU0_CLU1OUT 1 ///< 使用 CLU1OUT 作为CLU0_B的输入
#define CLU_MXB_CLU0_CLU2OUT 2 ///< 使用 CLU2OUT 作为CLU0_B的输入
#define CLU_MXB_CLU0_CLU3OUT 3 ///< 使用 CLU3OUT 作为CLU0_B的输入
#define CLU_MXB_CLU0_ADBUSY0 4 ///< 使用 ADBUSY0 作为CLU0_B的输入
#define CLU_MXB_CLU0_ADBUSY1 5 ///< 使用 ADBUSY1 作为CLU0_B的输入
#define CLU_MXB_CLU0_PWM3 6    ///< 使用 PWM3 作为CLU0_B的输入
#define CLU_MXB_CLU0_SPIMOSI 7 ///< 使用 SPIMOSI 作为CLU0_B的输入
#define CLU_MXB_CLU0_P0_2 8    ///< 使用 P0_2 作为CLU0_B的输入
#define CLU_MXB_CLU0_P0_4 9    ///< 使用 P0_4 作为CLU0_B的输入
#define CLU_MXB_CLU0_P0_6 10   ///< 使用 P0_6 作为CLU0_B的输入
#define CLU_MXB_CLU0_P2_11 11  ///< 使用 P2_11 作为CLU0_B的输入
#define CLU_MXB_CLU0_P0_11 12  ///< 使用 P0_11 作为CLU0_B的输入
#define CLU_MXB_CLU0_P0_13 13  ///< 使用 P0_13 作为CLU0_B的输入
#define CLU_MXB_CLU0_P0_15 14  ///< 使用 P0_15 作为CLU0_B的输入
#define CLU_MXB_CLU0_P2_7 15   ///< 使用 P2_7 作为CLU0_B的输入

#define CLU_MXB_CLU1_CLU0OUT 0 ///< 使用 CLU0OUT 作为CLU1_B的输入
#define CLU_MXB_CLU1_CLU1OUT 1 ///< 使用 CLU1OUT 作为CLU1_B的输入
#define CLU_MXB_CLU1_CLU2OUT 2 ///< 使用 CLU2OUT 作为CLU1_B的输入
#define CLU_MXB_CLU1_CLU3OUT 3 ///< 使用 CLU3OUT 作为CLU1_B的输入
#define CLU_MXB_CLU1_ADBUSY0 4 ///< 使用 ADBUSY0 作为CLU1_B的输入
#define CLU_MXB_CLU1_ADBUSY1 5 ///< 使用 ADBUSY1 作为CLU1_B的输入
#define CLU_MXB_CLU1_PWM1 6    ///< 使用 PWM1 作为CLU1_B的输入
#define CLU_MXB_CLU1_SPIMISO 7 ///< 使用 SPIMISO 作为CLU1_B的输入
#define CLU_MXB_CLU1_P0_3 8    ///< 使用 P0_3 作为CLU1_B的输入
#define CLU_MXB_CLU1_P0_4 9    ///< 使用 P0_4 作为CLU1_B的输入
#define CLU_MXB_CLU1_P0_7 10   ///< 使用 P0_7 作为CLU1_B的输入
#define CLU_MXB_CLU1_P2_11 11  ///< 使用 P2_11 作为CLU1_B的输入
#define CLU_MXB_CLU1_P0_12 12  ///< 使用 P0_12 作为CLU1_B的输入
#define CLU_MXB_CLU1_P0_13 13  ///< 使用 P0_13 作为CLU1_B的输入
#define CLU_MXB_CLU1_P1_0 14   ///< 使用 P1_0 作为CLU1_B的输入
#define CLU_MXB_CLU1_P2_7 15   ///< 使用 P2_7 作为CLU1_B的输入

#define CLU_MXB_CLU2_CLU0OUT 0 ///< 使用 CLU0OUT 作为CLU2_B的输入
#define CLU_MXB_CLU2_CLU1OUT 1 ///< 使用 CLU1OUT 作为CLU2_B的输入
#define CLU_MXB_CLU2_CLU2OUT 2 ///< 使用 CLU2OUT 作为CLU2_B的输入
#define CLU_MXB_CLU2_CLU3OUT 3 ///< 使用 CLU3OUT 作为CLU2_B的输入
#define CLU_MXB_CLU2_PWM1 4    ///< 使用 PWM1 作为CLU2_B的输入
#define CLU_MXB_CLU2_PWM3 5    ///< 使用 PWM3 作为CLU2_B的输入
#define CLU_MXB_CLU2_I2CSDA 6  ///< 使用 I2CSDA 作为CLU2_B的输入
#define CLU_MXB_CLU2_SPICLK 7  ///< 使用 SPICLK 作为CLU2_B的输入
#define CLU_MXB_CLU2_P3_9 8    ///< 使用 P3_9 作为CLU2_B的输入
#define CLU_MXB_CLU2_P1_14 9   ///< 使用 P1_14 作为CLU2_B的输入
#define CLU_MXB_CLU2_P2_0 10   ///< 使用 P2_0 作为CLU2_B的输入
#define CLU_MXB_CLU2_P1_11 11  ///< 使用 P1_11 作为CLU2_B的输入
#define CLU_MXB_CLU2_P2_3 12   ///< 使用 P2_3 作为CLU2_B的输入
#define CLU_MXB_CLU2_P2_5 13   ///< 使用 P2_5 作为CLU2_B的输入
#define CLU_MXB_CLU2_P2_13 14  ///< 使用 P2_13 作为CLU2_B的输入
#define CLU_MXB_CLU2_P2_15 15  ///< 使用 P2_15 作为CLU2_B的输入

#define CLU_MXB_CLU3_CLU0OUT 0 ///< 使用 CLU0OUT 作为CLU3_B的输入
#define CLU_MXB_CLU3_CLU1OUT 1 ///< 使用 CLU1OUT 作为CLU3_B的输入
#define CLU_MXB_CLU3_CLU2OUT 2 ///< 使用 CLU2OUT 作为CLU3_B的输入
#define CLU_MXB_CLU3_CLU3OUT 3 ///< 使用 CLU3OUT 作为CLU3_B的输入
#define CLU_MXB_CLU3_PWM0 4    ///< 使用 PWM0 作为CLU3_B的输入
#define CLU_MXB_CLU3_PWM2 5    ///< 使用 PWM2 作为CLU3_B的输入
#define CLU_MXB_CLU3_I2CSCL 6  ///< 使用 I2CSCL 作为CLU3_B的输入
#define CLU_MXB_CLU3_SPICSN 7  ///< 使用 SPICSN 作为CLU3_B的输入
#define CLU_MXB_CLU3_P1_13 8   ///< 使用 P1_13 作为CLU3_B的输入
#define CLU_MXB_CLU3_P1_14 9   ///< 使用 P1_14 作为CLU3_B的输入
#define CLU_MXB_CLU3_P1_10 10  ///< 使用 P1_10 作为CLU3_B的输入
#define CLU_MXB_CLU3_P1_11 11  ///< 使用 P1_11 作为CLU3_B的输入
#define CLU_MXB_CLU3_P2_4 12   ///< 使用 P2_4 作为CLU3_B的输入
#define CLU_MXB_CLU3_P2_5 13   ///< 使用 P2_5 作为CLU3_B的输入
#define CLU_MXB_CLU3_P2_14 14  ///< 使用 P2_14 作为CLU3_B的输入
#define CLU_MXB_CLU3_P2_15 15  ///< 使用 P2_15 作为CLU3_B的输入

#define CLU_FN_0 0x0               ///< CLU真值表的最小相 0        注意最小相之间只能用 | （C语言按位或）
#define CLU_FN_1 0xff              ///< CLU真值表的最小相 1        注意最小相之间只能用 | （C语言按位或）
#define CLU_FN_A 0xf0              ///< CLU真值表的最小相 a        注意最小相之间只能用 | （C语言按位或）
#define CLU_FN_NOTA 0x0f           ///< CLU真值表的最小相 !a       注意最小相之间只能用 | （C语言按位或）
#define CLU_FN_B 0xcc              ///< CLU真值表的最小相 b        注意最小相之间只能用 | （C语言按位或）
#define CLU_FN_NOTB 0x33           ///< CLU真值表的最小相 !b       注意最小相之间只能用 | （C语言按位或）
#define CLU_FN_C 0xaa              ///< CLU真值表的最小相 c        注意最小相之间只能用 | （C语言按位或）
#define CLU_FN_NOTC 0x55           ///< CLU真值表的最小相 !c       注意最小相之间只能用 | （C语言按位或）
#define CLU_FN_A_B 0xc0            ///< CLU真值表的最小相 a&b      注意最小相之间只能用 | （C语言按位或）
#define CLU_FN_NOTA_NOTB 0x03      ///< CLU真值表的最小相 !a&!b    注意最小相之间只能用 | （C语言按位或）
#define CLU_FN_NOTA_B 0x0c         ///< CLU真值表的最小相 !a&b     注意最小相之间只能用 | （C语言按位或）
#define CLU_FN_A_NOTB 0x30         ///< CLU真值表的最小相 a&!b     注意最小相之间只能用 | （C语言按位或）
#define CLU_FN_A_C 0xa0            ///< CLU真值表的最小相 a&c      注意最小相之间只能用 | （C语言按位或）
#define CLU_FN_NOTA_NOTC 0x05      ///< CLU真值表的最小相 !a&!c    注意最小相之间只能用 | （C语言按位或）
#define CLU_FN_NOTA_C 0x0a         ///< CLU真值表的最小相 !a&c     注意最小相之间只能用 | （C语言按位或）
#define CLU_FN_A_NOTC 0x50         ///< CLU真值表的最小相 a&!c     注意最小相之间只能用 | （C语言按位或）
#define CLU_FN_B_C 0x88            ///< CLU真值表的最小相 b&c      注意最小相之间只能用 | （C语言按位或）
#define CLU_FN_NOTB_NOTC 0x11      ///< CLU真值表的最小相 !b&!c    注意最小相之间只能用 | （C语言按位或）
#define CLU_FN_NOTB_C 0x22         ///< CLU真值表的最小相 !b&c     注意最小相之间只能用 | （C语言按位或）
#define CLU_FN_B_NOTC 0x44         ///< CLU真值表的最小相 b&!c     注意最小相之间只能用 | （C语言按位或）
#define CLU_FN_NOTA_NOTB_NOTC 0x01 ///< CLU真值表的最小相 !a&!b&!c 注意最小相之间只能用 | （C语言按位或）
#define CLU_FN_NOTA_NOTB_C 0x02    ///< CLU真值表的最小相 !a&!b&c  注意最小相之间只能用 | （C语言按位或）
#define CLU_FN_NOTA_B_NOTC 0x04    ///< CLU真值表的最小相 !a&b&!c  注意最小相之间只能用 | （C语言按位或）
#define CLU_FN_NOTA_B_C 0x08       ///< CLU真值表的最小相 !a&b&c   注意最小相之间只能用 | （C语言按位或）
#define CLU_FN_A_NOTB_NOTC 0x10    ///< CLU真值表的最小相 a&!b&!c  注意最小相之间只能用 | （C语言按位或）
#define CLU_FN_A_NOTB_C 0x20       ///< CLU真值表的最小相 a&!b&c   注意最小相之间只能用 | （C语言按位或）
#define CLU_FN_A_B_NOTC 0x40       ///< CLU真值表的最小相 a&b&!c   注意最小相之间只能用 | （C语言按位或）
#define CLU_FN_A_B_C 0x80          ///< CLU真值表的最小相 a&b&c    注意最小相之间只能用 | （C语言按位或）

void CLU_Init(CLU_TypeDef *CLUx,u8 CLU_MODEL_CLUx, CLU_InitTypeDef *CLU_InitStruct);
void CLU_StructInit(CLU_InitTypeDef *CLU_InitStruct);

void CLU_Enable(CLU_TypeDef *CLUx);
void CLU_Disable(CLU_TypeDef *CLUx);

u8 CLU_ReadOutVolue(CLU_TypeDef *CLUx,u8 CLU_MODEL_CLUx);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif /*__LKS32MC08x_CLU_H */
