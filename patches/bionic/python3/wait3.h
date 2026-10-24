/* wait3 -- not declared by older NDK headers (r21 i686); wait4 has always been there. */
#ifndef NDK_BIONIC_WAIT3_H
#define NDK_BIONIC_WAIT3_H

#include <sys/resource.h>
#include <sys/types.h>
#include <sys/wait.h>

static inline pid_t ndk_wait3(int *status, int options, struct rusage *ru) {
  return wait4(-1, status, options, ru);
}
#define wait3 ndk_wait3

#endif
