/**
  ******************************************************************************
  * File Name          : main.h
  * Description        : This file contains the common defines of the application
  ******************************************************************************
  *
  * COPYRIGHT(c) 2017 STMicroelectronics
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
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H
  /* Includes ------------------------------------------------------------------*/

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private define ------------------------------------------------------------*/

#define SENSE1_Pin GPIO_PIN_0
#define SENSE1_GPIO_Port GPIOA
#define SENSE2_Pin GPIO_PIN_1
#define SENSE2_GPIO_Port GPIOA
#define SENSE3_Pin GPIO_PIN_2
#define SENSE3_GPIO_Port GPIOA
#define SENSE4_Pin GPIO_PIN_3
#define SENSE4_GPIO_Port GPIOA
#define BAT_MEAS_Pin GPIO_PIN_4
#define BAT_MEAS_GPIO_Port GPIOA
#define LED_Pin GPIO_PIN_5
#define LED_GPIO_Port GPIOA
#define EN1_UC_Pin GPIO_PIN_6
#define EN1_UC_GPIO_Port GPIOA
#define EN2_UC_Pin GPIO_PIN_7
#define EN2_UC_GPIO_Port GPIOA
#define EN3_UC_Pin GPIO_PIN_0
#define EN3_UC_GPIO_Port GPIOB
#define EN4_UC_Pin GPIO_PIN_1
#define EN4_UC_GPIO_Port GPIOB
#define IN21_UC_Pin GPIO_PIN_10
#define IN21_UC_GPIO_Port GPIOB
#define IN22_UC_Pin GPIO_PIN_11
#define IN22_UC_GPIO_Port GPIOB
#define IN31_UC_Pin GPIO_PIN_12
#define IN31_UC_GPIO_Port GPIOB
#define IN32_UC_Pin GPIO_PIN_13
#define IN32_UC_GPIO_Port GPIOB
#define IN41_UC_Pin GPIO_PIN_14
#define IN41_UC_GPIO_Port GPIOB
#define IN42_UC_Pin GPIO_PIN_15
#define IN42_UC_GPIO_Port GPIOB
#define SERVO1_UC_Pin GPIO_PIN_8
#define SERVO1_UC_GPIO_Port GPIOA
#define SERVO2_UC_Pin GPIO_PIN_9
#define SERVO2_UC_GPIO_Port GPIOA
#define SERVO3_UC_Pin GPIO_PIN_10
#define SERVO3_UC_GPIO_Port GPIOA
#define IN11_UC_Pin GPIO_PIN_8
#define IN11_UC_GPIO_Port GPIOB
#define IN12_UC_Pin GPIO_PIN_9
#define IN12_UC_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

/**
  * @}
  */ 

/**
  * @}
*/ 

#endif /* __MAIN_H */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
