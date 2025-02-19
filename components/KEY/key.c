/*
*********************************************************************************************************
*
*	模块名称 : xxx模块
*	文件名称 : key.c 
*	版    本 : V1.
*   日    期 : 2024-12-13 
*	说    明 : 
*	修改记录 :
*		版本号  日期        作者     说明
*		V1.0    
*		V1.1    
*	Copyright (C), 2015-2030, 河南华软智能科技有限公司
*
*********************************************************************************************************
*/
/*include----------------------------------------------------------------------*/
#include "main.h"
/*define-----------------------------------------------------------------------*/
static char *TAG ="KEY";
/*variate----------------------------------------------------------------------*/
static void button_up_event_cb(void *arg, void *data)
{
     ESP_LOGI(TAG, "KEY_UP down");
}

static void button_down_event_cb(void *arg, void *data)
{
     ESP_LOGI(TAG, "KEY_down down");
}
static void button_push_event_cb(void *arg, void *data)
{
     ESP_LOGI(TAG, "KEY_push down");
}

void Button1_init(uint32_t button_num, uint8_t BUTTON_ACTIVE_LEVEL)
{
	esp_err_t err;
    button_config_t btn_cfg = {
        .type = BUTTON_TYPE_GPIO,
        .gpio_button_config = {
            .gpio_num = button_num,
            .active_level = BUTTON_ACTIVE_LEVEL,
        },
    };
    button_handle_t btn = iot_button_create(&btn_cfg);
    assert(btn);
	err = iot_button_register_cb(btn, BUTTON_PRESS_DOWN, button_up_event_cb, NULL);   
    ESP_ERROR_CHECK(err);
}
void Button2_init(uint32_t button_num, uint8_t BUTTON_ACTIVE_LEVEL)
{
	esp_err_t err;
    button_config_t btn_cfg = {
        .type = BUTTON_TYPE_GPIO,
        .gpio_button_config = {
            .gpio_num = button_num,
            .active_level = BUTTON_ACTIVE_LEVEL,
        },
    };
    button_handle_t btn = iot_button_create(&btn_cfg);
    assert(btn);       
	err = iot_button_register_cb(btn, BUTTON_PRESS_DOWN, button_down_event_cb, NULL);   
    ESP_ERROR_CHECK(err);
}
void Button3_init(uint32_t button_num, uint8_t BUTTON_ACTIVE_LEVEL)
{
	esp_err_t err;
    button_config_t btn_cfg = {
        .type = BUTTON_TYPE_GPIO,
        .gpio_button_config = {
            .gpio_num = button_num,
            .active_level = BUTTON_ACTIVE_LEVEL,
        },
    };
    button_handle_t btn = iot_button_create(&btn_cfg);
    assert(btn);
	err = iot_button_register_cb(btn, BUTTON_PRESS_DOWN, button_push_event_cb, NULL);    
    ESP_ERROR_CHECK(err);
}

void Btn_init(void)
{
	Button1_init(UP_BUTTON_NUM ,ACTIVE_LEVEL_HIGH);
	Button2_init(DOWN_BUTTON_NUM ,ACTIVE_LEVEL_HIGH);
	Button3_init(PUSH_BUTTON_NUM ,ACTIVE_LEVEL_LOW);
}

void Key_task(void *arg)
{
	Btn_init();
	while (1)
	{
		vTaskDelay(10 / portTICK_PERIOD_MS);
	}
	
}
/*Function prototype End*******************************************************/










