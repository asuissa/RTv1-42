/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_error_functions.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymekraou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/14 20:05:37 by ymekraou          #+#    #+#             */
/*   Updated: 2019/04/14 20:23:49 by ymekraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	clean_lists(t_light *light, t_elem *elem)
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
