/**
 * @file
 * @copyright (C)2021, LINKO SEMICONDUCTOR Co.ltd
 * @brief 文件名称： lks32mc07x_uart.c\n
 * 文件标识： 无 \n
 * 内容摘要： UART外设驱动程序 \n
 * 其它说明： 无 \n
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2023年2月23日 <td>1.0     <td>cakezhang      <td>创建
 * </table>
 */
#include "lks32mc07x_lib.h"

static void UART_SetBaud(uint32_t Uart0Baud, uint32_t Uart1Baud);
static uint32_t UART_ReadBaud(UART_TypeDef *UARTx);
#ifndef MCU_MCLK
#define MCU_MCLK 96000000
#endif
/**
 *@brief @b 函数名称:   void UART_Init(UART_TypeDef* UARTx, EUART_InitTypeDef* UART_InitStruct)
 *@brief @b 功能描述:   UART初始化函数
 *@see被引用内容：      SYS_ModuleClockCmd()
 *@param输入参数：      UART_TypeDef：UARTx , UART_InitTypeDef
 *@param输出参数：      无
 *@return返 回 值：     无
 *@note其它说明：       串口波特率计算使用UART_MCU_MCLK系统时钟进行计算，使用前需要确认系统时钟频率
 *@warning             无
 *@par 示例代码：
 *@code
         UART_InitTypeDef UART_InitStruct;
         UART_StructInit(&UART_InitStruct);
         UART_InitStruct.BaudRate  = 9600;                // 设置波特率9600
         UART_InitStruct.WordLength= UART_WORDLENGTH_8b;  // 发送数据长度8位
         UART_InitStruct.StopBits  = UART_STOPBITS_1b;    // 停止位长度1位
         UART_InitStruct.FirstSend = UART_FIRSTSEND_LSB;  // 先发送LSB
         UART_InitStruct.ParityMode= UART_Parity_NO;      // 无奇偶校验
         UART_InitStruct.RXD_INV   = DISABLE;             // RXD电平正常输出
         UART_InitStruct.TXD_INV   = DISABLE;             // TXD电平正常输出
         UART_InitStruct.IRQEna    = UART_IRQEna_SendOver | UART_IRQEna_RcvOver;
         UART_Init(UART0, &UART_InitStruct);

  @endcode
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2023年2月23日 <td>1.0     <td>cakezhang      <td>创建
 * </table>
 */
void UART_Init(UART_TypeDef *UARTx, UART_InitTypeDef *UART_InitStruct)
{
    // uint32_t clkDivUART;
    // uint32_t divCoefficient;
    uint32_t parity;
    uint32_t parityEna;

    if (UARTx == UART0)
    {
        SYS_ModuleClockCmd(SYS_Module_UART0, ENABLE);
        UART_SetBaud(UART_InitStruct->BaudRate, UART_ReadBaud(UART1));
    }
    else if (UARTx == UART1)
    {
        SYS_ModuleClockCmd(SYS_Module_UART1, ENABLE);
        UART_SetBaud(UART_ReadBaud(UART0), UART_InitStruct->BaudRate);
    }

    if (UART_InitStruct->ParityMode == UART_Parity_EVEN)
    {
        parityEna = ENABLE;
        parity = 0;
    }
    else if (UART_InitStruct->ParityMode == UART_Parity_ODD)
    {
        parityEna = ENABLE;
        parity = 1;
    }
    else
    {
        parityEna = DISABLE;
        parity = 0;
    }
    UARTx->CTRL = UART_InitStruct->WordLength | (UART_InitStruct->StopBits << 1) | (UART_InitStruct->FirstSend << 2) | (parity << 3) | (parityEna << 4) | (UART_InitStruct->MultiDropEna << 5) | (UART_InitStruct->Bit9Value << 6) | (UART_InitStruct->IOFlipEna << 7);

    UARTx->IOC = (UART_InitStruct->TXD_INV << 1) | UART_InitStruct->RXD_INV;

    UARTx->ADR = UART_InitStruct->Match485Addr;
    UARTx->RE = UART_InitStruct->DMARE;
    UARTx->IE = UART_InitStruct->IRQEna;
}

/**
 *@brief @b 函数名称:   void UART_StructInit(UART_InitTypeDef* UART_InitStruct)
 *@brief @b 功能描述:   UART结构体初始化函数
 *@see被引用内容：   无
 *@param输入参数：   UART_InitTypeDef
 *@param输出参数：  无
 *@return返 回 值： 无
 *@note其它说明：   无
 *@warning         无
 *@par 示例代码：
 *@code
           UART_InitTypeDef UART_InitStruct;
           UART_StructInit(&UART_InitStruct);  //初始化UART相关配置结构体变量
  @endcode
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2023年2月23日 <td>1.0     <td>cakezhang      <td>创建
 * </table>
 */
