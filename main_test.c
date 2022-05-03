#include "get_next_line.h"
#include <sys/stat.h>
#include <fcntl.h>

int main()
{
	int fd = open("multiple_nlx5", O_RDONLY);
	char *nextline = get_next_line(fd);
	printf("%s \n", nextline);
	printf("that was the first line \n");
	char *nextline2 = get_next_line(fd);
	printf("%s \n", nextline2);
	printf("that was the 2nd line \n");
	char *nextline3 = get_next_line(fd);
	printf("%s \n", nextline3);
	int x = 0;
	while (x++ < 15)
	{
		printf("%s", get_next_line(fd));
	}
}