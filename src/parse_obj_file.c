/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_obj_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngrasset <ngrasset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/13 19:17:52 by ngrasset          #+#    #+#             */
/*   Updated: 2018/04/15 18:13:18 by ngrasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <scop.h>
#include <libft.h>
#include <stdio.h>

t_uint			count_vertices(char **data)
{
	t_uint		count;
	t_uint		i;

	count = 0;
	i = 0;
	while (data[i] != NULL)
	{
		if (data[i][0] == 'v' && data[i][1] == ' ')
			count++;
		i++;
	}
	return (count);
}

t_uint			count_indices(char **data)
{
	t_uint		count;
	t_uint		i;
	int			holder[4];
	int			matches;

	count = 0;
	i = 0;
	while (data[i] != NULL)
	{
		matches = sscanf(data[i], "f %d %d %d %d",
				holder, holder + 1, holder + 2, holder + 3);
		if (matches == 3)
			count += 3;
		else if (matches == 4)
			count += 6;
		i++;
	}
	return (count);
}

int				parse_vertices(t_model *model, char **data)
{
	int		i;
	int		matches;

	i = 0;
	while (*data)
	{
		if ((*data)[0] == 'v' && (*data)[1] == ' ')
		{
			matches = sscanf(*data, "v %f %f %f\n",
					&(model->vertices[i].coord[0]),
					&(model->vertices[i].coord[1]),
					&(model->vertices[i].coord[2]));
			if (matches != 3)
				return (sc_store_error(SC_ERRNO_OBJ_VERTICES, *data));
			i++;
		}
		data++;
	}
	return (0);
}

int				parse_indices(t_model *model, char **data)
{
	int			i;
	int			matches;
	int			h[4];

	i = 0;
	while (*data)
	{
		if ((*data)[0] == 'f' && (*data)[1] == ' ')
		{
			matches = sscanf(*data, "f %d %d %d %d", h, h + 1, h + 2, h + 3);
			if (matches != 3 && matches != 4)
				return (sc_store_error(SC_ERRNO_OBJ_FACES, *data));
			model->indices[i++] = h[0] - 1;
			model->indices[i++] = h[1] - 1;
			model->indices[i++] = h[2] - 1;
			if (matches == 4)
			{
				model->indices[i++] = h[0] - 1;
				model->indices[i++] = h[2] - 1;
				model->indices[i++] = h[3] - 1;
			}
		}
		data++;
	}
	return (0);
}

t_model			*parse_model_file(char *path)
{
	t_model		*model;
	char		**file_data;

	if ((model = (t_model *)malloc(sizeof(t_model))) == NULL)
	{
		sc_store_error(SC_ERRNO_MEMORY, "");
		return (NULL);
	}
	if ((file_data = read_file(path)) == NULL)
		return (NULL);
	model->vertices_count = count_vertices(file_data);
	model->indices_count = count_indices(file_data);
	if (model->vertices_count == 0 || model->indices_count == 0)
	{
		sc_store_error(SC_ERRNO_OBJ_FILE, "");
		return (NULL);
	}
	model->vertices = malloc(sizeof(t_vertex) * model->vertices_count);
	model->indices = malloc(sizeof(t_uint) * model->indices_count);
	if (parse_vertices(model, file_data) != 0 ||
			parse_indices(model, file_data) != 0)
		return (NULL);
	create_model_uv(model);
	free_string_tab(file_data);
	return (model);
}
