#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int
cmp(const void *a, const void *b)
{
	unsigned int x = (*(unsigned int *)a);
	unsigned int y = (*(unsigned int *)b);

	return x < y ? -1 : x > y;
}

int
main(int argc, char **argv)
{
	char *line = NULL;
	FILE *fd;
	size_t len = 0;
	ssize_t read;
	int elves = 0;
	unsigned int calories[255] = {0};
	unsigned int max = 0;

	if ((fd = fopen("input", "r")) < 0) {
		printf("Cannot open file\n");
		return 1;
	}

	while ((read = getline(&line, &len, fd)) != -1) {
		if (read == 1)
			elves++;
		else
			calories[elves] += atoi(line);
	}

	fclose(fd);

	if (line != NULL)
		free(line);

	qsort(&calories, 255, sizeof(unsigned int), cmp);

	for (int i=254; i>251; i--) {
		max += calories[i];
	}
	printf("max top 3 calories %d\n", max);
	return 0;
}
