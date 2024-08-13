
#include "mocksyms.h"
#include <taskLib.h>
#include <ioLib.h>
#include <errno.h>

int gettimeofday(struct timeval *tv, struct timezone *tz) {
    if (tv) {
        struct timespec ts;
        clock_gettime(CLOCK_REALTIME, &ts);  // Get the current time
        tv->tv_sec = ts.tv_sec;
        tv->tv_usec = ts.tv_nsec / 1000;  // Convert nanoseconds to microseconds
    }
    // VxWorks does not support timezone info, so tz can be ignored or set to zero.
    if (tz) {
        tz->tz_minuteswest = 0;
        tz->tz_dsttime = 0;
    }
    return 0;
}

time_t timegm(struct tm *tm) {
    // Save and temporarily set the TZ environment variable to UTC
    char *tz = getenv("TZ");
    setenv("TZ", "", 1);
    tzset();

    time_t ret = mktime(tm);  // Use mktime, which assumes local time

    // Restore the original TZ environment variable
    if (tz)
        setenv("TZ", tz, 1);
    else
        unsetenv("TZ");
    tzset();

    return ret;
}

int access(const char *pathname, int mode) {
    // Use open with the desired mode to check accessibility
    int fd = open(pathname, O_RDONLY);
    if (fd < 0) {
        // If open failed, return -1
        return -1;
    }
    close(fd);
    return 0;
}
