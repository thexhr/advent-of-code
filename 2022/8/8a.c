#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LEN 6 //101
#define LINES 3

int
check_visible(char lines[LINES][MAX_LINE_LEN])
{
	int lc = 0, tree, invisible = 0;

	for (lc = 0; lc < MAX_LINE_LEN; lc++) {
		if (lc == 0 || lc == MAX_LINE_LEN-1) {
			//printf("%c", lines[1][lc]);
			continue;
		}
		tree = lines[1][lc];
		if ((tree < lines[1][lc-1]) &&
			(tree < lines[1][lc+1]) &&
			(tree < lines[0][lc]) &&
			(tree < lines[2][lc])) {
			invisible++;
			//printf("%c*", lines[1][lc]);
		} else {
			//printf("%c", lines[1][lc]);
		}
	}
	//printf("\n");
	return invisible;
}

int
main(int argc, char **argv)
{
	char *line = NULL;
	char lines[LINES+1][MAX_LINE_LEN];
	//char l1[MAX_LINE_LEN];
	//char l2[MAX_LINE_LEN];
	FILE *fd;
	size_t len = 0;
	ssize_t read;
	int counter = 0, inv = 0;

	memset(lines, 0, sizeof(lines));

	if ((fd = fopen("input", "r")) == NULL) {
		printf("Cannot open file\n");
		return 1;
	}

	while ((read = getline(&line, &len, fd)) != -1) {
		if (read <= 1)
			continue;
		if (read > MAX_LINE_LEN) {
			printf("Buffer to short. Abort\n");
			return 1;
		}

		if (counter > LINES) {
			for (int i=0; i<LINES; i++) {
				strncpy(lines[i], lines[i+1], read);
			}
			strncpy(lines[LINES], line, read);

			inv += check_visible(lines);
		} else if (counter == LINES) {
			//printf("%s", line);
			strncpy(lines[counter], line, read);

			inv += check_visible(lines);
		} else {
			strncpy(lines[counter], line, read);
		}
		counter++;
	}

	printf("visible trees: %d, invs: %d\n", counter*(MAX_LINE_LEN-1), inv);
	fclose(fd);

	if (line != NULL)
		free(line);

	return 0;
}
