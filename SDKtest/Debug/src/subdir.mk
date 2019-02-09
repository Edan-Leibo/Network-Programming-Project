################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/ClientHandler.cpp \
../src/DataTransferTest.cpp \
../src/HallOfFameTest.cpp \
../src/LoginTest.cpp \
../src/RegisterTest.cpp \
../src/SDKtest.cpp \
../src/ShowUsersTest.cpp 

OBJS += \
./src/ClientHandler.o \
./src/DataTransferTest.o \
./src/HallOfFameTest.o \
./src/LoginTest.o \
./src/RegisterTest.o \
./src/SDKtest.o \
./src/ShowUsersTest.o 

CPP_DEPS += \
./src/ClientHandler.d \
./src/DataTransferTest.d \
./src/HallOfFameTest.d \
./src/LoginTest.d \
./src/RegisterTest.d \
./src/SDKtest.d \
./src/ShowUsersTest.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/user/Desktop/NetworkingLab/SDKServer/src" -I"/home/user/Desktop/NetworkingLab/SDKClient/src" -I"/home/user/Desktop/NetworkingLab/Utils/src" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


