#ifndef main_h
#define main_h



#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "esp_log.h"
#include "esp_err.h"
#include "esp_check.h"
#include "driver/gpio.h"
#include "driver/i2c.h"
#include "driver/i2c_master.h"
#include "driver/spi_master.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "esp_timer.h"
#include "driver/uart.h"
#include "driver/rmt_encoder.h"


// #include "esp_lcd_panel_io.h"
// #include "esp_lcd_panel_vendor.h"
// #include "esp_lcd_panel_ops.h"
// #include "esp_lcd_st7735.h"
// #include "lvgl.h"
#include "iot_button.h"


#include "MyUART.h"
#include "muti_button.h"
#include "timer.h"

#include "led.h"
#include "led_driver.h"
#include "key.h"
#include "lcd.h"
#include "ST7735.h"

#include "bsp_board.h"

#endif