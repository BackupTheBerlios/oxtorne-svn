/**
 *******************************************************************************
 * <P> KulaMath is the C interface to the oxtorne Library. </P>
 *
 * @author      Markus S Friese
 *
 * @date		28. March 2009
 *******************************************************************************
 */


/*
 *******************************************************************************
 * Include only once
 *******************************************************************************
 */
#ifndef OXWORLDMATHINTERFACE_INCLUDE
#define OXWORLDMATHINTERFACE_INCLUDE

/*
 *******************************************************************************
 * If compiling from C++ we need an extern "C" definition
 *******************************************************************************
 */
#ifdef __cplusplus
	#define OX extern "C"
#else
	#define OX
#endif

/*
 *******************************************************************************
 * Structure used to represent a three dimensional vector of type integer
 *******************************************************************************
 */
typedef struct {
	int x, y, z;
} kPoint3i;

/*
 *******************************************************************************
 * Structure used to represent a three dimensional vector of type floating point
 *******************************************************************************
 */
typedef struct {
	float x, y, z;
} kPoint3f;

/*
 *******************************************************************************
 * Basic type factories to create geometry objects
 *******************************************************************************
 */
OX kPoint3f make_point3f( const float, const float, const float );
OX kPoint3i make_point3i( const int, const int, const int );

OX kPoint3f plus3f( const kPoint3f*, const kPoint3f* );
OX kPoint3i plus3i( const kPoint3i*, const kPoint3i* );

OX kPoint3f minus3f( const kPoint3f*, const kPoint3f* );
OX kPoint3i minus3i( const kPoint3i*, const kPoint3i* );

OX kPoint3f times3f( const kPoint3f*, const float );
OX kPoint3i times3i( const kPoint3i*, const int );

OX kPoint3f normalize3f( const kPoint3f* );

OX kPoint3f rotate3f( const kPoint3f* );


#endif
