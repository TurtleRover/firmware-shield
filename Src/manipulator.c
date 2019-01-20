/*
 * manipulator.c
 *
 *  Created on: 12.11.2018
 *      Author: mr_frost
 */

#include "manipulator.h"

volatile uint16_t lastAlpha[2] = { 0, 0 };
volatile uint16_t lastBeta[2] = { 0, 0 };
volatile uint8_t mani_x = 0;
volatile uint8_t mani_y = 0;

volatile uint8_t maniTimeDivider = 0;

volatile eManiDirection maniDirection = stop;

void setManipulator(uint16_t axis_1, uint16_t axis_2) {
	if (axis_1 < MANI_AXIS_1_MIN || axis_1 > MANI_AXIS_1_MAX)
		axis_1 = 3300;

	if (axis_2 < MANI_AXIS_2_MIN || axis_2 > MANI_AXIS_2_MAX)
		axis_2 = 3300;

	TIM1->CCR3 = axis_1;
	TIM1->CCR2 = axis_2;

}

uint16_t * calculateManipulator() {
	const uint8_t ONE_DEGREE = 7;   // 7 us for one degree
	const uint16_t T0 = 1500;    // 1500 us

	switch (maniDirection) {
	case (stop):
		break;
	case (up):
		mani_y++;
		if (mani_y >= MANI_DIM)
			mani_y = MANI_DIM - 1;
		break;
	case (down):
		if (mani_y > 0)
			mani_y--;
		break;
	case (left):
		mani_x++;
		if (mani_x >= MANI_DIM)
			mani_x = MANI_DIM - 1;
		break;
	case (right):
		if (mani_x > 0)
			mani_x--;
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
	uint16_t alphaNew = (uint16_t) ((float) alphaNewT / 2.4f);
	uint16_t betaNew = (uint16_t) ((float) betaNewT / 2.4f);

	uint16_t * calculatedValues = malloc(2 * sizeof(uint16_t));
	calculatedValues[0] = alphaNew;
	calculatedValues[1] = betaNew;

	return calculatedValues;
}

void setGripper(uint16_t gripper) {
	if (gripper < MANI_GRIPPER_MIN || gripper > MANI_GRIPPER_MAX)
		gripper = 3300;
	TIM1->CCR1 = gripper;

}
