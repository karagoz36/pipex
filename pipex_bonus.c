/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkaragoz <tkaragoz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 11:03:28 by tkaragoz          #+#    #+#             */
/*   Updated: 2024/06/28 16:17:03 by tkaragoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	child_prcs(char *cmd, char **env)
{
	int		fd[2];
	pid_t	pid;

	if (pipe(fd) == -1)
		ft_error("Error in pipe process");
	pid = fork();
	if (pid == -1)
		ft_error("Error in fork process");
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		execute(cmd, env);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
	}
}

int	out_prcs(int argc, char **argv)
{
	int	outfile;

	if (ft_strncmp(argv[1], "here_doc", 8) == 0)
		outfile = open(argv[argc -1], O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		outfile = open(argv[argc -1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (outfile == -1)
		ft_error("Error in opening outfile");
	return (outfile);
}

int	in_prcs(char **argv)
{
	int	infile;

	if (ft_strncmp(argv[1], "here_doc", 8) == 0)
	{
		here_doc(argv[2]);
		return (3);
	}
	else
	{
		infile = open(argv[1], O_RDONLY);
		if (infile == -1)
			ft_error("Error in opening input file");
		dup2 (infile, STDIN_FILENO);
		close(infile);
		return (2);
	}
}

int	main(int argc, char **argv, char **env)
{
	pid_t	pid;
	int		outfile;
	int		i;
	int		j;

	if (argc < 5 || (ft_strncmp(argv[1], "here_doc", 8) == 0 && argc < 6))
		ft_error("Not valid arguments");
	i = in_prcs(argv);
	j = i;
	while (i < argc - 2)
		child_prcs(argv[i++], env);
	outfile = out_prcs(argc, argv);
	pid = fork();
	if (pid == 0)
	{
		dup2(outfile, STDOUT_FILENO);
		close(outfile);
		execute(argv[argc - 2], env);
	}
	i = 0;
	while (++i < argc - 2)
		wait(NULL);
	return (0);
}
