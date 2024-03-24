################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
src/%.obj: ../src/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C5500 Compiler'
	"D:/Mao/software/ccs1260/ccs/tools/compiler/c5500_4.4.1/bin/cl55" -v5505 --memory_model=huge -g --include_path="D:/Mao/software/ccs1260/ccs/tools/compiler/c5500_4.4.1/include" --include_path="C:/ti/bios_5_42_02_10/packages/ti/bios/include" --include_path="C:/ti/bios_5_42_02_10/packages/ti/rtdx/include/c5500" --include_path="D:/Mao/software/ccs1260/ccs/workspace/TMS320VC5505/Audio/inc" --include_path="D:/Mao/software/ccs1260/ccs/workspace/TMS320VC5505/Audio/Debug" --define=_DEBUG --define=c5545 --diag_warning=225 --ptrdiff_size=32 --algebraic --asm_source=algebraic --preproc_with_compile --preproc_dependency="src/$(basename $(<F)).d_raw" --obj_directory="src" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


