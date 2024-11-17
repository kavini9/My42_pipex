#include "pipex.h"
char	**ft_split(char const *s, char c);
int	ft_strncmp(const char *s1, const char *s2, size_t n);

int *init_pipes(t_pipex *pipex)
{
  int i;

  i = 0;
  pipex -> pfds = malloc(2 * ( pipex -> cmd_count - 1) * sizeof(int));
  if (!pfds)
    return (NULL);
  while ( i < pipex -> cmd_count - 1)
  {
    
  }
}





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
		pipex_error("arr_path = ft_split crashed");
	return (arr_path);
}

void pipex_init(t_pipex *pipex, int ac, char **av, char **envp)
{
	pipex -> infd = open(av[1], O_RDONLY);
	if (argc > 5 && ft_strncmp(av[1], "here_doc", 8) == 0)
		pipex -> heredoc = 1;
	pipex -> cmd_count = ac - 3 - pipex -> heredoc;
	pipex -> outfd = open(av[ac - 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
	pipex -> arr_path = get_path_array(envp);
	pipex -> cmds ;
	pipex -> pfds = init_pipes();
	pipex -> cmd_arr = NULL;
	pipex -> path = NULL;
}
