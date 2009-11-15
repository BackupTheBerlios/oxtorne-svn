#include "xosm.h"
#include "sqlite3.h"
#include "database.h"


int main (int argc, const char * argv[]) {
	
	if ( argc < 3 )
	{
		printf( "Usage: %s [-v] [map].osm [database].db\n", argv[0] );
		printf( "Use the provided map.db" );
		exit( 1 );
	}

	// Show config
	printf( "Source: %s\n", argv[1] );
	printf( "Target: %s\n", argv[2] );
	
	// Open source file
	osmXmlHandle* handle = osmNewXmlReader( argv[1] );
	
	// open database
	sqlite3* db;
	sqlite3_open( argv[2], &db );
	
	// set sqlite to transaction mode
	db_exec( db, "BEGIN", NULL );
	
	// iterate osm xml file
	while ( osmNextElement( handle ) )
	{
		// Handle the node case
		if ( XML_OSM_TYPE_NODE == handle->type )
		{
			xmlNode_t* node = (xmlNode_t*)handle->element;
			
			db_exec
				( db
				, "insert into nodes values(?, ?, ?);"
				, L"INT", node->id
				, L"DBL", node->lon
            , L"DBL", node->lat
				, NULL );
		}
		
		// handle the way case
		if ( XML_OSM_TYPE_WAY == handle->type ) {
			xmlWay_t* way = (xmlWay_t*)handle->element;
			
			// know the order of waypoints
			size_t wayPointNumber = 0;
			
			// Waypoints
			xmlWayPoint_t* point;
			for ( point = way->points; NULL != point; point = point->next ) {
				db_exec
					( db
					, "insert into ways values(?, ?, ?);"
					, L"INT", way->id
					, L"INT", wayPointNumber++
					, L"INT", point->id
					, NULL );
			}
			
			// don't forget the tags
		}
		
		// other stuff to do here?
	}
	
	// set sqlite to mission accomplished mode
	db_exec( db, "COMMIT", NULL );
	
	// close database
	sqlite3_close( db );
	
	// close xml parser
	osmFreeReader( handle );
}
