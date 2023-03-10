/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
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

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include<stdbool.h>

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
TIM_HandleTypeDef htim2;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM2_Init(void);
/* USER CODE BEGIN PFP */
void Tone_start(){
	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_2);

}
static void Tone_stop(){


   HAL_TIM_PWM_Stop(&htim2, TIM_CHANNEL_2);

}
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM2_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

uint8_t button=0;
bool state = false;

bool Button_pressed()
{

	if( HAL_GPIO_ReadPin(Button_GPIO_Port, Button_Pin)==1 &&state==false)
	{
		button ++;
		state= true;
	}
	else if( HAL_GPIO_ReadPin(Button_GPIO_Port, Button_Pin) == 0 && state == true)
		{
			state = false;
		}

		if(button%2 == 0)
			return true;
		else
			return false;
}

enum notes {
    C4 = 261, // (261 Hz)
    D4 = 293, // (293 Hz)
    E4 = 329, // (329 Hz)
    F4 = 349, // (349 Hz)
    G4 = 392, // (392 Hz)
    A4 = 440, // (440 Hz)
    B4 = 493, // (493 Hz)
    C5 = 523  // (523 Hz)
  };
enum notes A[] = {G4,G4,A4,A4,G4,G4,E4,G4,G4,E4,E4,D4,
                    G4,G4,A4,A4,G4,G4,E4,G4,E4,D4,E4,C4};

enum notes B[]={C4,C4,C4,C4,D4,D4,D4,E4,E4,E4,E4,F4,F4,F4,F4,G4,G4,F4,F4,F4,F4,F4,F4,F4,F4,F4,F4,F4,F4,G4};
static void freq_set(int x){
    int freq = 32000000/x;
    __HAL_TIM_SET_AUTORELOAD(&htim2 , freq);
    __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2, freq/2);
    __HAL_TIM_SET_COUNTER(&htim2, 0);
}

static void tone_stop(){
  HAL_TIM_PWM_Stop(&htim2, TIM_CHANNEL_2);
}

static void tone_start(){
  HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_2);
}
static void Red_LED(){

HAL_GPIO_WritePin(GREEN_LED_GPIO_Port, GREEN_LED_Pin, GPIO_PIN_RESET);
HAL_GPIO_WritePin(RED_LED_GPIO_Port, RED_LED_Pin, GPIO_PIN_SET);

}
static void Green_LED(){

HAL_GPIO_WritePin(RED_LED_GPIO_Port, RED_LED_Pin, GPIO_PIN_RESET);
HAL_GPIO_WritePin(GREEN_LED_GPIO_Port, GREEN_LED_Pin, GPIO_PIN_SET);

}
int song_A()
   {
   	 //----------melody 1----------------------------------------

     while(1)   // wait if first melody finished without pressing the button
     {
     	if(!Button_pressed()) // move to the next melody if button pressed
     		break;
     }
     button++;

 	  for (int i = 0 ; i < sizeof(A)/sizeof(enum notes) ; i++) {
 		 if(Button_pressed())
 		 	  {
 			 	freq_set(A[i]);
 	 	        HAL_Delay(500);
 	 	        /*---------LED----------------------*/
 	 	        if ((i%2)==1){
 	 	        	Red_LED();
 	 	        }
 	 	        else{
 	 	        	Green_LED();
 	 	        }

 	 	        /* �? Note 소리 내고 10 Millisecond �?�어주기 */
 	 	        tone_stop() ;
 	 	      HAL_Delay(10);
 	 	        tone_start() ;

 	 	       if(i == (sizeof(A)/sizeof(enum notes)-1))
 	 	        		{
 	 	        	i=0;
 	 	        		}

 		 	  }
 		 else     // if button pressed move to the next melody
 			  {
 			// HAL_Delay(2000);
 				break;
 		  	  }

 	 	      }
 	 //----------melody 2----------------------------------------

 	    while(1)   // wait if first melody finished without pressing the button
 	     {
 	     	if(!Button_pressed()) // move to the next melody if button pressed
 	     		break;
 	     }
 	     button++;
 	 	  for (int i = 0 ; i < sizeof(B)/sizeof(enum notes) ; i++) {
 	 		 if(Button_pressed())

 	 		{
 	 			freq_set(B[i]);
 	 			 HAL_Delay(500);
 	 	  /*---------LED----------------------*/
 	 			      if ((i%2)==1){
 	 			 	    	Red_LED();
 	 			 	 	  }
 	 			 	  else{
 	 			 	 	    Green_LED();
 	 			 	 	 }
 	 	 	        /* �? Note 소리 내고 10 Millisecond �?�어주기 */
 	 	 	        tone_stop() ;
 	 	 	        HAL_Delay(10);
 	 	 	        tone_start() ;


 	 	 	       if(i == (sizeof(B)/sizeof(enum notes)-1))
 	 	 	        		{i=0;}


 	 		 }
 	 		 else     // if button pressed move to the next melody
 	 		{break; }
 	 	  	  	  	  	  	  	  	  	  	  	  	  	  	  	  	  }
//----------melody 3----------------------------------------

 	   while(1)   // wait if first melody finished without pressing the button
 	  {
 		 if(!Button_pressed()) // move to the next melody if button pressed
 	 	 break;
 	   }
 	  button++;

 	  for (int i = 0 ; i < sizeof(B)/sizeof(enum notes) ; i++) {
 	  if(Button_pressed())

 	 	{
 	 	freq_set(B[i]);
 	 	 HAL_Delay(100);
 	 	  /*---------LED----------------------*/
 	 	 	 			      if ((i%2)==1){
 	 	 	 			 	    	Red_LED();
 	 	 	 			 	 	  }
 	 	 	 			 	  else{
 	 	 	 			 	 	    Green_LED();
 	 	 	 			 	 	 }
 	 	/* �? Note 소리 내고 10 Millisecond �?�어주기 */
 	 	 tone_stop() ;
 	 	  HAL_Delay(10);
 	 	 tone_start() ;


 	 	  if(i == (sizeof(B)/sizeof(enum notes)-1))
 	 	 	{i=0;}

 	 	  }
 	 	 		 else     // if button pressed move to the next melody
 	 	 		{break; }
 	 	 	  	  	  	  	  	  	  	  	  	  	  	  	  	  	  	  } 	  /* �?�악 �??나면 5초 후 반복 */
 	      tone_stop() ;
 	      HAL_Delay(500);
 	      tone_start() ;

   }

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
  MX_TIM2_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

song_A();
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

  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_MSI;
  RCC_OscInitStruct.MSIState = RCC_MSI_ON;
  RCC_OscInitStruct.MSICalibrationValue = 0;
  RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_6;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_MSI;
  RCC_OscInitStruct.PLL.PLLM = 1;
  RCC_OscInitStruct.PLL.PLLN = 8;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV7;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
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
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure the main internal regulator output voltage 
  */
  if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 0;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 122310;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_PWM_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */
  HAL_TIM_MspPostInit(&htim2);

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
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, RED_LED_Pin|GREEN_LED_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : Button_Pin */
  GPIO_InitStruct.Pin = Button_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(Button_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : RED_LED_Pin GREEN_LED_Pin */
  GPIO_InitStruct.Pin = RED_LED_Pin|GREEN_LED_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

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
