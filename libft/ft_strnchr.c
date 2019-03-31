/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymekraou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 09:48:16 by ymekraou          #+#    #+#             */
/*   Updated: 2018/11/27 09:54:15 by ymekraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char		*ft_strnchr(const char *s, int c, size_t n)
{
	size_t			i;
	const char		*str;

	str = NULL;
	i = 0;
	while (s[i] != '\0' && i < n)
	{
		if (s[i] == c)
		{
			str = (s + i);
			return ((char*)str);
		}
		i++;
	}
	if (s[i] == '\0' && c == '\0' && i < n)
		str = (s + i);
	return ((char*)str);
}
