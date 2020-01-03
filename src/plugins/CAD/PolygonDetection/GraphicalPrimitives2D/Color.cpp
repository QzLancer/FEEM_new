#include "Color.h"
#include "../macros.h"

#include <math.h>
#include <stdio.h>

/*
Color::Color(void)
{
}

Color::~Color(void)
{
}
*/
//////////////////////////////////////////////////////////////////////////
// NOTE:
// r,g,b values are from 0 to 1
// h = [0,360], s = [0,1], v = [0,1]
//		if s == 0, then h = -1 (undefined)
//////////////////////////////////////////////////////////////////////////



/***
* @descr converts RGB triplet to a Hex string
* @param the RGB triplet
* @return the string with the corresponding value in ASCII
*/
std::string Color::RGBtoHEX(float r, float g, float b) {
  char color_hex[16];
  sprintf(color_hex,"#000000"); // black by default
  
  if ((r>=0 && r<=1) && (g>=0 && g<=1) && (b>=0 && b<=1))
	  sprintf(color_hex,"#%2x%2x%2x",(unsigned int)(r*255), (unsigned int)(g*255), (unsigned int)(b*255));

  return std::string(color_hex);
}

/***
* @descr converts RGB triplet to HSV triplet
* @param the RGB triplet and three pointers to the HSV triplet
* @see if any of the pointer to HSV triplet is nullptr, nothing is done 
*/
void Color::RGBtoHSV( float r, float g, float b, float *h, float *s, float *v )
{
	if (h && s && v)
	{
		float min, max, delta;

		min = MIN(MIN(r, g), b);
		max = MAX(MAX(r, g), b);
		*v = max;				// v

		delta = max - min;

		if( max != 0 )
			*s = delta / max;		// s
		else {
			// r = g = b = 0		// s = 0, v is undefined
			*s = 0;
			*h = -1;
			return;
		}

		if( r == max )
			*h = ( g - b ) / delta;		// between yellow & magenta
		else if( g == max )
			*h = 2 + ( b - r ) / delta;	// between cyan & yellow
		else
			*h = 4 + ( r - g ) / delta;	// between magenta & cyan

		*h *= 60;				// degrees
		if( *h < 0 )
			*h += 360;
	}

}


/***
* @descr converts an HSV triplet to an RGB triplet
* @param three pointers to the RGB triplet and the HSV triplet
* @see if any of the pointer to HSV triplet is nullptr, nothing is done 
*/
void Color::HSVtoRGB( float *r, float *g, float *b, float h, float s, float v )
{
	int i;
	float f, p, q, t;

	if( s == 0 ) {
		// achromatic (grey)
		*r = *g = *b = v;
		return;
	}

	h /= 60;			// sector 0 to 5
	i = (int) floor( h );
	f = h - i;			// factorial part of h
	p = v * ( 1 - s );
	q = v * ( 1 - s * f );
	t = v * ( 1 - s * ( 1 - f ) );

	switch( i ) {
		case 0:
			*r = v;
			*g = t;
			*b = p;
			break;
		case 1:
			*r = q;
			*g = v;
			*b = p;
			break;
		case 2:
			*r = p;
			*g = v;
			*b = t;
			break;
		case 3:
			*r = p;
			*g = q;
			*b = v;
			break;
		case 4:
			*r = t;
			*g = p;
			*b = v;
			break;
		default:		// case 5:
			*r = v;
			*g = p;
			*b = q;
			break;
	}

}
