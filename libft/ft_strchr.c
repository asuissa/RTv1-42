/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymekraou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 23:26:08 by ymekraou          #+#    #+#             */
/*   Updated: 2019/02/24 19:12:33 by ymekraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strchr(const char *s, int c)
{
	int			i;
	const char	*str;

	str = NULL;
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
		{
			str = (s + i);
			return ((char*)str);
		}
		i++;
	}
	if (s[i] == '\0' && c == '\0')
		str = (s + i);
	return ((char*)str);
}
