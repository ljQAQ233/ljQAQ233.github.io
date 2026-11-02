// print argc, argv, envp, auxv respectively
// compile with textos's sdk with attached libc cc:
// textos/build/app/libc/cc vecs.c -static -o vecs
#include <elf.h>
#include <stdint.h>
#include <stdio.h>

// clang-format off

#define AT_LIST           \
  X(AT_NULL)              \
  X(AT_IGNORE)            \
  X(AT_EXECFD)            \
  X(AT_PHDR)              \
  X(AT_PHENT)             \
  X(AT_PHNUM)             \
  X(AT_PAGESZ)            \
  X(AT_BASE)              \
  X(AT_FLAGS)             \
  X(AT_ENTRY)             \
  X(AT_NOTELF)            \
  X(AT_UID)               \
  X(AT_EUID)              \
  X(AT_GID)               \
  X(AT_EGID)              \
  X(AT_PLATFORM)          \
  X(AT_HWCAP)             \
  X(AT_CLKTCK)            \
  X(AT_SECURE)            \
  X(AT_BASE_PLATFORM)     \
  X(AT_RANDOM)            \
  X(AT_HWCAP2)            \
  X(AT_EXECFN)            \
  X(AT_SYSINFO_EHDR)      \
  X(AT_L1I_CACHESHAPE)    \
  X(AT_L1D_CACHESHAPE)    \
  X(AT_L2_CACHESHAPE)     \
  X(AT_L3_CACHESHAPE)     \
  X(AT_L1I_CACHESIZE)     \
  X(AT_L1I_CACHEGEOMETRY) \
  X(AT_L1D_CACHESIZE)     \
  X(AT_L1D_CACHEGEOMETRY) \
  X(AT_L2_CACHESIZE)      \
  X(AT_L2_CACHEGEOMETRY)  \
  X(AT_L3_CACHESIZE)      \
  X(AT_L3_CACHEGEOMETRY)  \
  X(AT_MINSIGSTKSZ)

// clang-format on

#define X(name) [name] = #name,
static char *at_names[] = {AT_LIST};
#undef X

typedef struct {
  uintptr_t t, v;
} auxv_t;

void dump_auxv(auxv_t *a) {
  char *t = at_names[a->t];
  if (!t)
    t = "UNKNOWN";
  printf("%-20s: ", t);
  switch (a->t) {
  case AT_EXECFN:
  case AT_PLATFORM:
    printf("%s", (char *)a->v);
    break;
  default:
    printf("%lx", a->v);
  }
  printf("\n");
}

extern char **environ;

int main(int argc, char *argv[]) {
  printf("argc = %d\n", argc);
  for (int i = 0; i < argc; i++) {
    printf("argv[%d] = %s\n", i, argv[i]);
  }
  char **env = environ;
  for (int i = 0; *env; i++, env++) {
    printf("envp[%d] = %s\n", i, *env);
  }
  auxv_t *p = (void *)(env + 1);
  for (; p->t != AT_NULL; p++)
    dump_auxv(p);
  return 0;
}
