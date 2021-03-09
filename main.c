#include <unistd.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

int		get_next_line(int fd, char **line);

int main(void)
{
	char *line;
	int ret;

	int fd = open("txt.txt", O_RDONLY);
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		printf("%s\n", line);
		printf("%i\n", ret);
		free (line);
	}
	printf("%s\n", line);
	printf("%i\n", ret);
	free (line);
	return (0);
}
