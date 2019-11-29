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

static	void	ft_free_memory(char **p)
{
	*p = ft_realloc_content("", "");
	free(*p);
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
	while ((rd_status = read(fd, buffer, BUFFER_SIZE)) > 0)
	{	
		buffer[rd_status] = '\0';
		if (ft_analyse(buffer))
		{
			ft_cut_line (buffer, line, remain_str);
			ft_free_memory(&buffer);
			return (ft_returns(rd_status, remain_str));
		}
		*line = ft_realloc_content(*line, buffer); 
	}
	if (!rd_status)
	{
		if (ft_analyse(remain_str))
			ft_cut_line(buffer, line, remain_str);	
		else
		{
			*line = ft_realloc_content(remain_str, "");
			printf("remain: %s\n", remain_str);
			*remain_str = 0;
		}
		ft_free_memory(&buffer);
	}
	return (ft_returns(rd_status, remain_str));
}

//Terminar de chequear liberación de memoria al hacer reallocs
//Chequear returns para que imprima última linea
//Lectura de mútiples fd
//Pasar tests
