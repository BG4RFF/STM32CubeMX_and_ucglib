/*
 * ucg_com_stm32_hal.h
 *
 *  Created on: 04.02.2018
 *      Author: Hare
 */

#ifndef UCG_COM_STM32_HAL_H_
#define UCG_COM_STM32_HAL_H_

#include "ucg.h"
#include "stm32f1xx_hal.h"


#define DATA_BUFFER_SIZE 128
#define SPI_TIMEOUT 10000
#define SPI_HANDLER hspi1

extern SPI_HandleTypeDef hspi1; // use your spi handler

int16_t ucg_com_stm32_hal(ucg_t *ucg, int16_t msg, uint16_t arg, uint8_t *data);

#endif /* UCG_COM_STM32_HAL_H_ */
