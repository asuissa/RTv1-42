/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymekraou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 20:30:26 by ymekraou          #+#    #+#             */
/*   Updated: 2019/02/24 19:04:50 by ymekraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		lft_putchar(char c)
{
	write(1, &c, 1);
}

static void		lft_putstr(char const *s)
{
	int i;

	i = 0;
	while (s[i] != '\0')
	{
		lft_putchar(s[i++]);
	}
}

void			ft_putendl(char const *s)
{
	if (s != NULL)
	{
		lft_putstr(s);
		lft_putchar('\n');
	}
}
