/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdiaz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/11 11:07:39 by tdiaz             #+#    #+#             */
/*   Updated: 2018/08/11 11:09:46 by tdiaz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ftssl.h"

static unsigned char g_padding[64] = {
	0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

uint32_t	g_cuberoot[64] = {
	0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1,
	0x923f82a4, 0xab1c5ed5, 0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
	0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174, 0xe49b69c1, 0xefbe4786,
	0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
	0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147,
	0x06ca6351, 0x14292967, 0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
	0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85, 0xa2bfe8a1, 0xa81a664b,
	0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
	0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a,
	0x5b9cca4f, 0x682e6ff3, 0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
	0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
};

void	init_sha256(t_shaset *set)
{
	set->count[0] = 0;
	set->count[1] = 0;
	set->st[0] = 0x6a09e667;
	set->st[1] = 0xbb67ae85;
	set->st[2] = 0x3c6ef372;
	set->st[3] = 0xa54ff53a;
	set->st[4] = 0x510e527f;
	set->st[5] = 0x9b05688c;
	set->st[6] = 0x1f83d9ab;
	set->st[7] = 0x5be0cd19;
}

void	update_sha256(t_shaset *set, unsigned char *in, unsigned int len)
{
	unsigned int	index;
	unsigned int	sublen;
	unsigned int	i;

	index = (unsigned int)((set->count[1] >> 3) & 0x3f);
	if ((set->count[1] += (uint32_t)len << 3) < ((uint32_t)len << 3))
		set->count[0]++;
	set->count[0] += (uint32_t)len >> 29;
	sublen = 64 - index;
	if (len >= sublen)
	{
		ft_memcpy((t_ptr)&set->buff[index], (t_ptr)in, sublen);
		hash_sha256(set->st, set->buff);
		i = sublen;
		while (i + 63 < len)
		{
			hash_sha256(set->st, &in[i]);
			i += 64;
		}
		index = 0;
	}
	else
		i = 0;
	ft_memcpy((t_ptr)&set->buff[index], (t_ptr)&in[i], len - i);
}

void	round_sha256(uint32_t *st[8], uint32_t buff[16])
{
	uint32_t	buffset[64];
	uint32_t	t1;
	uint32_t	t2;
	int			i;

	i = -1;
	while (++i < 64)
	{
		if (i < 16)
			buffset[i] = buff[i];
		else
			buffset[i] = wordcalc(buffset, i);
		t1 = (*st)[7] + sigma_1((*st)[4]) + ch((*st)[4], (*st)[5], (*st)[6]) +
			g_cuberoot[i] + buffset[i];
		t2 = sigma_0((*st)[0]) + maj((*st)[0], (*st)[1], (*st)[2]);
		(*st)[7] = (*st)[6];
		(*st)[6] = (*st)[5];
		(*st)[5] = (*st)[4];
		(*st)[4] = (*st)[3] + t1;
		(*st)[3] = (*st)[2];
		(*st)[2] = (*st)[1];
		(*st)[1] = (*st)[0];
		(*st)[0] = t1 + t2;
	}
}

void	hash_sha256(uint32_t st[8], unsigned char block[64])
{
	uint32_t	cpy[8];
	uint32_t	buff[16];
	int			i;

	i = -1;
	while (++i < 8)
		cpy[i] = st[i];
	beuc_bits(buff, block, 64);
	round_sha256(&st, buff);
	i = -1;
	while (++i < 8)
		st[i] += cpy[i];
	ft_memset((unsigned char *)buff, 0, sizeof(buff));
}

void	end_sha256(unsigned char digest[32], t_shaset *set)
{
	unsigned char	bits[8];
	unsigned int	index;
	unsigned int	padlen;

	bec_bits(bits, set->count, 8);
	index = (unsigned int)((set->count[1] >> 3) & 0x3f);
	padlen = (index < 56) ? (56 - index) : (120 - index);
	update_sha256(set, g_padding, padlen);
	update_sha256(set, bits, 8);
	bec_bits(digest, set->st, 32);
	ft_memset((t_ptr)set, 0, sizeof(*set));
}
