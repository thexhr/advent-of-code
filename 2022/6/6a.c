#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_PATTERNS 13

int
is_marker(const char *pattern)
{
	char c1;

	for (int i=0; i < MAX_PATTERNS; i++) {
		c1 = pattern[i];
		for (int j=i+1;j <= MAX_PATTERNS; j++) {
			if (c1 == pattern[j]) {
				return 0;
			}
		}
	}
	return 1;
}

int
main(int argc, char **argv)
{
	char pattern[MAX_PATTERNS+1];
	char l;
	ssize_t len;
	int fd;
	int count = 0, marker = 0;

	if ((fd = open("input", O_RDONLY)) == -1) {
		printf("Cannot open file\n");
		return 1;
	}

	memset(pattern, 0, MAX_PATTERNS);

	while ((len = read(fd, &l, 1)) > 0) {
		printf("%c", l);
		marker++;
		if (count > MAX_PATTERNS) {
			for (int i=0; i<MAX_PATTERNS; i++) {
				pattern[i] = pattern[i+1];
			}
			pattern[MAX_PATTERNS] = l;
			pattern[count+1] = '\0';
			if (is_marker(pattern)) {
				break;
			}
		} else {
			//printf("%c", l);
			pattern[count] = l;
			count++;
		}
	}

	printf("\nmarker: %d\n", marker);
	close(fd);

	return 0;
}
