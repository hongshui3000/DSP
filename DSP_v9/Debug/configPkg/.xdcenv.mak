#
_XDCBUILDCOUNT = 
ifneq (,$(findstring path,$(_USEXDCENV_)))
override XDCPATH = C:/ti/bios_6_37_03_30/packages;D:/sound/tronlong/dsp/demo/SYSBIOS/Platform;C:/ti/ccsv5/ccs_base;C:/ti/tirtos_c2000_2_00_02_36/packages;C:/ti/tirtos_c2000_2_00_02_36/products/bios_6_40_02_27/packages;C:/ti/tirtos_c2000_2_00_02_36/products/ipc_3_10_01_11/packages;C:/ti/tirtos_c2000_2_00_02_36/products/ndk_2_23_01_01/packages;C:/ti/tirtos_c2000_2_00_02_36/products/uia_2_00_01_34/packages
override XDCROOT = C:/ti/xdctools_3_25_03_72
override XDCBUILDCFG = ./config.bld
endif
ifneq (,$(findstring args,$(_USEXDCENV_)))
override XDCARGS = 
override XDCTARGETS = 
endif
#
ifeq (0,1)
PKGPATH = C:/ti/bios_6_37_03_30/packages;D:/sound/tronlong/dsp/demo/SYSBIOS/Platform;C:/ti/ccsv5/ccs_base;C:/ti/tirtos_c2000_2_00_02_36/packages;C:/ti/tirtos_c2000_2_00_02_36/products/bios_6_40_02_27/packages;C:/ti/tirtos_c2000_2_00_02_36/products/ipc_3_10_01_11/packages;C:/ti/tirtos_c2000_2_00_02_36/products/ndk_2_23_01_01/packages;C:/ti/tirtos_c2000_2_00_02_36/products/uia_2_00_01_34/packages;C:/ti/xdctools_3_25_03_72/packages;..
HOSTOS = Windows
endif
