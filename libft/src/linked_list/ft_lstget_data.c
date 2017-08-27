/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstget_data.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngrasset <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/27 19:02:12 by ngrasset          #+#    #+#             */
/*   Updated: 2017/08/27 19:17:39 by ngrasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	*ft_lstget_data(t_list *list, unsigned int index)
{
	unsigned int		i;

	if (!list)
		return (NULL);
	i = 0;
	while (i < index)
	{
		list = list->next;
		if (!list)
			return (NULL);
		i++;
	}
	return (list->content);
}
