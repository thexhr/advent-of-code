#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int
main(int argc, char **argv)
{
	char *line = NULL;
	FILE *fd;
	size_t len = 0;
	ssize_t read;
	int last = 100000, inc = 0;

	if ((fd = fopen("input", "r")) == NULL) {
		printf("Cannot open file\n");
		return 1;
	}

	while ((read = getline(&line, &len, fd)) != -1) {
		//printf("%s", line);
		if (atoi(line) > last)
			inc++;
		last = atoi(line);
	}

	printf("incs: %d\n", inc);

	fclose(fd);

	if (line != NULL)
		free(line);

	return 0;
}