void UART_StructInit(UART_InitTypeDef *UART_InitStruct)
{
    UART_InitStruct->BaudRate = 9600;
    UART_InitStruct->WordLength = UART_WORDLENGTH_8b;
    UART_InitStruct->StopBits = UART_STOPBITS_1b;
    UART_InitStruct->FirstSend = UART_FIRSTSEND_LSB;
    UART_InitStruct->ParityMode = UART_Parity_NO;

    UART_InitStruct->MultiDropEna = DISABLE;
    UART_InitStruct->Bit9Value = 0;
    UART_InitStruct->IOFlipEna = DISABLE;

    UART_InitStruct->Match485Addr = 0;
    UART_InitStruct->IRQEna = 0;
    UART_InitStruct->RXD_INV = DISABLE;
    UART_InitStruct->TXD_INV = DISABLE;
}

/**
 *@brief @b 函数名称:   void UART_SENDDATA(UART_TypeDef *UARTx, uint32_t n)
 *@brief @b 功能描述:   UART发送数据
 *@see被引用内容：   UARTx
 *@param输入参数：   UART_TypeDef：UARTx， n：要发生1Byte数据
 *@param输出参数：   无
 *@return返 回 值：  无
 *@note其它说明：    无
 *@warning          无
 *@par 示例代码：
 *@code
           UART_SendData(UART0，0x12);//串口0发送0x12一字节数据
  @endcode
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2023年2月23日 <td>1.0     <td>cakezhang      <td>创建
 * </table>
 */
void UART_SendData(UART_TypeDef *UARTx, uint32_t n)
{
    UARTx->BUFF = n;
}

/**
 *@brief @b 函数名称:   uint32_t UART_ReadData(UART_TypeDef *UARTx)
 *@brief @b 功能描述:   UART读缓冲区数据
 *@see被引用内容：   UART0
 *@param输入参数：   UART_TypeDef：UART0
 *@param输出参数：   无
 *@return返 回 值：  返回串口接收缓冲区的1Byte数据
 *@note其它说明：    无
 *@warning          无
 *@par 示例代码：
 *@code
           u8 UART_BUFF = 0;
           UART_BUFF = UART_ReadData(UART0);//读取串口0接收一字节数据
  @endcode
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2023年2月23日 <td>1.0     <td>cakezhang      <td>创建
 * </table>
 */
uint32_t UART_ReadData(UART_TypeDef *UARTx)
{
    return UARTx->BUFF;
}

/**
 *@brief @b 函数名称:   uint32_t UART_GetIRQFlag(UART_TypeDef *UARTx , uint32_t tempFlag)
 *@brief @b 功能描述:   获取UART中断标志
 *@see被引用内容：   UARTx
 *@param输入参数：   UART_TypeDef：UARTx \n
                    tempFlag参数可选：
 *<table>           <tr><td> 宏定义               <td>说明
                    <tr><th>UART_IF_SendOver     <td>发送完成中断
                    <tr><th>UART_IF_RcvOver      <td>接收完成中断
                    <tr><th>UART_IF_SendBufEmpty <td>发送缓冲区空中断
                    <tr><th>UART_IF_StopError    <td>停止位错误
                    <tr><th>UART_IF_CheckError   <td>校验错误
                    <tr><th>UART_IF_TX_OV        <td>发送缓冲区溢出中断
                    <tr><th>UART_IF_RX_OV        <td>接收缓冲区溢出中断
                    <tr><th>UART_IF_LBD          <td>LIN break character 检测中断
                    <tr><th>UART_IF_IDLE         <td>空闲帧中断
 *</table>
 *@param输出参数：   无
 *@return返 回 值：  无
 *@note其它说明：    无
 *@warning          只有对应中断使能后，改为才能读取，如果对应中断未使能，读取结果一直为0
 *@par 示例代码：
 *@code
           if(UART_GetIRQFlag(UART0,UART_IF_SendOver))//获取发送完成中断标志位
           {
             UART_ClearIRQFlag(UART0,UART_IF_SendOver)//清除发送完成中断标志位
           }
  @endcode
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2023年2月23日 <td>1.0     <td>cakezhang      <td>创建
 * </table>
 */
uint32_t UART_GetIRQFlag(UART_TypeDef *UARTx, uint32_t tempFlag)
{
    if ((UARTx->IF) & tempFlag & (UARTx->IE))
    {
        return 1;
    }
    return 0;
}
/**
 *@brief @b 函数名称:   void UART_ClearIRQFlag(UART_TypeDef *UARTx, uint32_t nFlag)
 *@brief @b 功能描述:   清除UART中断标志
 *@see被引用内容：   UART0
 *@param输入参数：   UART_TypeDef：UART0 \n
                    tempFlag参数可选：
 *<table>           <tr><td> 宏定义               <td>说明
                    <tr><th>UART_IF_SendOver     <td>发送完成中断
                    <tr><th>UART_IF_RcvOver      <td>接收完成中断
                    <tr><th>UART_IF_SendBufEmpty <td>发送缓冲区空中断
                    <tr><th>UART_IF_StopError    <td>停止位错误
                    <tr><th>UART_IF_CheckError   <td>校验错误
                    <tr><th>UART_IF_TX_OV        <td>发送缓冲区溢出中断
                    <tr><th>UART_IF_RX_OV        <td>接收缓冲区溢出中断
                    <tr><th>UART_IF_LBD          <td>LIN break character 检测中断
                    <tr><th>UART_IF_IDLE         <td>空闲帧中断
 *</table>
 *@param输出参数：   无
 *@return返 回 值：  无
 *@note其它说明：    无
 *@warning          无
 *@par 示例代码：
 *@code
           if(UART_GetIRQFlag(UART0,UART_IF_SendOver))//获取发送完成中断标志位
           {
              UART_ClearIRQFlag(UART0,UART_IF_SendOver)//清除发送完成中断标志位
           }
  @endcode
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2023年2月23日 <td>1.0     <td>cakezhang      <td>创建
 * </table>
 */
