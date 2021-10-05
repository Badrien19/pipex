/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badrien <badrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 16:31:14 by badrien           #+#    #+#             */
/*   Updated: 2021/10/05 12:16:01 by badrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h" 

/*
** TO DO
** NORM
** FREE split
*/

char	*find_path(char **cmd, char **env)
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
			return (free_double_array_ret(paths, path));
		free(path);
		i++;
	}
	return (NULL);
}

int	execute_cmd1(char **argv, char **env, int fd[2])
{
	int		file_in;
	char	**cmd;
	char	*path;
	pid_t	pid;

	file_in = open(argv[1], O_RDONLY, 0777);
	if (file_in == -1)
		return (3);
	cmd = ft_split(argv[2], ' ');
	if (cmd[0] == NULL)
		return (5);
	path = find_path(cmd, env);
	if (path == NULL)
		return (4);
	pid = fork();
	if (pid == -1)
		return (1);
	if (pid == 0)
	{
		close_dup(fd, file_in, 1);
		execve(path, cmd, env);
	}
	free(path);
	return (0);
}

int	execute_cmd2(char **argv, char **env, int fd[2])
{
	int		file_out;
	char	**cmd;
	char	*path;
	pid_t	pid;

	file_out = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (file_out == -1)
		return (3);
	cmd = ft_split(argv[3], ' ');
	if (cmd[0] == NULL)
		return (5);
	path = find_path(cmd, env);
	if (path == NULL)
		return (4);
	pid = fork();
	if (pid == -1)
		return (1);
	if (pid == 0)
	{
		close_dup(fd, file_out, 2);
		execve(path, cmd, env);
	}
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	int		fd[2];
	int		error_id1;
	int		error_id2;

	if (argc != 5)
		printf("Error: Bad arguments\n");
	else
	{
		error_id1 = execute_cmd1(argv, env, fd);
		error_id2 = execute_cmd2(argv, env, fd);
		if (error_id1 != 0)
			error(error_id1);
		if (error_id2 != 0)
			error(error_id2);
	}
	return (0);
}
