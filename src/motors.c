/*
 * motors.c
 *
 *  Created on: Mar 22, 2017
 *      Author: marcin
 */

#include "motors.h"
#include <stdio.h>
#include <stdlib.h>

volatile uint16_t lastAlpha[2] = {0,0};
volatile uint16_t lastBeta[2] = {0,0};
volatile uint8_t mani_x = 0;
volatile uint8_t mani_y = 0;

volatile uint8_t maniTimeDivider = 0;


volatile eManiDirection maniDirection = stop;

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

	uint16_t axis_1_old = TIM1->CCR3;
	uint16_t axis_2_old = TIM1->CCR2;

	if (maniUseDiff) {
		int16_t axis_1_diff = (axis_1 - axis_1_old) & 0x7fff;
		int16_t axis_2_diff = (axis_2 - axis_2_old) & 0x7fff;

		if (axis_1_diff > MANI_DIFF) {
			if (axis_1 > axis_1_old) axis_1_old += MANI_DIFF;
			else axis_1_old -= MANI_DIFF;
			TIM1->CCR3 = axis_1_old;
		}
		else TIM1->CCR3 = axis_1;

		if (axis_2_diff > MANI_DIFF) {
			if (axis_2 > axis_2_old) axis_2_old += MANI_DIFF;
			else axis_2_old -= MANI_DIFF;
			TIM1->CCR2 = axis_2_old;
		}
		else TIM1->CCR2 = axis_2;
	}
	else if (maniTimeDivider >= MANI_TIME_DIVIDER && maniDirection != stop) {
		maniTimeDivider = 0;
		uint16_t * calculatedValues;
		calculatedValues = calculateManipulator();
		TIM1->CCR3 = calculatedValues[0];
		TIM1->CCR2 = calculatedValues[1];
		free(calculatedValues);
	}
	maniTimeDivider++;
}

uint16_t * calculateManipulator() {
	const uint8_t ONE_DEGREE = 7;   // 7 us for one degree
	const uint16_t T0 = 1500;    // 1500 us

	switch (maniDirection) {
		case(stop):
			break;
		case(up):
			mani_y++;
			if (mani_y >= MANI_DIM) mani_y = MANI_DIM - 1;
			break;
		case(down):
			if (mani_y > 0) mani_y--;
			break;
		case(left):
			mani_x++;
			if (mani_x >= MANI_DIM) mani_x = MANI_DIM - 1;
			break;
		case(right):
			if (mani_x > 0) mani_x--;
			break;
		default:
			break;
	}

	uint8_t alphaAngle = alpha[mani_x][mani_y];
	uint8_t betaAngle = beta[mani_x][mani_y];

	int8_t alphaDelta = -(90 - alphaAngle);
	int8_t betaDelta = 180 - betaAngle;

	int16_t alphaDeltaT = ONE_DEGREE * alphaDelta;
	int16_t betaDeltaT = ONE_DEGREE * betaDelta;

	uint16_t alphaNewT = T0 + alphaDeltaT;
	uint16_t betaNewT = T0 + betaDeltaT;

	//  48000 depends on STM timer
	uint16_t alphaNew = (uint16_t)((float)alphaNewT/2.4f);
	uint16_t betaNew = (uint16_t)((float)betaNewT/2.4f);

	uint16_t * calculatedValues = malloc(2*sizeof(uint16_t));
	calculatedValues[0] = alphaNew;
	calculatedValues[1] = betaNew;

	return calculatedValues;
}

void setGripper(uint16_t gripper) {
	if (gripper < MANI_GRIPPER_MIN || gripper > MANI_GRIPPER_MAX)
		gripper = 3000;

	uint16_t gripperOld = TIM1->CCR1;
	int16_t gripper_diff = (gripper - gripperOld) & 0x7fff;

	if (gripper_diff > MANI_DIFF) {
		if (gripper > gripperOld) gripperOld += GRIPPER_DIFF;
		else gripperOld -= GRIPPER_DIFF;

		TIM1->CCR1 = gripperOld;
	}
	else TIM1->CCR1 = gripper;


}
