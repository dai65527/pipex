/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 05:41:52 by dnakano           #+#    #+#             */
/*   Updated: 2021/05/31 19:12:44 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char	*dst_c;
	char	*src_c;

	if (dst == src)
		return (dst);
	dst_c = (char *)dst;
	src_c = (char *)src;
	while (n-- > 0)
		*dst_c++ = *src_c++;
	return (dst);
}
