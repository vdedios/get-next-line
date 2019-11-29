#include "get_next_line.h"

int	get_next_line(int fd, char **line)
{
	ssize_t		rd_status;
	char		*buffer;
	static char 	remain_str[BUFFER_SIZE];
	int		readen;
	
	*line = remain_str;
	readen = 1;
	rd_status = 0;
	if(!(buffer = malloc((BUFFER_SIZE + 1) * sizeof(char))))
		return (-1);
	buffer = ft_realloc_content("", "");
	while ((rd_status = read(fd, buffer, BUFFER_SIZE)) > 0)
	{	
		readen = 0;
		buffer[rd_status] = '\0';
		if (ft_analyse(buffer))
		{
			ft_cut_line (buffer, line, remain_str);
			free(buffer);
			return (rd_status);
		}
		*line = ft_realloc_content(*line, buffer); 
	}
	if (readen)
	{
		if (ft_analyse(buffer))
			ft_cut_line(buffer, line, remain_str);	
		else
			*line = ft_realloc_content(remain_str, "");
	}
	free(buffer);
	return ((int)rd_status);
}

//2- Arreglar que detecte fin de archivo y gestionar returns
//Estudiar cómo hacer para liberar memoria
//Arreglar lineas con sólo salto de linea y testear demás caracteres raro
