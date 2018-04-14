/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat4.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngrasset <ngrasset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 17:00:38 by ngrasset          #+#    #+#             */
/*   Updated: 2018/04/14 17:48:49 by ngrasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_math.h"
#include <string.h>
#include <stdio.h>

static const t_mat4x4 g_mat_identity = {
	1.0f, 0.0f, 0.0f, 0.0f,
	0.0f, 1.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 1.0f, 0.0f,
	0.0f, 0.0f, 0.0f, 1.0f
};

void print_matrix(t_mat4x4 mat) {
	for (int i = 0; i < 4; i++) {
		printf("%d: %f\t%f\t%f\t%f\n", i, MAT_AT(mat, 0, i), MAT_AT(mat, 1, i), MAT_AT(mat, 2, i), MAT_AT(mat, 3, i));
	}
}

void		mat4x4_identity(t_mat4x4 res)
{
	for (int i = 0; i < 16; i++)
		res[i] = g_mat_identity[i];
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

void		mat4x4_rotate_x(t_mat4x4 res, t_mat4x4 source, float angle)
{
	float s;
	float c;
	s = sinf(angle);
	c = cosf(angle);
	t_mat4x4 rot = (t_mat4x4){
		1.f, 0.f, 0.f, 0.f,
		0.f,   c,   s, 0.f,
		0.f,  -s,   c, 0.f,
		0.f, 0.f, 0.f, 1.f
	};
	return mat4x4_mul(res, source, rot);
}

void		mat4x4_rotate_y(t_mat4x4 res, t_mat4x4 source, float angle)
{
	float s;
	float c;
	s = sinf(angle);
	c = cosf(angle);
	t_mat4x4 rot = (t_mat4x4){
		  c, 0.f,   s, 0.f,
		0.f, 1.f, 0.f, 0.f,
		 -s, 0.f,   c, 0.f,
		0.f, 0.f, 0.f, 1.f
	};
	return mat4x4_mul(res, source, rot);
}

void		mat4x4_rotate_z(t_mat4x4 res, t_mat4x4 source, float angle)
{
	float s;
	float c;
	printf("\n\n%f\n\n", angle);
	s = sinf(angle);
	c = cosf(angle);
	t_mat4x4 rot = (t_mat4x4){
		  c,  -s, 0.f, 0.f,
		  s,   c, 0.f, 0.f,
		0.f, 0.f, 1.f, 0.f,
		0.f, 0.f, 0.f, 1.f
	};
	return mat4x4_mul(res, source, rot);
}

void		mat4x4_scale(t_mat4x4 dst, t_mat4x4 src, float scale)
{
	for (int i = 0; i < 12; i++) {
		dst[i] = src[i] * scale;
	}
}

void		mat4x4_translate(t_mat4x4 m, t_v3 transform)
{
	MAT_AT(m, 0, 3) = transform[0];
	MAT_AT(m, 1, 3) = transform[1];
	MAT_AT(m, 2, 3) = transform[2];
}

void		mat4x4_perspective(t_mat4x4 m, float y_fov, float aspect, float n, float f)
{
	float const a = 1.f / (float) tan(y_fov / 2.f);

	MAT_AT(m, 0, 0) = a / aspect;
	MAT_AT(m, 1, 0) = 0.f;
	MAT_AT(m, 2, 0) = 0.f;
	MAT_AT(m, 3, 0) = 0.f;
	MAT_AT(m, 0, 1) = 0.f;
	MAT_AT(m, 1, 1) = a;
	MAT_AT(m, 2, 1) = 0.f;
	MAT_AT(m, 3, 1) = 0.f;
	MAT_AT(m, 0, 2) = 0.f;
	MAT_AT(m, 1, 2) = 0.f;
	MAT_AT(m, 2, 2) = -((f + n) / (f - n));
	MAT_AT(m, 3, 2) = -1.f;
	MAT_AT(m, 0, 3) = 0.f;
	MAT_AT(m, 1, 3) = 0.f;
	MAT_AT(m, 2, 3) = -((2.f * f * n) / (f - n));
	MAT_AT(m, 3, 3) = 0.f;
}
