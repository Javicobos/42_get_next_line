/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcobos-d <jcobos-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 15:47:18 by jcobos-d          #+#    #+#             */
/*   Updated: 2022/05/10 16:08:43 by jcobos-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd);
char	*ft_strjoin_len(char *s1, char *s2, int len_2);
char	*nl_saved(char **savedline);
char	*read_problems(char **savedline, char *mybuffer, ssize_t readreturn);
char	*line_returner(char **savedline, char *mybuffer, ssize_t readreturn);

char	*get_next_line(int fd)
{
	static char	*savedline;
	char		*mybuffer;
	ssize_t		readreturn;

	if (savedline && ft_strchr(savedline, '\n'))
		return (nl_saved(&savedline));
	mybuffer = malloc(BUFFER_SIZE + 1);
	if (!(mybuffer))
		return (0);
	readreturn = read(fd, mybuffer, BUFFER_SIZE);
	if (readreturn == -1 || readreturn == 0)
		return (read_problems(&savedline, mybuffer, readreturn));
	mybuffer[readreturn] = '\0';
	if (ft_strchr(mybuffer, '\n') || readreturn < BUFFER_SIZE)
		return (line_returner(&savedline, mybuffer, readreturn));
	savedline = ft_strjoin_len(savedline, mybuffer, ft_strlen(mybuffer));
	free(mybuffer);
	return (get_next_line(fd));
}

char	*ft_strjoin_len(char *s1, char *s2, int len_2)
{
	char	*goal;
	int		len_1;
	int		len_goal;

	len_1 = ft_strlen((char *)s1);
	len_goal = len_1 + len_2;
	goal = malloc(len_goal + 1);
	if (!goal)
		return (0);
	ft_memcpy(goal, s1, len_1);
	ft_memcpy(goal + len_1, s2, len_2);
	goal[len_goal] = '\0';
	free(s1);
	return (goal);
}

char	*nl_saved(char **savedline)
{
	char	*postbuffer;
	char	*returnline;
	int		newcharacters;

	postbuffer = ft_strdup(ft_strchr(*savedline, '\n'));
	newcharacters = ft_strchr(*savedline, '\n') - *savedline + 1;
	returnline = malloc(newcharacters + 1);
	ft_strlcpy(returnline, *savedline, newcharacters + 1);
	free(*savedline);
	if (ft_strlen(postbuffer) > 1)
		*savedline = ft_strdup(postbuffer + 1);
	else
		*savedline = 0;
	free(postbuffer);
	return (returnline);
}

char	*read_problems(char **savedline, char *mybuffer, ssize_t readreturn)
{
	char	*returnline;

	free(mybuffer);
	if (readreturn == 0 && *savedline)
	{
		returnline = ft_strdup(*savedline);
		free(*savedline);
		*savedline = 0;
		return (returnline);
	}
	return (0);
}

char	*line_returner(char **savedline, char *mybuffer, ssize_t readreturn)
{
	char	*postbuffer;
	int		newcharacters;
	char	*returnline;

	postbuffer = ft_strchr(mybuffer, '\n');
	if (postbuffer)
	{
		newcharacters = postbuffer - mybuffer + 1;
		returnline = ft_strjoin_len(*savedline, mybuffer, newcharacters);
		if (ft_strlen(postbuffer) > 1)
			*savedline = ft_strdup(postbuffer + 1);
		else
			*savedline = 0;
	}
	else
	{
		returnline = ft_strjoin_len(*savedline, mybuffer, readreturn);
		*savedline = 0;
	}
	free(mybuffer);
	return (returnline);
}
