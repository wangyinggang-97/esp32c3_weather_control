#include "lcd.h"
#include "main.h"

static const char* TAG = "SPI_LCD" ;



void BLK_init(void)
{
	gpio_config_t gpio_init_struct = {0};

    gpio_init_struct.intr_type = GPIO_INTR_DISABLE;         /* 失能引脚中断 */
    gpio_init_struct.mode = GPIO_MODE_INPUT_OUTPUT;         /* 输入输出模式 */
    gpio_init_struct.pull_up_en = GPIO_PULLUP_DISABLE;       /* 使能上拉 */
    gpio_init_struct.pull_down_en = GPIO_PULLDOWN_DISABLE;  /* 失能下拉 */
    gpio_init_struct.pin_bit_mask = 1ull << BLK_GPIO_PIN;   /* 设置的引脚的位掩码 */
    ESP_ERROR_CHECK(gpio_config(&gpio_init_struct));                         /* 配置GPIO */

	ESP_LOGI(TAG,"BLK GPIO init ok");
}
void st7735_lcd_init(void)
{
	ESP_LOGI(TAG, "Initialize SPI bus");
	spi_bus_config_t buscfg ={
        .miso_io_num = -1,  // ST7735 不需要 MISO
        .mosi_io_num = EXAMPLE_PIN_NUM_MOSI,
        .sclk_io_num = EXAMPLE_PIN_NUM_SCLK,
        .quadwp_io_num = -1,
        .quadhd_io_num = -1,
        .max_transfer_sz = EXAMPLE_LCD_H_RES*EXAMPLE_LCD_V_RES*sizeof(uint16_t),  // RGB565 格式
    };
    ESP_ERROR_CHECK(spi_bus_initialize(LCD_HOST, &buscfg, SPI_DMA_CH_AUTO));

	ESP_LOGI(TAG, "Install panel IO");
	esp_lcd_panel_io_handle_t io_handle = NULL;
	esp_lcd_panel_io_spi_config_t io_config = {
		.dc_gpio_num = EXAMPLE_PIN_NUM_LCD_DC,
		.cs_gpio_num = EXAMPLE_PIN_NUM_LCD_CS,
		.pclk_hz = EXAMPLE_LCD_PIXEL_CLOCK_HZ,
		.lcd_cmd_bits = EXAMPLE_LCD_CMD_BITS,
		.lcd_param_bits = EXAMPLE_LCD_PARAM_BITS,
		.spi_mode = 0,
		.trans_queue_depth = 10,
	};
    // Attach the LCD to the SPI bus
	ESP_ERROR_CHECK(esp_lcd_new_panel_io_spi((esp_lcd_spi_bus_handle_t)LCD_HOST, &io_config, &io_handle));

    esp_lcd_panel_handle_t panel_handle = NULL;
    esp_lcd_panel_dev_config_t panel_config = {
        .reset_gpio_num = EXAMPLE_PIN_NUM_LCD_RST,
        .rgb_ele_order = LCD_RGB_ELEMENT_ORDER_RGB,
		//.rgb_ele_order = LCD_RGB_ELEMENT_ORDER_BGR,
        .bits_per_pixel = 16,
    };

	ESP_LOGI(TAG, "Install st7735 panel driver");
    ESP_ERROR_CHECK(esp_lcd_new_panel_st7735(io_handle, &panel_config, &panel_handle));
	ESP_ERROR_CHECK(esp_lcd_panel_reset(panel_handle));
    ESP_ERROR_CHECK(esp_lcd_panel_init(panel_handle));
    // ESP_ERROR_CHECK(esp_lcd_panel_invert_color(panel_handle, true));
	ESP_ERROR_CHECK(esp_lcd_panel_swap_xy(panel_handle, false));
    ESP_ERROR_CHECK(esp_lcd_panel_mirror(panel_handle, true, false));
    // user can flush pre-defined pattern to the screen before we turn on the screen or backlight
    ESP_ERROR_CHECK(esp_lcd_panel_disp_on_off(panel_handle, true));

	BLK_init();
	ESP_LOGI(TAG, "blk init ok");
	BLK(1);
	// uint16_t red_color = 0xF800;  // RGB565 格式的红色
    // esp_lcd_panel_draw_bitmap(panel_handle, 0, 0, EXAMPLE_LCD_H_RES, EXAMPLE_LCD_V_RES, &red_color);

}


void lcd_task(void *arg)
{
	// st7735_lcd_init();
	st7735_init();
	st7735_invert_color(1);
	while (1)
	{
		vTaskDelay(10 / portTICK_PERIOD_MS);
	}
	vTaskDelete(NULL);	
}