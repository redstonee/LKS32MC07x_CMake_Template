/**
 * @file
 * @copyright (C)2015, LINKO SEMICONDUCTOR Co.ltd
 * @brief 文件名称： lks32mc07x_wake.h\n
 * 文件标识： 无 \n
 * 内容摘要： wake驱动头文件 \n
 * 其它说明： 无 \n
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2023年02月23日 <td>1.0    <td>HuangMG    <td>创建
 * </table>
 */

#ifndef __lks32mc07x_WAKE__
#define __lks32mc07x_WAKE__
#include "lks32mc07x.h"

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

  /**
   *@brief 低功耗时钟配置中间变量
   */
  typedef struct
  {
    uint32_t AFE_REG5_RECORD;
    uint32_t CLK_CFG_RECORD;

  } WAKE_InitTypeDef;

  /**
   *@brief 低功耗IO唤醒电平枚举成员
   */
  typedef enum
  {
    WAKETRIG_LOW,  /**输入IO低电平唤醒*/
    WAKETRIG_HIGH, /**输入IO高电平唤醒*/
  } enumWakeTrigLevel;

/*休眠唤醒间隔时间*/
#define SYS_WakeInterval_025s 0x00 /**< 休眠唤醒间隔时间0.25s*/
#define SYS_WakeInterval_05s 0x01  /**< 休眠唤醒间隔时间0.5s*/
#define SYS_WakeInterval_1s 0x02   /**< 休眠唤醒间隔时间1s*/
#define SYS_WakeInterval_2s 0x03   /**< 休眠唤醒间隔时间2s*/
#define SYS_WakeInterval_4s 0x04   /**< 休眠唤醒间隔时间4s*/
#define SYS_WakeInterval_8s 0x05   /**< 休眠唤醒间隔时间8s*/
#define SYS_WakeInterval_16s 0x06  /**< 休眠唤醒间隔时间16s*/
#define SYS_WakeInterval_32s 0x07  /**< 休眠唤醒间隔时间32s*/

/*低功耗唤醒IO滤波*/
#define IOWK_FLT_EN 0x02 /**< 使能IO滤波*/
#define IOWK_FLT_DI 0x00 /**< 关闭IO滤波*/

/*低功耗唤醒IO选择*/
#define WAKEIO_P0_0 BIT0     /**< P0.0 作为唤醒IO*/
#define WAKEIO_P0_2 BIT1     /**< P0.2 作为唤醒IO*/
#define WAKEIO_P0_6 BIT2     /**< P0.6 作为唤醒IO*/
#define WAKEIO_P0_11 BIT3    /**< P0.11作为唤醒IO*/
#define WAKEIO_P0_14 BIT4    /**< P0.14作为唤醒IO*/
#define WAKEIO_P2_4 BIT5     /**< P2.4 作为唤醒IO*/
#define WAKEIO_P2_7 BIT6     /**< P2.7 作为唤醒IO*/
#define WAKEIO_P2_15 BIT7    /**< P2.15 作为唤醒IO*/
#define WAKEIO_CLUOUT0 BIT8  /**< CLUOUT0 作为唤醒使能*/
#define WAKEIO_CLUOUT1 BIT9  /**< CLUOUT1 作为唤醒使能*/
#define WAKEIO_CLUOUT2 BIT10 /**< CLUOUT2 作为唤醒使能*/
#define WAKEIO_CLUOUT3 BIT11 /**< CLUOUT3 作为唤醒使能*/

  /*休眠、唤醒*/
  void SYS_EVTCLRSleep(void);
  void SYS_FallSleep(void);
  void SYS_SetWakeInterval(uint32_t rth, uint32_t wth, uint8_t ena);
  void Switch2PLL(void);
  void Switch2HRC(void);
  void SetWakeIO(uint32_t wakeIO, enumWakeTrigLevel trigLevel, uint32_t flt, uint8_t ena);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif
