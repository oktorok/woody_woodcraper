#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main(void)
{
	char *text;

	text = strdup("Lorem ipsum dolor sit amet, consectetuer adipiscing elit. Aenean commodo ligula eget dolor. Aenean m");
	printf("Text:\n%s\nsize=%d\n\n", text, strlen(text));
	for(int i=0; i < 100; i++)
		text[i] ^= 0x42;
	int fd;
	fd = open("test.txt", O_WRONLY);
	write(fd, text, 101);
	close(fd);
	return 0;
}
