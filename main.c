
#include <msp430f249.h>
#define uchar unsigned char
#define uint unsigned int
#define SHIFT_NUM 8 //共八个灯

enum LED_MODE
{
  LEFT_SHIFT_ON,
  RIGHT_SHIFT_ON,
  LEFT_SHIFT_OFF,
  RIGHT_SHIFT_OFF,
  ON,
  OFF,
};


enum LED_MODE mode;

/*软件延迟ms主程序*/
 
void delayus(uint t)
{
    uint i;
    while(t--){
        for(i=1300;i>0;i--);
  }
}

void main( void )
{
    uint mask = 0x01;
    uchar i;
    uchar mode = LEFT_SHIFT_ON;
    // Stop watchdog timer to prevent time out reset
    WDTCTL = WDTPW + WDTHOLD;
    P1DIR = 0xFF;
    P1SEL = 0x00;
    P1OUT = 0xFF;
    while (1)
    {
      for(i=0;i<SHIFT_NUM;i++)
      {
        switch(mode)
            {
            case 0:
              mask <<= 1;
              if (mask == 0x100)
                mask = 0x80;
              break;
            case 1:
              mask >>= 1;
              if (mask == 0x00)
                mask = 0x01;
              break;
	    case 2:
              mask <<= 1;
	      mask |= 0x01;
	      if (mask == 0x1FF)
		mask = 0xFF;
	      break;
	    case 3:
	      mask >>= 1;
	      mask &=~ 0x80;
	      if (mask == 0x00)
		mask = 0x01;
	      break;
            case 4:
              mask |= 0xFF;
              break;
            case 5:
              mask &=~ 0xFF;
              break;
	    }
            P1OUT =~ mask;
            delayus(8);
        
      }
      if(++mode == 6) 
      {
        mask |= 0x01;
        mode = 0;
      }
    }

}
