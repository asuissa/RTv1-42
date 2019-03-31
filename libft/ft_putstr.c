/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymekraou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 19:40:21 by ymekraou          #+#    #+#             */
/*   Updated: 2018/11/24 06:44:16 by ymekraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

static void		lft_putchar(char c)
{
	write(1, &c, 1);
}

void			ft_putstr(char const *s)
{
	int i;

	if (s != NULL)
	{
		i = 0;
		while (s[i] != '\0')
		{
			lft_putchar(s[i++]);
		}
	}
}
