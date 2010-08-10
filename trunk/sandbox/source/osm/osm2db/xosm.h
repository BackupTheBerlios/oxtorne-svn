/*
 *  xmlOsmReader.h
 *  XmlTest
 *
 *  Created by Markus F on 26.04.09.
 *  Copyright 2009 Markus F. All rights reserved.
 *
 */

#include <libxml/xmlreader.h>


/**
 * xmlOsmTypes:
 *
 * Identifies an item by a constant type
 */
typedef enum {
    XML_OSM_TYPE_NONE = 0,
    XML_OSM_TYPE_NODE = 1,
    XML_OSM_TYPE_WAY = 2
} xmlOsmType;


/**
 * xmlTag_t:
 *
 * saves tagging information for whatever type
 */
typedef struct xmlTag_t {
    xmlChar* key;
    xmlChar* value;
    struct xmlTag_t* next;
} xmlTag_t;


/**
 * xmlNode_t:
 *
 * a node type a node save geodesic information
 */
typedef struct xmlNode_t {
    unsigned int id;
    double lat;
    double lon;
    xmlTag_t* tags;
} xmlNode_t;


/**
 * xmlWayPoint_t:
 *
 * a way point knows an id which points towards a node. A way point also knows
 * the next way point in a chain of waypoints which results in a way.
 */
typedef struct xmlWayPoint_t {
    unsigned int id;
    struct xmlWayPoint_t* next;
} xmlWayPoint_t;


/**
 * xmlWay_t:
 *
 * a way knows its id, can be tagged and contains several waypoints.
 */
typedef struct xmlWay_t {
    unsigned int id;
    xmlTag_t* tags;
    xmlWayPoint_t* points;
} xmlWay_t;


/**
 * osmXmlHandle:
 *
 * save information about the current element while parsing. element can be
 * stolen by bending the pointer towards NULL - not recommended since you then
 * have to free it yourself.
 */
typedef struct osmXmlHandle {
    xmlTextReaderPtr reader;
    xmlOsmType type;
    void* element;
} osmXmlHandle;


    
osmXmlHandle*
    osmNewXmlReader( const char *URI );

void
    osmFreeReader( osmXmlHandle* );

int
    osmNextElement( osmXmlHandle* );
    

