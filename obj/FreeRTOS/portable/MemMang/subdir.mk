################################################################################
# MRS Version: {"version":"1.8.5","date":"2023/05/22"}
# 自动生成的文件。不要编辑！
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../FreeRTOS/portable/MemMang/heap_4.c 

OBJS += \
./FreeRTOS/portable/MemMang/heap_4.o 

C_DEPS += \
./FreeRTOS/portable/MemMang/heap_4.d 


# Each subdirectory must supply rules for building sources it contributes
FreeRTOS/portable/MemMang/%.o: ../FreeRTOS/portable/MemMang/%.c
	@	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"D:\Cube_machine\Main_Control_FreeRTOS\main_control\Ld" -I"D:\Cube_machine\Main_Control_FreeRTOS\main_control\Startup" -I"D:\Cube_machine\Main_Control_FreeRTOS\main_control\Debug" -I"D:\Cube_machine\Main_Control_FreeRTOS\main_control\Core" -I"D:\Cube_machine\Main_Control_FreeRTOS\main_control\User" -I"D:\Cube_machine\Main_Control_FreeRTOS\main_control\Peripheral\inc" -I"D:\Cube_machine\Main_Control_FreeRTOS\main_control\FreeRTOS" -I"D:\Cube_machine\Main_Control_FreeRTOS\main_control\FreeRTOS\include" -I"D:\Cube_machine\Main_Control_FreeRTOS\main_control\FreeRTOS\portable\Common" -I"D:\Cube_machine\Main_Control_FreeRTOS\main_control\FreeRTOS\portable\GCC\RISC-V" -I"D:\Cube_machine\Main_Control_FreeRTOS\main_control\FreeRTOS\portable\GCC\RISC-V\chip_specific_extensions\RV32I_PFIC_no_extensions" -I"D:\Cube_machine\Main_Control_FreeRTOS\main_control\FreeRTOS\portable\MemMang" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

