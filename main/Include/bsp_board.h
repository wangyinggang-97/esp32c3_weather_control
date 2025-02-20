#ifndef  bsp_board_h
#define  bsp_board_h

#include "main.h"


//key

#define UP_BUTTON_NUM           5
#define DOWN_BUTTON_NUM         4
#define PUSH_BUTTON_NUM         6
#define ACTIVE_LEVEL_LOW        0
#define ACTIVE_LEVEL_HIGH       1
#define KEY_TASK_STACK_SIZE   (4 * 1024)
#define KEY_TASK_PRIORITY     23

//led
#define LED_STRIP_GPIO 8  // 定义 LED 灯带连接的 GPIO 引脚
#define LED_STRIP_LED_NUM 32  // 定义 LED 灯带上的 LED 数量
#define LED_STRIP_RMT_RES_HZ  (10 * 1000 * 1000)
#define LED_STRIP_TASK_STACK_SIZE   (4 * 1024)
#define LED_STRIP_TASK_PRIORITY     22


#define EXAMPLE_LED_NUMBERS         1
#define EXAMPLE_CHASE_SPEED_MS      10

//lcd_touch
#define BLK_GPIO_PIN 10
#define LCD_HOST  SPI2_HOST

#define EXAMPLE_LCD_H_RES              128
#define EXAMPLE_LCD_V_RES              160

#define LCD_TASK_STACK_SIZE   (4 * 1024)
#define LCD_TASK_PRIORITY     21

/* blk端口定义 */
#define BLK(x)          do { x ?                                      \
                             gpio_set_level(BLK_GPIO_PIN, 1) :  \
                             gpio_set_level(BLK_GPIO_PIN, 0); \
                        } while(0)  /* LED翻转 */

#define EXAMPLE_LCD_CMD_BITS           8
#define EXAMPLE_LCD_PARAM_BITS         8

#define EXAMPLE_LCD_PIXEL_CLOCK_HZ     (10 * 1000 * 1000)
#define EXAMPLE_LCD_BK_LIGHT_ON_LEVEL  1
#define EXAMPLE_LCD_BK_LIGHT_OFF_LEVEL !EXAMPLE_LCD_BK_LIGHT_ON_LEVEL
#define EXAMPLE_PIN_NUM_SCLK           0
#define EXAMPLE_PIN_NUM_MOSI           1
#define EXAMPLE_PIN_NUM_MISO           -1
#define EXAMPLE_PIN_NUM_LCD_DC         2
#define EXAMPLE_PIN_NUM_LCD_RST        7
#define EXAMPLE_PIN_NUM_LCD_CS         3
#define EXAMPLE_PIN_NUM_BK_LIGHT       10
#define EXAMPLE_PIN_NUM_TOUCH_CS       4

#define EXAMPLE_LVGL_TICK_PERIOD_MS    2
#define EXAMPLE_LVGL_TASK_MAX_DELAY_MS 500
#define EXAMPLE_LVGL_TASK_MIN_DELAY_MS 1
#define EXAMPLE_LVGL_TASK_STACK_SIZE   (4 * 1024)
#define EXAMPLE_LVGL_TASK_PRIORITY     2

//touch



#endif