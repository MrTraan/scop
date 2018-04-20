/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngrasset <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/27 16:19:46 by ngrasset          #+#    #+#             */
/*   Updated: 2018/04/20 18:22:32 by ngrasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <scop.h>

static void			framebuffer_size_callback(GLFWwindow *window, int width,
		int height)
{
	(void)window;
	glViewport(0, 0, width, height);
}

static GLFWwindow	*create_window(void)
{
	GLFWwindow		*window;

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Scop",
			NULL, NULL);
	if (!window)
	{
		sc_store_error(SC_ERRNO_WINDOW, "");
		return (NULL);
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	return (window);
}

static int			setup_opengl(void)
{
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		return (sc_store_error(SC_ERRNO_GLAD, ""));
	glEnable(GL_DEPTH_TEST);
	return (0);
}

static void			main_loop(t_app *app)
{
	static int		texture_mode = 0;

	if (texture_mode && glfwGetKey(app->window, GLFW_KEY_T) == GLFW_RELEASE)
		texture_mode = !texture_mode;
	if (!texture_mode && glfwGetKey(app->window, GLFW_KEY_T) == GLFW_PRESS)
		texture_mode = !texture_mode;
	glUniform1i(glGetUniformLocation(app->shader, "textureMode"), texture_mode);
	if (glfwGetKey(app->window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(app->window, GL_TRUE);
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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
