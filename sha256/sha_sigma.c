/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha_sigma.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdiaz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/13 19:04:36 by tdiaz             #+#    #+#             */
/*   Updated: 2018/08/13 19:04:59 by tdiaz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ftssl.h"

uint32_t	sigma_0(uint32_t x)
{
	return (rotright(x, 2) ^ rotright(x, 13) ^ rotright(x, 22));
}

uint32_t	sigma_1(uint32_t x)
{
	return (rotright(x, 6) ^ rotright(x, 11) ^ rotright(x, 25));
}

uint32_t	sigma_o(uint32_t x)
{
	return (rotright(x, 7) ^ rotright(x, 18) ^ rightshft(x, 3));
}

uint32_t	sigma_i(uint32_t x)
{
	return (rotright(x, 17) ^ rotright(x, 19) ^ rightshft(x, 10));
}
