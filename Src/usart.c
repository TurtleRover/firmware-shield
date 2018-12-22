/**
 ******************************************************************************
 * File Name          : USART.c
 * Description        : This file provides code for the configuration
 *                      of the USART instances.
 ******************************************************************************
 ** This notice applies to any and all portions of this file
 * that are not between comment pairs USER CODE BEGIN and
 * USER CODE END. Other portions of this file, whether
 * inserted by the user or by software development tools
 * are owned by their respective copyright owners.
 *
 * COPYRIGHT(c) 2018 STMicroelectronics
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *   1. Redistributions of source code must retain the above copyright notice,
 *      this list of conditions and the following disclaimer.
 *   2. Redistributions in binary form must reproduce the above copyright notice,
 *      this list of conditions and the following disclaimer in the documentation
 *      and/or other materials provided with the distribution.
 *   3. Neither the name of STMicroelectronics nor the names of its contributors
 *      may be used to endorse or promote products derived from this software
 *      without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "usart.h"
#include "gpio.h"
#include "dma.h"

/* USER CODE BEGIN 0 */
DMA_HandleTypeDef hdma_usart1_rx;
DMA_HandleTypeDef hdma_usart1_tx;

extern volatile uint16_t Battery_level;

volatile bool maniUseDiff;
/* USER CODE END 0 */

UART_HandleTypeDef huart1;
DMA_HandleTypeDef hdma_usart1_rx;
DMA_HandleTypeDef hdma_usart1_tx;

/* USART1 init function */

void MX_USART1_UART_Init(void)
{

	huart1.Instance = USART1;
	huart1.Init.BaudRate = 115200;
	huart1.Init.WordLength = UART_WORDLENGTH_8B;
	huart1.Init.StopBits = UART_STOPBITS_1;
	huart1.Init.Parity = UART_PARITY_NONE;
	huart1.Init.Mode = UART_MODE_TX_RX;
	huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart1.Init.OverSampling = UART_OVERSAMPLING_16;
	huart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
	huart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
	if (HAL_UART_Init(&huart1) != HAL_OK)
	{
		_Error_Handler(__FILE__, __LINE__);
	}

}

void HAL_UART_MspInit(UART_HandleTypeDef* uartHandle)
{

	GPIO_InitTypeDef GPIO_InitStruct;
	if (uartHandle->Instance == USART1)
	{
		/* USER CODE BEGIN USART1_MspInit 0 */

		/* USER CODE END USART1_MspInit 0 */
		/* USART1 clock enable */
		__HAL_RCC_USART1_CLK_ENABLE()
		;

		/**USART1 GPIO Configuration
		 PB6     ------> USART1_TX
		 PB7     ------> USART1_RX
		 */
		GPIO_InitStruct.Pin = GPIO_PIN_6 | GPIO_PIN_7;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
		GPIO_InitStruct.Alternate = GPIO_AF0_USART1;
		HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

		/* USART1 DMA Init */
		/* USART1_RX Init */
		hdma_usart1_rx.Instance = DMA1_Channel3;
		hdma_usart1_rx.Init.Direction = DMA_PERIPH_TO_MEMORY;
		hdma_usart1_rx.Init.PeriphInc = DMA_PINC_DISABLE;
		hdma_usart1_rx.Init.MemInc = DMA_MINC_ENABLE;
		hdma_usart1_rx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
		hdma_usart1_rx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
		hdma_usart1_rx.Init.Mode = DMA_NORMAL;
		hdma_usart1_rx.Init.Priority = DMA_PRIORITY_LOW;
		if (HAL_DMA_Init(&hdma_usart1_rx) != HAL_OK)
		{
			_Error_Handler(__FILE__, __LINE__);
		}

		__HAL_LINKDMA(uartHandle, hdmarx, hdma_usart1_rx);

		/* USART1_TX Init */
		hdma_usart1_tx.Instance = DMA1_Channel2;
		hdma_usart1_tx.Init.Direction = DMA_MEMORY_TO_PERIPH;
		hdma_usart1_tx.Init.PeriphInc = DMA_PINC_DISABLE;
		hdma_usart1_tx.Init.MemInc = DMA_MINC_ENABLE;
		hdma_usart1_tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
		hdma_usart1_tx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
		hdma_usart1_tx.Init.Mode = DMA_NORMAL;
		hdma_usart1_tx.Init.Priority = DMA_PRIORITY_LOW;
		if (HAL_DMA_Init(&hdma_usart1_tx) != HAL_OK)
		{
			_Error_Handler(__FILE__, __LINE__);
		}

		__HAL_LINKDMA(uartHandle, hdmatx, hdma_usart1_tx);

		/* USART1 interrupt Init */
		HAL_NVIC_SetPriority(USART1_IRQn, 0, 0);
		HAL_NVIC_EnableIRQ(USART1_IRQn);
		/* USER CODE BEGIN USART1_MspInit 1 */

		/* USER CODE END USART1_MspInit 1 */
	}
}

