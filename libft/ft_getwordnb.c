/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getwordnb.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymekraou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 13:26:33 by ymekraou          #+#    #+#             */
/*   Updated: 2018/11/22 23:05:16 by ymekraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

size_t	ft_getwordnb(char const *s, char c)
{
	size_t	i;
	size_t	cpt;

	i = 0;
	cpt = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c)
			i++;
		if (s[i] != '\0')
			cpt++;
		while (s[i] != c && s[i] != '\0')
			i++;
	}
	return (cpt);
}
