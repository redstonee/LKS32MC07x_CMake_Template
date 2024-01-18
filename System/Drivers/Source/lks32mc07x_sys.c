/**
 * @file
 * @copyright (C)2015, LINKO SEMICONDUCTOR Co.ltd
 * @brief 文件名称： lks32mc07x_sys.c\n
 * 文件标识： 无 \n
 * 内容摘要： SYS外设驱动程序 \n
 * 其它说明： 无 \n
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2023年02月12日 <td>1.0     <td>ywx      <td>创建
 * </table>
 */

#include "lks32mc07x_sys.h"

/**
 * @brief 全局变量存储主时钟频率值
 *
 */
static u32 sys_clk = 96000000;

static void SoftDelay(u32 cnt)
{
    volatile u32 t_cnt;
    for (t_cnt = 0; t_cnt < cnt; t_cnt++)
    {
        __NOP();
    }
}

/**
 *@brief @b 函数名称:   void SYS_Init(SYS_InitTypeDef* SYS_InitStruct)
 *@brief @b 功能描述:   SYS模块初始化函数
 *@see被调用函数：      无
 *@param输入参数：      SYS_InitTypeDef* SYS_InitStruct
 *@param输出参数：      无
 *@return返 回 值：     无
 *@note其它说明：       一般不使用该函数，因为涉及模块较多，比较杂乱，对应里面的配置在各模块
 *                     初始化单独配置。
 *@warning             无
 *@par 示例代码：
 *@code
           SYS_InitTypeDef SYS_InitStruct;
           SYS_StructInit(&SYS_InitStruct);
           SYS_InitStruct.PLL_SrcSel = SYS_PLLSRSEL_RCH;    // 使用内部4MHz晶振作为时钟输入源
           SYS_Init(&SYS_InitStruct);
  @endcode
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2023年02月12日 <td>1.0     <td>ywx      <td>创建
 * </table>
 */
void SYS_Init(SYS_InitTypeDef *SYS_InitStruct)
{
    uint32_t RCHPd, XTALPdn;
    uint32_t tmp1, tmp2;

    SYS_WR_PROTECT = 0x7A83; // 解除系统寄存器写保护

    tmp1 = AFE->REG6;
    tmp1 &= 0x7FFF;
    tmp1 |= (SYS_InitStruct->PLL_SrcSel << 15);
    AFE->REG6 = tmp1;

    if (SYS_InitStruct->PLL_SrcSel == SYS_PLLSRSEL_CRYSTAL)
    {
        RCHPd = DISABLE;  /*RCH(4MHz)时钟关闭*/
        XTALPdn = ENABLE; /*晶体起振电路开启*/
    }
    else
    {
        RCHPd = ENABLE;    /*RCH(4MHz)时钟打开*/
        XTALPdn = DISABLE; /*晶体起振电路关闭*/
    }

    tmp2 = AFE->REG5;
    tmp2 &= 0xBBFF; // 1010 1010 1111 1111
    tmp2 |= (RCHPd << 10);
    tmp2 |= (XTALPdn << 14);
    AFE->REG5 = tmp2;

    SYS_CLK_CFG = SYS_InitStruct->PLL_DivSel + (SYS_InitStruct->Clk_Sel << 8);
    SYS->CLK_DIV0 = SYS_InitStruct->Clk_DivSPI;
    SYS->CLK_DIV2 = SYS_InitStruct->Clk_DivUART;
    SYS->CLK_FEN = SYS_InitStruct->Clk_FEN;
}

/**
 *@brief @b 函数名称:   void SYS_StructInit(SYS_InitTypeDef* SYS_InitStruct)
 *@brief @b 功能描述:   SYS结构体初始化
 *@see被调用函数：      无
 *@param输入参数：      SYS_InitTypeDef* SYS_InitStruct
 *@param输出参数：      无
 *@return返 回 值：     无
 *@note其它说明：       无
 *@warning             无
 *@par 示例代码：
 *@code
           SYS_InitTypeDef SYS_InitStruct;
           SYS_StructInit(&SYS_InitStruct);
  @endcode
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2023年02月12日 <td>1.0     <td>ywx      <td>创建
 * </table>
 */
