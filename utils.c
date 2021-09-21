/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badrien <badrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 16:10:06 by badrien           #+#    #+#             */
/*   Updated: 2021/09/21 16:23:02 by badrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
