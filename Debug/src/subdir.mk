################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/adc.c \
../src/dma.c \
../src/gpio.c \
../src/i2c.c \
../src/main.c \
../src/mani.c \
../src/motors.c \
../src/spi.c \
../src/stm32f0xx_hal_msp.c \
../src/stm32f0xx_it.c \
../src/tim.c \
../src/usart.c 

OBJS += \
./src/adc.o \
./src/dma.o \
./src/gpio.o \
./src/i2c.o \
./src/main.o \
./src/mani.o \
./src/motors.o \
./src/spi.o \
./src/stm32f0xx_hal_msp.o \
./src/stm32f0xx_it.o \
./src/tim.o \
./src/usart.o 

C_DEPS += \
./src/adc.d \
./src/dma.d \
./src/gpio.d \
./src/i2c.d \
./src/main.d \
./src/mani.d \
./src/motors.d \
./src/spi.d \
./src/stm32f0xx_hal_msp.d \
./src/stm32f0xx_it.d \
./src/tim.d \
./src/usart.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM GNU C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0 -mthumb -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -fno-move-loop-invariants -Wall -Wextra  -g3 -DDEBUG -DTRACE -DSTM32F030x8 -I"../include" -I"../system/include" -I"../system/include/cmsis" -I"../system/include/stm32f0xx" -I"../system/include/cmsis/device" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


