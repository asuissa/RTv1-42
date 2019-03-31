/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymekraou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 20:57:06 by ymekraou          #+#    #+#             */
/*   Updated: 2018/11/24 04:41:07 by ymekraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static size_t	lft_strlen(const char *s)
{
	size_t			cpt;

	cpt = 0;
	while (s[cpt] != '\0')
		cpt++;
	return (cpt);
}

char			*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*ptr;

	if (s == NULL || f == NULL)
		return (NULL);
	if (!(ptr = (char*)malloc(sizeof(char) * (lft_strlen(s) + 1))))
		return (NULL);
	i = 0;
	while (s[i] != '\0')
	{
		*(ptr + i) = (*f)(i, s[i]);
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}
