/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-dios <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 18:21:58 by vde-dios          #+#    #+#             */
/*   Updated: 2019/11/29 18:22:01 by vde-dios         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
** Auxiliar functions for get_next_line main function
*/

int	ft_analyse(char *buffer)
{
	int i;
	
	i = 0;
	while (i < BUFFER_SIZE)
		if (buffer[i++] == '\n')
			return (1);
	return (0);
}

char	*ft_realloc_content(char *line, char *buffer)
{
	int	i;
	int	j;
	char	*new_str;
	
	i = 0;
	j = 0;
	while (buffer[i])
		i++;
	while (line[j])
		j++;	
	if (!(new_str =(char *)malloc( (i + j + 1) * sizeof(char))))
		return (NULL);	
	while (*line)
		*new_str++ = *line++;
	while (*buffer)
		*new_str++ = *buffer++; 
	*new_str = '\0';
	return (new_str - i - j);
}

void	ft_cut_line(char *buffer, char **line, char *remain_str)
{
	int i;

	i = 0;
	remain_str = ft_realloc_content(*line, "");
	*line = ft_realloc_content("", "");
	buffer = ft_realloc_content(remain_str, buffer);
	while (buffer[i] != '\n')
		i++;
	buffer[i] = '\0';
	*line = ft_realloc_content(buffer, "");	
	buffer = &buffer[i + 1];
	while (*buffer)
		*remain_str++ = *buffer++;	
	*remain_str = '\0';
} 
