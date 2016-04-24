################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CFG_SRCS += \
../vlfft_evmc6678l.cfg 

C_SRCS += \
C:/development_tools/libraries/STMLib/src/STMHelper.c 

OBJS += \
./STMHelper.obj 

GEN_SRCS += \
./configPkg/compiler.opt \
./configPkg/linker.cmd 

C_DEPS += \
./STMHelper.pp 

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
"STMHelper.pp" 

OBJS__QUOTED += \
"STMHelper.obj" 

C_SRCS__QUOTED += \
"C:/development_tools/libraries/STMLib/src/STMHelper.c" 

CFG_SRCS__QUOTED += \
"../vlfft_evmc6678l.cfg" 

GEN_OPTS__FLAG += \
--cmd_file="./configPkg/compiler.opt" 

GEN_CMDS__FLAG += \
-l"./configPkg/linker.cmd" 


