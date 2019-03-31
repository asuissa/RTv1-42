/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymekraou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 18:32:04 by ymekraou          #+#    #+#             */
/*   Updated: 2018/11/21 19:13:41 by ymekraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static	int		get_abs(int a)
{
	if (a < 0)
		return (-a);
	return (a);
}

static	int		get_digitnb(int n)
{
	int		i;

	i = 0;
	while (n != 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

char			*ft_itoa(int n)
{
	char	*str;
	int		len;

	len = get_digitnb(n);
	if (n <= 0)
		len += 1;
	if (!(str = (char*)malloc(sizeof(char) * (len + 1))))
		return (0);
	str[len--] = '\0';
	if (n == 0)
		str[0] = 48;
	if (n < 0)
		str[0] = '-';
	while (n != 0)
	{
		str[len--] = get_abs(n % 10) + 48;
		n = n / 10;
	}
	return (str);
}
