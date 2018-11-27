/*
 * manipulator.h
 *
 *  Created on: 12.11.2018
 *      Author: mr_frost
 */

#ifndef MANIPULATOR_H_
#define MANIPULATOR_H_

#include "stm32f0xx_hal.h"
#include "main.h"
#include <stdbool.h>


#define	MANI_AXIS_1_MIN	500 //2800
#define MANI_AXIS_1_MAX	6000 //3900
#define MANI_AXIS_2_MIN	500 //3500
#define MANI_AXIS_2_MAX	6000 //4200
#define MANI_GRIPPER_MIN 1000
#define MANI_GRIPPER_MAX 5000
#define MANI_DIFF 15	//the lower number the slower manipulator
#define GRIPPER_DIFF 10
#define MANI_TIME_DIVIDER 5
#define MANI_DIM 50

volatile uint16_t gripperValue;


extern const volatile uint8_t alpha[MANI_DIM][MANI_DIM];
extern const volatile uint8_t beta[MANI_DIM][MANI_DIM];
extern volatile bool maniUseDiff;

void setManipulator(uint16_t axis_1, uint16_t axis_2);
void setGripper(uint16_t gripper);
uint16_t * calculateManipulator();

typedef enum eManiDirection {
	stop,
	up,
	down,
	left,
	right
} eManiDirection;


typedef struct manipulator {
	uint16_t axis_1;
	uint16_t axis_2;
	uint16_t gripper;
} manipulator;

volatile manipulator mani;


#endif /* MANIPULATOR_H_ */
