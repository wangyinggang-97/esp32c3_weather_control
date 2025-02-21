#ifndef TIMER_H
#define TIMER_H

#include "main.h"

void esptimer_init(void);
void periodic_timer_callback(void* arg);
#endif