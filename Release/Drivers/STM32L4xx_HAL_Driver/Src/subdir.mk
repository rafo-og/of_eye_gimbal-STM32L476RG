################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_ll_dma.c \
../Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_ll_exti.c \
../Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_ll_gpio.c \
../Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_ll_pwr.c \
../Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_ll_rcc.c \
../Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_ll_spi.c \
../Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_ll_tim.c \
../Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_ll_usart.c \
../Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_ll_utils.c 

OBJS += \
./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_ll_dma.o \
./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_ll_exti.o \
./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_ll_gpio.o \
./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_ll_pwr.o \
./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_ll_rcc.o \
./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_ll_spi.o \
./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_ll_tim.o \
./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_ll_usart.o \
./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_ll_utils.o 

C_DEPS += \
./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_ll_dma.d \
./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_ll_exti.d \
./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_ll_gpio.d \
./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_ll_pwr.d \
./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_ll_rcc.d \
./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_ll_spi.d \
./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_ll_tim.d \
./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_ll_usart.d \
./Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_ll_utils.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_ll_dma.o: ../Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_ll_dma.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 '-DHSE_VALUE=8000000' '-DMSI_VALUE=4000000' '-DLSI_VALUE=32000' '-DHSE_STARTUP_TIMEOUT=100' '-DHSI_VALUE=16000000' '-DLSE_STARTUP_TIMEOUT=5000' '-DLSE_VALUE=32768' '-DDATA_CACHE_ENABLE=1' '-DVDD_VALUE=3300' '-DINSTRUCTION_CACHE_ENABLE=1' '-DEXTERNALSAI2_CLOCK_VALUE=2097000' -DSTM32L476xx -DUSE_FULL_LL_DRIVER '-DEXTERNALSAI1_CLOCK_VALUE=2097000' '-DPREFETCH_ENABLE=1' -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_ll_dma.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_ll_exti.o: ../Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_ll_exti.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 '-DHSE_VALUE=8000000' '-DMSI_VALUE=4000000' '-DLSI_VALUE=32000' '-DHSE_STARTUP_TIMEOUT=100' '-DHSI_VALUE=16000000' '-DLSE_STARTUP_TIMEOUT=5000' '-DLSE_VALUE=32768' '-DDATA_CACHE_ENABLE=1' '-DVDD_VALUE=3300' '-DINSTRUCTION_CACHE_ENABLE=1' '-DEXTERNALSAI2_CLOCK_VALUE=2097000' -DSTM32L476xx -DUSE_FULL_LL_DRIVER '-DEXTERNALSAI1_CLOCK_VALUE=2097000' '-DPREFETCH_ENABLE=1' -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_ll_exti.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_ll_gpio.o: ../Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_ll_gpio.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 '-DHSE_VALUE=8000000' '-DMSI_VALUE=4000000' '-DLSI_VALUE=32000' '-DHSE_STARTUP_TIMEOUT=100' '-DHSI_VALUE=16000000' '-DLSE_STARTUP_TIMEOUT=5000' '-DLSE_VALUE=32768' '-DDATA_CACHE_ENABLE=1' '-DVDD_VALUE=3300' '-DINSTRUCTION_CACHE_ENABLE=1' '-DEXTERNALSAI2_CLOCK_VALUE=2097000' -DSTM32L476xx -DUSE_FULL_LL_DRIVER '-DEXTERNALSAI1_CLOCK_VALUE=2097000' '-DPREFETCH_ENABLE=1' -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_ll_gpio.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_ll_pwr.o: ../Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_ll_pwr.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 '-DHSE_VALUE=8000000' '-DMSI_VALUE=4000000' '-DLSI_VALUE=32000' '-DHSE_STARTUP_TIMEOUT=100' '-DHSI_VALUE=16000000' '-DLSE_STARTUP_TIMEOUT=5000' '-DLSE_VALUE=32768' '-DDATA_CACHE_ENABLE=1' '-DVDD_VALUE=3300' '-DINSTRUCTION_CACHE_ENABLE=1' '-DEXTERNALSAI2_CLOCK_VALUE=2097000' -DSTM32L476xx -DUSE_FULL_LL_DRIVER '-DEXTERNALSAI1_CLOCK_VALUE=2097000' '-DPREFETCH_ENABLE=1' -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_ll_pwr.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_ll_rcc.o: ../Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_ll_rcc.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 '-DHSE_VALUE=8000000' '-DMSI_VALUE=4000000' '-DLSI_VALUE=32000' '-DHSE_STARTUP_TIMEOUT=100' '-DHSI_VALUE=16000000' '-DLSE_STARTUP_TIMEOUT=5000' '-DLSE_VALUE=32768' '-DDATA_CACHE_ENABLE=1' '-DVDD_VALUE=3300' '-DINSTRUCTION_CACHE_ENABLE=1' '-DEXTERNALSAI2_CLOCK_VALUE=2097000' -DSTM32L476xx -DUSE_FULL_LL_DRIVER '-DEXTERNALSAI1_CLOCK_VALUE=2097000' '-DPREFETCH_ENABLE=1' -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_ll_rcc.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_ll_spi.o: ../Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_ll_spi.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 '-DHSE_VALUE=8000000' '-DMSI_VALUE=4000000' '-DLSI_VALUE=32000' '-DHSE_STARTUP_TIMEOUT=100' '-DHSI_VALUE=16000000' '-DLSE_STARTUP_TIMEOUT=5000' '-DLSE_VALUE=32768' '-DDATA_CACHE_ENABLE=1' '-DVDD_VALUE=3300' '-DINSTRUCTION_CACHE_ENABLE=1' '-DEXTERNALSAI2_CLOCK_VALUE=2097000' -DSTM32L476xx -DUSE_FULL_LL_DRIVER '-DEXTERNALSAI1_CLOCK_VALUE=2097000' '-DPREFETCH_ENABLE=1' -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_ll_spi.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_ll_tim.o: ../Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_ll_tim.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 '-DHSE_VALUE=8000000' '-DMSI_VALUE=4000000' '-DLSI_VALUE=32000' '-DHSE_STARTUP_TIMEOUT=100' '-DHSI_VALUE=16000000' '-DLSE_STARTUP_TIMEOUT=5000' '-DLSE_VALUE=32768' '-DDATA_CACHE_ENABLE=1' '-DVDD_VALUE=3300' '-DINSTRUCTION_CACHE_ENABLE=1' '-DEXTERNALSAI2_CLOCK_VALUE=2097000' -DSTM32L476xx -DUSE_FULL_LL_DRIVER '-DEXTERNALSAI1_CLOCK_VALUE=2097000' '-DPREFETCH_ENABLE=1' -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_ll_tim.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_ll_usart.o: ../Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_ll_usart.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 '-DHSE_VALUE=8000000' '-DMSI_VALUE=4000000' '-DLSI_VALUE=32000' '-DHSE_STARTUP_TIMEOUT=100' '-DHSI_VALUE=16000000' '-DLSE_STARTUP_TIMEOUT=5000' '-DLSE_VALUE=32768' '-DDATA_CACHE_ENABLE=1' '-DVDD_VALUE=3300' '-DINSTRUCTION_CACHE_ENABLE=1' '-DEXTERNALSAI2_CLOCK_VALUE=2097000' -DSTM32L476xx -DUSE_FULL_LL_DRIVER '-DEXTERNALSAI1_CLOCK_VALUE=2097000' '-DPREFETCH_ENABLE=1' -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_ll_usart.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_ll_utils.o: ../Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_ll_utils.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 '-DHSE_VALUE=8000000' '-DMSI_VALUE=4000000' '-DLSI_VALUE=32000' '-DHSE_STARTUP_TIMEOUT=100' '-DHSI_VALUE=16000000' '-DLSE_STARTUP_TIMEOUT=5000' '-DLSE_VALUE=32768' '-DDATA_CACHE_ENABLE=1' '-DVDD_VALUE=3300' '-DINSTRUCTION_CACHE_ENABLE=1' '-DEXTERNALSAI2_CLOCK_VALUE=2097000' -DSTM32L476xx -DUSE_FULL_LL_DRIVER '-DEXTERNALSAI1_CLOCK_VALUE=2097000' '-DPREFETCH_ENABLE=1' -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_ll_utils.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

