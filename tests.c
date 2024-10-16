/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweerasi <wweerasi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 12:04:39 by wweerasi          #+#    #+#             */
/*   Updated: 2024/10/16 19:08:47 by wweerasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <stdio.h>

int main()
{
	char *infile = "infile.txt";
	char *outfile = "outfile.txt";
	char **cmd1 = {"sort"};
	char **cmd2 = {"grep", "x"};
	char **cmd3 = {"grep", "y"};
	char **cmd4 = {"wc", "-l"};
	char **cmd = {cmd1, cmd2, cmd3, cmd4, cmd5};
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
	}



//might be able to save the pids in array so we can wait for each pid
}	
