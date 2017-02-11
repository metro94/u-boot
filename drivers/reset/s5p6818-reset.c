#include <common.h>
#include <dm/device.h>
#include <reset-uclass.h>

DECLARE_GLOBAL_DATA_PTR;

struct s5p6818_reset_platdata {
	unsigned int *reset_bank;
	unsigned int tot_reset_ids;
};

static int s5p6818_reset_ofdata_to_platdata(struct udevice *dev)
{
	struct s5p6818_reset_platdata *plat = dev->platdata;
	fdt_addr_t addr;
	unsigned int tot_reset_ids;

	addr = dev_get_addr(dev);
	if (addr == FDT_ADDR_T_NONE)
		return -EINVAL;

	tot_reset_ids = fdtdec_get_uint(
		gd->fdt_blob,
		dev->of_offset,
		"tot_reset_ids",
		0
	);
	if (!tot_reset_ids)
		return -EINVAL;

	plat->reset_bank = (unsigned int *)addr;
	plat->tot_reset_ids = tot_reset_ids;

	return 0;
}

static int s5p6818_reset_request(struct reset_ctl *reset_ctl) {
	struct s5p6818_reset_platdata *plat = reset_ctl->dev->platdata;

	if (reset_ctl->id >= plat->tot_reset_ids)
		return -ENODEV;
	return 0;
}

static int s5p6818_reset_free(struct reset_ctl *reset_ctl) {
	return 0;
}

static int s5p6818_reset_assert(struct reset_ctl *reset_ctl) {
	struct s5p6818_reset_platdata *plat = reset_ctl->dev->platdata;
	unsigned int bank = reset_ctl->id / 32;
	unsigned int num = reset_ctl->id % 32;

	plat->reset_bank[bank] &= ~(1 << num);

	return 0;
}

static int s5p6818_reset_deassert(struct reset_ctl *reset_ctl) {
	struct s5p6818_reset_platdata *plat = reset_ctl->dev->platdata;
	unsigned int bank = reset_ctl->id / 32;
	unsigned int num = reset_ctl->id % 32;

	plat->reset_bank[bank] |=  (1 << num);

	return 0;
}

static const struct reset_ops s5p6818_reset_ops = {
	.request = s5p6818_reset_request,
	.free = s5p6818_reset_free,
	.rst_assert = s5p6818_reset_assert,
	.rst_deassert = s5p6818_reset_deassert
};

static const struct udevice_id s5p6818_reset_ids[] = {
	{ .compatible = "nexell,s5p6818-reset" }
};

U_BOOT_DRIVER(s5p6818_reset) = {
	.name = "reset_s5p6818",
	.id = UCLASS_RESET,
	.of_match = s5p6818_reset_ids,
	.ofdata_to_platdata = s5p6818_reset_ofdata_to_platdata,
	.platdata_auto_alloc_size = sizeof(struct s5p6818_reset_platdata),
	.ops = &s5p6818_reset_ops,
	.flags = DM_FLAG_PRE_RELOC
};
