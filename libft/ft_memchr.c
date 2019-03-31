/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymekraou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/16 02:40:27 by ymekraou          #+#    #+#             */
/*   Updated: 2019/02/24 19:10:09 by ymekraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_memchr(const void *s, int c, size_t n)
{
	size_t		i;
	const char	*str;

	str = NULL;
	i = 0;
	while (i < n)
	{
		if (*(char*)(s + i) == (char)c)
		{
			str = (s + i);
			break ;
		}
		i++;
	}
	return ((void*)str);
}
