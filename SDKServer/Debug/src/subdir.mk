################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/FileManager.cpp \
../src/RequestManager.cpp \
../src/Server.cpp \
../src/User.cpp 

OBJS += \
./src/FileManager.o \
./src/RequestManager.o \
./src/Server.o \
./src/User.o 

CPP_DEPS += \
./src/FileManager.d \
./src/RequestManager.d \
./src/Server.d \
./src/User.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/user/Desktop/NetworkingLab/Utils/src" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


