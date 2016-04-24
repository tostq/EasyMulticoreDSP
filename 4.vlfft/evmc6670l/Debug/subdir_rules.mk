################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
configPkg/compiler.opt: ../vlfft_evmc6670l.cfg
	@echo 'Building file: $<'
	@echo 'Invoking: XDCtools'
	"C:/Program Files/Texas Instruments/xdctools_3_23_01_43/xs" --xdcpath="C:/Program Files/Texas Instruments/ipc_1_24_02_27/packages;C:/Work/Customer/Massmarket/2012 0808 Shanghai  Beijing Hands on workshop/lab/vlfft/evmc6670l/../;C:/Program Files/Texas Instruments/bios_6_33_02_31/packages;C:/ti/edma3_lld_02_11_05_02/packages;C:/ti/mcsdk_2_00_09_21/demos;" xdc.tools.configuro -o configPkg -t ti.targets.elf.C66 -p custom.vlfft.evmc6670l.core0 -r debug -c "C:/ti/ccsv5/tools/compiler/c6000" "$<"
	@echo 'Finished building: $<'
	@echo ' '

configPkg/linker.cmd: configPkg/compiler.opt
configPkg/: configPkg/compiler.opt


