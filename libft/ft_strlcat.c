/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymekraou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 20:14:59 by ymekraou          #+#    #+#             */
/*   Updated: 2019/02/24 19:12:18 by ymekraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t		lft_strlen(const char *s)
{
	size_t	cpt;

	cpt = 0;
	while (s[cpt] != '\0')
		cpt++;
	return (cpt);
}

size_t				ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	len;

	if (size < lft_strlen(dst))
		len = size;
	else
		len = lft_strlen(dst);
	len += lft_strlen(src);
	if (size == 0)
		return (len);
	i = 0;
	while (dst[i] != '\0')
		i++;
	j = 0;
	while (i < size - 1 && src[j] != '\0')
	{
		dst[i] = src[j];
		j++;
		i++;
	}
	dst[i] = '\0';
	return (len);
}
