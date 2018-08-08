#ifndef MODULE_H
#define MODULE_H

#include <node_api.h>   /* n-api */
#include <stdio.h>      /* fprintf */
#include <sys/time.h>   /* gettimeofday, timeval (for timestamp in microseconds) */

#ifdef __cplusplus
extern "C" {
#endif

  long long int uDelta (const char *namespace);

#ifdef __cplusplus
}
#endif

#define NAMESPACE_MAXLENGTH 127

#endif // MODULE_H
