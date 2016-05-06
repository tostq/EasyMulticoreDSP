################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CFG_SRCS += \
../SharedMemory.cfg 

C_SRCS += \
../SharedMemory.c 

OBJS += \
./SharedMemory.obj 

GEN_SRCS += \
./configPkg/compiler.opt \
./configPkg/linker.cmd 

C_DEPS += \
./SharedMemory.pp 

GEN_MISC_DIRS += \
./configPkg/ 

GEN_CMDS += \
./configPkg/linker.cmd 

GEN_OPTS += \
./configPkg/compiler.opt 

GEN_SRCS__QUOTED += \
"configPkg\compiler.opt" \
"configPkg\linker.cmd" 

GEN_MISC_DIRS__QUOTED += \
"configPkg\" 

C_DEPS__QUOTED += \
"SharedMemory.pp" 

OBJS__QUOTED += \
"SharedMemory.obj" 

C_SRCS__QUOTED += \
"../SharedMemory.c" 

CFG_SRCS__QUOTED += \
"../SharedMemory.cfg" 

GEN_OPTS__FLAG += \
--cmd_file="./configPkg/compiler.opt" 

GEN_CMDS__FLAG += \
-l"./configPkg/linker.cmd" 


