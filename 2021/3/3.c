#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 12
#define ENTRIES 1000

int
bin2dec(char *bin, int len)
{
	char *ptr = bin;
	int dec = 0, l = 0;

	while (l < len) {
		if (*ptr == '1') dec = dec * 2 + 1;
		else if (*ptr == '0') dec *= 2;
		ptr++; l++;
	}

	return dec;
}

int
main(int argc, char **argv)
{
	char *line = NULL;
	FILE *fd;
	size_t len = 0;
	ssize_t read;
	int pos = 0, c = 0;
	char input[ENTRIES+1][MAX+2];
	char gamma[MAX+2];
	char epsilon[MAX+2];

	if ((fd = fopen("input", "r")) == NULL) {
		printf("Cannot open file\n");
		return 1;
	}

	memset(input, 0, sizeof(input));
	memset(gamma, 0, sizeof(gamma));
	memset(epsilon, 0, sizeof(epsilon));

	while ((read = getline(&line, &len, fd)) != -1) {
		snprintf(input[pos++], MAX+1, "%s", line);
	}

	int ones = 0, zeroes = 0;

	for (pos = 0; pos < MAX; pos++) {
		for (c = 0; c < ENTRIES; c++) {
			if (input[c][pos] == 48)
				ones++;
			else
			 	zeroes++;
		}
		if (ones > zeroes) {
			gamma[pos] = '1';
			epsilon[pos] = '0';
		} else {
			gamma[pos] = '0';
			epsilon[pos] = '1';
		}
		ones = zeroes = 0;
	}

	printf("mult: %d\n", bin2dec(gamma, sizeof(gamma)) * bin2dec(epsilon, sizeof(epsilon)));

	fclose(fd);

	if (line != NULL)
		free(line);

	return 0;
}
