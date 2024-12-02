/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweerasi <wweerasi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 15:32:07 by wweerasi          #+#    #+#             */
/*   Updated: 2024/12/02 21:31:44 by wweerasi         ###   ########.fr       */
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
		pipex_error("");
	if (!ft_strchr(*cmd_arr,'/'))
		path = get_cmd_path(*cmd_arr, pipex -> arr_path);
	else if (access(*cmd_arr, F_OK | R_OK | X_OK) == 0)
		path = ft_strdup(*cmd_arr);
	if (!path)
		pipex_error("path", pipex); // free cmd_arr
	execve(path, cmd_arr, pipex -> envp);
	pipex_error("execve", pipex);	
}
