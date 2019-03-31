/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymekraou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/17 21:20:51 by ymekraou          #+#    #+#             */
/*   Updated: 2019/02/24 19:03:25 by ymekraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	void		*ptr;
	size_t		i;

	ptr = (char*)malloc(sizeof(char) * (size + 1));
	if (ptr == NULL)
		return (NULL);
	i = 0;
	while (i < size + 1)
	{
		*(char*)(ptr + i) = '\0';
		i++;
	}
	return ((char*)ptr);
}
