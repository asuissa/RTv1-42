/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymekraou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 22:34:49 by ymekraou          #+#    #+#             */
/*   Updated: 2018/11/28 13:30:48 by ymekraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static size_t		lft_strlen(const char *s)
{
	size_t		cpt;

	cpt = 0;
	while (s[cpt] != '\0')
		cpt++;
	return (cpt);
}

char				*ft_strjoin(char const *s1, char const *s2)
{
	size_t		len;
	char		*str;
	size_t		i;
	size_t		j;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	len = lft_strlen(s1) + lft_strlen(s2);
	if (!(str = (char*)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		str[i] = (char)s1[i];
		i++;
	}
	j = 0;
	while (s2[j] != '\0')
	{
		str[i] = (char)s2[j];
		i++;
		j++;
	}
	str[i] = '\0';
	return (str);
}
