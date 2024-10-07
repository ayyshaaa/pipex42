/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistierl <aistierl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 18:18:25 by aistierl          #+#    #+#             */
/*   Updated: 2024/10/07 12:06:37 by aistierl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**ft_free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		free(tab[i++]);
	free(tab);
	return (NULL);
}

char	**ft_list_paths(char **envp)
{
	int		i;
	char	*all_paths;
	char	**each_path;

	i = 0;
	while (strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	all_paths = ft_substr(envp[i], 5, ft_strlen(envp[i]) - 5);
	if (all_paths == NULL)
		return (NULL);
	each_path = ft_split(all_paths, ':');
	free(all_paths);
	i = 0;
	while (each_path[i])
	{
		each_path[i] = ft_concat_free(each_path[i], "/");
		i++;
	}
	return (each_path);
}

char	*ft_cmd_path(char *argv, char **envp)
{
	int		i;
	char	**each_path;
	char	*temp;

	if (argv[0] == '/' || argv[0] == '.' || argv[0] == '~')
	{
		if (access(argv, F_OK | X_OK) != -1)
			return (argv);
		return (0);
	}
	each_path = ft_list_paths(envp);
	i = 0;
	while (each_path[i])
	{
		temp = ft_strjoin(each_path[i], argv);
		if (access(temp, F_OK | X_OK) != -1)
			return (temp);
		i++;
	}
	free(temp);
	return (0);
}

void	ft_exec(char *argv, char **envp)
{
	char	**full_cmd;
	char	*cmd_path;
	int		exec_return_value;

	full_cmd = ft_split(argv, ' ');
	cmd_path = ft_cmd_path(full_cmd[0], envp);
	if (cmd_path == 0)
	{
		ft_free_tab(full_cmd);
		perror("Command or command path is invalid.");
	}
	exec_return_value = execve(cmd_path, full_cmd, envp);
	if (exec_return_value == -1)
	{
		free(cmd_path);
		ft_free_tab(full_cmd);
		perror("execve is not functionning");
	}
}