void UART_ClearIRQFlag(UART_TypeDef *UARTx, uint32_t tempFlag)
{
    UARTx->IF = tempFlag;
}

/**
 *@brief @b 函数名称:   uint8_t UART_SendAddr_485(UART_TypeDef *UARTx, uint8_t n)
 *@brief @b 功能描述:   发送485通讯中需要接收数据的从机地址
 *@see被引用内容：   UARTx
 *@param输入参数：   UART_TypeDef：UARTx， n：要发生1Byte地址
 *@param输出参数：   无
 *@return返 回 值：  1：发送失败，0：发送成功
 *@note其它说明：    cnt作用是延时防止程序卡死。在发送数据后立即发送地址的情况下,会
                    判断等待发送缓冲区空在进行地址发送，如果长时间还未发送完成（cnt计数时间），
                    则跳出while循环。如果串口波特率较低cnt计数已满，会出现数据还未发送完成进行
                    下一个数据发送，为了避免此类问题发送可以增加cnt值。
 *@warning         无
 *@par 示例代码：
 *@code
           UART_SendAddr_485(UART0,0x55);//串口0发送485从机接收地址为0x55
  @endcode
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2021年10月14日 <td>1.0     <td>HuangMG      <td>创建
 * </table>
 */
uint8_t UART_SendAddr_485(UART_TypeDef *UARTx, uint8_t n)
{
    uint32_t m = 0x100;
    uint32_t cnt = 0xffffff;
    m |= n;
    UARTx->BUFF = m;
    while (!(UARTx->STT & BIT0)) /*发送缓冲区非空*/
    {
        if (cnt > 0)
        {
            cnt--;
            __NOP();
        }
        else
        {
            return 1; /*发送失败*/
        }
    }
    return 0; /*发送成功*/
}

/**
 *@brief @b 函数名称:   uint8_t UART_SendData_485(UART_TypeDef *UARTx, uint8_t n)
 *@brief @b 功能描述:   发送485通讯中的数据信息
 *@see被引用内容：   UARTx
 *@param输入参数：   UART_TypeDef：UARTx， n：要发生1Byte数据
 *@param输出参数：   无
 *@return返 回 值：  1：发送失败，0：发送成功
 *@note其它说明：    cnt作用是延时防止程序卡死。在发送数据后立即发送地址的情况下,会
                    判断等待发送缓冲区空在进行地址发送，如果长时间还未发送完成（cnt计数时间），
                    则跳出while循环。如果串口波特率较低cnt计数已满，会出现数据还未发送完成进行
                    下一个数据发送，为了避免此类问题发送可以增加cnt值。
 *@warning          无
 *@par 示例代码：
 *@code
           UART_SendData_485(UART0,0x12);//串口0发送485数据为0x12
  @endcode
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2021年10月14日 <td>1.0     <td>HuangMG      <td>创建
 * </table>
 */
uint8_t UART_SendData_485(UART_TypeDef *UARTx, uint8_t n)
{
    uint32_t cnt = 0xffffff;
    UARTx->BUFF = n;
    while (!(UARTx->STT & BIT0)) /*发送缓冲区非空*/
    {
        if (cnt > 0)
        {
            cnt--;
            __NOP();
        }
        else
        {
            return 1; /*发送失败*/
        }
    }
    return 0; /*发送成功*/
}
static void UART_SetBaud(uint32_t Uart0Baud, uint32_t Uart1Baud)
{
    uint32_t d0 = SYS_ReadMcuClk() / Uart0Baud;
    uint32_t d1 = SYS_ReadMcuClk() / Uart1Baud;
    uint32_t max = d0 > d1 ? d0 : d1;
    uint32_t d2;
    d2 = max >> 16;
    d2 += 1;
    d0 /= d2;
    d1 /= d2;
    d0 -= 1;
    d1 -= 1;
    UART0->DIVL = d0 & 0xFF;
    UART0->DIVH = (d0 & 0xFF00) >> 8;
    UART1->DIVL = d1 & 0xFF;
    UART1->DIVH = (d1 & 0xFF00) >> 8;
    SYS->WR_PROTECT = 0x7A83;
    SYS_CLK_DIV2 = d2 - 1;
    SYS->WR_PROTECT = 0x0;
}
static uint32_t UART_ReadBaud(UART_TypeDef *UARTx)
{
    uint32_t baud;
    baud = SYS_ReadMcuClk() / SYS_CLK_DIV2 / (1 + 256 * UARTx->DIVH + UARTx->DIVL);
    return baud;
}
/************************ (C) COPYRIGHT LINKO SEMICONDUCTOR *****END OF FILE****/
