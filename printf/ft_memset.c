/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdiaz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/09 12:00:08 by tdiaz             #+#    #+#             */
/*   Updated: 2018/07/10 19:43:04 by tdiaz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	char			*cpy;
	unsigned char	ch;

	ch = (unsigned char)c;
	i = 0;
	cpy = (char*)b;
	while (i < len)
	{
		cpy[i] = ch;
		i++;
	}
	return (cpy);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char	*c_dst;
	char	*c_src;
	size_t	i;

	i = 0;
	c_dst = (char*)dst;
	c_src = (char*)src;
	while (i < n)
	{
		c_dst[i] = c_src[i];
		i++;
	}
	return (c_dst);
}
