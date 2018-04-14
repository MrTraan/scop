/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngrasset <ngrasset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/14 16:12:59 by ngrasset          #+#    #+#             */
/*   Updated: 2018/04/14 18:03:59 by ngrasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <scop.h>

void		view_init(t_view *view, t_shader shader)
{
	view->transform_loc = glGetUniformLocation(shader, "model");
	view->view_loc = glGetUniformLocation(shader, "view");
	view->projection_loc = glGetUniformLocation(shader, "projection");
	mat4x4_identity(view->projection);
	mat4x4_perspective(view->projection, TO_RADIAN(45.0f),
			(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 100.0f);
	mat4x4_identity(view->view);
	mat4x4_translate(view->view, (t_v3){0.f, 0.f, -3.f});
	mat4x4_identity(view->transform);
	mat4x4_scale(view->transform, view->transform, 0.3f);
}

void		view_update(t_view *view)
{
	mat4x4_rotate_y(view->transform, view->transform, TO_RADIAN(1.0f));
}

void		view_bind(t_view *view)
{
	glUniformMatrix4fv(view->view_loc, 1, GL_FALSE, view->view);
	glUniformMatrix4fv(view->projection_loc, 1, GL_FALSE, view->projection);
	glUniformMatrix4fv(view->transform_loc, 1, GL_FALSE, view->transform);
}
