/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdiaz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/02 10:55:49 by tdiaz             #+#    #+#             */
/*   Updated: 2018/08/13 22:30:34 by tdiaz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftssl.h"

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
	int		i;

	i = 1;
	if (argc > 1)
	{
		if (comp(argv[1], "md5"))
			md5_dispatch(argc, argv);
		else if (comp(argv[1], "sha256"))
			sha_dispatch(argc, argv);
		else if (comp(argv[1], "sha3"))
			sha3_dispatch(argc, argv);
		else
			ft_printf("Unknown command: %s\n", argv[1]);
	}
	return (0);
}
