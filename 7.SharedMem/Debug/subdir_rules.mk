################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
SharedMemory.obj: ../SharedMemory.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"D:/ti/C6000 Code Generation Tools 7.4.2/bin/cl6x" -mv6600 --abi=eabi -g --include_path="D:/ti/C6000 Code Generation Tools 7.4.2/include" --include_path="D:/ti/ccsv5/tools/compiler/c6000_7.3.4/include" --display_error_number --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="SharedMemory.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

configPkg/compiler.opt: ../SharedMemory.cfg
	@echo 'Building file: $<'
	@echo 'Invoking: XDCtools'
	"D:/ti/xdctools_3_23_03_53/xs" --xdcpath="D:/ti/bios_6_33_05_46/packages;D:/ti/ipc_1_24_03_32/packages;D:/ti/ccsv5/ccs_base;" xdc.tools.configuro -o configPkg -t ti.targets.elf.C66 -p ti.platforms.evm6678 -r release -c "D:/ti/C6000 Code Generation Tools 7.4.2" --compileOptions "-g --optimize_with_debug" "$<"
	@echo 'Finished building: $<'
	@echo ' '

configPkg/linker.cmd: configPkg/compiler.opt
configPkg/: configPkg/compiler.opt


