/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_cmd_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweerasi <wweerasi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 21:27:51 by wweerasi          #+#    #+#             */
/*   Updated: 2024/12/04 03:54:52 by wweerasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

char	*get_cmd_path(char *cmd, char **arr_path)
{
	char *cmd_path;
	char *tmp;

	while(*arr_path)
	{
		cmd_path = ft_strjoin("/", cmd);
		tmp = cmd_path;
		if (cmd_path)
			cmd_path = ft_strjoin(*arr_path, tmp);
		if (tmp)
			free(tmp);
		if (!cmd_path)
			return (NULL);
		if (access(cmd_path, F_OK | X_OK) == 0)
			return (cmd_path);
		free(cmd_path);
		arr_path++;
	}
	return (ft_strdup(cmd));
}

void execute_cmd(int cmd_no, t_pipex *pipex)
{
	char **cmd_arr;
	char *path;

	cmd_arr = pipex -> cmd_arr;
	path = pipex -> path;
	cmd_arr = ft_split(pipex -> av[cmd_no + 2 + pipex -> heredoc], ' ');
	if (!cmd_arr || !*cmd_arr)
		pipex_error("cmd:", pipex);
	if (!ft_strchr(*cmd_arr,'/'))
		path = get_cmd_path(*cmd_arr, pipex -> arr_path);
	else if (access(*cmd_arr, F_OK | R_OK | X_OK) == 0)
		path = ft_strdup(*cmd_arr);
	if (!path)
		pipex_error("path:", pipex); // free cmd_
	execve(path, cmd_arr, pipex -> envp);
	pipex_sys_error("execve:", pipex);	
}

//handle cmd = "" and "    "
//also when binary exist but not executable exit code should be 126;
