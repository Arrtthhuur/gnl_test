/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: abeznik <abeznik@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/16 11:16:37 by abeznik       #+#    #+#                 */
/*   Updated: 2020/11/27 12:20:51 by abeznik       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int			main(void)
{
	char	*line;
	int		fd;
	int		line_nb;

	fd = open("test2.txt", O_RDONLY);
	line_nb = 1;
	while (get_next_line(fd, &line) == 1)
	{
		printf("\033[1;31m");
		printf("Line #%d:	%s\n", line_nb, line);
		printf("\033[0m");
		line_nb++;
	}
	return (0);
}
