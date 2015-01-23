#ifndef __MONEY_LIB_H
#define __MONEY_LIB_H

// force debug mode on release build
unsigned int _debug;

#define ARR_LEN(s)        (sizeof(s)/sizeof(s[0]))
// return the rest of r1 len - r2 len
#define ARR_NEL(r1, r2)   (ARR_LEN(r1) - ARR_LEN(r2))

#ifdef DEBUG
#define debug(format, args...) fprintf (stderr, "[DEBUG] " format "\n", args)
#else
void debug(const char *fmt, ...);
#endif //DEBUG

#endif //__MONEY_LIB_H
