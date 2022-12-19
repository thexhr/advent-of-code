#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum shape_score {
	A,
	B,
	C,
};

enum round_score {
	LOOSE = 0,
	DRAW = 3,
	WON = 6,
};

const char *
desc(const char c)
{
	switch (c) {
		case 'A': return "Rock";
		case 'B': return "Paper";
		case 'C': return "Scissor";
	}

	return "";
}

/* returns 0 for draw, 1 for player win, 2 for elve win */
int
play(const char e, const char p)
{
	/* A for Rock, B for Paper, and C for Scissors.
	 * Rock defeats Scissors, Scissors defeats Paper, and Paper defeats Rock. If both players choose the same shape, the round instead ends in a draw.
	 *
	 * E/P  R | P | S
	 *    R 0 | 1 | 2
	 *    P 1 | 0 | 1
	 *    S 2 | 1 | 0
	 */

	if (e == p)
		return 0;

	// Rock
	if (e == 'A') {
		if (p == 'B') return 1; // Paper
		if (p == 'C') return 2; // Scissor
	}
	// Paper
	if (e == 'B') {
		if (p == 'A') return 2; // Rock
		if (p == 'C') return 1; // Scissor
	}
	// Scissor
	if (e == 'C') {
		if (p == 'A') return 1; // Rock
		if (p == 'B') return 2; // Paper
	}

	return -1;
}

char
get_shape(const char e, const char p)
{
	// Rock
	if (e == 'A') {
		if (p == 'X') return 'C'; // Loose
		if (p == 'Y') return 'A'; // Draw
		if (p == 'Z') return 'B'; // Win
	}
	// Paper
	if (e == 'B') {
		if (p == 'X') return 'A'; // Loose
		if (p == 'Y') return 'B'; // Draw
		if (p == 'Z') return 'C'; // Win
	}
	// Scissor
	if (e == 'C') {
		if (p == 'X') return 'B'; // Loose
		if (p == 'Y') return 'C'; // Draw
		if (p == 'Z') return 'A'; // Win
	}

	return '0';
}

int
main(int argc, char **argv)
{
	char *line = NULL;
	FILE *fd;
	size_t len = 0;
	ssize_t read;
	char elve, player = '0', shape;
	int res, score, total;
	enum shape_score ss;
	enum round_score rs;

	if ((fd = fopen("input", "r")) == NULL) {
		printf("Cannot open file\n");
		return 1;
	}

	total = 0;

	while ((read = getline(&line, &len, fd)) != -1) {
		if (read <= 1)
			continue;
		elve = line[0];
		player = line[2];

		shape = get_shape(elve, player);
		printf("Elve plays %s,\tI play %s\t", desc(elve), desc(shape));
		res = play(elve, shape);

		ss = shape - 64;

		score = ss;
		switch (res) {
			case 0: rs = DRAW; score += rs; printf("It's Draw "); break;
			case 1: rs = WON; score += rs; printf("Me wins "); break;
			case 2: rs = LOOSE; score += rs; printf("Elve wins "); break;
			default: printf("Cannot happen "); break;
		}
		printf("\t final score: %d\n", score);
		total += score;
	}
	printf("final score: %d\n", total);

	fclose(fd);

	if (line != NULL)
		free(line);

	return 0;
}
