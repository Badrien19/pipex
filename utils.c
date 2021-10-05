/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badrien <badrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 16:10:06 by badrien           #+#    #+#             */
/*   Updated: 2021/10/05 12:02:58 by badrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h" 

char	*ft_strnstr(const char *haystack, const char *needle, int len)
{
	int	i;
	int	x;
	int	taille;

	i = 0;
	x = 0;
	taille = 0;
	while (needle[taille] != '\0')
		taille++;
	if (taille == 0)
		return ((char *)haystack);
	while (haystack[i] != '\0' && i < len)
	{
		while (haystack[i + x] == needle[x] && i
			+ x < len && haystack[i + x] != '\0')
			x++;
		if (x == taille)
			return ((char *)&haystack[i]);
		x = 0;
		i++;
	}
	return (0);
}

size_t	ft_strlen(const char *chaine)
{
	size_t	i;

	i = 0;
	while (chaine[i] != '\0')
		i++;
	return (i);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned int	i;

	i = 0;
	if (dest == NULL)
		return (NULL);
	while (i < n)
	{
		((unsigned char *) dest)[i] = ((unsigned char *) src)[i];
		i++;
	}
	return (dest);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	unsigned int	i;
	char			*ret;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	i = ft_strlen((char *)s1);
	ret = malloc(sizeof(char) * (i + ft_strlen((char *) s2) + 1));
	if (ret == NULL)
		return (0);
	ft_memcpy(ret, s1, i);
	ft_memcpy(&ret[i], s2, ft_strlen((char *) s2) + 1);
	return (ret);
}