void SYS_StructInit(SYS_InitTypeDef *SYS_InitStruct)
{
    SYS_InitStruct->PLL_SrcSel = SYS_PLLSRSEL_RCH;
    SYS_InitStruct->PLL_DivSel = 0xFF;
    SYS_InitStruct->Clk_Sel = CLK_SEL_PLL;

    SYS_InitStruct->Clk_DivSPI = SYS_Clk_SPIDiv1;
    SYS_InitStruct->Clk_DivUART = SYS_Clk_UARTDiv1;
    SYS_InitStruct->Clk_FEN = 0;

    SYS_InitStruct->WDT_Ena = DISABLE;
    SYS_InitStruct->PORFilter_Ena = DISABLE;
}

/**
 *@brief @b 函数名称:   void SYS_ClearRst(void)
 *@brief @b 功能描述:   SYS清除复位标志记录
 *@see被调用函数：      无
 *@param输入参数：      无
 *@param输出参数：      无
 *@return返 回 值：     无
 *@note其它说明：       请注意由于复位记录工作于低速时钟域，清除执行完成需要一定时间，不应清
                       除后立即读记录状态
 *@warning             无
 *@par 示例代码：
 *@code
           u32 RSET_VALUE = 0;
           SYS_ClearRst();//清除复位标志记录
           delay_ms(1);
           RSET_VALUE = SYS_GetRstSource();//读取复位源记录值
  @endcode
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2023年02月12日 <td>1.0     <td>ywx      <td>创建
 * </table>
 */
void SYS_ClearRst(void)
{
    SYS->WR_PROTECT = 0x7a83;
    SYS->SFT_RST = 0x0;
    SYS->WR_PROTECT = 0;
}

/**
 *@brief @b 函数名称:   void SYS_ModuleClockCmd(uint32_t nModule, FuncState state)
 *@brief @b 功能描述:   数字模块时钟使能和停止
 *@see被调用枚举：      FuncState
 *@param输入参数：
 *                     state： ENABLE使能 , DISABLE关闭
 *                     nModule：参数可选： \n
 * <table>
 *                     <tr><td> 宏定义                   <td>原始值   <td>说明
 *                     <tr><th> SYS_Module_I2C          <td> BIT0    <td>I2C模块
 *                     <tr><th> SYS_Module_HALL         <td> BIT1    <td>HALL模块
 *                     <tr><th> SYS_Module_TIMER        <td> BIT2    <td>UTIMER模块
 *                     <tr><th> SYS_Module_MCPWM        <td> BIT3    <td>MCPWM模块
 *                     <tr><th> SYS_Module_UART0        <td> BIT4    <td>UART0模块
 *                     <tr><th> SYS_Module_UART1        <td> BIT5    <td>UART1模块
 *                     <tr><th> SYS_Module_DSP          <td> BIT6    <td>DSP模块
 *                     <tr><th> SYS_Module_CAN          <td> BIT7    <td>CAN模块
 *                     <tr><th> SYS_Module_SPI          <td> BIT8    <td>SPI模块
 * </table>
 *@param输出参数：      无
 *@return返 回 值：     无
 *@note其它说明：       无
 *@warning             无
 *@par 示例代码：
 *@code
        SYS_ModuleClockCmd(SYS_Module_SPI,ENABLE);//使能SPI时钟
  @endcode
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author     <th>Description
 * <tr><td>2023年02月12日 <td>1.0     <td>ywx      <td>创建
 * </table>
 */
void SYS_ModuleClockCmd(uint32_t nModule, FuncState state)
{
    SYS->WR_PROTECT = 0x7A83; // 解除系统寄存器写保护

    if (state == ENABLE)
    {
        SYS->CLK_FEN |= nModule;
    }
    else
    {
        SYS->CLK_FEN &= ~nModule;
    }
    SYS->WR_PROTECT = 0x0; // 系统寄存器写保护
}

