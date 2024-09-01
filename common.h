enum YUV_OPTIONS                                                                       
{
     BIG_ENDIAN_ORDER = 1, //RGB reading from low to high memory.  Otherwise, uses nativ
     PAD_4B = 2, // pad 0x00 on the high B. ie 0x00RRGGBB
};
#define 	TEST_BIT_MASK(y, flag)   ( ((y)&(flag)) == (flag) )

int crop_and_interpolate_rgb888(
    const uint8_t *srcImage,
    int srcWidth,
    int srcHeight,
    uint8_t *dstImage,
    int dstWidth,
    int dstHeight);


