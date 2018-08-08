#include "./module.h"

static struct timeval timer_us;
static long long int ts_us = -1;

long long int uDelta (const char *namespace) {
  long long int now, delta;
  if (ts_us < 0) {
    if (!gettimeofday(&timer_us, NULL)) {
      ts_us = ((long long int) timer_us.tv_sec) * 1000000ll +
               (long long int) timer_us.tv_usec;
    }
    else return -2ll;
  }
  if (!gettimeofday(&timer_us, NULL)) {
    now = ((long long int) timer_us.tv_sec) * 1000000ll +
           (long long int) timer_us.tv_usec;
  }
  else return -3ll;

  delta = now - ts_us; ts_us = now;

  return delta;
}
