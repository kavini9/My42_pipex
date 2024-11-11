/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweerasi <wweerasi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 14:51:32 by wweerasi          #+#    #+#             */
/*   Updated: 2024/11/11 20:37:50 by wweerasi         ###   ########.fr       */
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


void pipex_init(t_pipex *pipex, int ac, char **av, char **envp)
{
	pipex -> infd = open(av[1], O_RDONLY);
	if (argc > 5 && ft_strncmp(av[1], "here_doc", 8) == 0)
		pipex -> heredoc = 1;
	pipex -> cmd_count = ac - 3 - pipex -> heredoc;
	pipex -> outfd = open(av[ac - 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
	pipex -> arr_path = get_arr_path(envp);
	pipex -> cmds ;
	pipex -> pfds = malloc( (cmd_count - 1) * 2 * sizeof(int));
}

void fd_redirect(int i, t_pipex pipex)
{
	if (i == 0)
	{
		dup2(pipex -> infd, STDIN_FILENO);
		dup2(pipex -> pfds[1], STDOUT_FILENO);
		close(pipex -> pfds[0]);
		close(pipex -> infd);
	}
	if (i == cmd_count - 1)
	{
		dup2(pipex -> pfds[i * 2], STDIN_FILENO);
		dup2(pipex -> outfd, STDOUT_FILENO);
		close(pipe -> pfds[





void pipex(t_pipex pipex)
{
	int	i;
	int	pipefd[2];
	pid_t	pid;

	i = 1;
	pipe(pipefd);
	while (i <= pipex -> cmd_count)
	{
		pid = fork();
		if (pid < 0)
			return (perror("Fork: "));
		fd_redirect(i, pipex);
	}
}





char **validate_cmd(t_pipex pipex)
{
	
}

char	**get_arr_path(char **envp)
{
	char	**arr_path;

	arr_path = NULL;
	if (!envp || !*envp)
		return (NULL); //check what kind of error this may cause
	while (*envp && ft_strncmp(*envp, "PATH=", 5))
		envp++;
	if (*envp)
		arr_path = ft_split( *envp + 5, ':');
	if (!arr_path)
		//erro message cz arr_path is null
	return (arr_path);
}


char 	**parse_cmd(char **argv[], int start,  int end)
{ 

	





//command handling
//if argv[i] strchr('/') true ==> split('/')
//if arg[last] strchr (' ') true ==> split(' ')
