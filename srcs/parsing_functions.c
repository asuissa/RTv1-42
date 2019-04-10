/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymekraou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 02:33:37 by ymekraou          #+#    #+#             */
/*   Updated: 2019/04/10 22:05:28 by asuissa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

void		ft_free_parse(char **tab, char *line)
{
	int		i;

	i = -1;
	while (tab[++i])
		free(tab[i]);
	if (tab)
		free(tab);
	tab = NULL;
	if (line)
		free(line);
	line = NULL;
}

void		ft_error(char *msg)
{
	ft_putstr(msg);
	exit(1);
}
