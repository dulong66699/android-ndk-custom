/* _ctypes is linked into the static python on bionic, where libdl.a is a
 * stub anyway (and in r28/r28-beta3 an LLVM bitcode archive lld cannot read).
 * A static executable cannot load libraries, so answer every call with
 * failure, which ctypes reports as OSError. Weak, so libc.a wins where it
 * has them. */
#include <stddef.h>

static const char dl_static_msg[] = "dynamic loading is not available in a static executable";
static int dl_static_err;

__attribute__((weak)) void *dlopen(const char *file, int mode) { (void)file; (void)mode; dl_static_err = 1; return NULL; }
__attribute__((weak)) void *dlsym(void *handle, const char *name) { (void)handle; (void)name; dl_static_err = 1; return NULL; }
__attribute__((weak)) int dlclose(void *handle) { (void)handle; return 0; }
__attribute__((weak)) char *dlerror(void) {
  if (!dl_static_err) return NULL;
  dl_static_err = 0;
  return (char *)dl_static_msg;
}
