/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymekraou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 19:58:57 by ymekraou          #+#    #+#             */
/*   Updated: 2019/02/24 19:10:54 by ymekraou         ###   ########.fr       */
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

char			*ft_strdup(const char *s1)
{
	char		*str;
	size_t		lenght;
	size_t		i;

	lenght = lft_strlen(s1);
	str = (char *)malloc(sizeof(char) * (lenght + 1));
	if (str == NULL)
		return (NULL);
	i = 0;
	while (i < lenght)
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
