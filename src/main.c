/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngrasset <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/27 16:19:46 by ngrasset          #+#    #+#             */
/*   Updated: 2018/04/15 16:35:02 by ngrasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <scop.h>

void				glfw_key_callback(GLFWwindow *window, int key,
		int scancode, int action, int mods)
{
	(void)mods;
	(void)scancode;
	(void)window;
	if (key == GLFW_KEY_T && action == GLFW_RELEASE)
	{
		printf("released key t\n");
	}
}

static void			framebuffer_size_callback(GLFWwindow* window, int width,
		int height)
{
	(void)window;
	glViewport(0, 0, width, height);
}

#include <stdlib.h>

void check_gl_error(void) {
	GLenum err = glGetError();
	if (err != GL_NO_ERROR)
	{

		while(err!=GL_NO_ERROR) {
			switch(err) {
				case GL_INVALID_OPERATION:      printf("INVALID_OPERATION");      break;
				case GL_INVALID_ENUM:           printf("INVALID_ENUM");           break;
				case GL_INVALID_VALUE:          printf("INVALID_VALUE");          break;
				case GL_OUT_OF_MEMORY:          printf("OUT_OF_MEMORY");          break;
				case GL_INVALID_FRAMEBUFFER_OPERATION:  printf("INVALID_FRAMEBUFFER_OPERATION");  break;
			}
			err=glGetError();
		}
		exit (1);
	}
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
	if (window)
	{
		glfwMakeContextCurrent(window);
		glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
		glfwSetKeyCallback(window, glfw_key_callback);
	}
	return (window);
}

static int			setup_opengl(void)
{
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		fprintf(stderr, "Failed to initialize glad\n");
		return (1);
	}
	glEnable(GL_DEPTH_TEST);
	return (0);
}

int					main(int argc, char **argv)
{
	GLFWwindow	*window;
	t_model		*model;
	t_shader	shader; 
	t_view		view;
	t_texture	texture;

	if (argc < 2)
	{
		sc_store_error(SC_ERRNO_NO_ARGUMENT, "");
		return (sc_perror());
	}
	if ((window = create_window()) == NULL || setup_opengl() != 0)
		return (1);
	if ((model = parse_model_file(argv[1])) == NULL)
		return (sc_perror());
	if ((texture = load_texture("./resources/kitten.jpg", GL_RGB)) == SC_TEXTURE_FAILED)
		return (sc_perror());
	if ((shader = compile_shader("./shaders/shader.vs", "./shaders/shader.fs")) == SC_SHADER_FAILED)
		return (sc_perror());
	use_shader(shader);
	view_init(&view, shader);
	create_model_vao(model);
	use_texture(texture);
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		view_update(&view);
		use_shader(shader);
		view_bind(&view);
		draw_model(model);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();
	delete_model(model);
	return (0);
}
