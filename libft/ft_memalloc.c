/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymekraou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/17 20:27:00 by ymekraou          #+#    #+#             */
/*   Updated: 2019/02/24 19:02:42 by ymekraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	void		*ptr;
	size_t		i;

	ptr = (char*)malloc(sizeof(char) * size);
	if (ptr == NULL)
		return (NULL);
	i = 0;
	while (i < size)
	{
		*(char*)(ptr + i) = 0;
		i++;
	}
	return ((void*)ptr);
}