/**
 *@brief @b 函数名称:   void SYS_AnalogModuleClockCmd(uint32_t nModule, FuncState state)
 *@brief @b 功能描述:   模拟模块使能和停止
 *@see被调用枚举：      FuncState
 *@param输入参数：
 *                     state： ENABLE使能 , DISABLE关闭
 *                     nModule：参数可选： \n
 * <table>
 *                     <tr><td> 宏定义                  <td>说明
 *                     <tr><th> SYS_AnalogModule_ADC    <td>  BIT0  <td> ADC模块
 *                     <tr><th> SYS_AnalogModule_OPA0   <td>  BIT2  <td> OPA0模块
 *                     <tr><th> SYS_AnalogModule_OPA1   <td> BIT3   <td> OPA1模块
 *                     <tr><th> SYS_AnalogModule_OPA2   <td>  BIT4  <td> OPA2模块
 *                     <tr><th> SYS_AnalogModule_OPA3   <td>  BIT5  <td> OPA3模块
 *                     <tr><th> SYS_AnalogModule_CMP0   <td>  BIT6  <td> CMP0模块
 *                     <tr><th> SYS_AnalogModule_CMP1   <td>  BIT7  <td> CMP1模块
 *                     <tr><th> SYS_AnalogModule_BGP    <td>  BIT8  <td> BGP模块
 *                     <tr><th> SYS_AnalogModule_RCH    <td>  BIT10 <td> RCH模块
 *                     <tr><th> SYS_AnalogModule_DAC    <td>  BIT12 <td> DAC模块
 *                     <tr><th> SYS_AnalogModule_TMP    <td>  BIT13 <td> 温度传感器
 *                     <tr><th> SYS_AnalogModule_XTAL   <td>  BIT14 <td> 晶振
 *                     <tr><th> SYS_AnalogModule_PLL    <td>  BIT15 <td> PLL模块
 * </table>
 *@param输出参数：      无
 *@return返 回 值：     无
 *@note其它说明：       无
 *@warning             无
 *@par 示例代码：
 *@code
        SYS_AnalogModuleClockCmd(SYS_AnalogModule_PLL,ENABLE);//使能PLL模块
  @endcode
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author     <th>Description
 * <tr><td>2023年02月12日 <td>1.0     <td>ywx      <td>创建
 * </table>
 */
void SYS_AnalogModuleClockCmd(uint32_t nModule, FuncState state)
{
    SYS->WR_PROTECT = 0x7A83; // 解除系统寄存器写保护

    if (state != DISABLE)
    {
        AFE->REG5 |= nModule;
    }
    else
    {
        AFE->REG5 &= ~nModule;
    }
}

/**
 *@brief @b 函数名称:   void SYS_SoftResetModule(uint32_t nModule)
 *@brief @b 功能描述:   数字模块软复位
 *@see被调用枚举：      无
 *@param输入参数：
 *                     state： ENABLE使能 , DISABLE关闭
 *                     nModule：参数可选： \n
 * <table>
 *                     <tr><td> 宏定义                   <td>原始值   <td>说明
 *                     <tr><th> SYS_Module_I2C          <td> BIT0    <td>I2C模块
 *                     <tr><th> SYS_Module_HALL         <td> BIT1    <td>HALL模块
 *                     <tr><th> SYS_Module_TIMER        <td> BIT2    <td>UTIMER模块
 *                     <tr><th> SYS_Module_MCPWM        <td> BIT3    <td>MCPWM模块
 *                     <tr><th> SYS_Module_UART0        <td> BIT4    <td>UART0模块
 *                     <tr><th> SYS_Module_UART1        <td> BIT5    <td>UART1模块
 *                     <tr><th> SYS_Module_DSP          <td> BIT6    <td>DSP模块
 *                     <tr><th> SYS_Module_CAN          <td> BIT7    <td>CAN模块
 *                     <tr><th> SYS_Module_SPI          <td> BIT8    <td>SPI模块
 * </table>
 *@param输出参数：      无
 *@return返 回 值：     无
 *@note其它说明：       无
 *@warning             无
 *@par 示例代码：
 *@code
        //软复位SPI模块，清除SPI寄存器配置，PC指针复位
        SYS_SoftResetModule(SYS_Module_SPI);
  @endcode
*@par 修改日志:增加延时函数，等待寄存器复位完毕与释放复位操作。
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author     <th>Description
 * <tr><td>2023年02月12日 <td>1.0     <td>ywx      <td>创建
 * </table>
 */
