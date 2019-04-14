/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_error_functions.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymekraou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/14 11:24:40 by ymekraou          #+#    #+#             */
/*   Updated: 2019/04/14 11:30:52 by ymekraou         ###   ########.fr       */
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

void		invalid_file_error(int fd)
{
	close(fd);
	ft_error("file is empty, incomplete or invalid\n");
}

void		ft_error(char *msg)
{
	ft_putstr(msg);
	exit(1);
}
