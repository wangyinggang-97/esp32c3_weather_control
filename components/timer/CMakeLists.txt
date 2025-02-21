idf_component_register(SRCS  "timer.c"
                       INCLUDE_DIRS "include"
					   REQUIRES main  esp_timer lvgl__lvgl
					   )