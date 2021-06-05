/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ppx_readfromfile.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/05 18:26:17 by dnakano           #+#    #+#             */
/*   Updated: 2021/06/05 22:51:03 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include "libft/libft.h"
#include "pipex.h"

#define BUFFERSIZE 2048

static int	readfromfile_child(const char *filename, int pipe_fd[2])
{
	int		filefd;

	close(pipe_fd[0]);
	filefd = open(filename, O_RDONLY);
	if (filefd == -1)
	{
		ppx_puterr(filename, 1);
		close(pipe_fd[1]);
		return (1);
	}
	if (ppx_readandwrite(filefd, pipe_fd[1]) == -1)
	{
		ppx_puterr(filename, 1);
		close(filefd);
		close(pipe_fd[1]);
		return (1);
	}
	close(filefd);
	close(pipe_fd[1]);
	return (0);
}

pid_t	ppx_readfromfile(const char *filename)
{
	int		pipe_fd[2];
	pid_t	pid;

	if (pipe(pipe_fd) == -1)
		return (ppx_puterr("pipe", -1));
	pid = fork();
	if (pid == -1)
		return (ppx_puterr("fork", -1));
	if (pid == 0)
		exit(readfromfile_child(filename, pipe_fd));
	close(pipe_fd[1]);
	if (dup2(pipe_fd[0], 0) == -1)
	{
		ppx_puterr("dup2", 0);
		close(pipe_fd[0]);
		return (-1);
	}
	return (pid);
}
