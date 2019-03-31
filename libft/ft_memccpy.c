/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymekraou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/16 03:07:51 by ymekraou          #+#    #+#             */
/*   Updated: 2019/02/24 19:09:36 by ymekraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t	i;
	char	*ptr;

	ptr = NULL;
	i = 0;
	while (i < n)
	{
		*(char*)(dst + i) = *(char*)(src + i);
		if (*(char*)(src + i) == (char)c)
		{
			ptr = (char*)(dst + i + 1);
			break ;
		}
		i++;
	}
	return ((void*)ptr);
}
