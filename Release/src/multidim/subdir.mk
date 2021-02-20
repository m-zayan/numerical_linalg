################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/multidim/matrix.cpp \
../src/multidim/matrix_alloc.cpp \
../src/multidim/matrix_ops.cpp \
../src/multidim/matrix_stdout.cpp 

OBJS += \
./src/multidim/matrix.o \
./src/multidim/matrix_alloc.o \
./src/multidim/matrix_ops.o \
./src/multidim/matrix_stdout.o 

CPP_DEPS += \
./src/multidim/matrix.d \
./src/multidim/matrix_alloc.d \
./src/multidim/matrix_ops.d \
./src/multidim/matrix_stdout.d 


# Each subdirectory must supply rules for building sources it contributes
src/multidim/%.o: ../src/multidim/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


