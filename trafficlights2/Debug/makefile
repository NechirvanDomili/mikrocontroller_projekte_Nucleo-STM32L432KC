################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Drivers/STM32L4xx_HAL_Driver/Src/subdir.mk
-include Core/Startup/subdir.mk
-include Core/Src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
trafficlights2.elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
trafficlights2.list \

OBJCOPY_BIN += \
trafficlights2.bin \


# All Target
all: trafficlights2.elf secondary-outputs

# Tool invocations
trafficlights2.elf: $(OBJS) $(USER_OBJS) C:\Users\nechi\STM32CubeIDE\workspace_1.3.0\trafficlights2\STM32L432KCUX_FLASH.ld
	arm-none-eabi-gcc -o "trafficlights2.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m4 -T"C:\Users\nechi\STM32CubeIDE\workspace_1.3.0\trafficlights2\STM32L432KCUX_FLASH.ld" --specs=nosys.specs -Wl,-Map="trafficlights2.map" -Wl,--gc-sections -static --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

trafficlights2.list: $(EXECUTABLES)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "trafficlights2.list"
	@echo 'Finished building: $@'
	@echo ' '

trafficlights2.bin: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "trafficlights2.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_BIN)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
