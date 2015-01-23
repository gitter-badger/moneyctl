#include <time.h>

#ifndef __MONEY_CORE_H
#define __MONEY_CORE_H

#define VERSION "0.0.1"

#define TRANS_ADD 0
#define TRANS_SUB 1
//#define TIME_FMT "%Y/%m/%d-%H:%M:%S"
#define TIME_FMT "%s"

typedef struct trans {
	struct tm tm;
	unsigned int type;
	float count;
} trans_t;

int initCore();

int transaction(unsigned char type, float count);

int showStatics();

int getBudget(float *count, struct tm *since);

#endif //__MONEY_CORE_H
