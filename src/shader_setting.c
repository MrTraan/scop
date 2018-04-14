/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader_setting.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngrasset <ngrasset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 12:35:39 by ngrasset          #+#    #+#             */
/*   Updated: 2018/04/14 18:01:49 by ngrasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <scop.h>

void	shader_set_int(t_shader s, char *name, int value)
{
	glUniform1i(glGetUniformLocation(s, name), value);
}

void	shader_set_float(t_shader s, char *name, float value)
{
	glUniform1f(glGetUniformLocation(s, name), value);
}

int		check_shader_compilation(t_shader shader)
{
	int 	success;
	char	info_log[512];

	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shader, 512, NULL, info_log);
		return (sc_store_error(SC_ERRNO_SHADER_COMP, info_log));
	}
	return (0);
}

int		check_shader_linking(t_shader shader)
{
	int 	success;
	char	info_log[512];

	glGetProgramiv(shader, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shader, 512, NULL, info_log);
		return (sc_store_error(SC_ERRNO_SHADER_LINK, info_log));
	}
	return (0);
}
