PROJ_NAME := PriorityQueue
OBJ_FILES = main.o 
OBJ_FILES += $(PROJ_NAME).o

LIB_DIRS = ./../../STM32F4_Middleware/PriorityQueue
SRC_DIRS := $(LIB_DIRS)/src
INC_DIRS := $(LIB_DIRS)/inc
STD_LIBS = $(LIB_DIRS)/../../STM32F4_Drivers/BASE/inc

all: build

main.o:main.c
	@gcc -c -I./$(INC_DIRS) -I$(STD_LIBS) main.c -o main.o -DPRIORITY_QUEUE_TEST
$(PROJ_NAME).o:$(SRC_DIRS)/$(PROJ_NAME).c
	@gcc -c -I./$(INC_DIRS) -I$(STD_LIBS) $(SRC_DIRS)/$(PROJ_NAME).c -o $(PROJ_NAME).o -DPRIORITY_QUEUE_TEST
	
.PHONY: build	
build:$(OBJ_FILES)
	@gcc $(OBJ_FILES) -o main.exe
	@echo "Build Done!"
	@echo $(OBJ_FILES)
	
.PHONY: run	
run:
	@./main.exe
	
.PHONY: clean	
clean:
	@rm ./*
	@echo "Clear All Output File!"

print-%:
	@echo $($(subst print-,,$@))
