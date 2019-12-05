/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-dios <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 18:21:25 by vde-dios          #+#    #+#             */
/*   Updated: 2019/11/29 23:18:24 by vde-dios         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static	void	ft_free_memory(char **p)
{
	*p = NULL;
	free(*p);
}

static int	ft_remain(char **remain_str, char **buffer, char **line)
{
	if (*line)
	{
		if (ft_analyse(*remain_str))
		{
			*remain_str = ft_cut_line(*buffer, line);	
			ft_free_memory(buffer);
			return (1);
		}
		else if (**line)
		{
			*line = ft_realloc_content(*line, "");
			ft_free_memory(buffer);
			ft_free_memory(remain_str);		
		}
	}	
	else
		*line = ft_realloc_content("", "");
	return (0);
}

static	int	ft_keep_reading(ssize_t rd_status, char *buffer, 
	char **remain_str, char **line)
{
	buffer[rd_status] = '\0';
	if (ft_analyse(buffer))
	{
		*remain_str = ft_cut_line(buffer, line);
		ft_free_memory(&buffer);
		return (1);
	}
	*line = ft_realloc_content(*line, buffer);
	return (0);
}

int	get_next_line(int fd, char **line)
{
	ssize_t		rd_status;
	char		*buffer;
	static char 	*remain_str[4096];

	if (!line)
		return (-1);
	*line = remain_str[fd];
	rd_status = 0;
	if(!(buffer = malloc((BUFFER_SIZE + 1) * sizeof(char))))
		return (-1);
	while ((rd_status = read(fd, buffer, BUFFER_SIZE)) > 0)
		if (ft_keep_reading(rd_status, buffer, &remain_str[fd], line))
			return (1);
	if (rd_status < 0)
		return (-1);
	return (ft_remain(&remain_str[fd], &buffer, line));
}
