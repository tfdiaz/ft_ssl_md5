/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdiaz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/14 18:32:57 by tdiaz             #+#    #+#             */
/*   Updated: 2018/08/14 18:33:12 by tdiaz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftssl.h"

void	c64_bits(unsigned char *output, uint64_t *input, unsigned int len)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = 0;
	while (j < len)
	{
		output[j] = (unsigned char)(input[i] & 0xff);
		output[j + 1] = (unsigned char)((input[i] >> 8) & 0xff);
		output[j + 2] = (unsigned char)((input[i] >> 16) & 0xff);
		output[j + 3] = (unsigned char)((input[i] >> 24) & 0xff);
		output[j + 4] = (unsigned char)((input[i] >> 32) & 0xff);
		output[j + 5] = (unsigned char)((input[i] >> 40) & 0xff);
		output[j + 6] = (unsigned char)((input[i] >> 48) & 0xff);
		output[j + 7] = (unsigned char)((input[i] >> 56) & 0xff);
		i++;
		j += 8;
	}
}

uint64_t	rot64l(uint64_t x, int n)
{
	return ((x << n) | (x >> (64 - n)));
}

int	g_xyshft[24] = {
	10, 7, 11, 17, 18, 3, 5, 16, 8, 21, 24, 4, 15, 23, 19, 13, 12, 2, 20, 14, 22, 9, 6, 1
};

uint64_t	g_fdshftreg[24] = {
	0x0000000000000001, 0x0000000000008082, 0x800000000000808a,
	0x8000000080008000, 0x000000000000808b, 0x0000000080000001,
    0x8000000080008081, 0x8000000000008009, 0x000000000000008a,
	0x0000000000000088, 0x0000000080008009, 0x000000008000000a,
	0x000000008000808b, 0x800000000000008b, 0x8000000000008089,
	0x8000000000008003, 0x8000000000008002, 0x8000000000000080,
	0x000000000000800a, 0x800000008000000a, 0x8000000080008081,
	0x8000000000008080, 0x0000000080000001, 0x8000000080008008
};

void	hash_sha3(uint64_t state[25])
{
	int i;
	int j;
	int k;
	uint64_t calc[5];
	uint64_t tmp;

	k = 0;
	while (k < 24)
	{
	//Theda
		i = 0;
		while (i < 5)
		{
			calc[i] = state[i] ^ state[i + 5] ^ state[i + 10] ^ state[i + 15] ^ state[i + 20];
			i++;
		}
		i = 0;
		while (i < 5)
		{
			tmp = calc[(i + 4) % 5] ^ rot64l(calc[(i + 1) % 5], 1);
			j = 0;
			while (j < 25)
			{
				state[i + j] ^= tmp;
				j += 5;
			}
			i++;
		}
	// for (int i = 0; i < 25; i++)
	// 	ft_printf("theda: %i: %#llx ", i, state[i]);
	//Rho Pi
		tmp = state[1];
		i = 0;
		while (i < 24)
		{
			j = g_xyshft[i];
			calc[0] = state[j];
			state[j] = rot64l(tmp, ((i + 1) * (i + 2))/2 % 64);
			tmp = calc[0];
			i++;
		}
		// for (int i = 0; i < 25; i++)
		// 	ft_printf("Rho Pi: %i: %#llx ", i, state[i]);
		// for (int i = 0; i < 25; i++)
		// 	ft_printf("After Pi: %x\n", state[i]);		
	//Chi
		j = 0;
		while (j < 25)
		{
			i = 0;
			while (i < 5)
			{
				calc[i] = state[j + i];
				i++;
			}
			i = 0;
			while (i < 5)
			{
				state[j + i] ^= (~calc[(i + 1) % 5]) & calc[(i + 2) % 5];
				i++;
			}
			j += 5;
		}
	//ita
		state[0] ^= g_fdshftreg[k];
	// for (int i = 0; i < 25; i++)
	// 	ft_printf("One round: %i: %#llx ", i, state[i]);
		k++;
	}
}

void	init_sha3(t_sha3set *set)
{
	int i;

	i = 0;
	while (i < 25)
	{
		set->state.lane[i] = 0;
		i++;
	}
	set->digestlen = 32;
	set->pt = 0;
	set->rsiz = 200 - 64;
}

void	update_sha3(t_sha3set *set, unsigned char *in, unsigned int len)
{
	size_t i;
	int j;

	j = set->pt;
	i = 0;
	while (i < len)
	{
		set->state.bus[j++] ^= ((const uint8_t *)in)[i];
		if (j >= set->rsiz)
		{
			hash_sha3(set->state.lane);
			j = 0;
		}
		i++;
	}
	set->pt = j;
}

void	end_sha3(unsigned char digest[32], t_sha3set *set)
{
	set->state.bus[set->pt] ^= 0x06;
	set->state.bus[set->rsiz - 1] ^= 0x80;
	// for (int i = 0; i < 25; i++)
	// 	ft_printf("%i: %#llx ", i, set->state.lane[i]);
	hash_sha3(set->state.lane);
	//ft_printf("%x\n", set->state.lane[0]);
    for (int i = 0; i < set->digestlen; i++) {
        ((uint8_t *) digest)[i] = set->state.bus[i];
    }	
}