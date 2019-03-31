/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymekraou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 22:53:46 by ymekraou          #+#    #+#             */
/*   Updated: 2019/02/24 19:03:46 by ymekraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		lft_putchar(char c)
{
	write(1, &c, 1);
}

void			ft_putnbr(int n)
{
	if (n < 0)
	{
		if (n == -2147483648)
		{
			ft_putnbr(-2);
			ft_putnbr(147483648);
		}
		else
		{
			lft_putchar('-');
			ft_putnbr(-n);
		}
	}
	else
	{
		if (n >= 0 && n <= 9)
			lft_putchar(n + 48);
		else
		{
			ft_putnbr(n / 10);
			ft_putnbr(n % 10);
		}
	}
}
