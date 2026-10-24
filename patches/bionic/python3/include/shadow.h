/* shadow.h -- bionic has none, and Android has no shadow password database. */
#ifndef NDK_BIONIC_SHADOW_H
#define NDK_BIONIC_SHADOW_H

#include <errno.h>
#include <stddef.h>

struct spwd {
  char *sp_namp;
  char *sp_pwdp;
  long sp_lstchg;
  long sp_min;
  long sp_max;
  long sp_warn;
  long sp_inact;
  long sp_expire;
  unsigned long sp_flag;
};

static inline struct spwd *getspnam(const char *name) { (void)name; errno = 0; return NULL; }
static inline struct spwd *getspent(void) { return NULL; }
static inline void setspent(void) {}
static inline void endspent(void) {}

#endif
