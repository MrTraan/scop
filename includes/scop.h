/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngrasset <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/27 16:28:22 by ngrasset          #+#    #+#             */
/*   Updated: 2018/04/15 16:37:46 by ngrasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCOP_H
# define SCOP_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <ft_math.h>
#include <stb_image.h>

# define SCREEN_WIDTH 800
# define SCREEN_HEIGHT 600
# define SC_ERRNO_MEMORY		1
# define SC_ERRNO_OBJ_VERTICES	2
# define SC_ERRNO_OBJ_FACES		3
# define SC_ERRNO_OPEN_FILE		4
# define SC_ERRNO_NO_ARGUMENT	5
# define SC_ERRNO_SHADER_COMP	6
# define SC_ERRNO_SHADER_LINK	7

# define SC_SHADER_FAILED 		0
# define SC_TEXTURE_FAILED		0

typedef unsigned int	t_uint;
typedef unsigned int	t_shader;
typedef unsigned int	t_texture;

typedef struct			s_vertex
{
	t_v3				coord;
	t_v3				color;
	t_v2				uv;
}						t_vertex;

typedef struct			s_model
{
	t_vertex			*vertices;
	t_uint				vertices_count;
	t_uint				*indices;
	t_uint				indices_count;
	unsigned int		vao;
	unsigned int		vbo;
	unsigned int		ebo;
	t_v2				bounds_x;
	t_v2				bounds_y;
	t_v2				bounds_z;
}						t_model;

typedef struct			s_view
{
	t_mat4x4			projection;
	t_mat4x4			view;
	t_mat4x4			transform;
	t_uint				projection_loc;
	t_uint				view_loc;
	t_uint				transform_loc;
}						t_view;

typedef struct			s_texture_settings
{
	int					width;
	int					height;
	int					nr_channels;
	stbi_uc				*data;
}						t_texture_settings;

char					**read_file(char *path);
char					*read_ol_file(char *path);
t_model					*parse_model_file(char *path);

t_shader				compile_shader(char *vertex_path, char *fragment_path);
void 					use_shader(t_shader s);
void					delete_shader(t_shader s);
void					shader_set_float(t_shader s, char *name, float value);
void					shader_set_int(t_shader s, char *name, int value);
int						check_shader_compilation(t_shader shader);
int						check_shader_linking(t_shader shader);

int						sc_store_error(int errno, char *msg);
int						sc_perror(void);

void					view_bind(t_view *view);
void					view_init(t_view *view, t_shader shader);
void					view_update(t_view *view);

void					draw_model(t_model *model);
void					create_model_vao(t_model *model);
void					create_model_uv(t_model *model);
void					delete_model(t_model *model);

t_texture				load_texture(char *path, GLenum format);
void					use_texture(t_texture t);


void check_gl_error(void);
#endif
