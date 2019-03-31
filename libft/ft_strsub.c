/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymekraou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 22:21:10 by ymekraou          #+#    #+#             */
/*   Updated: 2018/11/24 04:36:14 by ymekraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	size_t		end;
	char		*sub;
	size_t		i;

	if (s == NULL)
		return (NULL);
	if (!(sub = (char*)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	end = start + len;
	i = 0;
	while (start < end)
	{
		sub[i] = (char)s[start];
		i++;
		start++;
	}
	sub[i] = '\0';
	return (sub);
}
