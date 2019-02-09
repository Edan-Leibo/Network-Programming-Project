################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/FileTest.cpp \
../src/MultipleListenerTest.cpp \
../src/TCPSocketTest.cpp \
../src/UDPSocketTest.cpp \
../src/main.cpp 

OBJS += \
./src/FileTest.o \
./src/MultipleListenerTest.o \
./src/TCPSocketTest.o \
./src/UDPSocketTest.o \
./src/main.o 

CPP_DEPS += \
./src/FileTest.d \
./src/MultipleListenerTest.d \
./src/TCPSocketTest.d \
./src/UDPSocketTest.d \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/user/Desktop/NetworkingLab/Utils/src" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


