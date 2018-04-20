/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngrasset <ngrasset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/15 16:25:36 by ngrasset          #+#    #+#             */
/*   Updated: 2018/04/20 18:22:49 by ngrasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <scop.h>
#include <stdio.h>
#include <stdlib.h>

int			load_ppm(char *path, t_texture_settings *img)
{
	unsigned int	n;
	FILE			*fd;
	int				match;
	
	fd = fopen(path, "rb");
	match = fscanf(fd, "P6\n%d %d\n255\n", &(img->width), &(img->height));
	if (match != 2)
		return (1);
	n = img->width * img->height;
	img->data = (char *)malloc(sizeof(unsigned int) * 3 * n);
	fread(img->data, sizeof(unsigned int) * 3, n, fd);
	fflush(fd);
	return (0);
}

t_texture		load_texture(char *path, GLenum format)
{
	t_texture			t;
	t_texture_settings	set;

	if (load_ppm(path, &set) != 0)
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
	free(set.data);
	glBindTexture(GL_TEXTURE_2D, 0);
	return (t);
}

void			use_texture(t_texture t)
{
	glBindTexture(GL_TEXTURE_2D, t);
}
