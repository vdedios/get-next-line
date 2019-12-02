/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-dios <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 18:21:58 by vde-dios          #+#    #+#             */
/*   Updated: 2019/11/29 23:12:53 by vde-dios         ###   ########.fr       */
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
	if (buffer)
		while (buffer[i])
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
	if (line)
		while (line[i])
			i++;	
	while (buffer[j])
		j++;
	if (!(new_str =(char *)malloc( (i + j + 1) * sizeof(char))))
		return (NULL);	
	if (line)
		while (*line)
			*new_str++ = *line++;
	while (*buffer)
		*new_str++ = *buffer++; 
	*new_str = '\0';
	return (new_str - i - j);
}

char	*ft_cut_line(char *buffer, char **line)
{
	int i;
	int j;

	i = 0;
	j = 0;	
	buffer = ft_realloc_content(*line, buffer);
	while (buffer[i] != '\n')
		i++;
	while (buffer[j])
		j++;
	buffer[i] = '\0';
	*line = ft_realloc_content(buffer, "");	
	if (j - 1 ==  i)
		return (ft_realloc_content("", ""));
	return (ft_realloc_content(&buffer[i + 1], ""));
} 
