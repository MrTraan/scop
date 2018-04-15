/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngrasset <ngrasset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 11:11:51 by ngrasset          #+#    #+#             */
/*   Updated: 2018/04/15 18:04:10 by ngrasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <scop.h>
#include <stdlib.h>

t_shader	load_shader(char *path, GLenum type)
{
	t_shader	id;
	char		*file;

	if ((file = read_ol_file(path)) == NULL)
		return (SC_SHADER_FAILED);
	id = glCreateShader(type);
	glShaderSource(id, 1, (const GLchar *const *)&file, NULL);
	glCompileShader(id);
	if (check_shader_compilation(id) != 0)
		return (SC_SHADER_FAILED);
	free(file);
	return (id);
}

t_shader	compile_shader(char *vertex_path, char *fragment_path)
{
	t_shader	program;
	t_shader	shaders[2];

	shaders[0] = load_shader(vertex_path, GL_VERTEX_SHADER);
	shaders[1] = load_shader(fragment_path, GL_FRAGMENT_SHADER);
	if (shaders[0] == SC_SHADER_FAILED || shaders[1] == SC_SHADER_FAILED)
		return (SC_SHADER_FAILED);
	program = glCreateProgram();
	glAttachShader(program, shaders[0]);
	glAttachShader(program, shaders[1]);
	glLinkProgram(program);
	glDeleteShader(shaders[0]);
	glDeleteShader(shaders[1]);
	if ((check_shader_linking(program)) != 0)
		return (SC_SHADER_FAILED);
	use_shader(program);
	return (program);
}

void		use_shader(t_shader s)
{
	glUseProgram(s);
}

void		delete_shader(t_shader s)
{
	glDeleteProgram(s);
}
