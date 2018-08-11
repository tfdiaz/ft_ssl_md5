/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdiaz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/02 10:55:49 by tdiaz             #+#    #+#             */
/*   Updated: 2018/08/02 11:09:59 by tdiaz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ssl.h"

int			comp(const char *s1, const char *s2)
{
	while (*s1 == *s2)
	{
		if (!*s1)
			return (1);
		s1++;
		s2++;
	}
	return (0);
}

int			main(int argc, char **argv)
{
	char	buff[4068];
	int		i;
	int		iread;

	i = 1;
	if (argc > 1)
	{
		if (comp(argv[1], "md5"))
			md5_dispatch(argc, argv);
		else if (comp(argv[1], "sha256"))
			ft_printf("Nothing yet");
	}
	return (0);
}
/*		ft_printf("A : %u B: %u C: %u D: %u\n", st[0], st[1], st[2], st[3]); */
