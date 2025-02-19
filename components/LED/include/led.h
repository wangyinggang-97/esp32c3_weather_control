#ifndef LED_H
#define LED_H

#include "main.h"
#include "led_strip.h"
#include "led_strip_interface.h"

void breathing_effect(uint8_t r, uint8_t g, uint8_t b, uint16_t delay_ms);
void flowing_effect(uint8_t r, uint8_t g, uint8_t b, uint16_t delay_ms);
void led_task(void *arg);


#endif