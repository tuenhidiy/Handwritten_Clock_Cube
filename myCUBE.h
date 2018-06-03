/*
Name    : myCUBE.h
Project : LED CUBE 16x8x8 (8x8x8 RED & 8x8x8 GREEN)
Version : 1.0
Date    : 03.06.2018
Author  : tuenhidiy
Email   : tuenhi.n2012@gmail.com
*/

#ifndef myCUBE_h
  #define myCUBE_h
  #include "myCUBEClass.h"

  myCUBE myCUBE;
 
    ISR(TIMER1_COMPA_vect)
    { 
      myCUBE.Show();
    }

#endif
