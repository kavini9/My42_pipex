/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweerasi <wweerasi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 14:51:32 by wweerasi          #+#    #+#             */
/*   Updated: 2024/10/17 17:35:13 by wweerasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;

	if (argc != 5){
		ft_putendl_fd("# Output: Error: Invalid number of arguments.\n
			# Usage: ./pipex file1 cmd1 cmd2 file2", 2);
		exit(EXIT_SUCCESS);
	}
	pipex();
}

void pipex()

char	**get_arr_path(char **envp)
{
	char	**arr_path;

	if (!envp)
		return (NULL); //check what kind of error this may cause
	while (*envp && ft_strncmp(*envp, "PATH=", 5))
		*envp++;
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
//
