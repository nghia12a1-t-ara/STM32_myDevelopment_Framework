PROJ_NAME := Queue
OBJ_FILES = out/main.o 
OBJ_FILES += out/$(PROJ_NAME).o

LIB_DIRS = ./../../STM32F4_Middleware/Queue
SRC_DIRS := $(LIB_DIRS)/src
INC_DIRS := $(LIB_DIRS)/inc
STD_LIBS = $(LIB_DIRS)/../../STM32F4_Drivers/BASE/inc

all: build

out/main.o:main.c
	@gcc -c -I./$(INC_DIRS) -I$(STD_LIBS) main.c -o out/main.o -DC_QUEUE_TEST
out/$(PROJ_NAME).o:$(SRC_DIRS)/$(PROJ_NAME).c
	@gcc -c -I./$(INC_DIRS) -I$(STD_LIBS) $(SRC_DIRS)/$(PROJ_NAME).c -o out/$(PROJ_NAME).o -DC_QUEUE_TEST
	
.PHONY: build
build:$(OBJ_FILES)
	@gcc $(OBJ_FILES) -o out/main.exe
	@echo "Build Done!"
	@echo $(OBJ_FILES)

.PHONY: run
run:
	@out/main.exe
	
.PHONY: clean
clean:
	@rm ./out/*
	@echo "Clear All Output File!"

print-%:
	@echo $($(subst print-,,$@))
