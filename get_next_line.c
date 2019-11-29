/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-dios <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 18:21:25 by vde-dios          #+#    #+#             */
/*   Updated: 2019/11/29 21:07:27 by vde-dios         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static	int	ft_returns(ssize_t rd_status, char *remain_str)
{
	if (rd_status < 0)
		return (-1);
	if (rd_status)
		return (1);
	if	(!rd_status)
		if (!*remain_str)
			return (0);
	return (1); 
}

int	get_next_line(int fd, char **line)
{
	ssize_t			rd_status;
	char			*buffer;
	static char 	remain_str[BUFFER_SIZE];
	
	*line = remain_str;
	rd_status = 0;
	if(!(buffer = malloc((BUFFER_SIZE + 1) * sizeof(char))))
		return (-1);
	buffer = ft_realloc_content("", "");
	while ((rd_status = read(fd, buffer, BUFFER_SIZE)) > 0)
	{	
		buffer[rd_status] = '\0';
		if (ft_analyse(buffer))
		{
			ft_cut_line (buffer, line, remain_str);
			free(buffer);
			return (ft_returns(rd_status, remain_str));
		}
		*line = ft_realloc_content(*line, buffer); 
	}
	if (!rd_status)
	{
		if (ft_analyse(remain_str))
			ft_cut_line(buffer, line, remain_str);	
		else
			*line = ft_realloc_content(remain_str, "");
	free(buffer);
	}
	return (ft_returns(rd_status, remain_str));
}
