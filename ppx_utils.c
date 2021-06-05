/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ppx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/05 22:16:28 by dnakano           #+#    #+#             */
/*   Updated: 2021/06/06 08:37:10 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "libft/libft.h"

#define BUFFERSIZE 2048

int	ppx_puterr(const char *name, int ret)
{
	char	*msg;

	msg = ft_strjoin("pipex: ", name);
	if (msg == NULL)
		return (ret);
	perror(msg);
	free(msg);
	return (ret);
}

int	ppx_readandwrite(int readfd, int writefd)
{
	ssize_t	len;
	char	buf[BUFFERSIZE];

	while (1)
	{
		len = read(readfd, buf, BUFFERSIZE);
		if (len == -1)
			return (-1);
		if (len == 0)
			return (0);
		len = write(writefd, buf, len);
		if (len == -1)
			return (-1);
	}
}
