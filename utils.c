/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badrien <badrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 16:10:06 by badrien           #+#    #+#             */
/*   Updated: 2021/09/22 12:09:51 by badrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h" 

char	*ft_strnstr(const char *haystack, const char *needle, int len)
{
	int i;
	int x;
	int taille;

	i = 0;
	x = 0;
	taille = 0;
	while (needle[taille] != '\0')
		taille++;
	if (taille == 0)
		return ((char *)haystack);
	while (haystack[i] != '\0' && i < len)
	{
		while (haystack[i + x] == needle[x] &&
			i + x < len && haystack[i + x] != '\0')
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
	size_t i;

	i = 0;
	while (chaine[i] != '\0')
		i++;
	return (i);
}

static char		**free_all(char **tab)
{
	int i;

	i = 0;
	while (tab[i] != NULL)
		free(tab[i++]);
	free(tab);
	return (0);
}

static int		motcounter(const char *str, char charset)
{
	int i;
	int mot;
	int motcount;

	motcount = 0;
	mot = 1;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == charset)
		{
			if (mot++ == 0)
				motcount++;
		}
		else
			mot = 0;
		i++;
	}
	if (mot == 0)
		motcount++;
	return (motcount);
}

static char		*fill(const char *str, char charset, int *i)
{
	char	*tmp;
	int		y;

	y = 0;
	while (str[*i] == charset && str[*i] != '\0')
		(*i)++;
	while ((str[(*i) + y] != charset) && str[(*i) + y] != '\0')
		y++;
	tmp = malloc(sizeof(char) * (y + 1));
	if (tmp == 0)
		return (NULL);
	y = 0;
	while ((str[*i] != charset) && str[*i] != '\0')
		tmp[y++] = str[(*i)++];
	tmp[y] = '\0';
	return (tmp);
}

char			**ft_split(const char *str, char charset)
{
	int		wordcount;
	char	**tab;
	int		x;
	int		i;

	x = 0;
	i = 0;
	if (str == NULL)
		return (NULL);
	wordcount = motcounter(str, charset);
	tab = malloc(sizeof(char *) * wordcount + 1);
	if (tab == 0)
		return (0);
	while (wordcount > 0)
	{
		tab[x++] = fill(str, charset, &i);
		if (tab[x - 1] == NULL)
			return (free_all(tab));
		wordcount--;
	}
	tab[x] = 0;
	return (tab);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t i;

	i = 0;
	if (n == 0)
		return (0);
	while (s1[i] != '\0' && s2[i] != '\0' && i < n)
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	if (i == n)
		i--;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned int i;

	i = 0;
	if (dest == NULL)
		return (NULL);
	while (i < n)
	{
		((unsigned char*)dest)[i] = ((unsigned char*)src)[i];
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
	if (!(ret = malloc(sizeof(char) * (i + ft_strlen((char*)s2) + 1))))
		return (0);
	ft_memcpy(ret, s1, i);
	ft_memcpy(&ret[i], s2, ft_strlen((char*)s2) + 1);
	return (ret);
}