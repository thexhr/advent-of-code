#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_LINE_LEN 100
#define LINES 99

int
check_visible(char lines[LINES][MAX_LINE_LEN+1])
{
	int tree, visible = 0;
	int is_smaller = 0;

	for (int row = 0; row < LINES; row++) {
		// First and last line are always visible
		if (row == 0 || row == LINES-1) {
			visible += MAX_LINE_LEN-1;
			continue;
		}
		if (visible
		for (int column = 0; column < MAX_LINE_LEN; column++) {
out:
			if (is_smaller) {
				//printf("*");
				is_smaller = 0;
			}
			// First and last tree in a row is always visible
			if (column == 0 || column == MAX_LINE_LEN-1) {
				visible++;
				continue;
			}
			tree = lines[row][column];
			printf("%d", tree);
			for (int i=column+1; i < MAX_LINE_LEN; i++) {
				// As soon as the tree is smaller as one to the RIGHT, it's invisible
				if (tree < lines[row][i]) {
					is_smaller = 1;
					goto out;
				}
			}
			for (int i=column-1; i > 0; i--) {
				// As soon as the tree is smaller as one to the LEFT, it's invisible
				if (tree < lines[row][i]) {
					is_smaller = 1;
					goto out;
				}
			}
			for (int i=row-1; i > 0; i--) {
				// As soon as the tree is smaller as one to the ABOVE, it's invisible
				if (tree < lines[i][column]) {
					is_smaller = 1;
					goto out;
				}
			}
			for (int i=row+1; i < LINES; i++) {
				// As soon as the tree is smaller as one to the BELOW, it's invisible
				if (tree < lines[i][column]) {
					is_smaller = 1;
					goto out;
				}
			}
		}
		sleep(1);
	}

	return visible;
}

int
main(int argc, char **argv)
{
	char *line = NULL;
	char lines[LINES+1][MAX_LINE_LEN+1];
	FILE *fd;
	size_t len = 0;
	ssize_t read;
	int counter = 0, visible = 0, total = 0;

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

		//printf("%s", line);
		strncpy(lines[counter++], line, read);
	}
	visible = check_visible(lines);

	// Last line of trees
	visible += MAX_LINE_LEN-1;

	total = counter * (MAX_LINE_LEN);
	printf("trees toal: %d, visible: %d invs: %d\n", total, visible, total-visible);
	fclose(fd);

	if (line != NULL)
		free(line);

	return 0;
}
