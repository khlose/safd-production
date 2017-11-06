################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/flash.c \
../Src/font5x7.c \
../Src/main.c \
../Src/ssd1306.c \
../Src/ssd1306libtest.c \
../Src/stm32l4xx_hal_msp.c \
../Src/stm32l4xx_it.c \
../Src/system_stm32l4xx.c 

OBJS += \
./Src/flash.o \
./Src/font5x7.o \
./Src/main.o \
./Src/ssd1306.o \
./Src/ssd1306libtest.o \
./Src/stm32l4xx_hal_msp.o \
./Src/stm32l4xx_it.o \
./Src/system_stm32l4xx.o 

C_DEPS += \
./Src/flash.d \
./Src/font5x7.d \
./Src/main.d \
./Src/ssd1306.d \
./Src/ssd1306libtest.d \
./Src/stm32l4xx_hal_msp.d \
./Src/stm32l4xx_it.d \
./Src/system_stm32l4xx.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o: ../Src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32L475xx -I"C:/Users/schwi/Documents/GitHub/safd-production/safd-prototype/Inc" -I"C:/Users/schwi/Documents/GitHub/safd-production/safd-prototype/Drivers/STM32L4xx_HAL_Driver/Inc" -I"C:/Users/schwi/Documents/GitHub/safd-production/safd-prototype/Drivers/STM32L4xx_HAL_Driver/Inc/Legacy" -I"C:/Users/schwi/Documents/GitHub/safd-production/safd-prototype/Drivers/CMSIS/Device/ST/STM32L4xx/Include" -I"C:/Users/schwi/Documents/GitHub/safd-production/safd-prototype/Drivers/CMSIS/Include"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


