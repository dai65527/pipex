/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ppx_wait_children.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/12 09:06:57 by dnakano           #+#    #+#             */
/*   Updated: 2021/06/13 16:36:30 by dnakano          ###   ########.fr       */
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

	ret = 0;
	cnt = 0;
	while (cnt < n)
	{
		pid = wait(&status);
		if (n >= 2 && (pid == pids[n - 2] || pid == pids[n - 1]) && ret == 0)
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
