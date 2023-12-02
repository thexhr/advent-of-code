#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int
main(int argc, char **argv)
{
	char *line = NULL, *ptr;
	FILE *fd;
	size_t len = 0;
	ssize_t read;
	int first = -1;
	int last = -1;
	int sum = 0;

	if ((fd = fopen("input", "r")) == NULL) {
		printf("Cannot open file\n");
		return 1;
	}

	while ((read = getline(&line, &len, fd)) != -1) {
		ptr = line;
		while (*ptr != '\n') {
			if (isdigit(*ptr) != 0) {
				if (first == -1)
					first = *ptr-48;
				last = *ptr-48;
			}
			ptr++;
		}

		sum += (first * 10) + last;
		//printf("%d, %d, %d, %s", first, last, sum, line);
		first = last = -1;
	}

	printf("sum: %d\n", sum);

	fclose(fd);

	if (line != NULL)
		free(line);

	return 0;
}
