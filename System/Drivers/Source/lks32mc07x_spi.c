/*******************************************************************************
 * 版权所有 (C)2015, LINKO SEMICONDUCTOR Co.ltd
 *
 * 文件名称： lks32mc07x_spi.c
 * 文件标识：
 * 内容摘要： SPI外设驱动程序
 * 其它说明： 无
 * 当前版本： V 1.0
 * 作    者：
 * 完成日期：
 *
 * 修改记录1：
 * 修改日期：
 * 版 本 号：V 1.0
 * 修 改 人：
 * 修改内容：创建
 *
 * 修改记录2：
 * 修改日期：
 * 版 本 号：
 * 修 改 人：
 * 修改内容：
 *
 *******************************************************************************/
#include "lks32mc07x_lib.h"

/**
 *@brief @b 函数名称:   void SPI_Init(SPI_TypeDef* SPIx, SPI_InitTypeDef* SPI_InitStruct)
 *@brief @b 功能描述:   SPI初始化函数
 *@see被引用内容：       SYS_ModuleClockCmd()
 *@param输入参数：       SPIx：SPI , SPI_InitTypeDef *SPI_InitStruct
 *@param输出参数：       无
 *@return返 回 值：      无
 *@note其它说明：        无
 *@warning              无
 *@par 示例代码：
 *@code
            SPI_InitTypeDef SPI_InitStruct;
            SPI_StructInit(&SPI_InitStruct);              //SPI结构体初始化
            SPI_InitStruct.Duplex = SPI_Full;             //双工模式设置
            SPI_InitStruct.Mode = SPI_Master;             //master主机模式
            SPI_InitStruct.EN = ENABLE;                   //使能SPI模块
            SPI_InitStruct.DMA = SPI_DMA_DISABLE;         // 选择SPI搬移方式，由MCU搬运数据到SPI
            SPI_InitStruct.Trig = 0;                      //内部自动触发传输
            SPI_InitStruct.DataOrder = SPI_FIRSTSEND_MSB; //该字节先发送 MSB
            SPI_InitStruct.CPHA = 0;                      //第一个沿为发送数据时刻
            SPI_InitStruct.CPOL = 0;                      //CLK默认高电平
            SPI_InitStruct.BaudRate = 30;                 //传输速度96MHZ/(2*(30+1))= 1.548MHZ
            SPI_InitStruct.ByteLength = 0;                //发送零个字节
            SPI_InitStruct.IRQEna = DISABLE;              //关闭SPI各中断
            SPI_Init(SPI, &SPI_InitStruct);               //SPI初始化程序
  @endcode
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author      <th>Description
 * <tr><td>2016年05月21日 <td>1.0        <td>cfwu          <td>创建
 * </table>
 */
void SPI_Init(SPI_TypeDef *SPIx, SPI_InitTypeDef *SPI_InitStruct)
{
    SYS_WR_PROTECT = 0x7a83; /* 使能系统寄存器写操作*/
    SYS_SFT_RST |= BIT0;     // 复位SPI
    SYS_SFT_RST &= ~BIT0;    // 释放SPI
    SYS_WR_PROTECT = 0x0;    /* 关闭系统寄存器写操作*/

    SYS_ModuleClockCmd(SYS_Module_SPI0, ENABLE);

    SPIx->IE = SPI_InitStruct->Trig << 3 | (SPI_InitStruct->IRQEna);

    SPIx->BAUD = SPI_InitStruct->BaudRate | (SPI_InitStruct->TRANS_MODE << 15);

    SPIx->SIZE = SPI_InitStruct->ByteLength;

    SPIx->CFG = SPI_InitStruct->EN | (SPI_InitStruct->ENDIAN << 1) | (SPI_InitStruct->CPOL << 2) | (SPI_InitStruct->CPHA << 3) | (SPI_InitStruct->Mode << 4) | (SPI_InitStruct->CS << 5) | (SPI_InitStruct->Duplex << 6);
}

/**
 *@brief @b 函数名称:    void SPI_StructInit(SPI_InitTypeDef* SPI_InitStruct)
 *@brief @b 功能描述:    SPI结构体初始化
 *@see被引用内容：       无
 *@param输入参数：       SPI_InitTypeDef *SPI_InitStruct
 *@param输出参数：       无
 *@return返 回 值：      无
 *@note其它说明：        无
 *@warning              无
 *@par 示例代码：
 *@code
            SPI_InitTypeDef SPI_InitStruct;
            SPI_StructInit(&SPI_InitStruct);              //SPI结构体初始化
  @endcode
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author      <th>Description
 * <tr><td>2016年05月21日 <td>1.0        <td>cfwu          <td>创建
 * </table>
 */
