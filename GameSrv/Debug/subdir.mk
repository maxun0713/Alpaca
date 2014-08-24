################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../GameSrv.o \
../GatePortSink.o \
../Main.o \
../Message.pb.o 

CPP_SRCS += \
../GameSrv.cpp \
../GatePortSink.cpp \
../Main.cpp \
../Message.pb.cpp 

OBJS += \
./GameSrv.o \
./GatePortSink.o \
./Main.o \
./Message.pb.o 

CPP_DEPS += \
./GameSrv.d \
./GatePortSink.d \
./Main.d \
./Message.pb.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/home/marv/Alpaca/alpaca-src/include -I/home/marv/Alpaca/include -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


