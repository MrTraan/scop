/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngrasset <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/27 14:47:48 by ngrasset          #+#    #+#             */
/*   Updated: 2017/08/27 19:46:25 by ngrasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <scop.h>
#include <stdio.h>
#include <libft.h>
#include <fcntl.h>

int				read_float(char **str, float *dst)
{
	int			i;
	char		*cpy;

	cpy = *str;
	i = 0;
	if (*cpy == '-')
		i++;
	while (ft_isdigit(cpy[i]))
		i++;
	if (cpy[i] != '.')
		return (-1);
	i++;
	while (ft_isdigit(cpy[i]))
		i++;
	if (i >= 255)
		return (-1);
	*dst = strtof(cpy, str);
	return (0);
}

int				read_vertex(char *line, t_obj_file *obj_file)
{
	float		n;
	t_vector3	vertex;

	line += 2;
	if (read_float(&line, &n) != 0)
		return (-1);
	vertex.x = n;
	if (*line != ' ')
		return (-1);
	line++;
	if (read_float(&line, &n) != 0)
		return (-1);
	vertex.y = n;
	if (*line != ' ')
		return (-1);
	line++;
	if (read_float(&line, &n) != 0)
		return (-1);
	vertex.z = n;
	if (*line)
		return (-1);
	ft_lstpush_back(&(obj_file->vertices), ft_lstnew(&vertex, sizeof(t_vector3)));
	return (0);
}

int			read_uv(char *line, t_obj_file *obj_file)
{
	float			n;
	t_vector2		uv;

	line += 3;
	if (read_float(&line, &n) != 0)
		return (-1);
	uv.x = n;
	if (*line != ' ')
		return (-1);
	line++;
	if (read_float(&line, &n) != 0)
		return (-1);
	uv.y = n;
	if (*line)
		return (-1);
	ft_lstpush_back(&(obj_file->uvs), ft_lstnew(&uv, sizeof(t_vector2)));
	return (0);
}

int			read_normal(char *line, t_obj_file *obj_file)
{
	float		n;
	t_vector3	normal;

	line += 3;
	if (read_float(&line, &n) != 0)
		return (-1);
	normal.x = n;
	if (*line != ' ')
		return (-1);
	line++;
	if (read_float(&line, &n) != 0)
		return (-1);
	normal.y = n;
	if (*line != ' ')
		return (-1);
	line++;
	if (read_float(&line, &n) != 0)
		return (-1);
	normal.z = n;
	if (*line)
		return (-1);
	ft_lstpush_back(&(obj_file->normals), ft_lstnew(&normal, sizeof(t_vector3)));
	return (0);
}

int			read_face(char *line, t_obj_file *obj_file)
{
	unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
    int matches = sscanf(line, "f %d/%d/%d %d/%d/%d %d/%d/%d", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2] );
    if (matches != 9) {
        printf("File can't be read by our simple parser : ( Try exporting with other options\n");
        return -1;
    }
	ft_lstpush_back(&(obj_file->vertices), ft_lstnew((t_vector3 *)ft_lstget_data(obj_file->vertices, vertexIndex[0] - 1), sizeof(t_vector3)));
	ft_lstpush_back(&(obj_file->vertices), ft_lstnew((t_vector3 *)ft_lstget_data(obj_file->vertices, vertexIndex[1] - 1), sizeof(t_vector3)));
	ft_lstpush_back(&(obj_file->vertices), ft_lstnew((t_vector3 *)ft_lstget_data(obj_file->vertices, vertexIndex[2] - 1), sizeof(t_vector3)));

	ft_lstpush_back(&(obj_file->uvs), ft_lstnew((t_vector3 *)ft_lstget_data(obj_file->uvs, uvIndex[0] - 1), sizeof(t_vector3)));
	ft_lstpush_back(&(obj_file->uvs), ft_lstnew((t_vector3 *)ft_lstget_data(obj_file->uvs, uvIndex[1] - 1), sizeof(t_vector3)));
	ft_lstpush_back(&(obj_file->uvs), ft_lstnew((t_vector3 *)ft_lstget_data(obj_file->uvs, uvIndex[2] - 1), sizeof(t_vector3)));

	ft_lstpush_back(&(obj_file->normals), ft_lstnew((t_vector3 *)ft_lstget_data(obj_file->normals, normalIndex[0] - 1), sizeof(t_vector3)));
	ft_lstpush_back(&(obj_file->normals), ft_lstnew((t_vector3 *)ft_lstget_data(obj_file->normals, normalIndex[1] - 1), sizeof(t_vector3)));
	ft_lstpush_back(&(obj_file->normals), ft_lstnew((t_vector3 *)ft_lstget_data(obj_file->normals, normalIndex[2] - 1), sizeof(t_vector3)));

	return (0);
}

void do_shit(t_list *elem)
{
	t_vector3 *shit = (t_vector3 *)(elem->content);

	printf("%f %f %f\n", shit->x, shit->y, shit->z);
}

t_obj_file		*load_obj_file(char *path)
{
	t_obj_file	*obj_file;
	int			fd;
	char		*line;

	if (!(obj_file = malloc(sizeof(t_obj_file))))
		return (NULL);
	memset(obj_file, 0, sizeof(t_obj_file));

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (NULL);
	while (get_next_line(fd, &line))
	{
		if (strncmp(line, "v ", 2) == 0)
		{
			if (read_vertex(line, obj_file) != 0)
				return (NULL);
		}
		if (strncmp(line, "vt ", 3) == 0)
		{
			if (read_uv(line, obj_file) != 0)
				return (NULL);
		}
		if (strncmp(line, "vn ", 3) == 0)
		{
			if (read_normal(line, obj_file) != 0)
				return (NULL);
		}
		if (strncmp(line, "f ", 2) == 0)
		{
			if (read_face(line, obj_file) != 0)
				return (NULL);
		}
		free(line);
	}
	ft_lstiter(obj_file->vertices, do_shit);
	return (obj_file);
}
