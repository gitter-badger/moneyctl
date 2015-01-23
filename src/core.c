#define  _XOPEN_SOURCE 700
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <sys/stat.h>
#include <glib-2.0/glib.h>

#include "lib.h"
#include "core.h"

#define GTRANS(it) ((trans_t *)it->data)
#define DATA_DIR  "/moneyctl/"
#define DATA_FILE "data.db"

FILE *data_f;
GList *trans_l;

FILE *loadData(char *);
trans_t *trans_alloc(struct tm time, unsigned int type, float count);
GList *generateTrans();

/*
 * init the Core, It should init the core struct on the future
 * return 0 on success
 */
int initCore()
{
	data_f = loadData(DATA_FILE);
	trans_l = generateTrans();

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
	struct tm *tm;
	time_t rawtime;
	char tm_s[12], type_c;
	trans_t *trans;
	time(&rawtime);
	tm = gmtime(&rawtime);
	trans = trans_alloc(*tm, type, count);
	trans_l = g_list_append(trans_l, trans);
	fseek(data_f, 0L, SEEK_END);
	strftime(tm_s, 11, TIME_FMT, tm);
	if(type == TRANS_ADD)
		type_c = '+';
	else if(type == TRANS_SUB)
		type_c = '-';
	else
		return 1;
	fprintf(data_f, "%s %c %f\n", tm_s, type_c, count);
	fflush(data_f);
	return 0;
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

/*
 * Return budget since time or all if since is NULL
 * parm *count: float where to store budget
 * parm *since: date from where to start counting or NULL for all
 * return 0 on success
 */
int getBudget(float *count, struct tm *since) {
	debug("getBudget");
	GList *l;
	time_t t;
	l = trans_l;
	if(since) {
		t = mktime(since);
		while(l != NULL && mktime(&GTRANS(l)->tm) < t) {
			l = l->next;
		}
	}
	*count = 0.F;
	for (; l != NULL;  l = l->next) {
		trans_t *trs = GTRANS(l);
		if(trs == NULL) {
			debug("GList Data NULL!");
			continue;
		}
		if(trs->type == TRANS_ADD)
			*count += trs->count;
		else
			*count -= trs->count;
	}
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
	debug("loadData(%s) => %s", file_name, data_path);
	return fopen(data_path, "a+");
}

GList *generateTrans() {
	GList *list = NULL;
	trans_t *trans;
	struct tm tm;
	char type_c, tm_s[12];
	float count;
	unsigned int type;

	// TODO: g_list_append is slow
	while(fscanf(data_f, "%11s %c %f", tm_s, &type_c, &count) != EOF) {
		memset(&tm, 0, sizeof(tm));
		strptime(tm_s, TIME_FMT, &tm);
		switch(type_c) {
			case '+':
				type = TRANS_ADD;
				break;
			case '-':
				type = TRANS_SUB;
				break;
			default:
				debug("Wrong transaction type: %c! pass",
						type_c);
				continue;
		}
		if(count < 0) {
			debug("Wrong transaction count: %d", count);
			continue;
		}
		trans = trans_alloc(tm, type, count);
		list = g_list_append(list, trans);
	}

	return list;
}

trans_t *trans_alloc(struct tm tm, unsigned int type, float count) {
	trans_t *trans = (trans_t *)malloc(sizeof(trans_t));
	trans->tm = tm;
	trans->type = type;
	trans->count = count;
	return trans;
}
