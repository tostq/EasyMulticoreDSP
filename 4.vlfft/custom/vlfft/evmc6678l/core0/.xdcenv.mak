#
_XDCBUILDCOUNT = 10
ifneq (,$(findstring path,$(_USEXDCENV_)))
override XDCPATH = 
override XDCROOT = C:/PROGRA~1/TEXASI~1/xdctools_3_20_08_88
override XDCBUILDCFG = ./config.bld
endif
ifneq (,$(findstring args,$(_USEXDCENV_)))
override XDCARGS = 
override XDCTARGETS = 
endif
#
ifeq (0,1)
PKGPATH = C:/PROGRA~1/TEXASI~1/xdctools_3_20_08_88/packages;../../../..
HOSTOS = Windows
endif
