################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../tests/test_api/alloc_nd_matrix.cpp \
../tests/test_api/api_main_test.cpp \
../tests/test_api/linalg_dot.cpp \
../tests/test_api/linalg_echelon.cpp \
../tests/test_api/linalg_hessenberg.cpp \
../tests/test_api/linalg_lu.cpp \
../tests/test_api/linalg_matmul.cpp \
../tests/test_api/linalg_transpose.cpp \
../tests/test_api/sum_alg.cpp 

OBJS += \
./tests/test_api/alloc_nd_matrix.o \
./tests/test_api/api_main_test.o \
./tests/test_api/linalg_dot.o \
./tests/test_api/linalg_echelon.o \
./tests/test_api/linalg_hessenberg.o \
./tests/test_api/linalg_lu.o \
./tests/test_api/linalg_matmul.o \
./tests/test_api/linalg_transpose.o \
./tests/test_api/sum_alg.o 

CPP_DEPS += \
./tests/test_api/alloc_nd_matrix.d \
./tests/test_api/api_main_test.d \
./tests/test_api/linalg_dot.d \
./tests/test_api/linalg_echelon.d \
./tests/test_api/linalg_hessenberg.d \
./tests/test_api/linalg_lu.d \
./tests/test_api/linalg_matmul.d \
./tests/test_api/linalg_transpose.d \
./tests/test_api/sum_alg.d 


# Each subdirectory must supply rules for building sources it contributes
tests/test_api/%.o: ../tests/test_api/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


