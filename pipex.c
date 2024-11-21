/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweerasi <wweerasi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 14:51:32 by wweerasi          #+#    #+#             */
/*   Updated: 2024/11/14 19:54:51 by wweerasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int ac, char **av, char **envp)
{
	t_pipex	pipex;

	if (ac != 5)
	{
		ft_putendl_fd("# Output: Error: Invalid number of arguments.\n
			# Usage: ./pipex file1 cmd1 cmd2 file2", 2);
		exit(EXIT_FAILURE);
	}
	pipex_init(&pipex, ac, av, envp);
	pipex(&pipex);
}

void	dup_io(t_pipex *pipex, int rd_fd, int wr_fd)
{
	if (dup2(rd_fd, STDIN) == -1)
		pipex_error("dup failed");
	if (dup2(wr_fd, STDOUT) == -1)
		pipex_error("dup failed");
}


void redirect_io(int i, t_pipex pipex)
{
	if (i == 0)
		dup_io(pipex, pipex -> infd, pipex -> pfds[1]); 
	if (i == cmd_count - 1)
		dup_io(pipex, pipex -> pfds[(i - 1) * 2], pipex -> outfd);
	else
		dup_io(pipex, pipex -> pfds[(i - 1) * 2], pipex -> pfds[(i * 2) + 1]);
	close_pipes(pipex)
}

int	wait_child(pid_t pid)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (FAILSTD);
}

void pipex(t_pipex pipex)
{
	int	i;
	pid_t	pid;

	i = 0;
	while (i < pipex -> cmd_count)
	{
		pid = fork();
		if (pid < 0)
			pipex_error("Fork: "));
		else if (pid == 0)
		{
			redirect_io(i, pipex);
			execute_cmd(i, pipex);
		}
		i++;
	}
	close_pfds();
	while (pid > 0)
		status = wait_child(pid);
	return (status);
}

