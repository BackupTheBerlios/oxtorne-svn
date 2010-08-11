#include "stdio.h"
#include "string.h"

int main(int argc, char** argv)
{
   if ( 2 != argc )
   {
      char* exec = strrchr(argv[0], '\\');
      printf("Usage: %s FILE\n", exec ? ++exec : argv[0]);
      return 1;
   }

   return 0;
}
