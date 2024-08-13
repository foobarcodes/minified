
#ifndef MOCK_SYMS_H
#define MOCK_SYMS_H

#include <sys/time.h>
#include <time.h>

#ifdef __cplusplus
extern "C" {
#endif

int gettimeofday(struct timeval *tv, struct timezone *tz);
time_t timegm(struct tm *tm);
int access(const char *pathname, int mode);

#ifdef __cplusplus
}
#endif

#endif // DUMMY_FUNCTIONS_H
