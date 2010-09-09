#include "stdio.h"
#include "string.h"
#include "stdlib.h"


typedef struct list {
   wchar_t* word;
   struct list* next;
} list;


int main(int argc, char** argv)
{
   FILE* file = 0;
   wchar_t buffer[2048];
   list *first, *last;
   size_t counter = 0;

   if ( 2 != argc )
   {
      // show some help
      char* exec = strrchr(argv[0], '\\');
      printf("Usage: %s FILE\n", exec ? ++exec : argv[0]);
      return 1;
   }

   // open unicode file
   file = fopen(argv[1], "r,ccs=UNICODE");

   // skip trash of first row
   fgetws(buffer, 2048, file);
   
   // erstes Listenelement anlegen
   first = (list*)malloc(sizeof(list));
   last = first;
   last->next = 0;
   last->word = 0;

   while(fgetws(buffer, 2048, file))
   {
      size_t strSize = (wcslen(buffer)+1) * sizeof(wchar_t);
      last->word = (wchar_t*)malloc(strSize);
      memcpy(last->word, buffer, strSize);

      // Next list item
      last->next = (list*)malloc(sizeof(list));
      last = last->next;
      last->next = 0;
      last->word = 0;

      ++counter;
   }

   printf("Lines: %i\n", counter);
   fclose(file);
   system("PAUSE");

   // done
   return 0;
}
