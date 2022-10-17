/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmkim <yongmkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 15:16:22 by yongmkim          #+#    #+#             */
/*   Updated: 2022/01/30 15:47:09 by yongmkim         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_free(char **s)
{
	if (*s)
	{
		free(*s);
		*s = NULL;
	}
	return (NULL);
}

static char	*ft_send_line_without_nl(char **line)
{
	char	*temp;

	if ((*line)[0] == '\0')
		ft_free(line);
	else if (ft_strlen(*line))
	{
		temp = ft_strdup(*line);
		ft_free(line);
		return (temp);
	}
	return (NULL);
}

static char	*ft_send_line(char **save_line, char **read_buf, int read_size)
{
	char	*send_line;
	char	*remain_line;
	int		pos;

	ft_free(read_buf);
	if (!*save_line || read_size < 0)
		return (NULL);
	pos = ft_strchr_find_nl(*save_line);
	remain_line = NULL;
	if (pos)
	{
		if ((*save_line)[pos] != '\0')
		{
			(*save_line)[pos - 1] = '\0';
			remain_line = ft_strdup(*save_line + pos);
			send_line = ft_strjoin(*save_line, "\n");
		}
		else
			send_line = ft_strdup(*save_line);
		ft_free(save_line);
		*save_line = remain_line;
		return (send_line);
	}
	return (ft_send_line_without_nl(save_line));
}

char	*get_next_line(int fd)
{
	static char	*save_line;
	char		*temp;
	char		*read_buf;
	int			read_size;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, NULL, 0) < 0)
		return (NULL);
	read_buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!read_buf)
		return (NULL);
	if (!save_line)
		ft_init_saveline(&save_line, &read_size);
	while (1)
	{
		if (ft_strchr_find_nl(save_line))
			return (ft_send_line(&save_line, &read_buf, read_size));
		read_size = read(fd, read_buf, BUFFER_SIZE);
		if (read_size <= 0)
			break ;
		read_buf[read_size] = '\0';
		temp = ft_strjoin(save_line, read_buf);
		ft_free(&save_line);
		save_line = temp;
	}
	return (ft_send_line(&save_line, &read_buf, read_size));
}
