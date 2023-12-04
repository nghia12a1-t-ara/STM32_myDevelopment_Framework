# Warning with empty module
ifeq ($(MODULE),)
	$(error export MODULE before starting tests: example export MODULE=FLASH ...)
endif	

ifeq ($(TEST),)
	$(error export TEST before starting tests: example export TEST=FLASH_TS_001 ...)
endif

# Load to FLASH or RAM - Default Load to FLASH
ifeq ($(LOAD_TO),)
    LOAD_TO=FLASH
endif

PRO_DIR := .
PROJ_NAME := $(TEST)
DRIVER_DIR := $(PRO_DIR)/../STM32F4_Drivers
DRV_TEST_DIR := $(PRO_DIR)/../STM32F4_Driver_Testing
STARTUP_DIR := $(PRO_DIR)/startup
PYTHON_DIR := $(PRO_DIR)/testing/python
DEBUGGER_DIR := $(PRO_DIR)/../Debugger

include $(PRO_DIR)/User_Config.mak
include $(DRV_TEST_DIR)/test_$(MODULE)/make/$(TEST)

# Warning empty MODULE_LIST
ifeq ($(MODULE_LIST),)
	$(error Need add MODULE_LIST in make test)
endif

# include make and source test suite
SRC_DIRS += $(DRV_TEST_DIR)/test_$(MODULE)/$(TEST)/test_suite/src
SRC_DIRS += $(DRV_TEST_DIR)/test_$(MODULE)/$(TEST)/test_case/src
INC_DIRS += $(DRV_TEST_DIR)/test_$(MODULE)/$(TEST)/test_suite/inc
INC_DIRS += $(DRV_TEST_DIR)/test_$(MODULE)/$(TEST)/test_case/inc
SRC_DIRS += $(STARTUP_DIR)
INC_DIRS += $(STARTUP_DIR)

PATH_OUTPUT = $(DRV_TEST_DIR)/output

# Testing source framework
INC_DIRS += $(PRO_DIR)/testing/TestCUnit/inc
SRC_DIRS += $(PRO_DIR)/testing/TestCUnit/src

############### Add source/header file to build ###############
find_files_inc = $(DRIVER_DIR)/$(MODULES)/inc
find_files_src = $(DRIVER_DIR)/$(MODULES)/src
gen_files_inc = $(DRIVER_DIR)/$(MODULES)/Generate/inc
gen_files_src = $(DRIVER_DIR)/$(MODULES)/Generate/src
DRV_INC_DIRS := $(foreach MODULES,$(MODULE_LIST),$(find_files_inc))
DRV_SRC_DIRS := $(foreach MODULES,$(MODULE_LIST),$(find_files_src))
GEN_INC_DIRS := $(foreach MODULES,$(GENERATE_LIST),$(gen_files_inc))
GEN_SRC_DIRS := $(foreach MODULES,$(GENERATE_LIST),$(gen_files_src))
INC_DIRS += $(DRV_INC_DIRS)
SRC_DIRS += $(DRV_SRC_DIRS)
INC_DIRS += $(GEN_INC_DIRS)
SRC_DIRS += $(GEN_SRC_DIRS)

