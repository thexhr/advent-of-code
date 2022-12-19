#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int
includes(int r[4])
{
	if ((r[2] >= r[0]) && (r[1] >= r[3]))
		return 1;
	if ((r[0] >= r[2]) && (r[3] >= r[1]))
		return 1;

	return 0;
}

int
main(int argc, char **argv)
{
	char *line = NULL, *token, *t2;
	FILE *fd;
	size_t len = 0;
	ssize_t read;
	int ranges[4] = { 0 };
	int sum = 0;

	if ((fd = fopen("input", "r")) == NULL) {
		printf("Cannot open file\n");
		return 1;
	}

	while ((read = getline(&line, &len, fd)) != -1) {
		if (read <= 1)
			continue;

		int i = 0;
		while ((token = strsep(&line, ",")) != NULL) {
			while ((t2 = strsep(&token, "-")) != NULL) {
				ranges[i++] = atoi(t2);
			}
		}
		i = 0;
#if 0
		for (i = 0; i< 4; i++) {
			printf("%d ", ranges[i]);
		}
#endif
		if (includes(ranges)) {
			//printf("x");
			sum++;
		}
		//printf("\n");
	}

	printf("final sum: %d\n", sum);
	fclose(fd);

	if (line != NULL)
		free(line);

	return 0;
}
