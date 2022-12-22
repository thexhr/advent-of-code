#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static const char *dir_str[] = {
    "forward", "down", "up",
};

enum direction {
	FORWARD,
	DOWN,
	UP,
};

void
steer(int dir, int value, int *hor, int *depth)
{
	if (dir == FORWARD)
		*hor += value;
	else if (dir == DOWN)
		*depth += value;
	else if (dir == UP)
		*depth -= value;

	printf("dir: %s, value: %d, hor: %d, depth: %d\n", dir_str[dir], value, *hor, *depth);
}

int
main(int argc, char **argv)
{
	char *line = NULL, *token;
	FILE *fd;
	size_t len = 0;
	ssize_t read;
	int horizontal = 0, depth = 0, direction = -1, temp = 0;

	if ((fd = fopen("input", "r")) == NULL) {
		printf("Cannot open file\n");
		return 1;
	}

	while ((read = getline(&line, &len, fd)) != -1) {
		while ((token = strsep(&line, " ")) != NULL) {
			if (strcmp(token, "forward") == 0)
				direction = FORWARD;
			else if (strcmp(token, "down") == 0)
				direction = DOWN;
			else if (strcmp(token, "up") == 0)
				direction = UP;

			if (direction != -1)
				temp = atoi(token);
		}
		steer(direction, temp, &horizontal, &depth);
		direction = -1;
		temp = 0;
	}

	printf("hori: %d, depth: %d, mult: %d\n", horizontal, depth, horizontal*depth);

	fclose(fd);

	if (line != NULL)
		free(line);

	return 0;
}
