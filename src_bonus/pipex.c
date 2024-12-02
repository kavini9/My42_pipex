/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweerasi <wweerasi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 14:51:32 by wweerasi          #+#    #+#             */
/*   Updated: 2024/12/03 01:02:30 by wweerasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

void	dup_io(t_pipex *pipex, int rd_fd, int wr_fd)
{
	if (dup2(rd_fd, STDIN) == -1)
		pipex_error("dup2", pipex);
	if (dup2(wr_fd, STDOUT) == -1)
		pipex_error("dup2", pipex);
}

void	redirect_io(int i, t_pipex pipex)
{

	if (i == 0)
	{
		open_file(pipex);
		dup_io(pipex, pipex -> infd, pipex -> pfds[1]);
		close(pipex -> infd);
	}	
	if (i == cmd_count - 1)
	{
		open_file(pipex);
		dup_io(pipex, pipex -> pfds[2 * (i - 1)], pipex -> outfd);
		close(pipex -> outfd);
	}
	else
	{
		i *= 2;
		dup_io(pipex, pipex -> pfds[i - 2], pipex -> pfds[i + 1]);
	}
	close_pfds(pipex)
}

int	wait_child(pid_t pid_last)
{
	int	status;
}

void	pipex(t_pipex pipex)
{
	int	i;
	int	status;
	pid_t	pid;

	i = 0;
	while (i < pipex -> cmd_count)
	{
		pid = fork();
		if (pid < 0)
			pipex_error("fork:", pipex);
		else if (pid == 0)
		{
			redirect_io(i, pipex);
			execute_cmd(i, pipex);
		}
		i++;
	}
	close_pfds();
	status = wait_child(pid);
	return (status);
}
