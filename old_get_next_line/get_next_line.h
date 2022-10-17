/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmkim <yongmkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 15:16:13 by yongmkim          #+#    #+#             */
/*   Updated: 2022/01/30 15:39:36 by yongmkim         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <unistd.h>
# include <stdlib.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 8
# endif

char	*get_next_line(int fd);

int		ft_strchr_find_nl(char *s);
int		ft_strlen(char *s);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strdup(char *s);
void	ft_init_saveline(char **save_line, int *read_size);

#endif
