################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := D:/ti/ccsv5/tools/compiler/c6000_7.3.4

ORDERED_OBJS += \
"./cv/cvutils.obj" \
"./cv/cvthresh.obj" \
"./cv/cvtables.obj" \
"./cv/cvsumpixels.obj" \
"./cv/cvshapedescr.obj" \
"./cv/cvpyramids.obj" \
"./cv/cvmorph.obj" \
"./cv/cvimgwarp.obj" \
"./cv/cvhaar.obj" \
"./cv/cvfilter.obj" \
"./cv/cvcontours.obj" \
"./cv/cvapprox.obj" \
"./cxcore/cxtables.obj" \
"./cxcore/cxsumpixels.obj" \
"./cxcore/cxouttext.obj" \
"./cxcore/cxerror.obj" \
"./cxcore/cxdrawing.obj" \
"./cxcore/cxdatastructs.obj" \
"./cxcore/cxcopy.obj" \
"./cxcore/cxcmp.obj" \
"./cxcore/cxarray.obj" \
"./cxcore/cxarithm.obj" \
"./cxcore/cxalloc.obj" \
"./highgui/loadsave.obj" \
"./highgui/cvcap_v4l.obj" \
"./highgui/cvcap.obj" \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include highgui/subdir_vars.mk
-include cxcore/subdir_vars.mk
-include cv/subdir_vars.mk
-include highgui/subdir_rules.mk
-include cxcore/subdir_rules.mk
-include cv/subdir_rules.mk
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
all: emcv.lib

# Tool invocations
emcv.lib: $(OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: C6000 Archiver'
	"D:/ti/ccsv5/tools/compiler/c6000_7.3.4/bin/ar6x" r "emcv.lib" $(ORDERED_OBJS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(C6000_LIBRARY_OUTPUTS__QUOTED) "emcv.lib"
	-$(RM) "highgui\cvcap.pp" "highgui\cvcap_v4l.pp" "highgui\loadsave.pp" "cxcore\cxalloc.pp" "cxcore\cxarithm.pp" "cxcore\cxarray.pp" "cxcore\cxcmp.pp" "cxcore\cxcopy.pp" "cxcore\cxdatastructs.pp" "cxcore\cxdrawing.pp" "cxcore\cxerror.pp" "cxcore\cxouttext.pp" "cxcore\cxsumpixels.pp" "cxcore\cxtables.pp" "cv\cvapprox.pp" "cv\cvcontours.pp" "cv\cvfilter.pp" "cv\cvhaar.pp" "cv\cvimgwarp.pp" "cv\cvmorph.pp" "cv\cvpyramids.pp" "cv\cvshapedescr.pp" "cv\cvsumpixels.pp" "cv\cvtables.pp" "cv\cvthresh.pp" "cv\cvutils.pp" 
	-$(RM) "highgui\cvcap.obj" "highgui\cvcap_v4l.obj" "highgui\loadsave.obj" "cxcore\cxalloc.obj" "cxcore\cxarithm.obj" "cxcore\cxarray.obj" "cxcore\cxcmp.obj" "cxcore\cxcopy.obj" "cxcore\cxdatastructs.obj" "cxcore\cxdrawing.obj" "cxcore\cxerror.obj" "cxcore\cxouttext.obj" "cxcore\cxsumpixels.obj" "cxcore\cxtables.obj" "cv\cvapprox.obj" "cv\cvcontours.obj" "cv\cvfilter.obj" "cv\cvhaar.obj" "cv\cvimgwarp.obj" "cv\cvmorph.obj" "cv\cvpyramids.obj" "cv\cvshapedescr.obj" "cv\cvsumpixels.obj" "cv\cvtables.obj" "cv\cvthresh.obj" "cv\cvutils.obj" 
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
