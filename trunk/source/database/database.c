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

#include "database.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"

size_t wcslen( const wchar_t* string )
{
	size_t len = 0;
	for ( ; L'\0' != string[len]; ++len );
	return len;
}


int db_exec( sqlite3* db, const char* query, ... )
{
	// SQliteStatement
   sqlite3_stmt* pStmt;
	
   // prepare the prepared query
   int rc = sqlite3_prepare( db, query, -1, &pStmt, NULL );
	
	// check for errors
	if ( SQLITE_ERROR == rc )
	{
		// prompt an error
		printf( "Execution failed with error:\n%s\n", sqlite3_errmsg( db ) );
		
		if ( NULL != pStmt )
		{
			// Statement in memory?
			sqlite3_free( pStmt );
		}
		
		// return an error
		return SQLITE_ERROR;
	}
	
	// good, no errors. continue with the variable argument list ...
	va_list vl;
	va_start(vl, query);
	
	// counting the current binding position
	size_t index = 0;
	
	// we will check abort criteria inside of loop
	while ( 1 )
	{
		// The string identifies the following type
		wchar_t* hint = va_arg( vl, wchar_t* );
		
		// finding null ends the loop
		if ( NULL == hint )
			break;
		
		// And now compare ...
		if ( 0 == memcmp( hint, L"INT", sizeof( wchar_t ) * 3 ) )
		{
			// read and bind an integer
			int next = va_arg( vl, int );
			sqlite3_bind_int( pStmt, ++index, next );
			
			// skip the rest of the loop
			continue;
		}
		
		// Could it be that we received a text?
		if ( 0 == memcmp( hint, L"TXT", sizeof( wchar_t ) * 3 ) )
		{
			// read and bind a string
			wchar_t* next = va_arg( vl, wchar_t* );
			
			// Bind without freeing the given string
			sqlite3_bind_text16( pStmt, ++index, next, wcslen( next ), NULL );
			
			// skip the rest of the loop again
			continue;
		}
		
		// Could it be we received a double value?
		if ( 0 == memcmp( hint, L"DBL", sizeof( wchar_t ) * 3 ) )
		{
			// read and bind an integer
			double next = va_arg( vl, double );
			sqlite3_bind_double( pStmt, ++index, next );
			
			// skip the rest of the loop
			continue;
		}
	}
	
	// va_list completed
	va_end(vl);
	
	// start iterating with the prepared query
	while( SQLITE_ROW == sqlite3_step( pStmt ) )
	{
		// TODO: read return values
	}
		
	// Error handling
	if ( SQLITE_DONE != sqlite3_errcode( db ) )
	{
		printf( "Execution failed:\n%s\n%s\n", sqlite3_errmsg( db ), query );
	}
		
	return SQLITE_OK;
}
