/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngrasset <ngrasset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/20 18:41:07 by ngrasset          #+#    #+#             */
/*   Updated: 2018/04/20 18:42:24 by ngrasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <scop.h>

static void			framebuffer_size_callback(GLFWwindow *window, int width,
		int height)
{
	(void)window;
	glViewport(0, 0, width, height);
}

GLFWwindow			*create_window(void)
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

int					setup_opengl(void)
{
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		return (sc_store_error(SC_ERRNO_GLAD, ""));
	glEnable(GL_DEPTH_TEST);
	return (0);
}
