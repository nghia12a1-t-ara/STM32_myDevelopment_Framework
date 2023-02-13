I continuously complete makefile project (Endian_Test Project)
I try to create a project as a common template for driver projects
** Project have 4 main folders:   
 - MODULE has source codes of driver modules, for examples: GPIO, FLASH, ...
 - FRAMEWORK contains fixed files, used for any projects of a microcontroller family
 - TEST contains test suites and test cases
 - OUTPUT contains object files, binary files, test output & report

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

Step by Step: 
 - open Cygwin and cd to FRAMEWORK folder of project
 - export MODULE (ex: export MODULE=gpio)
 - export TEST_SUITE (ex: export TEST=gpio_TS_001)
 - make clean; make build; make run; make export
 - make py


  

