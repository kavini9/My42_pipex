/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweerasi <wweerasi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 21:16:34 by wweerasi          #+#    #+#             */
/*   Updated: 2024/12/04 02:44:50 by wweerasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "../lib/libft/libft.h"

# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <stdlib.h>
# include <string.h>
# include <errno.h>
# include <stdio.h>

typedef struct s_pipex
{
	int	infd;
	int	outfd;
	int	heredoc;
	int	cmd_count;
	int	*pfds;
	int	status;
	int	ac;
	char	**av;
	char	**envp;
	char	**arr_path;
	char	**cmd_arr;
	char	*path;
} t_pipex;

void	ft_pipex(t_pipex *pipex);
void	redirect_io(int i, t_pipex *pipex);
void	open_file(int i, int *fd, char *file, t_pipex *pipex);
void	dup_io(t_pipex *pipex, int rd_fd, int wr_fd);
void	wait_child(int i, pid_t pid, t_pipex *pipex);

void	pipex_init(t_pipex *pipex, int ac, char **av, char **envp);
void	init_pipeline(t_pipex *pipex);
void	get_path_array(char **envp, t_pipex *pipex);

void	execute_cmd(int cmd_no, t_pipex *pipex);
char	*get_cmd_path(char *cmd, char **arr_path);

void	pipex_sys_error(char *sys_call, t_pipex *pipex);
void	pipex_error(char *err_note, t_pipex *pipex);
void	pipex_clean(t_pipex *pipex);
void	close_pfds(t_pipex *pipex);
void	free_arr(char ***arr);
#endif
