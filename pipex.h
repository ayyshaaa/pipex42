/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistierl <aistierl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 16:34:59 by aistierl          #+#    #+#             */
/*   Updated: 2024/10/06 19:22:31 by aistierl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

#include "./libft/libft.h"
#include "./gnl/get_next_line.h"
#include "./ftprintf/ftprintf.h"
#include <unistd.h>
 #include <sys/wait.h> 

void	ft_child_process(char *file_input, char *raw_cmd, char **envp, int *pipe_ends);
void	ft_parent_process(char *file_output, char *raw_cmd, char **envp, int *pipe_ends);
void	ft_exec(char *argv, char **envp);
char	*ft_cmd_path(char *argv, char **envp);
char    **ft_list_paths(char **envp);
char	**ft_free_tab(char **tab);


#endif