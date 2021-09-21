/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badrien <badrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 15:28:46 by badrien           #+#    #+#             */
/*   Updated: 2021/09/21 16:26:08 by badrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char **ft_split(const char *str, char charset);
int	ft_strncmp(const char *s1, const char *s2, size_t n);

// TO DO
// MakeFile
// .H
// systeme erreur
//

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/wait.h>

#endif

int find_path(char **arg, char **env)
{
	// parcourir env a la recherche de PATH=
	// separer les differenet PATH par les :
	// ajouer / et le nom de la commande arg[0]
	// execve sur chacune des possibiliter ( execve(tmp, cmd, env); )
}

int child_job(int fd,char **argv, char **env,int pip)
{
	char **arg;
	
	arg = ft_split(argv[2], " ");
	if (arg[0] == NULL)
		return (-1);
	dup2(pip, STDOUT_FILENO); 	 //remplacer/copie le 1 par le 2
	close(pip);
	dup2(fd, STDIN_FILENO);
	
	find_path(arg, env); // execve a besoin du path, les argument, env
}

void pipex(int fd1,int fd2,char **argv, char **env)
{
	int pip[2];
	pid_t id;
	pipe(tab); // to check tab[0] envoie tab [1] prendre
	
	id = fork(); // > 0 parent et 0 le child
	
	if(id == 0) // dans le child
		child_job(fd1, argv, env, pip[1])

}

int	main(int argc, char **argv, char *env[])
{
	int		fd1;
	int		fd2;

	if (argc != 5)
	{
		printf("Error");
		exit(-1);
	}
	fd1 = open(argv[1], O_RDONLY);
	fd2 = open(argv[4], O_CREAT | O_RDWR | O_TRUNC);
	if (fd1 < 0 || fd2 < 0)
		return (-1);
	pipex(fd1, fd2, argv, env);
	return (1);
}