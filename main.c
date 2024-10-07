/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistierl <aistierl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 16:33:52 by aistierl          #+#    #+#             */
/*   Updated: 2024/10/07 12:28:05 by aistierl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./pipex.h"

void	ft_child_process(char *file_input, char *raw_cmd, char **envp,
		int *pipe_ends)
{
	int	infile;

	infile = open(file_input, O_RDONLY);
	if (infile < 0)
		perror ("Cannot open infile");
	dup2(infile, STDIN_FILENO);
	dup2(pipe_ends[1], STDOUT_FILENO);
	close(pipe_ends[0]);
	ft_exec(raw_cmd, envp);
	close(infile);
}

void	ft_child_two_process(char *file_output, char *raw_cmd, char **envp,
		int *pipe_ends)
{
	int	outfile;

	outfile = open(file_output, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (outfile < 0)
		perror ("Cannot open outfile"); ;
	dup2(pipe_ends[0], STDIN_FILENO);
	dup2(outfile, STDOUT_FILENO);
	close(pipe_ends[1]);
	ft_exec(raw_cmd, envp);
	close(outfile);
}

int	main(int argc, char **argv, char **envp)
{
	int		pipe_ends[2];
	pid_t	child;
	pid_t	second_child;

	if (argc != 5)
		perror("Number of arguments is invalid.");
	else
	{
		pipe(pipe_ends);
		if (pipe(pipe_ends) == -1)
			perror("Pipe creation failed");
		child = fork();
		if (child < 0)
			perror ("Child fork failed.");
		else if (child == 0)
			ft_child_process(argv[1], argv[2], envp, pipe_ends);
		second_child = fork();
		if (second_child < 0)
			perror ("Parent fork failed.");
		else if (second_child == 0)
			ft_child_two_process(argv[4], argv[3], envp, pipe_ends);
		close(pipe_ends[0]);
		close(pipe_ends[1]);
		waitpid(child, NULL, 0);
		waitpid(second_child, NULL, 0);
	}
	return (0);
}
