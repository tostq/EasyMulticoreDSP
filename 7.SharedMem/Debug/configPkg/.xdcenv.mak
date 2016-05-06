#
_XDCBUILDCOUNT = 
ifneq (,$(findstring path,$(_USEXDCENV_)))
override XDCPATH = D:/ti/bios_6_33_05_46/packages;D:/ti/ipc_1_24_03_32/packages;D:/ti/ccsv5/ccs_base
override XDCROOT = D:/ti/xdctools_3_23_03_53
override XDCBUILDCFG = ./config.bld
endif
ifneq (,$(findstring args,$(_USEXDCENV_)))
override XDCARGS = 
override XDCTARGETS = 
endif
#
ifeq (0,1)
PKGPATH = D:/ti/bios_6_33_05_46/packages;D:/ti/ipc_1_24_03_32/packages;D:/ti/ccsv5/ccs_base;D:/ti/xdctools_3_23_03_53/packages;..
HOSTOS = Windows
endif
