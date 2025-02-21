idf_component_register(SRCS "st7735.c" "lcd.c"
                       INCLUDE_DIRS "include"
                       REQUIRES main driver esp_lcd esp_lcd_st7735 lvgl__lvgl timer
                       )
