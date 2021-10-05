/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badrien <badrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 17:15:21 by badrien           #+#    #+#             */
/*   Updated: 2021/10/05 10:46:13 by badrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <stdlib.h>

/* main.c */

int		main(int argc, char **argv, char **env);

/* utils.c */

void	error(int i);
char	*ft_strnstr(const char *haystack, const char *needle, int len);
size_t	ft_strlen(const char *chaine);
void	*ft_memcpy(void *dest, const void *src, size_t n);
char	*ft_strjoin(char const *s1, char const *s2);

/* ft_split.c */

char	**ft_split(const char *str, char charset);

#endif