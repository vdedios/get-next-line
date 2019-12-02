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

static	int	ft_returns(ssize_t rd_status, char *remain_str, char *line)
{
	if (rd_status < 0)
		return (-1);
	if (rd_status)
		return (1);
	if (!rd_status)
	{
		if (!remain_str && !line)
			return (0);
		if (remain_str)
			if (!*remain_str && !*line)
				return (0);
	}
	return (1); 
}

static	void	ft_free_memory(char **p)
{
	*p = ft_realloc_content("", "");
	free(*p);
}

int	get_next_line(int fd, char **line)
{
	ssize_t			rd_status;
	char			*buffer;
	static char 	*remain_str[4096];

	*line = remain_str[fd];
	rd_status = 0;
	if(!(buffer = malloc((BUFFER_SIZE + 1) * sizeof(char))))
		return (-1);
	*buffer = '\0';
	while ((rd_status = read(fd, buffer, BUFFER_SIZE)) > 0)
	{	
		buffer[rd_status] = '\0';
		if (ft_analyse(buffer))
		{
			remain_str[fd] = ft_cut_line (buffer, line);
			ft_free_memory(&buffer);
			return (ft_returns(rd_status, remain_str[fd], *line));
		}
		*line = ft_realloc_content(*line, buffer); 
	}
	if (!rd_status)
		if (ft_analyse(remain_str[fd]))
			remain_str[fd] = ft_cut_line(buffer, line);	
	ft_free_memory(&buffer);
	return (ft_returns(rd_status, remain_str[fd], *line));
}
