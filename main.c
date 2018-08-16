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

int			main(int argc, char **argv)
{
	int		i;

	i = 1;
	if (argc > 1)
	{
		if (strcomp(argv[1], "md5"))
			md5_dispatch(argc, argv);
		else if (strcomp(argv[1], "sha256"))
			sha_dispatch(argc, argv);
		else if (strcomp(argv[1], "sha3"))
			sha3_dispatch(argc, argv);
		else
			ft_printf("Unknown command: %s\n", argv[1]);
	}
	return (0);
}
