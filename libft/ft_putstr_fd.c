/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymekraou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 21:56:44 by ymekraou          #+#    #+#             */
/*   Updated: 2019/02/24 19:04:27 by ymekraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		lft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void			ft_putstr_fd(char const *s, int fd)
{
	int		i;

	if (s != NULL)
	{
		i = 0;
		while (s[i] != '\0')
		{
			lft_putchar_fd(s[i++], fd);
		}
	}
}
