idf_component_register(SRCS "." "led.c" "led_driver.c"
                       INCLUDE_DIRS "include"
					   REQUIRES main driver  esp_driver_rmt  led_strip
					   )