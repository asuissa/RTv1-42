/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line_functions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymekraou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 13:22:28 by ymekraou          #+#    #+#             */
/*   Updated: 2019/04/18 14:19:22 by ymekraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

int		ft_isnumber(char *nb)
{
	int	i;

	i = 0;
	if (!nb)
		return (0);
	if (*nb == '-' || *nb == '+')
		nb++;
	while (*nb)
	{
		if (*nb == '.')
			i++;
		else if (!ft_isdigit(*nb) && *nb != '.')
			return (0);
		nb++;
	}
	if (i > 1 || *(nb - 1) == '.')
		return (0);
	return (1);
}

char	**parse_word(char *line)
{
	char	**tab;

	if (!(tab = ft_strsplit(line, ':')) || tab[2] != NULL)
	{
		free_split_tab(tab);
		return (NULL);
	}
	if ((!ft_isnumber(&tab[1][1]) || tab[1][0] != ' ')
			&& !ft_strstr(tab[0], "color"))
	{
		free_split_tab(tab);
		return (NULL);
	}
	return (tab);
}

void	free_split_tab(char **tab)
{
	int		i;

	i = -1;
	while (tab[++i])
		free(tab[i]);
	if (tab)
		free(tab);
	tab = NULL;
}
