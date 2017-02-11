#include <common.h>
#include <asm/io.h>
#include <asm/armv8/mmu.h>
#include <fdtdec.h>

static struct mm_region nanopi_m3_mem_map[] = {
	{
		// DRAM
		.virt = 0x40000000ULL,
		.phys = 0x40000000ULL,
		.size = 0x40000000ULL,
		.attrs = PTE_BLOCK_MEMTYPE(MT_NORMAL) |
			PTE_BLOCK_OUTER_SHARE
	}, {
		// Registers
		.virt = 0xC0000000ULL,
		.phys = 0xC0000000ULL,
		.size = 0x20000000ULL,
		.attrs = PTE_BLOCK_MEMTYPE(MT_DEVICE_NGNRNE) |
			PTE_BLOCK_INNER_SHARE |
			PTE_BLOCK_PXN | PTE_BLOCK_UXN
	}, {
		// SRAM
		.virt = 0xFFFF0000ULL,
		.phys = 0xFFFF0000ULL,
		.size = 0x00010000ULL,
		.attrs = PTE_BLOCK_MEMTYPE(MT_NORMAL) |
			PTE_BLOCK_OUTER_SHARE
	}, {
		0,
	}
};


struct mm_region *mem_map = nanopi_m3_mem_map;

int board_init(void)
{
	return 0;
}

int dram_init(void)
{
	return fdtdec_setup_memory_size();
}

void reset_cpu(ulong addr)
{
	setbits_le32(0xC0010224, 1 << 3);
	setbits_le32(0xC0010228, 1 << 12);
	while (1);
}

void dram_init_banksize(void)
{
	fdtdec_setup_memory_banksize();
}
