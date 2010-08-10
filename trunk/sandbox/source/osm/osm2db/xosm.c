
#include "xosm.h"

#include <stdio.h>
#include <string.h>


/**
 * xmlTagMake:
 *
 * Create a node with a key and a value pair. Initialized to NULL
 */
xmlTag_t*
xmlTagMake()
{
    xmlTag_t* tagObj = (xmlTag_t*) malloc( sizeof(xmlTag_t) );

    if (tagObj == NULL)
    {
        fprintf(stderr, "Out of memory during tag creation\n");
        return NULL;
    }
    
    tagObj->key = NULL;
    tagObj->value = NULL;
    tagObj->next = NULL;
    
    return tagObj;
}


/**
 * xmlTagFree:
 *
 * Free a given tag and also free every following tag
 */
void
xmlTagFree(xmlTag_t* t)
{
    if ( t == NULL )
        return;

    if ( t->next != NULL )
        xmlTagFree( t->next );
    
    if ( t->key != NULL )
        free( t->key );
    
    if ( t->value != NULL )
        free( t->value );

    free( t );
}


/**
 * xmlTagAddLast:
 *
 * Add a new tag to the end of the given list of tags
 */
void
xmlTagAddLast(xmlTag_t* head, xmlTag_t* element)
{
    if ( head->next != NULL )
    {
        return ( xmlTagAddLast(head->next, element) );
    }
    
    head->next = element;
}


/**
 * xmlWayPointMake:
 *
 * Create a waypoint and initialize everything to NULL
 */
xmlWayPoint_t*
xmlWayPointMake()
{
    xmlWayPoint_t* wayPntObj = (xmlWayPoint_t*) malloc(sizeof(xmlWayPoint_t));
    
    if (wayPntObj == NULL)
    {
        fprintf(stderr, "Out of memory during way point creation\n");
        return NULL;
    }
    
    wayPntObj->id = 0;
    wayPntObj->next = NULL;
    
    return wayPntObj;
}


/**
 * xmlWayPointFree:
 *
 * Free a waypoint and everything connected to that waypoint
 */
void
xmlWayPointFree(xmlWayPoint_t* t)
{
    if ( t == NULL )
        return;
    
    if ( t->next != NULL )
        xmlWayPointFree( t->next );
    
    free( t );
}


/**
 * xmlWayPointAddLast:
 *
 * Add a new point to the tail of the list of points
 */
void
xmlWayPointAddLast(xmlWayPoint_t* head, xmlWayPoint_t* element)
{
    if ( head->next != NULL )
    {
        return (xmlWayPointAddLast( head->next, element ));
    }
    
    head->next = element;
}


/**
 * xmlWayMake:
 *
 * Create a way and initialize everything to NULL
 */
xmlWay_t*
xmlWayMake()
{
    xmlWay_t* wayObj = (xmlWay_t*) malloc( sizeof(xmlWay_t) );

    if (wayObj == NULL)
    {
        fprintf(stderr, "Out of memory during way creation\n");
        return NULL;
    }
    
    wayObj->id = 0;
    wayObj->tags = NULL;
    wayObj->points = NULL;
    
    return wayObj;
}


/**
 * xmlWayFree:
 *
 * Free a way and everything connected to that way
 */
void
xmlWayFree(xmlWay_t* t)
{
    if ( t == NULL )
        return;
    
    if ( t->points != NULL )
        xmlWayPointFree( t->points );
    
    if ( t->tags != NULL )
        xmlTagFree( t->tags );
    
    free( t );
}


/**
 * xmlNodeMake:
 *
 * Create a node containing loaded values and tag pointer pointing to NULL
 */
xmlNode_t*
xmlNodeMake()
{
    xmlNode_t* nodeObj = (xmlNode_t*) malloc( sizeof(xmlNode_t) );

    if (nodeObj == NULL)
    {
        fprintf(stderr, "Out of memory during node creation\n");
        return NULL;
    }
    
    nodeObj->tags = NULL;
    nodeObj->id = 0;
    nodeObj->lat = 0.0;
    nodeObj->lon = 0.0;
    
    return nodeObj;
}


