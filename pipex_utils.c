/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badrien <badrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 12:02:38 by badrien           #+#    #+#             */
/*   Updated: 2021/10/05 12:19:35 by badrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h" 

/*
** i = 1 -> cmd 1
** i = 2 -> cmd 2
*/

char	*free_double_array_ret(char **tab, char *ret)
{
	int	i;

	i = 0;
	while (tab[i] != NULL)
		free(tab[i++]);
	free(tab);
	return (ret);
}

void	close_dup(int fd[2], int file, int i)
{
	if (i == 1)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		dup2(file, STDIN_FILENO);
		close(fd[1]);
	}
	if (i == 2)
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		dup2(file, STDOUT_FILENO);
		close(fd[0]);
	}
}

void	error(int i)
{
	if (i == 1)
		printf("Error: Can not opening pipe\n");
	if (i == 2)
		printf("Error: Can not create fork\n");
	if (i == 3)
		printf("Error: File error\n");
	if (i == 4)
		printf("Error: Command not found\n");
	if (i == 5)
		printf("Error: Malloc fail\n");
}