void SPI_StructInit(SPI_InitTypeDef *SPI_InitStruct)
{
    SPI_InitStruct->Duplex = SPI_Full;
    SPI_InitStruct->CS = 0;
    SPI_InitStruct->Mode = SPI_Slave;
    SPI_InitStruct->CPOL = 0;
    SPI_InitStruct->CPHA = 0;
    SPI_InitStruct->ENDIAN = DISABLE;
    SPI_InitStruct->EN = 0;

    SPI_InitStruct->IRQEna = DISABLE;
    SPI_InitStruct->Trig = 0;

    SPI_InitStruct->TRANS_MODE = 0;
    SPI_InitStruct->BaudRate = 3;

    SPI_InitStruct->ByteLength = 0;
}

/**
 *@brief @b 函数名称:   void SPI_SendData(SPI_TypeDef *SPIx, uint8_t n)
 *@brief @b 功能描述:   SPI发送数据
 *@see被引用内容：       无
 *@param输入参数：       SPIx：SPI , n：发送一字节数据
 *@param输出参数：       无
 *@return返 回 值：      无
 *@note其它说明：        无
 *@warning              无
 *@par 示例代码：
 *@code
            SPI_SendData(SPI,0x12);  //SPI发送0x12一字节数据
  @endcode
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author      <th>Description
 * <tr><td>2016年05月21日 <td>1.0        <td>cfwu          <td>创建
 * </table>
 */
void SPI_SendData(SPI_TypeDef *SPIx, uint8_t n)
{
    SPIx->TX_DATA = n;
}
/**
 *@brief @b 函数名称:   uint8_t SPI_ReadData(SPI_TypeDef *SPIx)
 *@brief @b 功能描述:   SPI读缓冲区数据
 *@see被引用内容：       无
 *@param输入参数：       SPIx：SPI
 *@param输出参数：       无
 *@return返 回 值：      无
 *@note其它说明：        无
 *@warning              无
 *@par 示例代码：
 *@code
            u8 SPI_RXValue = 0;
            SPI_RXValue = SPI_ReadData(SPI);  //SPI接收一字节数据
  @endcode
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author      <th>Description
 * <tr><td>2016年05月21日 <td>1.0        <td>cfwu          <td>创建
 * </table>
 */
uint8_t SPI_ReadData(SPI_TypeDef *SPIx)
{
    return SPIx->RX_DATA;
}

/**
 *@brief @b 函数名称:   uint8_t SPI_GetIRQFlag(SPI_TypeDef *SPIx,u8 IRQ_Flag)
 *@brief @b 功能描述:   获取SPI中断标志位
 *@see被引用内容：       无
 *@param输入参数：       SPIx：SPI
                        IRQ_Flag：
 * <table>              <tr><th>SPI_IF_TranDone       <td>传输完成中断标志位 \n
 * 						<tr><th>SPI_IF_SSErr          <td>传输异常中断标志位 \n
 * 						<tr><th>SPI_IF_DataOver       <td>传输溢出中断标志位 \n
 * </table>
 *@param输出参数：       无
 *@return返 回 值：      无
 *@note其它说明：        无
 *@warning              只有对应中断使能后，改为才能读取，如果对应中断未使能，读取结果一直为0
 *@par 示例代码：
 *@code
            if(SPI_GetIRQFlag(SPI,SPI_IF_TranDone))//获取传输完成中断标志位
            {
            }
  @endcode
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author      <th>Description
 * <tr><td>2022年04月20日 <td>1.0       <td>Zhu Jie       <td>创建
 * </table>
 */
uint8_t SPI_GetIRQFlag(SPI_TypeDef *SPIx, u8 IRQ_Flag)
{
    u8 SPI_IRQFlag = 0;
    if (SPIx->IE & IRQ_Flag)
    {
        SPI_IRQFlag = 1;
    }
    else
    {
        SPI_IRQFlag = 0;
    }
    return SPI_IRQFlag;
}

/**
 *@brief @b 函数名称:   void SPI_ClearIRQFlag(SPI_TypeDef *SPIx,u8 IRQ_Flag)
 *@brief @b 功能描述:   清除SPI中断标志位
 *@see被引用内容：       无
 *@param输入参数：       SPIx：SPI
                        IRQ_Flag：
 * <table>              <tr><th>SPI_IF_TranDone       <td>传输完成中断标志位 \n
 * 						<tr><th>SPI_IF_SSErr          <td>传输异常中断标志位 \n
 * 						<tr><th>SPI_IF_DataOver       <td>传输溢出中断标志位 \n
 * </table>
 *@param输出参数：       无
 *@return返 回 值：      无
 *@note其它说明：        无
 *@warning              无
 *@par 示例代码：
 *@code
            if(SPI_GetIRQFlag(SPI,SPI_IF_TranDone))//获取传输完成中断标志位
            {
                SPI_ClearIRQFlag(SPI,SPI_IF_TranDone);//清除传输完成中断标志位
            }
  @endcode
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author      <th>Description
 * <tr><td>2022年04月20日 <td>1.0      <td>Zhu Jie        <td>创建
 * </table>
 */
void SPI_ClearIRQFlag(SPI_TypeDef *SPIx, u8 IRQ_Flag)
{
    SPIx->IE |= IRQ_Flag;
}
