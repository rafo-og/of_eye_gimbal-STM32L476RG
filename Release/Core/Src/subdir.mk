################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/adns2610.c \
../Core/Src/eyes.c \
../Core/Src/gimbalControl.c \
../Core/Src/gpio.c \
../Core/Src/main.c \
../Core/Src/opticalFlow.c \
../Core/Src/spi.c \
../Core/Src/stm32l4xx_it.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32l4xx.c \
../Core/Src/tim.c \
../Core/Src/usart.c 

OBJS += \
./Core/Src/adns2610.o \
./Core/Src/eyes.o \
./Core/Src/gimbalControl.o \
./Core/Src/gpio.o \
./Core/Src/main.o \
./Core/Src/opticalFlow.o \
./Core/Src/spi.o \
./Core/Src/stm32l4xx_it.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32l4xx.o \
./Core/Src/tim.o \
./Core/Src/usart.o 

C_DEPS += \
./Core/Src/adns2610.d \
./Core/Src/eyes.d \
./Core/Src/gimbalControl.d \
./Core/Src/gpio.d \
./Core/Src/main.d \
./Core/Src/opticalFlow.d \
./Core/Src/spi.d \
./Core/Src/stm32l4xx_it.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32l4xx.d \
./Core/Src/tim.d \
./Core/Src/usart.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/adns2610.o: ../Core/Src/adns2610.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 '-DHSE_VALUE=8000000' '-DMSI_VALUE=4000000' '-DLSI_VALUE=32000' '-DHSE_STARTUP_TIMEOUT=100' '-DHSI_VALUE=16000000' '-DLSE_STARTUP_TIMEOUT=5000' '-DLSE_VALUE=32768' '-DDATA_CACHE_ENABLE=1' '-DVDD_VALUE=3300' '-DINSTRUCTION_CACHE_ENABLE=1' '-DEXTERNALSAI2_CLOCK_VALUE=2097000' -DSTM32L476xx -DUSE_FULL_LL_DRIVER '-DEXTERNALSAI1_CLOCK_VALUE=2097000' '-DPREFETCH_ENABLE=1' -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/adns2610.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/eyes.o: ../Core/Src/eyes.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 '-DHSE_VALUE=8000000' '-DMSI_VALUE=4000000' '-DLSI_VALUE=32000' '-DHSE_STARTUP_TIMEOUT=100' '-DHSI_VALUE=16000000' '-DLSE_STARTUP_TIMEOUT=5000' '-DLSE_VALUE=32768' '-DDATA_CACHE_ENABLE=1' '-DVDD_VALUE=3300' '-DINSTRUCTION_CACHE_ENABLE=1' '-DEXTERNALSAI2_CLOCK_VALUE=2097000' -DSTM32L476xx -DUSE_FULL_LL_DRIVER '-DEXTERNALSAI1_CLOCK_VALUE=2097000' '-DPREFETCH_ENABLE=1' -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/eyes.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/gimbalControl.o: ../Core/Src/gimbalControl.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 '-DHSE_VALUE=8000000' '-DMSI_VALUE=4000000' '-DLSI_VALUE=32000' '-DHSE_STARTUP_TIMEOUT=100' '-DHSI_VALUE=16000000' '-DLSE_STARTUP_TIMEOUT=5000' '-DLSE_VALUE=32768' '-DDATA_CACHE_ENABLE=1' '-DVDD_VALUE=3300' '-DINSTRUCTION_CACHE_ENABLE=1' '-DEXTERNALSAI2_CLOCK_VALUE=2097000' -DSTM32L476xx -DUSE_FULL_LL_DRIVER '-DEXTERNALSAI1_CLOCK_VALUE=2097000' '-DPREFETCH_ENABLE=1' -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/gimbalControl.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/gpio.o: ../Core/Src/gpio.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 '-DHSE_VALUE=8000000' '-DMSI_VALUE=4000000' '-DLSI_VALUE=32000' '-DHSE_STARTUP_TIMEOUT=100' '-DHSI_VALUE=16000000' '-DLSE_STARTUP_TIMEOUT=5000' '-DLSE_VALUE=32768' '-DDATA_CACHE_ENABLE=1' '-DVDD_VALUE=3300' '-DINSTRUCTION_CACHE_ENABLE=1' '-DEXTERNALSAI2_CLOCK_VALUE=2097000' -DSTM32L476xx -DUSE_FULL_LL_DRIVER '-DEXTERNALSAI1_CLOCK_VALUE=2097000' '-DPREFETCH_ENABLE=1' -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/gpio.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/main.o: ../Core/Src/main.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 '-DHSE_VALUE=8000000' '-DMSI_VALUE=4000000' '-DLSI_VALUE=32000' '-DHSE_STARTUP_TIMEOUT=100' '-DHSI_VALUE=16000000' '-DLSE_STARTUP_TIMEOUT=5000' '-DLSE_VALUE=32768' '-DDATA_CACHE_ENABLE=1' '-DVDD_VALUE=3300' '-DINSTRUCTION_CACHE_ENABLE=1' '-DEXTERNALSAI2_CLOCK_VALUE=2097000' -DSTM32L476xx -DUSE_FULL_LL_DRIVER '-DEXTERNALSAI1_CLOCK_VALUE=2097000' '-DPREFETCH_ENABLE=1' -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/main.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/opticalFlow.o: ../Core/Src/opticalFlow.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 '-DHSE_VALUE=8000000' '-DMSI_VALUE=4000000' '-DLSI_VALUE=32000' '-DHSE_STARTUP_TIMEOUT=100' '-DHSI_VALUE=16000000' '-DLSE_STARTUP_TIMEOUT=5000' '-DLSE_VALUE=32768' '-DDATA_CACHE_ENABLE=1' '-DVDD_VALUE=3300' '-DINSTRUCTION_CACHE_ENABLE=1' '-DEXTERNALSAI2_CLOCK_VALUE=2097000' -DSTM32L476xx -DUSE_FULL_LL_DRIVER '-DEXTERNALSAI1_CLOCK_VALUE=2097000' '-DPREFETCH_ENABLE=1' -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/opticalFlow.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/spi.o: ../Core/Src/spi.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 '-DHSE_VALUE=8000000' '-DMSI_VALUE=4000000' '-DLSI_VALUE=32000' '-DHSE_STARTUP_TIMEOUT=100' '-DHSI_VALUE=16000000' '-DLSE_STARTUP_TIMEOUT=5000' '-DLSE_VALUE=32768' '-DDATA_CACHE_ENABLE=1' '-DVDD_VALUE=3300' '-DINSTRUCTION_CACHE_ENABLE=1' '-DEXTERNALSAI2_CLOCK_VALUE=2097000' -DSTM32L476xx -DUSE_FULL_LL_DRIVER '-DEXTERNALSAI1_CLOCK_VALUE=2097000' '-DPREFETCH_ENABLE=1' -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/spi.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/stm32l4xx_it.o: ../Core/Src/stm32l4xx_it.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 '-DHSE_VALUE=8000000' '-DMSI_VALUE=4000000' '-DLSI_VALUE=32000' '-DHSE_STARTUP_TIMEOUT=100' '-DHSI_VALUE=16000000' '-DLSE_STARTUP_TIMEOUT=5000' '-DLSE_VALUE=32768' '-DDATA_CACHE_ENABLE=1' '-DVDD_VALUE=3300' '-DINSTRUCTION_CACHE_ENABLE=1' '-DEXTERNALSAI2_CLOCK_VALUE=2097000' -DSTM32L476xx -DUSE_FULL_LL_DRIVER '-DEXTERNALSAI1_CLOCK_VALUE=2097000' '-DPREFETCH_ENABLE=1' -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/stm32l4xx_it.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/syscalls.o: ../Core/Src/syscalls.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 '-DHSE_VALUE=8000000' '-DMSI_VALUE=4000000' '-DLSI_VALUE=32000' '-DHSE_STARTUP_TIMEOUT=100' '-DHSI_VALUE=16000000' '-DLSE_STARTUP_TIMEOUT=5000' '-DLSE_VALUE=32768' '-DDATA_CACHE_ENABLE=1' '-DVDD_VALUE=3300' '-DINSTRUCTION_CACHE_ENABLE=1' '-DEXTERNALSAI2_CLOCK_VALUE=2097000' -DSTM32L476xx -DUSE_FULL_LL_DRIVER '-DEXTERNALSAI1_CLOCK_VALUE=2097000' '-DPREFETCH_ENABLE=1' -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/syscalls.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/sysmem.o: ../Core/Src/sysmem.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 '-DHSE_VALUE=8000000' '-DMSI_VALUE=4000000' '-DLSI_VALUE=32000' '-DHSE_STARTUP_TIMEOUT=100' '-DHSI_VALUE=16000000' '-DLSE_STARTUP_TIMEOUT=5000' '-DLSE_VALUE=32768' '-DDATA_CACHE_ENABLE=1' '-DVDD_VALUE=3300' '-DINSTRUCTION_CACHE_ENABLE=1' '-DEXTERNALSAI2_CLOCK_VALUE=2097000' -DSTM32L476xx -DUSE_FULL_LL_DRIVER '-DEXTERNALSAI1_CLOCK_VALUE=2097000' '-DPREFETCH_ENABLE=1' -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/sysmem.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/system_stm32l4xx.o: ../Core/Src/system_stm32l4xx.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 '-DHSE_VALUE=8000000' '-DMSI_VALUE=4000000' '-DLSI_VALUE=32000' '-DHSE_STARTUP_TIMEOUT=100' '-DHSI_VALUE=16000000' '-DLSE_STARTUP_TIMEOUT=5000' '-DLSE_VALUE=32768' '-DDATA_CACHE_ENABLE=1' '-DVDD_VALUE=3300' '-DINSTRUCTION_CACHE_ENABLE=1' '-DEXTERNALSAI2_CLOCK_VALUE=2097000' -DSTM32L476xx -DUSE_FULL_LL_DRIVER '-DEXTERNALSAI1_CLOCK_VALUE=2097000' '-DPREFETCH_ENABLE=1' -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/system_stm32l4xx.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/tim.o: ../Core/Src/tim.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 '-DHSE_VALUE=8000000' '-DMSI_VALUE=4000000' '-DLSI_VALUE=32000' '-DHSE_STARTUP_TIMEOUT=100' '-DHSI_VALUE=16000000' '-DLSE_STARTUP_TIMEOUT=5000' '-DLSE_VALUE=32768' '-DDATA_CACHE_ENABLE=1' '-DVDD_VALUE=3300' '-DINSTRUCTION_CACHE_ENABLE=1' '-DEXTERNALSAI2_CLOCK_VALUE=2097000' -DSTM32L476xx -DUSE_FULL_LL_DRIVER '-DEXTERNALSAI1_CLOCK_VALUE=2097000' '-DPREFETCH_ENABLE=1' -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/tim.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/usart.o: ../Core/Src/usart.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 '-DHSE_VALUE=8000000' '-DMSI_VALUE=4000000' '-DLSI_VALUE=32000' '-DHSE_STARTUP_TIMEOUT=100' '-DHSI_VALUE=16000000' '-DLSE_STARTUP_TIMEOUT=5000' '-DLSE_VALUE=32768' '-DDATA_CACHE_ENABLE=1' '-DVDD_VALUE=3300' '-DINSTRUCTION_CACHE_ENABLE=1' '-DEXTERNALSAI2_CLOCK_VALUE=2097000' -DSTM32L476xx -DUSE_FULL_LL_DRIVER '-DEXTERNALSAI1_CLOCK_VALUE=2097000' '-DPREFETCH_ENABLE=1' -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/usart.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

