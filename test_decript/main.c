#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
extern void		decrypt(char *text, int size);

int main(void)
{
	int fd;
	char data[101];
	
	fd = open("test.txt", O_RDONLY);

	read(fd, data, 100);
	data[100] = 0;
	printf("%s\n", data);
	decrypt(data, 100);
	printf("%s\n", data);
	return 0;
}
