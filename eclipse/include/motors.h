#ifndef __motors_H_
#define __motors_H_

#include "stm32f0xx_hal.h"
#include "main.h"

#define	MANI_AXIS_1_MIN	3840
#define MANI_AXIS_1_MAX	5600
#define MANI_AXIS_2_MIN	2880
#define MANI_AXIS_2_MAX	3840
#define MANI_GRIPPER_MIN 3200
#define MANI_GRIPPER_MAX 4800

void setMotorX(uint8_t mot, uint8_t value, uint8_t direction);
void setManipulator(uint16_t axis_1, uint16_t axis_2);
void setGripper(uint16_t gripper);

volatile uint16_t gripperValue;

#endif
