################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/cbfifo.c \
../source/delay.c \
../source/finiteStateMachine.c \
../source/i2c.c \
../source/led.c \
../source/mma8451.c \
../source/mtb.c \
../source/semihost_hardfault.c \
../source/switch.c \
../source/sys_read_write.c \
../source/sysclock.c \
../source/test_cbfifo.c \
../source/tilt_angle_Acc_MKL25Z128xxx4_Project.c \
../source/touch.c \
../source/uart.c 

OBJS += \
./source/cbfifo.o \
./source/delay.o \
./source/finiteStateMachine.o \
./source/i2c.o \
./source/led.o \
./source/mma8451.o \
./source/mtb.o \
./source/semihost_hardfault.o \
./source/switch.o \
./source/sys_read_write.o \
./source/sysclock.o \
./source/test_cbfifo.o \
./source/tilt_angle_Acc_MKL25Z128xxx4_Project.o \
./source/touch.o \
./source/uart.o 

C_DEPS += \
./source/cbfifo.d \
./source/delay.d \
./source/finiteStateMachine.d \
./source/i2c.d \
./source/led.d \
./source/mma8451.d \
./source/mtb.d \
./source/semihost_hardfault.d \
./source/switch.d \
./source/sys_read_write.d \
./source/sysclock.d \
./source/test_cbfifo.d \
./source/tilt_angle_Acc_MKL25Z128xxx4_Project.d \
./source/touch.d \
./source/uart.d 


# Each subdirectory must supply rules for building sources it contributes
source/%.o: ../source/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DCPU_MKL25Z128VLK4 -DCPU_MKL25Z128VLK4_cm0plus -DFSL_RTOS_BM -DSDK_OS_BAREMETAL -DSDK_DEBUGCONSOLE=1 -DPRINTF_FLOAT_ENABLE=1 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -D__REDLIB__ -I"C:\Users\Ananth Deshpande\Documents\MCUXpressoIDE_11.2.0_4120\workspace\tilt_angle_Acc_MKL25Z128xxx4_Project\board" -I"C:\Users\Ananth Deshpande\Documents\MCUXpressoIDE_11.2.0_4120\workspace\tilt_angle_Acc_MKL25Z128xxx4_Project\source" -I"C:\Users\Ananth Deshpande\Documents\MCUXpressoIDE_11.2.0_4120\workspace\tilt_angle_Acc_MKL25Z128xxx4_Project" -I"C:\Users\Ananth Deshpande\Documents\MCUXpressoIDE_11.2.0_4120\workspace\tilt_angle_Acc_MKL25Z128xxx4_Project\drivers" -I"C:\Users\Ananth Deshpande\Documents\MCUXpressoIDE_11.2.0_4120\workspace\tilt_angle_Acc_MKL25Z128xxx4_Project\CMSIS" -I"C:\Users\Ananth Deshpande\Documents\MCUXpressoIDE_11.2.0_4120\workspace\tilt_angle_Acc_MKL25Z128xxx4_Project\utilities" -I"C:\Users\Ananth Deshpande\Documents\MCUXpressoIDE_11.2.0_4120\workspace\tilt_angle_Acc_MKL25Z128xxx4_Project\startup" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fmerge-constants -fmacro-prefix-map="../$(@D)/"=. -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


