/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_labelexist.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbateau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/08 16:33:54 by jbateau           #+#    #+#             */
/*   Updated: 2016/09/08 16:34:43 by jbateau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		ft_labelchr(t_parse *data, char *name)
{
	t_label	*label;

	label = data->label;
	while (label)
	{
		if (label->kind && label->name && !ft_strcmp(label->name, name))
			return (1);
		label = label->next;
	}
	return (0);
}

int		ft_labelexist(t_parse *data)
{
	t_label	*label;

	label = data->label;
	while (label)
	{
		if (!label->kind && label->name && !ft_labelchr(data, label->name))
			return (0);
		label = label->next;
	}
	return (1);
}
