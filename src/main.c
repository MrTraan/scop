/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngrasset <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/27 16:19:46 by ngrasset          #+#    #+#             */
/*   Updated: 2018/04/20 18:41:02 by ngrasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <scop.h>

static void			read_keyboard(t_app *app)
{
	if (glfwGetKey(app->window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(app->window, GL_TRUE);
	if (glfwGetKey(app->window, GLFW_KEY_UP) == GLFW_PRESS)
		app->view.model_offset[1] += 0.01f;
	if (glfwGetKey(app->window, GLFW_KEY_DOWN) == GLFW_PRESS)
		app->view.model_offset[1] -= 0.01f;
	if (glfwGetKey(app->window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		app->view.model_offset[0] += 0.01f;
	if (glfwGetKey(app->window, GLFW_KEY_LEFT) == GLFW_PRESS)
		app->view.model_offset[0] -= 0.01f;
}

static void			main_loop(t_app *app)
{
	static int		texture_mode = 0;

	if (texture_mode && glfwGetKey(app->window, GLFW_KEY_T) == GLFW_RELEASE)
		texture_mode = !texture_mode;
	if (!texture_mode && glfwGetKey(app->window, GLFW_KEY_T) == GLFW_PRESS)
		texture_mode = !texture_mode;
	glUniform1i(glGetUniformLocation(app->shader, "textureMode"), texture_mode);
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	read_keyboard(app);
	view_update(&(app->view));
	use_shader(app->shader);
	view_bind(&(app->view));
	glBindVertexArray(app->model->vao);
	glDrawElements(GL_TRIANGLES, app->model->indices_count, GL_UNSIGNED_INT, 0);
	glfwSwapBuffers(app->window);
	glfwPollEvents();
}

int					main(int argc, char **argv)
{
	t_app		app;

	if (argc < 2)
	{
		sc_store_error(SC_ERRNO_NO_ARGUMENT, "");
		return (sc_perror());
	}
	if ((app.window = create_window()) == NULL
		|| setup_opengl() != 0
		|| (app.model = parse_model_file(argv[1])) == NULL
		|| (app.texture = load_texture("./assets/kitten.ppm", GL_RGB)) ==
		SC_TEXTURE_FAILED
		|| (app.shader = compile_shader("./shaders/shader.vs",
		"./shaders/shader.fs")) == SC_SHADER_FAILED)
		return (sc_perror());
	view_init(&(app.view), app.shader);
	create_model_vao(app.model);
	use_texture(app.texture);
	while (!glfwWindowShouldClose(app.window))
		main_loop(&app);
	glfwTerminate();
	delete_model(app.model);
	return (0);
}
