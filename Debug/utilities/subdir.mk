################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../utilities/fsl_debug_console.c 

OBJS += \
./utilities/fsl_debug_console.o 

C_DEPS += \
./utilities/fsl_debug_console.d 


# Each subdirectory must supply rules for building sources it contributes
utilities/%.o: ../utilities/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DCPU_MKL25Z128VLK4 -DCPU_MKL25Z128VLK4_cm0plus -DFSL_RTOS_BM -DSDK_OS_BAREMETAL -DSDK_DEBUGCONSOLE=1 -DPRINTF_FLOAT_ENABLE=1 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -D__REDLIB__ -I"C:\Users\Ananth Deshpande\Documents\MCUXpressoIDE_11.2.0_4120\workspace\tilt_angle_Acc_MKL25Z128xxx4_Project\board" -I"C:\Users\Ananth Deshpande\Documents\MCUXpressoIDE_11.2.0_4120\workspace\tilt_angle_Acc_MKL25Z128xxx4_Project\source" -I"C:\Users\Ananth Deshpande\Documents\MCUXpressoIDE_11.2.0_4120\workspace\tilt_angle_Acc_MKL25Z128xxx4_Project" -I"C:\Users\Ananth Deshpande\Documents\MCUXpressoIDE_11.2.0_4120\workspace\tilt_angle_Acc_MKL25Z128xxx4_Project\drivers" -I"C:\Users\Ananth Deshpande\Documents\MCUXpressoIDE_11.2.0_4120\workspace\tilt_angle_Acc_MKL25Z128xxx4_Project\CMSIS" -I"C:\Users\Ananth Deshpande\Documents\MCUXpressoIDE_11.2.0_4120\workspace\tilt_angle_Acc_MKL25Z128xxx4_Project\utilities" -I"C:\Users\Ananth Deshpande\Documents\MCUXpressoIDE_11.2.0_4120\workspace\tilt_angle_Acc_MKL25Z128xxx4_Project\startup" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fmerge-constants -fmacro-prefix-map="../$(@D)/"=. -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


