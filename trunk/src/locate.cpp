#include <GetPot>
#include <stdio.h>
#include <stdlib.h>


// don't use headers.
extern bool eval(const char *key, char *args[]);
extern void list();

int main(int argc, char *argv[])
{
   if (2 > argc)
   {
      printf("usage: exec.exe function (arg[0-9]+ )* \n");
      printf("available functions are:\n");
      list();
      printf("exit.");
      return 1;
   }

   // enough space to create a zero terminated array
   char** rest = (char**)alloca(sizeof(char*) * (argc-1));

   // Get each argument
   for(int ii = 2; ii < argc; ++ii)
      rest[ii-2] = argv[ii];

   // terminate
   rest[argc-2] = 0;

   // Starte die Auswertung
   eval(argv[1], rest);

   return 0;
}
