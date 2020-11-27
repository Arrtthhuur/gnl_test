/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: abeznik <abeznik@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/16 09:47:36 by abeznik       #+#    #+#                 */
/*   Updated: 2020/11/27 16:21:31 by abeznik       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

static char		*ft_strchr(const char *s, int c)
{
	int		i;
	char	*str;

	str = (char *)s;
	if (*str == (char)c)
		return (str);
	i = 1;
	while (str[i - 1])
	{
		if (str[i] == (char)c)
			return (str + i);
		i++;
	}
	return (NULL);
}

static char		*ft_strnew(size_t size)
{
	char	*s;
	size_t	i;

	i = 0;
	s = (char*)malloc(size + 1);
	if (s == NULL)
		return (NULL);
	while (i < size)
	{
		s[i] = '\0';
		i++;
	}
	s[size] = '\0';
	return (s);
}

static void		ft_strdel(char **as)
{
	if (as)
	{
		free(*as);
		*as = NULL;
	}
	return ;
}

static int		ft_new_line(char **stack, char **line, int fd, int ret_read)
{
	int				len;
	char			*tmp_stack;

	printf("\033[1;36m");
	printf("\n");
	printf("[FT_New_Line] Enter\n");
	printf("-------------------\n");
	
	len = 0;
	
	printf("\n");
	printf("[NL - Length compute]\n");
	printf("~~~~~~~~~~~~~~~~~~~~~\n");
	printf("Computing length of string before EOL or EOF\n");
	printf("\n");
	printf("(Stack) Start\n");
	printf("=============\n");
	
	while (stack[fd][len] != '\n' && stack[fd][len] != '\0')
	{
		printf("stack[%d][%d]:	%c\n", fd, len, stack[fd][len]);

		len++;
	}
		
	printf("===========\n");
	printf("(Stack) End\n");
	printf("\n");
	printf("EOL or EOF found at length %d!\n", len);
	printf("\n");

	printf("[NL - EOL or EOF Check]\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~\n");

	if (stack[fd][len] == '\n')
	{
		printf("[NL - EOL]\n");
		printf("~~~~~~~~~~\n");
		printf("\n");
		
		*line = ft_substr(stack[fd], 0, len);
		
		printf("Append substr of stack to line\n");
		printf("\n");
		printf("(Stack) Start\n");
		printf("=============\n");
		printf("%s\n", stack[fd]);
		printf("===========\n");
		printf("(Stack) End\n");
		printf("\n");

		printf("Substr of stack starting from 0 to %d (length) into line: ", len);
		printf("%s\n", *line);
		printf("\n");

		tmp_stack = ft_strdup(stack[fd] + len + 1);

		printf("Duplicating content of updated stack + %d + 1 ...\n", len);
		printf("%s\n", (stack[fd] + len + 1));
		printf("\n");
		printf("... to temporary stack\n");
		printf("%s\n", tmp_stack);
		printf("\n");

		free(stack[fd]);

		printf("Freeing stack\n");
		printf("%s\n", stack[fd]);
		
		stack[fd] = tmp_stack;
		
		printf("Appending temporary stack to freed stack\n");
		printf("(Stack) Start\n");
		printf("=============\n");
		printf("%s\n", stack[fd]);
		printf("===========\n");
		printf("(Stack) End\n");	
		printf("\n");

		printf("[NL - EOF Check]\n");
		printf("\n");

		if (stack[fd][0] == '\0')
		{
			printf("stack[%d][0] = %c\n", fd, stack[fd][0]);

			printf("delete %s[%d]\n", stack[fd], fd);
			
			ft_strdel(&stack[fd]);
		}
		printf("No EOF encountered\n");
		printf("\n");
	}
	else if (stack[fd][len] == '\0')
	{
		printf("[NL - EOF]\n");
		printf("~~~~~~~~~~\n");
		printf("\n");

		printf("Check if number of bytes read is = to buffer size\n");
		printf("\n");

		if (ret_read == BUFFER_SIZE)
		{
			printf("ret_read = %d\n", ret_read);
			printf("BUFFER_SIZE = %d\n", BUFFER_SIZE);

			printf("Return GNL w/ %d & %s \n", fd, *line);
			printf("\n");

			return (get_next_line(fd, line));
		}
		*line = ft_strdup(stack[fd]);

		printf("Duplicating content of updated stack ...\n");
		printf("%s\n", stack[fd]);
		printf("\n");
		printf("... to line\n");
		printf("%s\n", *line);
		printf("\n");

		printf("And delete content of stack\n");
		printf("%s\n", stack[fd]);
		
		ft_strdel(&stack[fd]);
	}

	printf("\n");
	printf("------------------\n");
	printf("[FT_New_Line] Exit\n");
	printf("\n");

	printf("Return (1)\n");
	printf("\n");

	return (1);
	
	printf("\033[0m");
}

int				get_next_line(int fd, char **line)
{
	static char		*stack[42];
	char			heap[BUFFER_SIZE + 1];
	char			*tmp_stack;
	int				ret_read;

	printf("\033[1;32m");
	printf("\n");
	printf("[GNL] Enter\n");
	printf("-----------\n");

	if (fd < 0 || line == NULL)
	{
		printf("[GNL - Error Check]\n");
		printf("fd = %d\n", fd);
		printf("line = %s\n", *line);

		printf("Return (-1)\n");
		printf("\n");

		return (-1);	
	}

	printf("[GNL - Read Loop] Start\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~\n");

	while ((ret_read = read(fd, heap, BUFFER_SIZE)) > 0)
	{
		printf("Opened file descriptor %d, ", fd);
		printf("read %d byte(s) ", ret_read);
		printf("with a buffer (heap) of size %d.\n", BUFFER_SIZE);

		heap[ret_read] = '\0';

		printf("\n");
		printf("(Heap) Start\n");
		printf("============\n");
		printf("%s\n", heap);
		printf("==========\n");
		printf("(Heap) End\n");
		printf("\n");

		if (stack[fd] == NULL)
		{
			printf("[GNL - Empty Stack Check]\n");
			printf("~~~~~~~~~~~~~~~~~~~~~~~~~\n");
			printf("stack[%d] = %s\n", fd, stack[fd]);
			printf("\n");

			stack[fd] = ft_strnew(1);

			printf("[GNL - New Stack]\n");
			printf("~~~~~~~~~~~~~~~~~\n");
			printf("stack[%d] = %s\n", fd, stack[fd]);
			printf("\n");
		}	
		tmp_stack = ft_strjoin(stack[fd], heap);
		
		printf("\n");
		printf("[GNL - Join Stack & Heap]\n");
		printf("~~~~~~~~~~~~~~~~~~~~~~~~~\n");
		printf("Joining stack with heap to temporary stack\n");
		printf("\n");
		printf("(tmp_stack) Start\n");
		printf("=================\n");
		printf("%s\n", tmp_stack);
		printf("===============\n");
		printf("(tmp_stack) End\n");
		printf("\n");

		printf("[GNL - Free Stack]\n");
		printf("~~~~~~~~~~~~~~~~~~\n");
		printf("Freeing previously allocated memory of stack\n");
		printf("\n");

		printf("stack before free: %s\n", stack[fd]);

		free(stack[fd]);

		printf("stack after free: %s\n", stack[fd]);		
		printf("\n");

		stack[fd] = tmp_stack;

		printf("[GNL - Tmp_stack to Stack]\n");
		printf("~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
		printf("Copying temporary stack to freed stack\n");
		printf("\n");
		printf("(Stack) Start\n");
		printf("=============\n");
		printf("%s\n", stack[fd]);
		printf("===========\n");
		printf("(Stack) End\n");
		printf("\n");

		printf("[GNL - Strchr Heap]\n");
		printf("~~~~~~~~~~~~~~~~~~~\n");
		printf("Searching heap for EOL\n");
		printf("\n");
		printf("(Heap) Start\n");
		printf("=============\n");
		printf("%s\n", heap);
		printf("===========\n");
		printf("(Heap) End\n");
		printf("\n");

		if (ft_strchr(heap, '\n'))
		{
			break ;
		}

		printf("No EOL found, looping!\n");
		printf("\n");
	}
	
	printf("EOL found, broke the loop!\n");

	printf("\n");
	printf("~~~~~~~~~~~~~~~~~~~~~\n");
	printf("[GNL - Read Loop] End\n");
	printf("\n");

	if (ret_read < 0)
	{
		printf("[GNL - Read Error Check]\n");
		printf("ret_read = %d\n", ret_read);

		printf("Return (-1)\n");
		printf("\n");

		return (-1);
	}
		
	else if (ret_read == 0 && stack[fd] == NULL)
	{
		printf("[GNL - Read Error & Stack Check]\n");
		printf("The last read returned %d bytes and ", ret_read);
		printf("the stack is %s\n", stack[fd]);

		printf("\n");
		printf("Return (0)\n");
		printf("\n");

		return (0);
	}

	printf("----------\n");
	printf("[GNL] Exit\n");
	printf("\n");

	return (ft_new_line(stack, line, fd, ret_read));

	printf("\033[0m");
}
