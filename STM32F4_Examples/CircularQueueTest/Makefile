PROJ_NAME := CircularQueue
OBJ_FILES = out/main.o 
OBJ_FILES += out/$(PROJ_NAME).o

LIB_DIRS = ./../../STM32F4_Middleware/CircularQueue
SRC_DIRS := $(LIB_DIRS)/src
INC_DIRS := $(LIB_DIRS)/inc

all: build

out/main.o:main.c
	@gcc -c -I./$(INC_DIRS) main.c -o out/main.o
out/$(PROJ_NAME).o:$(SRC_DIRS)/$(PROJ_NAME).c
	@gcc -c -I./$(INC_DIRS) $(SRC_DIRS)/$(PROJ_NAME).c -o out/$(PROJ_NAME).o
	
.PHONY: build	
build:$(OBJ_FILES)
	@gcc $(OBJ_FILES) -o out/main.exe
	@echo "Build Done!"
	@echo $(OBJ_FILES)
	
.PHONY: run	
run:
	out/main.exe
	
.PHONY: clean	
clean:
	@rm ./out/*
	@echo "Clear All Output File!"

print-%:
	@echo $($(subst print-,,$@))
