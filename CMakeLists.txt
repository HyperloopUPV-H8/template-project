cmake_minimum_required (VERSION 3.4)
project (template-project ASM C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(STLIB_DIR ${CMAKE_SOURCE_DIR}/../ST-LIB)
set(EXECUTABLE ${PROJECT_NAME}.elf)

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_subdirectory(${STLIB_DIR} ${STLIB_DIR}/build)
add_executable(${EXECUTABLE} 
  ${CMAKE_SOURCE_DIR}/Core/Src/main.cpp 
  ${CMAKE_SOURCE_DIR}/Core/Src/syscalls.c 
  ${CMAKE_SOURCE_DIR}/Core/Src/stm32h7xx_hal_msp.c
  ${CMAKE_SOURCE_DIR}/Core/Src/stm32h7xx_it.c
  ${CMAKE_SOURCE_DIR}/Core/Src/sysmem.c
  ${CMAKE_SOURCE_DIR}/Core/Src/system_stm32h7xx.c
  ${CMAKE_SOURCE_DIR}/Core/Startup/startup_stm32h723zgtx.s
  )
target_link_libraries(${EXECUTABLE} ${STLIB_DIR}/build/libst-lib.a)

target_compile_definitions(${EXECUTABLE} PUBLIC
  -DUSE_HAL_DRIVER
  -DSTM32H723xx
  -DDATA_IN_D2_SRAM
)


target_include_directories(${EXECUTABLE} PUBLIC
  ${CMAKE_SOURCE_DIR}/Core/Inc
  ${CMAKE_SOURCE_DIR}/Drivers/STM32H7xx_HAL_Driver/Inc
  ${CMAKE_SOURCE_DIR}/Drivers/STM32H7xx_HAL_Driver/Inc/Legacy
  ${CMAKE_SOURCE_DIR}/Drivers/CMSIS/Device/ST/STM32H7xx/Include
  ${CMAKE_SOURCE_DIR}/Drivers/CMSIS/Include
  ${CMAKE_SOURCE_DIR}/LWIP/App
  ${CMAKE_SOURCE_DIR}/LWIP/Target 
  ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/LwIP/src/include
  ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/LwIP/system
  ${CMAKE_SOURCE_DIR}/Drivers/BSP/components/lan8742
  ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/LwIP/src/include/netif/ppp
  ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/LwIP/src/include/lwip
  ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/LwIP/src/include/lwip/apps
  ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/LwIP/src/include/lwip/priv
  ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/LwIP/src/include/lwip/prot
  ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/LwIP/src/include/netif
  ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/LwIP/src/include/compat/posix
  ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/LwIP/src/include/compat/posix/arpa
  ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/LwIP/src/include/compat/posix/net
  ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/LwIP/src/include/compat/posix/sys
  ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/LwIP/src/include/compat/stdc
  ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/LwIP/system/arch
  ${STLIB_DIR}/Drivers/CMSIS/Device/ST/STM32H7xx/Include
  ${STLIB_DIR}/Drivers/CMSIS/Include
  ${STLIB_DIR}/Drivers/STM32H7xx_HAL_Driver/Inc
  ${STLIB_DIR}/Drivers/STM32H7xx_HAL_Driver/Inc/Legacy
  ${STLIB_DIR}/Middlewares/Third_Party/LwIP/src/include
  ${STLIB_DIR}/Middlewares/Third_Party/LwIP/system
  ${STLIB_DIR}/Middlewares/Third_Party/LwIP/src/netif/ppp
  ${STLIB_DIR}/Middlewares/Third_Party/LwIP/src/include/lwip
  ${STLIB_DIR}/Middlewares/Third_Party/LwIP/src/include/lwip/apps
  ${STLIB_DIR}/Middlewares/Third_Party/LwIP/src/include/lwip/priv
  ${STLIB_DIR}/Middlewares/Third_Party/LwIP/src/include/lwip/prot
  ${STLIB_DIR}/Middlewares/Third_Party/LwIP/src/include/netif
  ${STLIB_DIR}/Middlewares/Third_Party/LwIP/src/include/compat
  ${STLIB_DIR}/Middlewares/Third_Party/LwIP/src/include/compat/posix
  ${STLIB_DIR}/Middlewares/Third_Party/LwIP/src/include/compat/posix/arpa
  ${STLIB_DIR}/Middlewares/Third_Party/LwIP/src/include/compat/posix/net
  ${STLIB_DIR}/Middlewares/Third_Party/LwIP/src/include/compat/posix/sys
  ${STLIB_DIR}/Middlewares/Third_Party/LwIP/src/include/compat/stdc
  ${STLIB_DIR}/Middlewares/Third_Party/LwIP/system/arch
  ${STLIB_DIR}/Drivers/BSP/Components
  ${STLIB_DIR}/LWIP/App
  ${STLIB_DIR}/LWIP/Target
  ${STLIB_DIR}/Inc
  ${STLIB_DIR}/Inc/HALAL/Models
  ${STLIB_DIR}/Inc/HALAL/Services
  ${STLIB_DIR}/Inc/ST-LIB_LOW
  ${STLIB_DIR}/Inc/ST-LIB_HIGH
)


target_compile_options(${EXECUTABLE} PUBLIC
  -mcpu=cortex-m7
  -mfpu=fpv5-d16
  -mfloat-abi=hard
  -mthumb
  
  -O0
  -ffunction-sections
  -fdata-sections
  -fno-exceptions
  $<$<COMPILE_LANGUAGE:CXX:-fno-rtti>
  $<$<COMPILE_LANGUAGE:CXX:-fno-use-cxa-atexit>

  -Wall

  --specs=nosys.specs
)
target_link_options(${EXECUTABLE} PUBLIC 
        -T${CMAKE_SOURCE_DIR}/STM32H723ZGTX_FLASH.ld
        -mcpu=cortex-m7
        -mthumb
        -mfpu=fpv5-d16
        -mfloat-abi=hard
        -specs=nosys.specs
        -lc
        -lm
        -lnosys
        -Wl,-Map=${PROJECT_NAME}.map,--cref
        -Wl,--gc-sections
        )

# Print executable size
add_custom_command(TARGET ${EXECUTABLE}
        POST_BUILD
        COMMAND arm-none-eabi-size ${EXECUTABLE})

# Create hex file
add_custom_command(TARGET ${EXECUTABLE}
        POST_BUILD
        COMMAND arm-none-eabi-objcopy -O ihex ${EXECUTABLE} ${PROJECT_NAME}.hex
        COMMAND arm-none-eabi-objcopy -O binary ${EXECUTABLE} ${PROJECT_NAME}.bin)
