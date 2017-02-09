#include <common.h>
#include <asm/io.h>
#include <asm/armv8/mmu.h>

#include <debug_uart.h>

DECLARE_GLOBAL_DATA_PTR;

static struct mm_region nanopi_m3_mem_map[] = {
	{
		.virt = 0x40000000U,
		.phys = 0x40000000U,
		.size = 0x40000000U,
		.attrs = PTE_BLOCK_MEMTYPE(MT_NORMAL) |
		        PTE_BLOCK_OUTER_SHARE
	}, {
		.virt = 0xC0000000U,
		.phys = 0xC0000000U,
		.size = 0x20000000U,
		.attrs = PTE_BLOCK_MEMTYPE(MT_DEVICE_NGNRNE) |
		        PTE_BLOCK_INNER_SHARE |
		        PTE_BLOCK_PXN | PTE_BLOCK_UXN
	}, {
		.virt = 0xFFFF0000U,
		.phys = 0xFFFF0000U,
		.size = 0x00010000U,
		.attrs = PTE_BLOCK_MEMTYPE(MT_DEVICE_NGNRNE) |
		        PTE_BLOCK_INNER_SHARE |
		        PTE_BLOCK_PXN | PTE_BLOCK_UXN
	}, {
		0,
	}
};


struct mm_region *mem_map = nanopi_m3_mem_map;

int board_early_init_f(void)
{
	debug_uart_init();
	return 0;
}

int board_init(void)
{
//	setbits_le32(0xC001B000U, 1 << 12);
//	*(volatile unsigned int*)(unsigned long long)0xC001B000U |= (1 << 12);
	return 0;
}

int dram_init(void)
{
	gd->ram_size = CONFIG_SYS_SDRAM_SIZE;
	return 0;
}

struct serial_device *default_serial_console(void)
{
	return NULL;
}

void reset_cpu(ulong addr)
{
}
