/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymekraou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/25 00:33:59 by ymekraou          #+#    #+#             */
/*   Updated: 2019/01/25 16:20:52 by ymekraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include "./libft.h"
# include <stdlib.h>
# include <unistd.h>
# define BUFF_SIZE 5

int						get_next_line(const int fd, char **file);

#endif
