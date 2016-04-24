################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
vlfftEDMA/vlfftEdmaConfig.obj: C:/Work/Customer/Massmarket/2012\ 0808\ Shanghai\ \ Beijing\ Hands\ on\ workshop/lab/vlfft/vlfftEDMA/vlfftEdmaConfig.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"C:/ti/ccsv5/tools/compiler/c6000/bin/cl6x" -mv6600 --symdebug:none -O3 --include_path="C:/ti/ccsv5/tools/compiler/c6000/include" --include_path="/include" --include_path="/src" --display_error_number --diag_warning=225 --abi=eabi --preproc_with_compile --preproc_dependency="vlfftEDMA/vlfftEdmaConfig.pp" --obj_directory="vlfftEDMA" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

vlfftEDMA/vlfftEdmaInit.obj: C:/Work/Customer/Massmarket/2012\ 0808\ Shanghai\ \ Beijing\ Hands\ on\ workshop/lab/vlfft/vlfftEDMA/vlfftEdmaInit.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"C:/ti/ccsv5/tools/compiler/c6000/bin/cl6x" -mv6600 --symdebug:none -O3 --include_path="C:/ti/ccsv5/tools/compiler/c6000/include" --include_path="/include" --include_path="/src" --display_error_number --diag_warning=225 --abi=eabi --preproc_with_compile --preproc_dependency="vlfftEDMA/vlfftEdmaInit.pp" --obj_directory="vlfftEDMA" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


