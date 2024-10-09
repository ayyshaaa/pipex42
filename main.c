/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistierl <aistierl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 16:33:52 by aistierl          #+#    #+#             */
/*   Updated: 2024/10/09 19:13:11 by aistierl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./pipex.h"

void	ft_close_pipes(int *pipe)
{
	close(pipe[0]);
	close(pipe[1]);
}

void	ft_tidyup(char *error_message, int *pipe_ends)
{
	ft_close_pipes(pipe_ends);
	perror(error_message);
	exit(1);
}

void	ft_child_process(char *file_input, char *raw_cmd, char **envp,
		int *pipe_ends)
{
	int	infile;

	infile = open(file_input, O_RDONLY);
	if (infile < 0)
		ft_tidyup("Cannot open infile.", pipe_ends);
	close(pipe_ends[0]);
	dup2(infile, STDIN_FILENO);
	dup2(pipe_ends[1], STDOUT_FILENO);
	close(infile);
	close(pipe_ends[1]);
	ft_exec(raw_cmd, envp);
}

void	ft_child_two_process(char *file_output, char *raw_cmd, char **envp,
		int *pipe_ends)
{
	int	outfile;

	outfile = open(file_output, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (outfile < 0)
		ft_tidyup("Cannot open outfile.", pipe_ends);
	close(pipe_ends[1]);
	dup2(pipe_ends[0], STDIN_FILENO);
	dup2(outfile, STDOUT_FILENO);
	close(outfile);
	close(pipe_ends[0]);
	ft_exec(raw_cmd, envp);
}

int	main(int argc, char **argv, char **envp)
{
	int		pipe_ends[2];
	pid_t	child;
	pid_t	second_child;
	int		status;

	status = 0;
	if (argc != 5)
		return (perror("Number of arguments is invalid."), 1);
	if (pipe(pipe_ends) == -1)
		return (perror("Pipe creation failed."), 1);
	child = fork();
	if (child < 0)
		ft_tidyup("Child fork failed.", pipe_ends);
	else if (child == 0)
		ft_child_process(argv[1], argv[2], envp, pipe_ends);
	second_child = fork();
	if (second_child < 0)
		ft_tidyup("Second child fork failed.", pipe_ends);
	else if (second_child == 0)
		ft_child_two_process(argv[4], argv[3], envp, pipe_ends);
	ft_close_pipes(pipe_ends);
	waitpid(child, &status, 0);
	waitpid(second_child, &status, 0);
	return (status);
}
