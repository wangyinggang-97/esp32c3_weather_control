#include "main.h"
#include "lvgl.h"

void periodic_timer_callback(void* arg)
{
    //button_ticks();
	/* Tell LVGL how many milliseconds has elapsed */
    lv_tick_inc(EXAMPLE_LVGL_TICK_PERIOD_MS);	
}

void esptimer_init(void)
{
	const esp_timer_create_args_t periodic_timer_args={
		.callback=&periodic_timer_callback,
		.name="periodic"
	};
	esp_timer_handle_t periodic_timer;
	 /* The timer has been created but is not running yet */
	esp_timer_create(&periodic_timer_args, &periodic_timer);
	
	 /* Start the timers */
    esp_timer_start_periodic(periodic_timer, 5000); //5ms

}