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
	int elves = 0, elve;
	unsigned int calories[255] = {0};
	unsigned int max = 0;

	if ((fd = fopen("input", "r")) == NULL) {
		printf("Cannot open file\n");
		return 1;
	}

	while ((read = getline(&line, &len, fd)) != -1) {
		if (read == 1)
			elves++;
		else
			calories[elves] += atoi(line);
	}

	for (int i=0; i<255; i++) {
		if (calories[i] >= max) {
			max = calories[i];
			elve = i;
		}
	}
	printf("elve %d calories %d\n", elve, max);

	fclose(fd);

	if (line != NULL)
		free(line);

	return 0;
}
