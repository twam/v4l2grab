/***************************************************************************
 *   Copyright (C) 2012 by Tobias Müller                                   *
 *   Tobias_Mueller@twam.info                                              *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

// use ITU-R float conversion for YUV420toRGB888 by default
#if !defined(ITU_R_FLOAT) && !defined(ITU_R_INT) && !defined(NTSC)
#define ITU_R_FLOAT
#endif

#if ((defined(ITU_R_FLOAT)) && (defined(ITU_R_INT)) && (defined(NTSC))) || ((defined(ITU_R_FLOAT)) && (defined(ITU_R_INT))) || ((defined(ITU_R_FLOAT)) && (defined(NTSC))) ||  ((defined(ITU_R_INT)) && (defined(NTSC)))
#error Only one conversion for YUV420toRGB888 is allowed!
#endif

#define CLIP(x) ( (x)>=0xFF ? 0xFF : ( (x) <= 0x00 ? 0x00 : (x) ) )

/**
	Convert from YUV format to RGB. Formulae are described on http://en.wikipedia.org/wiki/YUV
**/
static void YUYtoRGB(unsigned char* y, unsigned char* u, unsigned char* v, unsigned char* r, unsigned char* g, unsigned char* b)
{
#ifdef ITU_R_FLOAT
			// ITU-R float
			*r = CLIP((double)*y + 1.402*((double)*v-128.0));
			*g = CLIP((double)*y - 0.344*((double)*u-128.0) - 0.714*((double)*v-128.0));
			*b = CLIP((double)*y + 1.772*((double)*u-128.0));
#endif

#ifdef ITU_R_INT
			// ITU-R integer
			*r = CLIP( *y + (*v-128) + ((*v-128) >> 2) + ((*v-128) >> 3) + ((*v-128) >> 5) );
			*g = CLIP( *y - (((*u-128) >> 2) + ((*u-128) >> 4) + ((*u-128) >> 5)) - (((*v-128) >> 1) + ((*v-128) >> 3) + ((*v-128) >> 4) + ((*v-128) >> 5)) );  // 52 58
			*b = CLIP( *y + (*u-128) + ((*u-128) >> 1) + ((*u-128) >> 2) + ((*u-128) >> 6) );
#endif

#ifdef NTSC
			// NTSC integer
			*r = CLIP( (298*(*y-16) + 409*(*v-128) + 128) >> 8 );
			*g = CLIP( (298*(*y-16) - 100*(*u-128) - 208*(*v-128) + 128) >> 8 );
			*b = CLIP( (298*(*y-16) + 516*(*u-128) + 128) >> 8 );
#endif
}

/**
	Convert from YUV422 format to RGB888.

	\param width width of image
	\param height height of image
	\param src source
	\param dst destination
*/
void YUV422toRGB888(int width, int height, unsigned char *src, unsigned char *dst)
{
	int line, column;
	unsigned char *py, *pu, *pv;
	unsigned char r, g, b;
	unsigned char *tmp = dst;

	// This format is planar. The three components are three seperate sub-images
	// First the Y image with full resolution, than Cb and Cr with half resolution
	py = src;
	pu = src + 1;
	pv = src + 3;

	for (line = 0; line < height; ++line) {
		for (column = 0; column < width; ++column) {
			// convert YUV to RGB
			YUYtoRGB(py, pu, pv, &r, &g, &b);

			*tmp++ = r;
			*tmp++ = g;
			*tmp++ = b;

			// increase py every time
			py += 2;

			// increase pu,pv every second time
			if ((column & 1)==1) {
				pu += 4;
				pv += 4;
			}
		}
	}
}

/**
	Convert from YUV420 format to RGB888.

	\param width width of image
	\param height height of image
	\param src source
	\param dst destination
*/
void YUV420toRGB888(int width, int height, unsigned char *src, unsigned char *dst)
{
	int line, column;
	unsigned char *py, *pu, *pv;
	unsigned char r, g, b;
	unsigned char *tmp = dst;

	// In this format each four bytes is two pixels. Each four bytes is two Y's, a Cb and a Cr.
	// Each Y goes to one of the pixels, and the Cb and Cr belong to both pixels.

	unsigned char *base_py = src;
	unsigned char *base_pu = src+(height*width);
	unsigned char *base_pv = src+(height*width)+(height*width)/4;

	for (line = 0; line < height; ++line) {
		for (column = 0; column < width; ++column) {
			py = base_py+(line*width)+column;
			pu = base_pu+(line/2*width/2)+column/2;
			pv = base_pv+(line/2*width/2)+column/2;

			// convert YUV to RGB
			YUYtoRGB(py, pu, pv, &r, &g, &b);

			*tmp++ = r;
			*tmp++ = g;
			*tmp++ = b;
		}
	}
}