SRC_FILES := $(foreach SRC_DIRS, $(SRC_DIRS),$(wildcard $(SRC_DIRS)/*))
INC_FILES := $(foreach INC_DIRS, $(INC_DIRS),$(wildcard $(INC_DIRS)/*))
LINKER_FILE := $(PRO_DIR)/linker/stm32f4xx_linker_$(LOAD_TO).ld

# Compiler and linker flags
CC := $(COMPILER_DIR)/bin/arm-none-eabi-gcc
LD := $(COMPILER_DIR)/bin/arm-none-eabi-ld

INC_DIRS_OPT := $(foreach INC_DIRS,$(INC_DIRS),-I$(INC_DIRS))

# Compiler and linker option
CC_OPT := -mcpu=cortex-m4 -c -std=gnu11 -o0 -g3 $(INC_DIRS_OPT) -ffunction-sections -fdata-sections -Wall -fstack-usage --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -DLOAD_TO_$(LOAD_TO)
LD_OPT := -T $(LINKER_FILE) -Map $(PATH_OUTPUT)/$(PROJ_NAME).map -static

OJB_FILES := $(notdir $(SRC_FILES))
OJB_FILES := $(subst .c,.o,$(OJB_FILES))
PATH_OJBS := $(foreach OJB_FILES,$(OJB_FILES),$(PATH_OUTPUT)/$(OJB_FILES))

vpath %.c $(SRC_DIRS)
vpath %.h $(INC_DIRS)

# Build output file -elf -hex
build: $(OJB_FILES) $(LINKER_FILE)
	$(LD) $(LD_OPT) $(PATH_OJBS) -o $(PATH_OUTPUT)/$(PROJ_NAME).elf
	$(COMPILER_DIR)/arm-none-eabi/bin/objcopy.exe -O ihex "$(PATH_OUTPUT)/$(PROJ_NAME).elf" "$(PATH_OUTPUT)/$(PROJ_NAME).hex"
	size $(PATH_OUTPUT)/$(PROJ_NAME).elf
	
%.o: %.c $(INC_FILES)
	$(CC) $(CC_OPT) -c $< -o $(PATH_OUTPUT)/$@
	
# Clean all output files
.PHONY:clean
clean:
	rm -rf $(PATH_OUTPUT)/*.o $(PATH_OUTPUT)/*.su $(PATH_OUTPUT)/*.elf $(PATH_OUTPUT)/*.hex $(PATH_OUTPUT)/*.bin $(PATH_OUTPUT)/*.log $(PATH_OUTPUT)/*.map

# Run Test with Board
.PHONY:run
run:
	# remove report file
	rm -fr $(PATH_OUTPUT)/$(TEST).xml
	rm -fr $(PATH_OUTPUT)/result.log
    
	$(PRO_DIR)/debug/ST-LINKUtility/ST-LINK_CLI.exe -ME
	$(PRO_DIR)/debug/ST-LINKUtility/ST-LINK_CLI.exe -p "$(PATH_OUTPUT)/$(PROJ_NAME).hex" 0x08000000
	$(PRO_DIR)/debug/ST-LINKUtility/ST-LINK_CLI.exe -rst
	
	# read data from <TEST> address to check test case -> export result to log file
	@$(PRO_DIR)/debug/ST-LINKUtility/ST-LINK_CLI.exe -r32 0x20000000 4 | grep -i 00000000 > $(PATH_OUTPUT)/result.log
	
# Export report
.PHONY:report
report:
	if [[ -s $(PATH_OUTPUT)/result.log ]]; then \
		echo "Test $(TEST) is PASSED "; \
		cp $(PRO_DIR)/testing/Report_Template/Pass/Template.xml $(PATH_OUTPUT)/$(TEST).xml; \
		sed -i 's/TEST_NAME/$(TEST)/g' $(PATH_OUTPUT)/$(TEST).xml; \
		sed -i 's/TEST_DISCRIPTION/$(TEST_DETAILS)/g' $(PATH_OUTPUT)/$(TEST).xml; \
	else \
		echo "Test $(TEST) is FAILED "; \
		cp $(PRO_DIR)/testing/Report_Template/Fail/Template.xml $(PATH_OUTPUT)/$(TEST).xml; \
		sed -i 's/TEST_NAME/$(TEST)/g' $(PATH_OUTPUT)/$(TEST).xml; \
		sed -i 's/TEST_DISCRIPTION/$(TEST_DETAILS)/g' $(PATH_OUTPUT)/$(TEST).xml; \
	fi
	@$(PRO_DIR)/debug/ST-LINKUtility/ST-LINK_CLI.exe -rst
    
# .PHONY:debug
# debug:
    # $(DEBUGGER_DIR)/openocd/bin/openocd.exe -f $(DEBUGGER_DIR)/openocd/scripts/board/st_nucleo_f4.cfg

# list all test suite
.PHONY:info
info:
	@ls $(DRV_TEST_DIR)/test_$(MODULE)/make
	
print-%:
	@echo $($(subst print-,,$@))

py: $(PYTHON_DIR)/xmldata.py
	python $<
