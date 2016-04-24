################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
vlfftApps/genTestData.obj: C:/Work/Customer/Massmarket/2012\ 0808\ Shanghai\ \ Beijing\ Hands\ on\ workshop/lab/vlfft/vlfftApps/genTestData.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"C:/ti/ccsv5/tools/compiler/c6000/bin/cl6x" -mv6600 --symdebug:none -O3 --define=ENABLE_SYSTEM_TRACE_LOGS --include_path="C:/Work/Customer/Massmarket/2012 0808 Shanghai  Beijing Hands on workshop/lab/vlfft/evmc6670l/../vlfftInc" --include_path="C:/ti/ccsv5/tools/compiler/c6000/include" --include_path="C:/development_tools/libraries/STMLib/include" --include_path="C:/development_tools/libraries/STMLib/src" --display_error_number --diag_warning=225 --abi=eabi --preproc_with_compile --preproc_dependency="vlfftApps/genTestData.pp" --obj_directory="vlfftApps" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

vlfftApps/system_trace.obj: C:/Work/Customer/Massmarket/2012\ 0808\ Shanghai\ \ Beijing\ Hands\ on\ workshop/lab/vlfft/vlfftApps/system_trace.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"C:/ti/ccsv5/tools/compiler/c6000/bin/cl6x" -mv6600 --symdebug:none -O3 --define=ENABLE_SYSTEM_TRACE_LOGS --include_path="C:/Work/Customer/Massmarket/2012 0808 Shanghai  Beijing Hands on workshop/lab/vlfft/evmc6670l/../vlfftInc" --include_path="C:/ti/ccsv5/tools/compiler/c6000/include" --include_path="C:/development_tools/libraries/STMLib/include" --include_path="C:/development_tools/libraries/STMLib/src" --display_error_number --diag_warning=225 --abi=eabi --preproc_with_compile --preproc_dependency="vlfftApps/system_trace.pp" --obj_directory="vlfftApps" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

vlfftApps/vlfftApps.obj: C:/Work/Customer/Massmarket/2012\ 0808\ Shanghai\ \ Beijing\ Hands\ on\ workshop/lab/vlfft/vlfftApps/vlfftApps.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"C:/ti/ccsv5/tools/compiler/c6000/bin/cl6x" -mv6600 --symdebug:none -O3 --define=ENABLE_SYSTEM_TRACE_LOGS --include_path="C:/Work/Customer/Massmarket/2012 0808 Shanghai  Beijing Hands on workshop/lab/vlfft/evmc6670l/../vlfftInc" --include_path="C:/ti/ccsv5/tools/compiler/c6000/include" --include_path="C:/development_tools/libraries/STMLib/include" --include_path="C:/development_tools/libraries/STMLib/src" --display_error_number --diag_warning=225 --abi=eabi --preproc_with_compile --preproc_dependency="vlfftApps/vlfftApps.pp" --obj_directory="vlfftApps" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


