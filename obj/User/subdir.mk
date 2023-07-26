################################################################################
# MRS Version: {"version":"1.8.5","date":"2023/05/22"}
# 自动生成的文件。不要编辑！
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../User/can.c \
../User/ch32v30x_it.c \
../User/gpio.c \
../User/key_func.c \
../User/leddrive.c \
../User/main.c \
../User/system_ch32v30x.c \
../User/uart.c 

OBJS += \
./User/can.o \
./User/ch32v30x_it.o \
./User/gpio.o \
./User/key_func.o \
./User/leddrive.o \
./User/main.o \
./User/system_ch32v30x.o \
./User/uart.o 

C_DEPS += \
./User/can.d \
./User/ch32v30x_it.d \
./User/gpio.d \
./User/key_func.d \
./User/leddrive.d \
./User/main.d \
./User/system_ch32v30x.d \
./User/uart.d 


# Each subdirectory must supply rules for building sources it contributes
User/%.o: ../User/%.c
	@	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"D:\Cube_machine\Main_Control_FreeRTOS\main_control\Ld" -I"D:\Cube_machine\Main_Control_FreeRTOS\main_control\Startup" -I"D:\Cube_machine\Main_Control_FreeRTOS\main_control\Debug" -I"D:\Cube_machine\Main_Control_FreeRTOS\main_control\Core" -I"D:\Cube_machine\Main_Control_FreeRTOS\main_control\User" -I"D:\Cube_machine\Main_Control_FreeRTOS\main_control\Peripheral\inc" -I"D:\Cube_machine\Main_Control_FreeRTOS\main_control\FreeRTOS" -I"D:\Cube_machine\Main_Control_FreeRTOS\main_control\FreeRTOS\include" -I"D:\Cube_machine\Main_Control_FreeRTOS\main_control\FreeRTOS\portable\Common" -I"D:\Cube_machine\Main_Control_FreeRTOS\main_control\FreeRTOS\portable\GCC\RISC-V" -I"D:\Cube_machine\Main_Control_FreeRTOS\main_control\FreeRTOS\portable\GCC\RISC-V\chip_specific_extensions\RV32I_PFIC_no_extensions" -I"D:\Cube_machine\Main_Control_FreeRTOS\main_control\FreeRTOS\portable\MemMang" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

