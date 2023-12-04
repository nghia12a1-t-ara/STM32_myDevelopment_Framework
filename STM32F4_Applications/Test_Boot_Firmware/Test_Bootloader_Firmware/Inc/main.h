/*
 * main.h
 *
 *  Created on: Sep 24, 2023
 *      Author: WIN 10
 */

#ifndef MAIN_H_
#define MAIN_H_

#include "USART.h"
#include "Flash.h"
#include "Bootloader.h"
#include "GPIO.h"
#include "Systick.h"

/* USART1 TX Pin */
#define USART1_TX_PIN					GPIO_PIN_NO_9
#define USART1_TX_PORT_INS				GPIO_INSTANCE_A

/* USART1 RX Pin */
#define USART1_RX_PIN					GPIO_PIN_NO_10
#define USART1_RX_PORT_INS				GPIO_INSTANCE_A

#endif /* MAIN_H_ */
