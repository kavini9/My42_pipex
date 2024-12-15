/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweerasi <wweerasi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 01:58:43 by wweerasi          #+#    #+#             */
/*   Updated: 2024/12/08 09:23:30 by wweerasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static int	is_empty(char *str)
{
	if (*str == '\0')
		return (1);
	while (*str)
	{
		if (!(*str == ' ' || (*str >= 9 && *str <= 13)))
			return (0);
		str++;
	}
	return (1);
}

static char	**arrdup_empty(char *cmd)
{
	char **cmd_arr;

	cmd_arr = malloc(2 * sizeof(char *));
	if (cmd_arr)
	{
		cmd_arr[0] = ft_strdup(cmd);
		cmd_arr[1] = NULL;
	}
	return (cmd_arr);
}

int	access_check(char *cmd, t_pipex *pipex)
{
	if (access(cmd, F_OK) == 0)
	{
		if (access(cmd, X_OK) == 0)
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
	char	**arr_path;
	char	*cmd_path;
	char	*tmp;

	arr_path = pipex -> arr_path;
	while (arr_path && *arr_path)
	{
		cmd_path = ft_strjoin("/", cmd);
		tmp = cmd_path;
		if (cmd_path)
			cmd_path = ft_strjoin(*arr_path, tmp);
		if (tmp)
			free(tmp);
		if (!cmd_path)
			return (NULL);
		if (access_check(cmd_path, pipex) == 0)
			return (cmd_path);
		free(cmd_path);
		arr_path++;
	}
	pipex -> status = F_KO;
	pipex -> err_note = CMD_NOT_FOUND;
	return (ft_strdup(cmd));
}

void	execute_cmd(int cmd_no, t_pipex *pipex)
{
	char	**cmd_arr;
	char	*cmd;

	cmd = pipex -> av[cmd_no + 2 + pipex -> heredoc];
	if (is_empty(cmd))
		cmd_arr = arrdup_empty(cmd);
	else
		cmd_arr = ft_split(cmd, ' ');
	pipex -> cmd_arr = cmd_arr;
	if (!cmd_arr)
		pipex_error("cmd: ", pipex);
	if (*cmd_arr && !ft_strchr(*cmd_arr, '/'))
		pipex -> path = get_cmd_path(*cmd_arr, pipex);
	else if (*cmd_arr)// && access_check(*cmd_arr, pipex) == 0)
	{
		access_check(*cmd_arr, pipex);
		pipex -> path = ft_strdup(*cmd_arr);
	}
	if (!pipex -> path)
		pipex_sys_error("path: ", *cmd_arr, pipex);
	execve(pipex -> path, cmd_arr, pipex -> envp);
	pipex_sys_error("execve: ", *cmd_arr, pipex);
}
//free_cmd was on line 53. see why. if that still matters?
//handle cmd = "" and "    "
//also when binary exist but not executable exit code should be 126;
