cmake_minimum_required (VERSION 3.4)

if(${SIMULATE})
  include(linux-64.cmake)
  add_definitions(-DSIM_ON)
else()
  include(arm-none-eabi.cmake)
endif()
  

project (template-project ASM C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(EXECUTABLE ${PROJECT_NAME}.elf)

file(GLOB_RECURSE SOURCE_C ${CMAKE_SOURCE_DIR}/Core/*.c ${CMAKE_SOURCE_DIR}/Drivers/*.c ${CMAKE_SOURCE_DIR}/Middlewares/*.c ${CMAKE_SOURCE_DIR}/LWIP/*.c) 
file(GLOB_RECURSE SOURCE_CPP ${CMAKE_SOURCE_DIR}/Core/*.cpp ${CMAKE_SOURCE_DIR}/Drivers/*.cpp ${CMAKE_SOURCE_DIR}/Middlewares/*.cpp ${CMAKE_SOURCE_DIR}/LWIP/*.cpp) 
file(GLOB_RECURSE SOURCE_H ${CMAKE_SOURCE_DIR}/Core/*.h ${CMAKE_SOURCE_DIR}/Drivers/*.h ${CMAKE_SOURCE_DIR}/Middlewares/*.h ${CMAKE_SOURCE_DIR}/LWIP/*.h) 
file(GLOB_RECURSE SOURCE_HPP ${CMAKE_SOURCE_DIR}/Core/*.hpp ${CMAKE_SOURCE_DIR}/Drivers/*.hpp ${CMAKE_SOURCE_DIR}/Middlewares/*.hpp ${CMAKE_SOURCE_DIR}/LWIP/*.hpp) 

set(STLIB_DIR "$ENV{STLIB_PATH}")

if(${NUCLEO})
  add_definitions(-DNUCLEO)
  add_definitions(-DHSE_VALUE=8000000)
else()
  add_definitions(-DBOARD)
  add_definitions(-DHSE_VALUE=25000000)
endif()

if(${RELEASE} STREQUAL "Release")
  set(OPTIMIZATION -O3)
  set(DEBUG_CONFIGURATION -g0)
  set(STLIB_LIBRARY ${STLIB_DIR}/build/Release)
elseif(${RELEASE} STREQUAL "ReleaseDebug")
  set(OPTIMIZATION -O3)
  set(DEBUG_CONFIGURATION -g3)
  set(STLIB_LIBRARY ${STLIB_DIR}/build/ReleaseDebug)
else()
  set(OPTIMIZATION -O0)
  set(DEBUG_CONFIGURATION -g3)
  set(STLIB_LIBRARY ${STLIB_DIR}/build/Simulator/Debug/NUCLEO/NoEthernet) #This way by the moment just for compile
endif()

add_executable(${EXECUTABLE} 
  ${SOURCE_C}
  ${SOURCE_CPP}
  ${SOURCE_H}
  ${SOURCE_HPP}
  $<$<STREQUAL:${SIMULATE},FALSE>:Core/Startup/startup_stm32h723zgtx.s>
  )

target_link_libraries(${EXECUTABLE} PUBLIC ${STLIB_LIBRARY}/libst-lib.a)

target_compile_definitions(${EXECUTABLE} PUBLIC
  -DUSE_HAL_DRIVER
  -DSTM32H723xx
  -DDATA_IN_D2_SRAM
)

message("\n\nCMAKE:\n")
message(STATUS "[Debug, Release, ReleaseDebug]: " ${RELEASE})
message(STATUS "Optimization value: " ${OPTIMIZATION})
message(STATUS "Debug configuration value: " ${DEBUG_CONFIGURATION})
message(STATUS "[BOARD, NUCLEO] Config: NUCLEO: " ${NUCLEO})

target_compile_options(${EXECUTABLE} PUBLIC
  $<$<STREQUAL:${SIMULATE},FALSE>:-mcpu=cortex-m7>
  $<$<STREQUAL:${SIMULATE},FALSE>:-mfpu=fpv5-d16>
  $<$<STREQUAL:${SIMULATE},FALSE>:-mfloat-abi=hard>
  $<$<STREQUAL:${SIMULATE},FALSE>:-mthumb>
  ${OPTIMIZATION}
  ${DEBUG_CONFIGURATION}
  -ffunction-sections
  -fdata-sections
  -fno-exceptions
  ## disable Warnings for C files, this is Driver code from ST
  $<$<COMPILE_LANGUAGE:C>:-w>
  $<$<COMPILE_LANGUAGE:CXX>:-fno-use-cxa-atexit>
  $<$<COMPILE_LANGUAGE:CXX>:-fno-rtti>
  $<$<COMPILE_LANGUAGE:CXX>:-Wall>
  $<$<COMPILE_LANGUAGE:CXX>:-Wpedantic>
  $<$<COMPILE_LANGUAGE:CXX>:-Werror>
  -Wno-psabi
  $<$<STREQUAL:${SIMULATE},FALSE>:-specs=nosys.specs>
)

# REMEMBER TO CHANGE `.vscode/C_cpp_properties.json` TO MATCH THIS LIST
target_include_directories(${EXECUTABLE} PUBLIC
  Core/Inc
  $<$<STREQUAL:${SIMULATE},FALSE>:${STLIB_DIR}/Drivers/CMSIS/Device/ST/STM32H7xx/Include>
  $<$<STREQUAL:${SIMULATE},FALSE>:${STLIB_DIR}/Drivers/CMSIS/Include>
  $<$<STREQUAL:${SIMULATE},FALSE>:${STLIB_DIR}/Drivers/STM32H7xx_HAL_Driver/Inc>
  $<$<STREQUAL:${SIMULATE},FALSE>:${STLIB_DIR}/Drivers/STM32H7xx_HAL_Driver/Inc/Legacy>
  $<$<STREQUAL:${SIMULATE},FALSE>:${STLIB_DIR}/Middlewares/Third_Party/LwIP/src/include>
  $<$<STREQUAL:${SIMULATE},FALSE>:${STLIB_DIR}/Middlewares/Third_Party/LwIP/system>
  $<$<STREQUAL:${SIMULATE},FALSE>:${STLIB_DIR}/Middlewares/Third_Party/LwIP/src/netif/ppp>
  $<$<STREQUAL:${SIMULATE},FALSE>:${STLIB_DIR}/Middlewares/Third_Party/LwIP/src/include/lwip>
  $<$<STREQUAL:${SIMULATE},FALSE>:${STLIB_DIR}/Middlewares/Third_Party/LwIP/src/include/lwip/apps>
  $<$<STREQUAL:${SIMULATE},FALSE>:${STLIB_DIR}/Middlewares/Third_Party/LwIP/src/include/lwip/priv>
  $<$<STREQUAL:${SIMULATE},FALSE>:${STLIB_DIR}/Middlewares/Third_Party/LwIP/src/include/lwip/prot>
  $<$<STREQUAL:${SIMULATE},FALSE>:${STLIB_DIR}/Middlewares/Third_Party/LwIP/src/include/netif>
  $<$<STREQUAL:${SIMULATE},FALSE>:${STLIB_DIR}/Middlewares/Third_Party/LwIP/src/include/compat>
  $<$<STREQUAL:${SIMULATE},FALSE>:${STLIB_DIR}/Middlewares/Third_Party/LwIP/src/include/compat/posix>
  $<$<STREQUAL:${SIMULATE},FALSE>:${STLIB_DIR}/Middlewares/Third_Party/LwIP/src/include/compat/posix/arpa>
  $<$<STREQUAL:${SIMULATE},FALSE>:${STLIB_DIR}/Middlewares/Third_Party/LwIP/src/include/compat/posix/net>
  $<$<STREQUAL:${SIMULATE},FALSE>:${STLIB_DIR}/Middlewares/Third_Party/LwIP/src/include/compat/posix/sys>
  $<$<STREQUAL:${SIMULATE},FALSE>:${STLIB_DIR}/Middlewares/Third_Party/LwIP/src/include/compat/stdc>
  $<$<STREQUAL:${SIMULATE},FALSE>:${STLIB_DIR}/Middlewares/Third_Party/LwIP/system/arch>
  $<$<STREQUAL:${SIMULATE},FALSE>:${STLIB_DIR}/Drivers/BSP/Components>
  $<$<STREQUAL:${SIMULATE},FALSE>:${STLIB_DIR}/Drivers/BSP/Components/lan8742>
  $<$<STREQUAL:${SIMULATE},FALSE>:${STLIB_DIR}/LWIP/App>
  $<$<STREQUAL:${SIMULATE},FALSE>:${STLIB_DIR}/LWIP/Target>
  ${STLIB_DIR}/Inc
  ${STLIB_DIR}/Inc/HALAL
  ${STLIB_DIR}/Inc/HALALMock
  ${STLIB_DIR}/Inc/HALAL/Models
  ${STLIB_DIR}/Inc/HALAL/Services
  ${STLIB_DIR}/Inc/ST-LIB_LOW
  ${STLIB_DIR}/Inc/ST-LIB_HIGH
)
if(!${SIMULATE})
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
endif()
