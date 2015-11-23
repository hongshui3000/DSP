################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
active_noise_ctr.obj: ../active_noise_ctr.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"C:/ti/ccsv5/tools/compiler/c6000_7.4.4/bin/cl6x" -mv6740 --abi=eabi -g --include_path="../../../Include/StarterWare/Drivers" --include_path="D:/sound/tronlong/dsp/demo/SYSBIOS/Include/MathLib" --include_path="D:/sound/tronlong/dsp/demo/SYSBIOS/Include/DSPLib" --include_path="../../../Include/StarterWare/Drivers/hw" --include_path="../../../Include/StarterWare/Grlib/" --include_path="../../../Include/StarterWare/Usblib/" --include_path="../../../Include/StarterWare/Drivers/c674x" --include_path="../../../Include/StarterWare/Drivers/c674x/c6748" --include_path="C:/ti/ccsv5/tools/compiler/c6000_7.4.4/include" --define=c6748 --display_error_number --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="active_noise_ctr.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

configPkg/linker.cmd: ../app.cfg
	@echo 'Building file: $<'
	@echo 'Invoking: XDCtools'
	"C:/ti/xdctools_3_25_03_72/xs" --xdcpath="C:/ti/bios_6_37_03_30/packages;D:/sound/tronlong/dsp/demo/SYSBIOS/Platform;C:/ti/ccsv5/ccs_base;C:/ti/tirtos_c2000_2_00_02_36/packages;C:/ti/tirtos_c2000_2_00_02_36/products/bios_6_40_02_27/packages;C:/ti/tirtos_c2000_2_00_02_36/products/ipc_3_10_01_11/packages;C:/ti/tirtos_c2000_2_00_02_36/products/ndk_2_23_01_01/packages;C:/ti/tirtos_c2000_2_00_02_36/products/uia_2_00_01_34/packages;" xdc.tools.configuro -o configPkg -t ti.targets.elf.C674 -p ti.platforms.evm6748 -r debug -c "C:/ti/ccsv5/tools/compiler/c6000_7.4.4" "$<"
	@echo 'Finished building: $<'
	@echo ' '

configPkg/compiler.opt: | configPkg/linker.cmd
configPkg/: | configPkg/linker.cmd

dsp_fpga_emifa.obj: ../dsp_fpga_emifa.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"C:/ti/ccsv5/tools/compiler/c6000_7.4.4/bin/cl6x" -mv6740 --abi=eabi -g --include_path="../../../Include/StarterWare/Drivers" --include_path="D:/sound/tronlong/dsp/demo/SYSBIOS/Include/MathLib" --include_path="D:/sound/tronlong/dsp/demo/SYSBIOS/Include/DSPLib" --include_path="../../../Include/StarterWare/Drivers/hw" --include_path="../../../Include/StarterWare/Grlib/" --include_path="../../../Include/StarterWare/Usblib/" --include_path="../../../Include/StarterWare/Drivers/c674x" --include_path="../../../Include/StarterWare/Drivers/c674x/c6748" --include_path="C:/ti/ccsv5/tools/compiler/c6000_7.4.4/include" --define=c6748 --display_error_number --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="dsp_fpga_emifa.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

dsp_fpga_notify.obj: ../dsp_fpga_notify.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"C:/ti/ccsv5/tools/compiler/c6000_7.4.4/bin/cl6x" -mv6740 --abi=eabi -g --include_path="../../../Include/StarterWare/Drivers" --include_path="D:/sound/tronlong/dsp/demo/SYSBIOS/Include/MathLib" --include_path="D:/sound/tronlong/dsp/demo/SYSBIOS/Include/DSPLib" --include_path="../../../Include/StarterWare/Drivers/hw" --include_path="../../../Include/StarterWare/Grlib/" --include_path="../../../Include/StarterWare/Usblib/" --include_path="../../../Include/StarterWare/Drivers/c674x" --include_path="../../../Include/StarterWare/Drivers/c674x/c6748" --include_path="C:/ti/ccsv5/tools/compiler/c6000_7.4.4/include" --define=c6748 --display_error_number --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="dsp_fpga_notify.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

main.obj: ../main.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"C:/ti/ccsv5/tools/compiler/c6000_7.4.4/bin/cl6x" -mv6740 --abi=eabi -g --include_path="../../../Include/StarterWare/Drivers" --include_path="D:/sound/tronlong/dsp/demo/SYSBIOS/Include/MathLib" --include_path="D:/sound/tronlong/dsp/demo/SYSBIOS/Include/DSPLib" --include_path="../../../Include/StarterWare/Drivers/hw" --include_path="../../../Include/StarterWare/Grlib/" --include_path="../../../Include/StarterWare/Usblib/" --include_path="../../../Include/StarterWare/Drivers/c674x" --include_path="../../../Include/StarterWare/Drivers/c674x/c6748" --include_path="C:/ti/ccsv5/tools/compiler/c6000_7.4.4/include" --define=c6748 --display_error_number --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="main.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

uPP.obj: ../uPP.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"C:/ti/ccsv5/tools/compiler/c6000_7.4.4/bin/cl6x" -mv6740 --abi=eabi -g --include_path="../../../Include/StarterWare/Drivers" --include_path="D:/sound/tronlong/dsp/demo/SYSBIOS/Include/MathLib" --include_path="D:/sound/tronlong/dsp/demo/SYSBIOS/Include/DSPLib" --include_path="../../../Include/StarterWare/Drivers/hw" --include_path="../../../Include/StarterWare/Grlib/" --include_path="../../../Include/StarterWare/Usblib/" --include_path="../../../Include/StarterWare/Drivers/c674x" --include_path="../../../Include/StarterWare/Drivers/c674x/c6748" --include_path="C:/ti/ccsv5/tools/compiler/c6000_7.4.4/include" --define=c6748 --display_error_number --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="uPP.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

utils.obj: ../utils.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"C:/ti/ccsv5/tools/compiler/c6000_7.4.4/bin/cl6x" -mv6740 --abi=eabi -g --include_path="../../../Include/StarterWare/Drivers" --include_path="D:/sound/tronlong/dsp/demo/SYSBIOS/Include/MathLib" --include_path="D:/sound/tronlong/dsp/demo/SYSBIOS/Include/DSPLib" --include_path="../../../Include/StarterWare/Drivers/hw" --include_path="../../../Include/StarterWare/Grlib/" --include_path="../../../Include/StarterWare/Usblib/" --include_path="../../../Include/StarterWare/Drivers/c674x" --include_path="../../../Include/StarterWare/Drivers/c674x/c6748" --include_path="C:/ti/ccsv5/tools/compiler/c6000_7.4.4/include" --define=c6748 --display_error_number --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="utils.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


