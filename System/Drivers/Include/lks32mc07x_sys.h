/**
 * @file
 * @copyright (C)2015, LINKO SEMICONDUCTOR Co.ltd
 * @brief 文件名称： lks32mc07x_sys.h\n
 * 文件标识： 无 \n
 * 内容摘要： sys驱动头文件 \n
 * 其它说明： 无 \n
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2023年02月12日 <td>1.0     <td>ywx      <td>创建
 * </table>
 */

#ifndef __lks32mc07x_SYS_H
#define __lks32mc07x_SYS_H
#include "lks32mc07x_lib.h"

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

    /**
     *@brief 模拟模块系统寄存器对象定义
     */

    typedef struct
    {
        __IO u32 ADC;  // 0x00)
        __IO u32 INFO; // 0x04)
        __IO u32 DBG;  // 0x08)

        __IO u32 null7;    // 0x0C)
        __IO u32 REG0;     // 0x10)
        __IO u32 REG1;     // 0x14)
        __IO u32 REG2;     // 0x18)
        __IO u32 REG3;     // 0x1C)
        __IO u32 REG4;     // 0x20)
        __IO u32 REG5;     // 0x24)
        __IO u32 REG6;     // 0x28)
        __IO u32 REG7;     // 0x2C)
        __IO u32 REG8;     // 0x30)
        __IO u32 REG9;     // 0x34)
        __IO u32 REGA;     // 0x38)
        __IO u32 REGB;     // 0x3C)
        __IO u32 REGC;     // 0x40)
        __IO u32 null1;    // 0x44
        __IO u32 null2;    // 0x48
        __IO u32 null3;    // 0x4C
        __IO u32 null4;    // 0x50
        __IO u32 null5;    // 0x54
        __IO u32 null6;    // 0x58
        __IO u32 DAC_CTRL; // 0x5C)
        __IO u32 DAC0;     // 0x60)
        __IO u32 DAC1;     // 0x64)
        __IO u32 DAC0_AMC; // 0x68)
        __IO u32 DAC0_DC;  // 0x6C)
        __IO u32 DAC1_AMC; // 0x70)
        __IO u32 DAC1_DC;  // 0x74)
    } AFE_TypeDef;
#define AFE ((AFE_TypeDef *)(SYS_BASE))

    /**
     *@brief 数字模块系统配置寄存器对象定义
     */
    typedef struct
    {
        __IO u32 CLK_CFG;    // 0x80)
        __IO u32 IO_CFG;     // 0x84)
        __IO u32 DBG_CFG;    // 0x88)
        __IO u32 null;       // 0x8c
        __IO u32 CLK_DIV0;   // 0x90)  // SPI clock div
        __IO u32 CLK_DIV1;   // 0x94)  // I2C clock div
        __IO u32 CLK_DIV2;   // 0x98)  // UART0/1 clock div
        __IO u32 CLK_FEN;    // 0x9C)  // perapheral clock enable
        __IO u32 TRIM;       // 0xA0)
        __IO u32 SFT_RST;    // 0xA4)
        __IO u32 WR_PROTECT; // 0xA8)
        __IO u32 MBIST;      // 0xC0)
        __IO u32 null7;      // 0xc4
        __IO u32 null8;      // 0xc8
        __IO u32 null9;      // 0xcc
        __IO u32 FLSE;       // 0xD0)
        __IO u32 FLSP;       // 0xD4)
        __IO u32 FLST;       // 0xD8)
        __IO u32 null10;     // 0xDc)
        __IO u32 SBIST;      // 0xE0)
        __IO u32 TEST;       // 0xFC)
    } SYS_TypeDef;
#define SYS ((SYS_TypeDef *)(SYS_BASE + 0x80))

    /**
     *@brief 系统初始化结构体句柄，初始化时请定义该句柄，并用其它地址来传参
     */
    typedef struct
    {
        uint32_t PLL_SrcSel; /*PLL信号输入源选择，RC时钟或外部晶体*/
        uint32_t PLL_DivSel; /*选择8个时钟周期中，哪个周期输出时钟*/
        uint32_t Clk_Sel;    /**选择4MHz HS时钟或者PLL作为主时钟*/

        uint32_t Clk_DivSPI;  /*SPI I2C时钟分频*/
        uint32_t Clk_DivUART; /*UART时钟分频*/
        uint32_t Clk_FEN;     /*模块时钟使能*/

        uint32_t WDT_Ena;       /*使能看门狗*/
        uint32_t PORFilter_Ena; /*使能POR滤波*/
    } SYS_InitTypeDef;

/*PLL信号输入源选择*/
#define SYS_PLLSRSEL_RCH 0x00     /*使用4MHz RC时钟*/
#define SYS_PLLSRSEL_CRYSTAL 0x01 /*使用晶体时钟*/

/* PLL 或者 HS 时钟选择*/
#define CLK_SEL_HS 0x00
#define CLK_SEL_PLL 0x01

#define SYS_MCLK_96M_RC 0x01
#define SYS_MCLK_48M_RC 0x02
#define SYS_MCLK_24M_RC 0x03
#define SYS_MCLK_12M_RC 0x04
#define SYS_MCLK_32K_RC 0x05

#define SYS_MCLK_96M_XTAL 0x11
#define SYS_MCLK_48M_XTAL 0x12
#define SYS_MCLK_24M_XTAL 0x13
#define SYS_MCLK_12M_XTAL 0x14

