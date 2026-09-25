#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/procinfo.h"
#include "user/user.h"

char *
state_name(int state)
{
  switch(state){
    case 0: return "UNUSED";
    case 1: return "USED";
    case 2: return "SLEEPING";
    case 3: return "RUNNABLE";
    case 4: return "RUNNING";
    case 5: return "ZOMBIE";
    default: return "UNKNOWN";
  }
}

int
main(void)
{
  struct procinfo info[64];
  int count;

  count = getprocsinfo(info, 64);

  if(count < 0){
    printf("getprocsinfo failed\n");
    exit(1);
  }

  printf("PID\tPPID\tSTATE\t\tCPU TICKS\tSIZE\tNAME\n");

  for(int i = 0; i < count; i++){
    printf("%d\t%d\t%s\t%d\t%d\t%s\n",
           info[i].pid,
           info[i].ppid,
           state_name(info[i].state),
           (int)info[i].cpu_ticks,
           (int)info[i].sz,
           info[i].name);
  }

  printf("\nTotal processes: %d\n", count);

  exit(0);
}
