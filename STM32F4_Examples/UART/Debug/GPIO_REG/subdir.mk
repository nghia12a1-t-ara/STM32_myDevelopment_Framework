################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../GPIO_REG/GPIO_REG.c 

OBJS += \
./GPIO_REG/GPIO_REG.o 

C_DEPS += \
./GPIO_REG/GPIO_REG.d 


# Each subdirectory must supply rules for building sources it contributes
GPIO_REG/%.o GPIO_REG/%.su: ../GPIO_REG/%.c GPIO_REG/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F401RETx -DSTM32F4 -c -I../Inc -I"D:/STM32/STM32_SourceCode/STM32_Programming/STM32F4_Examples/UART/NVIC_REG" -I"D:/STM32/STM32_SourceCode/STM32_Programming/STM32F4_Examples/UART/GPIO_REG" -I"D:/STM32/STM32_SourceCode/STM32_Programming/STM32F4_Examples/UART/CLOCK_REG" -I"D:/STM32/STM32_SourceCode/STM32_Programming/STM32F4_Examples/UART/UART_REG" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-GPIO_REG

clean-GPIO_REG:
	-$(RM) ./GPIO_REG/GPIO_REG.d ./GPIO_REG/GPIO_REG.o ./GPIO_REG/GPIO_REG.su

.PHONY: clean-GPIO_REG

