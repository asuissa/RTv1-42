/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymekraou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 19:52:45 by ymekraou          #+#    #+#             */
/*   Updated: 2018/11/24 04:00:51 by ymekraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static size_t	lft_strlen(const char *s)
{
	size_t		cpt;

	cpt = 0;
	while (s[cpt] != '\0')
		cpt++;
	return (cpt);
}

char			*ft_strmap(char const *s, char (*f)(char))
{
	size_t		i;
	char		*str;

	str = NULL;
	if (s != 0 && f != 0)
	{
		if (!(str = (char*)malloc(sizeof(char) * (lft_strlen(s) + 1))))
			return (NULL);
		i = 0;
		while (s[i] != '\0')
		{
			*(str + i) = (char)(*f)(*(s + i));
			i++;
		}
		str[i] = '\0';
	}
	return (str);
}
