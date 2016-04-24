################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
STMHelper.obj: C:/development_tools/libraries/STMLib/src/STMHelper.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"D:/ti/ccsv5/tools/compiler/c6000_7.3.4/bin/cl6x" -mv6600 --symdebug:none -O3 --define=ENABLE_SYSTEM_TRACE_LOGS --include_path="D:/ti/mcsdk_2_01_02_06/demos/vlfft/vlfftInc" --include_path="D:/ti/ccsv5/tools/compiler/c6000_7.3.4/include" --include_path="C:/development_tools/libraries/STMLib/include" --include_path="C:/development_tools/libraries/STMLib/src" --display_error_number --diag_warning=225 --abi=eabi --preproc_with_compile --preproc_dependency="STMHelper.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

configPkg/compiler.opt: ../vlfft_evmc6678l.cfg
	@echo 'Building file: $<'
	@echo 'Invoking: XDCtools'
	"D:/ti/xdctools_3_23_03_53/xs" --xdcpath="D:/ti/ipc_1_24_03_32/packages;D:/ti/mcsdk_2_01_02_06/demos/vlfft/;D:/ti/bios_6_33_05_46/packages;D:/ti/edma3_lld_02_11_05_02/packages;D:/ti/mcsdk_2_01_02_06/demos;D:/ti/ccsv5/ccs_base;" xdc.tools.configuro -o configPkg -t ti.targets.elf.C66 -p custom.vlfft.evmc6678l.core0 -r debug -c "D:/ti/ccsv5/tools/compiler/c6000_7.3.4" "$<"
	@echo 'Finished building: $<'
	@echo ' '

configPkg/linker.cmd: configPkg/compiler.opt
configPkg/: configPkg/compiler.opt


