################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CFG_SRCS += \
../app.cfg 

LIB_SRCS += \
../uPP.lib 

C_SRCS += \
../active_noise_ctr.c \
../dsp_fpga_emifa.c \
../dsp_fpga_notify.c \
../main.c \
../uPP.c \
../utils.c 

OBJS += \
./active_noise_ctr.obj \
./dsp_fpga_emifa.obj \
./dsp_fpga_notify.obj \
./main.obj \
./uPP.obj \
./utils.obj 

C_DEPS += \
./active_noise_ctr.pp \
./dsp_fpga_emifa.pp \
./dsp_fpga_notify.pp \
./main.pp \
./uPP.pp \
./utils.pp 

GEN_MISC_DIRS += \
./configPkg/ 

GEN_CMDS += \
./configPkg/linker.cmd 

GEN_OPTS += \
./configPkg/compiler.opt 

GEN_FILES += \
./configPkg/linker.cmd \
./configPkg/compiler.opt 

GEN_FILES__QUOTED += \
"configPkg\linker.cmd" \
"configPkg\compiler.opt" 

GEN_MISC_DIRS__QUOTED += \
"configPkg\" 

C_DEPS__QUOTED += \
"active_noise_ctr.pp" \
"dsp_fpga_emifa.pp" \
"dsp_fpga_notify.pp" \
"main.pp" \
"uPP.pp" \
"utils.pp" 

OBJS__QUOTED += \
"active_noise_ctr.obj" \
"dsp_fpga_emifa.obj" \
"dsp_fpga_notify.obj" \
"main.obj" \
"uPP.obj" \
"utils.obj" 

C_SRCS__QUOTED += \
"../active_noise_ctr.c" \
"../dsp_fpga_emifa.c" \
"../dsp_fpga_notify.c" \
"../main.c" \
"../uPP.c" \
"../utils.c" 

GEN_CMDS__FLAG += \
-l"./configPkg/linker.cmd" 

GEN_OPTS__FLAG += \
--cmd_file="./configPkg/compiler.opt" 


