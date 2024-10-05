/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistierl <aistierl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 16:33:52 by aistierl          #+#    #+#             */
/*   Updated: 2024/10/05 15:30:26 by aistierl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./pipex.h"

// void	child_process(int	f1, char **cmd)
// {}

// void	pipex(int f1, int f2, char *args, char **envp)
// {
// 	int		end[2];
// 	pid_t	parent;
	
// 	char	*path_from_env;
// 	char	**mypaths;
// 	char	**mycmdargs;
// 	int		i;

// 	pipe(end);
// 	parent = fork();
// 	if (parent < 0)
// 		return (perror("Fork: "));
// 	if (parent == 0)
// 		ft_child_process(f1, cmd1);
// 	else
// 		ft_parent_process(f2, cmd2);	
// }

char	**ft_free_tab(char **tab)
{
	int		i;

	i = 0;
	while (tab[i])
		free(tab[i++]);
	free(tab);
	return (NULL);
}

void	ft_pipex(int f1, int f2, char **argv, char **envp)
{
	
	char	*PATH_from_env;
	char	**each_path;
	char	*str_test;
	char	**full_cmd_with_slash;
	char 	**full_cmd_with_path;
	char	*cmd_with_path_noflag;
	char	**full_cmd_without_path;
	int		i;

	full_cmd_with_path = NULL;
	if (argv[2][0] == '/' || argv[2][0] == '.' || argv[2][0] == '~')
	{
		full_cmd_with_path = ft_split(argv[2], ' ');
		full_cmd_without_path = ft_split(ft_strrchr(argv[2], '/'), ' ');
		if (access(full_cmd_with_path[0], F_OK) == 0 && access(full_cmd_with_path[0], X_OK) == 0)
		{
			ft_printf("1. Yay ! Found %s in : %s\n", full_cmd_without_path[0], full_cmd_with_path[0]);
			execve(full_cmd_with_path[0], full_cmd_without_path, envp);
		}
		else
		{
			ft_printf("Nowhere to be found.\n");
			return (0);
		}
	}
	else
	{
		i = 0;
		while (strncmp(envp[i], "PATH=", 5) != 0)
		i++;
		PATH_from_env = ft_substr(envp[i], 5, ft_strlen(envp[i]) - 5);
		each_path = ft_split(&PATH_from_env[i], ':');
		free(PATH_from_env);
		
		full_cmd_without_path = ft_split(argv[2], ' ');
		full_cmd_with_slash = ft_split(ft_strjoin("/", argv[2]), ' ');
		i = 0;
		while (each_path[i])
		{
			cmd_with_path_noflag = ft_strjoin(each_path[i], full_cmd_with_slash[0]);
			if (cmd_with_path_noflag == NULL)
				return (0);
			if (access(cmd_with_path_noflag, F_OK | X_OK) == 0)
			{
				ft_printf("2. Yay ! Found %s in : %s\n", full_cmd_without_path[0], cmd_with_path_noflag);
				execve(cmd_with_path_noflag, full_cmd_without_path, envp);
			}
			free(cmd_with_path_noflag);
			i++;
		}
		ft_free_tab(full_cmd_with_slash);
		ft_printf("nowhere to be found.\n");
	}

	// x2 for argv[3]
}

int	main(int argc, char **argv, char **envp)
{
	int		f1;
	int		f2;
	(void) argc;
	
	f1 = open(argv[1], O_RDONLY);
	f2 = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (f1 < 0 || f2 < 0)
		return(-1);
	ft_pipex(f1, f2, argv, envp);
	return (0);
}