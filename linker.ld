ENTRY(_start)

SECTIONS
{
  . = 2M;

	.text BLOCK(4K) : ALIGN(4K)
	{
		*(.multiboot)
		*(.text)
	}

	.rodata BLOCK(4K) : ALIGN(4K)
	{
		*(.rodata)
	}

	.data BLOCK(4K) : ALIGN(4K)
	{
		*(.data)
	}

	.bss BLOCK(4K) : ALIGN(4K)
	{
		*(COMMON)
		*(.bss)
	}

  /* HEAP AREA */
  . = ALIGN(4K);
  heap_start = .;
  . = . + 1M;
  heap_end = .;

  /* APPLICATION AREA */
  /* . = ALIGN(4K); */
  /* app_aread_start = .; */
  /* . = . + 1M; */
  /* exec_end = .; */
}
