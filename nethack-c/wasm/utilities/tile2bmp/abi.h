#include "config.h"
#include "tile.h"
#define PACK __attribute__((packed))
typedef struct tagBMIH {
    uint32_t biSize;
    int32_t biWidth;
    int32_t biHeight;
    uint16_t biPlanes;
    uint16_t biBitCount;
    uint32_t biCompression;
    uint32_t biSizeImage;
    int32_t biXPelsPerMeter;
    int32_t biYPelsPerMeter;
    uint32_t biClrUsed;
    uint32_t biClrImportant;
} PACK BITMAPINFOHEADER;

typedef struct tagBMFH {
    uint16_t bfType;
    uint32_t bfSize;
    uint16_t bfReserved1;
    uint16_t bfReserved2;
    uint32_t bfOffBits;
} PACK BITMAPFILEHEADER;

typedef struct tagRGBQ {
    uint8_t rgbBlue;
    uint8_t rgbGreen;
    uint8_t rgbRed;
    uint8_t rgbReserved;
} PACK RGBQUAD;
#define BI_RGB       0L
#define BI_RLE8      1L
#define BI_RLE4      2L
#define BI_BITFIELDS 3L

#define RGBQUAD_COUNT 256
#pragma pack(1)
struct tagBMP {
    BITMAPFILEHEADER bmfh;
    BITMAPINFOHEADER bmih;
    RGBQUAD bmaColors[RGBQUAD_COUNT];
    uchar packtile; /* start */
} PACK;
#pragma pack()
