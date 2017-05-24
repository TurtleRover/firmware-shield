/*
 * motors.c
 *
 *  Created on: Mar 22, 2017
 *      Author: marcin
 */

#include "motors.h"

void setMotorX(uint8_t mot, uint8_t value, uint8_t direction) {
	switch (mot) {
	/*	mixed up due to hardware mistake */
	case 1:
		HAL_GPIO_WritePin(IN11_UC_GPIO_Port, IN11_UC_Pin, direction);
		HAL_GPIO_WritePin(IN12_UC_GPIO_Port, IN12_UC_Pin, direction^1);
		TIM3->CCR4 = value;
		break;
	case 2:
		HAL_GPIO_WritePin(IN21_UC_GPIO_Port, IN21_UC_Pin, direction);
		HAL_GPIO_WritePin(IN22_UC_GPIO_Port, IN22_UC_Pin, direction^1);
		TIM3->CCR3 = value;
		break;
	case 3:
		HAL_GPIO_WritePin(IN31_UC_GPIO_Port, IN31_UC_Pin, direction);
		HAL_GPIO_WritePin(IN32_UC_GPIO_Port, IN32_UC_Pin, direction^1);
		TIM3->CCR1 = value;
		break;
	case 4:
		HAL_GPIO_WritePin(IN41_UC_GPIO_Port, IN41_UC_Pin, direction);
		HAL_GPIO_WritePin(IN42_UC_GPIO_Port, IN42_UC_Pin, direction^1);
		TIM3->CCR2 = value;
		break;
	default:
		break;
	}
}

void setManipulator(uint16_t axis_1, uint16_t axis_2) {
	if (axis_1 < MANI_AXIS_1_MIN || axis_1 > MANI_AXIS_1_MAX) axis_1 = 3600;

	if (axis_2 < MANI_AXIS_2_MIN || axis_2 > MANI_AXIS_2_MAX) axis_2 = 3600;

	uint16_t axis_1_old = TIM1->CCR1;
	uint16_t axis_2_old = TIM1->CCR2;

	if (axis_1 > axis_1_old) axis_1_old += 10;
	else axis_1_old -= 10;

	if (axis_2 > axis_2_old) axis_2_old += 10;
	else axis_2_old -= 10;

	TIM1->CCR1 = axis_1_old;
	TIM1->CCR2 = axis_2_old;
}

void setGripper(uint16_t gripper) {
	if (gripper < MANI_GRIPPER_MIN || gripper > MANI_GRIPPER_MAX)
		gripper = 3600;

	uint16_t gripperOld = TIM1->CCR3;
	if (gripper > gripperOld) gripperOld += 10;
	else gripperOld -= 10;

	TIM1->CCR3 = gripperOld;
}
