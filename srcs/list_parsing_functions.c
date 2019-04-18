/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_parsing_functions.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymekraou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/14 20:05:37 by ymekraou          #+#    #+#             */
/*   Updated: 2019/04/18 14:17:35 by ymekraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

void		clean_lists(t_light *light, t_elem *elem)
{
	t_light	*tmp_light;
	t_elem	*tmp_elem;

	while (light)
	{
		tmp_light = light->next;
		free(light);
		light = tmp_light;
	}
	while (elem)
	{
		tmp_elem = elem->next;
		free(elem);
		elem = tmp_elem;
	}
}

t_light		*get_last_light(t_light **head)
{
	t_light	*tmp;

	if (!(*head))
	{
		if (!(*head = (t_light*)malloc(sizeof(t_light))))
			return (NULL);
		(*head)->next = NULL;
		return (*head);
	}
	else
	{
		tmp = *head;
		while (tmp->next)
			tmp = tmp->next;
		if (!(tmp->next = (t_light*)malloc(sizeof(t_light))))
			return (NULL);
		tmp->next->next = NULL;
		return (tmp->next);
	}
}

t_elem		*get_last_elem(t_elem **head)
{
	t_elem	*tmp;

	if (!(*head))
	{
		if (!(*head = (t_elem*)malloc(sizeof(t_elem))))
			return (NULL);
		(*head)->next = NULL;
		return (*head);
	}
	else
	{
		tmp = *head;
		while (tmp->next)
			tmp = tmp->next;
		if (!(tmp->next = (t_elem*)malloc(sizeof(t_elem))))
			return (NULL);
		tmp->next->next = NULL;
		return (tmp->next);
	}
}
