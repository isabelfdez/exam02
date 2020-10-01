#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int		ft_strlen(char *s)
{
	int	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strchr(char *s, char c)
{
	int i, len = 0;
	if (!s)
		return (NULL);
	i = ft_strlen(s);
	while (*s && *s != 'c')
	{
		s++;
		len++;
	}
	if (*s != 'c' && i == len)
		return (NULL);
	return (s);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char *s3;
	int	i = 0;
	if ((s3 = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1))))
		return (NULL);
	while (*s1)
		s3[i++] = *s1++;
	while (*s2)
		s3[i++] = *s2++;
	s3[i] = '\0';
	return (s3);
}

char	*ft_strdup(char *s)
{
	int	i = ft_strlen(s);
	int	j = 0;
	char *d;

	d = malloc(sizeof(char) * (i + 1));
	while (s[j])
	{
		d[j] = s[j];
		j++;
	}
	d[j] = '\0';
	return (d);
}

int 	get_next_line(char **line)
{
	char		buff[512];
	char		*tmp, *tmp1, *tmp2;
	static char	*aux;
	int			n = 0;

	if (!line)
		return (-1);
	while ((ft_strchr(aux, '\n') == NULL))
	{
		n = read(0, buff, 511);
		if (n < 0)
			return (-1);
		if (n == 0)
			break ;
		buff[n] = 0;
		if (!aux)
			aux = ft_strdup(buff);
		else
		{
			tmp = ft_strjoin(aux, buff);
			free(aux);
			aux = tmp;
		}
	}
	if (!n && !aux)
	{
		*line = ft_strdup("");
		return (0);
	}
	if ((tmp = ft_strchr(aux, '\n')))
	{
		*tmp = 0;
		*line = ft_strdup(tmp);
		tmp2 = ft_strdup(tmp++);
		free(aux);
		aux = tmp2;
	}
	else
	{
		*line = ft_strdup(aux);
		free(aux);
		aux = NULL;
	}
	return (1);
}

int main()
{
	char *line;
	int i;
	while (get_next_line(&line))
	{
		printf("%s\n", line);
		i++;
	}
}
