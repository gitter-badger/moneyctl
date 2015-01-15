#ifndef __MONEY_LIB_H
#define __MONEY_LIB_H

// force debug mode on release build
unsigned int _debug;

#ifdef DEBUG
#define debug(format, args...) fprintf (stderr, format, args)
#else
void debug(const char *fmt, ...);
#endif //DEBUG

#endif //__MONEY_LIB_H
