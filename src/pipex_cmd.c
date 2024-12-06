/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweerasi <wweerasi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 01:58:43 by wweerasi          #+#    #+#             */
/*   Updated: 2024/12/06 15:26:05 by wweerasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	access_check(char *cmd, t_pipex *pipex)
{
	if (access(cmd, F_OK) == 0)
	{
		if (access(cmd, X_KO) == 0)
			return (0);
		else
			pipex -> status = X_KO;
	}
	else
		pipex -> status = F_KO;
	return (-1);
}

char	*get_cmd_path(char *cmd, t_pipex *pipex)
{
	char	*cmd_path;
	char	*tmp;

	while (*pipex -> arr_path)
	{
		cmd_path = ft_strjoin("/", cmd);
		tmp = cmd_path;
		if (cmd_path)
			cmd_path = ft_strjoin(*pipex -> arr_path, tmp);
		if (tmp)
			free(tmp);
		if (!cmd_path)
			return (NULL);
		if (access_check(cmd_path, pipex) == 0)
			return(cmd_path);
	//	if (access(cmd_path, F_OK) == 0)
	//	{
	//		if (access(cmd_path, X_OK) == 0)
	//			return (cmd_path);
	//		else
	//			pipex -> status = X_KO;
	//	}
		free(cmd_path);
		pipex -> arr_path++;
	}
	return (ft_strdup(cmd));
}

void	execute_cmd(int cmd_no, t_pipex *pipex)
{
	char	**cmd_arr;
	char	*path;

	path = pipex -> path;
	cmd_arr = ft_split(pipex -> av[cmd_no + 2 + pipex -> heredoc], ' ');
	pipex -> cmd_arr = cmd_arr;
	if (!cmd_arr || !*cmd_arr)
		pipex_error("cmd: ", pipex);
	if (!ft_strchr(*cmd_arr, '/'))
		path = get_cmd_path(*cmd_arr, pipex);
	else if (access_check(*cmd_arr, pipex) == 0)
		path = ft_strdup(*cmd_arr);
//	else if (access(*cmd_arr, F_OK) == 0)
//	{
//		if (access(*cmd_arr, X_OK) == 0)
//			path = ft_strdup(*cmd_arr);
//		else
//			pipex -> status = X_KO;
//	}
//	else
//		pipex -> status = F_KO;
	if (!path)
		pipex_sys_error("path: ", *cmd_arr, pipex);
	execve(path, cmd_arr, pipex -> envp);
	pipex_sys_error("execve: ", *cmd_arr, pipex);
}
//free_cmd was on line 53. see why. if that still matters?
//handle cmd = "" and "    "
//also when binary exist but not executable exit code should be 126;
