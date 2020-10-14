/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
 */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include <unistd.h>
#include <stdio.h>
#include <string.h>
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
ETH_HandleTypeDef heth;

UART_HandleTypeDef huart3;

PCD_HandleTypeDef hpcd_USB_OTG_FS;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_ETH_Init(void);
static void MX_USART3_UART_Init(void);
static void MX_USB_OTG_FS_PCD_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void)
{
	/* USER CODE BEGIN 1 */

	/* USER CODE END 1 */

	/* MCU Configuration--------------------------------------------------------*/

	/* Reset of all peripherals, Initializes the Flash interface and the Systick. */
	HAL_Init();

	/* USER CODE BEGIN Init */

	/* USER CODE END Init */

	/* Configure the system clock */
	SystemClock_Config();

	/* USER CODE BEGIN SysInit */

	/* USER CODE END SysInit */

	/* Initialize all configured peripherals */
	MX_GPIO_Init();
	MX_ETH_Init();
	MX_USART3_UART_Init();
	MX_USB_OTG_FS_PCD_Init();
	/* USER CODE BEGIN 2 */

	/* USER CODE END 2 */

	/* Infinite loop */
	/* USER CODE BEGIN WHILE */
	//création des couleurs//

	typedef struct{
		int RValue;
		int GValue;
		int BValue;
	}color;

	color white = {255, 255, 255},
			green = {0, 255, 0},
			blue = {0, 0, 255},
			red = {255, 0, 0},
			purple = {255, 0, 255},
			yellow = {255, 255, 0},
			black = {0, 0, 0};

	void setLedColor(const unsigned int row, const unsigned int col, const unsigned int red, const unsigned int green,
			const unsigned int blue) {

		char message[11];
		sprintf(message, "R%d%d%02x%02x%02x\n", row, col, red, green, blue);
		HAL_UART_Transmit(&huart3, (uint8_t*)message, strlen(message), 10);
		HAL_Delay(50);

	}

	//recoit un tableau et l'affiche//

	//TODO ajouter fonction pour comparer matrice et actual_display pour modifier que les cases nécessaires //
	void Setledmatrix(color **tabline, int tabsize){
		for (int row = 0; row < tabsize; row ++){
			for (int col = 0; col < tabsize; col ++){
				setLedColor((row), (col), tabline[row][col].RValue, tabline[row][col].GValue, tabline[row][col].BValue );
				//HAL_UART_Transmit(&huart3, (uint8_t*)msg, strlen(msg), 10);

			}
		}
	}




	//créée et affiche un tableau de couleur unie//

	void Setonecolor(color color_selected,int tabsize){
		color line [7] = {color_selected, color_selected, color_selected, color_selected, color_selected, color_selected, color_selected};
		color * tabline [7] = {line, line, line, line, line, line, line};
		Setledmatrix(tabline, tabsize);
	}


	//créée et affiche tableau avec numéro//

	void Setnumber(int number, color nbr_color, color bckgrnd, int tabsize){
		if (number == 0){                  // modifie la couleur des emplacements à modifier pour former un 0 //
			color line_1 [7] = {bckgrnd, bckgrnd, nbr_color, nbr_color, nbr_color, bckgrnd, bckgrnd};
			color line_2 [7] = {bckgrnd, nbr_color, bckgrnd, bckgrnd, bckgrnd, nbr_color, bckgrnd};
			color line_3 [7] = {bckgrnd, nbr_color, bckgrnd, bckgrnd, bckgrnd, nbr_color, bckgrnd};
			color line_4 [7] = {bckgrnd, nbr_color, bckgrnd, bckgrnd, bckgrnd, nbr_color, bckgrnd};
			color line_5 [7] = {bckgrnd, nbr_color, bckgrnd, bckgrnd, bckgrnd, nbr_color, bckgrnd};
			color line_6 [7] = {bckgrnd, nbr_color, bckgrnd, bckgrnd, bckgrnd, nbr_color, bckgrnd};
			color line_7 [7] = {bckgrnd, bckgrnd, nbr_color, nbr_color, nbr_color, bckgrnd, bckgrnd};
			color *number_tabline [7] = {line_1, line_2, line_3, line_4, line_5, line_6, line_7};
			Setledmatrix(number_tabline, tabsize);
		}
		if (number == 1){                  // modifie la couleur des emplacements à modifier pour former un 1 //
			color line_1 [7] = {bckgrnd, bckgrnd, bckgrnd, nbr_color, bckgrnd, bckgrnd, bckgrnd};
			color line_2 [7] = {bckgrnd, bckgrnd, nbr_color, nbr_color, bckgrnd, bckgrnd, bckgrnd};
			color line_3 [7] = {bckgrnd, nbr_color, bckgrnd, nbr_color, bckgrnd, bckgrnd, bckgrnd};
			color line_4 [7] = {bckgrnd, bckgrnd, bckgrnd, nbr_color, bckgrnd, bckgrnd, bckgrnd};
			color line_5 [7] = {bckgrnd, bckgrnd, bckgrnd, nbr_color, bckgrnd, bckgrnd, bckgrnd};
			color line_6 [7] = {bckgrnd, bckgrnd, bckgrnd, nbr_color, bckgrnd, bckgrnd, bckgrnd};
			color line_7 [7] = {bckgrnd, nbr_color, nbr_color, nbr_color, nbr_color, nbr_color, bckgrnd};
			color *number_tabline [7] = {line_1, line_2, line_3, line_4, line_5, line_6, line_7};
			Setledmatrix(number_tabline, tabsize);
		}
		if (number == 2){
			color line_1 [7] = {bckgrnd, bckgrnd, nbr_color, nbr_color, nbr_color, bckgrnd, bckgrnd};
			color line_2 [7] = {bckgrnd, nbr_color, bckgrnd, bckgrnd, bckgrnd, nbr_color, bckgrnd};
			color line_3 [7] = {bckgrnd, bckgrnd, bckgrnd, bckgrnd, bckgrnd, nbr_color, bckgrnd};
			color line_4 [7] = {bckgrnd, bckgrnd, nbr_color, nbr_color, nbr_color, bckgrnd, bckgrnd};
			color line_5 [7] = {bckgrnd, nbr_color, bckgrnd, bckgrnd, bckgrnd, bckgrnd, bckgrnd};
			color line_6 [7] = {bckgrnd, nbr_color, bckgrnd, bckgrnd, bckgrnd, bckgrnd, bckgrnd};
			color line_7 [7] = {bckgrnd, bckgrnd, nbr_color, nbr_color, nbr_color, nbr_color, bckgrnd};
			color *number_tabline [7] = {line_1, line_2, line_3, line_4, line_5, line_6, line_7};
			Setledmatrix(number_tabline, tabsize);
		}

		if (number == 3){
			color line_1 [7] = {bckgrnd, bckgrnd, nbr_color, nbr_color, nbr_color, bckgrnd, bckgrnd};
			color line_2 [7] = {bckgrnd, nbr_color, bckgrnd, bckgrnd, bckgrnd, nbr_color, bckgrnd};
			color line_3 [7] = {bckgrnd, bckgrnd, bckgrnd, bckgrnd, bckgrnd, nbr_color, bckgrnd};
			color line_4 [7] = {bckgrnd, bckgrnd, bckgrnd, nbr_color, nbr_color, bckgrnd, bckgrnd};
			color line_5 [7] = {bckgrnd, bckgrnd, bckgrnd, bckgrnd, bckgrnd, nbr_color, bckgrnd};
			color line_6 [7] = {bckgrnd, nbr_color, bckgrnd, bckgrnd, bckgrnd, nbr_color, bckgrnd};
			color line_7 [7] = {bckgrnd, bckgrnd, nbr_color, nbr_color, nbr_color, bckgrnd, bckgrnd};
			color *number_tabline [7] = {line_1, line_2, line_3, line_4, line_5, line_6, line_7};
			Setledmatrix(number_tabline, tabsize);
		}

		if (number == 4){
			color line_1 [7] = {bckgrnd, nbr_color, bckgrnd, bckgrnd, bckgrnd, nbr_color, bckgrnd};
			color line_2 [7] = {bckgrnd, nbr_color, bckgrnd, bckgrnd, bckgrnd, nbr_color, bckgrnd};
			color line_3 [7] = {bckgrnd, nbr_color, bckgrnd, bckgrnd, bckgrnd, nbr_color, bckgrnd};
			color line_4 [7] = {bckgrnd, bckgrnd, nbr_color, nbr_color, nbr_color, bckgrnd, bckgrnd};
			color line_5 [7] = {bckgrnd, bckgrnd, bckgrnd, bckgrnd, bckgrnd, nbr_color, bckgrnd};
			color line_6 [7] = {bckgrnd, bckgrnd, bckgrnd, bckgrnd, bckgrnd, nbr_color, bckgrnd};
			color line_7 [7] = {bckgrnd, bckgrnd, bckgrnd, bckgrnd, bckgrnd, nbr_color, bckgrnd};
			color *number_tabline [7] = {line_1, line_2, line_3, line_4, line_5, line_6, line_7};
			Setledmatrix(number_tabline, tabsize);
		}

		if (number == 5){
			color line_1 [7] = {bckgrnd, nbr_color, nbr_color, nbr_color, nbr_color, nbr_color, bckgrnd};
			color line_2 [7] = {bckgrnd, nbr_color, bckgrnd, bckgrnd, bckgrnd, bckgrnd, bckgrnd};
			color line_3 [7] = {bckgrnd, nbr_color, bckgrnd, bckgrnd, bckgrnd, bckgrnd, bckgrnd};
			color line_4 [7] = {bckgrnd, bckgrnd, nbr_color, nbr_color, nbr_color, bckgrnd, bckgrnd};
			color line_5 [7] = {bckgrnd, bckgrnd, bckgrnd, bckgrnd, bckgrnd, nbr_color, bckgrnd};
			color line_6 [7] = {bckgrnd, bckgrnd, bckgrnd, bckgrnd, bckgrnd, nbr_color, bckgrnd};
			color line_7 [7] = {bckgrnd, nbr_color, nbr_color, nbr_color, nbr_color, bckgrnd, bckgrnd};
			color *number_tabline [7] = {line_1, line_2, line_3, line_4, line_5, line_6, line_7};
			Setledmatrix(number_tabline, tabsize);
		}

		if (number == 6){
			color line_1 [7] = {bckgrnd, bckgrnd, nbr_color, nbr_color, nbr_color, bckgrnd, bckgrnd};
			color line_2 [7] = {bckgrnd, nbr_color, bckgrnd, bckgrnd, bckgrnd, nbr_color, bckgrnd};
			color line_3 [7] = {bckgrnd, nbr_color, bckgrnd, bckgrnd, bckgrnd, bckgrnd, bckgrnd};
			color line_4 [7] = {bckgrnd, bckgrnd, nbr_color, nbr_color, nbr_color, bckgrnd, bckgrnd};
			color line_5 [7] = {bckgrnd, nbr_color, bckgrnd, bckgrnd, bckgrnd, nbr_color, bckgrnd};
			color line_6 [7] = {bckgrnd, nbr_color, bckgrnd, bckgrnd, bckgrnd, nbr_color, bckgrnd};
			color line_7 [7] = {bckgrnd, bckgrnd, nbr_color, nbr_color, nbr_color, bckgrnd, bckgrnd};
			color *number_tabline [7] = {line_1, line_2, line_3, line_4, line_5, line_6, line_7};
			Setledmatrix(number_tabline, tabsize);
		}

		if (number == 7){
			color line_1 [7] = {bckgrnd, nbr_color, nbr_color, nbr_color, nbr_color, nbr_color, bckgrnd};
			color line_2 [7] = {bckgrnd, bckgrnd, bckgrnd, bckgrnd, bckgrnd, nbr_color, bckgrnd};
			color line_3 [7] = {bckgrnd, bckgrnd, bckgrnd, bckgrnd, bckgrnd, nbr_color, bckgrnd};
			color line_4 [7] = {bckgrnd, bckgrnd, bckgrnd, bckgrnd, nbr_color, bckgrnd, bckgrnd};
			color line_5 [7] = {bckgrnd, bckgrnd, bckgrnd, nbr_color, bckgrnd, bckgrnd, bckgrnd};
			color line_6 [7] = {bckgrnd, bckgrnd, nbr_color, bckgrnd, bckgrnd, bckgrnd, bckgrnd};
			color line_7 [7] = {bckgrnd, nbr_color, bckgrnd, bckgrnd, bckgrnd, bckgrnd, bckgrnd};
			color *number_tabline [7] = {line_1, line_2, line_3, line_4, line_5, line_6, line_7};
			Setledmatrix(number_tabline, tabsize);
		}

		if (number == 8){
			color line_1 [7] = {bckgrnd, bckgrnd, nbr_color, nbr_color, nbr_color, bckgrnd, bckgrnd};
			color line_2 [7] = {bckgrnd, nbr_color, bckgrnd, bckgrnd, bckgrnd, nbr_color, bckgrnd};
			color line_3 [7] = {bckgrnd, nbr_color, bckgrnd, bckgrnd, bckgrnd, nbr_color, bckgrnd};
			color line_4 [7] = {bckgrnd, bckgrnd, nbr_color, nbr_color, nbr_color, bckgrnd, bckgrnd};
			color line_5 [7] = {bckgrnd, nbr_color, bckgrnd, bckgrnd, bckgrnd, nbr_color, bckgrnd};
			color line_6 [7] = {bckgrnd, nbr_color, bckgrnd, bckgrnd, bckgrnd, nbr_color, bckgrnd};
			color line_7 [7] = {bckgrnd, bckgrnd, nbr_color, nbr_color, nbr_color, bckgrnd, bckgrnd};
			color *number_tabline [7] = {line_1, line_2, line_3, line_4, line_5, line_6, line_7};
			Setledmatrix(number_tabline, tabsize);
		}

		if (number == 9){
			color line_1 [7] = {bckgrnd, bckgrnd, nbr_color, nbr_color, nbr_color, bckgrnd, bckgrnd};
			color line_2 [7] = {bckgrnd, nbr_color, bckgrnd, bckgrnd, bckgrnd, nbr_color, bckgrnd};
			color line_3 [7] = {bckgrnd, nbr_color, bckgrnd, bckgrnd, bckgrnd, nbr_color, bckgrnd};
			color line_4 [7] = {bckgrnd, bckgrnd, nbr_color, nbr_color, nbr_color, bckgrnd, bckgrnd};
			color line_5 [7] = {bckgrnd, bckgrnd, bckgrnd, bckgrnd, bckgrnd, nbr_color, bckgrnd};
			color line_6 [7] = {bckgrnd, nbr_color, bckgrnd, bckgrnd, bckgrnd, nbr_color, bckgrnd};
			color line_7 [7] = {bckgrnd, bckgrnd, nbr_color, nbr_color, nbr_color, bckgrnd, bckgrnd};
			color *number_tabline [7] = {line_1, line_2, line_3, line_4, line_5, line_6, line_7};
			Setledmatrix(number_tabline, tabsize);
		}
	}


	//affiche un compte à rebours
	void countdown(int countdown, int tabsize){
		for(int count = countdown; count >= 0; count --){
			if (count == 9){
				Setnumber(count, white, black, tabsize);
			}
			if (count == 8){
				Setnumber(count, blue, black, tabsize);
			}
			if (count == 7){
				Setnumber(count, green, black, tabsize);
			}
			if (count == 6){
				Setnumber(count, yellow, black, tabsize);
			}
			if (count == 5){
				Setnumber(count, purple, black, tabsize);
			}
			if (count == 4){
				Setnumber(count, red, black, tabsize);
			}
			if (count == 3){
				Setnumber(count, green, black, tabsize);
			}
			if (count == 2){
				Setnumber(count, yellow, black, tabsize);
			}
			if (count == 1){
				Setnumber(count, red, black, tabsize);
			}
			if (count == 0){
				Setnumber(count, white, black, tabsize);
			}
			HAL_Delay(500);
		}
	}

	while (1)
	{

		int button_state = 0;
		while (button_state = HAL_GPIO_ReadPin(USER_Btn_GPIO_Port, USER_Btn_Pin) == 1){
			countdown(9,7);
			int new_button_state = HAL_GPIO_ReadPin(USER_Btn_GPIO_Port, USER_Btn_Pin);
			if (new_button_state==1){
				button_state = 0;
			}
		}

				//		Setnumber(5, red, white, 7);
				//		Setnumber(4, green, white, 7);
				//		Setnumber(3, blue, white, 7);
				//		Setnumber(2, red, green, 7);
				//		Setnumber(1, blue, white, 7);

				/* **********************************Correction de Thomas************************************
				 *	char int_to_ascii_hex_nibble(uint8_t nibble) {											*
				 * 		if (nibble < 10) return '0'+nibble;													*
				 *		else if (nibble < 16) return 'A'+(nibble-10);										*
				 *		else return '0';																	*
				 *	}																						*
				 *	void setLedColor(uint8_t row, uint8_t col, uint8_t red, uint8_t green, uint8_t blue) {	*
				 *		uint8_t trame[10];																	*
				 *		trame[0] = 'R';																		*
				 *		trame[1] = '0' + row;																*
				 *		trame[2] = '0' + col;																*
				 *		trame[3] = int_to_ascii_hex_nibble((red & 0xf0)>>4);								*
				 *		trame[4] = int_to_ascii_hex_nibble(red & 0x0f);										*
				 *		trame[5] = int_to_ascii_hex_nibble((green & 0xf0)>>4);								*
				 *		trame[6] = int_to_ascii_hex_nibble(green & 0x0f);									*
				 *		trame[7] = int_to_ascii_hex_nibble((blue & 0xf0)>>4);								*
				 *		trame[8] = int_to_ascii_hex_nibble(blue & 0x0f);									*
				 *		trame[9] = '\n';																	*
				 *		HAL_UART_Transmit(&huart3, trame, 10, 100);											*
				 *	}																						*
				 * 																							*
				 *********************************************************************************************/




				/* USER CODE END WHILE */

				/* USER CODE BEGIN 3 */
			}
			/* USER CODE END 3 */
		}

		/**
		 * @brief System Clock Configuration
		 * @retval None
		 */
		void SystemClock_Config(void)
		{
			RCC_OscInitTypeDef RCC_OscInitStruct = {0};
			RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

			/** Configure the main internal regulator output voltage
			 */
			__HAL_RCC_PWR_CLK_ENABLE();
			__HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
			/** Initializes the CPU, AHB and APB busses clocks
			 */
			RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
			RCC_OscInitStruct.HSEState = RCC_HSE_BYPASS;
			RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
			RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
			RCC_OscInitStruct.PLL.PLLM = 4;
			RCC_OscInitStruct.PLL.PLLN = 168;
			RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
			RCC_OscInitStruct.PLL.PLLQ = 7;
			if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
			{
				Error_Handler();
			}
			/** Initializes the CPU, AHB and APB busses clocks
			 */
			RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
					|RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
			RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
			RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
			RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
			RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

			if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
			{
				Error_Handler();
			}
		}

		/**
		 * @brief ETH Initialization Function
		 * @param None
		 * @retval None
		 */
		static void MX_ETH_Init(void)
		{

			/* USER CODE BEGIN ETH_Init 0 */

			/* USER CODE END ETH_Init 0 */

			/* USER CODE BEGIN ETH_Init 1 */

			/* USER CODE END ETH_Init 1 */
			heth.Instance = ETH;
			heth.Init.AutoNegotiation = ETH_AUTONEGOTIATION_ENABLE;
			heth.Init.PhyAddress = LAN8742A_PHY_ADDRESS;
			heth.Init.MACAddr[0] =   0x00;
			heth.Init.MACAddr[1] =   0x80;
			heth.Init.MACAddr[2] =   0xE1;
			heth.Init.MACAddr[3] =   0x00;
			heth.Init.MACAddr[4] =   0x00;
			heth.Init.MACAddr[5] =   0x00;
			heth.Init.RxMode = ETH_RXPOLLING_MODE;
			heth.Init.ChecksumMode = ETH_CHECKSUM_BY_HARDWARE;
			heth.Init.MediaInterface = ETH_MEDIA_INTERFACE_RMII;

			/* USER CODE BEGIN MACADDRESS */

			/* USER CODE END MACADDRESS */

			if (HAL_ETH_Init(&heth) != HAL_OK)
			{
				Error_Handler();
			}
			/* USER CODE BEGIN ETH_Init 2 */

			/* USER CODE END ETH_Init 2 */

		}

		/**
		 * @brief USART3 Initialization Function
		 * @param None
		 * @retval None
		 */
		static void MX_USART3_UART_Init(void)
		{

			/* USER CODE BEGIN USART3_Init 0 */

			/* USER CODE END USART3_Init 0 */

			/* USER CODE BEGIN USART3_Init 1 */

			/* USER CODE END USART3_Init 1 */
			huart3.Instance = USART3;
			huart3.Init.BaudRate = 115200;
			huart3.Init.WordLength = UART_WORDLENGTH_8B;
			huart3.Init.StopBits = UART_STOPBITS_1;
			huart3.Init.Parity = UART_PARITY_NONE;
			huart3.Init.Mode = UART_MODE_TX_RX;
			huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
			huart3.Init.OverSampling = UART_OVERSAMPLING_16;
			if (HAL_UART_Init(&huart3) != HAL_OK)
			{
				Error_Handler();
			}
			/* USER CODE BEGIN USART3_Init 2 */

			/* USER CODE END USART3_Init 2 */

		}

		/**
		 * @brief USB_OTG_FS Initialization Function
		 * @param None
		 * @retval None
		 */
		static void MX_USB_OTG_FS_PCD_Init(void)
		{

			/* USER CODE BEGIN USB_OTG_FS_Init 0 */

			/* USER CODE END USB_OTG_FS_Init 0 */

			/* USER CODE BEGIN USB_OTG_FS_Init 1 */

			/* USER CODE END USB_OTG_FS_Init 1 */
			hpcd_USB_OTG_FS.Instance = USB_OTG_FS;
			hpcd_USB_OTG_FS.Init.dev_endpoints = 4;
			hpcd_USB_OTG_FS.Init.speed = PCD_SPEED_FULL;
			hpcd_USB_OTG_FS.Init.dma_enable = DISABLE;
			hpcd_USB_OTG_FS.Init.phy_itface = PCD_PHY_EMBEDDED;
			hpcd_USB_OTG_FS.Init.Sof_enable = ENABLE;
			hpcd_USB_OTG_FS.Init.low_power_enable = DISABLE;
			hpcd_USB_OTG_FS.Init.lpm_enable = DISABLE;
			hpcd_USB_OTG_FS.Init.vbus_sensing_enable = ENABLE;
			hpcd_USB_OTG_FS.Init.use_dedicated_ep1 = DISABLE;
			if (HAL_PCD_Init(&hpcd_USB_OTG_FS) != HAL_OK)
			{
				Error_Handler();
			}
			/* USER CODE BEGIN USB_OTG_FS_Init 2 */

			/* USER CODE END USB_OTG_FS_Init 2 */

		}

		/**
		 * @brief GPIO Initialization Function
		 * @param None
		 * @retval None
		 */
		static void MX_GPIO_Init(void)
		{
			GPIO_InitTypeDef GPIO_InitStruct = {0};

			/* GPIO Ports Clock Enable */
			__HAL_RCC_GPIOC_CLK_ENABLE();
			__HAL_RCC_GPIOH_CLK_ENABLE();
			__HAL_RCC_GPIOA_CLK_ENABLE();
			__HAL_RCC_GPIOB_CLK_ENABLE();
			__HAL_RCC_GPIOD_CLK_ENABLE();
			__HAL_RCC_GPIOG_CLK_ENABLE();

			/*Configure GPIO pin Output Level */
			HAL_GPIO_WritePin(GPIOB, LD1_Pin|LD3_Pin|LD2_Pin, GPIO_PIN_RESET);

			/*Configure GPIO pin Output Level */
			HAL_GPIO_WritePin(USB_PowerSwitchOn_GPIO_Port, USB_PowerSwitchOn_Pin, GPIO_PIN_RESET);

			/*Configure GPIO pin : USER_Btn_Pin */
			GPIO_InitStruct.Pin = USER_Btn_Pin;
			GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
			GPIO_InitStruct.Pull = GPIO_NOPULL;
			HAL_GPIO_Init(USER_Btn_GPIO_Port, &GPIO_InitStruct);

			/*Configure GPIO pins : LD1_Pin LD3_Pin LD2_Pin */
			GPIO_InitStruct.Pin = LD1_Pin|LD3_Pin|LD2_Pin;
			GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
			GPIO_InitStruct.Pull = GPIO_NOPULL;
			GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
			HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

			/*Configure GPIO pin : USB_PowerSwitchOn_Pin */
			GPIO_InitStruct.Pin = USB_PowerSwitchOn_Pin;
			GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
			GPIO_InitStruct.Pull = GPIO_NOPULL;
			GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
			HAL_GPIO_Init(USB_PowerSwitchOn_GPIO_Port, &GPIO_InitStruct);

			/*Configure GPIO pin : USB_OverCurrent_Pin */
			GPIO_InitStruct.Pin = USB_OverCurrent_Pin;
			GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
			GPIO_InitStruct.Pull = GPIO_NOPULL;
			HAL_GPIO_Init(USB_OverCurrent_GPIO_Port, &GPIO_InitStruct);

		}

		/* USER CODE BEGIN 4 */

		/* USER CODE END 4 */

		/**
		 * @brief  This function is executed in case of error occurrence.
		 * @retval None
		 */
		void Error_Handler(void)
		{
			/* USER CODE BEGIN Error_Handler_Debug */
			/* User can add his own implementation to report the HAL error return state */

			/* USER CODE END Error_Handler_Debug */
		}

#ifdef  USE_FULL_ASSERT
		/**
		 * @brief  Reports the name of the source file and the source line number
		 *         where the assert_param error has occurred.
		 * @param  file: pointer to the source file name
		 * @param  line: assert_param error line source number
		 * @retval None
		 */
		void assert_failed(uint8_t *file, uint32_t line)
		{
			/* USER CODE BEGIN 6 */
			/* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
			/* USER CODE END 6 */
		}
#endif /* USE_FULL_ASSERT */

		/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
