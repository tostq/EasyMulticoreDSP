################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
notify_multicore.obj: ../notify_multicore.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"D:/ti/ccsv5/tools/compiler/c6000_7.3.4/bin/cl6x" -mv6600 -g --include_path="D:/ti/ccsv5/tools/compiler/c6000_7.3.4/include" --display_error_number --diag_warning=225 --abi=eabi --preproc_with_compile --preproc_dependency="notify_multicore.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

configPkg/compiler.opt: ../notify_multicore.cfg
	@echo 'Building file: $<'
	@echo 'Invoking: XDCtools'
	"D:/ti/xdctools_3_23_03_53/xs" --xdcpath="D:/ti/ipc_1_24_03_32/packages;D:/ti/bios_6_33_05_46/packages;D:/ti/ccsv5/ccs_base;" xdc.tools.configuro -o configPkg -t ti.targets.elf.C66 -p ti.sdo.ipc.examples.platforms.evm6678.core0 -r release -c "D:/ti/ccsv5/tools/compiler/c6000_7.3.4" --compileOptions "-g --optimize_with_debug" "$<"
	@echo 'Finished building: $<'
	@echo ' '

configPkg/linker.cmd: configPkg/compiler.opt
configPkg/: configPkg/compiler.opt


