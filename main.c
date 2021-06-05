/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/05 20:59:04 by dnakano           #+#    #+#             */
/*   Updated: 2021/06/05 21:09:29 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
	#include <unistd.h>
	#include <sys/wait.h>
#include "libft/libft.h"
#include "pipex.h"

int	main(int argc, char **argv)
{
	int	fd_bkup[2];

	if (!ppx_args_is_valid(argc, argv))
	{
		ft_putstr_fd("pipex: invalid argument\n", 2);
		return (1);
	}
	ppx_backup_fd(fd_bkup);
	ppx_readfromfile(argv[1]);
	char buf[1024];
	size_t len;
	while ((len = read(0, buf, 1024)) > 0) {
		write(1, buf, len);
	}
	wait(NULL);
	ppx_recovery_fd(fd_bkup);
}
