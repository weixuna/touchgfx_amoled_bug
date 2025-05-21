################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../TouchGFX/generated/images/src/BitmapDatabase.cpp \
../TouchGFX/generated/images/src/SVGDatabase.cpp \
../TouchGFX/generated/images/src/image_demo.cpp \
../TouchGFX/generated/images/src/image_hen.cpp \
../TouchGFX/generated/images/src/image_mianImage.cpp \
../TouchGFX/generated/images/src/image_uiuug.cpp 

OBJS += \
./TouchGFX/generated/images/src/BitmapDatabase.o \
./TouchGFX/generated/images/src/SVGDatabase.o \
./TouchGFX/generated/images/src/image_demo.o \
./TouchGFX/generated/images/src/image_hen.o \
./TouchGFX/generated/images/src/image_mianImage.o \
./TouchGFX/generated/images/src/image_uiuug.o 

CPP_DEPS += \
./TouchGFX/generated/images/src/BitmapDatabase.d \
./TouchGFX/generated/images/src/SVGDatabase.d \
./TouchGFX/generated/images/src/image_demo.d \
./TouchGFX/generated/images/src/image_hen.d \
./TouchGFX/generated/images/src/image_mianImage.d \
./TouchGFX/generated/images/src/image_uiuug.d 


# Each subdirectory must supply rules for building sources it contributes
TouchGFX/generated/images/src/%.o TouchGFX/generated/images/src/%.su TouchGFX/generated/images/src/%.cyclo: ../TouchGFX/generated/images/src/%.cpp TouchGFX/generated/images/src/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m33 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32U585xx -c -I../Core/Inc -I../TouchGFX/App -I../TouchGFX/target/generated -I../TouchGFX/target -I../Drivers/STM32U5xx_HAL_Driver/Inc -I../Drivers/STM32U5xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32U5xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include/ -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM33_NTZ/non_secure/ -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/ -I../Middlewares/Third_Party/CMSIS/RTOS2/Include/ -I../Middlewares/ST/touchgfx/framework/include -I../TouchGFX/generated/fonts/include -I../TouchGFX/generated/gui_generated/include -I../TouchGFX/generated/images/include -I../TouchGFX/generated/texts/include -I../TouchGFX/generated/videos/include -I../TouchGFX/gui/include -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -femit-class-debug-always -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-TouchGFX-2f-generated-2f-images-2f-src

clean-TouchGFX-2f-generated-2f-images-2f-src:
	-$(RM) ./TouchGFX/generated/images/src/BitmapDatabase.cyclo ./TouchGFX/generated/images/src/BitmapDatabase.d ./TouchGFX/generated/images/src/BitmapDatabase.o ./TouchGFX/generated/images/src/BitmapDatabase.su ./TouchGFX/generated/images/src/SVGDatabase.cyclo ./TouchGFX/generated/images/src/SVGDatabase.d ./TouchGFX/generated/images/src/SVGDatabase.o ./TouchGFX/generated/images/src/SVGDatabase.su ./TouchGFX/generated/images/src/image_demo.cyclo ./TouchGFX/generated/images/src/image_demo.d ./TouchGFX/generated/images/src/image_demo.o ./TouchGFX/generated/images/src/image_demo.su ./TouchGFX/generated/images/src/image_hen.cyclo ./TouchGFX/generated/images/src/image_hen.d ./TouchGFX/generated/images/src/image_hen.o ./TouchGFX/generated/images/src/image_hen.su ./TouchGFX/generated/images/src/image_mianImage.cyclo ./TouchGFX/generated/images/src/image_mianImage.d ./TouchGFX/generated/images/src/image_mianImage.o ./TouchGFX/generated/images/src/image_mianImage.su ./TouchGFX/generated/images/src/image_uiuug.cyclo ./TouchGFX/generated/images/src/image_uiuug.d ./TouchGFX/generated/images/src/image_uiuug.o ./TouchGFX/generated/images/src/image_uiuug.su

.PHONY: clean-TouchGFX-2f-generated-2f-images-2f-src

