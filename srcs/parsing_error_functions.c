/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_error_functions.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymekraou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/14 11:24:40 by ymekraou          #+#    #+#             */
/*   Updated: 2019/04/14 17:11:44 by ymekraou         ###   ########.fr       */
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

void		invalid_file_error(int fd)
{
	close(fd);
	ft_error("file is empty, incomplete or invalid\n");
}

char		**error_parse_word(char *line)
{
	char	**tab;

	if (!(tab = ft_strsplit(line, ':')) || tab[2] != NULL)
	{
		ft_free_parse(tab, line);
		ft_error("error parse word\n");
	}
	return (tab);
}

void		ft_error(char *msg)
{
	ft_putstr(msg);
	exit(1);
}
