#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#include "problems.h"

bool validate(unsigned char (*grid)[9][9]);
void solve(unsigned char (*problem)[9][9]);

static void print_grid(unsigned char (*problem)[9][9])
{
	printf("-------------------------\n");
	for(int i = 0; i < 9; ++i) {
		printf("| ");
		for(int j = 0; j < 9; ++j) {
			printf("%d %s", (*problem)[i][j], j % 3 == 2 ? "| " : "");
		}
		printf("\n");
		if(i % 3 == 2)
			printf("-------------------------\n");
	}
}

int main(int argc, char **argv)
{
	unsigned char (*problem)[9][9];
	int no;

	if(argc != 2)
		return -1;

	no = atoi(argv[1]);
	if(no < 1 || no > 4)
		return -1;
	problem = problems[no];

	solve(problem);
	print_grid(problem);
	return !validate(problem);
}
