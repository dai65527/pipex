/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 13:34:31 by dnakano           #+#    #+#             */
/*   Updated: 2021/05/13 20:04:03 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static int	itoalen(t_uint n)
{
	int		digit;

	if (!n)
		return (1);
	digit = 0;
	while (n > 0)
	{
		n /= 10;
		digit++;
	}
	return (digit);
}

char	*ft_itoa(int n)
{
	int		len;
	t_uint	n_abs;
	char	*s;

	if (n < 0)
		n_abs = -n;
	else
		n_abs = n;
	len = itoalen(n_abs);
	if (n < 0)
		len++;
	s = (char *)malloc(sizeof(char) * (len + 1));
	if (!s)
		return (NULL);
	if (n < 0)
		s[0] = '-';
	else if (n == 0)
		s[0] = '0';
	s[len] = 0;
	while (n_abs > 0)
	{
		s[--len] = n_abs % 10 + '0';
		n_abs /= 10;
	}
	return (s);
}
