/* posix_shm.h -- shm_open/shm_unlink, never in bionic. Android has no
 * /dev/shm, so back them with files under $TMPDIR (else /data/local/tmp). */
#ifndef NDK_BIONIC_POSIX_SHM_H
#define NDK_BIONIC_POSIX_SHM_H

#include <errno.h>
#include <fcntl.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

static inline int ndk_shm_path(const char *name, char *buf, size_t len) {
  const char *dir = getenv("TMPDIR");
  if (!dir || !*dir) dir = "/data/local/tmp";
  while (*name == '/') name++;
  if (!*name || strchr(name, '/')) { errno = EINVAL; return -1; }
  if ((size_t)snprintf(buf, len, "%s/%s", dir, name) >= len) { errno = ENAMETOOLONG; return -1; }
  return 0;
}

static inline int shm_open(const char *name, int oflag, mode_t mode) {
  char path[PATH_MAX];
  if (ndk_shm_path(name, path, sizeof path) < 0) return -1;
  return open(path, oflag | O_CLOEXEC | O_NOFOLLOW, mode);
}

static inline int shm_unlink(const char *name) {
  char path[PATH_MAX];
  if (ndk_shm_path(name, path, sizeof path) < 0) return -1;
  return unlink(path);
}

#endif
