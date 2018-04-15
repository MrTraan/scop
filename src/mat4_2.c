/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat4_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngrasset <ngrasset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/15 17:30:52 by ngrasset          #+#    #+#             */
/*   Updated: 2018/04/15 17:45:43 by ngrasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_math.h>
#include <string.h>
#include <stdio.h>

void		print_matrix(t_mat4x4 mat)
{
	int		i;

	i = 0;
	while (i < 4)
	{
		printf("%d: %f\t%f\t%f\t%f\n", i, MAT_AT(mat, 0, i),
				MAT_AT(mat, 1, i), MAT_AT(mat, 2, i), MAT_AT(mat, 3, i));
		i++;
	}
}

void		mat4x4_identity(t_mat4x4 res)
{
	int		i;

	i = 0;
	while (i < 16)
	{
		res[i] = g_mat_identity[i];
		i++;
	}
}

void		mat4x4_dup(t_mat4x4 dest, t_mat4x4 src)
{
	memcpy(dest, src, sizeof(t_mat4x4));
}

void		mat4x4_mul(t_mat4x4 res, t_mat4x4 a, t_mat4x4 b)
{
	int			c;
	int			r;
	int			k;
	t_mat4x4	tmp;

	memset(tmp, 0, sizeof(t_mat4x4));
	c = 0;
	while (c < 4)
	{
		r = 0;
		while (r < 4)
		{
			k = 0;
			while (k < 4)
			{
				MAT_AT(tmp, c, r) += MAT_AT(a, k, r) * MAT_AT(b, c, k);
				k++;
			}
			r++;
		}
		c++;
	}
	mat4x4_dup(res, tmp);
}

void		mat4x4_translate(t_mat4x4 m, t_v3 transform)
{
	MAT_AT(m, 0, 3) = transform[0];
	MAT_AT(m, 1, 3) = transform[1];
	MAT_AT(m, 2, 3) = transform[2];
}
