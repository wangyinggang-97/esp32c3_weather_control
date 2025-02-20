
#ifndef lcd_h
#define lcd_h

#include "esp_lcd_panel_io.h"
#include "esp_lcd_panel_vendor.h"
#include "esp_lcd_panel_ops.h"
#include "esp_lcd_st7735.h"
#include <esp_lcd_types.h>
#include <esp_lcd_panel_interface.h>

void st7735_lcd_init(void);
void lcd_task(void *arg);
#endif