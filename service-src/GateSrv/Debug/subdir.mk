################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../EventCallback.o \
../GatePortSink.o \
../GateSrv.o \
../ModuleManeger.o \
../SessionManager.o 

CPP_SRCS += \
../EventCallback.cpp \
../GatePortSink.cpp \
../GateSrv.cpp \
../ModuleManeger.cpp \
../SessionManager.cpp 

OBJS += \
./EventCallback.o \
./GatePortSink.o \
./GateSrv.o \
./ModuleManeger.o \
./SessionManager.o 

CPP_DEPS += \
./EventCallback.d \
./GatePortSink.d \
./GateSrv.d \
./ModuleManeger.d \
./SessionManager.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/home/marv/Alpaca/alpaca-src -I/home/marv/Alpaca/service-src -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


