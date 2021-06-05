/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ppx_args_is_valid.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/05 16:51:06 by dnakano           #+#    #+#             */
/*   Updated: 2021/06/05 21:07:48 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"

int	ppx_args_is_valid(int argc, char **argv)
{
	int	i;

	if (argc != 5)
		return (0);
	i = 1;
	while (i < argc)
	{
		if (ft_strlen(argv[i]) < 1)
			return (0);
		i++;
	}
	return (1);
}
