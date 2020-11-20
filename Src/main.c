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
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <ctype.h>
#include <string.h>



#include "gp4_game.h"
#include "leds_control.h"
#include "application.h"
#include "__debug.h"
#include "display.h"
#include "mydebug.h"


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

I2C_HandleTypeDef hi2c1;

UART_HandleTypeDef huart7;
UART_HandleTypeDef huart3;

PCD_HandleTypeDef hpcd_USB_OTG_FS;

/* Definitions for defaultTask */
osThreadId_t defaultTaskHandle;
const osThreadAttr_t defaultTask_attributes = {
		.name = "defaultTask",
		.priority = (osPriority_t) osPriorityNormal,
		.stack_size = 128 * 4
};
/* Definitions for myTask01 */
osThreadId_t myTask01Handle;
const osThreadAttr_t myTask01_attributes = {
		.name = "myTask01",
		.priority = (osPriority_t) osPriorityNormal,
		.stack_size = 128 * 4
};
/* Definitions for myTask02 */
osThreadId_t myTask02Handle;
const osThreadAttr_t myTask02_attributes = {
		.name = "myTask02",
		.priority = (osPriority_t) osPriorityNormal,
		.stack_size = 128 * 4
};
/* Definitions for myTask03 */
osThreadId_t myTask03Handle;
const osThreadAttr_t myTask03_attributes = {
		.name = "myTask03",
		.priority = (osPriority_t) osPriorityNormal,
		.stack_size = 128 * 4
};
/* Definitions for readToApp */
osMessageQueueId_t readToAppHandle;
const osMessageQueueAttr_t readToApp_attributes = {
		.name = "readToApp"
};
/* Definitions for appToDisplay */
osMessageQueueId_t appToDisplayHandle;
const osMessageQueueAttr_t appToDisplay_attributes = {
		.name = "appToDisplay"
};
/* Definitions for timerAutoPlayShort */
osTimerId_t timerAutoPlayShortHandle;
const osTimerAttr_t timerAutoPlayShort_attributes = {
		.name = "timerAutoPlayShort"
};
/* Definitions for timerAutoPlayLong */
osTimerId_t timerAutoPlayLongHandle;
const osTimerAttr_t timerAutoPlayLong_attributes = {
		.name = "timerAutoPlayLong"
};
/* Definitions for semDisplay */
osSemaphoreId_t semDisplayHandle;
const osSemaphoreAttr_t semDisplay_attributes = {
		.name = "semDisplay"
};
/* Definitions for semRead */
osSemaphoreId_t semReadHandle;
const osSemaphoreAttr_t semRead_attributes = {
		.name = "semRead"
};
/* USER CODE BEGIN PV */

