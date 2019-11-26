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

char	*ft_realloc_content(char *buffer, char **line)
{
	int	i;
	int	j;
	char	*new_str;
	
	i = 0;
	j = 0;
	while (buffer[i])
		i++;
	while ((*line)[j])
		j++;	
	if (!(new_str =(char *)malloc( (i + j + 1) * sizeof(char))))
		return (NULL);	
	while (**line)
		*new_str++ = *(*line)++;
	while (*buffer)
		*new_str++ = *buffer++; 
	*new_str = '\0';
	return (new_str - i - j);
}

void	ft_cut_line(char *buffer, char **line, char *remain_str)
{
	int i;

	i = 0;
	while (*buffer != '\n')
		remain_str[i++] = *buffer++;
	remain_str[i] = '\0';
	*line = ft_realloc_content(remain_str, line);		
	buffer++;
	while (*buffer)
		*remain_str++ = *buffer++;	
	*remain_str = '\0';
} 
