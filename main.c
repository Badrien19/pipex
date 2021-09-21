/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badrien <badrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 15:28:46 by badrien           #+#    #+#             */
/*   Updated: 2021/09/21 17:16:48 by badrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h" 

// TO DO
// MakeFile
// .H
// systeme erreur
// LEAK

int find_path(char **arg, char **env)
{
	int i;
	char *tmp;
	char **paths;

	i = 0;
	while(env[i])
	{
		if(ft_strncmp(env[i], "PATH=", 5) == 0)
			paths[0] = env[i][5];		
		i++;
	}
	// parcourir env a la recherche de PATH=
	paths = ft_split(paths[0], ":");
	// separer les differenet PATH par les :
	i = 0;
	while(paths[i])
	{
		if(arg[0][0] != '/')
		{
			tmp = ft_strjoin(paths[i], "/");
			tmp = ft_strjoin(tmp, arg[0]);
			// ajouer / et le nom de la commande arg[0]
		}
		if(access(tmp, X_OK) == 0) // access sur chacune des possibiliter
			execve(tmp, arg, env); //lancer avec execve  ( execve(tmp, cmd, env); )
		i++;
		free(tmp);
	}
	return (-1);
}

int parent_job(int fd,char **argv, char **env,int pip)
{
	char **arg;
	
	arg = ft_split(argv[3], " ");
	if (arg[0] == NULL)
		return (-1);
	dup2(pip, STDIN_FILENO); 	 //remplacer/copie le 1 par le 2
	close(pip);
	dup2(fd, STDOUT_FILENO);
	
	find_path(arg, env); // execve a besoin du path, les argument, env
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
	pipe(pip); // to check tab[0] envoie tab [1] prendre
	
	id = fork(); // > 0 parent et 0 le child
	
	if(id == 0) // dans le child
	{
		close(pip[0]);
		child_job(fd1, argv, env, pip[1]);
	}
	else
	{
		close(pip[1]);
		waitpid(id, NULL, 0);
		parent_job(fd2, argv, env, pip[0]);
	}
	
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