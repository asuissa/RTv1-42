/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_error_functions.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymekraou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/14 11:24:40 by ymekraou          #+#    #+#             */
/*   Updated: 2019/04/18 13:48:31 by ymekraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

void		ft_error(char *msg)
{
	ft_putstr(msg);
	exit(1);
}

void		invalid_file_error(int fd)
{
	close(fd);
	ft_error("file is empty, incomplete or invalid\n");
}

void		invalid_line_error(t_env *env, char *line, int fd)
{
	clean_lists(env->light, env->elem);
	ft_memdel((void**)&line);
	close(fd);
	ft_error("file is not formated correctly\n");
}
