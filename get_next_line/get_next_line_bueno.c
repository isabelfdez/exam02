
#include <stdio.h>

size_t ft_strlen(char *s)
{
    size_t i = 0;
    while (s[i] != '\0')
        i++;
    return(i);
}
char    *ft_strchr(char *str, int c)
{
    unsigned int i = 0, len;
    if(!str)
        return(NULL);
    len = ft_strlen(str);
    while (*str && *str != c)
    {
        i++;
        str++;
    }
    if ((*str != c && i == len))
        return (NULL);
    return(str);
}
char *ft_strjoin(char *s1, char *s2)
{
    int i = 0;
    char *dest;
    if (!(dest = malloc(ft_strlen(s1) + ft_strlen(s2)+ 1)))
        return (NULL);
    while (*s1 != '\0')
        dest[i++] = *s1++;
    while (*s2 != '\0')
        dest[i++] = *s2++;
    dest[i] = '\0';
    return (dest);
}
char *ft_strdup(char *str)
{
    int i = 0;
    char *dest;
    if (!(dest = malloc(ft_strlen(str) + 1)))
        return (NULL);
    while(str[i] != '\0')
    {
        dest[i] = str[i];
        i++;
    }
    dest[i] = '\0';
    return (dest);
}
int     get_next_line(char **line)
{
    static char	*aux;
    char		buffer[512];
    int			n;
    char		*temp, *temp1, *temp2;
    if(!line)
        return(-1);
    while (ft_strchr(aux, '\n') == NULL)
    {
        n = read(0, buffer, 511);
        if (n < 0)
            return(-1);
        if (n == 0)
            break;
        buffer[n] = 0;
        if(!aux)
            aux = ft_strdup(buffer);
        else
        {
            temp = ft_strjoin(aux, buffer);
            free (aux);
            aux = temp;
        }
    }
    if (!n && !*aux)
    {
        *line = ft_strdup("");
        return(0);
    }
    if ((temp1 = ft_strchr(aux, '\n')))
    {
        *temp1 = 0;
        *line = ft_strdup(aux);
        temp2 = ft_strdup(++temp1);
        free(aux);
        aux = temp2;
    }
    else
    {
        *line = ft_strdup(aux);
        free(aux);
        aux = NULL;
        return(0);
    }
    return (1);    
}