/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aisha <aisha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 16:34:59 by aistierl          #+#    #+#             */
/*   Updated: 2024/10/09 21:54:15 by aisha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "./ftprintf/ftprintf.h"
# include "./gnl/get_next_line.h"
# include "./libft/libft.h"
# include <sys/wait.h>
# include <unistd.h>

void	ft_child_process(char *file_input, char *raw_cmd, char **envp,
			int *pipe_ends);
void	ft_child_two_process(char *file_output, char *raw_cmd, char **envp,
			int *pipe_ends);
void	ft_exec(char *argv, char **envp);
char	*ft_cmd_path(char *argv, char **envp);
char	**ft_list_paths(char **envp);
char	**ft_free_tab(char **tab);
void	ft_close_pipes(int *pipe);
void	ft_tidyup(char *error_message, int *pipe_ends);
void	ft_child_process_bonus(int file_input, char *raw_cmd, char **envp, int file_output);

#endif