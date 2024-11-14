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
int	ft_strncmp(const char *s1, const char *s2, size_t n);

char	**get_path_array(char **envp)
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
		perror("arr_path = ft_split crashed");
	return (arr_path);
}

char	*get_cmd_path(char *cmd, char **arr_path)
{
	char *cmd_path;
	char *tmp;

	while(*arr_path)
	{
		cmd_path = ft_strjoin("/", cmd);
		if (!cmd_path)
			break;
		tmp = cmd_path;
		cmd_path = ft_strjoin(*arr_path,cmd);
		free(tmp);
		if (!cmd_path)
			break;
		if (access(cmd_path, F_OK) == 0 && access(*cmd_path, X_OK = 0))
			return (cmd_path);
	}

}
	


char	**get_cmd_array(int cmd_no, t_pipex *pipex)
{
	char **cmd_arr;
	char *path;

	cmd_arr = ft_split(pipex -> av[cmd_no + 2 + heredoc], ' ');
	if (!cmd_arr)
		perror("cmd_arr crashed at split");
	if (!ft_strchr(*cmd_arr,'/'))
		path = get_cmd_path(*cmd_arr, pipex -> arr_path);




	
}

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
