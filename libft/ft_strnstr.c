/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymekraou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 02:00:14 by ymekraou          #+#    #+#             */
/*   Updated: 2019/02/24 19:13:18 by ymekraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	lft_strlen(const char *s)
{
	size_t	cpt;

	cpt = 0;
	while (s[cpt] != '\0')
		cpt++;
	return (cpt);
}

char			*ft_strnstr(const char *haystack,
							const char *needle, size_t len)
{
	size_t		i;
	size_t		j;
	size_t		len_needle;

	if (needle[0] == '\0')
		return ((char*)haystack);
	len_needle = lft_strlen(needle);
	if (haystack[0] == '\0' || len < len_needle
			|| lft_strlen(haystack) < len_needle)
		return (NULL);
	i = 0;
	while (haystack[i + len_needle - 1] != '\0' && i <= len - 1)
	{
		j = 0;
		while (j < len_needle && i + j < len)
		{
			if (haystack[i + j] != needle[j])
				break ;
			j++;
		}
		if (j == len_needle)
			return ((char*)(haystack + i));
		i++;
	}
	return (NULL);
}
