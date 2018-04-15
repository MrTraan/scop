/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngrasset <ngrasset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/14 13:20:14 by ngrasset          #+#    #+#             */
/*   Updated: 2018/04/15 17:17:44 by ngrasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <scop.h>
#include <stdio.h>

static char		g_sc_error_buffer[100] = "";
static int		g_sc_errno = 0;

int				sc_store_error(int errno, char *msg)
{
	if (errno == SC_ERRNO_MEMORY)
		sprintf(g_sc_error_buffer, "Could not allocate memory.%s\n", msg);
	if (errno == SC_ERRNO_OBJ_VERTICES)
		sprintf(g_sc_error_buffer, "Invalid vertex in obj file: %s\n", msg);
	if (errno == SC_ERRNO_OBJ_FACES)
		sprintf(g_sc_error_buffer, "Invalid face in obj file: %s\n", msg);
	if (errno == SC_ERRNO_OPEN_FILE)
		sprintf(g_sc_error_buffer, "Could not open file: %s\n", msg);
	if (errno == SC_ERRNO_NO_ARGUMENT)
		sprintf(g_sc_error_buffer,
				"First argument must be a file name.%s\n", msg);
	if (errno == SC_ERRNO_SHADER_COMP)
		sprintf(g_sc_error_buffer, "Could not compile shader: %s\n", msg);
	if (errno == SC_ERRNO_SHADER_LINK)
		sprintf(g_sc_error_buffer, "Could not link shader: %s\n", msg);
	if (errno == SC_ERRNO_WINDOW)
		sprintf(g_sc_error_buffer, "Could not create glfw window.%s\n", msg);
	if (errno == SC_ERRNO_GLAD)
		sprintf(g_sc_error_buffer, "Failed to initialize glad.%s\n", msg);
	g_sc_errno = errno;
	return (errno);
}

int				sc_perror(void)
{
	fprintf(stderr, "Scop Error: %s\n", g_sc_error_buffer);
	return (g_sc_errno);
}
