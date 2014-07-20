################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/EventCallback.cpp \
../src/GateSrv.cpp \
../src/ModuleManeger.cpp \
../src/SessionManager.cpp \
../src/main.cpp 

OBJS += \
./src/EventCallback.o \
./src/GateSrv.o \
./src/ModuleManeger.o \
./src/SessionManager.o \
./src/main.o 

CPP_DEPS += \
./src/EventCallback.d \
./src/GateSrv.d \
./src/ModuleManeger.d \
./src/SessionManager.d \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/home/marv/Alpaca/alpaca-src -I/home/marv/Alpaca/service-src -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


