/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweerasi <wweerasi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 19:37:16 by wweerasi          #+#    #+#             */
/*   Updated: 2024/11/30 19:42:21 by wweerasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

void	close_pfds(t_pipex *pipex)
{
	int i;
	i = 0;
	while (i < pipex -> cmd_count - 1) //can this be zero at somepoint after redirecting
	{
		if (pipex -> pfds[2 * i] > 0)
			close(pipex -> pfds[2 * i]);
		if (pipex -> pfds[2 * i + 1] > 0)
			close(pipex -> pfds[2 * i + 1]);
		else
			break;              //to be used if pipes are not created correctly and program exits midway in pipe init function
		i++;
	}
	free(pipex -> pfds);
	pipex -> pfds = NULL;
}

void	pipex_error(const char *err_note, t_pipex *pipex)
{
	perror(err_note);
	close_pdfs(pipex);
  	free(pipex -> arr_path);
  	free(pipex -> path);
  	free_arr(pipex -> cmd_arr);
	exit(EXIT_FAILURE);
}
