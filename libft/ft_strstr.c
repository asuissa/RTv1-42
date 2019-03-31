/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymekraou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 01:08:42 by ymekraou          #+#    #+#             */
/*   Updated: 2019/02/24 19:13:05 by ymekraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	lft_strlen(const char *s)
{
	size_t		cpt;

	cpt = 0;
	while (s[cpt] != '\0')
		cpt++;
	return (cpt);
}

char			*ft_strstr(const char *haystack, const char *needle)
{
	size_t		i;
	size_t		j;
	size_t		needle_len;

	if (needle[0] == '\0')
		return ((char*)haystack);
	needle_len = lft_strlen(needle);
	if (haystack[0] == '\0' || needle_len > lft_strlen(haystack))
		return (NULL);
	i = 0;
	while (haystack[i + needle_len - 1] != '\0')
	{
		j = 0;
		while (j < needle_len)
		{
			if (haystack[i + j] != needle[j])
				break ;
			j++;
		}
		if (j == needle_len)
			return ((char*)(haystack + i));
		i++;
	}
	return (NULL);
}
