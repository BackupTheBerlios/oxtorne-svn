#include "stdio.h"
#include "string.h"
#include "sqlite3/sqlite3.h"
#include "sqlite3/sqlite3opt.h"


int main(int argc, char** argv)
{
   FILE* file = 0;
   wchar_t buffer[2048];
   sqlite3* db;
   sqlite3_stmt* pStmt;
   
   if ( 3 != argc )
   {
      // show some help
      char* exec = strrchr(argv[0], '\\');
      printf("Usage: %s DB FILE\n", exec ? ++exec : argv[0]);
      return 1;
   }

   // open unicode file
   file = fopen(argv[2], "r,ccs=UNICODE");

   // Prepare Database
   sqlite3_open(argv[1], &db);
   sqlite3_exec(db, "create table map(key, value);", NULL, NULL, NULL);

   // skip trash of first row
   fgetws(buffer, 2048, file);

   // prepared query
   sqlite3_exec(db, "begin;", NULL, NULL, NULL);
   sqlite3_prepare(db, "insert into map values(?,?)", -1, &pStmt, NULL);
   
   while(fgetws(buffer, 2048, file))
   {
      // Cut String at '=' symbol
      wchar_t* loc = wcschr(buffer, L'=');
      *loc = L'\0';
      ++loc;

      // Remove linebreak
      loc[wcslen(loc)-1] = L'\0';

      // attach values
      sqlite3_bind_text16(pStmt, 1, buffer, -1, NULL);
      sqlite3_bind_text16(pStmt, 2, loc, -1, NULL);
      sqlite3_step(pStmt);
      sqlite3_reset(pStmt);
   }

   // cleanup query
   sqlite3_finalize(pStmt);

   // cleanup database
   sqlite3_exec(db, "commit;", NULL, NULL, NULL);
   sqlite3_close(db);

   // done
   return 0;
}
