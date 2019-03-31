/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymekraou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 00:51:29 by ymekraou          #+#    #+#             */
/*   Updated: 2019/02/24 19:12:50 by ymekraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strrchr(const char *s, int c)
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
		}
		i++;
	}
	if (s[i] == '\0' && c == '\0')
		str = (s + i);
	return ((char*)str);
}
