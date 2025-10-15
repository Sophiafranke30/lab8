/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <string.h>
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
UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */
uint8_t inicio=0;
uint8_t jugador1=1;
uint8_t jugador2=0;
char rxData;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
/* USER CODE BEGIN PFP */
void semaforo(void);
void Player1(uint8_t num);
void Player2(uint8_t num);
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
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */
char msg[] = "Presione 'S' para comenzar\n";
HAL_UART_Transmit(&huart2, (uint8_t*)msg, strlen(msg), HAL_MAX_DELAY);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	  if (!inicio){
	        HAL_UART_Receive(&huart2, (uint8_t*)&rxData, 1, HAL_MAX_DELAY);
	        if (rxData == 'S'){ //Cuando se empieza el conteo regresivo, los LEDs se apagan para "resetear" ambos jugadores.
	    		HAL_GPIO_WritePin(LED1P1_GPIO_Port, LED1P1_Pin, GPIO_PIN_RESET);
	    		HAL_GPIO_WritePin(LED2P1_GPIO_Port, LED2P1_Pin, GPIO_PIN_RESET);
	    		HAL_GPIO_WritePin(LED3P1_GPIO_Port, LED3P1_Pin, GPIO_PIN_RESET);
	    		HAL_GPIO_WritePin(LED4P1_GPIO_Port, LED4P1_Pin, GPIO_PIN_RESET);
	    		HAL_GPIO_WritePin(LED1P2_GPIO_Port, LED1P2_Pin, GPIO_PIN_RESET);
	    		HAL_GPIO_WritePin(LED2P2_GPIO_Port, LED2P2_Pin, GPIO_PIN_RESET);
	    		HAL_GPIO_WritePin(LED3P2_GPIO_Port, LED3P2_Pin, GPIO_PIN_RESET);
	    		HAL_GPIO_WritePin(LED4P2_GPIO_Port, LED4P2_Pin, GPIO_PIN_RESET);
	          semaforo();
	          inicio = 1;		//Indicador para que inicien los contadores de los jugadores	
	          jugador1 = 0;		//Indica contador 0 para el jugador 1 y 2 para que estén apagadas las LEDs
	          jugador2 = 0;
	          Player1(jugador1);	//Modifica las LEds para ambos jugadores
	          Player2(jugador2);
	        }

	  HAL_Delay(10);
	  }
	  if (inicio == 0){
	  		Player1(0);	//Si no se ha recibido señal los LEds permanecen apagados.
	  		Player2(0);
	  }
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
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  /* USER CODE BEGIN MX_GPIO_Init_1 */
  GPIO_InitStruct.Pin = GPIO_PIN_10;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
  /* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, LED2P1_Pin|LED1P1_Pin|LED4P2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, LEDR_Pin|LEDY_Pin|LEDG_Pin|LED3P2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, LED4P1_Pin|LED1P2_Pin|LED2P2_Pin|LED3P1_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : LED2P1_Pin LED1P1_Pin LED4P2_Pin */
  GPIO_InitStruct.Pin = LED2P1_Pin|LED1P1_Pin|LED4P2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : LEDR_Pin LEDY_Pin LEDG_Pin LED3P2_Pin */
  GPIO_InitStruct.Pin = LEDR_Pin|LEDY_Pin|LEDG_Pin|LED3P2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : LED4P1_Pin LED1P2_Pin LED2P2_Pin LED3P1_Pin */
  GPIO_InitStruct.Pin = LED4P1_Pin|LED1P2_Pin|LED2P2_Pin|LED3P1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : PB1_Pin */
  GPIO_InitStruct.Pin = PB1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(PB1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : PB2_Pin */
  GPIO_InitStruct.Pin = PB2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(PB2_GPIO_Port, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI9_5_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);

  HAL_NVIC_SetPriority(EXTI15_10_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);

  /* USER CODE BEGIN MX_GPIO_Init_2 */
  HAL_NVIC_SetPriority(EXTI15_10_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);
  /* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */
void semaforo(void){
	char msg1[] = "\n Inicializando Semaforo\n";
	char msg2[] = "3...\n";
	HAL_UART_Transmit(&huart2, (uint8_t*)msg1, strlen(msg1), HAL_MAX_DELAY);
	HAL_UART_Transmit(&huart2, (uint8_t*)msg2, strlen(msg2), HAL_MAX_DELAY);
	HAL_GPIO_WritePin(LEDR_GPIO_Port, LEDR_Pin, GPIO_PIN_SET); //Encender LED rojo
	HAL_Delay(1000);
	HAL_GPIO_WritePin(LEDR_GPIO_Port, LEDR_Pin, GPIO_PIN_RESET); //Apagar LED rojo

	char msg3[] = "2...\n";
	HAL_UART_Transmit(&huart2, (uint8_t*)msg3, strlen(msg3), HAL_MAX_DELAY);
	HAL_GPIO_WritePin(LEDY_GPIO_Port, LEDY_Pin, GPIO_PIN_SET); //Encender LED amarillo
	HAL_Delay(1000);
	HAL_GPIO_WritePin(LEDY_GPIO_Port, LEDY_Pin, GPIO_PIN_RESET); //Apagar LED amarillo

	char msg4[] = "1...\n";
	HAL_UART_Transmit(&huart2, (uint8_t*)msg4, strlen(msg4), HAL_MAX_DELAY);
	HAL_GPIO_WritePin(LEDG_GPIO_Port, LEDG_Pin, GPIO_PIN_SET); //Encender LED verde
	HAL_Delay(1000);
	HAL_GPIO_WritePin(LEDG_GPIO_Port, LEDG_Pin, GPIO_PIN_RESET); //Apagar LED verde

	char msg5[] = "INICIA!\n"; //Comuniación serial para verificar que vana los pasos como deberían
	HAL_UART_Transmit(&huart2, (uint8_t*)msg5, strlen(msg5), HAL_MAX_DELAY);
}

void Player1(uint8_t num){

	switch(num){
	case 0:
		HAL_GPIO_WritePin(LED1P1_GPIO_Port, LED1P1_Pin, GPIO_PIN_RESET); //Todos los LEDs apagados
		HAL_GPIO_WritePin(LED2P1_GPIO_Port, LED2P1_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(LED3P1_GPIO_Port, LED3P1_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(LED4P1_GPIO_Port, LED4P1_Pin, GPIO_PIN_RESET);
		break;
	case 1:
		HAL_GPIO_WritePin(LED1P1_GPIO_Port, LED1P1_Pin, GPIO_PIN_SET); //Se van encendiendo los LEDs 1 a 1
		break;
	case 2:
		HAL_GPIO_WritePin(LED2P1_GPIO_Port, LED2P1_Pin, GPIO_PIN_SET);
		break;
	case 3:
		HAL_GPIO_WritePin(LED3P1_GPIO_Port, LED3P1_Pin, GPIO_PIN_SET);
		break;
	case 4:
		HAL_GPIO_WritePin(LED4P1_GPIO_Port, LED4P1_Pin, GPIO_PIN_SET);
		HAL_UART_Transmit(&huart2, (uint8_t*)"Jugador 1 GANO!\n", 17, HAL_MAX_DELAY); //Comuniación serial para verificar que vana los pasos como deberían.
		inicio = 0;  //Cuando termina apaga los LEDs y reinicia los contadores.
		jugador1 = 0;
		jugador2 = 0;
		break;
	}
}

void Player2(uint8_t num){  //Igual que la función para el jugador 1
    switch(num) {
    	case 0:
    		HAL_GPIO_WritePin(LED1P2_GPIO_Port, LED1P2_Pin, GPIO_PIN_RESET);
    		HAL_GPIO_WritePin(LED2P2_GPIO_Port, LED2P2_Pin, GPIO_PIN_RESET);
    		HAL_GPIO_WritePin(LED3P2_GPIO_Port, LED3P2_Pin, GPIO_PIN_RESET);
    		HAL_GPIO_WritePin(LED4P2_GPIO_Port, LED4P2_Pin, GPIO_PIN_RESET);
    		break;
        case 1:
        	HAL_GPIO_WritePin(LED1P2_GPIO_Port, LED1P2_Pin, GPIO_PIN_SET);
        	break;
        case 2:
        	HAL_GPIO_WritePin(LED2P2_GPIO_Port, LED2P2_Pin, GPIO_PIN_SET);
        	break;
        case 3:
        	HAL_GPIO_WritePin(LED3P2_GPIO_Port, LED3P2_Pin, GPIO_PIN_SET);
        	break;
        case 4:
            HAL_GPIO_WritePin(LED4P2_GPIO_Port, LED4P2_Pin, GPIO_PIN_SET);
            HAL_UART_Transmit(&huart2, (uint8_t*)"Jugador 2 GANO!\n", 17, HAL_MAX_DELAY);
            inicio = 0;
            jugador1 = 0;
            jugador2 = 0;
            break;
    }
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){ //Callback para que los botones funcionen como interruptores.
    static uint32_t last_interrupt_time = 0;
    uint32_t current_time = HAL_GetTick();

    // Debounce: ignorar interrupciones muy cercanas en el tiempo
    if (current_time - last_interrupt_time > 250) {
        if (HAL_GPIO_ReadPin(PB1_GPIO_Port, PB1_Pin) == GPIO_PIN_RESET && inicio == 1){ // Solo procesar si el juego ha comenzado
        	jugador1 ++;
            char msg7[]= "Jugador 1 +1\n";
             HAL_UART_Transmit(&huart2, (uint8_t*)msg7, strlen(msg7), HAL_MAX_DELAY);
             if (jugador1 > 4){
                jugador1 = 4; //Limita a que no se hagan más de 4 pts por jugador.
                jugador2 = 0;
                }
             Player1(jugador1);
            }

        if (HAL_GPIO_ReadPin(PB2_GPIO_Port, PB2_Pin) == GPIO_PIN_RESET && inicio == 1){
        	jugador2 ++;
        	char msg8[]= "Jugador 2 +1\n";
        	HAL_UART_Transmit(&huart2, (uint8_t*)msg8, strlen(msg8), HAL_MAX_DELAY);
        	if (jugador2 > 4){
        		jugador2 = 4;
        		jugador1 = 0;
        	   }
      	   Player2(jugador2);
        }

        }
            last_interrupt_time = current_time; //Debounce para antibloqueo de los botones y antirrebote de los mismsos.
        }

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}
#ifdef USE_FULL_ASSERT
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
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
