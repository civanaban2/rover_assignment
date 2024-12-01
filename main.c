#include "main.h"
#include <string.h>

UART_HandleTypeDef huart1;

//GPIO pins initialization
void GPIO_Init(void) {
	__HAL_RCC_GPIOA_CLK_ENABLE(); // GPIOA clock enable
  
	GPIO_InitTypeDef GPIO_InitStruct = {0};

	//PA5 and PA6 pins for output
  	GPIO_InitStruct.Pin = GPIO_PIN_5 | GPIO_PIN_6;
  	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
  	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}

//UART initialization
void UART_Init(void) {
  	__HAL_RCC_USART1_CLK_ENABLE(); // USART1 clock enable
  
  	//Configurations for UART
  	huart1.Instance = USART1;
  	huart1.Init.BaudRate = 9600;
  	huart1.Init.WordLength = UART_WORDLENGTH_8B;
  	huart1.Init.StopBits = UART_STOPBITS_1;
  	huart1.Init.Parity = UART_PARITY_NONE;
  	huart1.Init.Mode = UART_MODE_RX | UART_MODE_TX;
  	huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  	huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  	HAL_UART_Init(&huart1); // Initialize USART1
}

//Handling UART Data
void Process_UART_Data(uint8_t *data) {
  	
	// Process data for PA5 pin
  	if (data[0] == '0') {
    	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET); // Set PA5 LOW
  	}
  	else if (data[0] == '1') {
    	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET); // Set PA5 HIGH
  	}
  	else if (data[0] == '2') {
    	HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5); // Toggle PA5
  	}

  	// Process data for PA6 pin
 	if (data[1] == '0') {
    	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_RESET); // Set PA6 LOW
  	}
  	else if (data[1] == '1') {
    	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_SET); // Set PA6 HIGH
  	}
  	else if (data[1] == '2') {
    	HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_6); // Toggle PA6
  	}
}

int main(void) {
	// Initialize the HAL Library
	HAL_Init();

	// Initialize GPIO and UART
	GPIO_Init();
	UART_Init();

	// Array for receive data
	uint8_t input[2] = {0};

	// Endless loop for continuous data receive
	while (1) {
		// Receive data via UART
		if (HAL_UART_Receive(&huart1, input, 2, 1000) == HAL_OK) {
		// Process the received data
    		Process_UART_Data(input);
    	}
  	}
}