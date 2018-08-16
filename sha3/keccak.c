/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keccak.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdiaz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/16 09:29:23 by tdiaz             #+#    #+#             */
/*   Updated: 2018/08/16 09:29:27 by tdiaz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ftssl.h"

static int	g_xyshft[24] = {
	10, 7, 11, 17, 18, 3, 5, 16, 8, 21, 24, 4,
	15, 23, 19, 13, 12, 2, 20, 14, 22, 9, 6, 1
};

static uint64_t	g_fdshftreg[24] = {
	0x0000000000000001, 0x0000000000008082, 0x800000000000808a,
	0x8000000080008000, 0x000000000000808b, 0x0000000080000001,
	0x8000000080008081, 0x8000000000008009, 0x000000000000008a,
	0x0000000000000088, 0x0000000080008009, 0x000000008000000a,
	0x000000008000808b, 0x800000000000008b, 0x8000000000008089,
	0x8000000000008003, 0x8000000000008002, 0x8000000000000080,
	0x000000000000800a, 0x800000008000000a, 0x8000000080008081,
	0x8000000000008080, 0x0000000080000001, 0x8000000080008008
};

static uint64_t	rot64l(uint64_t x, int n)
{
	return ((x << n) | (x >> (64 - n)));
}

void			theta(uint64_t *state[25])
{
	int			i;
	int			j;
	uint64_t	calc[5];
	uint64_t	tmp;

	i = 0;
	while (i < 5)
	{
		calc[i] = (*state)[i] ^ (*state)[i + 5] ^ (*state)[i + 10] ^
			(*state)[i + 15] ^ (*state)[i + 20];
		i++;
	}
	i = 0;
	while (i < 5)
	{
		tmp = calc[(i + 4) % 5] ^ rot64l(calc[(i + 1) % 5], 1);
		j = 0;
		while (j < 25)
		{
			(*state)[i + j] ^= tmp;
			j += 5;
		}
		i++;
	}
	ft_memset((unsigned char *)calc, 0, sizeof(calc));
}

void			rhopi(uint64_t *state[25])
{
	int			i;
	int			j;
	uint64_t	calc[5];
	uint64_t	tmp;

	tmp = (*state)[1];
	i = 0;
	while (i < 24)
	{
		j = g_xyshft[i];
		calc[0] = (*state)[j];
		(*state)[j] = rot64l(tmp, ((i + 1) * (i + 2)) / 2 % 64);
		tmp = calc[0];
		i++;
	}
	ft_memset((unsigned char *)calc, 0, sizeof(calc));
}

void			chi(uint64_t *state[25])
{
	int			i;
	int			j;
	uint64_t	calc[5];

	j = 0;
	while (j < 25)
	{
		i = 0;
		while (i < 5)
		{
			calc[i] = (*state)[j + i];
			i++;
		}
		i = 0;
		while (i < 5)
		{
			(*state)[j + i] ^= (~calc[(i + 1) % 5]) & calc[(i + 2) % 5];
			i++;
		}
		j += 5;
	}
	ft_memset((unsigned char *)calc, 0, sizeof(calc));
}

void			iota(uint64_t *state[25], int r)
{
	(*state)[0] ^= g_fdshftreg[r];
}
