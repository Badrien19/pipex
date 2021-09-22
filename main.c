/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badrien <badrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 15:28:46 by badrien           #+#    #+#             */
/*   Updated: 2021/09/22 12:13:04 by badrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h" 

void error(int i)
{
	if (i == 1)
		printf("Error: Can not opening pipe\n");
	if (i == 2)
		printf("Error: Can not create fork\n");
	if (i == 3)
		printf("Error: file error\n");
	exit(i);
	
}

int find_path(char **cmd, char **env)
{
	int i;
	char *tmp;
	char **paths;
	char *path;
	
//printf("cmd = (%s)", cmd[0]);
//printf(" et (%s)\n", cmd[1]);
	i = 0;
	while (ft_strnstr(env[i], "PATH=", 5) == 0)
		i++;
	paths = ft_split(env[i] + 5, ':');
	i = 0;
//printf("PATHs 1  = %s\n", paths[0]);
	while(paths[i])
	{
		//printf("PATHs %d  = %s\n",i , paths[i]);
		if(cmd[0][0] != '/')
		{
			tmp = ft_strjoin(paths[i], "/");
			path = ft_strjoin(tmp, cmd[0]);
			//printf("%s\n", cmd[0]);
			//printf("%s\n", paths[i]);
			free(tmp);
		}
		if(access(path, X_OK) == 0) 
			execve(path, cmd, env);
		i++;
	}
	return (-1);
}

void parent_fork(char **argv, char **env, int *fd)
{
	int file_out;
	char	**cmd;

	file_out = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (file_out == -1)
		error(3);
	//printf("OK\n");
	close(fd[1]); // ?
	dup2(fd[0], STDIN_FILENO);
	dup2(file_out, STDOUT_FILENO);

	cmd = ft_split(argv[3], ' ');
	find_path(cmd, env);
}

void child_fork(char **argv, char **env, int *fd)
{
	int file_in;
	char	**cmd;

	file_in = open(argv[1], O_RDONLY, 0777);
	if (file_in == -1)
		error(3);
	//printf("OK\n");
	close(fd[0]); // ?
	dup2(fd[1], STDOUT_FILENO);
	dup2(file_in, STDIN_FILENO);

	cmd = ft_split(argv[2], ' ');
	find_path(cmd, env);
}

int	main(int argc, char **argv, char **env)

{
	int		fd[2];
	pid_t	pid;

	if (argc != 5)
		printf("Bad arguments\n");
	else
	{
		if (pipe(fd) == -1)
			error(1);
		pid = fork();
		if (pid == -1)
			error(2);
		if (pid == 0) // child
			child_fork(argv, env, fd);
		waitpid(pid, NULL, 0);
		parent_fork(argv, env, fd);
		close(fd[0]); // ?
		close(fd[1]); // ?
	}
	return (1);
}