/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweerasi <wweerasi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 15:32:07 by wweerasi          #+#    #+#             */
/*   Updated: 2024/11/14 22:11:45 by wweerasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

char	**ft_split(char const *s, char c);

char	*get_cmd_path(char *cmd, char **arr_path)
{
	char *cmd_path;
	char *tmp;

	while(*arr_path)
	{
		cmd_path = ft_strjoin("/", cmd);
		tmp = cmd_path;
		if (cmd_path)
			cmd_path = ft_strjoin(*arr_path,cmd_path);
		if (tmp)
			free(tmp);
		if (!cmd_path)
			break;
		if (access(cmd_path, F_OK | X_OK) == 0)
			return (cmd_path);
		free(cmd_path);
		arr_path++;
	}
	return (NULL);
}

void execute_cmd(int cmd_no, t_pipex *pipex)
{
	char **cmd_arr;
	char *path;

	cmd_arr = pipex -> cmd_arr;
	path = pipex -> path;
	cmd_arr = ft_split(pipex -> av[cmd_no + 2 + heredoc], ' ');
	if (!cmd_arr || !*cmd_arr)
		pipex_error("CMDARRAY_ERROR");
	if (!ft_strchr(*cmd_arr,'/'))
		path = get_cmd_path(*cmd_arr, pipex -> arr_path);
	else if (access(*cmd_arr, F_OK | R_OK | X_OK) == 0)
		path = ft_strdup(*cmd_arr);
	if (!path)
		pipex_error("PATH_ERROR"); // free cmd_arr
	execve(path, cmd_arr, pipex -> envp);
	pipex_error("EXECVE_FAIL);	
}
		
/*
int main(int argc, char **argv, char **envp)
{
	char **path_array;
//	char **cmd_path;
	char **temp;


	(void)argv;
	(void)argc;
	path_array = get_arr_path(envp);
	temp = path_array;
	while (*path_array)
	{
		printf("argv = %s_\n", *path_array);
		path_array++;	
	}
	path_array = temp;
	while (*temp)
	{
		printf("free = %s_\n", *temp);
		free(*temp);
		*temp =NULL;
		temp++;
	}
	free(path_array);
	path_array = NULL;

}
*/
