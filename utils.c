/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkaragoz <tkaragoz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 19:30:41 by tkaragoz          #+#    #+#             */
/*   Updated: 2024/06/28 14:36:06 by tkaragoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*get_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH", 4) == 0)
			return (env[i] + 5);
		i++;
	}
	return (NULL);
}

static char	*find_path(char *cmd, char **env)
{
	int		i;
	char	**paths;
	char	*path1;
	char	*path2;

	if (get_env(env) == NULL)
		return (NULL);
	paths = ft_split(get_env(env), ':');
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		path1 = ft_strjoin(paths[i], "/");
		path2 = ft_strjoin(path1, cmd);
		free(path1);
		if (access(path2, F_OK) == 0)
			return (ft_free(paths), path2);
		free(path2);
		i++;
	}
	ft_free(paths);
	return (NULL);
}

void	if_abs_path(char **cmd, char **env)
{
	if (execve(cmd[0], cmd, env) == -1)
	{
		ft_free(cmd);
		ft_error("Command not found/Execve not functioning");
	}
}

void	execute(char *cmd_str, char **env)
{
	char	**cmd;
	char	*path;

	if (!cmd_str || !*cmd_str)
		ft_error("Empty command");
	cmd = ft_split(cmd_str, ' ');
	if (access(cmd[0], F_OK) == 0)
		if_abs_path(cmd, env);
	else
	{
		path = find_path(cmd[0], env);
		if (!path)
		{
			free(path);
			ft_free(cmd);
			ft_error("No accessible command path.");
		}
	}
	if (execve(path, cmd, env) == -1)
	{
		free(path);
		ft_free(cmd);
		ft_error("Execve not functioning");
	}
}
