#!/bin/bash

PROJECT_NAME=template-project
EXECUTABLE=template-project.elf


echo "Enter Target (nucleo|n / board|b) : "
read TARGET

start=`date +%s.%N`


if [[ $* == *--NOETH* ]]
then
  ETH="NOETH"
else
  ETH="HAL_ETH_MODULE_ENABLED"
fi

if [[ $* == *--DEBUG* ]]
then
  DEBUG="-g3"
else
  DEBUG="-g0"
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

cmake -DCMAKE_TOOLCHAIN_FILE=arm-none-eabi.cmake -DDEBUG:STRING=${DEBUG} -D${TARGET}=ON -D${ETH}=ON ..
make -j16 all
RET_STATUS=$(echo "$?")

end=`date +%s.%N`
runtime=$( echo "$end - $start" | bc -l )

arm-none-eabi-objcopy -O binary ${EXECUTABLE} ${PROJECT_NAME}.bin

RED='\033[1;31m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color


if [[ $RET_STATUS == 0 ]]
then
  printf "\n\n\n${RED}%25s${NC} built!\n\n" ${PROJECT_NAME}
else
  printf "\n\n\n${RED}%15s${NC} not built correctly, errors ocurred.\n\n" ${PROJECT_NAME}
fi

printf "${RED}%20s ${NC}: ${YELLOW}\t%s\n" Target ${TARGET}
printf "${RED}%20s ${NC}: ${YELLOW}\t%ss\n" Compile $runtime
if ([ $ETH = "NOETH" ])
then
  printf "${RED}%20s ${NC}: ${YELLOW}\t%s\n" Ethernet OFF
fi
printf "\n"

if ([ $DEBUG = "-g3" ])
then
  printf "${RED}%20s ${NC}: ${YELLOW}\t%s\n" Debug ON 
else
  printf "${RED}%20s ${NC}: ${YELLOW}\t%s\n" Debug OFF
fi
printf "\n"

printf "${RED}%20s ${NC}: ${YELLOW}\t%s\n" Warnings ${WARNINGS}

printf "\n\n"

rm -R .cmake CMakeCache.txt cmake_install.cmake Makefile CMakeFiles template-project.map template-project.hex &>/dev/null
mv compile_commands.json ..
