/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweerasi <wweerasi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 01:58:13 by wweerasi          #+#    #+#             */
/*   Updated: 2024/12/08 09:35:32 by wweerasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	init_pipeline(t_pipex *pipex)
{
	int	i;
	int	pipe_count;

	i = 0;
	pipe_count = pipex -> cmd_count - 1;
	pipex -> pfds = malloc(2 * pipe_count * sizeof(int));
	if (!pipex -> pfds)
		pipex_error ("malloc: ", pipex);
	else
		ft_memset(pipex -> pfds, -1, 2 * pipe_count * sizeof(int));
	while (i < pipe_count)
	{
		if (pipe(pipex -> pfds + (2 * i)) < 0)
			pipex_sys_error("pipe: ", ft_itoa(i), pipex);
		i++;
	}
}

void	get_path_array(char **envp, t_pipex *pipex)
{
	pipex -> arr_path = NULL;
	if (!envp || !*envp || !**envp)
		return;
	while (*envp && ft_strncmp(*envp, "PATH=", 5))
		envp++;
	if (*envp && **envp)
		pipex -> arr_path = ft_split(*envp + 5, ':');
	if (!pipex -> arr_path)
		pipex_error("split: ", pipex);
}
//when the path is given like ex: /usr/bin/cat , because the pipex -> arr_ path iis still null it causes a error instead of executing correctly is still not found 
void	pipex_init(t_pipex *pipex, int ac, char **av, char **envp)
{
	pipex -> infd = -1;
	pipex -> outfd = -1;
	pipex -> heredoc = 0;
	if (ac > 5 && ft_strcmp(av[1], "here_doc") == 0)
		pipex -> heredoc = 1;
	pipex -> cmd_count = ac - 3 - pipex -> heredoc;
	init_pipeline(pipex);
	pipex -> status = EXIT_FAILURE;
	pipex -> ac = ac;
	pipex -> av = av;
	pipex -> envp = envp;
	get_path_array(envp, pipex);
	pipex -> cmd_arr = NULL;
	pipex -> path = NULL;
}
