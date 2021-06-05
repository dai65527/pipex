/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ppx_execcmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/05 23:18:07 by dnakano           #+#    #+#             */
/*   Updated: 2021/06/06 08:52:33 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include "libft/libft.h"
#include "pipex.h"

static void	freestrs(char **strs)
{
	char	**orig;

	orig = strs;
	while (*strs != NULL)
	{
		free(*strs);
		strs++;
	}
	free(orig);
}

static int	findcmdpath(const char *cmd, char *path)
{
	if (ft_strlcpy(path, cmd, PATH_MAX) >= PATH_MAX)
	{
		errno = ENAMETOOLONG;
		return (-1);
	}
	return (0);
}

static int	execcmd(const char *cmd)
{
	char		**argv;
	char		path[PATH_MAX];
	extern char	**environ;

	argv = ft_split(cmd, ' ');
	if (argv == NULL)
		return (ppx_puterr("ft_split", 1));
	if (findcmdpath(argv[0], path) == -1)
		return (ppx_puterr(argv[0], 1));
	execve(argv[0], argv, environ);
	ppx_puterr(argv[0], 1);
	freestrs(argv);
	return (1);
}

static int	execcmd_child(const char *cmd, int pipe_fd[2])
{
	if (dup2(pipe_fd[1], 1) == -1)
	{
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		return (ppx_puterr("dup2", 1));
	}
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	return (execcmd(cmd));
}

pid_t	ppx_execcmd(const char *cmd)
{
	pid_t	pid;
	int		pipe_fd[2];

	if (pipe(pipe_fd) == -1)
		return (-1);
	pid = fork();
	if (pid == -1)
	{
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		return ((pid_t)ppx_puterr("pipe", -1));
	}
	if (pid == 0)
		exit(execcmd_child(cmd, pipe_fd));
	close(pipe_fd[1]);
	if (dup2(pipe_fd[0], 0) == -1)
	{
		close(pipe_fd[0]);
		return ((pid_t)ppx_puterr("dup2", 1));
	}
	close(pipe_fd[0]);
	return (pid);
}
