/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweerasi <wweerasi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 14:54:57 by wweerasi          #+#    #+#             */
/*   Updated: 2024/11/11 19:38:27 by wweerasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>

typedef struct s_pipex
{
	int	infd;
	int	outfd;
	int	heredoc;
	int	cmd_count;
	pid_t	pid;
	//char	***cmd
} t_pipex

#endif
