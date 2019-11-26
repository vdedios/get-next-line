#ifndef	GET_NEXT_LINE_H
#define	GET_NEXT_LINE_H

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

int	get_next_line(int fd, char **line);
int     ft_analyse(char *buffer);
char    *ft_realloc_content(char *buffer, char **line);
void    ft_cut_line(char *buffer, char **line, char *remain_str);

#endif
