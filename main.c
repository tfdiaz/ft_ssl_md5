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

t_send	g_send[4] = {
	{.prt = &md5_dispatch, .s = "md5"},
	{.prt = &sha_dispatch, .s = "sha256"},
	{.prt = &sha3_dispatch, .s = "sha3"},
	{0, 0}
};

int			readflmd5(int fd, char *buff, t_md5set *set)
{
	int iread;

	while (((iread = read(fd, buff, READ_SIZE))) > 0)
	{
		buff[iread] = '\0';
		update_md5(set, (t_ptr)buff, iread);
	}
	if (iread < 0)
		ft_printf("md5: File to read is directory.\n");
	return (iread);
}

int			readflsha3(int fd, char *buff, t_sha3set *set)
{
	int iread;

	while (((iread = read(fd, buff, READ_SIZE))) > 0)
	{
		buff[iread] = '\0';
		update_sha3(set, (t_ptr)buff, iread);
	}
	if (iread < 0)
		ft_printf("sha3: File to read is directory.\n");
	return (iread);
}

int			readflsha256(int fd, char *buff, t_sha2set *set)
{
	int iread;

	while (((iread = read(fd, buff, READ_SIZE))) > 0)
	{
		buff[iread] = '\0';
		update_sha256(set, (t_ptr)buff, iread);
	}
	if (iread < 0)
		ft_printf("sha256: File to read is directory.\n");
	return (iread);
}

int			main(int argc, char **argv)
{
	int		i;

	if (argc > 1)
	{
		i = 0;
		while (g_send[i].prt != NULL)
		{
			if (strcomp(argv[1], g_send[i].s))
			{
				g_send[i].prt(argc, argv);
				exit(0);
			}
			i++;
		}
		ft_printf("Unknown command: %s\n", argv[1]);
	}
	return (0);
}
