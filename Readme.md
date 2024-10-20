## STM32 Development FRAMEWORK
	> Author: Nghĩa Taarabt
	> Blog: https://www.laptrinhdientu.com/
	> Youtube: https://www.youtube.com/@laptrinhdientu
#### Description
	+ This project is my personal project to develop a development and testing framework for developing projects with ST microcontrollers.
	+ Development STM32 Driver follow as AUTOSAR MCAL / Middleware / Tools
	+ Testing Framework for MCAL Layer and Middleware, Tools for generate HTML/XML reports
	+ Develop some microcontroller projects base on this Framework

#### Project Structure
| MODULE | source codes of driver modules, for examples: GPIO, FLASH, UART, .etc.v.. |
| FRAMEWORK | fixed files, used for any projects of a microcontroller family |
| TEST | test suites and test cases for MCAL Layer |
| OUTPUT | object files, binary files, test output & report |

```
(P)_____DRIVER__________FLASH_________INC___FLASH.h
   |	      	   |	         |____SRC___FLASH.c
   |		   |___ + <other driver modules>
   |
   |___FRAMEWORK________TestCUnit______INC_____result.h 	 <test header>
   |               |              |____SRC_____result.c 	 <test source>
   |               |              |____stm32_startup.c 	 	 <startup file>
   |		   |____LINKER__________stm32f4_linker_FLASH.ld 	 <linker script file>
   |               |_ST-LINKUTILITY____<files to download FLASH>
   |               |___TEMP_REPORT_____<Template XML file for test report>
   |               |____PYTHON_________xmldata.py	 <Export test report>
   |               |___MAKEFILE
   |
   |_____TEST_________TEST_FLASH_______FLASH_TS_001_____test_suite__ <include + source>
   |               |               |                |___test_case__ <include + source>
   |               |               |___ + <other test suites> 
   |               |               |_______MAKE_____ <makefiles for test suites>
   |               |___+ <other test modules> 
   |
   |_____OUTPUT_____ <output files contains:__ object files, map file, log file
    					   |__ elf/hex/bin files
                                           |__ xml file (test suite output)
					   |__ csv file (test report)
```

## How to use this Framework
 - open Cygwin and cd to FRAMEWORK folder of project
 - export MODULE (ex: export MODULE=gpio)
 - export TEST_SUITE (ex: export TEST=gpio_TS_001)
 - make clean; make build; make run; make export
 - make py
