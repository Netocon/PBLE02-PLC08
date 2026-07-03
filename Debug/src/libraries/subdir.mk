################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/libraries/endoder.c \
../src/libraries/io.c \
../src/libraries/keys.c \
../src/libraries/lcd.c \
../src/libraries/serial.c \
../src/libraries/system_LPC11Uxx.c \
../src/libraries/timer.c 

S_SRCS += \
../src/libraries/aeabi_romdiv_patch.s 

C_DEPS += \
./src/libraries/endoder.d \
./src/libraries/io.d \
./src/libraries/keys.d \
./src/libraries/lcd.d \
./src/libraries/serial.d \
./src/libraries/system_LPC11Uxx.d \
./src/libraries/timer.d 

OBJS += \
./src/libraries/aeabi_romdiv_patch.o \
./src/libraries/endoder.o \
./src/libraries/io.o \
./src/libraries/keys.o \
./src/libraries/lcd.o \
./src/libraries/serial.o \
./src/libraries/system_LPC11Uxx.o \
./src/libraries/timer.o 


# Each subdirectory must supply rules for building sources it contributes
src/libraries/%.o: ../src/libraries/%.s src/libraries/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU Assembler'
	arm-none-eabi-gcc -c -x assembler-with-cpp -DDEBUG -D__CODE_RED -DCORE_M0 -D__LPC11UXX__ -D__REDLIB__ -g3 -gdwarf-4 -mcpu=cortex-m0 -mthumb -specs=redlib.specs -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/libraries/%.o: ../src/libraries/%.c src/libraries/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__CODE_RED -DCORE_M0 -D__LPC11UXX__ -D__REDLIB__ -O0 -fno-common -g3 -gdwarf-4 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -v -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m0 -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src-2f-libraries

clean-src-2f-libraries:
	-$(RM) ./src/libraries/aeabi_romdiv_patch.o ./src/libraries/endoder.d ./src/libraries/endoder.o ./src/libraries/io.d ./src/libraries/io.o ./src/libraries/keys.d ./src/libraries/keys.o ./src/libraries/lcd.d ./src/libraries/lcd.o ./src/libraries/serial.d ./src/libraries/serial.o ./src/libraries/system_LPC11Uxx.d ./src/libraries/system_LPC11Uxx.o ./src/libraries/timer.d ./src/libraries/timer.o

.PHONY: clean-src-2f-libraries

