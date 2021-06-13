/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/05 20:59:04 by dnakano           #+#    #+#             */
/*   Updated: 2021/06/13 13:53:16 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include "libft/libft.h"
#include "pipex.h"

/*
** todo
** - bonus multiple pipe
** - add test.sh to github actions
** - norminette
*/

int	ppx_args_is_valid(int argc, char **argv)
{
	int	i;

	if (argc != 5)
		return (0);
	i = 1;
	while (i < argc)
	{
		if (ft_strlen(argv[i]) < 1)
			return (0);
		i++;
	}
	return (1);
}

int	main(int argc, char **argv)
{
	int		fd_bkup[2];
	int		ret;
	pid_t	*pids;
	int		idx;

	if (!ppx_args_is_valid(argc, argv))
	{
		ft_putstr_fd("pipex: invalid argument\n", 2);
		return (1);
	}
	pids = malloc(sizeof(pid_t) * (argc - 1));
	ppx_backup_fd(fd_bkup);
	pids[0] = ppx_readfromfile(argv[1]);
	idx = 0;
	while (++idx < argc - 2)
		pids[idx] = ppx_execcmd(argv[idx + 1]);
	pids[argc - 2] = ppx_writetofile(argv[argc - 1]);
	ret = ppx_wait_children(pids, argc - 1);
	free(pids);
	ppx_recovery_fd(fd_bkup);
	return (ret);
}
