/*
  ******************************************************************************
  * File Name          : ucg_com_stm32_hal.c
  * Description        : Main program body
  ******************************************************************************
  * µC-spezifische Anweisungen zw. ucg und stm32
  * Hal-Driver im Einsatz
  ******************************************************************************
*/


#include "stm32f1xx_hal.h"
#include "ucg.h"
#include "ucg_com_stm32_hal.h"

int16_t ucg_com_stm32_hal(ucg_t *ucg, int16_t msg, uint16_t arg, uint8_t *data)
{

	//  uint8_t *ptr;
	//  static uint8_t buffer_count;
	//  static uint8_t buffer[DATA_BUFFER_SIZE+1];


  switch(msg)
  {
    case UCG_COM_MSG_POWER_UP: //10
      /* "data" is a pointer to ucg_com_info_t structure with the following information: */
      /*	((ucg_com_info_t *)data)->serial_clk_speed value in nanoseconds */
      /*	((ucg_com_info_t *)data)->parallel_clk_speed value in nanoseconds */
      /* "arg" is not used */

      /* This message is sent once at the uC startup and for power up. */			// done by HAL_init
      /* setup i/o or do any other setup */
      break;

    case UCG_COM_MSG_POWER_DOWN:  //11
      /* "data" and "arg" are not used*/
      /* This message is sent for a power down request */

      break;
    case UCG_COM_MSG_DELAY:  //12
      /* "data" is not used */
      /* "arg" contains the number of microseconds for the delay */
      /* By receiving this message, the following code should delay by */
      /* "arg" microseconds. One microsecond is 0.000001 second */

      break;
    case UCG_COM_MSG_CHANGE_RESET_LINE: //13
      /* "data" is not used */
      /* "arg" = 1: set the reset output line to 1 */							// idle => high = 1
      /* "arg" = 0: set the reset output line to 0 */							// active => low = 0
    	if(arg == 0)
    	    HAL_GPIO_WritePin(Reset_GPIO_Port, Reset_Pin, GPIO_PIN_RESET);
    	else
    	  	HAL_GPIO_WritePin(Reset_GPIO_Port, Reset_Pin, GPIO_PIN_SET);

      break;

    case UCG_COM_MSG_CHANGE_CD_LINE:  //15
      /* "ucg->com_status"  bit 0 contains the old level for the CD line */
      /* "data" is not used */
      /* "arg" = 1: set the command/data (a0) output line to 1 */				//high = 1 => data or parameter
      /* "arg" = 0: set the command/data (a0) output line to 0 */				//low  = 0 => command
    	if(arg == 0)
    		HAL_GPIO_WritePin(CD_GPIO_Port, CD_Pin, GPIO_PIN_RESET);
    	else
    		HAL_GPIO_WritePin(CD_GPIO_Port, CD_Pin, GPIO_PIN_SET);

      break;

    case UCG_COM_MSG_CHANGE_CS_LINE:  //14
      /* "ucg->com_status"  bit 1 contains the old level for the CS line */
      /* "data" is not used */
      /* "arg" = 1: set the chipselect output line to 1 */
      /* "arg" = 0: set the chipselect output line to 0 */ 						//active => low = 0

    	if(arg == 0)
    		HAL_GPIO_WritePin(CS_GPIO_Port, CS_Pin, GPIO_PIN_RESET);
    	else
    		HAL_GPIO_WritePin(CS_GPIO_Port, CS_Pin, GPIO_PIN_SET);

      break;

    case UCG_COM_MSG_SEND_BYTE:  //16
      /* "data" is not used */
      /* "arg" contains one byte, which should be sent to the display */
      /* The current status of the CD line is available */
      /* in bit 0 of u8g->com_status */
    	HAL_SPI_Transmit(&SPI_HANDLER, (uint8_t *)&arg, 1, SPI_TIMEOUT);

      break;

    case UCG_COM_MSG_REPEAT_1_BYTE: //17
      /* "data[0]" contains one byte */
      /* repeat sending the byte in data[0] "arg" times */
      /* The current status of the CD line is available */
      /* in bit 0 of u8g->com_status */
    	while( arg > 0 ) {
        	HAL_SPI_Transmit(&SPI_HANDLER, (uint8_t *)data, 1, SPI_TIMEOUT);
        arg--;
          }
      break;

    case UCG_COM_MSG_REPEAT_2_BYTES: //18
      /* "data[0]" contains first byte */
      /* "data[1]" contains second byte */
      /* repeat sending the two bytes "arg" times */
      /* The current status of the CD line is available */
      /* in bit 0 of u8g->com_status */
    	while( arg > 0 ) {
    		HAL_SPI_Transmit(&SPI_HANDLER, (uint8_t *)data, 2, SPI_TIMEOUT);
    	arg--;
         }
      break;

    case UCG_COM_MSG_REPEAT_3_BYTES:  //19
      /* "data[0]" contains first byte */
      /* "data[1]" contains second byte */
      /* "data[2]" contains third byte */
      /* repeat sending the three bytes "arg" times */
      /* The current status of the CD line is available */
      /* in bit 0 of u8g->com_status */
    	while( arg > 0 ) {
    		HAL_SPI_Transmit(&SPI_HANDLER, (uint8_t *)data, 3, SPI_TIMEOUT);
    	arg--;
          }
       break;

    case UCG_COM_MSG_SEND_STR:  //20
      /* "data" is an array with "arg" bytes */
      /* send "arg" bytes to the display */

    		HAL_SPI_Transmit(&SPI_HANDLER, (uint8_t *)data, arg, SPI_TIMEOUT);

      break;

    case UCG_COM_MSG_SEND_CD_DATA_SEQUENCE:  //21
      /* "data" is a pointer too two bytes, which contain the cd line status and display data */
      /* "arg" contains the number of these two byte tuples which need to be analyzed and sent.*/
      /* Below is a example sequence. The content of bit 0 in u8g->com_status is undefined for this message */

      while(arg > 0)
      {
    	  if ( *data != 0 )
    	  	  {
    		  	  if ( *data == 1 )
    		  	  {
    		  		  /* set CD (=D/C=A0) line to low */
    		  		  HAL_GPIO_WritePin(CD_GPIO_Port, CD_Pin, GPIO_PIN_RESET);
    		  	  }
    		  	  else
    		  	  {
    		  		  /* set CD (=D/C=A0) line to high */
    		  		  HAL_GPIO_WritePin(CD_GPIO_Port, CD_Pin, GPIO_PIN_SET);
    		  	  }
    	  	  }
    	  data++;
			/* send *data to the display */
			HAL_SPI_Transmit(&SPI_HANDLER, (uint8_t *)data, 1, SPI_TIMEOUT);
		  data++;
		  arg--;
      }
      break;
  }
  return 1;
}
