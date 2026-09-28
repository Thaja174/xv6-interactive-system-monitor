#include "kernel/types.h"
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

void
display_dashboard(void)
{
  struct procinfo info[64];
  int count;

  count = getprocsinfo(info, 64);

  if(count < 0){
    printf("getprocsinfo failed\n");
    return;
  }

  printf("\n");
  printf("===============================================\n");
  printf("          XV6 INTERACTIVE MONITOR              \n");
  printf("===============================================\n");

  printf("PID   PPID   STATE       CPU TICKS   SIZE   NAME\n");
  printf("-----------------------------------------------\n");

  for(int i = 0; i < count; i++){
    printf("%d     %d     %s     %d        %d   %s\n",
           info[i].pid,
           info[i].ppid,
           state_name(info[i].state),
           (int)info[i].cpu_ticks,
           (int)info[i].sz,
           info[i].name);
  }

  printf("-----------------------------------------------\n");
  printf("Total processes: %d\n", count);
  printf("===============================================\n");
}

int
main(void)
{

  display_dashboard();

  exit(0);
}

