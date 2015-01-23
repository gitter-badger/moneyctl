#include <stdarg.h>
#include <stdio.h>
#include "lib.h"

#ifndef DEBUG
void debug(const char *fmt, ...) {

	if(_debug) {
		va_list args;
		va_start(args, fmt);
		fputs("[DEBUG] ", stderr);
		vfprintf(stderr, fmt, args);
		fputc('\n', stderr);
		va_end(args);
	}
}
#endif
