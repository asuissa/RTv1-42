/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymekraou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 02:33:37 by ymekraou          #+#    #+#             */
/*   Updated: 2019/04/10 02:38:21 by ymekraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

void		ft_free_parse(char **tab, char *line)
{
	int		i;

	i = -1;
	while (tab[++i])
		free(tab[i]);
	free(tab);
	free(line);
}

void		ft_error(char *msg)
{
	ft_putstr(msg);
	exit(1);
}
