################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Inchie4KeyLED.cpp \
../src/InchieKey.cpp \
../src/InchieKeyLED.cpp \
../src/InchieLED.cpp \
../src/InchiePot.cpp \
../src/InchieTest.cpp \
../src/SLIPEncodedSerial.cpp \
../src/ledkey_4x.cpp \
../src/main.cpp 

C_SRCS += \
../src/BlinkLed.c \
../src/Timer.c \
../src/uart.c 

OBJS += \
./src/BlinkLed.o \
./src/Inchie4KeyLED.o \
./src/InchieKey.o \
./src/InchieKeyLED.o \
./src/InchieLED.o \
./src/InchiePot.o \
./src/InchieTest.o \
./src/SLIPEncodedSerial.o \
./src/Timer.o \
./src/ledkey_4x.o \
./src/main.o \
./src/uart.o 

C_DEPS += \
./src/BlinkLed.d \
./src/Timer.d \
./src/uart.d 

CPP_DEPS += \
./src/Inchie4KeyLED.d \
./src/InchieKey.d \
./src/InchieKeyLED.d \
./src/InchieLED.d \
./src/InchiePot.d \
./src/InchieTest.d \
./src/SLIPEncodedSerial.d \
./src/ledkey_4x.d \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0 -mthumb -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall -Wextra  -g3 -DDEBUG -DUSE_FULL_ASSERT -DTRACE -DOS_USE_TRACE_SEMIHOSTING_DEBUG -DSTM32F051 -DUSE_STDPERIPH_DRIVER -DHSE_VALUE=8000000 -I"../include" -I"../system/include" -I"../system/include/cmsis" -I"../system/include/stm32f0-stdperiph" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C++ Compiler'
	arm-none-eabi-g++ -mcpu=cortex-m0 -mthumb -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall -Wextra  -g3 -DDEBUG -DUSE_FULL_ASSERT -DTRACE -DOS_USE_TRACE_SEMIHOSTING_DEBUG -DSTM32F051 -DUSE_STDPERIPH_DRIVER -DHSE_VALUE=8000000 -I"../include" -I"../system/include" -I"../system/include/cmsis" -I"../system/include/stm32f0-stdperiph" -std=gnu++11 -fabi-version=0 -fno-exceptions -fno-rtti -fno-use-cxa-atexit -fno-threadsafe-statics -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


