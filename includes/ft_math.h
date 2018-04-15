/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_math.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngrasset <ngrasset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 16:53:11 by ngrasset          #+#    #+#             */
/*   Updated: 2018/04/15 18:00:59 by ngrasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MATH_H
# define FT_MATH_H

# include <math.h>
# define TO_RADIAN(A) (A * (M_PI / 180.0f))
# define MAT_AT(M, X, Y) (M[X + 4 * Y])

typedef float		t_v2[2];
typedef float		t_v3[3];
typedef float		t_mat4x4[16];
extern t_mat4x4		g_mat_identity;

void				mat4x4_identity(t_mat4x4 res);
void				mat4x4_mul(t_mat4x4 res, t_mat4x4 a, t_mat4x4 b);
void				mat4x4_rotate_x(t_mat4x4 res, t_mat4x4 source, float angle);
void				mat4x4_rotate_y(t_mat4x4 res, t_mat4x4 source, float angle);
void				mat4x4_rotate_z(t_mat4x4 res, t_mat4x4 source, float angle);
void				mat4x4_scale(t_mat4x4 dst, t_mat4x4 src, float scale);
void				print_matrix(t_mat4x4 mat);
void				mat4x4_dup(t_mat4x4 dest, t_mat4x4 src);
void				mat4x4_perspective(t_mat4x4 m, float a, float n, float f);
void				mat4x4_translate(t_mat4x4 m, t_v3 transform);

#endif
