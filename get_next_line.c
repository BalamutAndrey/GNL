/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboris <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 14:05:35 by eboris            #+#    #+#             */
/*   Updated: 2019/09/26 18:17:12 by eboris           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

char    *ft_strcpy(char *dst, const char *src)
{
    size_t    i;
    
    i = 0;
    while (src[i] != '\0')
    {
        dst[i] = src[i];
        i++;
    }
    dst[i] = src[i];
    return (dst);
}

void    *ft_memset(void *b, int c, size_t len)
{
    size_t    i;
    
    i = 0;
    while (len > 0)
    {
        ((char *)b)[i] = (unsigned char)c;
        i++;
        len--;
    }
    return (b);
}

void    ft_bzero(void *s, size_t n)
{
    if (n > 0)
        ft_memset(s, 0, n);
}

size_t    ft_strlen(const char *s)
{
    size_t    i;
    
    i = 0;
    while (s[i] != '\0')
    {
        i++;
    }
    return (i);
}

char    *ft_strjoin(char const *s1, char const *s2)
{
    char    *tmp;
    size_t    i;
    size_t    n;
    size_t    s1_l;
    size_t    s2_l;
    
    i = 0;
    n = 0;
    s1_l = ft_strlen(s1);
    s2_l = ft_strlen(s2);
    tmp = malloc((s1_l + s2_l + 1) * sizeof(char));
    if (!(tmp))
        return (NULL);
    while (s1[i] != '\0')
    {
        tmp[i] = s1[i];
        i++;
    }
    while (s2[n] != '\0')
    {
        tmp[i + n] = s2[n];
        n++;
    }
    tmp[i + n] = '\0';
    return (tmp);
}

void    ft_strdel(char **as)
{
    if (*as != NULL)
    {
        free(*as);
        *as = NULL;
    }
}

char    *ft_strdup(const char *s1)
{
    char    *dst;
    
    dst = (char *)malloc((ft_strlen(s1) + 1) * sizeof(char));
    if (dst)
    {
        ft_strcpy(dst, s1);
        return (dst);
    }
    else
    {
        return (NULL);
    }
}

char    *ft_strstr(const char *haystack, const char *needle)
{
    size_t    n;
    size_t    m;
    size_t    z;
    char    *hay;
    char    *need;
    
    need = (char *)needle;
    hay = (char *)haystack;
    n = 0;
    z = ft_strlen(need);
    if (z == 0)
        return (&hay[0]);
    while (hay[n] != '\0')
    {
        m = 0;
        if (hay[n] == need[m])
            while ((hay[n + m] == need[m]) && (m <= z))
            {
                if (m == z - 1)
                    return (&hay[n]);
                m++;
            }
        n++;
    }
    return (NULL);
}

void    *ft_memalloc(size_t size)
{
    int    *tmp;
    
    tmp = malloc(size * sizeof(char));
    if (!tmp)
        return (NULL);
    ft_bzero(tmp, size);
    return (tmp);
}

void    *ft_memcpy(void *dst, const void *src, size_t n)
{
    size_t    i;
    
    i = 0;
    if ((n == 0) || (dst == src))
        return (dst);
    while (i < n)
    {
        ((unsigned char *)dst)[i] = ((unsigned char *)src)[i];
        i++;
    }
    return (dst);
}

t_list    *ft_lstnew(void const *content, size_t content_size)
{
    t_list    *new;
    
    new = malloc(sizeof(t_list));
    if (!(new))
        return (NULL);
    if (content != NULL)
    {
        new->content = malloc(content_size);
        if (!(new->content))
            return (NULL);
        ft_memcpy(new->content, content, content_size);
        new->content_size = content_size;
        new->next = NULL;
    }
    else
    {
        new->content = NULL;
        new->content_size = 0;
        new->next = NULL;
    }
    return (new);
}

char    *ft_strsub(char const *s, unsigned int start, size_t len)
{
    unsigned int    i;
    size_t            n;
    char            *tmp;
    
    i = 0;
    n = 0;
    while ((s[i] != '\0') && (i < start))
        i++;
    if (i != start)
        return (NULL);
    tmp = malloc((len + 1) * sizeof(char));
    if (!(tmp))
        return (NULL);
    while ((s[i] != '\0') && (n < len))
    {
        tmp[n] = s[i];
        i++;
        n++;
    }
    tmp[n] = '\0';
    if (n != len)
        return (NULL);
    return (tmp);
}

static int		gnl_read_file(t_list *list)
{
	int		read_result;
	char	*text;

	if (list->content != NULL)
	{
		free(list->content);
		list->content = NULL;
	}
	if ((text = (char *)malloc(sizeof(char) * (BUFF_SIZE + 1))) == NULL)
		return (-1);
	read_result = read(list->content_size, text, BUFF_SIZE);
	if (read_result < 1)
	{
		ft_strdel(&text);
		return (read_result);
	}
	text[read_result] = '\0';
	if ((list->content = ft_memalloc(read_result + 1)) == NULL)
		return (-1);
	list->content = ft_memcpy(list->content, text, (read_result + 1));
	ft_strdel(&text);
	return (read_result);
}

static int		gnl_write_string(char *text, char **line, t_list *list)
{
	char	*temp;
	char	*temp2;
	int		i;
	int		n;

	if ((text == NULL) || (text[0] == '\0'))
		return (0);
	else if (ft_strstr(text, "\n") == NULL)
	{
		free(list->content);
		list->content = NULL;
		*line = text;
		return (1);
	}
	i = ft_strlen(ft_strstr(text, "\n"));
	n = ft_strlen(text);
	temp = ft_strsub(text, 0, n - i);
	*line = temp;
	temp2 = ft_strsub(text, n - i + 1, i - 1);
	ft_strdel(&text);
	if ((list->content = ft_memalloc(i)) == NULL)
		return (-1);
	list->content = ft_memcpy(list->content, temp2, i);
	ft_strdel(&temp2);
	return (1);
}

static int		gnl_read_string(t_list *list, char **line)
{
	int		f_read;
	char	*text;
	char	*temp;

	text = NULL;
	f_read = 1;
	while (f_read > 0)
	{
		if ((text == NULL) && (list->content != NULL))
			text = ft_strdup(list->content);
		else if ((text != NULL) && (list->content != NULL))
		{
			temp = ft_strjoin(text, list->content);
			ft_strdel(&text);
			text = temp;
		}
		if ((text != NULL) && ((ft_strstr(text, "\n")) || (f_read == 0)))
		{
			f_read = gnl_write_string(text, line, list);
			return (f_read);
		}
		f_read = gnl_read_file(list);
	}
	f_read = gnl_write_string(text, line, list);
	return (f_read);
}

static t_list	*gnl_find_list(int fd)
{
	static t_list	*first_list;
	t_list			*temp;
	t_list			*new;

	if (first_list == NULL)
	{
		if ((first_list = ft_lstnew(NULL, 0)) == NULL)
			return (NULL);
		first_list->content_size = fd;
	}
	temp = first_list;
	while (temp != NULL)
		if ((int)temp->content_size == fd)
			return (temp);
		else if (temp->next != NULL)
			temp = temp->next;
		else
		{
			if ((new = ft_lstnew(NULL, 0)) == NULL)
				return (NULL);
			temp->next = new;
			new->content_size = fd;
		}
	return (NULL);
}

int				get_next_line(const int fd, char **line)
{
	t_list	*list;
	char	a;
	int		exit_code;

	if ((line == NULL) || (fd < 0) || (read(fd, &a, 0) < 0))
	{
		return (-1);
	}
	list = gnl_find_list(fd);
	if (!(list))
	{
		return (-1);
	}
	exit_code = gnl_read_string(list, line);
	return (exit_code);
}
