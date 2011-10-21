#ifndef __FUNCTIONAL_RECURSION__
#define __FUNCTIONAL_RECURSION__
#include "task.h"

#include <string.h>
#include <stdio.h>

#undef TASK // first recursion
#define TASK(NAME) extern Task TASK_NAME(NAME);
#include "functional.cpp"

#undef TASK // second recursion
#define TASK(NAME) &TASK_NAME(NAME),
const struct Task* g_tasks[] =
{
#include "functional.cpp"
	0
};

bool eval(const char* key, char* args[])
{
   for(size_t ii = 0; g_tasks[ii]; ++ii)
      if (!strcmp(g_tasks[ii]->name, key))
         return g_tasks[ii]->func(key, args);
   
   return false;
}

void list()
{
   for(size_t ii = 0; g_tasks[ii]; ++ii)
      printf(" - %s\n   %s\n", g_tasks[ii]->name, g_tasks[ii]->desc);
}

#else // __FUNCTIONAL_RECURSION__
TASK(Chaos)
#endif // __FUNCTIONAL_RECURSION__
