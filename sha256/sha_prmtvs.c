/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha_prmtvs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdiaz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/11 13:07:54 by tdiaz             #+#    #+#             */
/*   Updated: 2018/08/11 13:13:47 by tdiaz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ftssl.h"

uint32_t	ch(uint32_t x, uint32_t y, uint32_t z)
{
	return ((x & y) ^ ((~x) & (z)));
}

uint32_t	maj(uint32_t x, uint32_t y, uint32_t z)
{
	return ((x & y) ^ (x & z) ^ (y & z));
}

uint32_t	rotright(uint32_t x, int n)
{
	return ((x >> n) | (x << (32 - n)));
}

uint32_t	rightshft(uint32_t x, int n)
{
	return (x >> n);
}

uint32_t	wordcalc(uint32_t x[64], int i)
{
	return (sigma_i(x[i - 2]) + x[i - 7] + sigma_o(x[i - 15]) + x[i - 16]);
}
