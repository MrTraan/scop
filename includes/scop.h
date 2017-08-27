/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngrasset <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/27 16:28:22 by ngrasset          #+#    #+#             */
/*   Updated: 2017/08/27 19:54:50 by ngrasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCOP_H
# define SCOP_H

# include "../libft/includes/libft.h"

typedef struct		s_obj_file
{
	t_list			*vertices;
	t_list			*uvs;
	t_list			*normals;
}					t_obj_file;

typedef struct		s_vector2
{
	float			x;
	float			y;
}					t_vector2;

typedef struct		s_vector3
{
	float			x;
	float			y;
	float			z;
}					t_vector3;

t_obj_file		*load_obj_file(char *path);

#endif
