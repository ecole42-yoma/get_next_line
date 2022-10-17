/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmkim <yongmkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 15:16:22 by yongmkim          #+#    #+#             */
/*   Updated: 2022/02/01 17:16:36 by yongmkim         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static t_list	*ft_list_init(t_list **head, int fd, int keyword)
{
	t_list	*temp;

	if (keyword == FT_DEL)
	{
		ft_free(&((*head)->save_line), NULL, FT_DEL);
		free(*head);
		*head = NULL;
		return (NULL);
	}
	temp = malloc(sizeof(t_list) * 1);
	if (!temp)
		return (NULL);
	temp->fd = fd;
	temp->save_line = ft_strdup("");
	if (!*head)
	{
		temp->next = NULL;
		temp->read_size = BUFFER_SIZE;
	}
	else
	{
		temp->next = (*head)->next;
		(*head)->next = temp;
	}
	return (temp);
}

static t_list	*ft_list_find(t_list **head, ssize_t fd, int keyword)
{
	t_list	*lead;
	t_list	*follow;

	lead = *head;
	while (lead)
	{
		if (lead->fd == fd)
		{
			if (keyword == FT_ADD)
				return (lead);
			else if (keyword == FT_DEL)
			{
				follow->next = lead->next;
				ft_list_init(&lead, 0, FT_DEL);
				if (!(follow->next) && follow == *head)
					return (ft_list_init(head, 0, FT_DEL));
				return (NULL);
			}
		}
		follow = lead;
		lead = lead->next;
	}
	return (ft_list_init(head, fd, FT_NEW));
}

static char	*ft_send_line_without_nl(t_list **head, t_list **temp)
{
	char	*send_line;

	if (!((*temp)->save_line))
		ft_list_find(head, (*temp)->fd, FT_DEL);
	else if (((*temp)->save_line)[0] == '\0')
		ft_list_find(head, (*temp)->fd, FT_DEL);
	else if (ft_strlen((*temp)->save_line))
	{
		send_line = ft_strdup((*temp)->save_line);
		ft_list_find(head, (*temp)->fd, FT_DEL);
		return (send_line);
	}
	return (NULL);
}

static char	*ft_send_line(t_list **head, t_list **temp, char **buf, ssize_t r_s)
{
	char	*send_line;
	char	*remain_line;
	ssize_t	pos_rear;

	if (r_s < 0)
		return (ft_free(buf, NULL, FT_DEL));
	ft_free(buf, NULL, FT_DEL);
	pos_rear = ft_strchr_find_nl((*temp)->save_line);
	remain_line = NULL;
	send_line = NULL;
	if (pos_rear)
	{
		if (((*temp)->save_line)[pos_rear] != '\0')
		{
			((*temp)->save_line)[pos_rear - 1] = '\0';
			remain_line = ft_strdup(&((*temp)->save_line)[pos_rear]);
			send_line = ft_strjoin((*temp)->save_line, "\n");
		}
		else
			send_line = ft_strdup((*temp)->save_line);
		ft_free(&((*temp)->save_line), NULL, FT_DEL);
		(*temp)->save_line = remain_line;
		return (send_line);
	}
	return (ft_send_line_without_nl(head, temp));
}

char	*get_next_line(int fd)
{
	static t_list	*head;
	t_list			*temp;
	char			*buf;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, NULL, 0) < 0)
		return (NULL);
	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!head)
		head = ft_list_init(&head, -1, FT_NEW);
	if (!head || !buf)
		return (ft_free(&buf, (char **)ft_list_find(&head, 0, FT_DEL), FT_DEL));
	temp = ft_list_find(&head, fd, FT_ADD);
	if (!temp)
		return (ft_free(&buf, NULL, FT_DEL));
	while (1)
	{
		if (ft_strchr_find_nl(temp->save_line))
			return (ft_send_line(&head, &temp, &buf, temp->read_size));
		temp->read_size = read(fd, buf, BUFFER_SIZE);
		if (temp->read_size <= 0)
			break ;
		buf[temp->read_size] = '\0';
		ft_free(&(temp->save_line), &buf, FT_ADD);
	}
	return (ft_send_line(&head, &temp, &buf, temp->read_size));
}
