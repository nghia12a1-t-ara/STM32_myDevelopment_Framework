################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../FLASH_REG/FLASH_REG.c 

OBJS += \
./FLASH_REG/FLASH_REG.o 

C_DEPS += \
./FLASH_REG/FLASH_REG.d 


# Each subdirectory must supply rules for building sources it contributes
FLASH_REG/%.o FLASH_REG/%.su: ../FLASH_REG/%.c FLASH_REG/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F401RETx -DSTM32F4 -c -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-FLASH_REG

clean-FLASH_REG:
	-$(RM) ./FLASH_REG/FLASH_REG.d ./FLASH_REG/FLASH_REG.o ./FLASH_REG/FLASH_REG.su

.PHONY: clean-FLASH_REG

