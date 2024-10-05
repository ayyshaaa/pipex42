/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistierl <aistierl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 18:18:25 by aistierl          #+#    #+#             */
/*   Updated: 2024/10/05 18:32:48 by aistierl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char    **ft_list_paths(char **envp)
{
    int     i;
    char    *all_paths;
    char    **each_path;
    
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
		ft_concat_free(each_path[i++], "/");
}

void	ft_parse_cmd_path(int argc, char **argv, char **envp,
		t_pipex_data *data)
{
	int		i;
	int		j;
	int		k;
	char	*PATH_from_env;
	char	**each_path;
	char	**temp;
	char	*temp2;
    
    each_path = ft_list_paths(envp);
	i = 2;
	j = 0;
	k = 0;
	while (i < argc - 1)
	{
		if (argv[i][0] == '/' || argv[i][0] == '.' || argv[i][0] == '~')
		{
			temp = ft_split(argv[2], ' ');
            if (access() != -1)
			    data->cmd_path[j++] = temp[0];
			ft_free_tab(temp);
		}
		else
        {
            while (each_path[k])
            {
			    temp2 = ft_strjoin(each_path[k], argv[i]);
                if (access() != -1)
                    data->cmd_path[j++] = temp2[0];
                k++;
		        free(temp2);
            }
        }
        i++;
	}
	data->cmd_path[j] = NULL;
}