/**
 * xmlNodeFree:
 *
 * Free the node and all tags connected to that node
 */
void
xmlNodeFree(xmlNode_t* n)
{
    if ( n == NULL )
        return;

    if ( n->tags != NULL )
    {
        xmlTagFree( n->tags );
    }
    
    free( n );
}


/**
 * xmlTextReaderIsStartElement:
 *
 * Check, if current element is a node
 */
int
xmlTextReaderIsStartElement(xmlTextReaderPtr reader, xmlChar* key)
{
    // check if not opening tag
    if ( xmlTextReaderNodeType(reader) != XML_READER_TYPE_ELEMENT )
        return 0;
    
    // name must match key - then it's okay
    return !xmlStrcmp( xmlTextReaderConstName(reader), key );
}


/**
 * xmlTextReaderIsEndElement:
 *
 * Check, if current element is a node
 */
int
xmlTextReaderIsEndElement(xmlTextReaderPtr reader, xmlChar* key)
{
    // check if not opening tag
    if ( xmlTextReaderNodeType(reader) != XML_READER_TYPE_END_ELEMENT )
        return 0;
    
    // name must match key - then it's okay
    return !xmlStrcmp( xmlTextReaderConstName(reader), key );
}


/**
 * xmlTextReaderParseAttributeToUInt:
 *
 * Parse to an unsigned integer value
 */
unsigned int
xmlTextReaderParseAttributeToUInt(xmlTextReaderPtr reader, xmlChar* key)
{
    // try parsing the integer value
    xmlChar* text = xmlTextReaderGetAttribute(reader, key);
    
    // Parse the integer value
    unsigned int value = atoi( (char*) text );
    
    if (value == 0)
    {
        // possible error
        fprintf( stderr, "Found %i while parsing %s\n", value, key );
    }
    
    // attributes must be freed
    free(text);
    
    // return the result
    return value;
}


/**
 * xmlTextReaderParseAttributeToDouble:
 *
 * Parse to a double value
 */
double
xmlTextReaderParseAttributeToDouble(xmlTextReaderPtr reader, xmlChar* key)
{
    // try parsing the integer value
    xmlChar* text = xmlTextReaderGetAttribute(reader, key);
    
    // Parse the integer value
    double value = atof( (char*) text );
    
    if (value == 0.0)
    {
        // possible error
        fprintf( stderr, "Found %f while parsing %s\n", value, key );
    }
    
    // attributes must be freed
    free(text);
    
    // return the result
    return value;
}


/**
 * xmlTextReaderParseAttributeToChar:
 *
 * Parse to a character array (as a copy to the heap). The string is directly
 * copied from the libxml to the local heap, therefor the stringtype
 */
xmlChar*
xmlTextReaderParseAttributeToChar(xmlTextReaderPtr reader, xmlChar* key)
{
    // return the attribute, reallocation not required
    return xmlTextReaderGetAttribute(reader, key);
}



/**
 * xmlTextReaderParseTag:
 *
 * Parse an element which should actually be a tag
 */
xmlTag_t*
xmlTextReaderParseTag(xmlTextReaderPtr reader)
{
    // check if opening tag element
    if (!xmlTextReaderIsStartElement(reader, BAD_CAST"tag"))
        return NULL;
    
    // seems okay, parse tag
    xmlTag_t* next = xmlTagMake();
    next->key = xmlTextReaderParseAttributeToChar(reader, BAD_CAST"k");
    next->value = xmlTextReaderParseAttributeToChar(reader, BAD_CAST"v");
    return next;
}


/**
 * xmlTextParseWayPoint:
 *
 * Parse a waypoint. multiple waypoint build a way
 */
xmlWayPoint_t*
xmlTextParseWayPoint(xmlTextReaderPtr reader)
{
    // check if opening tag element
    if (!xmlTextReaderIsStartElement(reader, BAD_CAST"nd"))
        return NULL;
    
    // seems okay, parse waypoint
    xmlWayPoint_t* next = xmlWayPointMake();
    next->id = xmlTextReaderParseAttributeToUInt(reader, BAD_CAST"ref");
    return next;
}


