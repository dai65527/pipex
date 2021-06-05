/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ppx_writetofile.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/05 21:42:48 by dnakano           #+#    #+#             */
/*   Updated: 2021/06/06 08:37:22 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include "pipex.h"

static int	writetofile_child(const char *filename)
{
	int	filefd;

	filefd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (filefd == -1)
		return (ppx_puterr(filename, 1));
	if (ppx_readandwrite(0, filefd) == -1)
	{
		ppx_puterr(filename, 1);
		close(filefd);
		return (1);
	}
	close(filefd);
	return (0);
}

pid_t	ppx_writetofile(const char *filename)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return ((pid_t)ppx_puterr("fork", -1));
	if (pid == 0)
		exit(writetofile_child(filename));
	return (pid);
}
