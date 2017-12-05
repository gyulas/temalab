################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
INO_SRCS += \
..\levitation_aio.ino 

CPP_SRCS += \
..\.ino.cpp 

C_SRCS += \
..\controller.c 

C_DEPS += \
.\controller.c.d 

LINK_OBJ += \
.\.ino.cpp.o \
.\controller.c.o 

INO_DEPS += \
.\levitation_aio.ino.d 

CPP_DEPS += \
.\.ino.cpp.d 


# Each subdirectory must supply rules for building sources it contributes
.ino.cpp.o: ..\.ino.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"C:\sloeber\/arduinoPlugin/packages/arduino/tools/avr-gcc/4.9.2-atmel3.5.4-arduino2/bin/avr-g++" -c -g -Os -Wall -Wextra -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -flto -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=10802 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR   -I"C:\sloeber\arduinoPlugin\packages\arduino\hardware\avr\1.6.20\cores\arduino" -I"C:\sloeber\arduinoPlugin\packages\arduino\hardware\avr\1.6.20\variants\mega" -I"C:\sloeber\arduinoPlugin\libraries\TimerOne\1.1.0" -I"C:\sloeber\arduinoPlugin\libraries\VL6180X\1.2.0" -I"C:\sloeber\arduinoPlugin\packages\arduino\hardware\avr\1.6.20\libraries\Wire" -I"C:\sloeber\arduinoPlugin\packages\arduino\hardware\avr\1.6.20\libraries\Wire\src" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"
	@echo 'Finished building: $<'
	@echo ' '

controller.c.o: ..\controller.c
	@echo 'Building file: $<'
	@echo 'Starting C compile'
	"C:\sloeber\/arduinoPlugin/packages/arduino/tools/avr-gcc/4.9.2-atmel3.5.4-arduino2/bin/avr-gcc" -c -g -Os -Wall -Wextra -std=gnu11 -ffunction-sections -fdata-sections -flto -fno-fat-lto-objects -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=10802 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR   -I"C:\sloeber\arduinoPlugin\packages\arduino\hardware\avr\1.6.20\cores\arduino" -I"C:\sloeber\arduinoPlugin\packages\arduino\hardware\avr\1.6.20\variants\mega" -I"C:\sloeber\arduinoPlugin\libraries\TimerOne\1.1.0" -I"C:\sloeber\arduinoPlugin\libraries\VL6180X\1.2.0" -I"C:\sloeber\arduinoPlugin\packages\arduino\hardware\avr\1.6.20\libraries\Wire" -I"C:\sloeber\arduinoPlugin\packages\arduino\hardware\avr\1.6.20\libraries\Wire\src" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 "$<"  -o  "$@"
	@echo 'Finished building: $<'
	@echo ' '

levitation_aio.o: ..\levitation_aio.ino
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"C:\sloeber\/arduinoPlugin/packages/arduino/tools/avr-gcc/4.9.2-atmel3.5.4-arduino2/bin/avr-g++" -c -g -Os -Wall -Wextra -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -flto -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=10802 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR   -I"C:\sloeber\arduinoPlugin\packages\arduino\hardware\avr\1.6.20\cores\arduino" -I"C:\sloeber\arduinoPlugin\packages\arduino\hardware\avr\1.6.20\variants\mega" -I"C:\sloeber\arduinoPlugin\libraries\TimerOne\1.1.0" -I"C:\sloeber\arduinoPlugin\libraries\VL6180X\1.2.0" -I"C:\sloeber\arduinoPlugin\packages\arduino\hardware\avr\1.6.20\libraries\Wire" -I"C:\sloeber\arduinoPlugin\packages\arduino\hardware\avr\1.6.20\libraries\Wire\src" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"
	@echo 'Finished building: $<'
	@echo ' '