/* Definitions for UARTReception */
osMessageQueueId_t UARTReceptionHandle;
const osMessageQueueAttr_t UARTReception_attributes = {
		.name = "UARTReception"
};
/* Definitions for UARTSend */
osMessageQueueId_t UARTSendHandle;
const osMessageQueueAttr_t UARTSend_attributes = {
		.name = "UARTSend"
};

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_ETH_Init(void);
static void MX_USART3_UART_Init(void);
static void MX_USB_OTG_FS_PCD_Init(void);
static void MX_I2C1_Init(void);
static void MX_UART7_Init(void);
void StartDefaultTask(void *argument);
void StartTask01(void *argument);
void StartTask02(void *argument);
void StartTask03(void *argument);
void Callback01(void *argument);
void Callback02(void *argument);

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
	//	MX_ETH_Init();
	MX_USART3_UART_Init();
	//	MX_USB_OTG_FS_PCD_Init();
	MX_I2C1_Init();
	MX_UART7_Init();
	/* USER CODE BEGIN 2 */


	/* USER CODE END 2 */

	/* Init scheduler */
	osKernelInitialize();

	/* USER CODE BEGIN RTOS_MUTEX */
	/* add mutexes, ... */
	/* USER CODE END RTOS_MUTEX */

	/* Create the semaphores(s) */
	/* creation of semDisplay */
	semDisplayHandle = osSemaphoreNew(1, 1, &semDisplay_attributes);

	/* creation of semRead */
	semReadHandle = osSemaphoreNew(1, 1, &semRead_attributes);

	/* USER CODE BEGIN RTOS_SEMAPHORES */
	/* add semaphores, ... */
	/* USER CODE END RTOS_SEMAPHORES */

	/* Create the timer(s) */
	/* creation of timerAutoPlayShort */
	timerAutoPlayShortHandle = osTimerNew(Callback01, osTimerOnce, NULL, &timerAutoPlayShort_attributes);

	/* creation of timerAutoPlayLong */
	timerAutoPlayLongHandle = osTimerNew(Callback02, osTimerOnce, NULL, &timerAutoPlayLong_attributes);

	/* USER CODE BEGIN RTOS_TIMERS */
	/* start timers, add new ones, ... */
	/* USER CODE END RTOS_TIMERS */

	/* Create the queue(s) */
	/* creation of readToApp */
	readToAppHandle = osMessageQueueNew (16, sizeof(data_msg), &readToApp_attributes);

	/* creation of appToDisplay */
	appToDisplayHandle = osMessageQueueNew (16, sizeof(data_msg), &appToDisplay_attributes);

	/* USER CODE BEGIN RTOS_QUEUES */
	/* add queues, ... */
	/* USER CODE END RTOS_QUEUES */

	/* Create the thread(s) */
	/* creation of defaultTask */
	defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);

	/* creation of myTask01 */
	myTask01Handle = osThreadNew(StartTask01, NULL, &myTask01_attributes);

	/* creation of myTask02 */
	myTask02Handle = osThreadNew(StartTask02, NULL, &myTask02_attributes);

	/* creation of myTask03 */
	myTask03Handle = osThreadNew(StartTask03, NULL, &myTask03_attributes);

	/* USER CODE BEGIN RTOS_THREADS */

	/* creation of uart queue */


	UARTReceptionHandle = osMessageQueueNew (100, 5, &UARTReception_attributes);

	UARTSendHandle = osMessageQueueNew (100, 10, &UARTSend_attributes);
	/* add threads, ... */
	/* USER CODE END RTOS_THREADS */

	/* Start scheduler */
	osKernelStart();

	/* We should never get here as control is now taken by the scheduler */
	/* Infinite loop */
	/* USER CODE BEGIN WHILE */
	/* USER CODE END WHILE */

	/* USER CODE BEGIN 3 */
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
 * @brief I2C1 Initialization Function
 * @param None
 * @retval None
 */
