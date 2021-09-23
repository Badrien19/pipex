/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badrien <badrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 16:31:14 by badrien           #+#    #+#             */
/*   Updated: 2021/09/23 17:28:19 by badrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h" 

char *find_path(char **cmd, char **env)
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
			return (path);
		i++;
	}
	return (NULL);
}

int execute_cmd1(char **argv, char **env)
{
	int		file_in;
	char **cmd;
	char *path;
	pid_t	pid;

	cmd = ft_split(argv[2]); // ETAPE 1
	if (cmd[0] == NULL)
		//ERREUR
	path = find_path(cmd, env); // ETAPE 2
	if (path == NULL)
		//ERREUR
	fork(pid);
	if (pid == -1)
		//ERREUR
	if (pid == 0)
	{
		file_in = open(argv[1], O_RDONLY, 0777);
		if (file_in == -1)
			// ERROR
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		dup2(file_in, STDIN_FILENO);
		close(fd[1]);
		execve(path, cmd, env);
	}
	return (0);
}

int execute_cmd1(char **argv, char **env) // TO DO ERREUR
{
	int		file_out;
	char **cmd;
	char *path;
	pid_t	pid;

	cmd = ft_split(argv[3]); // ETAPE 1
	path = find_path(cmd, env); // ETAPE 2

	fork(pid);
	if (pid == 0)
	{
		file_out = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		dup2(file_out, STDOUT_FILENO);
		close(fd[1]);
		execve(path, cmd, env);
	}
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	int		file_in;
	int		file_out;
	int		fd[2];
	char *path;
	char **cmd;
	pid_t	pid;

	if (argc != 5)
		printf("Bad arguments\n");
	else
	{
		execute_cmd_1(argv, env);
		execute_cmd_2(argv, env);
		
		//TO DO clean UP
	}
	
	
}