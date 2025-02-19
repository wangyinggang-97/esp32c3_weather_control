#ifndef MyUART_H_
#define MyUART_H_

#include "main.h"

#define RX_BUF_SIZE 100
#define TXD_PIN  (GPIO_NUM_5)
#define RXD_PIN  (GPIO_NUM_4)

void MyUart_init(void);
int sendData(const char* logName, const char* data);

void tx_task(void *arg);
void rx_task(void *arg);
#endif