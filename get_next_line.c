/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcobos-d <jcobos-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 15:47:18 by jcobos-d          #+#    #+#             */
/*   Updated: 2022/05/02 18:01:43 by jcobos-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd);
char	*ft_strchr(const char *s, int c);
char	*ft_strjoin_len(char *s1, char *s2, int len_2);
void	*ft_memcpy(void *dest, const void *src, size_t n);
size_t	ft_strlen(const char *str);
char	*ft_strdup(const char *src);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);

char *get_next_line(int fd)
{
	static char	*savedline;
	char	*mybuffer;
	char	*returnline;
	char	*postbuffer;
	int		newcharacters;

	if (savedline && ft_strchr(savedline, '\n')) //todo este trozo es un mierdón
	{
		postbuffer = ft_strchr(savedline, '\n');
		newcharacters = postbuffer - savedline + 1;
		returnline = malloc(newcharacters + 1);
		ft_strlcpy(returnline, savedline, newcharacters + 1);
		free(savedline);
		if (ft_strlen(postbuffer) > 1)
		{
			savedline = ft_strdup(postbuffer + 1);
		}
		else
			savedline = 0;
		return (returnline);
	}

	mybuffer = malloc(BUFFER_SIZE + 1);
	if (!(mybuffer))
		return (0);
	ssize_t readreturn = read(fd, mybuffer, BUFFER_SIZE);
	if (readreturn == -1)
	{
		free(mybuffer);
		return 0;
	}
	if (readreturn == 0)
	{
		free(mybuffer);
		if (savedline)
		{
			returnline = ft_strdup(savedline);
			free(savedline);
			savedline = 0;
			return (returnline);
		}
		return (0);
	}
	mybuffer[readreturn] = '\0';
	
	//printf("savedline is at %p\n", savedline);
	if (!savedline)
	{
		savedline = malloc(5);
		//printf("savedline was just allocated at %p\n", savedline);
		savedline[0] = '\0';
	}
	//printf("savedline is at %p\n", savedline);
	
	postbuffer = ft_strchr(mybuffer, '\n');
	if (postbuffer) //we found newline
	{
		//printf("postbuffer is at %p and mybuffer at %p\n", postbuffer, mybuffer);
		int newcharacters = postbuffer - mybuffer + 1;
		//printf("newcharacters = %i\n", newcharacters);
		returnline = ft_strjoin_len(savedline, mybuffer, newcharacters);
		if (ft_strlen(postbuffer) > 1)
			savedline = ft_strdup(postbuffer + 1);
		else
			savedline = 0;
		return (returnline);
	}
	//did not find newline
	
	if (readreturn < BUFFER_SIZE) //file ended, no /n found
	{
		//if (readreturn > 0)
		//{
		returnline = ft_strjoin_len(savedline, mybuffer, readreturn);
		savedline = 0;
		return (returnline);
		//}
		//else
		//{
		//	free(mybuffer);
		//	free(savedline);
		//	savedline = 0;
		//	return (0);
		//}
	}
	
	savedline = ft_strjoin_len(savedline, mybuffer, ft_strlen(mybuffer)); //and then we have to read again
	return (get_next_line(fd));
}


char	*ft_strchr(const char *s, int c)
{
	int	pos;

	pos = 0;
	while (s[pos])
	{
		if (s[pos] == (char)c)
			return ((char *)(s + pos));
		pos++;
	}
	if (!c)
		return ((char *)(s + pos));
	return (0);
}

char	*ft_strjoin_len(char *s1, char *s2, int len_2)
{
	char	*goal;
	int		len_1;
	int		len_goal;

	//printf("we start \n");
	len_1 = ft_strlen((char *)s1);
	len_goal = len_1 + len_2;
	//printf("we mid \n");
	goal = malloc(len_goal + 1);
	if (!goal)
		return (0);
	//printf("we are about to copy \n");
	ft_memcpy(goal, s1, len_1);
	ft_memcpy(goal + len_1, s2, len_2);
	goal[len_goal] = '\0';
	//printf("s1 is %s at %p\n", s1, s1);
	free(s1);
	//printf("s2 is %s\n", s2);
	free(s2);
	return (goal);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned long int	pos;

	pos = 0;
	if (!dest && !src)
		return (dest);
	while (pos < n)
	{
		*(unsigned char *)(dest + pos) = *(unsigned char *)(src + pos);
		pos++;
	}
	return (dest);
}

size_t	ft_strlen(const char *str)
{
	size_t	count;

	count = 0;
	while (str && str[count])
		count++;
	return (count);
}

char	*ft_strdup(const char *src)
{
	int		len;
	char	*goal;

	len = ft_strlen(src);
	goal = malloc(len + 1);
	if (!goal)
		return (0);
	ft_memcpy(goal, src, len + 1);
	return (goal);
}

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	len_src_return;
	size_t	bytes_to_copy;

	len_src_return = ft_strlen(src);
	if (size > 0)
	{
		if (len_src_return >= size - 1)
			bytes_to_copy = size - 1;
		else
			bytes_to_copy = len_src_return;
		ft_memcpy((void *)dest, (void *)src, bytes_to_copy);
		dest[bytes_to_copy] = '\0';
	}
	return (len_src_return);
}
