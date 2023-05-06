ENTRY(Reset_Handler)

MEMORY
{
	FLASH(rx):ORIGIN =0x08000000,LENGTH =512K
	RESULT_SRAM(rwx):ORIGIN =0x20000000,LENGTH =4
	SRAM(rwx):ORIGIN =0x20000004,LENGTH =98300		/* 96KB - 4B = 98300B */
}

__max_heap_size = 0x400;	/* A symbol declaration */
__max_stack_size = 0x200;

SECTIONS
{
	.text :
	{	/* '.' = VMA = 0x20000004 */
		*(.isr_vector)
		*(.text)
		*(.text*)
		*(.init)
		*(.fini)
		*(.rodata)
		*(.rodata.*)
		. = ALIGN(4);
		_etext = .;		/* store the updated location counter value into a symbol '_etext' */	
	}> SRAM
	
	.data :
	{
		_sdata = .;
		*(.data)
		*(.data.*)
		. = ALIGN(4);
		_edata = .;
	}> SRAM
	
	.bss :
	{
		_sbss = .;
		__bss_start__ = _sbss;
		*(.bss)
		*(.bss.*)
		. = ALIGN(4);
		_ebss = .;
		__bss_end__ = _ebss;
		. = ALIGN(4);
		end = .;
		__end__ = .;
	}> SRAM
	
	.result :
	{
		*(.result)
	} > RESULT_SRAM
}