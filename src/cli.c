#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "lib.h"
#include "core.h"


void help(char *prog_name) {
	printf(	"Usage: %s [-hvd] [-a count] [-r count] [-s] [-b<since_time>]\n"
		"Options:\n"
		"    -a count	: add the value count to budge\n"
		"    -r count	: sub the value count from budget\n"
		"    -s		: show statics\n"
		"    -b[since]	: show all budget or starting from since\n"
		"		  since is Epoch time or [float]{h,d,w,m,y}\n"
		"    -h		: help message\n"
		"    -v		: version\n"
		"    -d		: output debug messages\n"
		, prog_name);
}

struct tm *getSince(const char *since) {
	size_t len;
	time_t t;
	float plus;
	len = strlen(since);
	// should add 1 if jsut -b{h,d,w,m,y}
	plus = len > 1 ? 0.F : 1.F;
	time(&t);
	switch (since[len - 1]) {
	case 'h':
	case 'H':
			t -= (time_t)((atof(since) + plus) * 3600);
			break;
	case 'd':
	case 'D':
			t -= (time_t)((atof(since) + plus) * 86400);
			break;
	case 'w':
	case 'W':
			t -= (time_t)((atof(since) + plus) * 604800);
			break;
	case 'm':
	case 'M':
			t -= (time_t)((atof(since) + plus) * 18144000);
			break;
	case 'y':
	case 'Y':
			t -= (time_t)((atof(since) + plus) * 6622560000);
			break;
	default:
			t = (time_t)atoi(since);
	}
	return localtime(&t);
}

int main(int argc, char *argv[]) {
	char opt, *budgetSince = NULL;
	unsigned int  add = 0, remove = 0, statics = 0, budget = 0;
	float addCount = 0.F, removeCount = 0.F, budgetCount = 0.F;
	_debug = 0;
	if (argc == 1) {
		help(*argv);
		exit(EXIT_SUCCESS);
	}
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
				budgetSince = optarg;
			break;
		default:
			help(*argv);
			exit(EXIT_FAILURE);
		}
	}
	debug("flags: add(%d, %.3f), remove(%d, %.3f), statics(%d), budget(%d, %s)",
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
		if (budgetSince)
			since = getSince(budgetSince);
		getBudget(&budgetCount, since);
		printf("Your Budget: %.2f\n", budgetCount);
	}
	exit(EXIT_SUCCESS);
}
