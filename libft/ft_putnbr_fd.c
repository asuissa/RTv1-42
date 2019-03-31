/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymekraou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 23:09:28 by ymekraou          #+#    #+#             */
/*   Updated: 2018/11/22 22:26:19 by ymekraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

static void		lft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void			ft_putnbr_fd(int n, int fd)
{
	if (n < 0)
	{
		if (n == -2147483648)
		{
			ft_putnbr_fd(-2, fd);
			ft_putnbr_fd(147483648, fd);
		}
		else
		{
			lft_putchar_fd('-', fd);
			ft_putnbr_fd(-n, fd);
		}
	}
	else
	{
		if (n >= 0 && n <= 9)
			lft_putchar_fd(n + 48, fd);
		else
		{
			ft_putnbr_fd(n / 10, fd);
			ft_putnbr_fd(n % 10, fd);
		}
	}
}
