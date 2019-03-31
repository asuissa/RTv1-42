/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymekraou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/16 04:59:43 by ymekraou          #+#    #+#             */
/*   Updated: 2019/03/07 05:31:06 by ymekraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		lft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

int				ft_atoi(const char *str)
{
	int		i;
	int		res;
	char	sign;

	i = 0;
	sign = '+';
	while (str[i] == '\t' || str[i] == '\n' || str[i] == '\v'
			|| str[i] == '\f' || str[i] == '\r' || str[i] == ' ')
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		sign = str[i];
		i++;
	}
	res = 0;
	if (lft_isdigit(str[i]) == 0)
		return (res);
	while (lft_isdigit(str[i]) != 0)
	{
		res = res * 10 + str[i] - 48;
		i++;
	}
	if (sign == '-')
		return (-res);
	return (res);
}
