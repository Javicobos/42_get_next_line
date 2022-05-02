/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcobos-d <jcobos-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 15:48:26 by jcobos-d          #+#    #+#             */
/*   Updated: 2022/05/02 21:40:59 by jcobos-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
