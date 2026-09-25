#ifndef _PROCINFO_H_
#define _PROCINFO_H_

#include "types.h"

#define PROCINFO_NAME_LEN 16

struct procinfo {
  int pid;
  int ppid;
  int state;
  uint64 cpu_ticks;
  uint64 sz;
  char name[PROCINFO_NAME_LEN];
};

#endif
