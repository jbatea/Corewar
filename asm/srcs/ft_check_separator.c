/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_separator.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbateau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/08 16:37:11 by jbateau           #+#    #+#             */
/*   Updated: 2016/09/08 16:51:42 by jbateau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int	ft_check_separator(char *tmp)
{
	int	i;

	i = 0;
	while (tmp[i])
	{
		if (tmp[i] == SEPARATOR_CHAR && tmp[i + 1] &&
				tmp[i + 1] == SEPARATOR_CHAR)
			return (0);
		if (tmp[i] == SEPARATOR_CHAR && !tmp[i + 1])
			return (0);
		i++;
	}
	return (1);
}
