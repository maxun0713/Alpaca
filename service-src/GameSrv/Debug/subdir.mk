################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../GameSrv.cpp \
../GatePortSink.cpp \
../ModuleManeger.cpp \
../main.cpp 

OBJS += \
./GameSrv.o \
./GatePortSink.o \
./ModuleManeger.o \
./main.o 

CPP_DEPS += \
./GameSrv.d \
./GatePortSink.d \
./ModuleManeger.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/home/marv/Alpaca/alpaca-src -I/home/marv/Alpaca/service-src -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


