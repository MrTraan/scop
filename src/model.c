/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   model.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngrasset <ngrasset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/14 16:07:17 by ngrasset          #+#    #+#             */
/*   Updated: 2018/04/15 15:43:17 by ngrasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <scop.h>
#include <stdlib.h>

void		create_model_vao(t_model *model)
{
	glGenVertexArrays(1, &(model->vao));
	glGenBuffers(1, &(model->vbo));
	glGenBuffers(1, &(model->ebo));
	glBindVertexArray(model->vao);
	glBindBuffer(GL_ARRAY_BUFFER, model->vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(t_vertex) * model->vertices_count,
			model->vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, model->ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(t_uint) * model->indices_count,
			model->indices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(t_vertex),
			(void *)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(t_vertex),
			(void *)offsetof(t_vertex, color));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(t_vertex),
			(void *)offsetof(t_vertex, uv));
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void		create_model_uv(t_model *model)
{
	t_uint	i;
	t_v2	bounds_x;
	t_v2	bounds_y;
	t_v2	bounds_z;

	i = 0;
	bounds_x[0] = model->vertices[0].coord[0];
	bounds_x[1] = model->vertices[0].coord[0];
	bounds_y[0] = model->vertices[0].coord[1];
	bounds_y[1] = model->vertices[0].coord[1];
	bounds_z[0] = model->vertices[0].coord[2];
	bounds_z[1] = model->vertices[0].coord[2];
	while (i < model->vertices_count)
	{
		model->vertices[i].color[0] = 1.0f / (i % 6 + 1) - 0.15f;
		model->vertices[i].color[1] = 1.0f / (i % 6 + 1) - 0.15f;
		model->vertices[i].color[2] = 1.0f / (i % 6 + 1) - 0.15f;
		if (model->vertices[i].coord[0] < bounds_x[0])
			bounds_x[0] = model->vertices[i].coord[0];
		if (model->vertices[i].coord[0] > bounds_x[1])
			bounds_x[1] = model->vertices[i].coord[0];
		if (model->vertices[i].coord[1] < bounds_y[0])
			bounds_y[0] = model->vertices[i].coord[1];
		if (model->vertices[i].coord[1] > bounds_y[1])
			bounds_y[1] = model->vertices[i].coord[1];
		if (model->vertices[i].coord[2] < bounds_z[0])
			bounds_z[0] = model->vertices[i].coord[2];
		if (model->vertices[i].coord[2] > bounds_z[1])
			bounds_z[1] = model->vertices[i].coord[2];
		i++;
	}
	i = 0;
	while (i < model->vertices_count)
	{
		model->vertices[i].uv[0] = model->vertices[i].coord[2] + bounds_z[0] / (bounds_z[1] + bounds_z[0]);
		model->vertices[i].uv[1] = model->vertices[i].coord[1] + bounds_y[0] / (bounds_y[1] + bounds_y[0]);
		i++;
	}
	model->bounds_x[0] = bounds_x[0];
	model->bounds_x[1] = bounds_x[1];
	model->bounds_y[0] = bounds_y[0];
	model->bounds_y[1] = bounds_y[1];
	model->bounds_z[0] = bounds_z[0];
	model->bounds_z[1] = bounds_z[1];
	
	float middle_x = (model->bounds_x[1] - model->bounds_x[0]) / 2 + model->bounds_x[0];
	float middle_y = (model->bounds_y[1] - model->bounds_y[0]) / 2 + model->bounds_y[0];
	float middle_z = (model->bounds_z[1] - model->bounds_z[0]) / 2 + model->bounds_z[0];
	i = 0;
	while (i < model->vertices_count)
	{
		model->vertices[i].coord[0] -= middle_x;
		model->vertices[i].coord[1] -= middle_y;
		model->vertices[i].coord[2] -= middle_z;
		i++;
	}

}

void		draw_model(t_model *model)
{
	glBindVertexArray(model->vao);
	glDrawElements(GL_TRIANGLES, model->indices_count, GL_UNSIGNED_INT, 0);
}

void		delete_model(t_model *model)
{
	free(model->vertices);
	free(model->indices);
	free(model);
}
