/*
 * key.h
 *
 *  Created on: Oct 9, 2024
 *      Author: Administrator
 */

#ifndef KEY_H_
#define KEY_H_

void Button1_init(uint32_t button_num, uint8_t BUTTON_ACTIVE_LEVEL);
void Button2_init(uint32_t button_num, uint8_t BUTTON_ACTIVE_LEVEL);
void Button3_init(uint32_t button_num, uint8_t BUTTON_ACTIVE_LEVEL);

void Btn_init(void);
void Key_task(void *arg);
#endif /* KEY_H_ */
