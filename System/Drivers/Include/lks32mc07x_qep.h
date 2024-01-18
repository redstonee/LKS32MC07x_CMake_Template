/**
 * @file
 * @copyright (C)2015, LINKO SEMICONDUCTOR Co.ltd
 * @brief 文件名称： lks32mc07x_qep.h\n
 * 文件标识： 无 \n
 * 内容摘要： QEP驱动头文件 \n
 * 其它说明： 无 \n
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2023年02月23日 <td>1.0    <td>HuangMG     <td>创建
 * </table>
 */

#ifndef __lks32mc07x_QEP_H
#define __lks32mc07x_QEP_H

/* Includes ------------------------------------------------------------------*/
#include "lks32mc07x.h"

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

    /**
     *@brief 编码器寄存器结构体句柄
     */
    typedef struct
    {
        __IO uint32_t CFG; /**<编码器配置寄存器*/
        __IO uint32_t TH;  /**<编码器计数门限寄存器*/
        __IO uint32_t CNT; /**<编码器计数值寄存器*/
        __IO uint32_t IE;  /**<编码器中断使能*/
        __IO uint32_t IF;  /**<编码器中断标志位*/
    } TIM_QEPTypeDef;

    /**
     * QEP0结构体基地址定义
     */
#define QEP0 ((TIM_QEPTypeDef *)QEP0_BASE)
    /**
     * QEP1结构体基地址定义
     */

#define QEP1 ((TIM_QEPTypeDef *)QEP1_BASE)

    typedef struct
    {
        /**
         * @brief 编码器模式选择 \n
         * @see QEP_Mode_T1 \n
         * @see QEP_Mode_T1_T2 \n
         * @see QEP_Mode_CCWSIGN_UpDown \n
         * @see QEP_Mode_CCWCW_UpDown
         */
        uint32_t QEP_Mode;      // 编码器模式选择
        uint32_t QEP_FE_CNT_EN; // 使能下降沿计算（上升沿始终计数），ENABLE使能 DISABLE失能
        uint32_t QEP_ZNC;       // Z信号清零极性选择：低电平/下降沿清零使能，ENABLE使能 DISABLE失能
        uint32_t QEP_ZPC;       // Z信号清零极性选择：高电平/上升沿清零使能 ，ENABLE使能 DISABLE失能
        uint32_t QEP_ZLC;       // Z信号电平清零QEP计数器使能，ENABLE使能 DISABLE失能
        uint32_t QEP_ZEC;       // Z信号边沿清零QEP计数器使能，ENABLE使能 DISABLE失能
        uint16_t QEP_TH;        // QEP计数门限寄存器
        /**
         * @brief 编码器对应时钟分频系数 \n
         * @see ECD_Clk_Div1  \n
         * @see ECD_Clk_Div2  \n
         * @see ECD_Clk_Div4  \n
         * @see ECD_Clk_Div8  \n
         * @see ECD_Clk_Div16 \n
         * @see ECD_Clk_Div32 \n
         * @see ECD_Clk_Div64 \n
         * @see ECD_Clk_Div128
         */
        uint32_t QEP_ClockDiv; // 时钟分频
        uint32_t QEP_Filter;   // 信号输入滤波
        /**
         * @brief 编码器中断使能 \n
         * @see QEP_IRQEna_None \n
         * @see QEP_IRQEna_UnderFlow \n
         * @see QEP_IRQEna_OverFlow
         */
        uint32_t QEP_IRQEna; // 中断使能
    } TIM_QEPInitTypeDef;

#define QEP_CLK_DIV1 0x00   /**<QEP计数器频率1分频*/
#define QEP_CLK_DIV2 0x01   /**<QEP计数器频率2分频*/
#define QEP_CLK_DIV4 0x02   /**<QEP计数器频率4分频*/
#define QEP_CLK_DIV8 0x03   /**<QEP计数器频率8分频*/
#define QEP_CLK_DIV16 0x04  /**<QEP计数器频率16分频*/
#define QEP_CLK_DIV32 0x05  /**<QEP计数器频率32分频*/
#define QEP_CLK_DIV64 0x06  /**<QEP计数器频率64分频*/
#define QEP_CLK_DIV128 0x07 /**<QEP计数器频率128分频*/

    /**
     * @brief 编码器中断使能配置定义
     */
#define QEP_IRQEna_None 0         /**<无使能*/
                                  /**
                                   * @brief 编码器中断使能配置定义
                                   */
#define QEP_IRQEna_UnderFlow BIT0 /**<使能下溢中断*/
                                  /**
                                   * @brief 编码器中断使能配置定义
                                   */
#define QEP_IRQEna_OverFlow BIT1  /**<使能上溢中断*/

    /**
     * @brief 编码器中断标志定义
     */
#define QEP_IF_UNDERFLOW BIT0 /**<Encoder下溢中断*/
                              /**
                               * @brief 编码器中断标志定义
                               */
#define QEP_IF_OVERFLOW BIT1  /**<Encoder上溢中断*/

#define QEP_Mode_T1 ((uint32_t)0x00)             /*counting on T1*/
#define QEP_Mode_T1_T2 ((uint32_t)0x01)          /*counting on T1&T2*/
#define QEP_Mode_CCWSIGN_UpDown ((uint32_t)0x02) /*CCW+SIGN 符号加脉冲信号计数模式, 若需要计数信号的上下沿，则QEP_FE_CNT_EN置1*/
#define QEP_Mode_CCWCW_UpDown ((uint32_t)0x03)   /*CCW+CW   符号加脉冲信号计数模式, 若需要计数信号的上下沿，则QEP_FE_CNT_EN置1*/

    /*QEP初始化*/
    void TIM_QEPInit(TIM_QEPTypeDef *QEPx, TIM_QEPInitTypeDef *TIM_QEPInitStruct);
    void TIM_QEPStructInit(TIM_QEPInitTypeDef *TIM_QEPInitStruct);
    void TIM_QEPCmd(TIM_QEPTypeDef *QEPx, FuncState state);
    uint16_t TIM_QEP_GetCount(TIM_QEPTypeDef *QEPx);
    void QEP_ClearIRQFlag(TIM_QEPTypeDef *QEPx, uint32_t tempFlag);
    u16 QEP_GetIRQFlag(TIM_QEPTypeDef *QEPx, u32 QEP_IF_x);
    u16 QEP_GetFlag(TIM_QEPTypeDef *QEPx, u32 QEP_IF_x);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif
