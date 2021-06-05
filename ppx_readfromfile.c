/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ppx_readfromfile.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/05 18:26:17 by dnakano           #+#    #+#             */
/*   Updated: 2021/06/05 21:11:31 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include "libft/libft.h"

#define BUFFERSIZE 1024

static int	puterr(const char *filename)
{
	char	*msg;

	msg = ft_strjoin("pipex: ", filename);
	if (msg == NULL)
		return (1);
	perror(msg);
	free(msg);
	return (1);
}

static int	readandwrite(int filefd, int writefd)
{
	ssize_t	len;
	char	buf[BUFFERSIZE];

	while (1)
	{
		len = read(filefd, buf, BUFFERSIZE);
		if (len == -1)
			return (-1);
		if (len == 0)
			return (0);
		len = write(writefd, buf, len);
		if (len == -1)
			return (-1);
	}
}

static int	readfromfile_child(const char *filename, int pipe_fd[2])
{
	int		filefd;

	close(pipe_fd[0]);
	filefd = open(filename, O_RDONLY);
	if (filefd == -1)
	{
		puterr(filename);
		close(pipe_fd[1]);
		return (1);
	}
	if (readandwrite(filefd, pipe_fd[1]) == -1)
	{
		puterr(filename);
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
		return (-1);
	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
		exit(readfromfile_child(filename, pipe_fd));
	close(pipe_fd[1]);
	if (dup2(pipe_fd[0], 0) == -1)
	{
		close(pipe_fd[0]);
		return (-1);
	}
	return (pid);
}
