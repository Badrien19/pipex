/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badrien <badrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 15:28:46 by badrien           #+#    #+#             */
/*   Updated: 2021/09/23 16:25:46 by badrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** No need to free, when execve is ending the entire heap is free,
** including malloc
*/


/*

PLAN:
-	check nb of input
-	on fork
-	open argv[1]
-	on dup
-	on extrait la commande
- 	on trouve le PATH
-	execve
-	wait pip
-	on fork
- 	open argv[4]
-	on dup
-	on extrait la commande
-	on trouve le PATH
-	execve
-	affiche les erreurs
*/
#include "pipex.h" 

int	find_path(char **cmd, char **env)
{
	int		i;
	char	*tmp;
	char	**paths;
	char	*path;

	paths = NULL;
	i = 0;
	while (ft_strnstr(env[i], "PATH=", 5) == 0 && env[i] != NULL)
		i++;
	if (env[i] != NULL)
		paths = ft_split(env[i] + 5, ':');
	i = 0;
	while (paths[i])
	{
		if (cmd[0][0] != '/')
		{
			tmp = ft_strjoin(paths[i], "/");
			path = ft_strjoin(tmp, cmd[0]);
			free(tmp);
		}
		if (access(path, X_OK) == 0)
			execve(path, cmd, env); 
		i++;
	}
	return (-1);
}

int	parent_fork(char **argv, char **env, int *fd)
{
	int		file_out;
	char	**cmd;

	file_out = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (file_out == -1)
		error(3);
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	dup2(file_out, STDOUT_FILENO);
	cmd = ft_split(argv[3], ' ');
	close(fd[0]);
	if (find_path(cmd, env) == -1)
		return (-1);
	return (0);
}

int	child_fork(char **argv, char **env, int *fd)
{
	int		file_in;
	char	**cmd;

	file_in = open(argv[1], O_RDONLY, 0777);
	if (file_in == -1)
		error(3);
	close(fd[0]);
	dup2(fd[1], STDOUT_FILENO);
	dup2(file_in, STDIN_FILENO);
	cmd = ft_split(argv[2], ' ');
	close(fd[1]);
	if (find_path(cmd, env) == -1)
		return (-1);
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	int		fd[2];
	int		flag;
	pid_t	pid;

	flag = 0;
	if (argc != 5)
		printf("Bad arguments\n");
	else
	{
		if (pipe(fd) == -1)
			error(1);
		pid = fork();
		if (pid == -1)
			error(2);
		if (pid == 0)
			if (child_fork(argv, env, fd) == -1)
						{
			close(fd[0]);
			close(fd[1]);
			error(4);
		}
		waitpid(pid, NULL, 0);
		if (parent_fork(argv, env, fd) == -1)
			flag += 1;
	}
	if(flag > 0)
		{
			close(fd[0]);
			close(fd[1]);
			error(4);
		}
	return (0);
}

// cat < infile | echo ok > outfile
// ./pipex infile cat  "echo ok" outfile

//fork dans l'enfant les dup(s) puis execve (attention different dup)