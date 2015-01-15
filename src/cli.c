#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "lib.h"
#include "core.h"


void help(char *prog_name) {
	printf("Usage: %s [-hvd] [-a count] [-r count] [-s]\n", prog_name);
}

int main(int argc, char *argv[]) {
	char opt;
	unsigned int  add = 0, remove = 0, statics = 0;
	float addCount = 0.f, removeCount = 0.f;
	_debug = 0;
	while((opt = getopt(argc, argv, "hvdsa:r:")) != -1) {
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
		default:
			help(*argv);
			exit(EXIT_FAILURE);
		}
	}
	debug("flags: add(%d, %.3f), remove(%d, %.3f), statics(%d)\n",
			add, addCount, remove, removeCount, statics);
	if(add)
		addMoney(addCount);
	if(remove)
		subMoney(removeCount);
	if(statics)
		showStatics();
	exit(EXIT_SUCCESS);
}
