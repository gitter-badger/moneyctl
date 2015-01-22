#ifndef __MONEY_CORE_H
#define __MONEY_CORE_H

#define VERSION "0.0.1"

#define TRANS_ADD 0
#define TRANS_SUB 1

typedef struct trons {
	time_t time;
	unsigned int type;
	float count;
} trons_t;

int initCore();

int transaction(unsigned char type, float count);

int showStatics();

#endif //__MONEY_CORE_H
