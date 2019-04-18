/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymekraou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 11:37:04 by ymekraou          #+#    #+#             */
/*   Updated: 2019/04/18 15:24:06 by ymekraou         ###   ########.fr       */
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

char			*ft_strtrim(char const *s)
{
	char		*trim;
	size_t		len;
	size_t		start;
	size_t		end;
	size_t		i;

	if (s == 0)
		return (NULL);
	start = 0;
	while (s[start] == ' ' || s[start] == '\n'
		|| s[start] == '\t')
		start++;
	end = lft_strlen(s);
	while ((s[end] == ' ' || s[end] == '\n' || s[end] == '\t'
		|| s[end] == 0) && (end > start))
		end--;
	len = end - start + 1;
	if (!(trim = malloc(sizeof(char) * (len + 1))))
		return (NULL);
	i = 0;
	while (start <= end)
		trim[i++] = (char)*(s + start++);
	trim[i] = '\0';
	return (trim);
}
