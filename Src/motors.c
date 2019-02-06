/*
 * motors.c
 *
 *  Created on: 12.11.2018
 *      Author: mr_frost
 */

#include "motors.h"


void setMotorX(uint8_t mot, uint8_t value, uint8_t direction) {
	switch (mot) {
	/*	mixed up due to hardware mistake */
	case 1:
		HAL_GPIO_WritePin(DIR1_GPIO_Port, DIR1_Pin, direction);
		TIM3->CCR1 = value;
		break;
	case 2:
		HAL_GPIO_WritePin(DIR2_GPIO_Port, DIR2_Pin, direction);
		TIM3->CCR2 = value;
		break;
	case 3:
		HAL_GPIO_WritePin(DIR3_GPIO_Port, DIR3_Pin, direction);
		TIM3->CCR3 = value;
		break;
	case 4:
		HAL_GPIO_WritePin(DIR4_GPIO_Port, DIR4_Pin, direction);
		TIM3->CCR4 = value;
		break;
	default:
		break;
	}
}
