#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "lib.h"
#include "core.h"


void help(char *prog_name) {
	printf("Usage: %s [-hvd] [-a count] [-r count] [-s] [-b[<since_time>]]\n",
			prog_name);
}

int main(int argc, char *argv[]) {
	char opt;
	unsigned int  add = 0, remove = 0, statics = 0, budget = 0,
		      budgetSince = 0;
	float addCount = 0.F, removeCount = 0.F, budgetCount = 0.F;
	_debug = 0;
	while((opt = getopt(argc, argv, "hvdsa:r:b::")) != -1) {
		switch(opt) {
		case 'h':
			help(*argv);
			exit(EXIT_SUCCESS);
			break;
		case 'v':
			printf("%s v" VERSION "\n", *argv);
			return 0;
			break;
		case 'd':
			_debug = 1;
			break;
		case 'a':
			add = 1;
			addCount = atof(optarg);
			break;
		case 'r':
			remove = 1;
			removeCount = atof(optarg);
			break;
		case 's':
			statics = 1;
			break;
		case 'b':
			budget = 1;
			if (optarg != 0)
				budgetSince = atoi(optarg);
			break;
		default:
			help(*argv);
			exit(EXIT_FAILURE);
		}
	}
	debug("flags: add(%d, %.3f), remove(%d, %.3f), statics(%d), budget(%d, %d)",
			add, addCount, remove, removeCount, statics, budget,
			budgetSince);
	initCore();
	if(add)
		transaction(TRANS_ADD, addCount);
	if(remove)
		transaction(TRANS_SUB, removeCount);
	if(statics)
		showStatics();
	if(budget) {
		struct tm *since = NULL;
		if (budgetSince > 0)
			since = localtime((time_t *)&budgetSince);
		getBudget(&budgetCount, since);
		printf("Your Budget: %.2f\n", budgetCount);
	}
	exit(EXIT_SUCCESS);
}
