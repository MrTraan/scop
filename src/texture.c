/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngrasset <ngrasset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/15 16:25:36 by ngrasset          #+#    #+#             */
/*   Updated: 2018/04/15 17:55:35 by ngrasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <scop.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <stdio.h>

t_texture		load_texture(char *path, GLenum format)
{
	t_texture			t;
	t_texture_settings	set;

	set.data = stbi_load(path, &(set.width), &(set.height),
			&(set.nr_channels), 0);
	if (!set.data)
	{
		sc_store_error(SC_ERRNO_OPEN_FILE, path);
		return (SC_TEXTURE_FAILED);
	}
	glGenTextures(1, &t);
	glBindTexture(GL_TEXTURE_2D, t);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, set.width, set.height,
			0, format, GL_UNSIGNED_BYTE, set.data);
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(set.data);
	glBindTexture(GL_TEXTURE_2D, 0);
	return (t);
}

void			use_texture(t_texture t)
{
	glBindTexture(GL_TEXTURE_2D, t);
}
