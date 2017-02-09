#ifndef __SERIAL_S5P_H__
#define __SERIAL_S5P_H__

union br_rest {
	unsigned short	slot;		/* udivslot */
	unsigned char	value;		/* ufracval */
};

struct s5p_uart {
	unsigned int	ulcon;
	unsigned int	ucon;
	unsigned int	ufcon;
	unsigned int	umcon;
	unsigned int	utrstat;
	unsigned int	uerstat;
	unsigned int	ufstat;
	unsigned int	umstat;
	unsigned char	utxh;
	unsigned char	res1[3];
	unsigned char	urxh;
	unsigned char	res2[3];
	unsigned int	ubrdiv;
	union br_rest	rest;
	unsigned char	res3[0xffd0];
};

static inline int s5p_uart_divslot(void)
{
	return 0;
}

#endif
