################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := D:/ti/ccsv5/tools/compiler/c6000_7.3.4

ORDERED_OBJS += \
$(GEN_CMDS__FLAG) \
"./vlfftApps/vlfftApps.obj" \
"./vlfftApps/system_trace.obj" \
"./vlfftApps/genTestData.obj" \
"./vlfftEDMA/vlfftEdmaInit.obj" \
"./vlfftEDMA/vlfftEdmaConfig.obj" \
"./vlfftSrc/vlfft_2ndIter.obj" \
"./vlfftSrc/vlfft_1stIter.obj" \
"./vlfftSrc/vlfftUtil.obj" \
"./vlfftSrc/vlfftParamsInit.obj" \
"./vlfftSrc/tsc_h.obj" \
"./vlfftSrc/transpose_2Rows_8XCols_cplxMatrix_sa.obj" \
"./vlfftSrc/transpose_2Cols_rowsX8_cplxMatrix_sa.obj" \
"./vlfftSrc/multiTwiddle_1_sa.obj" \
"./vlfftSrc/multTwiddle.obj" \
"./vlfftSrc/messgQUtil.obj" \
"./vlfftSrc/genTwiddle.obj" \
"./vlfftSrc/dmaParamInit.obj" \
"./vlfftSrc/dft.obj" \
"./vlfftSrc/DSPF_sp_radix4_fftSPxSP.obj" \
"./vlfftSrc/DSPF_sp_mixedRadix_fftSPXSP.obj" \
"./STMHelper.obj" \
-ledma3_lld_drv.ae66 \
-lstm_d.c66xx_elf.lib \
-ledma3_lld_drv_sample.ae66 \
-ledma3_lld_rm.ae66 \
-l"libc.a" \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include vlfftSrc/subdir_vars.mk
-include vlfftEDMA/subdir_vars.mk
-include vlfftApps/subdir_vars.mk
-include subdir_rules.mk
-include vlfftSrc/subdir_rules.mk
-include vlfftEDMA/subdir_rules.mk
-include vlfftApps/subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: vlfft_evmc6678l.out

# Tool invocations
vlfft_evmc6678l.out: $(OBJS) $(GEN_CMDS)
	@echo 'Building target: $@'
	@echo 'Invoking: C6000 Linker'
	"D:/ti/ccsv5/tools/compiler/c6000_7.3.4/bin/cl6x" -mv6600 --symdebug:none -O3 --define=ENABLE_SYSTEM_TRACE_LOGS --display_error_number --diag_warning=225 --abi=eabi -z -m"vlfft_evmc6678l.map" --warn_sections -i"D:/ti/ccsv5/tools/compiler/c6000_7.3.4/lib" -i"C:/development_tools/libraries/STMLib/lib" -i"D:/ti/ccsv5/tools/compiler/c6000_7.3.4/include" -i"D:/ti/edma3_lld_02_11_05_02/packages/ti/sdo/edma3/drv/lib/66/release" -i"D:/ti/edma3_lld_02_11_05_02/packages/ti/sdo/edma3/rm/lib/c6678-evm/66/release" -i"D:/ti/edma3_lld_02_11_05_02/packages/ti/sdo/edma3/drv/sample/lib/c6678-evm/66/release" --reread_libs --rom_model -o "vlfft_evmc6678l.out" $(ORDERED_OBJS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(GEN_SRCS__QUOTED)$(GEN_MISC_FILES__QUOTED)$(C6000_EXECUTABLE_OUTPUTS__QUOTED)$(GEN_OPTS__QUOTED)$(GEN_CMDS__QUOTED) "vlfft_evmc6678l.out"
	-$(RMDIR) $(GEN_MISC_DIRS__QUOTED)
	-$(RM) "STMHelper.pp" "vlfftSrc\dft.pp" "vlfftSrc\dmaParamInit.pp" "vlfftSrc\genTwiddle.pp" "vlfftSrc\messgQUtil.pp" "vlfftSrc\multTwiddle.pp" "vlfftSrc\vlfftParamsInit.pp" "vlfftSrc\vlfftUtil.pp" "vlfftSrc\vlfft_1stIter.pp" "vlfftSrc\vlfft_2ndIter.pp" "vlfftEDMA\vlfftEdmaConfig.pp" "vlfftEDMA\vlfftEdmaInit.pp" "vlfftApps\genTestData.pp" "vlfftApps\system_trace.pp" "vlfftApps\vlfftApps.pp" 
	-$(RM) "STMHelper.obj" "vlfftSrc\DSPF_sp_mixedRadix_fftSPXSP.obj" "vlfftSrc\DSPF_sp_radix4_fftSPxSP.obj" "vlfftSrc\dft.obj" "vlfftSrc\dmaParamInit.obj" "vlfftSrc\genTwiddle.obj" "vlfftSrc\messgQUtil.obj" "vlfftSrc\multTwiddle.obj" "vlfftSrc\multiTwiddle_1_sa.obj" "vlfftSrc\transpose_2Cols_rowsX8_cplxMatrix_sa.obj" "vlfftSrc\transpose_2Rows_8XCols_cplxMatrix_sa.obj" "vlfftSrc\tsc_h.obj" "vlfftSrc\vlfftParamsInit.obj" "vlfftSrc\vlfftUtil.obj" "vlfftSrc\vlfft_1stIter.obj" "vlfftSrc\vlfft_2ndIter.obj" "vlfftEDMA\vlfftEdmaConfig.obj" "vlfftEDMA\vlfftEdmaInit.obj" "vlfftApps\genTestData.obj" "vlfftApps\system_trace.obj" "vlfftApps\vlfftApps.obj" 
	-$(RM) "vlfftSrc\DSPF_sp_mixedRadix_fftSPXSP.pp" "vlfftSrc\multiTwiddle_1_sa.pp" "vlfftSrc\transpose_2Cols_rowsX8_cplxMatrix_sa.pp" "vlfftSrc\transpose_2Rows_8XCols_cplxMatrix_sa.pp" 
	-$(RM) "vlfftSrc\DSPF_sp_radix4_fftSPxSP.pp" "vlfftSrc\tsc_h.pp" 
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
