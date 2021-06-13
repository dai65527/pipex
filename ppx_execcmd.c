/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ppx_execcmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/05 23:18:07 by dnakano           #+#    #+#             */
/*   Updated: 2021/06/13 16:58:51 by dnakano          ###   ########.fr       */
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

static char	**getpath(const char **envp)
{
	char	*path;

	path = NULL;
	while (*envp)
	{
		if (!ft_strncmp(*envp, "PATH=", 5))
			return (ft_split(*envp + 5, ':'));
		envp++;
	}
	return (ft_calloc(sizeof(char**), 1));
}

static int	exectryall(const char **argv)
{
	size_t		i;
	extern char	**environ;
	char		**paths;
	char		fullpath[PATH_MAX + 1];

	if (ft_strchr(argv[0], '/') != NULL &&
		execve(argv[0], (char* const*)argv, (char* const*)environ) == -1)
		return (ppx_puterr(argv[0], 127));
	paths = getpath((const char**)environ);
	if (paths == NULL)
		return (ppx_puterr("malloc", 1));
	i = 0;
	while (paths[i] != NULL)
	{
		if (ft_strlcpy(fullpath, paths[i], PATH_MAX + 1) > PATH_MAX
			|| ft_strlcat(fullpath, "/", PATH_MAX) > PATH_MAX
			|| ft_strlcat(fullpath, argv[0], PATH_MAX) > PATH_MAX)
		{
			errno = ENAMETOOLONG;
			freestrs(paths);
			exit(ppx_puterr(argv[0], 1));
			break;
		}
		// ft_putendl_fd(fullpath, 2);
		execve(fullpath, (char* const*)argv, (char* const*)environ);
		if (errno != ENOENT)
			return ppx_puterr(NULL, 1);
		i++;
	}
	ft_putstr_fd("pipex: ", 2);
	ft_putstr_fd((char *)argv[0], 2);
	ft_putendl_fd(": command not found", 2);
	return (127);
}

static int	execcmd(const char *cmd)
{
	int			ret;
	char		**argv;
	char		path[PATH_MAX];

	argv = ft_split(cmd, ' ');
	if (argv == NULL)
		return (ppx_puterr("ft_split", 1));
	if (findcmdpath(argv[0], path) != 0)
		return (ppx_puterr(argv[0], 1));
	ret = exectryall((const char **)argv);
	freestrs(argv);
	return (ret);
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
