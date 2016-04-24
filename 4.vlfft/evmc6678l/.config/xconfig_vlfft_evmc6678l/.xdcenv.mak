#
_XDCBUILDCOUNT = 0
ifneq (,$(findstring path,$(_USEXDCENV_)))
override XDCPATH = D:/ti/ipc_1_24_03_32/packages;D:/ti/mcsdk_2_01_02_06/demos/vlfft;D:/ti/bios_6_33_05_46/packages;D:/ti/edma3_lld_02_11_05_02/packages;D:/ti/mcsdk_2_01_02_06/demos;D:/ti/ccsv5/ccs_base;D:/ti/mcsdk_2_01_02_06/demos/vlfft/evmc6678l/.config
override XDCROOT = D:/ti/xdctools_3_23_03_53
override XDCBUILDCFG = ./config.bld
endif
ifneq (,$(findstring args,$(_USEXDCENV_)))
override XDCARGS = 
override XDCTARGETS = 
endif
#
ifeq (0,1)
PKGPATH = D:/ti/ipc_1_24_03_32/packages;D:/ti/mcsdk_2_01_02_06/demos/vlfft;D:/ti/bios_6_33_05_46/packages;D:/ti/edma3_lld_02_11_05_02/packages;D:/ti/mcsdk_2_01_02_06/demos;D:/ti/ccsv5/ccs_base;D:/ti/mcsdk_2_01_02_06/demos/vlfft/evmc6678l/.config;D:/ti/xdctools_3_23_03_53/packages;..
HOSTOS = Windows
endif
