#ifndef __motors_H_
#define __motors_H_

#include "stm32f0xx_hal.h"
#include "main.h"

#define	MANI_AXIS_1_MIN	1000 //2800
#define MANI_AXIS_1_MAX	5000 //3900
#define MANI_AXIS_2_MIN	1000 //3500
#define MANI_AXIS_2_MAX	5000 //4200
#define MANI_GRIPPER_MIN 2500
#define MANI_GRIPPER_MAX 4400

void setMotorX(uint8_t mot, uint8_t value, uint8_t direction);
void setManipulator(uint16_t axis_1, uint16_t axis_2);
void setGripper(uint16_t gripper);

volatile uint16_t gripperValue;

typedef struct {
	uint16_t axis_1;
	uint16_t axis_2;
	uint16_t gripper;
} manipulator;

#endif
