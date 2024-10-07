/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistierl <aistierl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 13:06:45 by aistierl          #+#    #+#             */
/*   Updated: 2024/10/07 15:14:19 by aistierl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./pipex.h"

void	ft_child_process(int file_input, char *raw_cmd, char **envp,
		int file_output)
{
	dup2(file_input, STDIN_FILENO);
	dup2(file_output, STDOUT_FILENO);
	ft_exec(raw_cmd, envp);
}

int	main(int argc, char **argv, char **envp)
{
	int		pipe_ends[2];
	pid_t	child;
	int		nb_cmd;
	int		i;
	int		file_input;
	int		file_output;

	if (argc < 5)
		perror("Number of arguments is invalid.");
	nb_cmd = argc - 2;
	file_input = open(argv[1], O_RDONLY);
	file_output = open(argv[argc - 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (file_input < 0 || file_output < 0)
		perror("Cannot open infile/outfile.");
    i = 2;
	while (i < nb_cmd)
	{
		if (i != nb_cmd - 1)
		{
			pipe(pipe_ends);
			if (pipe(pipe_ends) == -1)
				perror("Pipe creation failed");
		}
		child = fork();
		if (child < 0)
			perror("Child fork failed.");
		else if (child == 0 && i != nb_cmd - 1)
        {
            close(pipe_ends[0]);
			ft_child_process(file_input, argv[i], envp, pipe_ends[1]);
        }
        else if (child == 0 && i == nb_cmd - 1)
			ft_child_process(file_input, argv[i], envp, file_output);
        else
        {
		    waitpid(child, NULL, 0);
		    file_input = pipe_ends[0];
		    close(pipe_ends[1]);
        }
		i++;
	}
	return (0);
}