void SYS_SoftResetModule(uint32_t nModule)
{
    SYS->WR_PROTECT = 0x7A83;
    SYS->SFT_RST = nModule;
    SYS->WR_PROTECT = 1;
}

/**
 *@brief @b 函数名称:   void SYS_SoftReset_all(uint32_t state)
 *@brief @b 功能描述:   数字模块软复位
 *@see被调用枚举：      无
 *@param输入参数：
 *                     state： ENABLE使能 , DISABLE关闭
 *                     nModule：参数可选： \n
 *@param输出参数：      无
 *@return返 回 值：     无
 *@note其它说明：       无
 *@warning             无
 *@par 示例代码：
 *@code
        //软复位所有模块，清除相关外设寄存器配置，PC指针复位
        SYS_SoftResetModule(ENABLE);
  @endcode
*@par 修改日志:增加延时函数，等待寄存器复位完毕与释放复位操作。
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author     <th>Description
 * <tr><td>2023年02月12日 <td>1.0     <td>ywx      <td>创建
 * </table>
 */
void SYS_SoftReset_all(uint32_t state)
{
    if (state == 1)
    {
        SYS->WR_PROTECT = 0x7A83;
        SYS->SFT_RST = 0xffffff;
        SYS->WR_PROTECT = 1;
    }
    else
    {
        SYS->WR_PROTECT = 0x7A83;
        SYS->SFT_RST = 0x0;
        SYS->WR_PROTECT = 1;
    }
}

/**
 *@brief @b 函数名称:   void SYS_MclkChoice(u8 SYS_MCLK_x)
 *@brief @b 功能描述:   主时钟选择
 *@see被调用枚举：      无
 *@param输入参数：
 *                     nModule：参数可选： \n
 * <table>
 *                     <tr><td> 宏定义                   <td>原始值   <td>说明
 *
 * 						<tr><th> SYS_MCLK_96M_RC			0x01	96MHz_PLL_RC
 *						<tr><th> SYS_MCLK_48M_RC			0x02	48MHz_PLL_RC
 *						<tr><th> SYS_MCLK_24M_RC    		0x03	24MHz_PLL_RC
 *						<tr><th> SYS_MCLK_12M_RC    		0x04	12MHz_PLL_RC
 *						<tr><th> SYS_MCLK_32K_RC    		0x05	32kHz_LSI
 *						<tr><th> SYS_MCLK_96M_XTAL          0x11	96MHz_PLL_XTAL
 *						<tr><th> SYS_MCLK_48M_XTAL          0x12	48MHz_PLL_XTAL
 *						<tr><th> SYS_MCLK_24M_XTAL          0x13	24MHz_PLL_XTAL
 *						<tr><th> SYS_MCLK_12M_XTAL          0x14	12MHz_PLL_XTAL
 * </table>
 *@param输出参数：      无
 *@return返 回 值：     无
 *@note其它说明：       无
 *@warning             无
 *@par 示例代码：
 *@code
        //软复位SPI模块，清除SPI寄存器配置，PC指针复位
        SYS_MclkChoice(SYS_MCLK_96M_RC);
  @endcode
*@par 修改日志:增加延时函数，等待寄存器复位完毕与释放复位操作。
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author     <th>Description
 * <tr><td>2023年02月12日 <td>1.0     <td>ywx      <td>创建
 * </table>
 */
