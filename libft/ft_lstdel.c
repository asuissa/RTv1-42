/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymekraou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 05:59:55 by ymekraou          #+#    #+#             */
/*   Updated: 2018/11/27 02:20:13 by ymekraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	ft_lstdel(t_list **alst, void (*del)(void*, size_t))
{
	t_list	*stock;
	t_list	*next_link;

	stock = *alst;
	while (stock)
	{
		next_link = stock->next;
		del(stock->content, stock->content_size);
		free(stock);
		stock = next_link;
	}
	(*alst) = NULL;
}
