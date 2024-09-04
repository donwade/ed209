#include <Arduino.h>

int RGB888to565 (uint8_t *in, uint16_t *out, uint32_t size)
{
    uint32_t by_888 = 0;
    uint32_t by_565 = 0;

    // don't look too close, the RGB888 does have its
    // R and G swapped (h/w bug) so we swap it back for
    // color correctness.

    while(size--){
        uint16_t R, G, B;
        uint16_t mix;
        B = in[by_888++] >> 3; // 5 bit accuracy
        G = in[by_888++] >> 2; // 6 bit accuracy
        R = in[by_888++] >> 3; // 5 bit accuracy
        mix = (R << (5+6)) | (G << (5+0)) |  B;
        out[by_565++] = mix;
        //if (!(by_565 % 32)) printf("0x%02x 0x%02x 0x%02x 0x%04x \n ", R, G, B, mix);
    }
    return 1;
}

typedef struct DIM
{
    uint16_t x;
    uint16_t y;
}DIM;

DIM dims[] =
{
    {96,	96},     //FRAMESIZE_96X96

    {160,	120},    //FRAMESIZE_QQVGA
    {176,	144},    //FRAMESIZE_QCIF
    {240,	176},    //FRAMESIZE_HQVGA
    {240,	240},    //FRAMESIZE_240X240
    {320,	240},    //FRAMESIZE_QVGA

    {400,	296},    //FRAMESIZE_CIF
    {480,	320},    //FRAMESIZE_HVGA
    {640,	480},    //FRAMESIZE_VGA
    {800,	600},    //FRAMESIZE_SVGA
    {1024,	768},    //FRAMESIZE_XGA

    {1280,	720},    //FRAMESIZE_HD
    {1280,	1024},   //FRAMESIZE_SXGA
    {1600,	1200},   //FRAMESIZE_UXGA
    {1920,	1080},   //FRAMESIZE_FHD
    {720,	1280},   //FRAMESIZE_P_HD

    {864,	1536},   //FRAMESIZE_P_3MP
    {2048,	1536},   //FRAMESIZE_QXGA
    {2560,	1440},   //FRAMESIZE_QHD
    {2560,	1600},   //FRAMESIZE_WQXGA
    {1080,	1920},   //FRAMESIZE_P_FHD

    {2560,	1920}    //FRAMESIZE_QSXGA
};

bool get_dims( uint8_t index, uint16_t *w, uint16_t *h, uint32_t *numPixels)
{
	if (index <= sizeof(dims)/sizeof(DIM))
	{
		*w = dims[index].x;
		*h = dims[index].y;
		*numPixels = dims[index].x * dims[index].y;
		return true;
	}
	else
	{
		*w = 0;
		*h = 0;
		*numPixels = 0;
		return false;
	}
}

static volatile	uint32_t dwn, across;

bool grey2rgb888 ( uint16_t startX, uint16_t startY, uint16_t wide, uint16_t height,
				   uint8_t *pBufGrey, uint16_t width_grey, uint16_t height_grey,
				   uint8_t *pBuff888, uint16_t width_888, uint16_t height888)
{
	//uint8_t *pSrcHome =  pBufGrey + startY * width_grey + startX;
    //uint8_t *pDestHome = pBuff888;
   	int16_t foo;

    for (dwn = 0; dwn < height; dwn++)
    {

    	uint8_t *pSrcRow  = pBufGrey  + dwn * width_grey;
    	uint8_t *pDestRow = pBuff888 + dwn * width_888;

		for (across = 0; across < wide; across++)
		{
	    	//log_i("across = %d / %d", across, wide);
			uint8_t grey = *(pSrcRow + across);

			*(pDestRow + across * 3 + 0) = grey;
			*(pDestRow + across * 3 + 1) = grey;
			*(pDestRow + across * 3 + 2) = grey;
		}
	  	log_i("dwn = %d / %d ", dwn, height);
    }
  	//log_i("dwn = %d / %d ac = %d / %d  foo= %d", dwn, height, across, wide, foo);
}

