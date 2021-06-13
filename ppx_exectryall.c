/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ppx_exectryall.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/13 17:37:07 by dnakano           #+#    #+#             */
/*   Updated: 2021/06/13 17:49:13 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <limits.h>
#include <unistd.h>
#include "pipex.h"
#include "libft/libft.h"

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
	return (ft_calloc(sizeof(char **), 1));
}

static void	put_notfound(const char *cmd)
{
	ft_putstr_fd("pipex: ", 2);
	ft_putstr_fd((char *)cmd, 2);
	ft_putendl_fd(": command not found", 2);
}

static int	exectry(const char *path, char *const *argv, char *const *envp)
{
	char		fullpath[PATH_MAX + 1];

	if (ft_strlcpy(fullpath, path, PATH_MAX + 1) > PATH_MAX
		|| ft_strlcat(fullpath, "/", PATH_MAX) > PATH_MAX
		|| ft_strlcat(fullpath, argv[0], PATH_MAX) > PATH_MAX)
	{
		errno = ENAMETOOLONG;
		return (ppx_puterr(argv[0], 1));
	}
	execve(fullpath, argv, envp);
	if (errno != ENOENT)
		return (ppx_puterr(NULL, 1));
	return (0);
}

int	ppx_exectryall(const char **argv)
{
	size_t		i;
	int			ret;
	extern char	**environ;
	char		**paths;

	if (ft_strchr(argv[0], '/') != NULL
		&& execve(argv[0], (char *const *)argv, (char *const *)environ) == -1)
		return (ppx_puterr(argv[0], 127));
	paths = getpath((const char **)environ);
	if (paths == NULL)
		return (ppx_puterr("malloc", 1));
	i = 0;
	while (paths[i] != NULL)
	{
		ret = exectry(paths[i], (char *const *)argv, (char *const *)environ);
		if (ret != 0)
		{
			ppx_freestrs(paths);
			return (ret);
		}
		i++;
	}
	put_notfound(argv[0]);
	return (127);
}
