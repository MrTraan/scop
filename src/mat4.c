/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat4.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngrasset <ngrasset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 17:00:38 by ngrasset          #+#    #+#             */
/*   Updated: 2018/04/15 17:45:19 by ngrasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_math.h>
#include <string.h>
#include <stdio.h>

t_mat4x4	g_mat_identity = {
	1.0f, 0.0f, 0.0f, 0.0f,
	0.0f, 1.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 1.0f, 0.0f,
	0.0f, 0.0f, 0.0f, 1.0f
};

void		mat4x4_rotate_x(t_mat4x4 res, t_mat4x4 source, float angle)
{
	float		s;
	float		c;
	t_mat4x4	rot;

	s = sinf(angle);
	c = cosf(angle);
	mat4x4_identity(rot);
	rot[5] = c;
	rot[6] = s;
	rot[9] = -s;
	rot[10] = c;
	return (mat4x4_mul(res, source, rot));
}

void		mat4x4_rotate_y(t_mat4x4 res, t_mat4x4 source, float angle)
{
	float		s;
	float		c;
	t_mat4x4	rot;

	s = sinf(angle);
	c = cosf(angle);
	mat4x4_identity(rot);
	rot[0] = c;
	rot[2] = s;
	rot[8] = -s;
	rot[10] = c;
	return (mat4x4_mul(res, source, rot));
}

void		mat4x4_rotate_z(t_mat4x4 res, t_mat4x4 source, float angle)
{
	float		s;
	float		c;
	t_mat4x4	rot;

	s = sinf(angle);
	c = cosf(angle);
	mat4x4_identity(rot);
	rot[0] = c;
	rot[1] = -s;
	rot[4] = s;
	rot[5] = c;
	return (mat4x4_mul(res, source, rot));
}

void		mat4x4_scale(t_mat4x4 dst, t_mat4x4 src, float scale)
{
	int		i;

	i = 0;
	while (i < 12)
	{
		dst[i] = src[i] * scale;
		i++;
	}
}

void		mat4x4_perspective(t_mat4x4 m, float aspect, float n, float f)
{
	float		a;

	a = 1.f / (float)tan(TO_RADIAN(45.0f) / 2.f);
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
