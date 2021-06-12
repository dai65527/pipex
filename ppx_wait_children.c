/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ppx_wait_childlen.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/12 09:06:57 by dnakano           #+#    #+#             */
/*   Updated: 2021/06/12 09:18:17 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/wait.h>

int	ppx_wait_children(pid_t *pids, size_t n)
{
	int		ret;
	int		status;
	size_t	cnt;
	pid_t	pid;

	cnt = 0;
	while (cnt < n)
	{
		pid = wait(&status);
		if (n >= 2 && pid == pids[n - 2])
		{
			if (WIFEXITED(status))
				ret = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				ret = WTERMSIG(status) + 128;
		}
		cnt++;
	}
	return ret;
}
