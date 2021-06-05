/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/05 20:59:04 by dnakano           #+#    #+#             */
/*   Updated: 2021/06/05 21:44:09 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdlib.h>
	#include <unistd.h>
	#include <sys/wait.h>
#include "libft/libft.h"
#include "pipex.h"

int	main(int argc, char **argv)
{
	int		fd_bkup[2];
	pid_t	*pids;

	if (!ppx_args_is_valid(argc, argv))
	{
		ft_putstr_fd("pipex: invalid argument\n", 2);
		return (1);
	}
	pids = malloc(sizeof(pid_t) * (argc - 1));
	ppx_backup_fd(fd_bkup);
	pids[0] = ppx_readfromfile(argv[1]);
	pids[argc - 1] = ppx_writetofile(argv[argc - 1]);
	wait(NULL);
	wait(NULL);
	free(pids);
	ppx_recovery_fd(fd_bkup);
}
