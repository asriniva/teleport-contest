#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stddef.h>
#pragma pack(push,1)
typedef struct {uint16_t bfType;uint32_t bfSize;uint16_t bfReserved1,bfReserved2;uint32_t bfOffBits;} BMPFILEHEADER;
typedef struct {uint32_t biSize;int32_t biWidth,biHeight;uint16_t biPlanes,biBitCount;uint32_t biCompression,biSizeImage;int32_t biXPelsPerMeter,biYPelsPerMeter;uint32_t biClrUsed,biClrImportant;} BMPINFOHEADER;
#pragma pack(pop)
typedef struct {uint8_t r,g,b;} RGB;
