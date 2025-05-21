################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../TouchGFX/generated/images/src/controlCenter_iamge/image_fore.cpp \
../TouchGFX/generated/images/src/controlCenter_iamge/image_fore_pressed.cpp \
../TouchGFX/generated/images/src/controlCenter_iamge/image_jishi.cpp \
../TouchGFX/generated/images/src/controlCenter_iamge/image_liangdu.cpp \
../TouchGFX/generated/images/src/controlCenter_iamge/image_miaobiao.cpp \
../TouchGFX/generated/images/src/controlCenter_iamge/image_naozhong.cpp \
../TouchGFX/generated/images/src/controlCenter_iamge/image_shezhi.cpp \
../TouchGFX/generated/images/src/controlCenter_iamge/image_taiwan.cpp \
../TouchGFX/generated/images/src/controlCenter_iamge/image_wurao.cpp \
../TouchGFX/generated/images/src/controlCenter_iamge/image_zhendong.cpp 

OBJS += \
./TouchGFX/generated/images/src/controlCenter_iamge/image_fore.o \
./TouchGFX/generated/images/src/controlCenter_iamge/image_fore_pressed.o \
./TouchGFX/generated/images/src/controlCenter_iamge/image_jishi.o \
./TouchGFX/generated/images/src/controlCenter_iamge/image_liangdu.o \
./TouchGFX/generated/images/src/controlCenter_iamge/image_miaobiao.o \
./TouchGFX/generated/images/src/controlCenter_iamge/image_naozhong.o \
./TouchGFX/generated/images/src/controlCenter_iamge/image_shezhi.o \
./TouchGFX/generated/images/src/controlCenter_iamge/image_taiwan.o \
./TouchGFX/generated/images/src/controlCenter_iamge/image_wurao.o \
./TouchGFX/generated/images/src/controlCenter_iamge/image_zhendong.o 

CPP_DEPS += \
./TouchGFX/generated/images/src/controlCenter_iamge/image_fore.d \
./TouchGFX/generated/images/src/controlCenter_iamge/image_fore_pressed.d \
./TouchGFX/generated/images/src/controlCenter_iamge/image_jishi.d \
./TouchGFX/generated/images/src/controlCenter_iamge/image_liangdu.d \
./TouchGFX/generated/images/src/controlCenter_iamge/image_miaobiao.d \
./TouchGFX/generated/images/src/controlCenter_iamge/image_naozhong.d \
./TouchGFX/generated/images/src/controlCenter_iamge/image_shezhi.d \
./TouchGFX/generated/images/src/controlCenter_iamge/image_taiwan.d \
./TouchGFX/generated/images/src/controlCenter_iamge/image_wurao.d \
./TouchGFX/generated/images/src/controlCenter_iamge/image_zhendong.d 


# Each subdirectory must supply rules for building sources it contributes
TouchGFX/generated/images/src/controlCenter_iamge/%.o TouchGFX/generated/images/src/controlCenter_iamge/%.su TouchGFX/generated/images/src/controlCenter_iamge/%.cyclo: ../TouchGFX/generated/images/src/controlCenter_iamge/%.cpp TouchGFX/generated/images/src/controlCenter_iamge/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m33 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32U585xx -c -I../Core/Inc -I../TouchGFX/App -I../TouchGFX/target/generated -I../TouchGFX/target -I../Drivers/STM32U5xx_HAL_Driver/Inc -I../Drivers/STM32U5xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32U5xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include/ -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM33_NTZ/non_secure/ -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/ -I../Middlewares/Third_Party/CMSIS/RTOS2/Include/ -I../Middlewares/ST/touchgfx/framework/include -I../TouchGFX/generated/fonts/include -I../TouchGFX/generated/gui_generated/include -I../TouchGFX/generated/images/include -I../TouchGFX/generated/texts/include -I../TouchGFX/generated/videos/include -I../TouchGFX/gui/include -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -femit-class-debug-always -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-TouchGFX-2f-generated-2f-images-2f-src-2f-controlCenter_iamge

clean-TouchGFX-2f-generated-2f-images-2f-src-2f-controlCenter_iamge:
	-$(RM) ./TouchGFX/generated/images/src/controlCenter_iamge/image_fore.cyclo ./TouchGFX/generated/images/src/controlCenter_iamge/image_fore.d ./TouchGFX/generated/images/src/controlCenter_iamge/image_fore.o ./TouchGFX/generated/images/src/controlCenter_iamge/image_fore.su ./TouchGFX/generated/images/src/controlCenter_iamge/image_fore_pressed.cyclo ./TouchGFX/generated/images/src/controlCenter_iamge/image_fore_pressed.d ./TouchGFX/generated/images/src/controlCenter_iamge/image_fore_pressed.o ./TouchGFX/generated/images/src/controlCenter_iamge/image_fore_pressed.su ./TouchGFX/generated/images/src/controlCenter_iamge/image_jishi.cyclo ./TouchGFX/generated/images/src/controlCenter_iamge/image_jishi.d ./TouchGFX/generated/images/src/controlCenter_iamge/image_jishi.o ./TouchGFX/generated/images/src/controlCenter_iamge/image_jishi.su ./TouchGFX/generated/images/src/controlCenter_iamge/image_liangdu.cyclo ./TouchGFX/generated/images/src/controlCenter_iamge/image_liangdu.d ./TouchGFX/generated/images/src/controlCenter_iamge/image_liangdu.o ./TouchGFX/generated/images/src/controlCenter_iamge/image_liangdu.su ./TouchGFX/generated/images/src/controlCenter_iamge/image_miaobiao.cyclo ./TouchGFX/generated/images/src/controlCenter_iamge/image_miaobiao.d ./TouchGFX/generated/images/src/controlCenter_iamge/image_miaobiao.o ./TouchGFX/generated/images/src/controlCenter_iamge/image_miaobiao.su ./TouchGFX/generated/images/src/controlCenter_iamge/image_naozhong.cyclo ./TouchGFX/generated/images/src/controlCenter_iamge/image_naozhong.d ./TouchGFX/generated/images/src/controlCenter_iamge/image_naozhong.o ./TouchGFX/generated/images/src/controlCenter_iamge/image_naozhong.su ./TouchGFX/generated/images/src/controlCenter_iamge/image_shezhi.cyclo ./TouchGFX/generated/images/src/controlCenter_iamge/image_shezhi.d ./TouchGFX/generated/images/src/controlCenter_iamge/image_shezhi.o ./TouchGFX/generated/images/src/controlCenter_iamge/image_shezhi.su ./TouchGFX/generated/images/src/controlCenter_iamge/image_taiwan.cyclo ./TouchGFX/generated/images/src/controlCenter_iamge/image_taiwan.d ./TouchGFX/generated/images/src/controlCenter_iamge/image_taiwan.o ./TouchGFX/generated/images/src/controlCenter_iamge/image_taiwan.su ./TouchGFX/generated/images/src/controlCenter_iamge/image_wurao.cyclo ./TouchGFX/generated/images/src/controlCenter_iamge/image_wurao.d ./TouchGFX/generated/images/src/controlCenter_iamge/image_wurao.o ./TouchGFX/generated/images/src/controlCenter_iamge/image_wurao.su ./TouchGFX/generated/images/src/controlCenter_iamge/image_zhendong.cyclo ./TouchGFX/generated/images/src/controlCenter_iamge/image_zhendong.d ./TouchGFX/generated/images/src/controlCenter_iamge/image_zhendong.o ./TouchGFX/generated/images/src/controlCenter_iamge/image_zhendong.su

.PHONY: clean-TouchGFX-2f-generated-2f-images-2f-src-2f-controlCenter_iamge

