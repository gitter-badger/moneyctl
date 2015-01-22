#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/stat.h>

#include "lib.h"
#include "core.h"

#define DATA_DIR  "/moneyctl/"
#define DATA_FILE "data.db"

FILE *data_f;
FILE *loadData(char *);
/*
 * init the Core, It should init the core struct on the future
 * return 0 on success
 */
int initCore()
{
	data_f = loadData(DATA_FILE);

	return 0;
}

/*
 * add Money to the main budget
 * parm count: added money count
 * return 0 on success
 */
int addMoney(float count)
{
	return 0;
}

/*
 * sub Money from the main budget
 * parm count: subed money count
 * return 0 on success
 */
int subMoney(float count)
{
	return 0;
}

/*
 * money transaction
 * parm type: type of transaction
 * parm count: subed money count
 * return 0 on success
 */
int transaction(unsigned char type, float count)
{
	return 0;
}

FILE* loadData(char *file_name) {
	char data_path[250];
	struct stat st = {0};
	if(getenv("XDG_DATA_HOME")) {
		// get 200 max char, 50 for the rest
		strncpy(data_path, getenv("XDG_DATA_HOME"),
			ARR_NEL(data_path, DATA_DIR) + strlen(file_name));
	} else {
		strncpy(data_path, getenv("HOME"),
			ARR_NEL(data_path, DATA_DIR) + strlen(file_name) - 13);
		strcat(data_path, "/.local/share");
	}
	strcat(data_path, DATA_DIR);
	//check if dir exits or make it
	if(stat(data_path, &st) != 0) {
		mkdir(data_path, 0700);
	}
	strcat(data_path, file_name);
	debug("loadData(%s) => %s\n", file_name, data_path);
	return fopen(data_path, "a+");
}

trons_t *generateTrons() {
}

/*
 * show the statics, it should accept a pointer to an struct to set it values on
 * the future
 * return 0 on success
 */
int showStatics()
{
	return 0;
}

