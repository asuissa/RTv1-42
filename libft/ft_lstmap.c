/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymekraou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 21:22:55 by ymekraou          #+#    #+#             */
/*   Updated: 2018/11/27 02:51:04 by ymekraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static void		emptylist(t_list *head_new)
{
	t_list	*next_link;

	while (head_new)
	{
		next_link = head_new->next;
		free(head_new->content);
		free(head_new);
		head_new = next_link;
	}
}

t_list			*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*new;
	t_list	*head_new;

	if (lst == NULL || f == NULL)
		return (NULL);
	new = f(lst);
	head_new = new;
	while (lst->next)
	{
		new->next = f(lst->next);
		if (new->next == NULL)
		{
			emptylist(head_new);
			return (NULL);
		}
		lst = lst->next;
		new = new->next;
	}
	return (head_new);
}
