################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
vlfftEDMA/vlfftEdmaConfig.obj: D:/ti/mcsdk_2_01_02_06/demos/vlfft/vlfftEDMA/vlfftEdmaConfig.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"D:/ti/ccsv5/tools/compiler/c6000_7.3.4/bin/cl6x" -mv6600 --symdebug:none -O3 --include_path="D:/ti/ccsv5/tools/compiler/c6000_7.3.4/include" --include_path="D:/ti/STMLib/include" --include_path="D:/ti/STMLib/src" --display_error_number --diag_warning=225 --abi=eabi --preproc_with_compile --preproc_dependency="vlfftEDMA/vlfftEdmaConfig.pp" --obj_directory="vlfftEDMA" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

vlfftEDMA/vlfftEdmaInit.obj: D:/ti/mcsdk_2_01_02_06/demos/vlfft/vlfftEDMA/vlfftEdmaInit.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"D:/ti/ccsv5/tools/compiler/c6000_7.3.4/bin/cl6x" -mv6600 --symdebug:none -O3 --include_path="D:/ti/ccsv5/tools/compiler/c6000_7.3.4/include" --include_path="D:/ti/STMLib/include" --include_path="D:/ti/STMLib/src" --display_error_number --diag_warning=225 --abi=eabi --preproc_with_compile --preproc_dependency="vlfftEDMA/vlfftEdmaInit.pp" --obj_directory="vlfftEDMA" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


