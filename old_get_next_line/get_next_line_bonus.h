/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmkim <yongmkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 15:16:13 by yongmkim          #+#    #+#             */
/*   Updated: 2022/02/01 12:00:07 by yongmkim         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
# include <unistd.h>
# include <stdlib.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 8
# endif
# define FT_DEL 0
# define FT_NEW 1
# define FT_ADD 2

typedef struct s_list
{
	struct s_list	*next;
	char			*save_line;
	int				fd;
	ssize_t			read_size;
}				t_list;

char	*get_next_line(int fd);

int		ft_strchr_find_nl(char *s);
int		ft_strlen(char *s);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strdup(char *s);
char	*ft_free(char **s1, char **s2, int keyword);

#endif
