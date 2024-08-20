#include <stdio.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define RGBto565(r,g,b) ((((r) & 0xF8) << 8) | (((g) & 0xFC) << 3) | ((b) >> 3))

// -------------------------------------------------------------------
uint16_t *convert( uint16_t w, uint16_t h, uint8_t *_input)
{
  int i, x, y, j;

  long bmpsize = w * h;
  const int TRIPLET = 3;
  const int LINE_WIDTH = TRIPLET * w;

  uint16_t *output =(uint16_t *) malloc( w * h * sizeof(uint16_t));
  uint16_t *temp = output;

  int r,g,b;

   printf("%s:  w=%d, h=%d \n",__FUNCTION__,w,h);

    uint32_t do_crlf = 0;
    for(int row= 0 ; row< h; row++)
    {
        for(int column=0; column < w; column++)
        {
            b = _input[column + 0 + row * LINE_WIDTH];
            g = _input[column + 1 + row * LINE_WIDTH];
            r = _input[column + 2 + row * LINE_WIDTH];

			uint16_t c;
			if ( 0
			  // ||row == 0
			  // || column == 0
			  // || row == (h-1)
			   || column == (w-1)
				)
				c = 0xFFFF;
			else
            	//c = 0x3333;
            	c = RGBto565(r,g,b);

			*temp = c;
			temp++;

           // if((do_crlf & 0xf)==0 && do_crlf>0) printf("\n  ");
           // printf("0x%04x,",c); do_crlf++;
       }
  }
  printf("\n\n");
  return output;
}