/**
 * xmlTextReaderParseNode:
 *
 * Parse the current subtree, which should actually be a node
 */
xmlNode_t*
xmlTextReaderParseNode(xmlTextReaderPtr reader)
{
    // check if opening node element
    if (!xmlTextReaderIsStartElement(reader, BAD_CAST"node"))
        return NULL;
    
    // Depth of the current element
    const int depth = xmlTextReaderDepth(reader);
    
    // seems okay, create node
    xmlNode_t* next = xmlNodeMake();
    
    // parse its attributes
    next->id = xmlTextReaderParseAttributeToUInt(reader, BAD_CAST"id");
    next->lat = xmlTextReaderParseAttributeToDouble(reader, BAD_CAST"lat");
    next->lon = xmlTextReaderParseAttributeToDouble(reader, BAD_CAST"lon");

    // start parsing children
    while(xmlTextReaderRead(reader) == 1 && xmlTextReaderDepth(reader) > depth)
    {
        // check out the tags
        xmlTag_t* tag = xmlTextReaderParseTag(reader);
        if (next->tags == NULL)
        {
            next->tags = tag;
        }
        else
        {
            xmlTagAddLast(next->tags, tag);
        }
    }
    
    return next;
}


/**
 * xmlTextReaderParseWay:
 *
 * Parse the current subtree, which should actually be a way
 */
xmlWay_t*
xmlTextReaderParseWay(xmlTextReaderPtr reader)
{
    // check if opening node element
    if (!xmlTextReaderIsStartElement(reader, BAD_CAST"way"))
        return NULL;
    
    // Depth of the current element
    const int depth = xmlTextReaderDepth(reader);
    
    // seems okay, create node
    xmlWay_t* next = xmlWayMake();
    
    // parse its attributes (only id here)
    next->id = xmlTextReaderParseAttributeToUInt(reader, BAD_CAST"id");

    // start parsing children
    while(xmlTextReaderRead(reader) == 1 && xmlTextReaderDepth(reader) > depth)
    {
        // check out the tags
        xmlTag_t* tag;
        
        if ( tag = xmlTextReaderParseTag(reader) )
        {
            if (next->tags == NULL)
            {
                next->tags = tag;
            }
            else
            {
                xmlTagAddLast( next->tags, tag );
            }
            
            // skip the loop tail
            continue;
        }
        
        // check out the way markers
        xmlWayPoint_t* wPoint;
        
        if ( wPoint = xmlTextParseWayPoint(reader) )
        {
            if (next->points == NULL)
            {
                next->points = wPoint;
            }
            else
            {
                xmlWayPointAddLast( next->points, wPoint );
            }

            // skip the loop tail
            continue;
        }
    }
    
    return next;
}






/**
 * xmlOsmNodeType:
 *
 * Get the element type of the current Element
 */
int osmXmlNodeType (xmlTextReaderPtr reader)
{
    // No element -> no type
    if (xmlTextReaderNodeType( reader ) != XML_READER_TYPE_ELEMENT)
        return XML_OSM_TYPE_NONE;
    
    // Get the element's name
    const xmlChar* elementName = xmlTextReaderConstName( reader );
    
    // compare strings
    if (!xmlStrcmp( elementName, BAD_CAST"node"))
        return XML_OSM_TYPE_NODE;
    
    // compare strings
    if (!xmlStrcmp( elementName, BAD_CAST"way"))
        return XML_OSM_TYPE_WAY;
    
    // more does not seem interesting
    return XML_OSM_TYPE_NONE;
}


/**
 * osmXmlFreeElement:
 *
 * Free the entire element from the heap
 */
