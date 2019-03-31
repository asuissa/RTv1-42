/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymekraou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/24 20:11:25 by ymekraou          #+#    #+#             */
/*   Updated: 2018/12/07 04:59:23 by ymekraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int			deal_end(char **s1)
{
	free(*s1);
	if (!(*s1 = ft_strnew(0)))
		return (0);
	return (1);
}

int			assembly_string(char **s1, char **s2)
{
	char	*stock;
	size_t	i;
	size_t	len;

	i = 0;
	while (*(*s1 + i) != '\n' && *(*s1 + i) != '\0')
		i++;
	if (!(*s2 = ft_strnew(i)))
		return (0);
	ft_memmove(*s2, *s1, i);
	if (*(*s1 + i) == '\0')
		return (deal_end(s1));
	stock = ft_strdup(*s1);
	free(*s1);
	len = ft_strlen(stock) - i - 1;
	*s1 = ft_strnew(len);
	if (!(stock) || !(*s1))
		return (0);
	ft_memmove(*s1, stock + i + 1, len);
	free(stock);
	return (1);
}

char		*custom_strjoin(char **s1, char **s2)
{
	size_t		i;
	size_t		j;
	char		*str;

	if (!(str = ft_strnew(ft_strlen(*s1) + ft_strlen(*s2))))
	{
		free(*s1);
		return (NULL);
	}
	i = -1;
	while (*(*s1 + ++i) != '\0')
		str[i] = *(*s1 + i);
	free(*s1);
	j = 0;
	while (*(*s2 + j) != '\0')
		str[i++] = *(*s2 + j++);
	str[i] = '\0';
	free(*s2);
	return (str);
}

t_list		*fd_finder(const int fd, t_list **head)
{
	t_list				*nav;

	if (fd < 0)
		return (NULL);
	nav = *head;
	while (nav)
	{
		if (nav->content_size == (size_t)fd)
			return (nav);
		nav = nav->next;
	}
	if (!nav)
	{
		if (!(nav = ft_lstnew("", 1)))
			return (NULL);
		nav->content_size = (size_t)(fd);
		ft_lstadd(head, nav);
	}
	return (*head);
}

int			get_next_line(const int fd, char **line)
{
	static t_list		*head = NULL;
	t_list				*tmp;
	char				buf[BUFF_SIZE];
	char				*str;
	int					ret_val;

	if (!(line) || !(tmp = fd_finder(fd, &head)))
		return (-1);
	ret_val = BUFF_SIZE;
	while (!(ft_strchr(tmp->content, '\n')) && ret_val == BUFF_SIZE)
	{
		ret_val = read(fd, buf, BUFF_SIZE);
		if (ret_val == 0)
			break ;
		if (!(str = ft_strnew(ret_val)) || ret_val == -1)
			return (-1);
		ft_memmove(str, buf, ret_val);
		if (!(tmp->content = custom_strjoin((char**)&(tmp->content), &str)))
			return (-1);
	}
	if (ret_val == 0 && *(char*)tmp->content == '\0')
		return (0);
	if (!(assembly_string((char**)&(tmp->content), line)))
		return (-1);
	return (1);
}
