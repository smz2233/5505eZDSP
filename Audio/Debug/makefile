################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := D:/Mao/software/ccs1260/ccs/tools/compiler/c5500_4.4.1

GEN_OPTS__FLAG := 
GEN_CMDS__FLAG := 

ORDERED_OBJS += \
"./src/IIR_filters_fourth_order.obj" \
"./src/PLL.obj" \
"./src/SweepGenerator.obj" \
"./src/aic3204.obj" \
"./src/aic3204_init.obj" \
"./src/main.obj" \
"./src/sinewaves.obj" \
"./src/stereo.obj" \
"./src/timer.obj" \
"./src/usbstk5505.obj" \
"./src/usbstk5505_gpio.obj" \
"./src/usbstk5505_i2c.obj" \
"../55xdsph.lib" \
"../CSLc55x5h.lib" \
"../lnkx.cmd" \
$(GEN_CMDS__FLAG) \
-llibc.a \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include src/subdir_vars.mk
-include subdir_rules.mk
-include src/subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(INO_DEPS)),)
-include $(INO_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(SV7A_DEPS)),)
-include $(SV7A_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(PDE_DEPS)),)
-include $(PDE_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXE_OUTPUTS += \
Audio.out 

EXE_OUTPUTS__QUOTED += \
"Audio.out" 


# All Target
all: Audio.out

# Tool invocations
Audio.out: $(OBJS) $(CMD_SRCS) $(LIB_SRCS) $(GEN_CMDS)
	@echo 'Building target: "$@"'
	@echo 'Invoking: C5500 Linker'
	"D:/Mao/software/ccs1260/ccs/tools/compiler/c5500_4.4.1/bin/cl55" -v5505 --memory_model=huge -g --define=_DEBUG --define=c5545 --diag_warning=225 --ptrdiff_size=32 --algebraic --asm_source=algebraic -z -m"Audio.map" --stack_size=0x200 --heap_size=0x400 -i"D:/Mao/software/ccs1260/ccs/tools/compiler/c5500_4.4.1/lib" -i"D:/Mao/software/ccs1260/ccs/tools/compiler/c5500_4.4.1/include" -i"C:/ti/bios_5_42_02_10/packages/ti/rtdx/lib/c5500" -i"C:/ti/bios_5_42_02_10/packages/ti/bios/lib" -i"D:/Mao/software/ccs1260/ccs/workspace/TMS320VC5505/Audio" --reread_libs --warn_sections --xml_link_info="Audio_linkInfo.xml" --rom_model --sys_stacksize=0x200 -o "Audio.out" $(ORDERED_OBJS)
	@echo 'Finished building target: "$@"'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(EXE_OUTPUTS__QUOTED)
	-$(RM) "src\IIR_filters_fourth_order.obj" "src\PLL.obj" "src\SweepGenerator.obj" "src\aic3204.obj" "src\aic3204_init.obj" "src\main.obj" "src\sinewaves.obj" "src\stereo.obj" "src\timer.obj" "src\usbstk5505.obj" "src\usbstk5505_gpio.obj" "src\usbstk5505_i2c.obj" 
	-$(RM) "src\IIR_filters_fourth_order.d" "src\PLL.d" "src\SweepGenerator.d" "src\aic3204.d" "src\aic3204_init.d" "src\main.d" "src\sinewaves.d" "src\stereo.d" "src\timer.d" "src\usbstk5505.d" "src\usbstk5505_gpio.d" "src\usbstk5505_i2c.d" 
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

