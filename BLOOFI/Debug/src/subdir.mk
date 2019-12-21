################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/BFINode.c \
../src/TestBloomFilter.c \
../src/bitset.c \
../src/bloofi.c \
../src/bloom.c \
../src/hashtable.c \
../src/list.c 

OBJS += \
./src/BFINode.o \
./src/TestBloomFilter.o \
./src/bitset.o \
./src/bloofi.o \
./src/bloom.o \
./src/hashtable.o \
./src/list.o 

C_DEPS += \
./src/BFINode.d \
./src/TestBloomFilter.d \
./src/bitset.d \
./src/bloofi.d \
./src/bloom.d \
./src/hashtable.d \
./src/list.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


