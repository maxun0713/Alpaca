################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../BusEngine.o \
../ClientNode.o \
../ClientNodePort.o \
../Exporter.o \
../Node.o \
../ServerNode.o \
../ServerNodePort.o \
../main.o 

CPP_SRCS += \
../BusEngine.cpp \
../ClientNode.cpp \
../ClientNodePort.cpp \
../Exporter.cpp \
../Node.cpp \
../ServerNode.cpp \
../ServerNodePort.cpp \
../main.cpp 

OBJS += \
./BusEngine.o \
./ClientNode.o \
./ClientNodePort.o \
./Exporter.o \
./Node.o \
./ServerNode.o \
./ServerNodePort.o \
./main.o 

CPP_DEPS += \
./BusEngine.d \
./ClientNode.d \
./ClientNodePort.d \
./Exporter.d \
./Node.d \
./ServerNode.d \
./ServerNodePort.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


