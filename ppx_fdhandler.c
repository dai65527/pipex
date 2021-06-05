/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ppx_fdhandler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/05 17:03:50 by dnakano           #+#    #+#             */
/*   Updated: 2021/06/05 20:46:49 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	ppx_backup_fd(int fd_bkup[2])
{
	fd_bkup[0] = dup(0);
	fd_bkup[1] = dup(1);
	if (fd_bkup[0] == -1 || fd_bkup[1] == -1)
		return (-1);
	return (0);
}

int	ppx_recovery_fd(int fd_bkup[2])
{
	if (dup2(fd_bkup[0], 0) == -1)
	{
		close(fd_bkup[0]);
		close(fd_bkup[1]);
		return (-1);
	}
	if (dup2(fd_bkup[1], 1) == -1)
	{
		close(fd_bkup[1]);
		return (-1);
	}
	return (0);
}
