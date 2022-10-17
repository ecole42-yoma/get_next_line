/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmkim <yongmkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 15:16:16 by yongmkim          #+#    #+#             */
/*   Updated: 2022/02/01 11:57:06 by yongmkim         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	ft_strchr_find_nl(char *s)
{
	int	pos;

	if (!s)
		return (0);
	pos = 0;
	while (s[pos])
	{
		if (s[pos] == '\n')
			return (pos + 1);
		pos++;
	}
	return (0);
}

int	ft_strlen(char *s)
{
	int	len;

	if (!s)
		return (0);
	len = 0;
	while (s[len])
		len++;
	return (len);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*temp;
	int		len_s1;
	int		pos;

	if (!s1 && !s2)
		return (NULL);
	len_s1 = ft_strlen(s1);
	temp = (char *)malloc(sizeof(char) * (len_s1 + ft_strlen(s2) + 1));
	if (!temp)
		return (NULL);
	pos = 0;
	while (s1 && s1[pos])
	{
		temp[pos] = s1[pos];
		pos++;
	}
	while (s2 && s2[pos - len_s1])
	{
		temp[pos] = s2[pos - len_s1];
		pos++;
	}
	temp[pos] = '\0';
	return (temp);
}

char	*ft_strdup(char *s)
{
	char	*temp;
	int		pos;

	if (!ft_strlen(s))
		return (NULL);
	temp = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!temp)
		return (NULL);
	pos = 0;
	while (s && s[pos])
	{
		temp[pos] = s[pos];
		pos++;
	}
	temp[pos] = '\0';
	return (temp);
}

char	*ft_free(char **s1, char **s2, int keyword)
{
	char	*temp;

	if (keyword == FT_DEL)
	{
		if (*s1)
		{
			free(*s1);
			*s1 = NULL;
		}
	}
	else if (keyword == FT_ADD)
	{
		temp = ft_strjoin((char *)*s1, *s2);
		ft_free(s1, NULL, FT_DEL);
		*s1 = temp;
	}
	return (NULL);
}
