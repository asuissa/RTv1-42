/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line_functions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymekraou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 13:22:28 by ymekraou          #+#    #+#             */
/*   Updated: 2019/04/19 18:18:47 by ymekraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

void	*free_split_tab(char **tab)
{
	int		i;

	i = -1;
	while (tab[++i])
		free(tab[i]);
	if (tab)
		free(tab);
	tab = NULL;
	return (NULL);
}

int		check_color_format(char *str)
{
	int		i;

	if (str[0] != ' ')
		return (0);
	i = 0;
	while (str[++i])
	{
		if (convert_hexa(str[i]) == -1)
			return (0);
	}
	return (1);
}

int		check_double_format(char *str)
{
	int		i;
	int		dot;

	if (str[0] != ' ')
		return (0);
	i = 0;
	if (str[1] == '+' || str[1] == '-')
		i = 1;
	dot = 0;
	while (str[++i])
	{
		if (str[i] == '.' && dot == 1)
			return (0);
		if (str[i] == '.' && dot == 0)
			dot = 1;
		if (!(ft_isdigit(str[i])) && str[i] != '.')
			return (0);
	}
	return (1);
}

char	**parse_word(char *line)
{
	char	**tab;

	if (!(tab = ft_strsplit(line, ':')))
		return (NULL);
	if (!(tab[1]) || tab[2] || (ft_strlen(tab[1]) > 12))
	{
		free_split_tab(tab);
		return (NULL);
	}
	if (ft_strstr("\tcolor", tab[0]))
	{
		if (!(check_color_format(tab[1])))
			return (free_split_tab(tab));
	}
	else
	{
		if (!(check_double_format(tab[1])))
			return (free_split_tab(tab));
	}
	return (tab);
}
