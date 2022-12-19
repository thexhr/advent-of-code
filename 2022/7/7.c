#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void
cd(const char *line)
{
	printf("-- cd %s", line);
}

int
main(int argc, char **argv)
{
	char *line = NULL, *token;
	FILE *fd;
	size_t len = 0;
	ssize_t read;
	int cmd = 0;

	if ((fd = fopen("input", "r")) == NULL) {
		printf("Cannot open file\n");
		return 1;
	}

	while ((read = getline(&line, &len, fd)) != -1) {
		if (read <= 1)
			continue;

		while ((token = strsep(&line, " ")) != NULL) {
			//printf("|%s|", token);
			if (strcmp(token, "$") == 0) {
				cmd = 1;
				continue;
			}
			// Previous token was a command
			if (cmd) {
				if (strcmp(token, "cd") == 0) {
					cd(line);
				}
				cmd = 0;
				continue;
			}
		}
	}

	fclose(fd);

	if (line != NULL)
		free(line);

	return 0;
}
