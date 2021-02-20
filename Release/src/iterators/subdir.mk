################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/iterators/RandomAccessNdIterator.cpp \
../src/iterators/SequentialNdIterator.cpp 

OBJS += \
./src/iterators/RandomAccessNdIterator.o \
./src/iterators/SequentialNdIterator.o 

CPP_DEPS += \
./src/iterators/RandomAccessNdIterator.d \
./src/iterators/SequentialNdIterator.d 


# Each subdirectory must supply rules for building sources it contributes
src/iterators/%.o: ../src/iterators/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


