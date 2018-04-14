/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_math.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngrasset <ngrasset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 16:53:11 by ngrasset          #+#    #+#             */
/*   Updated: 2018/04/14 16:34:43 by ngrasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MATH
# define FT_MATH

# include <math.h>
# define TO_RADIAN(A) (A * (M_PI / 180.0f))
# define MAT_AT(M, X, Y) (M[X + 4 * Y])
# define MAT_IDENTITY ((t_mat4x4){\
		1.0f, 0.0f, 0.0f, 0.0f,\
		0.0f, 1.0f, 0.0f, 0.0f,\
		0.0f, 0.0f, 1.0f, 0.0f,\
		0.0f, 0.0f, 0.0f, 1.0f})

# define FT_MATH_H_DEFINE_VEC(n) \
typedef float t_v##n[n]; \
static inline void t_v##n##_add(t_v##n res, t_v##n const a, t_v##n const b) \
{ \
	int i; \
	for (i = 0; i < n; ++i) \
		res[i] = a[i] + b[i]; \
} \
static inline void t_v##n##_dup(t_v##n dst, t_v##n const src) \
{ \
	int i; \
	for (i = 0; i < n; ++i) \
		dst[i] = src[i]; \
} \
static inline void t_v##n##_sub(t_v##n res, t_v##n const a, t_v##n const b) \
{ \
	int i; \
	for (i = 0; i < n; ++i) \
		res[i] = a[i] - b[i]; \
} \
static inline void t_v##n##_scale(t_v##n res, t_v##n const v, float const s) \
{ \
	int i; \
	for (i = 0; i < n; ++i) \
		res[i] = v[i] * s; \
} \
static inline float t_v##n##_mul_inneres(t_v##n const a, t_v##n const b) \
{ \
	float p = 0.; \
	int i; \
	for (i = 0; i < n; ++i) \
		p += b[i] * a[i]; \
	return p; \
} \
static inline float t_v##n##_len(t_v##n const v) \
{ \
	return (float) sqrt(t_v##n##_mul_inneres(v,v)); \
} \
static inline void t_v##n##_norm(t_v##n res, t_v##n const v) \
{ \
	float k = 1.f / t_v##n##_len(v); \
	t_v##n##_scale(res, v, k); \
}

FT_MATH_H_DEFINE_VEC(2)
FT_MATH_H_DEFINE_VEC(3)
FT_MATH_H_DEFINE_VEC(4)

typedef float		t_mat4x4[16];

void				mat4x4_identity(t_mat4x4 res);
void				mat4x4_mul(t_mat4x4 res, t_mat4x4 a, t_mat4x4 b);
void				mat4x4_rotate_x(t_mat4x4 res, t_mat4x4 source, float angle);
void				mat4x4_rotate_y(t_mat4x4 res, t_mat4x4 source, float angle);
void				mat4x4_rotate_z(t_mat4x4 res, t_mat4x4 source, float angle);
void				mat4x4_scale(t_mat4x4 dst, t_mat4x4 src, float scale);
void				print_matrix(t_mat4x4 mat);
void				mat4x4_dup(t_mat4x4 dest, t_mat4x4 src);
void				mat4x4_perspective(t_mat4x4 m, float y_fov, float aspect, float n, float f);
void				mat4x4_translate(t_mat4x4 m, t_v3 transform);


#endif
