/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweerasi <wweerasi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 12:04:39 by wweerasi          #+#    #+#             */
/*   Updated: 2024/10/17 17:35:16 by wweerasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <stdio.h>

int main()
{
	char *infile = "infile.txt";
	char *outfile = "outfile.txt";
	char **cmd1 = {"/bin/sort", {"ls", "-l", NULL}, NULL};
	char **cmd2 = {"/bin/grep", {"grep", "x", NULL}, NULL};
	char **cmd3 = {"/bin/grep", {"grep", "y", NULL}, NULL};
	char **cmd4 = {"/bin/wc", {"wc","-l", NULL}, NULL};
	char **cmd = {cmd1, cmd2, cmd3, cmd4, cmd5};
	int *pids[5];//might have to malloc
	int pfds[2];
	int procnum = 0;
	pid_t pid = 0;

	if (pipe(pfds) == -1)
	{
		perror("pipe");
		exit(1);
	}
	while (procnum < 5)
	{
		if (pid == 0)
		{
			pid = fork();
			if (pid == -1)
			{
				perror("fork");
				exit(1);
			}
			pids[procnum] = pid;
		}
	}
	int i = 0;
	while (pids[i])
	{
		if (pid[i] == pids)
		{
			close(pfds[0]);
			dup2(pfds[1],0);
			execve(cmd[i])
		}
	}

	if (pids[0] == 0)
	{
		while(wait() > 0)
			usleep(1);
	}
	




//might be able to save the pids in array so we can wait for each pid
}	
