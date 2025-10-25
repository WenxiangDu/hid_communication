################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/User_Src/com.c \
../Core/User_Src/user_hid_mouse.c 

OBJS += \
./Core/User_Src/com.o \
./Core/User_Src/user_hid_mouse.o 

C_DEPS += \
./Core/User_Src/com.d \
./Core/User_Src/user_hid_mouse.d 


# Each subdirectory must supply rules for building sources it contributes
Core/User_Src/%.o Core/User_Src/%.su Core/User_Src/%.cyclo: ../Core/User_Src/%.c Core/User_Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_PWR_LDO_SUPPLY -DUSE_HAL_DRIVER -DSTM32H743xx -c -I../Core/Inc -I../USB_HOST/App -I../USB_HOST/Target -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Middlewares/ST/STM32_USB_Host_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Host_Library/Class/HID/Inc -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-User_Src

clean-Core-2f-User_Src:
	-$(RM) ./Core/User_Src/com.cyclo ./Core/User_Src/com.d ./Core/User_Src/com.o ./Core/User_Src/com.su ./Core/User_Src/user_hid_mouse.cyclo ./Core/User_Src/user_hid_mouse.d ./Core/User_Src/user_hid_mouse.o ./Core/User_Src/user_hid_mouse.su

.PHONY: clean-Core-2f-User_Src