void HAL_UART_MspDeInit(UART_HandleTypeDef* uartHandle)
{

	if (uartHandle->Instance == USART1)
	{
		/* USER CODE BEGIN USART1_MspDeInit 0 */

		/* USER CODE END USART1_MspDeInit 0 */
		/* Peripheral clock disable */
		__HAL_RCC_USART1_CLK_DISABLE();

		/**USART1 GPIO Configuration
		 PB6     ------> USART1_TX
		 PB7     ------> USART1_RX
		 */
		HAL_GPIO_DeInit(GPIOB, GPIO_PIN_6 | GPIO_PIN_7);

		/* USART1 DMA DeInit */
		HAL_DMA_DeInit(uartHandle->hdmarx);
		HAL_DMA_DeInit(uartHandle->hdmatx);

		/* USART1 interrupt Deinit */
		HAL_NVIC_DisableIRQ(USART1_IRQn);
		/* USER CODE BEGIN USART1_MspDeInit 1 */

		/* USER CODE END USART1_MspDeInit 1 */
	}
}

/* USER CODE BEGIN 1 */
void response_OK()
{
	HAL_UART_Transmit_IT(&huart1, "OK   \r\n", 7);
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if (huart->Instance == USART1)
	{
		/*	check further only if the last characters are fine	*/
		if (rxBuffer[RX_BUFFER_SIZE - 2] == 0x0D
				&& rxBuffer[RX_BUFFER_SIZE - 1] == 0x0A)
		{
			emergencyStop = 0;

			switch (rxBuffer[0])
			{
			/****************** Safety ******************/

			/* watchdog controll <!!! WARNING, USE WITH CAUTION !!!> */
			case 0x01:
				if (rxBuffer[1] == 0x01)
				{
					watchdogFlag = 0x01; // enable watchdog (default)
					response_OK();
				}
				else if (rxBuffer[1] == 0x00)
				{
					watchdogFlag = 0x00; // disable watchdog
					response_OK();
				}
				else
					// do nothing
					;
				break;

				/****************** Driving ******************/

				/*	set motors speed	*/
			case 0x10:
				setMotorX(1, rxBuffer[1] & 0x7F, (rxBuffer[1] & 0x80) >> 7);
				setMotorX(2, rxBuffer[2] & 0x7F, (rxBuffer[2] & 0x80) >> 7);
				setMotorX(3, rxBuffer[3] & 0x7F, (rxBuffer[3] & 0x80) >> 7);
				setMotorX(4, rxBuffer[4] & 0x7F, (rxBuffer[4] & 0x80) >> 7);
				response_OK();
				break;

				/****************** Internal sensors ******************/

				/*	read battery voltage */
			case 0x30:
				HAL_ADC_Start(&hadc);
				while (HAL_ADC_PollForConversion(&hadc, 10) != HAL_OK)
					;
				Battery_level = HAL_ADC_GetValue(&hadc);

				HAL_UART_Transmit_IT(&huart1, (uint8_t *) &Battery_level, 2);
				break;

				/****************** Communication ******************/

				/******** I2C ********/

				/*	Write */
			case 0x41:
				HAL_I2C_Master_Transmit_IT(&hi2c2, rxBuffer[1], &rxBuffer[2],
						3);
				response_OK();
				break;
				/*	Read */
			case 0x42:
				HAL_I2C_Mem_Read_IT(&hi2c2, rxBuffer[1], rxBuffer[2],
						rxBuffer[3], txBuffer, rxBuffer[3]);
				HAL_UART_Transmit_IT(&huart1, txBuffer, 8);
				break;

				/****************** Servos ******************/

				/*	set servo duty on channel 1*/
			case 0x81:
				mani.axis_1 = (rxBuffer[1] << 8) + rxBuffer[2];
				maniUseDiff = true;
				setManipulator(mani.axis_1, mani.axis_2);
				response_OK();
				break;

				/*	set servo duty on channel 2*/
			case 0x82:
				mani.axis_2 = (rxBuffer[1] << 8) + rxBuffer[2];
				maniUseDiff = true;
				setManipulator(mani.axis_1, mani.axis_2);
				response_OK();
				break;

				/*	set servo duty on channel 3*/
			case 0x83:
				mani.gripper = (rxBuffer[1] << 8) + rxBuffer[2];
				maniUseDiff = true;
				setGripper(mani.gripper);
				response_OK();
				break;

				/*	set manipulator orientation (only axis without gripper)	- 2 bytes MSB first*/
			case 0x84:
				mani.axis_1 = (rxBuffer[1] << 8) + rxBuffer[2];
				mani.axis_2 = (rxBuffer[3] << 8) + rxBuffer[4];
				maniUseDiff = true;
				setManipulator(mani.axis_1, mani.axis_2);
				response_OK();
				break;

				/*	set gripper value	*/
			case 0x94:
				mani.gripper = (rxBuffer[1] << 8) + rxBuffer[2];
				maniUseDiff = true;
				setGripper(mani.gripper);
				response_OK();
				break;

				/*	set camera position */ // LEGACY
			case 0xA4:
				mani.axis_2 = (rxBuffer[1] << 8) + rxBuffer[2];
				maniUseDiff = true;
				response_OK();
				break;
			default:
				break;
			}
		}
		__HAL_UART_FLUSH_DRREGISTER(&huart1); // Clear the buffer to prevent overrun

		HAL_UART_Receive_DMA(&huart1, rxBuffer, RX_BUFFER_SIZE);
	}
}
/* USER CODE END 1 */

/**
 * @}
 */

/**
 * @}
 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
