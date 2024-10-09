/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aisha <aisha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 13:06:45 by aistierl          #+#    #+#             */
/*   Updated: 2024/10/09 22:42:09 by aisha            ###   ########.fr       */
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

void	ft_child_process_bonus(int file_input, char *raw_cmd, char **envp, int file_output)
{
	dup2(file_input, STDIN_FILENO);
	dup2(file_output, STDOUT_FILENO);
	close(file_input);
	close(file_output);
	ft_exec(raw_cmd, envp);
}

int	main(int argc, char **argv, char **envp)
{
	int		pipe_ends[2];
	pid_t	child;
	int	i;
	int j;
	int	file_input;
	int	file_output;
	int		*child_id_list;

	if (argc < 5)
		return (perror("Number of arguments is invalid."), 1);
	file_input = open(argv[1], O_RDONLY);
	file_output = open(argv[argc - 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (file_input < 0 || file_output < 0)
		perror("Cannot open infile/outfile.");
	i = 2;
	j = 0;
	child_id_list = malloc(sizeof(int) * (argc - 3));
	if (!child_id_list)
		return (perror("Failed to allocate memory for child IDs."), 1);
	while (i < argc - 2)
	{
		if (pipe(pipe_ends) == -1)
			return (perror("Pipe creation failed."), 1);
		child = fork();
		if (child < 0)
			ft_tidyup("Child fork failed.", pipe_ends);
		else if (child == 0)
		{
			close(pipe_ends[0]);
			ft_child_process_bonus(file_input, argv[i], envp, pipe_ends[1]);		
		}
		close(pipe_ends[1]);
		file_input = pipe_ends[0];			
		child_id_list[j++] = child;
		i++;
	}
	ft_child_process_bonus(file_input, argv[i], envp, file_output);
	i = 0;
	while (child_id_list && child_id_list[i])
		waitpid(child_id_list[i++], NULL, 0);
	free(child_id_list);
	ft_close_pipes(pipe_ends);
	return (0);
}
