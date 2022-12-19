#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STACKS 9
#define MAX_ELEMENTS 255

int stack[MAX_STACKS][MAX_ELEMENTS];
int top[MAX_STACKS];

int
char2ascii(const char letter)
{
	return letter;
}

void
init()
{
	for (int i=0; i < MAX_STACKS; i++) {
		for (int j=0; j < MAX_ELEMENTS; j++) {
			stack[i][j] = -1;
		}
		top[i] = -1;
	}
}

int
isempty(int no)
{
	if (no > MAX_STACKS)
		return -1;

	if (top[no] == -1)
		return 1;

	return 0;
}

void
show_stack()
{
	for (int i=0; i < MAX_STACKS; i++) {
		if (isempty(i)) {
			printf("%d: empty\n", i+1);
			continue;
		}
		printf("%d: ", i+1);
		for (int j=0; j < MAX_ELEMENTS; j++) {
			if (stack[i][j] == -1) {
				printf("\n");
				break;
			}
			else
			 	printf("[%c]", stack[i][j]);
		}
	}
}

int
isfull(int stack_no)
{
	if (stack_no > MAX_STACKS) {
		printf("Too many stacks\n");
		return -1;
	}

	if (top[stack_no] < MAX_ELEMENTS)
		return 0;

	return 1;
}

void
push(int stack_no, int item)
{
	if (stack_no > MAX_STACKS) {
		printf("Too many stacks\n");
		return;
	}

	if (isfull(stack_no)) {
		printf("Stack %d is full\n", stack_no);
		return;
	}

	top[stack_no]++;

	stack[stack_no][top[stack_no]] = item;
}

int
pop(int stack_no)
{
	int ret = -255;

	if (stack_no > MAX_STACKS) {
		printf("Too many stacks\n");
		return ret;
	}

	if (isempty(stack_no)) {
		printf("Stack %d is empty\n", stack_no);
		exit(1);
		return ret;
	}

	ret = stack[stack_no][top[stack_no]];
	stack[stack_no][top[stack_no]] = -1;
	top[stack_no]--;

	return ret;
}

void
init_day6()
{
	// *************************************************************************
	// XXX I was lazy and hard-coded the puzzle and removed it from the final
	// XXX input
	// *************************************************************************
	push(0, char2ascii('R'));
	push(0, char2ascii('N'));
	push(0, char2ascii('F'));
	push(0, char2ascii('V'));
	push(0, char2ascii('L'));
	push(0, char2ascii('J'));
	push(0, char2ascii('S'));
	push(0, char2ascii('M'));

	push(1, char2ascii('P'));
	push(1, char2ascii('N'));
	push(1, char2ascii('D'));
	push(1, char2ascii('Z'));
	push(1, char2ascii('F'));
	push(1, char2ascii('J'));
	push(1, char2ascii('W'));
	push(1, char2ascii('H'));

	push(2, char2ascii('W'));
	push(2, char2ascii('R'));
	push(2, char2ascii('C'));
	push(2, char2ascii('D'));
	push(2, char2ascii('G'));

	push(3, char2ascii('N'));
	push(3, char2ascii('B'));
	push(3, char2ascii('S'));

	push(4, char2ascii('M'));
	push(4, char2ascii('Z'));
	push(4, char2ascii('W'));
	push(4, char2ascii('P'));
	push(4, char2ascii('C'));
	push(4, char2ascii('B'));
	push(4, char2ascii('F'));
	push(4, char2ascii('N'));

	push(5, char2ascii('P'));
	push(5, char2ascii('R'));
	push(5, char2ascii('M'));
	push(5, char2ascii('W'));

	push(6, char2ascii('R'));
	push(6, char2ascii('T'));
	push(6, char2ascii('N'));
	push(6, char2ascii('G'));
	push(6, char2ascii('L'));
	push(6, char2ascii('S'));
	push(6, char2ascii('W'));

	push(7, char2ascii('Q'));
	push(7, char2ascii('T'));
	push(7, char2ascii('H'));
	push(7, char2ascii('F'));
	push(7, char2ascii('N'));
	push(7, char2ascii('B'));
	push(7, char2ascii('V'));

	push(8, char2ascii('L'));
	push(8, char2ascii('M'));
	push(8, char2ascii('H'));
	push(8, char2ascii('Z'));
	push(8, char2ascii('N'));
	push(8, char2ascii('F'));
}


// XXX I converted the input file to the following format
// a b c
// cut -d ' ' -f 2,4,6 input.orig > input
void
parse_line(char *line, int *amount, int *from, int *to)
{
	char *token;
	int c = 0;

	while ((token = strsep(&line, " ")) != NULL) {
		if (c == 0)
			*amount = atoi(token);
		else if (c == 1)
			*from = atoi(token);
		else if (c == 2)
			*to = atoi(token);
		c++;
	}
}

int
top_of_stack(int stack_no)
{
	if (stack_no > MAX_STACKS) {
		printf("Too many stacks\n");
		return -255;
	}

	if (isempty(stack_no)) {
		printf("Stack %d is empty\n", stack_no);
		exit(1);
		return -255;
	}

	return stack[stack_no][top[stack_no]];
}

int
main(int argc, char **argv)
{
	char *line = NULL;
	FILE *fd;
	size_t len = 0;
	ssize_t read;
	int amount, from, to, temp, round;

	amount = from = to = round = 0;

	init();
	init_day6();

	if ((fd = fopen("input", "r")) == NULL) {
		printf("Cannot open file\n");
		return 1;
	}

	while ((read = getline(&line, &len, fd)) != -1) {
		if (read <= 1)
			continue;

		amount = from = to = 0;
		parse_line(line, &amount, &from, &to);
		//printf("(%d) Move %d from %d to %d\n", round, amount, from, to);

		for (int i=0; i < amount; i++) {
			temp = pop(from-1);
			push(to-1, temp);
		}
		//show_stack();
		round++;
	}

	for (int i=0; i < MAX_STACKS; i++) {
		printf("%c", top_of_stack(i));
	}
	printf("\n");

	fclose(fd);

	if (line != NULL)
		free(line);

	return 0;
}
