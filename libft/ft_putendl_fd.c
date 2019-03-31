/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymekraou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 22:07:08 by ymekraou          #+#    #+#             */
/*   Updated: 2018/11/24 06:46:58 by ymekraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

static void			lft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

static void			lft_putstr_fd(char const *s, int fd)
{
	int		i;

	i = 0;
	while (s[i] != '\0')
	{
		lft_putchar_fd(s[i++], fd);
	}
}

void				ft_putendl_fd(const char *s, int fd)
{
	if (s != NULL)
	{
		lft_putstr_fd(s, fd);
		lft_putchar_fd('\n', fd);
	}
}
