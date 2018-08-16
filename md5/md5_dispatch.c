/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_dispatch.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdiaz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/10 16:45:58 by tdiaz             #+#    #+#             */
/*   Updated: 2018/08/10 16:46:08 by tdiaz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ftssl.h"

static int	g_sflag = FALSE;
static int	g_qflag = FALSE;
static int	g_rflag = FALSE;
static int	g_pflag = FALSE;

static void	prt_digest(unsigned char digest[16])
{
	unsigned int	i;

	i = 0;
	while (i < 16)
	{
		ft_printf("%02x", digest[i]);
		i++;
	}
}

void		md5string(char *s)
{
	t_md5set		set;
	unsigned char	digest[16];
	unsigned int	len;

	len = ft_strlen(s);
	init_md5(&set);
	update_md5(&set, (t_ptr)s, len);
	end_md5(digest, &set);
	if (g_rflag == FALSE && g_qflag == FALSE)
		ft_printf("MD5 (\"%s\") = ", s);
	prt_digest(digest);
	if (g_rflag && g_qflag == FALSE)
		ft_printf(" \"%s\"", s);
	ft_printf("\n");
	g_sflag = 0;
}

void		md5_stdin(void)
{
	t_md5set		set;
	unsigned char	digest[16];
	unsigned int	len;
	char			buff[READ_SIZE + 1];
	int				iread;

	init_md5(&set);
	while (((iread = read(STDIN_FILENO, buff, READ_SIZE))) > 0)
	{
		buff[iread] = '\0';
		if (g_pflag)
			ft_printf("%s", buff);
		update_md5(&set, (t_ptr)buff, iread);
	}
	if (iread < 0)
	{
		ft_printf("md5: Error during READ command.\n");
		return ;
	}
	end_md5(digest, &set);
	prt_digest(digest);
	ft_printf("\n");
	g_pflag = 0;
}

void		md5_file(char *s)
{
	t_md5set		set;
	int				fd;
	int				iread;
	char			buff[READ_SIZE + 1];
	unsigned char	digest[16];

	if ((fd = open(s, O_RDONLY)) < 0)
		ft_printf("md5: Error: %s: can't be open.\n", s);
	else
	{
		init_md5(&set);
		if (readflmd5(fd, buff, &set) < 0)
			return ;
		end_md5(digest, &set);
		close(fd);
		if (g_rflag == FALSE && g_qflag == FALSE)
			ft_printf("MD5 (%s) = ", s);
		prt_digest(digest);
		if (g_rflag && g_qflag == FALSE)
			ft_printf(" %s", s);
		ft_printf("\n");
	}
}

void		md5_dispatch(int argc, char **argv)
{
	int	i;
	int input;

	i = 2;
	input = TRUE;
	while (i < argc)
	{
		if (strcomp(argv[i], "-q") && i < 6)
			g_qflag = TRUE;
		else if (strcomp(argv[i], "-r") && i < 6)
			g_rflag = TRUE;
		else if (strcomp(argv[i], "-s") && i < 6)
			g_sflag = TRUE;
		else if (strcomp(argv[i], "-p") && i < 6)
			g_pflag = TRUE;
		else
		{
			input = FALSE;
			(g_pflag > 0) ? md5_stdin() : 0;
			(g_sflag > 0) ? md5string(argv[i]) : md5_file(argv[i]);
		}
		i++;
	}
	if (input == TRUE)
		md5_stdin();
}
