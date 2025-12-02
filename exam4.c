#include <stdlib.h>

int	ft_fopen(char *file, char **argv, int type)
{
	if (!file || !argv || (type != 'r' && type != 'w'))
		return -1;

	int fd[2];

	pipe(fd);
	if( type == 'r')
	{
		if (fork() == 0)
		{
			dup2(fd[1], 1);
			close(fd[0]);
			close(fd[1]);
			execvp(file, argv);
			exit (-1);
		}
		close(fd[1]);
		return (fd[0]);
	}
	if( type == 'w')
	{
		if (fork() == 0)
		{
			dup2(fd[0], 0);
			close(fd[0]);
			close(fd[1]);
			execvp(file, argv);
			exit (-1);
		}
		close(fd[0]);
		return (fd[1]);
	}
	return -1;
}

