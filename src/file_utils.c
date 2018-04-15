/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngrasset <ngrasset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/13 19:18:44 by ngrasset          #+#    #+#             */
/*   Updated: 2018/04/15 17:01:34 by ngrasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <libft.h>
#include <scop.h>

char	**read_file(char *path)
{
	char		*buffer;
	char		**lines;
	FILE		*fh;
	long		size;

	if ((fh = fopen(path, "r")) == NULL)
	{
		sc_store_error(SC_ERRNO_OPEN_FILE, path);
		return (NULL);
	}
	fseek(fh, 0L, SEEK_END);
	size = ftell(fh);
	rewind(fh);
	if ((buffer = (char *)malloc(size + 1)) == NULL)
	{
		fclose(fh);
		sc_store_error(SC_ERRNO_MEMORY, "");
		return (NULL);
	}
	fread(buffer, size, 1, fh);
	buffer[size] = '\0';
	fclose(fh);
	lines = ft_strsplit(buffer, '\n');
	free(buffer);
	return (lines);
}

char	*read_ol_file(char *path)
{
	char		*buffer;
	FILE		*fh;
	long		size;

	if ((fh = fopen(path, "r")) == NULL)
	{
		sc_store_error(SC_ERRNO_OPEN_FILE, path);
		return (NULL);
	}
	fseek(fh, 0L, SEEK_END);
	size = ftell(fh);
	rewind(fh);
	if ((buffer = (char *)malloc(size + 1)) == NULL)
	{
		fclose(fh);
		sc_store_error(SC_ERRNO_MEMORY, "");
		return (NULL);
	}
	fread(buffer, size, 1, fh);
	buffer[size] = '\0';
	fclose(fh);
	return (buffer);
}
