/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/05 20:59:04 by dnakano           #+#    #+#             */
/*   Updated: 2021/06/12 09:18:12 by dnakano          ###   ########.fr       */
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
	int		ret;
	pid_t	*pids;

	if (!ppx_args_is_valid(argc, argv))
	{
		ft_putstr_fd("pipex: invalid argument\n", 2);
		return (1);
	}
	pids = malloc(sizeof(pid_t) * (argc - 1));
	ppx_backup_fd(fd_bkup);
	pids[0] = ppx_readfromfile(argv[1]);
	pids[1] = ppx_execcmd(argv[2]);
	pids[2] = ppx_execcmd(argv[3]);
	pids[argc - 2] = ppx_writetofile(argv[argc - 1]);
	ret = ppx_wait_children(pids, argc - 1);
	free(pids);
	ppx_recovery_fd(fd_bkup);
	return (ret);
}
