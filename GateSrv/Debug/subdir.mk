################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../GamePortSink.o \
../GateSrv.o \
../Main.o \
../Message.pb.o \
../SessionManager.o 

CPP_SRCS += \
../GamePortSink.cpp \
../GateSrv.cpp \
../Main.cpp \
../Message.pb.cpp \
../SessionManager.cpp 

OBJS += \
./GamePortSink.o \
./GateSrv.o \
./Main.o \
./Message.pb.o \
./SessionManager.o 

CPP_DEPS += \
./GamePortSink.d \
./GateSrv.d \
./Main.d \
./Message.pb.d \
./SessionManager.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/home/marv/Alpaca/alpaca-src/include -I/home/marv/Alpaca/include -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


