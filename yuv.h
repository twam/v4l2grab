#ifndef _YUV_H_
#define _YUV_H_

void YUV422toRGB888(int width, int height, unsigned char *src, unsigned char *dst);
void YUV420toRGB888(int width, int height, unsigned char *src, unsigned char *dst);

#endif
