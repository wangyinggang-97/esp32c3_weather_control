#include "main.h"

void app_main(void)
{
	esptimer_init();
	//xTaskCreate(led_task2,"led",LED_STRIP_TASK_STACK_SIZE,NULL,LED_STRIP_TASK_PRIORITY,NULL);
    xTaskCreate(Key_task,"key",KEY_TASK_STACK_SIZE,NULL,KEY_TASK_PRIORITY,NULL);
    xTaskCreate(lcd_task,"lcd",LCD_TASK_STACK_SIZE,NULL,LCD_TASK_PRIORITY,NULL);
    while (1) {
		 vTaskDelay(10);
    }

}
