#!/bin/bash

echo "Enter Target (nucleo|n / board|b) : "
read TARGET

start=`date +%s.%N`

rm -R CMakeCache.txt compile_commands.json cmake_install.cmake Makefile CMakeFiles

if [[ $* == *--NOETH* ]]
then
  ETH="NOETH"
else
  ETH="HAL_ETH_MODULE_ENABLED"
fi

if ([ $TARGET = "board" ] || [ $TARGET = "b" ] || [ $TARGET = "B" ] || [ $TARGET = "Board" ] || [ $TARGET = "BOARD" ])
then
  TARGET="BOARD"
else
  if ([ $TARGET = "nucleo" ] || [ $TARGET = "n" ] || [ $TARGET = "N" ] || [ $TARGET = "Nucleo" ]  || [ $TARGET = "NUCLEO" ])
  then
    TARGET="NUCLEO"
  else
    echo "Wrong value, exiting"
    exit 1
  fi
fi

cmake -DCMAKE_TOOLCHAIN_FILE=arm-none-eabi.cmake -D${TARGET}=ON -D${ETH}=ON .
make -j16 all

end=`date +%s.%N`
runtime=$( echo "$end - $start" | bc -l )

RED='\033[1;31m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color
EXECUTABLE=template-project.elf
PROJECT_NAME=template-project


printf "\n\n\n${RED}%25s${NC} built!\n\n" ${PROJECT_NAME}

printf "${RED}%20s ${NC}: ${YELLOW}\t%s\n" Target ${TARGET}
printf "${RED}%20s ${NC}: ${YELLOW}\t%ss\n" Compile $runtime
printf "\n"
arm-none-eabi-objcopy -O ihex ${EXECUTABLE} ${PROJECT_NAME}.hex
arm-none-eabi-objcopy -O binary ${EXECUTABLE} ${PROJECT_NAME}.bin

