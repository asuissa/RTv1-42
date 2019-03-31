/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymekraou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 11:41:39 by ymekraou          #+#    #+#             */
/*   Updated: 2019/02/24 19:11:28 by ymekraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t		lft_strlen(const char *s)
{
	size_t		cpt;

	cpt = 0;
	while (s[cpt] != '\0')
		cpt++;
	return (cpt);
}

char				*ft_strncpy(char *dst, const char *src, size_t len)
{
	size_t		i;
	size_t		src_len;

	src_len = lft_strlen(src);
	i = 0;
	while (i < len)
	{
		if (i >= src_len)
			dst[i] = '\0';
		else
			dst[i] = src[i];
		i++;
	}
	return (dst);
}
