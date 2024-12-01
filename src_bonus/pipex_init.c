/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweerasi <wweerasi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 19:36:53 by wweerasi          #+#    #+#             */
/*   Updated: 2024/12/01 05:18:37 by wweerasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

void	init_pipes(t_pipex *pipex)
{
  int i;

  i = 0;
  pipex -> pfds = malloc(2 * ( pipex -> cmd_count - 1) * sizeof(int));
  if (!pipex -> pfds)
    pipex_error ("pipe_malloc failed");
  while ( i < pipex -> cmd_count - 1)
  {
    if (pipe( pipex -> pfds[2 * i] < 0)
	    pipex_error("PIPE_ERROR");
	i++;
  }	    
}

char	**get_path_array(char **envp)
{
  char	**arr_path;

	arr_path = NULL;
	if (!envp || !*envp)
		pipex_error ("No ENVP");
	while (*envp && ft_strncmp(*envp, "PATH=", 5))
		envp++;
	if (*envp)
		arr_path = ft_split( *envp + 5, ':');
	if (!arr_path)
		pipex_error("arr_path = ft_split crashed");
	return (arr_path);
}

void pipex_init(t_pipex *pipex, int ac, char **av, char **envp)
{
	pipex -> infd = -1; //open(av[1], O_RDONLY);
	pipex -> outfd = -1 //open(av[ac - 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (argc > 5 && ft_strcmp(av[1], "here_doc") == 0)
		pipex -> heredoc = 1;
	pipex -> cmd_count = ac - 3 - pipex -> heredoc;
	pipex -> arr_path = get_path_array(envp);
	pipex -> cmds ;
	pipex -> pfds = init_pipes();
	pipex -> cmd_arr = NULL;
	pipex -> path = NULL;
}
