################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
D:/STM32/STM32_SourceCode/STM32F4/STM32F4/STM32F4\ Standard\ Peripheral\ Library/Libraries/CMSIS/DSP_Lib/Examples/arm_dotproduct_example/arm_dotproduct_example_f32.c 

OBJS += \
./Libraries/CMSIS/DSP_Lib/Examples/arm_dotproduct_example/arm_dotproduct_example_f32.o 

C_DEPS += \
./Libraries/CMSIS/DSP_Lib/Examples/arm_dotproduct_example/arm_dotproduct_example_f32.d 


# Each subdirectory must supply rules for building sources it contributes
Libraries/CMSIS/DSP_Lib/Examples/arm_dotproduct_example/arm_dotproduct_example_f32.o: D:/STM32/STM32_SourceCode/STM32F4/STM32F4/STM32F4\ Standard\ Peripheral\ Library/Libraries/CMSIS/DSP_Lib/Examples/arm_dotproduct_example/arm_dotproduct_example_f32.c Libraries/CMSIS/DSP_Lib/Examples/arm_dotproduct_example/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DARM_MATH_CM4 -DSTM32F4XX -DSTM32 -DSTM32F401RETx -DSTM32F4 -c -I../Inc -I"D:/STM32/STM32_SourceCode/Register Programming/Common_Lib" -I"D:/STM32/STM32_SourceCode/STM32F4/STM32F4/STM32F4 Standard Peripheral Library/Libraries/CMSIS/Include" -I"D:/STM32/STM32_SourceCode/STM32F4/STM32F4/STM32F4 Standard Peripheral Library/Libraries/STM32F4xx_StdPeriph_Driver/inc" -I"D:/STM32/STM32_SourceCode/STM32F4/STM32F4/STM32F4 Standard Peripheral Library/Libraries/CMSIS/Lib" -I"D:/STM32/STM32_SourceCode/STM32F4/STM32F4/STM32F4 Standard Peripheral Library/Libraries/CMSIS/Lib/ARM" -I"D:/STM32/STM32_SourceCode/STM32F4/STM32F4/STM32F4 Standard Peripheral Library/Libraries/CMSIS/Lib/G++" -I"D:/STM32/STM32_SourceCode/STM32F4/STM32F4/STM32F4 Standard Peripheral Library/Libraries/CMSIS/Lib/GCC" -I"D:/STM32/STM32_SourceCode/STM32F4/STM32F4/STM32F4 Standard Peripheral Library/Libraries/CMSIS/Device/ST/STM32F4xx/Include" -O0 -ffunction-sections -fdata-sections -Wall -v -fstack-usage -MMD -MP -MF"Libraries/CMSIS/DSP_Lib/Examples/arm_dotproduct_example/arm_dotproduct_example_f32.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

