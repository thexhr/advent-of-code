#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int
prio(char p)
{
	int c = 0;

	if (islower(p)) {
		c = (int)p - 96;
	} else if (isupper(p)) {
		c = (int)p - 38;
	}

	return c;
}

char
find_dups(char *l1, char *l2, char *l3)
{
	char *p1 = l1;
	char *p2;
	char *p3;

	while (*p1 != '\0') {
		p2 = l2;
		while (*p2 != '\0') {
			p3 = l3;
			while (*p3 != '\0') {
				if (*p3 == *p2 && *p2 == *p1)
					return *p3;
				p3++;
			}
			p2++;
		}
		p1++;
	}
	return '0';
}

int
main(int argc, char **argv)
{
	char *line = NULL;
	char *larr[3];
	FILE *fd;
	size_t len = 0;
	ssize_t read;
	char dup;
	int sum = 0, counter = 0;

	if ((fd = fopen("input", "r")) == NULL) {
		printf("Cannot open file\n");
		return 1;
	}

	// XXX 48 is the max line length in input XXX
	for (int i=0; i < 3; i++) {
		if ((larr[i] = calloc(1, sizeof(char)*50)) == NULL) {
			return -1;
		}
	}

	while ((read = getline(&line, &len, fd)) != -1) {
		if (read <= 1)
			continue;
		if (read > 49) {
			printf("line len to long\n");
			return -1;
		}

		snprintf(larr[counter], read, "%s", line);

		if (counter == 2) {
			dup = find_dups(larr[0], larr[1], larr[2]);
			sum += prio(dup);
			//printf("%s, %s, %s dup: %c, \n", larr[0], larr[1], larr[2], dup);
			counter = 0;
			memset(larr[0], 0, 50);
			memset(larr[1], 0, 50);
			memset(larr[2], 0, 50);
			continue;
		}
		counter++;
	}

	printf("final sum: %d\n", sum);
	fclose(fd);

	if (line != NULL)
		free(line);

	return 0;
}
