/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/05 16:55:32 by dnakano           #+#    #+#             */
/*   Updated: 2021/06/05 23:15:05 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

int	ppx_args_is_valid(int argc, char **argv);
int	ppx_backup_fd(int fd_bkup[2]);
int	ppx_recovery_fd(int fd_bkup[2]);
pid_t	ppx_readfromfile(const char *filename);
pid_t	ppx_writetofile(const char *filename);

int	ppx_puterr(const char *name, int ret);
int	ppx_readandwrite(int inputfd, int writefd);

#endif