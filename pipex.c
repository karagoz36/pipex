/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkaragoz <tkaragoz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 14:28:12 by tkaragoz          #+#    #+#             */
/*   Updated: 2024/06/28 10:34:07 by tkaragoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	ft_child(char **argv, int *fd_p, char **env)
{
	int		fd;

	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		close(fd_p[0]);
		close(fd_p[1]);
		ft_error("Error in opening");
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	close(fd_p[0]);
	dup2(fd_p[1], STDOUT_FILENO);
	close(fd_p[1]);
	execute(argv[2], env);
}

static void	ft_child2(char **argv, int *fd_p, char **env)
{
	int	fd;

	fd = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		close(fd_p[0]);
		close(fd_p[1]);
		ft_error("Error in writing");
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	close(fd_p[1]);
	dup2(fd_p[0], STDIN_FILENO);
	close(fd_p[0]);
	execute(argv[3], env);
}

int	main(int argc, char **argv, char **env)
{
	int		fd_p[2];
	pid_t	pid1;
	pid_t	pid2;
	int		status;

	if (argc != 5)
		ft_error("Not valid arguments");
	if (pipe(fd_p) == -1)
		ft_error("Error in pipe");
	pid1 = fork();
	if (pid1 == -1)
		ft_error("Error in fork process 1");
	if (!pid1)
		ft_child(argv, fd_p, env);
	pid2 = fork();
	if (pid2 == -1)
		ft_error("Error in fork process 2");
	if (!pid2)
		ft_child2(argv, fd_p, env);
	close(fd_p[0]);
	close(fd_p[1]);
	status = 0;
	waitpid(pid1, &status, 0);
	waitpid(pid2, &status, 0);
	return (0);
}
