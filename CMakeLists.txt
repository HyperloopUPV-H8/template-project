cmake_minimum_required (VERSION 3.4)

include(arm-none-eabi.cmake)

project (template-project ASM C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(EXECUTABLE ${PROJECT_NAME}.elf)

file(GLOB_RECURSE SOURCE_C ${CMAKE_SOURCE_DIR}/Core/*.c ${CMAKE_SOURCE_DIR}/Drivers/*.c ${CMAKE_SOURCE_DIR}/Middlewares/*.c ${CMAKE_SOURCE_DIR}/LWIP/*.c) 
file(GLOB_RECURSE SOURCE_CPP ${CMAKE_SOURCE_DIR}/Core/*.cpp ${CMAKE_SOURCE_DIR}/Drivers/*.cpp ${CMAKE_SOURCE_DIR}/Middlewares/*.cpp ${CMAKE_SOURCE_DIR}/LWIP/*.cpp) 
file(GLOB_RECURSE SOURCE_H ${CMAKE_SOURCE_DIR}/Core/*.h ${CMAKE_SOURCE_DIR}/Drivers/*.h ${CMAKE_SOURCE_DIR}/Middlewares/*.h ${CMAKE_SOURCE_DIR}/LWIP/*.h) 
file(GLOB_RECURSE SOURCE_HPP ${CMAKE_SOURCE_DIR}/Core/*.hpp ${CMAKE_SOURCE_DIR}/Drivers/*.hpp ${CMAKE_SOURCE_DIR}/Middlewares/*.hpp ${CMAKE_SOURCE_DIR}/LWIP/*.hpp) 

set(STLIB_DIR "/opt/ST-LIB")

if(${NUCLEO})
  add_definitions(-DNUCLEO)
  add_definitions(-DHSE_VALUE=8000000)
else()
  add_definitions(-DBOARD)
  add_definitions(-DHSE_VALUE=25000000)
endif()

if(${RELEASE})
  set(OPTIMIZATION -O3)
  set(DEBUG_CONFIGURATION -g0)
  set(STLIB_LIBRARY ${STLIB_DIR}/build/Release/lib)
else()
  set(OPTIMIZATION -O0)
  set(DEBUG_CONFIGURATION -g3)
  set(STLIB_LIBRARY ${STLIB_DIR}/build/Debug/lib)
endif()

add_executable(${EXECUTABLE} 
  ${SOURCE_C}
  ${SOURCE_CPP}
  ${SOURCE_H}
  ${SOURCE_HPP}
  Core/Startup/startup_stm32h723zgtx.s
  )

target_link_libraries(${EXECUTABLE} PUBLIC ${STLIB_LIBRARY}/libst-lib.a)

target_compile_definitions(${EXECUTABLE} PUBLIC
  -DUSE_HAL_DRIVER
  -DSTM32H723xx
  -DDATA_IN_D2_SRAM
)

message("\n\nCMAKE:\n")
message(STATUS "[DEBUG, RELEASE]: RELEASE: " ${RELEASE})
message(STATUS "Optimization value: " ${OPTIMIZATION})
message(STATUS "Debug configuration value: " ${DEBUG_CONFIGURATION})
message(STATUS "[BOARD, NUCLEO] Config: NUCLEO: " ${NUCLEO})

target_compile_options(${EXECUTABLE} PUBLIC
  -mcpu=cortex-m7
  -mfpu=fpv5-d16
  -mfloat-abi=hard
  -mthumb
  ${OPTIMIZATION}
  ${DEBUG_CONFIGURATION}
  -ffunction-sections
  -fdata-sections
  -fno-exceptions
  $<$<COMPILE_LANGUAGE:CXX>:-fno-use-cxa-atexit>
  $<$<COMPILE_LANGUAGE:CXX>:-fno-rtti>

  -Wall
  -specs=nosys.specs
)

target_include_directories(${EXECUTABLE} PUBLIC
  Drivers/CMSIS/Device/ST/STM32H7xx/Include
  Drivers/CMSIS/Include
  Drivers/STM32H7xx_HAL_Driver/Inc
  Drivers/STM32H7xx_HAL_Driver/Inc/Legacy
  Middlewares/Third_Party/LwIP/src/include
  Middlewares/Third_Party/LwIP/system
  Middlewares/Third_Party/LwIP/src/netif/ppp
  Middlewares/Third_Party/LwIP/src/include/lwip
  Middlewares/Third_Party/LwIP/src/include/lwip/apps
  Middlewares/Third_Party/LwIP/src/include/lwip/priv
  Middlewares/Third_Party/LwIP/src/include/lwip/prot
  Middlewares/Third_Party/LwIP/src/include/netif
  Middlewares/Third_Party/LwIP/src/include/compat
  Middlewares/Third_Party/LwIP/src/include/compat/posix
  Middlewares/Third_Party/LwIP/src/include/compat/posix/arpa
  Middlewares/Third_Party/LwIP/src/include/compat/posix/net
  Middlewares/Third_Party/LwIP/src/include/compat/posix/sys
  Middlewares/Third_Party/LwIP/src/include/compat/stdc
  Middlewares/Third_Party/LwIP/system/arch
  Middlewares/Third_Party/
  Drivers/BSP/Components
  Drivers/BSP/Components/lan8742
  LWIP/App
  LWIP/Target
  Core/Inc
  ${STLIB_DIR}/Inc
  ${STLIB_DIR}/Inc/HALAL/Models
  ${STLIB_DIR}/Inc/HALAL/Services
  ${STLIB_DIR}/Inc/ST-LIB_LOW
  ${STLIB_DIR}/Inc/ST-LIB_HIGH
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
