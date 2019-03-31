/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymekraou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 13:46:48 by ymekraou          #+#    #+#             */
/*   Updated: 2018/11/28 12:17:04 by ymekraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int		emptytab(int k, char **tab)
{
	while (k >= 0)
		free(tab[k--]);
	return (0);
}

static int		filltab(char const *s, char c, char **tab)
{
	size_t	i;
	size_t	j;
	int		k;
	size_t	len;

	i = 0;
	k = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c)
			i++;
		if (s[i] == '\0')
			break ;
		len = ft_getwordlen(s + i, c);
		if (!(tab[k] = ft_strnew(len + 1)))
			return (emptytab(k, tab));
		j = 0;
		while (s[i] != '\0' && s[i] != c)
			*(*(tab + k) + j++) = (char)s[i++];
		k++;
	}
	tab[k] = NULL;
	return (1);
}

char			**ft_strsplit(char const *s, char c)
{
	char	**tab;

	if (s == NULL)
		return (NULL);
	if (!(tab = (char**)malloc(sizeof(char*) * (ft_getwordnb(s, c) + 1))))
		return (NULL);
	if (!(filltab(s, c, tab)))
	{
		free(tab);
		return (NULL);
	}
	return (tab);
}
