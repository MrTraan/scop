/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngrasset <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/27 16:19:46 by ngrasset          #+#    #+#             */
/*   Updated: 2017/08/27 20:17:15 by ngrasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <scop.h>
#include <stdio.h>


int		main(int argc, char **argv)
{
	t_obj_file *obj_file;

	if (argc == 1)
		return (0);
	if (!(obj_file = load_obj_file(argv[1])))
	{
		printf("Was there an error?\n");
		return 1;
	}

	t_vector3 *arr;
	t_list *ptr;

	size_t len = ft_lstlen(obj_file->vertices);
	arr = malloc(sizeof(t_vector3) * len);

	ptr = obj_file->vertices;
	for (size_t i = 0; i < len; i++)
	{
		memcpy(arr + i, ptr->content, sizeof(t_vector3));
		ptr = ptr->next;
	}


	return (0);
}
