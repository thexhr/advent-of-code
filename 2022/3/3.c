#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

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
find_dups(char *l1, char *l2)
{
	char *p1 = l1;
	char *p2;

	while (*p1 != '\0') {
		p2 = l2;
		while (*p2 != '\0') {
			if (*p2 == *p1)
				return *p2;
			p2++;
		}
		p1++;
	}
	return '0';
}

int
main(int argc, char **argv)
{
	char *line = NULL, *w1 = NULL, *w2;
	FILE *fd;
	size_t len = 0;
	ssize_t read;
	char dup;
	int sum = 0;

	if ((fd = fopen("input", "r")) == NULL) {
		printf("Cannot open file\n");
		return 1;
	}

	while ((read = getline(&line, &len, fd)) != -1) {
		if (read <= 1)
			continue;

		//printf("2 items, len %ld ", read/2);
		if ((w1 = calloc(1, (read/2)+2)) == NULL) {
			printf("cannot allocate memory\n");
			return 1;
		}
		snprintf(w1, (read/2)+1, "%s", line);
		w2 = line + (read/2);

		dup = find_dups(w1, w2);
		//printf("dup: %c, prio: %d", dup, prio(dup));

		sum += prio(dup);
		//printf("\n");
	}

	printf("final sum: %d\n", sum);
	fclose(fd);

	if (line != NULL)
		free(line);
	if (w1 != NULL)
		free(w1);

	return 0;
}
