#include "task.h"

#include <stdlib.h>
#include <stdio.h>


bool funChaos(const char*, char* args[])
{
   for(size_t ii = 0; args[ii]; ++ii)
      printf("Arg is %s\n", args[ii]);

   return true;
}

TASK_STRUCT(Chaos, "Will do some major chaos to your pc. no arguments.")
