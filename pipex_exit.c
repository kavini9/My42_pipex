void	close_pipe_arr(t_pipex *pipex)
{
  int *fd;

  fd = pipex -> pfds;
	while (*fd)
  {
		close(*fd);
    fd++;
  }
	free(pipex -> pfds);
}

void	pipex_error(const char *err_note, t_pipex *pipex)
{
	perror(err_note);
	close_all_pipes(pipex);
  	free(pipex -> arr_path);
  	free(pipex -> path);
  	free_arr(pipex -> cmd_arr);
	exit(EXIT_FAILURE);
}
