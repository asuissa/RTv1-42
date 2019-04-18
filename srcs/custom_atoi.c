/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_double.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymekraou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/09 05:57:35 by ymekraou          #+#    #+#             */
/*   Updated: 2019/04/18 14:16:33 by ymekraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

int				avoid_spacing_char(char *str)
{
	int i;

	i = 0;
	while (str[i] == '\t' || str[i] == '\n' || str[i] == '\v'
			|| str[i] == '\f' || str[i] == '\r' || str[i] == ' ')
		++i;
	return (i);
}

double			ft_atoi_double(char *str)
{
	int		i;
	int		exp;
	double	res;
	char	sign;

	i = avoid_spacing_char(str);
	sign = '+';
	if (str[i] == '+' || str[i] == '-')
		sign = str[i++];
	res = 0;
	while (ft_isdigit(str[i]) != 0)
		res = res * 10 + str[i++] - 48;
	if (str[i] == '.')
	{
		exp = 1;
		while (ft_isdigit(str[++i]) != 0)
			res += (str[i] - 48) / pow(10, exp++);
	}
	if (sign == '-')
		return (-res);
	return (res);
}

int				convert_hexa(char c)
{
	if (c >= '0' && c <= '9')
		return (c - '0');
	if (c >= 'A' && c <= 'F')
		return (10 + (c - 'A'));
	if (c >= 'a' && c <= 'f')
		return (10 + (c - 'a'));
	return (-1);
}

int				ft_atoi_hexa(char *str)
{
	int		i;
	int		res;
	char	sign;

	i = avoid_spacing_char(str);
	sign = '+';
	if (str[i] == '+' || str[i] == '-')
		sign = str[i++];
	res = 0;
	if (convert_hexa(str[i]) == -1)
		return (res);
	while (convert_hexa(str[i]) >= 0)
		res = res * 16 + convert_hexa(str[i++]);
	if (sign == '-')
		return (-res);
	return (res);
}
