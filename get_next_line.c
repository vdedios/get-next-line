#include "get_next_line.h"

int	get_next_line(int fd, char **line)
{
	ssize_t		rd_status;
	char		buffer[BUFFER_SIZE];
	static char 	remain_str[BUFFER_SIZE];

	remain_str[0] = 0;
	*line = remain_str;
	while ((rd_status = read(fd, buffer, BUFFER_SIZE)) > 0)
	{	
		if (ft_analyse(buffer))
		{
			ft_cut_line (buffer, line, remain_str);
			return (1);
		}
		*line = ft_realloc_content(buffer, line); 
	}
	return (1);
}
