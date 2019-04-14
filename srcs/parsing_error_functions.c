/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_error_functions.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymekraou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/14 11:24:40 by ymekraou          #+#    #+#             */
/*   Updated: 2019/04/14 19:41:33 by asuissa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

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

int		invalid_read(char *file)
{
	int		fd;
	char	c[1];

	if ((fd = open(file, O_RDONLY)) <= 2)
		ft_error("Error fd open\n");
	if ((read(fd, c, 1)) > 0 && c[0] != 'c')
	{
		close(fd);
		ft_error("Error read\n");
	}
	return (fd);
}

int		ft_isnumber(char *nb)
{
	if (!nb)
		return (0);
	if (*nb == '-' || *nb == '+')
		nb++;
	while (*nb)
	{
		if (!ft_isdigit(*nb))
			return (0);
		nb++;
	}
	return (1);
}

void		invalid_file_error(int fd)
{
	close(fd);
	ft_error("file is empty, incomplete or invalid\n");
}

char		**parse_word(char *line)
{
	char	**tab;

	if (!(tab = ft_strsplit(line, ':')) || tab[2] != NULL)
	{
		free_split_tab(tab);
		return (NULL);
	}
	if (!ft_isnumber(&tab[1][1]) || tab[1][0] != ' ')
	{
		free_split_tab(tab);
		return (NULL);
	}
	return (tab);
}

void		ft_error(char *msg)
{
	ft_putstr(msg);
	exit(1);
}
