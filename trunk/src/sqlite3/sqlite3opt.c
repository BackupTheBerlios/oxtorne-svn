/*
 * Copyright (c) 2008 Markus Friese. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE
 * USE OF THIS SOFTWARE EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "sqlite3/sqlite3opt.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"

int opt_prepare( sqlite3* db, sqlite3_stmt** pStmt, const char* query, ... )
{
   // SQliteStatement
   va_list vl;
   size_t index;
   int ii, rc;
	
   // platz,um den string zu kopieren
   char* buffer = (char*) malloc( (strlen(query) + 1) * sizeof(char) );
   memcpy( buffer, query, strlen(query) + 1 );

   if ( !pStmt )
   {
      // Buffer wird wohl nicht mehr benotigt
      free( buffer );

      // Einen Fehler melden
      return SQLITE_ERROR;
   }

   // build a sqlite query
   for ( ii = 0; buffer[ii] != '\0'; ++ii )
   {
      // % symbol check
      if ( buffer[ii] == '%' && buffer[ii + 1] == '%' )
      {
         buffer[ii + 1] = ' ';
         continue;
      }

      // question mark replacement
      if ( buffer[ii] == '%' )
      {
         buffer[ii] = '?';
         buffer[ii + 1] = ' ';
      }
   }

   // prepare the prepared query
   rc = sqlite3_prepare( db, buffer, -1, pStmt, NULL );
	
	// check for errors
	if ( SQLITE_ERROR == rc )
	{
		// prompt an error
		printf( "Execution failed with error:\n%s\n", sqlite3_errmsg( db ) );
      free( buffer );
		
		if ( NULL != *pStmt )
		{
			// Statement in memory?
			sqlite3_free( *pStmt );
		}
		
		// return an error
		return SQLITE_ERROR;
	}
	
	// good, no errors. continue with the variable argument list ...
	va_start(vl, query);
	
	// counting the current binding position
	index = 0;
	
	// we will check abort criteria inside of loop
	for ( ii = 0; query[ii] != '\0'; ++ii )
	{
		// % symbol check
      if ( query[ii] == '%' && query[ii + 1] == '%' )
      {
         // skip the next %
         ++ii;
         continue;
      }

      // Integer Check
      if ( query[ii] == '%' && query[ii + 1] == 'i' )
      {
			// next argument is of type int
         sqlite3_bind_int( *pStmt, ++index, va_arg( vl, int ) );
         continue;
      }

      // String check
      if ( query[ii] == '%' && query[ii + 1] == 's' )
      {
         // sqlite will not free the string
         sqlite3_bind_text( *pStmt, ++index, va_arg( vl, char* ), -1, NULL );
         continue;
      }

      // Wide Character String check
      if ( query[ii] == '%' && query[ii + 1] == 'w' )
      {
			// sqlite will not free the string
         sqlite3_bind_text16( *pStmt, ++index, va_arg( vl, wchar_t* ), -1, NULL );
         continue;
      }

      // Float check
      if ( query[ii] == '%' && query[ii + 1] == 'f' )
      {
         sqlite3_bind_double( *pStmt, ++index, (double)va_arg( vl, float ) );
         continue;
      }

      // Double check
      if ( query[ii] == '%' && query[ii + 1] == 'F' )
      {
         sqlite3_bind_double( *pStmt, ++index, va_arg( vl, double ) );
         continue;
      }

      if ( query[ii] == '%' && query[ii + 1] != '\0' )
      {
         fprintf( stderr, "%c%c Combination is unknown\n", query[ii], query[ii + 1] );
      }
	}
	
	// va_list completed
	va_end(vl);

   // free the buffer
   free( buffer );

   // all done, all fine
   return SQLITE_OK;
}
