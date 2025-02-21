#include "lcd.h"
#include "main.h"
#include "lvgl.h"
#include "lv_demos.h"


static const char* TAG = "SPI_LCD" ;

static lv_disp_draw_buf_t disp_buf; // contains internal graphic buffer(s) called draw buffer(s)
static lv_disp_drv_t disp_drv;      // contains callback functions

static bool example_notify_lvgl_flush_ready(esp_lcd_panel_io_handle_t panel_io, esp_lcd_panel_io_event_data_t *edata, void *user_ctx)
{
    lv_disp_drv_t *disp_driver = (lv_disp_drv_t *)user_ctx;
    lv_disp_flush_ready(disp_driver);
    return false;
}

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
static void example_lvgl_flush_cb(lv_disp_drv_t *drv, const lv_area_t *area, lv_color_t *color_map)
{
    esp_lcd_panel_handle_t panel_handle = (esp_lcd_panel_handle_t) drv->user_data;
    int offsetx1 = area->x1;
    int offsetx2 = area->x2;
    int offsety1 = area->y1;
    int offsety2 = area->y2;
    // copy a buffer's content to a specific area of the display
    esp_lcd_panel_draw_bitmap(panel_handle, offsetx1, offsety1, offsetx2 + 1, offsety2 + 1, color_map);
}
/* Rotate display and touch, when rotated screen in LVGL. Called when driver parameters are updated. */
static void example_lvgl_port_update_callback(lv_disp_drv_t *drv)
{
    esp_lcd_panel_handle_t panel_handle = (esp_lcd_panel_handle_t) drv->user_data;

    switch (drv->rotated) {
    case LV_DISP_ROT_NONE:
        // Rotate LCD display
        esp_lcd_panel_swap_xy(panel_handle, false);
        esp_lcd_panel_mirror(panel_handle, true, false);
        // Rotate LCD touch
        // esp_lcd_touch_set_mirror_y(tp, false);
        // esp_lcd_touch_set_mirror_x(tp, false);

        break;
    case LV_DISP_ROT_90:
        // Rotate LCD display
        esp_lcd_panel_swap_xy(panel_handle, true);
        esp_lcd_panel_mirror(panel_handle, true, true);
        // Rotate LCD touch
        // esp_lcd_touch_set_mirror_y(tp, false);
        // esp_lcd_touch_set_mirror_x(tp, false);
        break;
    case LV_DISP_ROT_180:
        // Rotate LCD display
        esp_lcd_panel_swap_xy(panel_handle, false);
        esp_lcd_panel_mirror(panel_handle, false, true);
        // Rotate LCD touch
        // esp_lcd_touch_set_mirror_y(tp, false);
        // esp_lcd_touch_set_mirror_x(tp, false);

        break;
    case LV_DISP_ROT_270:
        // Rotate LCD display
        esp_lcd_panel_swap_xy(panel_handle, true);
        esp_lcd_panel_mirror(panel_handle, false, false);
        // Rotate LCD touch
        // esp_lcd_touch_set_mirror_y(tp, false);
        // esp_lcd_touch_set_mirror_x(tp, false);
        break;
    }
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
		.on_color_trans_done = example_notify_lvgl_flush_ready,
        .user_ctx = &disp_drv,
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
	// ESP_ERROR_CHECK(esp_lcd_panel_swap_xy(panel_handle, false));
    // ESP_ERROR_CHECK(esp_lcd_panel_mirror(panel_handle, true, false));
    // user can flush pre-defined pattern to the screen before we turn on the screen or backlight
    ESP_ERROR_CHECK(esp_lcd_panel_disp_on_off(panel_handle, true));

	BLK_init();
	ESP_LOGI(TAG, "blk init ok");
	BLK(1);
	// uint16_t *background;

	// background = (uint16_t *)malloc(EXAMPLE_LCD_H_RES * EXAMPLE_LCD_V_RES); 

	// for(int i = 0; i < EXAMPLE_LCD_H_RES * EXAMPLE_LCD_V_RES; i++)
	// {
	// 	 background[i] = COLOR_BLACK;
	// 	// background[i] = COLOR_WHITE;
	// 	//background[i] = COLOR_BLUE;
	// }
    // esp_lcd_panel_draw_bitmap(panel_handle, 0, 0, EXAMPLE_LCD_H_RES, EXAMPLE_LCD_V_RES, background);

	ESP_LOGI(TAG, "Initialize LVGL library");
    lv_init();
    // alloc draw buffers used by LVGL
    // it's recommended to choose the size of the draw buffer(s) to be at least 1/10 screen sized
    lv_color_t *buf1 = heap_caps_malloc(EXAMPLE_LCD_H_RES * 20 * sizeof(lv_color_t), MALLOC_CAP_DMA);
    assert(buf1);
    lv_color_t *buf2 = heap_caps_malloc(EXAMPLE_LCD_H_RES * 20 * sizeof(lv_color_t), MALLOC_CAP_DMA);
    assert(buf2);
    // initialize LVGL draw buffers
    lv_disp_draw_buf_init(&disp_buf, buf1, buf2, EXAMPLE_LCD_H_RES * 20);

	ESP_LOGI(TAG, "Register display driver to LVGL");
    lv_disp_drv_init(&disp_drv);
    disp_drv.hor_res = EXAMPLE_LCD_H_RES;
    disp_drv.ver_res = EXAMPLE_LCD_V_RES;
    disp_drv.flush_cb = example_lvgl_flush_cb;
    disp_drv.drv_update_cb = example_lvgl_port_update_callback;
    disp_drv.draw_buf = &disp_buf;
    disp_drv.user_data = panel_handle;
    lv_disp_t *disp = lv_disp_drv_register(&disp_drv);


}


void lcd_task(void *arg)
{
	st7735_lcd_init();
	// st7735_init();
	// st7735_rect(0,0,50,50,0xF800);
	//lv_demo_widgets();
	lv_demo_benchmark();
	while (1)
	{
		lv_timer_handler();
		vTaskDelay(10 / portTICK_PERIOD_MS);
	}
	vTaskDelete(NULL);	
}