/*SPI时钟分频*/
#define SYS_Clk_SPIDiv1 0
#define SYS_Clk_SPIDiv2 1
#define SYS_Clk_SPIDiv4 2
#define SYS_Clk_SPIDiv8 3

/*UART时钟分频*/
#define SYS_Clk_UARTDiv1 0
#define SYS_Clk_UARTDiv2 1
#define SYS_Clk_UARTDiv4 2
#define SYS_Clk_UARTDiv8 3

/*数字模块位定义*/
#define SYS_Module_SPI0 BIT0
#define SYS_Module_I2C0 BIT1
#define SYS_Module_CMP BIT2
#define SYS_Module_HALL0 BIT3
#define SYS_Module_TIMER0 BIT4
#define SYS_Module_TIMER1 BIT5
#define SYS_Module_TIMER2 BIT6
#define SYS_Module_TIMER3 BIT7
#define SYS_Module_QEP0 BIT8
#define SYS_Module_QEP1 BIT9
#define SYS_Module_MCPWM0 BIT10
#define SYS_Module_GPIO BIT11
#define SYS_Module_UART0 BIT14
#define SYS_Module_UART1 BIT15
#define SYS_Module_CRC0 BIT16
#define SYS_Module_DSP0 BIT17
#define SYS_Module_CAN0 BIT19
#define SYS_Module_SIF0 BIT20
#define SYS_Module_CL0 BIT21

/*模拟模块定义*/
#define SYS_AnalogModule_ADC BIT0   // ADC
#define SYS_AnalogModule_OPA0 BIT2  // OPA0
#define SYS_AnalogModule_OPA1 BIT3  // OPA1
#define SYS_AnalogModule_OPA2 BIT4  // OPA2
#define SYS_AnalogModule_OPA3 BIT5  // OPA3
#define SYS_AnalogModule_CMP0 BIT6  // CMP0
#define SYS_AnalogModule_CMP1 BIT7  // CMP1
#define SYS_AnalogModule_BGP BIT8   // BGP
#define SYS_AnalogModule_DAC1 BIT9  // BGP
#define SYS_AnalogModule_RCH BIT10  // RCH
#define SYS_AnalogModule_CMP2 BIT11 // CMP2
#define SYS_AnalogModule_DAC0 BIT12 // DAC
#define SYS_AnalogModule_TMP BIT13  // TEMPsss
#define SYS_AnalogModule_XTAL BIT14 // XTAL
#define SYS_AnalogModule_PLL BIT15  // PLL

    /**
     *@brief IWDG寄存器结构体句柄
     */
    typedef struct
    {
        __IO uint32_t PSW; /**<IWDG密码寄存器*/
        __IO uint32_t CFG; /**<IWDG配置寄存器*/
        __IO uint32_t CLR; /**<IWDG清零寄存器*/
        __IO uint32_t WTH; /**<IWDG计数器定时唤醒门限值寄存器*/
        __IO uint32_t RTH; /**<IWDG计数器超时复位门限值寄存器*/
        __IO uint32_t CNT; /**<IWDG计数器当前计数值寄存器*/
    } IWDG_TypeDef;
/**
 * IWDG结构体基地址定义
 */
#ifndef IWDG
#define IWDG ((IWDG_TypeDef *)IWDG_BASE)
#endif
    /**
     *@brief IWDG初始化结构体句柄
     */
    typedef struct
    {
        u32 DWK_EN; /**< 深度休眠定时唤醒使能*/
        u32 WDG_EN; /**< 独立看门狗使能*/
        u32 WTH;    /**< 看门狗定时唤醒时间（21位计数器，但低12恒位0）*/
        u32 RTH;    /**< 看门狗超时复位时间*/
    } IWDG_InitTypeDef;

#define SECOND2IWDGCNT(x) ((u32)(32000 * (float)x + 0x400) & 0x1ff000) /**<看门狗时间计算*/

    void IWDG_Init(IWDG_InitTypeDef *);      // 看门狗初始化
    void IWDG_StrutInit(IWDG_InitTypeDef *); // 看门狗配置结构体初始化
    void IWDG_DISABLE(void);                 // 关闭看门狗
    void IWDG_ENABLE(void);                  // 看门狗使能
    void IWDG_Feed(void);                    // 看门狗喂狗

    /*模块使能*/
    void SYS_ModuleClockCmd(uint32_t nModule, FuncState state);
    void SYS_AnalogModuleClockCmd(uint32_t nModule, FuncState state);

    /*模块软复位*/
    void SYS_SoftResetModule(uint32_t nModule);
    void SYS_SoftReset_all(uint32_t state);

    /*系统时钟配置*/
    void SYS_MclkChoice(u8 SYS_MCLK_x);

    /*获取当前时钟*/
    u32 SYS_ReadMcuClk(void);

    /*外设时钟分频设置*/
    void SYS_UartClkDiv(u16 div);
    void SYS_I2CClkDiv(u16 div);
    void SYS_SPIClkDiv(u16 div);

    /*SYS清零复位*/
    void SYS_ClearRst(void);

    /*SYS时钟初始化*/
    void SYS_Init(SYS_InitTypeDef *SYS_InitStruct);

    /*SYS时钟结构体初始化*/
    void SYS_StructInit(SYS_InitTypeDef *SYS_InitStruct);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif /*__lks32mc07x_SYS_H */

/************************ (C) COPYRIGHT LINKO SEMICONDUCTOR *****END OF FILE****/
