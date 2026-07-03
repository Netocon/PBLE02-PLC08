################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/cr_startup_lpc11uxx.c \
../src/crp.c \
../src/event.c \
../src/main.c \
../src/output.c \
../src/stateMachine.c \
../src/variables.c 

S_SRCS += \
../src/aeabi_romdiv_patch.s 

C_DEPS += \
./src/cr_startup_lpc11uxx.d \
./src/crp.d \
./src/event.d \
./src/main.d \
./src/output.d \
./src/stateMachine.d \
./src/variables.d 

OBJS += \
./src/aeabi_romdiv_patch.o \
./src/cr_startup_lpc11uxx.o \
./src/crp.o \
./src/event.o \
./src/main.o \
./src/output.o \
./src/stateMachine.o \
./src/variables.o 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.s src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU Assembler'
	arm-none-eabi-gcc -c -x assembler-with-cpp -DDEBUG -D__CODE_RED -DCORE_M0 -D__LPC11UXX__ -D__REDLIB__ -g3 -gdwarf-4 -mcpu=cortex-m0 -mthumb -specs=redlib.specs -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/%.o: ../src/%.c src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__CODE_RED -DCORE_M0 -D__LPC11UXX__ -D__REDLIB__ -O0 -fno-common -g3 -gdwarf-4 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -v -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m0 -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src

clean-src:
	-$(RM) ./src/aeabi_romdiv_patch.o ./src/cr_startup_lpc11uxx.d ./src/cr_startup_lpc11uxx.o ./src/crp.d ./src/crp.o ./src/event.d ./src/event.o ./src/main.d ./src/main.o ./src/output.d ./src/output.o ./src/stateMachine.d ./src/stateMachine.o ./src/variables.d ./src/variables.o

.PHONY: clean-src