void
osmXmlFreeElement(void** element, xmlOsmType* type )
{
    // do we have to free the element?
    if ( element != NULL )
    {
        if ( *type == XML_OSM_TYPE_WAY )
        {
            // seems like a way
            xmlWayFree( *element );
        }
        
        if ( *type == XML_OSM_TYPE_NODE )
        {
            // seems like a node
            xmlNodeFree( *element );
        }
    }
    
    *element = NULL;
    *type = XML_OSM_TYPE_NONE;
}


/**
 * osmNewXmlReader:
 *
 * Create a new Reader which reads input from XML files
 */
osmXmlHandle* osmNewXmlReader( const char *URI )
{
    // supply a new handle
    osmXmlHandle* handle;
    
    // alloc new handle on the heap
    handle = (osmXmlHandle*) malloc( sizeof(osmXmlHandle) );
    
    // set up new handle
    handle->element = NULL;
    handle->type = XML_OSM_TYPE_NONE;

    // this initialize the library and check potential API mismatches
    // between the version it was compiled for and the actual shared
    // library used.
    LIBXML_TEST_VERSION

    // reader which reads from file
    handle->reader = xmlReaderForFile(URI, NULL, 0);
    
    // done, get result
    return handle;
}


/**
 * osmFreeReader:
 *
 * Free everything the reader owns
 */
void osmFreeReader( osmXmlHandle* handle )
{
    // is this handle existing?
    if ( handle == NULL)
        return;
    
    // we free all available content
    osmXmlFreeElement( &handle->element, &handle->type );
    
    if ( handle->reader != NULL )
    {
        // Free the reader
        xmlFreeTextReader( handle->reader );

        // Cleanup function for the XML library.
        xmlCleanupParser();

        // this is to debug memory for regression tests
        xmlMemoryDump();
    }
    
    // free and go
    free( handle );
}


/**
 * osmNextElement:
 *
 * Go down the xml till the next node of interest, if any. if none fall out
 * and we're done. returns 1 if parsed something, return 0 on completion.
 */
int osmNextElement(osmXmlHandle* handle)
{
    // first clean up the old element
    osmXmlFreeElement( &handle->element, &handle->type );

    // use the reader for parsing
    xmlTextReaderPtr reader = handle->reader;
    
    // read while there are no problems
    while(xmlTextReaderRead( reader ) == 1)
    {
        // look for known types
        switch(osmXmlNodeType( reader ))
        {
            // looks pretty unknown
            case XML_OSM_TYPE_NONE:
            {
                // don't care value
                continue;
            }
            
            // looks like a node -> parse and return
            case XML_OSM_TYPE_NODE:
            {
                handle->element = xmlTextReaderParseNode( reader );
                handle->type = XML_OSM_TYPE_NODE;
                return 1;
            }
            
            // looks like a way -> parse and return
            case XML_OSM_TYPE_WAY:
            {
                handle->element = xmlTextReaderParseWay( reader );
                handle->type = XML_OSM_TYPE_WAY;
                return 1;
            }
        }
    }
    
    // fall out from parsing - we're done
    return 0;
}


/*******************************************************************************
 * DEBUGGING
 */
 
/*int main(int argc, char **argv) {
    if (argc != 2)
    {
        printf("Usage: XmlTest filename.xml\n");
        return(1);
    }

    osmXmlHandle* handle = osmNewXmlReader( argv[1] );
    
    
    while ( osmNextElement(handle) > 0 )
    {
        if (handle->type == XML_OSM_TYPE_NODE)
        {
            xmlNode_t* node = (xmlNode_t*)handle->element;
            printf("<Node lon:%f lat:%f id:%i>\n", node->lon, node->lat, node->id);
        }
        
        if (handle->type == XML_OSM_TYPE_WAY)
        {
            xmlWay_t* way = (xmlWay_t*)handle->element;
            printf("<Way id:%i>\n", way->id);
            
			xmlTag_t* tag;
            for (tag = way->tags; tag != NULL; tag = tag->next)
            {
                printf("\t<Tag key:%s value:%s>\n", tag->key, tag->value);
            }
        }
    }
    
    osmFreeReader( handle );

    // that's it
    return(0);
}*/
