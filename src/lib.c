#include <stdarg.h>
#include <stdio.h>
#include "lib.h"

#ifndef DEBUG
void debug(const char *fmt, ...) {

	if(_debug) {
		va_list args;
		va_start(args, fmt);
		vfprintf(stderr, fmt, args);
		va_end(args);
	}
}
#endif

