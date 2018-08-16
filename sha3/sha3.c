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

#include "../ftssl.h"

void	hash_sha3(uint64_t state[25])
{
	int	r;

	r = 0;
	while (r < 24)
	{
		theta(&state);
		rhopi(&state);
		chi(&state);
		iota(&state, r);
		r++;
	}
}

void	init_sha3(t_sha3set *set)
{
	int	i;

	i = 0;
	set->index = 0;
	set->digestlen = 32;
	set->rate = 200 - 64;
	while (i < 25)
	{
		set->state.lane[i] = 0;
		i++;
	}
}

void	update_sha3(t_sha3set *set, unsigned char *in, unsigned int len)
{
	size_t	i;
	int		j;

	j = set->index;
	i = 0;
	while (i < len)
	{
		set->state.byte[j++] ^= ((const uint8_t *)in)[i];
		if (j >= set->rate)
		{
			hash_sha3(set->state.lane);
			j = 0;
		}
		i++;
	}
	set->index = j;
}

void	end_sha3(unsigned char digest[32], t_sha3set *set)
{
	int i;

	i = -1;
	set->state.byte[set->index] ^= 0x06;
	set->state.byte[set->rate - 1] ^= 0x80;
	hash_sha3(set->state.lane);
	while (++i < set->digestlen)
		((uint8_t *)digest)[i] = set->state.byte[i];
	ft_memset((t_ptr)set, 0, sizeof(*set));
}
