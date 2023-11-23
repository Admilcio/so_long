#include "so_long.h"
#include <fcntl.h> 

static int	ft_nbrlen(int n)
{
	int	i;

	i = 0;
	if (n <= 0)
		i = 1;
	while (n)
	{
		n /= 10;
		++i;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		len;

	len = ft_nbrlen(n);
	str = calloc(len + 1, sizeof(char));
	if (!str)
		return (NULL);
	if (n == 0)
		str[0] = '0';
	if (n < 0)
	{
		str[0] = '-';
		if (n == INT_MIN)
		{
			str[--len] = '8';
			n /= 10;
		}
		n = -n;
	}
	while (len-- && n != 0)
	{
		str[len] = (n % 10) + '0';
		n /= 10;
	}
	return (str);
}

char	*buffer_total_clear(int fd, char **buffer, char *line)
{
	size_t	i;

	if (fd >= 0 && fd < FOPEN_MAX)
	{
		i = 0;
		while (buffer && buffer[fd][i] && i < BUFFER_SIZE)
			buffer[fd][i++] = '\0';
	}
	if (line)
		free(line);
	return (NULL);
}

int	line_updater(char **line, char buffer[])
{
	char	*join;
	int		i;

	join = ft_strjoinm(*line, buffer);
	free(*line);                                  
	if (join == NULL)
		return (-1);
	*line = join;
	i = 0;
	while ((*line)[i] != '\0')
	{
		if ((*line)[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

int	ft_strlenm(char const *s1)
{
	int	i;

	if (s1 == NULL)
		return (0);
	i = 0;
	while (s1[i] != '\0')
	{
		if (s1[i] == '\n')
			return (i + 1);
		i++;
	}
	return (i);
}

char	*ft_strjoinm(char const *s1, char const *s2)
{
	char	*s3;
	int		j;
	int		i;

	s3 = (char *)malloc(ft_strlenm(s1) + ft_strlenm(s2) + 1);
	if (!s3)
		return (s3);
	j = 0;
	i = 0;
	while (s1 != NULL && s1[i] != '\0')
		s3[j++] = s1[i++];
	i = 0;
	while (s2 != NULL && s2[i] != '\0')
	{
		s3[j++] = s2[i++];
		if (s2[i - 1] == '\n')
			break ;
	}
	s3[j] = '\0';
	return (s3);
}

void	buffer_clear(char *buffer)
{
	int	buffer_len;
	int	nr_cases;
	int	i;

	buffer_len = 0;
	while (buffer[buffer_len] != '\0')
		buffer_len++;
	nr_cases = ft_strlenm(buffer);
	i = 0;
	while (i < buffer_len)
	{
		if (nr_cases + i < buffer_len)
		{
			buffer[i] = buffer[nr_cases + i];
			buffer[nr_cases + i] = '\0';
		}
		else
			buffer[i] = '\0';
		i++;
	}
}

void	*ft_calloc(size_t count, size_t size)
{
	size_t	tot_size;
	void	*dst;

	tot_size = size * count;
	dst = malloc(tot_size);
	if (!dst)
		return (0);
	ft_memset(dst, 0, tot_size);
	return (dst);
}

void	*ft_memset(void *b, int c, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		((unsigned char *)b)[i] = c;
		i++;
	}
	return (b);
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	char		*line;
	int			flag;
	int			read_result;

	line = NULL;
	if (BUFFER_SIZE <= 0 || fd < 0 || fd >= FOPEN_MAX)
		return (buffer_total_clear(fd, (char **) buffer, line));
	while (1)
	{
		if (buffer[0] == '\0')
		{
			read_result = read(fd, buffer, BUFFER_SIZE);
			if (read_result == -1)
				return (buffer_total_clear(fd, NULL, line));
			if (read_result == 0)
				return (line);
		}
		flag = line_updater(&line, buffer);
		buffer_clear(buffer);
		
		if (flag == 1)
			return (line);
		if (flag == -1)
			return (NULL);
	}
}