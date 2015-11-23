## THIS IS A GENERATED FILE -- DO NOT EDIT
.configuro: .libraries,e674 linker.cmd package/cfg/app_pe674.oe674

linker.cmd: package/cfg/app_pe674.xdl
	$(SED) 's"^\"\(package/cfg/app_pe674cfg.cmd\)\"$""\"D:/sound/tronlong/dsp/demo/SYSBIOS/Application/DSP_v8/.config/xconfig_app/\1\""' package/cfg/app_pe674.xdl > $@