void SYS_MclkChoice(u8 SYS_MCLK_x)
{
    u32 reg = 0;
    SYS->WR_PROTECT = 0x7a83;
    SYS->CLK_CFG = 0; // 确保MCU工作在HRC
    switch (SYS_MCLK_x)
    {
    case SYS_MCLK_96M_RC:
    {
        AFE->REG5 |= (BIT15); // 打开PLL RCH default open
        AFE->REG6 &= ~BIT15;  // PLL来源于内部8Mhz
        reg = (1 << 8) | (0xff);
        sys_clk = 96000000;
        break;
    }
    case SYS_MCLK_48M_RC:
    {
        AFE->REG5 |= (BIT15); // 打开PLL RCH default open
        AFE->REG6 &= ~BIT15;  // PLL来源于内部8Mhz
        reg = (1 << 8) | (0x55);
        sys_clk = 48000000;
        break;
    }
    case SYS_MCLK_24M_RC:
    {
        AFE->REG5 |= (BIT15); // 打开PLL RCH default open
        AFE->REG6 &= ~BIT15;  // PLL来源于内部8Mhz
        reg = (1 << 8) | (0x11);
        sys_clk = 24000000;
        break;
    }
    case SYS_MCLK_12M_RC:
    {
        AFE->REG5 |= (BIT15); // 打开PLL RCH default open
        AFE->REG6 &= ~BIT15;  // PLL来源于内部8Mhz
        reg = (2 << 8) | (0xFF);
        sys_clk = 12000000;
        break;
    }
    case SYS_MCLK_32K_RC:
    {
        AFE->REG5 |= (BIT15);    // 打开PLL RCH default open
        AFE->REG6 &= ~BIT15;     // PLL来源于内部8Mhz
        reg = (1 << 8) | (0x01); // main clk from LSI
        sys_clk = 12000000;
        break;
    }
    case SYS_MCLK_96M_XTAL:
    {
        // 1.使用晶体时钟的时候，首先将主时钟切为HRC
        SYS->CLK_CFG &= 0xfCff; // 将第8 9 位为置0，主时钟来源HRC
        // 2.开启XTAL PLL
        AFE->REG5 |= (BIT15 | BIT14); // 打开PLL 晶振开关
        AFE->REG6 |= BIT15;           // PLL来源于外部晶振
        reg = (1 << 8) | (0xFF);
        sys_clk = 96000000;
        break;
    }
    case SYS_MCLK_48M_XTAL:
    {
        // 1.使用晶体时钟的时候，首先将主时钟切为HRC
        SYS->CLK_CFG &= 0xfCff; // 将第8 9 位为置0，主时钟来源HRC
        // 2.开启XTAL PLL
        AFE->REG5 |= (BIT15 | BIT14); // 打开PLL 晶振开关
        reg = (1 << 8) | (0x55);
        sys_clk = 48000000;
        break;
    }
    case SYS_MCLK_24M_XTAL:
    {
        // 1.使用晶体时钟的时候，首先将主时钟切为HRC
        SYS->CLK_CFG &= 0xfCff; // 将第8 9 位为置0，主时钟来源HRC
        // 2.开启XTAL PLL
        AFE->REG5 |= (BIT15 | BIT14); // 打开PLL 晶振开关
        reg = (1 << 8) | (0x11);
        sys_clk = 24000000;
        break;
    }
    case SYS_MCLK_12M_XTAL:
    {
        // 1.使用晶体时钟的时候，首先将主时钟切为HRC
        SYS->CLK_CFG &= 0xfCff; // 将第8 9 位为置0，主时钟来源HRC
        // 2.开启XTAL PLL
        AFE->REG5 |= (BIT15 | BIT14); // 打开PLL 晶振开关
        reg = (1 << 8) | (0x01);
        sys_clk = 12000000;
        break;
    }
    }
    // 主时钟切换位PLL时，延时100us
    SoftDelay(0x264F);  // 1个_NOP大约按一个系统时钟周期计算
    SYS->CLK_CFG = reg; // 选择时钟来源和分频
    SYS->WR_PROTECT = 0x0;
}

/**
 *@brief @b 函数名称:  u32 SYS_ReadMcuClk(void)
 *@brief @b 功能描述:   获取当前时钟
 *@see被调用枚举：      无
 *@param输入参数：
 *@param输出参数：      无
 *@return返 回 值：     时钟频率
 *@note其它说明：       无
 *@warning             无
 *@par 示例代码：
 *@code
  @endcode
*@par 修改日志:增加延时函数，等待寄存器复位完毕与释放复位操作。
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author     <th>Description
 * <tr><td>2023年02月12日 <td>1.0     <td>ywx      <td>创建
 * </table>
 */
