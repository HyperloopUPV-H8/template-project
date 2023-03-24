cmake_minimum_required (VERSION 3.4)
project (template-project)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(STLIB_DIR ../ST-LIB)
set(EXECUTABLE ${PROJECT_NAME}.elf)

add_subdirectory(${STLIB_DIR} ${STLIB_DIR}/build)
add_executable(${EXECUTABLE} ../Core/Src/main.cpp)
target_link_libraries(${EXECUTABLE} ${STLIB_DIR}/build/libST-LIB.a)

target_compile_definitions(${EXECUTABLE} PUBLIC
  -DUSE_HAL_DRIVER
  -DSTM32H723xx
  -DDATA_IN_D2_SRAM
)

target_include_directories(${EXECUTABLE} PUBLIC
  Core/Inc
  Drivers/STM32H7xx_HAL_Driver/Inc
  Drivers/STM32H7xx_HAL_Driver/Inc/Legacy
  Drivers/CMSIS/Device/ST/STM32H7xx/Include
  Drivers/CMSIS/Include
  LWIP/App
  LWIP/Target 
  Middlewares/Third_Party/LwIP/src/include
  Middlewares/Third_Party/LwIP/system
  Drivers/BSP/components/lan8742
  Middlewares/Third_Party/LwIP/src/include/netif/ppp
  Middlewares/Third_Party/LwIP/src/include/lwip
  Middlewares/Third_Party/LwIP/src/include/lwip/apps
  Middlewares/Third_Party/LwIP/src/include/lwip/priv
  Middlewares/Third_Party/LwIP/src/include/lwip/prot
  Middlewares/Third_Party/LwIP/src/include/netif
  Middlewares/Third_Party/LwIP/src/include/compat/posix
  Middlewares/Third_Party/LwIP/src/include/compat/posix/arpa
  Middlewares/Third_Party/LwIP/src/include/compat/posix/net
  Middlewares/Third_Party/LwIP/src/include/compat/posix/sys
  Middlewares/Third_Party/LwIP/src/include/compat/stdc
  Middlewares/Third_Party/LwIP/system/arch
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

# Print executable size
add_custom_command(TARGET ${EXECUTABLE}
        POST_BUILD
        COMMAND arm-none-eabi-size ${EXECUTABLE})

# Create hex file
add_custom_command(TARGET ${EXECUTABLE}
        POST_BUILD
        COMMAND arm-none-eabi-objcopy -O ihex ${EXECUTABLE} ${PROJECT_NAME}.hex
        COMMAND arm-none-eabi-objcopy -O binary ${EXECUTABLE} ${PROJECT_NAME}.bin)
