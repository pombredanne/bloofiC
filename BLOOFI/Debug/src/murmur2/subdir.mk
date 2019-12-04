################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/murmur2/MurmurHash2.c 

OBJS += \
./src/murmur2/MurmurHash2.o 

C_DEPS += \
./src/murmur2/MurmurHash2.d 


# Each subdirectory must supply rules for building sources it contributes
src/murmur2/%.o: ../src/murmur2/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