u32 SYS_ReadMcuClk(void)
{
    return sys_clk;
}

/**
 *@brief @b 函数名称:   void SYS_UartClkDiv(u16 div)
 *@brief @b 功能描述:   串口分频设置
 *@see被调用枚举：      无
 *@param输入参数：
 *                     div： 分频系数
 *@param输出参数：      无
 *@return返 回 值：     无
 *@note其它说明：       无
 *@warning             无
 *@par 示例代码：
 *@code
  @endcode
*@par 修改日志
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author     <th>Description
 * <tr><td>2023年02月12日 <td>1.0     <td>ywx      <td>创建
 * </table>
 */
void SYS_UartClkDiv(u16 div)
{
    SYS->WR_PROTECT = 0x7a83;
    SYS->CLK_DIV2 = div;
    SYS->WR_PROTECT = 0x0;
}

/**
 *@brief @b 函数名称:   void SYS_I2CClkDiv(u16 div)
 *@brief @b 功能描述:   I2C分频设置
 *@see被调用枚举：      无
 *@param输入参数：
 *                     div： 分频系数
 *@param输出参数：      无
 *@return返 回 值：     无
 *@note其它说明：       无
 *@warning             无
 *@par 示例代码：
 *@code
  @endcode
*@par 修改日志
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author     <th>Description
 * <tr><td>2023年02月12日 <td>1.0     <td>ywx      <td>创建
 * </table>
 */
void SYS_I2CClkDiv(u16 div)
{
    SYS->WR_PROTECT = 0x7a83;
    SYS->CLK_DIV0 = div;
    SYS->WR_PROTECT = 0x0;
}

/**
 *@brief @b 函数名称:   void SYS_SPIClkDiv(u16 div)
 *@brief @b 功能描述:   SPI分频设置
 *@see被调用枚举：      无
 *@param输入参数：
 *                     div： 分频系数
 *@param输出参数：      无
 *@return返 回 值：     无
 *@note其它说明：       无
 *@warning             无
 *@par 示例代码：
 *@code
  @endcode
*@par 修改日志
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author     <th>Description
 * <tr><td>2023年02月12日 <td>1.0     <td>ywx      <td>创建
 * </table>
 */
void SYS_SPIClkDiv(u16 div)
{
    SYS->WR_PROTECT = 0x7a83;
    SYS->CLK_DIV0 = div;
    SYS->WR_PROTECT = 0x0;
}

/**
 *@brief @b 函数名称:   void IWDG_Init(IWDG_InitTypeDef *this)
 *@brief @b 功能描述:   看门狗初始化
 *@see被引用内容：       无
 *@param输入参数：       IWDG_InitTypeDef *this 看门狗配置结构体
 *@param输出参数：       无
 *@return返 回 值：      无
 *@note其它说明：        无
 *@warning              无
 *@par 示例代码：
 *@code
            IWDG_InitTypeDef IWDG_InitStruct;
            IWDG_StrutInit(&IWDG_InitStruct);
            IWDG_InitStruct.WDG_EN  = ENABLE;      //使能看门狗
            IWDG_InitStruct.RTH     = SECOND2IWDGCNT(2.0);//设置看门狗
            IWDG_InitStruct.DWK_EN  = DISABLE;     // 深度休眠定时唤醒关闭
            IWDG_InitStruct.WTH     = 0;           // 看门狗定时唤醒时间（21位计数器，但低12恒位0）
            IWDG_Init(&IWDG_InitStruct);
  @endcode
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author      <th>Description
 * <tr><td>2023年02月28日 <td>1.0     <td>cakezhang      <td>创建
 * </table>
 */
