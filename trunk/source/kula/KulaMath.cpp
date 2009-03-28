/**
 *******************************************************************************
 * <P> KulaMath is the C interface to the oxtorne Library. One might say here
 * comes a lot of memory copy operations and that's true. But refactoring is
 * always fun, so I don't care about moving memory here ;) </P>
 *
 * @author      Markus S Friese
 *
 * @date		28. March 2009
 *******************************************************************************
 */

#include "KulaMath.h"
#include "OxGeometry.h"

using namespace oxtorne;

/*
 *******************************************************************************
 * Tool to convert the float point to a float oxtorne point quickly
 *******************************************************************************
 */
inline point<float,3> to_point3f( const kPoint3f& p )
{
	return make_point( p.x, p.y, p.z );
}

/*
 *******************************************************************************
 * Tool to convert the float point to a integer oxtorne point quickly
 *******************************************************************************
 */
inline point<int,3> to_point3i( const kPoint3i& p )
{
	return make_point( p.x, p.y, p.z );
}

/*
 *******************************************************************************
 * Tool to convert the oxtorne point to the kPoint3f ( -> C ) float case
 *******************************************************************************
 */
inline kPoint3f to_kPoint3f( const point<float,3>& p )
{
	kPoint3f point;
	point.x = p[0];
	point.y = p[1];
	point.z = p[2];
	return point;
}

/*
 *******************************************************************************
 * Tool to convert the oxtorne point to the kPoint3f ( -> C ) integer case
 *******************************************************************************
 */
inline kPoint3i to_kPoint3i( const point<int,3>& p )
{
	kPoint3i point;
	point.x = p[0];
	point.y = p[1];
	point.z = p[2];
	return point;
}

/*
 *******************************************************************************
 * Implementation of the float vector factory
 *******************************************************************************
 */
kPoint3f make_point3f( const float x, const float y, const float z )
{
	kPoint3f point;
	point.x = x;
	point.y = y;
	point.z = z;
	return point;
}


/*
 *******************************************************************************
 * Implementation of the integer vector factory
 *******************************************************************************
 */
kPoint3i make_point3i( const int x, const int y, const int z )
{
	kPoint3i point;
	point.x = x;
	point.y = y;
	point.z = z;
	return point;
}


/*
 *******************************************************************************
 * Implementation of the plus opertation for float vectors
 *******************************************************************************
 */
kPoint3f plus3f( const kPoint3f* a, const kPoint3f* b )
{
	return to_kPoint3f( to_point3f(*a) + to_point3f(*b) );
}

/*
 *******************************************************************************
 * Implementation of the plus opertation for int vectors
 *******************************************************************************
 */
kPoint3i plus3i( const kPoint3i* a, const kPoint3i* b )
{
	return to_kPoint3i( to_point3i(*a) + to_point3i(*b) );
}

/*
 *******************************************************************************
 * Implementation of the plus opertation for float vectors
 *******************************************************************************
 */
kPoint3f minus3f( const kPoint3f* a, const kPoint3f* b )
{
	return to_kPoint3f( to_point3f(*a) - to_point3f(*b) );
}

/*
 *******************************************************************************
 * Implementation of the plus opertation for int vectors
 *******************************************************************************
 */
kPoint3i minus3i( const kPoint3i* a, const kPoint3i* b )
{
	return to_kPoint3i( to_point3i(*a) - to_point3i(*b) );
}

/*
 *******************************************************************************
 * Implementation of the times opertation for float vectors
 *******************************************************************************
 */
kPoint3f times3f( const kPoint3f* a, const float b )
{
	return to_kPoint3f( to_point3f(*a) * b );
}

/*
 *******************************************************************************
 * Implementation of the times opertation for int vectors
 *******************************************************************************
 */
kPoint3i times3i( const kPoint3i* a, const int b )
{
	return to_kPoint3i( to_point3i(*a) * b );
}

/*
 *******************************************************************************
 * Implementation of the normalization operator (only applicable to floats)
 *******************************************************************************
 */
OX kPoint3f normalize3f( const kPoint3f* a )
{
	return to_kPoint3f( normalize( to_point3f(*a) ) );
}

/*
 *******************************************************************************
 * Implementation of the rotation operator. This will use the first given vector
 * as the rotational axis and the second one will be rotate around that axis
 * by the given degree.
 *******************************************************************************
 */
OX kPoint3f rotate3f( const kPoint3f* axis, const kPoint3f* point, const float degree )
{
	vector<float,3> result = normalize( rotate( to_point3f(*axis), to_point3f(*point), degree ) );
	return make_point3f( result[0], result[1], result[2] );
}


