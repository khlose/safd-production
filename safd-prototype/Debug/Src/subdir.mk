################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/buffer.c \
../Src/ds2782.c \
../Src/fall_detection.c \
../Src/lsm6ds3.c \
../Src/main.c \
../Src/ssd1306.c \
../Src/stm32l4xx_hal_msp.c \
../Src/stm32l4xx_it.c \
../Src/system_stm32l4xx.c \
../Src/util.c 

OBJS += \
./Src/buffer.o \
./Src/ds2782.o \
./Src/fall_detection.o \
./Src/lsm6ds3.o \
./Src/main.o \
./Src/ssd1306.o \
./Src/stm32l4xx_hal_msp.o \
./Src/stm32l4xx_it.o \
./Src/system_stm32l4xx.o \
./Src/util.o 

C_DEPS += \
./Src/buffer.d \
./Src/ds2782.d \
./Src/fall_detection.d \
./Src/lsm6ds3.d \
./Src/main.d \
./Src/ssd1306.d \
./Src/stm32l4xx_hal_msp.d \
./Src/stm32l4xx_it.d \
./Src/system_stm32l4xx.d \
./Src/util.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o: ../Src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32L475xx -I"C:/Users/Station13/Documents/GitHub/safd-production/safd-prototype/Inc" -I"C:/Users/Station13/Documents/GitHub/safd-production/safd-prototype/Drivers/STM32L4xx_HAL_Driver/Inc" -I"C:/Users/Station13/Documents/GitHub/safd-production/safd-prototype/Drivers/STM32L4xx_HAL_Driver/Inc/Legacy" -I"C:/Users/Station13/Documents/GitHub/safd-production/safd-prototype/Drivers/CMSIS/Device/ST/STM32L4xx/Include" -I"C:/Users/Station13/Documents/GitHub/safd-production/safd-prototype/Drivers/CMSIS/Include"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


