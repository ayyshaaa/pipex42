/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistierl <aistierl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 16:34:59 by aistierl          #+#    #+#             */
/*   Updated: 2024/10/05 17:08:17 by aistierl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

#include "./libft/libft.h"
#include "./gnl/get_next_line.h"
#include "./ftprintf/ftprintf.h"
#include <unistd.h>

typedef struct p_data
{
    char    **cmd_path;
    char    ***cmd;
}   t_pipex_data;


#endif