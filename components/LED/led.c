#include "main.h"

static led_strip_t *strip;
static const char *TAG = "led";

void breathing_effect(uint8_t r, uint8_t g, uint8_t b, uint16_t delay_ms)
{
    for (int i = 0; i < 255; i++) {
        for (int j = 0; j < LED_STRIP_LED_NUM; j++) {
            strip->set_pixel(strip, j, r * i / 255, g * i / 255, b * i / 255);
        }
        strip->refresh(strip);
        vTaskDelay(delay_ms / portTICK_PERIOD_MS);
    }

    for (int i = 255; i >= 0; i--) {
        for (int j = 0; j < LED_STRIP_LED_NUM; j++) {
            strip->set_pixel(strip, j, r * i / 255, g * i / 255, b * i / 255);
        }
        strip->refresh(strip);
        vTaskDelay(delay_ms / portTICK_PERIOD_MS);
    }
}

void flowing_effect(uint8_t r, uint8_t g, uint8_t b, uint16_t delay_ms)
{
    for (int i = 0; i < LED_STRIP_LED_NUM; i++) {
        strip->set_pixel(strip, i, r, g, b);
        strip->refresh(strip);
        vTaskDelay(delay_ms / portTICK_PERIOD_MS);
        strip->set_pixel(strip, i, 0, 0, 0);
    }
}
void led_task(void *arg)
{
	// LED strip general initialization, according to your led board design
    led_strip_config_t strip_config = {
        .strip_gpio_num = LED_STRIP_GPIO, // The GPIO that connected to the LED strip's data line
        .max_leds = LED_STRIP_LED_NUM,      // The number of LEDs in the strip,
        .led_model = LED_MODEL_WS2812,        // LED strip model
        .color_component_format = LED_STRIP_COLOR_COMPONENT_FMT_GRB, // The color order of the strip: GRB
        .flags = {
            .invert_out = false, // don't invert the output signal
        }
    };

    // LED strip backend configuration: RMT
    led_strip_rmt_config_t rmt_config = {
        .clk_src = RMT_CLK_SRC_DEFAULT,        // different clock source can lead to different power consumption
        .resolution_hz = LED_STRIP_RMT_RES_HZ, // RMT counter clock frequency
        .mem_block_symbols = 64,               // the memory size of each RMT channel, in words (4 bytes)
        .flags = {
            .with_dma = false, // DMA feature is available on chips like ESP32-S3/P4
        }
    };
    ESP_ERROR_CHECK(led_strip_new_rmt_device(&strip_config, &rmt_config, &strip));
    ESP_LOGI(TAG, "Created LED strip object with RMT backend");
    while (1) {
        // 呼吸灯效果
        breathing_effect(255, 0, 0, 5);  // 红色呼吸灯
        breathing_effect(0, 255, 0, 5);  // 绿色呼吸灯
        breathing_effect(0, 0, 255, 5);  // 蓝色呼吸灯

		// 流水灯效果
        flowing_effect(255, 0, 0, 100);  // 红色流水灯
        flowing_effect(0, 255, 0, 100);  // 绿色流水灯
        flowing_effect(0, 0, 255, 100);  // 蓝色流水灯
    }
}

