#include "leds_control.h"
#include "gp4_game.h"

#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include "cmsis_os.h"

#ifdef TEST_HEADER
#include TEST_HEADER
#endif

#ifndef NUMFER_OF_LEDS_PER_RING
#define NUMBER_OF_LEDS_PER_RING 24
#endif

#ifndef MAX_ROW
#define MAX_ROW 7
#endif

#ifndef MAX_COL
#define MAX_COL 7
#endif

#include "stm32f4xx_hal.h"
extern UART_HandleTypeDef huart3;
extern osMessageQueueId_t UARTReceptionHandle;
extern osMessageQueueId_t UARTSendHandle;

#define COL_COUNT 7		//il y a 7 colonnes (de 0 à 6)
#define LINE_COUNT 6	//il y a 6 lignes (de 0 à 5)
#define START_POSITION 3
#define SIZE_OF_BUFFER (4 + NUMBER_OF_LEDS_PER_RING * 3)


//static Color matrix[LINE_COUNT + 1][COL_COUNT];

//static bool is_matrix_init = false;

/**
 * @brief compute buffer to control led through serial link
 *
 * @param buffer Buffer to fill. Buffer must have enough memory: (4 + (nb leds per ring)*3) bytes
 * @param row Row number of led to control [1..7]
 * @param col Column number of led to control [1..7]
 * @param red Red value of RGB code
 * @param green Green value of RGB code
 * @param blue Blue value of RGB code
 */

/**
 * @brief encode number between 0 and 15 in its hexadecimal representation
 *
 * @param i Number to encode
 * @return [0-9A-F] if 0 < i < 16; X otherwise
 */
static inline unsigned char toHexaHalfByte(const unsigned char i) {
	if (i < 10) {
		return '0' + i;
	}
	else if (i < 16) {
		return 'A' + (i - 10);
	}
	else {
		return 'X';
	}
}

/**
 * @brief encode byte in its hexadecimal representation
 *
 * @param buffer Buffer to store result, should be at least size 2
 * @param byte Byte to encode
 */
static inline void encodeByte(unsigned char * const buffer, const unsigned char byte) {
	buffer[0] = toHexaHalfByte((byte >> 4) & 0x0F);
	buffer[1] = toHexaHalfByte(byte & 0x0F);
}

/**
 * @brief compute buffer to control led through serial link
 *
 * @param buffer Buffer to fill. Buffer must have enough memory: (4 + (nb leds per ring)*3) bytes
 * @param row Row number of led to control [1..7]
 * @param col Column number of led to control [1..7]
 * @param red Red value of RGB code
 * @param green Green value of RGB code
 * @param blue Blue value of RGB code
 */
static void computeMessage(unsigned char * const buffer,
		const unsigned char row,
		const unsigned char col,
		const unsigned char red,
		const unsigned char green,
		const unsigned char blue) {

	buffer[0] = 'R';

	buffer[1] = toHexaHalfByte(row);
	buffer[2] = toHexaHalfByte(col);
	encodeByte(&(buffer[3]), red);
	encodeByte(&(buffer[5]), green);
	encodeByte(&(buffer[7]), blue);

	buffer[SIZE_OF_LED_COMMAND_BUFFER - 1] = '\n';
}


LedControlReturnCode setLedColor(const unsigned int row,
		const unsigned int col,
		const unsigned int red,
		const unsigned int green,
		const unsigned int blue)	 {
	if (row > MAX_ROW || row == 0)
		return LCRC_ERROR_ROW;
	if (col > MAX_COL || col == 0)
		return LCRC_ERROR_COL;
	if (red > 255 || green > 255 || blue > 255)
		return LCRC_ERROR_RGB_VALUE;
	const unsigned int finalRow = row - 1;
	const unsigned int finalCol = col - 1;
	unsigned char buffer[10] = { 0 };
	computeMessage(buffer, finalRow, finalCol, red, green, blue);

	// HAL_UART_Transmit(&huart3, (uint8_t *)buffer, 10, 0xFFFF);

	osMessageQueuePut(UARTSendHandle, buffer, 1, 100);
	return LCRC_OK;
}

char readbutton(char *pReadData, char DataSize)
{
	//	unsigned char buffer[SIZE_OF_PLAYER_COMMAND_BUFFER] = { 0 };
	//	//const HAL_StatusTypeDef statusUART = HAL_UART_Receive(&huart3,(uint8_t*)buffer,SIZE_OF_PLAYER_COMMAND_BUFFER ,1 );
	//	if (statusUART == HAL_OK)
	//	{
	//		if(statusUART<=DataSize)
	//		{
	//			memcpy(pReadData,buffer,statusUART);
	//		}
	//		return LCRC_OK;
	//	}
	//	else
	//	{
	//		return LCRC_ERROR_SERIAL_READ;
	//
	//	}

	if (osMessageQueueGet(UARTReceptionHandle, pReadData, NULL, osWaitForever)==osOK){
		return LCRC_OK;
	}
	else {
		return LCRC_ERROR_SERIAL_READ;
	}
}