static void MX_I2C1_Init(void)
{

	/* USER CODE BEGIN I2C1_Init 0 */


	/* USER CODE END I2C1_Init 0 */

	/* USER CODE BEGIN I2C1_Init 1 */

	/* USER CODE END I2C1_Init 1 */
	hi2c1.Instance = I2C1;
	hi2c1.Init.ClockSpeed = 100000;
	hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
	hi2c1.Init.OwnAddress1 = 0;
	hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
	hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
	hi2c1.Init.OwnAddress2 = 0;
	hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
	hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
	if (HAL_I2C_Init(&hi2c1) != HAL_OK)
	{
		Error_Handler();
	}
	/** Configure Analogue filter
	 */
	if (HAL_I2CEx_ConfigAnalogFilter(&hi2c1, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
	{
		Error_Handler();
	}
	/** Configure Digital filter
	 */
	if (HAL_I2CEx_ConfigDigitalFilter(&hi2c1, 0) != HAL_OK)
	{
		Error_Handler();
	}
	/* USER CODE BEGIN I2C1_Init 2 */

	/* USER CODE END I2C1_Init 2 */

}

/**
 * @brief UART7 Initialization Function
 * @param None
 * @retval None
 */
static void MX_UART7_Init(void)
{

	/* USER CODE BEGIN UART7_Init 0 */

	/* USER CODE END UART7_Init 0 */

	/* USER CODE BEGIN UART7_Init 1 */

	/* USER CODE END UART7_Init 1 */
	huart7.Instance = UART7;
	huart7.Init.BaudRate = 115200;
	huart7.Init.WordLength = UART_WORDLENGTH_8B;
	huart7.Init.StopBits = UART_STOPBITS_1;
	huart7.Init.Parity = UART_PARITY_NONE;
	huart7.Init.Mode = UART_MODE_TX_RX;
	huart7.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart7.Init.OverSampling = UART_OVERSAMPLING_16;
	if (HAL_UART_Init(&huart7) != HAL_OK)
	{
		Error_Handler();
	}
	/* USER CODE BEGIN UART7_Init 2 */

	/* USER CODE END UART7_Init 2 */

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
	__HAL_RCC_GPIOE_CLK_ENABLE();
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

//void extract_rtc_data(){
//	HAL_I2C_Master_Transmit(&hi2c1, addr, (uint8_t*)buffer, size, timeout);
//
//}


/* USER CODE END 4 */

/* USER CODE BEGIN Header_StartDefaultTask */
/**
 * @brief  Function implementing the defaultTask thread.
 * @param  argument: Not used
 * @retval None
 */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void *argument)
{
	/* USER CODE BEGIN 5 */
	/* Infinite loop */

	//-------------- display debug msg--------------------------------------
//	int size_of_debug_frame = 31;
//	char debug_message[] = "dEngage le jeu que je le gagne\n";
//	char debug_frame[size_of_debug_frame];
//	//int change_count = 0;
//	memcpy((uint8_t*)debug_frame, debug_message, size_of_debug_frame);
//	HAL_UART_Transmit(&huart7, (uint8_t*)debug_message, size_of_debug_frame, 10);


	//----------------------------------------------------------------------


	//-------------- recup data from RTC--------------------------------------
//	uint8_t buffer[100] = { 0 };
//	uint8_t p_registre = 0x00;
//	uint16_t addr = 0xD0;
//	//uint8_t *pData;
//	uint16_t size = 8;
//	uint32_t timeout = 1000;
//	HAL_StatusTypeDef status;
//	uint8_t clock_init = 0x00;
//	HAL_I2C_Mem_Write(&hi2c1,addr, 0x00, 1, &clock_init, 1, 100);
	//----------------------------------------------------------------------

	//	HAL_I2C_Master_Transmit(&hi2c1, addr, &p_registre, 1, timeout);
	//	status = HAL_I2C_Master_Receive(&hi2c1, addr, &buffer, size, timeout);
	//	osDelay(2);

	uint16_t addr = 0xD0;
//	uint8_t minute_init = 37;
//	uint8_t hour_init = 17;
//	uint8_t date_init = 22;
//	uint8_t month_init = 17;
//	uint8_t year_init = 32;


//	HAL_I2C_Mem_Write(&hi2c1,addr, 0x01, 1, &minute_init, 1, 100);
//	HAL_I2C_Mem_Write(&hi2c1,addr, 0x02, 1, &hour_init, 1, 100);
//	HAL_I2C_Mem_Write(&hi2c1,addr, 0x04, 1, &date_init, 1, 100);
//	HAL_I2C_Mem_Write(&hi2c1,addr, 0x05, 1, &month_init, 1, 100);
//	HAL_I2C_Mem_Write(&hi2c1,addr, 0x06, 1, &year_init, 1, 100);



	char total_init [6];
	total_init[0] = 00;
	total_init[1]= 18;
	total_init[2] = 00;
	total_init[3] = 22;
	total_init[4] = 17;
	total_init[5] = 32;
	HAL_I2C_Mem_Write(&hi2c1,addr, 0x01, 1, (uint8_t*)total_init, 6, 100);


	void display_debug_msg(char debug_msg[], int size_of_debug_msg){
		//char debug_frame[size_of_debug_msg];
		//int change_count = 0;

		HAL_UART_Transmit(&huart3, (uint8_t*)debug_msg, size_of_debug_msg, 10);
	}


	void extract_complete_date(){
		//-------------- recup data from RTC--------------------------------------
		uint8_t buffer[100] = { 0 };
		uint8_t p_registre = 0x00;
		uint16_t addr = 0xD0;
		//uint8_t *pData;
		uint16_t size = 8;
		uint32_t timeout = 1000;
		HAL_StatusTypeDef status;
		//uint8_t clock_init = 0x00;
		//HAL_I2C_Mem_Write(&hi2c1,addr, 0x00, 1, &clock_init, 1, 100);

		HAL_I2C_Master_Transmit(&hi2c1, addr, &p_registre, 1, timeout);
		status = HAL_I2C_Master_Receive(&hi2c1, addr, (uint8_t*) buffer, size, timeout);
		osDelay(2);


		uint8_t sec_diz;
		uint8_t sec_unit;
		uint8_t min_diz;
		uint8_t min_unit;
		uint8_t hour_diz;
		uint8_t hour_unit;
		uint8_t date_diz;
		uint8_t date_unit;
		uint8_t month_diz;
		uint8_t month_unit;
		uint8_t year_diz;
		uint8_t year_unit;

		sec_diz = (buffer[0] & 0x70)>>4;
		sec_unit = (buffer[0] & 0x0F);
		min_diz = (buffer[1] & 0x70)>>4;
		min_unit = (buffer[1] & 0x0F);
		hour_diz = (buffer[2] & 0x10)>>4;
		hour_unit = (buffer[2] & 0x0F);
		date_diz = (buffer[4] & 0x30)>>4;
		date_unit = (buffer[4] & 0x0F);
		month_diz = (buffer[5] & 0x10)>>4;
		month_unit = (buffer[5] & 0x0F);
		year_diz = (buffer[6] & 0xF0)>>4;
		year_unit = (buffer[6] & 0x0F);

		int size_of_raw_date = 21;
		char raw_date [size_of_raw_date];

		raw_date[0] = 'd';
		raw_date[1] = date_diz + 48;
		raw_date[2] = date_unit + 48;
		raw_date[3] = ':';
		raw_date[4] = month_diz + 48;
		raw_date[5] = month_unit + 48;
		raw_date[6] = ':';
		raw_date[7] = year_diz + 48;
		raw_date[8] = year_unit + 48;
		raw_date[9] = ' ';
		raw_date[10] = '-';
		raw_date[11] = ' ';
		raw_date[12] = hour_diz + 48;
		raw_date[13] = hour_unit + 48;
		raw_date[14] = ':';
		raw_date[15] = min_diz + 48;
		raw_date[16] = min_unit + 48;
		raw_date[17] = ':';
		raw_date[18] = sec_diz + 48;
		raw_date[19] = sec_unit + 48;
		raw_date[20] = '\n';

		display_debug_msg(raw_date, size_of_raw_date);

	}
	extract_complete_date();
	unsigned char UARTmessageToSend[SIZE_OF_LED_COMMAND_BUFFER];
	unsigned char UARTmessageReceived[SIZE_OF_PLAYER_COMMAND_BUFFER];
	for(;;)
	{
		if (osMessageQueueGetCount(UARTSendHandle)){
			if(osMessageQueueGet(UARTSendHandle, UARTmessageToSend, 0, 10)==osOK){
				HAL_UART_Transmit(&huart7, UARTmessageToSend, SIZE_OF_LED_COMMAND_BUFFER, 10);
				osDelay(10);
			}
		}
		if(HAL_UART_Receive(&huart7, UARTmessageReceived,SIZE_OF_PLAYER_COMMAND_BUFFER, 10)==HAL_OK){
			osMessageQueuePut(UARTReceptionHandle, UARTmessageReceived, 1, 10);
		}




		//----------------Modification d'un tableau de charactere et affichage dans la fenetre de débug du simu----------
		//		int size_of_debug_frame = 31;
		//		char debug_message[] = "dEngage le jeu que je le gagne\n";
		//		char debug_frame[size_of_debug_frame];
		//		//int change_count = 0;
		//		memcpy((uint8_t*)debug_frame, debug_message, size_of_debug_frame);
		//		HAL_UART_Transmit(&huart7, (uint8_t*)debug_message, size_of_debug_frame, 10);
		//
		//		if(HAL_GPIO_ReadPin(USER_Btn_GPIO_Port, USER_Btn_Pin)){
		//			if(change_count == 0)
		//			{
		//				debug_frame_to_upper(truc, size_of_debug_frame);
		//				HAL_UART_Transmit(&huart7, (uint8_t*)truc, size_of_debug_frame, 10);
		//				change_count = 1;
		//			}
		//			else if(change_count == 1)
		//			{
		//				debug_frame_to_lower(truc, size_of_debug_frame);
		//				HAL_UART_Transmit(&huart7, (uint8_t*)truc, size_of_debug_frame, 10);
		//				change_count = 2;
		//			}
		//			else if(change_count == 2)
		//			{
		//				debug_frame_reverse(truc, size_of_debug_frame);
		//				HAL_UART_Transmit(&huart7, (uint8_t*)truc, size_of_debug_frame, 10);
		//				debug_frame_reverse(truc, size_of_debug_frame);
		//				change_count = 0;
		//			}
		//
		//		}
	}
	/* USER CODE END 5 */
}

/* USER CODE BEGIN Header_StartTask01 */
/**
 * @brief Function implementing the myTask01 thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_StartTask01 */
void StartTask01(void *argument)
{
	/* USER CODE BEGIN StartTask01 */


	debug_pr_fn(1,"read()entrée thread read\n");
	char recept_tab[5]={0};
	data_msg request;

	/* Infinite loop */
	for(;;)
	{
		//osDelay(1);
		if (readbutton(recept_tab, 5) == LCRC_OK) {
			debug_pr_fn(1,"read()input = (%d %d %d %d)\n", recept_tab[0], recept_tab[1], recept_tab[2], recept_tab[3]);
			if (recept_tab[3] == 100) {
				request.type = MSG_PLAYER;

				//if (recept_tab[1] == 49) {
				if (recept_tab[1] == '1') {
					request.params.player.player = PLAYER_1;
				}
				//if (recept_tab[1] == 50) {
				else if (recept_tab[1] == '2') {
					request.params.player.player = PLAYER_2;
				}
				else if (recept_tab[1] == '3') {
					int8_t player = get_active_player();
					if (player == NO_PLAYER){
						player = PLAYER_1;
					}
					request.params.player.player = player;
				}
				//if (recept_tab[2] == 117) { //vers le haut
				if (recept_tab[2] == 'u') { //vers le haut
					debug_pr_fn(2,"read_button():condition \"haut\"\n");
					request.params.player.direction = UP;
				}
				//if (recept_tab[2] == 114 ) {	// vers le droite
				else if (recept_tab[2] == 'r' ) {	// vers le droite
					debug_pr_fn(2,"read_button():condition \"droite\" \n");
					request.params.player.direction = RIGHT;
				}
				//if (recept_tab[2] == 100 ) { //vers le bas
				else if (recept_tab[2] == 'd') { //vers le bas
					debug_pr_fn(2,"read_button():condition \"bas\"\n");
					request.params.player.direction = DOWN;
				}
				//if (recept_tab[2] == 108 ) { //vers le gauche
				else if (recept_tab[2] == 'l' ) { //vers le gauche
					debug_pr_fn(2,"read_button():condition \"gauche\"\n");
					request.params.player.direction = LEFT;
				}
				debug_pr_fn(1,"read() send to queue = OK\n");
				SendMessage(LIST_READ, &request, sizeof(struct data_msg));
			}
		}
	}
}



/* USER CODE END StartTask01 */


/* USER CODE BEGIN Header_StartTask02 */
/**
 * @brief Function implementing the myTask02 thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_StartTask02 */
void StartTask02(void *argument)
{
	/* USER CODE BEGIN StartTask02 */
	/* Infinite loop */
	for(;;)
	{
		applicationV2();
	}
	/* USER CODE END StartTask02 */
}

/* USER CODE BEGIN Header_StartTask03 */
/**
 * @brief Function implementing the myTask03 thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_StartTask03 */
void StartTask03(void *argument)
{
	/* USER CODE BEGIN StartTask03 */
	/* Infinite loop */
	for(;;)
	{
		display();
	}
	/* USER CODE END StartTask03 */
}

/* Callback01 function */
void Callback01(void *argument)
{
	/* USER CODE BEGIN Callback01 */

	/* USER CODE END Callback01 */
}

/* Callback02 function */
void Callback02(void *argument)
{
	/* USER CODE BEGIN Callback02 */

	/* USER CODE END Callback02 */
}

/**
 * @brief  Period elapsed callback in non blocking mode
 * @note   This function is called  when TIM1 interrupt took place, inside
 * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
 * a global variable "uwTick" used as application time base.
 * @param  htim : TIM handle
 * @retval None
 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	/* USER CODE BEGIN Callback 0 */

	/* USER CODE END Callback 0 */
	if (htim->Instance == TIM1) {
		HAL_IncTick();
	}
	/* USER CODE BEGIN Callback 1 */

	/* USER CODE END Callback 1 */
}

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