void IWDG_Init(IWDG_InitTypeDef *this)
{
    this->RTH = (this->RTH > BIT21) ? BIT21 - 1 : this->RTH;
    this->WTH = (this->WTH > BIT21) ? BIT21 - 1 : this->WTH;
    IWDG->CFG = (this->DWK_EN << 4) | (this->WDG_EN);
    IWDG->PSW = PSW_IWDG_PRE;
    IWDG->RTH = this->RTH;
    if (this->RTH > this->WTH)
    {
        IWDG->WTH = this->RTH - this->WTH;
    }
    else
    {
        IWDG->WTH = 0x001000;
    }
    IWDG->PSW = PSW_IWDG_PRE;
    IWDG->CLR = PSW_IWDG_CLR;
}

/**
 *@brief @b 函数名称:   void IWDG_StrutInit(IWDG_InitTypeDef *this)
 *@brief @b 功能描述:   看门狗配置结构体初始化
 *@see被引用内容：       无
 *@param输入参数：       IWDG_InitTypeDef *this 看门狗配置结构体
 *@param输出参数：       无
 *@return返 回 值：      无
 *@note其它说明：        无
 *@warning              无
 *@par 示例代码：
 *@code
                IWDG_InitTypeDef IWDG_InitStruct;
                IWDG_StrutInit(&IWDG_InitStruct);    //初始化结构体
  @endcode
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author      <th>Description
 * <tr><td>2023年02月28日 <td>1.0     <td>cakezhang      <td>创建
 * </table>
 */
void IWDG_StrutInit(IWDG_InitTypeDef *this)
{
    this->DWK_EN = DISABLE;        // 深度休眠定时唤醒使能
    this->WDG_EN = DISABLE;        // 独立看门狗使能
    this->WTH = SECOND2IWDGCNT(1); // 看门狗定时唤醒时间,大于复位时间后无效
    this->RTH = SECOND2IWDGCNT(2); // 看门狗超时复位时间（21位计数器，但低12恒位0）
                                   // SECOND2IWDGCNT输入参数，秒
}

/**
 *@brief @b 函数名称:   void IWDG_DISABLE(void)
 *@brief @b 功能描述:   关闭看门狗模块
 *@see被引用内容：       无
 *@param输入参数：       无
 *@param输出参数：       无
 *@return返 回 值：      无
 *@note其它说明：        无
 *@warning              无
 *@par 示例代码：
 *@code
                IWDG_DISABLE();    //关闭看门狗模块
  @endcode
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author      <th>Description
 * <tr><td>2023年02月28日 <td>1.0     <td>cakezhang      <td>创建
 * </table>
 */
void IWDG_DISABLE(void)
{
    IWDG->CFG = 0x3c00;
}

/**
 *@brief @b 函数名称:   void IWDG_ENABLE(void)
 *@brief @b 功能描述:   打开看门狗模块
 *@see被引用内容：       无
 *@param输入参数：       无
 *@param输出参数：       无
 *@return返 回 值：      无
 *@note其它说明：        无
 *@warning              无
 *@par 示例代码：
 *@code
                IWDG_ENABLE();    //打开看门狗模块
  @endcode
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author      <th>Description
 * <tr><td>2023年02月28日 <td>1.0     <td>cakezhang      <td>创建
 * </table>
 */
void IWDG_ENABLE(void)
{
    IWDG->CFG = 0x1;
}

/**
 *@brief @b 函数名称:   void IWDG_Feed(void)
 *@brief @b 功能描述:   看门狗喂狗
 *@see被引用内容：       无
 *@param输入参数：       无
 *@param输出参数：       无
 *@return返 回 值：      无
 *@note其它说明：        无
 *@warning              无
 *@par 示例代码：
 *@code
                IWDG_Feed();    //看门狗喂狗
  @endcode
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author      <th>Description
 * <tr><td>2023年02月28日 <td>1.0     <td>cakezhang      <td>创建
 * </table>
 */
void IWDG_Feed(void)
{
    IWDG->PSW = PSW_IWDG_PRE;
    IWDG->CLR = PSW_IWDG_CLR;
}

/************************ (C) COPYRIGHT LINKO SEMICONDUCTOR *****END OF FILE****/
