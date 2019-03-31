/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymekraou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/16 04:10:46 by ymekraou          #+#    #+#             */
/*   Updated: 2019/02/24 19:09:53 by ymekraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t		i;

	if (dst > src)
	{
		i = len - 1;
		while (dst + i >= dst)
		{
			*(char*)(dst + i) = *(char*)(src + i);
			i--;
		}
	}
	else
	{
		i = 0;
		while (i < len)
		{
			*(char*)(dst + i) = *(char*)(src + i);
			i++;
		}
	}
	return ((void*)dst);
}
